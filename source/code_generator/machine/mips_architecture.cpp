/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                    **/
/************************************************************************************************************************/

#include "mips_architecture.h"


#include <sstream>
using namespace std;

//const int MIPSArchitecture::WORD_SIZE = 4;

MIPSArchitecture::MIPSArchitecture(SymbolTable * symbolTable, IntermediateCode * intermediateCode)
    : MachineCode(symbolTable, intermediateCode)
{
    registers_.push_back("$t0");
    registers_.push_back("$t1");
    registers_.push_back("$t2");
    registers_.push_back("$t3");
    registers_.push_back("$t4");
    registers_.push_back("$t5");
    registers_.push_back("$t6");
    registers_.push_back("$t7");

}

void MIPSArchitecture::generateCode()
{

    vector<BasicBlock *> *basicBlocks = this->intermediateCode_->getBasicBlocks();
    genStartingCode();

    for(size_t i = 0; i < basicBlocks->size(); i++) {
        //gen("# basic block");
        this->initDescriptorTables();

        BasicBlock * basicBlock = basicBlocks->at(i);
        basicBlock->optimise();

        functionInfo = NULL;

        if(basicBlock->isStartingFunction()) {
            //string MIPSInstruction = "\t.text ";
            //MIPSInstruction += getFunctionLabel(basicBlock->getFunctionName());
            //gen(MIPSInstruction);
            genLabel( getFunctionLabel(basicBlock->getFunctionName()) );

            list <IdentifierInformation *> * identifierInfoList = this->symbolTable_->getIdentifierInfoList();
            list <IdentifierInformation *>::iterator it = identifierInfoList->begin();

            while(it != identifierInfoList->end() && functionInfo == NULL) {

                if( (*it)->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_FUNCTION &&
                        strcmp((*it)->getIdentifier(), basicBlock->getFunctionName()) == 0) {

                    functionInfo = (FunctionInformation*)(*it);
                }

                it++;
            }

            if(functionInfo != NULL) {
                genPrologue(functionInfo);
            } else if(!strcmp(basicBlock->getFunctionName(), intermediateCode_->getMainFunctionName())) {
                genPrologue(0);
            }

        }

        vector<Instruction *> * instructionVector = basicBlock->getInstructionVector();

        for(size_t j = 0; j < instructionVector->size() ; j++) {
            Instruction * instruction = instructionVector->at( j );

                        //instruction->debug(cout);
            if(!instruction->isDeadCode()) {

                if(
                    (
                        instruction->getInstructionType()==INSTRUCTION_TYPE_GOTO ||
                        instruction->getInstructionType()==INSTRUCTION_TYPE_CONDITIONAL_GOTO ||
                        instruction->getInstructionType()==INSTRUCTION_TYPE_RETURN
                        // || instruction->getInstructionType()==INSTRUCTION_TYPE_CALL
                    )
                ) {
                    //saveAliveVariables();
                    saveVariables();
                }
                this->updateVariablesStatus(instruction);
                this->genInstruction(instruction);
            }
        }

        //SALVAR NA MEMORIA AS VARIÁVEIS NAO SALVAS,
        //E QUE SAO VIVAS NA SAIDA
        saveVariables();
        //saveAliveVariables();

        /*
        if(basicBlock->isLastFunctionBlock()){
            if(functionInfo != NULL) {
                genEpilogue(functionInfo);
            }else if(!strcmp(basicBlock->getFunctionName(), intermediateCode_->getMainFunctionName())){
                genEpilogue(0);
            }
        }
        */

        delete instructionVector;
        delete basicBlock;
    }
    functionInfo = NULL;
	 //gen("\tli $v0, 10"); // system call for exit
    //gen("\tsyscall");
    delete basicBlocks;

}


void MIPSArchitecture::genStartingCode()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    list <string> *stringList = symbolTable_->getStringList();
    IdentifierInformation *info;
    char temp[128];
    string MIPSInstruction;

    MIPSInstruction = "#file \"";
    MIPSInstruction += baseFileName_;
    MIPSInstruction += "\"";
    gen(MIPSInstruction);

    gen("\t.data");

    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation * varInfo = (VariableInformation *)info;
            if(varInfo->getScopeLevel()==GLOBAL_SCOPE) { //MODULE SCOPE
                MIPSInstruction = getGlobalVariableLabel(info);
                //MIPSInstruction += itoa( varInfo->getOffset(), temp, 10 );
                MIPSInstruction += ":\t.word\t0";
                gen(MIPSInstruction);
            }
        }
    }

    gen("new_line_str:\t.asciiz \"\\n\"");

    int strCount = 1;
    for(list<string>::iterator it = stringList->begin(); it!=stringList->end(); it++, strCount++) {
        MIPSInstruction = "str_";
        //MIPSInstruction += itoa( strCount, temp, 10 );
        sprintf(temp, "%d", strCount);
        MIPSInstruction += temp;
        MIPSInstruction += ":";
        //gen(MIPSInstruction);
        MIPSInstruction += "\t.asciiz ";
        MIPSInstruction += getMachineString(*it);
        gen(MIPSInstruction);
    }

    gen("\t .text");

    //MIPSInstruction = "\t.globl ";
    //MIPSInstruction += getFunctionLabel(intermediateCode_->getMainFunctionName());
    //gen("\t.globl _main");
    //gen(MIPSInstruction);
}

/*
void MIPSArchitecture::initDescriptorTables()
{
    for(unsigned int reg = 0; reg<registers_.size(); reg++){
        RegisterDescriptor * registerDescriptor = new RegisterDescriptor();
        this->registerDescriptorTable_.set(reg, registerDescriptor);
    }
}
*/

int MIPSArchitecture::getOffset(IdentifierInformation *identifierInformation)
{
    int offset = 0;
    if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
        FormalParameterInformation *formalParamameter = (FormalParameterInformation *)identifierInformation;
        offset = (formalParamameter->getOffset()-1)*(WORD_SIZE);
    } else if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
        VariableInformation *variable = (VariableInformation *)identifierInformation;
        offset = -( variable->getOffset()*(WORD_SIZE) );
    }
    return offset;
}

string MIPSArchitecture::getGlobalVariableLabel(IdentifierInformation *identifierInformation)
{
	string address;
	if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
        //TODO
		if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
			VariableInformation *variable = (VariableInformation *)identifierInformation;
			address = "_";
			address += variable->getIdentifier();
		}
		return address;
	}
}

string MIPSArchitecture::getVariableAddress(IdentifierInformation *identifierInformation)
{
    char temp[32];
    if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
        //TODO
        return getGlobalVariableLabel(identifierInformation);

        /*
        MIPSInstruction = "\tmovl _";
        if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation *variable = (VariableInformation *)identifierInformation;
            //MIPSInstruction += variable->getOffset();
            MIPSInstruction += variable->getIdentifier();
        }
        MIPSInstruction += "@GOTPCREL(%eip), %ebx";
        gen( MIPSInstruction );
        //gen movl _idV@GOTPCREL(%eip), %ebx
        string address = "(%ebx)";
        return address;
        */
    } else {
        //string address = itoa( getOffset(identifierInformation), temp, 10 );
        sprintf(temp, "%d", getOffset(identifierInformation));
        string address = temp;
        address += "($sp)";
        return address;
    }
}

void MIPSArchitecture::genInstruction(Instruction *instruction)
{
    if(instruction->getLabel()) {
        if(instruction->getLabel()->getType()==INSTRUCTION_ARGUMENT_TYPE_INSTUCTION_LABEL) {
            InstructionLabel *instructionLabel = (InstructionLabel *)instruction->getLabel();
            genLabel( getMachineInstructionLabel(instructionLabel->getLabelNumber()) );
        }
    }

    switch(instruction->getInstructionType()) {
    case INSTRUCTION_TYPE_ARITHMETIC:
        genArithmetic((ArithmeticInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_CALL:
        genCall((CallInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_CONDITIONAL_GOTO:
        genConditionalGoto((ConditionalGotoInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_COPY:
        genCopy((CopyInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_GOTO:
        genGoto((GotoInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_NEGATION:
        genNegation((NegationInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_NOP:
        genNop((NopInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_PARAMETER:
        genParam((ParameterInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_READ:
        genRead((ReadInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_RETURN:
        genReturn((ReturnInstruction*)instruction);
        break;

    case INSTRUCTION_TYPE_WRITE:
        genWrite((WriteInstruction*)instruction);
        break;

    default:
        break;
    }
}

//FAZER
int MIPSArchitecture::getEmptyRegister(list<int> *avoidList, list<int> *avoidSecondList)
{
    int min_cost = INT_MAX, best_reg = NO_REGISTER;
    list<IdentifierInformation *> *identifiers;
    for(int reg = 0; reg<getTotalRegisters(); reg++) {
        //há registrador livre?
        bool isAllowed = true;


        if(avoidList != NULL) {

            if(avoidSecondList != NULL) {

                for(list<int>::iterator it = avoidList->begin(); isAllowed && it!=avoidList->end(); it++) {
                    isAllowed = ( reg != (*it) );
                }

                for(list<int>::iterator it = avoidSecondList->begin(); isAllowed && it!=avoidSecondList->end(); it++) {
                    isAllowed = ( reg != (*it) );
                }

            } else {

                for(list<int>::iterator it = avoidList->begin(); it!=avoidList->end(); it++) {
                    isAllowed = ( reg != (*it) );
                }

            }
        }

        if(isAllowed) {
            if( getRegisterDescriptor(reg)->getVariablesList()->empty() ) {
//                            cout << "epaaaaaaa!";

                return reg;
            }
        }

        identifiers = getRegisterDescriptor(reg)->getVariablesList();

        //há registrador que armazena apenas variáveis não vivas?
        bool useRegister = isAllowed;
        for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {

            useRegister = useRegister && !getVariableDescriptor(*it)->isAlive();

        }
        if(useRegister) {
            return reg;
        }

        //há registrador que armazena apenas variáveis salvas?
        useRegister = isAllowed;
        for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {
            useRegister = useRegister && getVariableDescriptor(*it)->isInMemory();
        }
        if(useRegister)
            return reg;

        //qual registrador leva menor prejuizo de se escolhido?
        useRegister = isAllowed;
        int cost = 0;
        for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {
            if( getVariableDescriptor(*it)->isAlive() && (*it)->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_TEMPORARY ){
                cost = INT_MAX;
            }
            else if(getVariableDescriptor(*it)->isAlive() && !getVariableDescriptor(*it)->isInMemory()){
                if(cost<INT_MAX)
                    cost++;
            }

        }
        if(cost<min_cost) {
            best_reg = reg;
            min_cost = cost;
        }

    }
    //cout << "HERE " << best_reg << endl;
    if(best_reg!=NO_REGISTER) {
        identifiers = getRegisterDescriptor(best_reg)->getVariablesList();
        for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {

            //quando fazer o alive no DV
            /*
            if(getVariableDescriptor(*it)->isAlive() && !getVariableDescriptor(*it)->isInMemory()) {
                genStore(best_reg, (*it));
            }
            */

            if(!getVariableDescriptor(*it)->isInMemory()) {
                genStore(best_reg, (*it));
            }

        }
    }

    return best_reg;
}

//FUNÇÃO get_reg( instruction(op, x, y, z) )
//FAZER AQUI: FAZER DE ACORDO COM OS SLIDES
vector<int> *MIPSArchitecture::getRegisters(Instruction *instruction)
{
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    vector<int> * regs = new vector<int>();

    int destinationRegister = NO_REGISTER;
    int firstSourceRegister = NO_REGISTER;
    int secondSourceRegister = NO_REGISTER;

    switch(instruction->getInstructionType()) {

        // Otimiza acesso para operação comutativa
    case INSTRUCTION_TYPE_ARITHMETIC:
        this->optmiseArithmeticInstruction(instruction);
        break;

    case INSTRUCTION_TYPE_CONDITIONAL_GOTO:
        this->optmiseConditionalInstruction(instruction);
        break;

    default:
        break;
    }

    ArgumentInformation * src1 = 0;
    ArgumentInformation * src2 = 0;
    if(args->size()>1)
        src1 = args->at(1);

    if(args->size()==3)
        src2 = args->at(2);

    bool isFirstValidArgument = false;
    IdentifierInformation * firstSourceInfo = 0;
    VariableDescriptor * firstSourceDescriptor = 0;
    IdentifierInformation * secondSourceInfo = 0;
    VariableDescriptor * secondSourceDescriptor = 0;

    if(src1) {
        isFirstValidArgument = (src1->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER || src1->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY);
        if(isFirstValidArgument) {
            firstSourceInfo = this->getInfoFromArgument(src1->getInstructionArgument());
            firstSourceDescriptor = this->getVariableDescriptor(firstSourceInfo);

        }

        if(src2) {
            if(src2->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER || src2->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY) {
                secondSourceInfo = this->getInfoFromArgument(src2->getInstructionArgument());
                secondSourceDescriptor = this->getVariableDescriptor(secondSourceInfo);
            }
        }

        // aloca registrador Ry para y
        //caso 1: y não está em registrador
        if(isFirstValidArgument) {
            if(firstSourceDescriptor->getRegistersList()->empty()) {
                if(secondSourceDescriptor)
                    firstSourceRegister = getEmptyRegister( secondSourceDescriptor->getRegistersList() );
                else firstSourceRegister = getEmptyRegister( );
                genLoad(firstSourceInfo, firstSourceRegister);
            } else { //caso 2: y está no registrador R1
                firstSourceRegister = firstSourceDescriptor->getRegistersList()->front();
            }
        } else {
            if(secondSourceDescriptor)
                firstSourceRegister = getEmptyRegister( secondSourceDescriptor->getRegistersList() );
            else firstSourceRegister = getEmptyRegister( );

            if(src1->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                genMove( ((ImmediateArgument *) src1->getInstructionArgument())->getImmediateValue(), firstSourceRegister);
            }
        }

        if(secondSourceInfo) {
            //caso 1: z não está em registrador
            if(secondSourceDescriptor->getRegistersList()->empty()) {
                if(src2->getStatus()>=0) { //z é usado novamente
                    if(isFirstValidArgument)
                        secondSourceRegister = getEmptyRegister( firstSourceDescriptor->getRegistersList() );
                    else secondSourceRegister = getEmptyRegister( );
                    genLoad(secondSourceInfo, secondSourceRegister);
                }
                //else secondSourceRegister = NO_REGISTER;
            } else {
                secondSourceRegister = secondSourceDescriptor->getRegistersList()->front();
            }
        }
    }

    if(args->at(0)!=NULL) {
        if(isFirstValidArgument && instruction->getInstructionType()!=INSTRUCTION_TYPE_COPY) {
            if(src1->getStatus()>=0) {
                destinationRegister = getEmptyRegister( firstSourceDescriptor->getRegistersList(), secondSourceDescriptor->getRegistersList() );
            } else if(!firstSourceDescriptor->isInMemory() && src1->getStatus()==ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT) {
                genStore(firstSourceRegister, firstSourceInfo);
                destinationRegister = firstSourceRegister;
            } else {
                destinationRegister = firstSourceRegister;
            }

        } else {
            if(src1) {
                destinationRegister = firstSourceRegister;

            } else {
                destinationRegister = getEmptyRegister( );

            }
        }
        if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY && destinationRegister==NO_REGISTER ){
            if(src1){
                if(src2)
                    destinationRegister = getEmptyRegister( firstSourceDescriptor->getRegistersList(), secondSourceDescriptor->getRegistersList() );
                else destinationRegister = getEmptyRegister( firstSourceDescriptor->getRegistersList() );
            }else destinationRegister = getEmptyRegister( );
        }

    }

    regs->push_back(destinationRegister);
    regs->push_back(firstSourceRegister);
    regs->push_back(secondSourceRegister);

    delete args;
    return regs;
}

void MIPSArchitecture::swapArguments(ArgumentInformation *src1, ArgumentInformation *src2)
{
    InstructionArgument *arg = src2->getInstructionArgument();
    int status = src2->getStatus();
    src2->setInstructionArgument( src1->getInstructionArgument() );
    src2->setStatus( src1->getStatus() );
    src1->setInstructionArgument( arg );
    src1->setStatus( status );
}

void MIPSArchitecture::optmiseArithmeticInstruction(Instruction * instruction)
{

    ArithmeticInstruction * arithmeticInstruction = (ArithmeticInstruction*)instruction;
    ArithmeticOperator op = arithmeticInstruction->getArithmeticOperator();

    if(op == ARITHMETIC_OPERATOR_ADD || op == ARITHMETIC_OPERATOR_MULT) {

        vector<ArgumentInformation *> *args = arithmeticInstruction->getArgumentsInformation();

        ArgumentInformation * src1 = args->at(1);
        ArgumentInformation * src2 = args->at(2);

        if(src1->getInstructionArgument()->getType() == INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            swapArguments(src1, src2);
            //arithmeticInstruction->setFirstArgument(src2->getInstructionArgument());
            //arithmeticInstruction->setSecondArgument(src1->getInstructionArgument());
        } else {

            IdentifierInformation * identifierInfo1 = this->getInfoFromArgument(src1->getInstructionArgument());
            VariableDescriptor * variableDescriptor = this->getVariableDescriptor(identifierInfo1);

            list<int> * registersList = variableDescriptor->getRegistersList();


            // DV[y].reg.empty()
            // and instr.status_op1() != USED_IN_BLOCK
            // and instr.status_op2() != USED_IN_BLOCK)

            // STATUS < 0 => STATUS != USED_IN_BLOCK

            // ArgumentInformation:
            // #define ARGUMENT_INFORMATION_STATUS_NOT_ALIVE     -1
            // #define ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT -2

            if(registersList->empty() && src1->getStatus() < 0 && src2->getStatus() < 0) {


// instr.swap_operands();
                swapArguments(src1, src2);
                //arithmeticInstruction->setFirstArgument(src2->getInstructionArgument());
                //arithmeticInstruction->setSecondArgument(src1->getInstructionArgument());
            }

        }
    }


}

void MIPSArchitecture::optmiseConditionalInstruction(Instruction * instruction)
{
    ConditionalGotoInstruction * conditionalGotoInstruction = (ConditionalGotoInstruction*)instruction;
    RelationalOperator op = conditionalGotoInstruction->getRelationalOperator();


    vector<ArgumentInformation *> *args = conditionalGotoInstruction->getArgumentsInformation();

    ArgumentInformation * src1 = args->at(1);
    ArgumentInformation * src2 = args->at(2);

    if(src1->getInstructionArgument()->getType() == INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
        swapArguments(src1, src2);
        conditionalGotoInstruction->setRelationalOperator(mirrorRelationalOperator(op));
    } else {

        IdentifierInformation * identifierInfo1 = this->getInfoFromArgument(src1->getInstructionArgument());

        VariableDescriptor * variableDescriptor = this->getVariableDescriptor(identifierInfo1);
        list<int> * registersList = variableDescriptor->getRegistersList();

        // DV[y].reg.empty()
        // and instr.status_op1() != USED_IN_BLOCK
        // and instr.status_op2() != USED_IN_BLOCK)

        // STATUS < 0 => STATUS != USED_IN_BLOCK

        // ArgumentInformation:
        // #define ARGUMENT_INFORMATION_STATUS_NOT_ALIVE     -1
        // #define ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT -2

        if(registersList->empty() && src1->getStatus() < 0 && src2->getStatus() < 0) {
// instr.swap_operands();
            swapArguments(src1, src2);
            conditionalGotoInstruction->setRelationalOperator(mirrorRelationalOperator(op));

        }
    }
}

void MIPSArchitecture::genArithmetic(ArithmeticInstruction *instruction)
{
	vector<int> * regs = this->getRegisters(instruction);
	vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();

	IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(args->at(0)->getInstructionArgument());
	IdentifierInformation * src1IdentifierInfo = this->getInfoFromArgument( args->at(1)->getInstructionArgument());
	IdentifierInformation * src2IdentifierInfo = this->getInfoFromArgument( args->at(2)->getInstructionArgument());

	string MIPSInstruction;

	if(instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_ADD || instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_SUB){
		string op;
		string dst;
		string src1;
		string src2;

		switch(instruction->getArithmeticOperator()) {
		 case ARITHMETIC_OPERATOR_ADD:
		     op = "add";
		     break;
		 case ARITHMETIC_OPERATOR_SUB:
		     op = "sub";
		     break;
		 }

		dst = getRegister(regs->at(0));


		  if(regs->at(1) == NO_REGISTER) {
//            cout << args->at(0) << endl;
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
		
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
					 //op += "i";
                //src1 = getMachineImmediate(immediateArgument->getImmediateValue());
					MIPSInstruction = "\tli $t8, ";
					//MIPSInstruction += getRegister(regs->at(0));
					//MIPSInstruction += ", ";
					MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
					gen(MIPSInstruction);
					//src1 = getRegister(regs->at(0));
					src1 = "$t8";
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
					IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
					IdentifierInformation *identifierInformation = identifierArgument->getIdentifierInformation();
					 if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
						  //movl	$_a, 4(%esp)
						  MIPSInstruction = "\tla $t8, ";
						  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
						  gen(MIPSInstruction);
						  MIPSInstruction = "\tlw $t8, 0($t8)";
						  gen(MIPSInstruction);
						  src1 = "$t8";
					 } else {
						  MIPSInstruction = "\tlw $t8, ";
						  MIPSInstruction += getVariableAddress(identifierInformation);
						  gen(MIPSInstruction);
						  src1 = "$t8";
					 }
            }
//            else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY){
//
//            }
        } else {
            src1 = getRegister(regs->at(1));
        }

		if(regs->at(2) == NO_REGISTER) {
            if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
                //MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
                //MIPSInstruction += ", ";
		MIPSInstruction = "\tli $t9, ";
		//MIPSInstruction += getRegister(regs->at(0));
		//MIPSInstruction += ", ";
		MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
		gen(MIPSInstruction);
		//src1 = getRegister(regs->at(0));
		src2 = "$t9";
                //src2 = getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
				IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
					IdentifierInformation *identifierInformation = identifierArgument->getIdentifierInformation();
					 /*if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
						  //movl	$_a, 4(%esp)
						  MIPSInstruction = "\tla ";
						  MIPSInstruction += getRegister(regs->at(0));
						  MIPSInstruction += ", ";
						  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
						  gen(MIPSInstruction);
						  MIPSInstruction = "\tlw ";
						  MIPSInstruction += getRegister(regs->at(0));
						  MIPSInstruction += ", 0(";	
						  MIPSInstruction += getRegister(regs->at(0));
						  MIPSInstruction += ")";
						  gen(MIPSInstruction);
						src1 = getRegister(regs->at(0));
					 } else {
						  MIPSInstruction = "\tlw ";
						  MIPSInstruction += getRegister(regs->at(0));
						  MIPSInstruction += ", ";
						  MIPSInstruction += getVariableAddress(identifierInformation);
						  gen(MIPSInstruction);
						src1 = getRegister(regs->at(0));
					 }*/
					if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
						  //movl	$_a, 4(%esp)
						  MIPSInstruction = "\tla $t9, ";
						  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
						  gen(MIPSInstruction);
						  MIPSInstruction = "\tlw $t9, 0($t9)";
						  gen(MIPSInstruction);
						  src2 = "$t9";
					 } else {
						  MIPSInstruction = "\tlw $t9, ";
						  MIPSInstruction += getVariableAddress(identifierInformation);
						  gen(MIPSInstruction);
						  src2 = "$t9";
					 }
            }
        } else {
            src2 = getRegister(regs->at(2));
        }

			MIPSInstruction = "\t";
			MIPSInstruction += op;
			MIPSInstruction += " ";
			MIPSInstruction += dst;
			MIPSInstruction += ", ";
			MIPSInstruction += src1;
			MIPSInstruction += ", ";
			MIPSInstruction += src2;
        gen(MIPSInstruction);
	}else {
	}
	/*
    if(instruction->getArithmeticOperator()!=ARITHMETIC_OPERATOR_DIV && instruction->getArithmeticOperator()!=ARITHMETIC_OPERATOR_MOD) {
        if(regs->at(0)!=NO_REGISTER && regs->at(1)!=NO_REGISTER && regs->at(0) != regs->at(1)) {
            MIPSInstruction = "\tmovl ";

            MIPSInstruction += getRegister(regs->at(1));
            MIPSInstruction += ", ";
            MIPSInstruction += getRegister(regs->at(0));

            gen(MIPSInstruction);
        }
    }

	
    switch(instruction->getArithmeticOperator()) {
    case ARITHMETIC_OPERATOR_ADD:
        MIPSInstruction = "\tadd ";
        break;
    case ARITHMETIC_OPERATOR_SUB:
        MIPSInstruction = "\tsub ";
        break;
    case ARITHMETIC_OPERATOR_MULT:
        MIPSInstruction = "\timull ";
        break;
    case ARITHMETIC_OPERATOR_DIV:
    case ARITHMETIC_OPERATOR_MOD:
        break;
    }

    if(instruction->getArithmeticOperator()!=ARITHMETIC_OPERATOR_DIV && instruction->getArithmeticOperator()!=ARITHMETIC_OPERATOR_MOD) {

        if(regs->at(2) == NO_REGISTER) {
            if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
                if(immediateArgument->getImmediateValue()==1L && (instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_ADD || instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_SUB) ) {
                    if(instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_ADD) {
                        MIPSInstruction = "\tincl ";
                    } else {
                        MIPSInstruction = "\tdecl ";
                    }
                } else {
                    MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
                    MIPSInstruction += ", ";
                }
            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
                MIPSInstruction += ", ";
            }
        } else {
            MIPSInstruction += getRegister(regs->at(2));
            MIPSInstruction += ", ";
        }

        if(regs->at(0) == NO_REGISTER) {
//            cout << args->at(0) << endl;
            if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
//            else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY){
//
//            }
        } else {
            MIPSInstruction += getRegister(regs->at(0));
        }

        gen(MIPSInstruction);
    } else {
        MIPSInstruction = "\tmovl ";

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            MIPSInstruction += getRegister(regs->at(1));
        }

        MIPSInstruction += ", %edx";
        gen(MIPSInstruction);
        gen("\tsarl $63, %edx");

        MIPSInstruction = "\tmovl ";

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            } else {
//                cout << "What?" << endl;
            }
        } else {
            MIPSInstruction += getRegister(regs->at(1));
        }

        MIPSInstruction += ", %eax";
        gen(MIPSInstruction);

        MIPSInstruction = "\tidivl ";

        if(regs->at(2) == NO_REGISTER) {
            if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
                int reg = getEmptyRegister();
                MIPSInstruction = "\tmovl ";
                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
                MIPSInstruction += ", ";
                MIPSInstruction += getRegister(reg);
                gen(MIPSInstruction);

                list<IdentifierInformation *> *identifiers = getRegisterDescriptor(reg)->getVariablesList();
                for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {
                    getVariableDescriptor(*it)->removeRegister(reg);
                }
                getRegisterDescriptor(reg)->removeAllVariables();

                MIPSInstruction = "\tidivl ";
                MIPSInstruction += getRegister(reg);

            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            MIPSInstruction += getRegister(regs->at(2));
        }

        gen(MIPSInstruction);

        MIPSInstruction = "\tmovl ";

        if(instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_DIV) {
            MIPSInstruction += "%eax, ";
        } else {
            MIPSInstruction += "%edx, ";
        }

        if(regs->at(0) == NO_REGISTER) {
            if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            MIPSInstruction += getRegister(regs->at(0));
        }

        gen(MIPSInstruction);

    }
*/
    removeVariablesFromRegisters(regs->at(0));

    //cout << "HERE ? (1)" << endl;
    if(regs->at(0) == regs->at(1)) {
        // DV[y].reg.remove(Ry);

        /*
        cout << "HERE inside?" << endl;
        if(!src1IdentifierInfo){
            cout << "null ????" << endl;
        }else if(src1IdentifierInfo->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_TEMPORARY){
            cout << "temporary" << endl;
        }else if(src1IdentifierInfo->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE){
            cout << "variable" << endl;
        }else if(src1IdentifierInfo->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER){
            cout << "parameter" << endl;
        }else {
            cout << "what ????" << endl;
        }
        */
        if(src1IdentifierInfo) {
            VariableDescriptor * srcDV  = this->getVariableDescriptor(src1IdentifierInfo);
            srcDV->removeRegister(regs->at(0));
        }
    }
    //cout << "HERE ? (2)" << endl;
    VariableDescriptor * dstDV  = this->getVariableDescriptor(dstIdentifierInfo);
    RegisterDescriptor * dstDR  = this->getRegisterDescriptor(regs->at(0));

    //cout << "HERE ? (3)" << endl;
    //DV[x].reg = new_list(Rx); DV[x].mem = false;
    dstDV->removeAllRegisters();
    dstDV->addRegister(regs->at(0));
    dstDV->setInMemory(false);

    //cout << "HERE ? (4)" << endl;
//DR[Rx] = new_list(x);


    dstDR->removeAllVariables();
    dstDR->addVariable(dstIdentifierInfo);
    //cout << "HERE =)" << endl;
    /*
    if(regs->at(1)!=regs->at(0)) {
    }
    */
}

void MIPSArchitecture::genReturn(ReturnInstruction *intruction)
{
    vector<int> * regs;
    vector<ArgumentInformation *> *args = intruction->getArgumentsInformation();
    string MIPSInstruction;

    if(args->at(1)!=NULL) {
        regs = getRegisters(intruction);
        MIPSInstruction = "";
        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
		MIPSInstruction = "\tli $v0, ";
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
		MIPSInstruction = "\tlw $v0, ";
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            MIPSInstruction = "\tmove $v0, ";
            MIPSInstruction += getRegister(regs->at(1));
        }
        //MIPSInstruction += ", %eax";
        gen(MIPSInstruction);
    }
    //removeGlobalVariablesFromRegisters();
    //removeVariablesFromRegisters();
    genEpilogue(functionInfo);
    //gen("\tleave");
    //gen("\tret");
}

void MIPSArchitecture::genGoto(GotoInstruction *instruction)
{
    string MIPSInstruction = "\tj ";
    InstructionLabel *label = (InstructionLabel *)instruction->getLabelArgument();
    MIPSInstruction += getMachineInstructionLabel(label->getLabelNumber());
    gen(MIPSInstruction);
}

void MIPSArchitecture::genConditionalGoto(ConditionalGotoInstruction *instruction)
{
	vector<int> * regs = this->getRegisters(instruction);
	vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
	string MIPSInstruction;
	
	//switch( mirrorRelationalOperator(instruction->getRelationalOperator()) ) {
    switch( instruction->getRelationalOperator() ) {
    case RELATIONAL_OPERATOR_EQUAL:

        MIPSInstruction = "\tbeq ";
        break;
    case RELATIONAL_OPERATOR_DIFFERENT:
        MIPSInstruction = "\tbne ";

        break;
    case RELATIONAL_OPERATOR_GREATER:
        MIPSInstruction = "\tbgt ";
        break;

    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        MIPSInstruction = "\tbge ";
        break;
    case RELATIONAL_OPERATOR_LESS:

        MIPSInstruction = "\tblt ";
        break;
    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:

        MIPSInstruction = "\tble ";
        break;
    }

    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
				IdentifierInformation *identifierInformation = identifierArgument->getIdentifierInformation();
					 if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
						  //movl	$_a, 4(%esp)
						  string MIPSInstruction = "\tla $t8, ";
						  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
						  gen(MIPSInstruction);
						  MIPSInstruction = "\tlw $t8, 0($t8)";
						  gen(MIPSInstruction);

					 } else {
						  string MIPSInstruction = "\tlw $t8, ";
						  MIPSInstruction += getVariableAddress(identifierInformation);
						  gen(MIPSInstruction);
					 }
				MIPSInstruction += "$t8";
            //MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());

        }
    } else {

        MIPSInstruction += getRegister(regs->at(1));
    }

    MIPSInstruction += ", ";

 	if(regs->at(2) == NO_REGISTER) {
        if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
            MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
					IdentifierInformation *identifierInformation = identifierArgument->getIdentifierInformation();
					 if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
						  //movl	$_a, 4(%esp)
						  string MIPSInstruction = "\tla $t9, ";
						  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
						  gen(MIPSInstruction);
						  MIPSInstruction = "\tlw $t9, 0($t9)";
						  gen(MIPSInstruction);

					 } else {
						  string MIPSInstruction = "\tlw $t9, ";
						  MIPSInstruction += getVariableAddress(identifierInformation);
						  gen(MIPSInstruction);

					 }
				MIPSInstruction += "$t9";
            //MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        MIPSInstruction += getRegister(regs->at(2));
    }

    MIPSInstruction += ", ";

    InstructionLabel *label = (InstructionLabel *)instruction->getLabelArgument();

    MIPSInstruction += getMachineInstructionLabel(label->getLabelNumber());

    gen(MIPSInstruction);
}

void MIPSArchitecture::genCopy(CopyInstruction *copyInstruction)
{
    //string comment;
    vector<int> * regs = this->getRegisters(copyInstruction);
    vector<ArgumentInformation *> *args = copyInstruction->getArgumentsInformation();

    int dstReg = regs->at(0);

    ArgumentInformation * dst = args->at(0);

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());

    VariableDescriptor * dstDV = this->getVariableDescriptor(dstIdentifierInfo);
    RegisterDescriptor * dstDR  = this->getRegisterDescriptor(dstReg);

    // atualização das informações (Rx = Ry)

//DV[x].reg = new_list(Rx); DV[x].mem = false;
    //comment = "# ";
    //comment += dstIdentifierInfo->getIdentifier();
    //comment += " -> ";
    //comment += getRegister(dstReg);
    //gen(comment);
    dstDV->removeAllRegisters();
    dstDV->addRegister(dstReg);
    dstDV->setInMemory(false);

//DR[Rx].add(x);
    dstDR->addVariable(dstIdentifierInfo);


// não é necessário gerar código



}

void MIPSArchitecture::genNop(NopInstruction *instruction)
{
    gen("\tnop");
}

void MIPSArchitecture::genParam(ParameterInstruction * paramInstruction)
{
    
    //gen("\tpushl %ebp");
    //gen("\tmovl %esp, %ebp");

    vector<int> * regs  = getRegisters(paramInstruction);
    vector<ArgumentInformation *> *args = paramInstruction->getArgumentsInformation();
    string MIPSInstruction;


    // src2 register
    //MIPSInstruction = "\tpushl ";
    MIPSInstruction = "\taddi $sp, $sp, -";
    MIPSInstruction += getMachineImmediate(WORD_SIZE);
    gen(MIPSInstruction);
    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            MIPSInstruction = "\tli $t8, ";
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
            gen(MIPSInstruction);
            MIPSInstruction = "\tsw $t8, 0($sp)";
            gen(MIPSInstruction);
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
            MIPSInstruction = "\tlw $t8, ";
            MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            gen(MIPSInstruction);
            MIPSInstruction = "\tsw $t8, 0($sp)";
            gen(MIPSInstruction);
        }
    } else {
        MIPSInstruction = "\tsw ";
        MIPSInstruction += getRegister(regs->at(1));
        MIPSInstruction += ", 0($sp)";
        gen(MIPSInstruction);
    }
    //gen(MIPSInstruction);
}


void MIPSArchitecture::genCall(CallInstruction * callInstruction)
{
    vector<int> * regs;
    vector<ArgumentInformation *> *args;
    IdentifierInformation * dstIdentifierInfo;

    saveVariables();
    removeVariablesFromRegisters();

    if(callInstruction->getDestinationArgument()) {
        regs = this->getRegisters(callInstruction);
        args = callInstruction->getArgumentsInformation();
        dstIdentifierInfo = this->getInfoFromArgument(args->at(0)->getInstructionArgument());
    }
    //gen("\tpushl $0");
    //gen("pushl %eip");

    //saveGlobalVariables();

    //pushRegisters();

    string MIPSInstruction = "\tjal ";
    IdentifierInformation * functionInfo = ((IdentifierArgument*)callInstruction->getFirstArgument())->getIdentifierInformation();

    MIPSInstruction += getFunctionLabel(functionInfo);
    gen(MIPSInstruction);
    //popRegisters();

    if(callInstruction->getDestinationArgument()) {
        MIPSInstruction = "";//"\tmove %eax, ";
        if(regs->at(0) == NO_REGISTER) {

          // NAO DEVERIA SER CHAMADO!!! =0
                        cout << "ERROR (genCall): " << args->at(0)->getInstructionArgument()->getType() << endl;

//            if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
//                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
//                MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
//            } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
//                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
//                MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
//            }
//            else
//            {
//
//
//            }
        } else {
            MIPSInstruction = "\tmove ";
            MIPSInstruction += getRegister(regs->at(0));
            MIPSInstruction += ", $v0";
        }
        gen(MIPSInstruction);
        cout << MIPSInstruction << endl;

        VariableDescriptor * dstDV  = this->getVariableDescriptor(dstIdentifierInfo);
        RegisterDescriptor * dstDR  = this->getRegisterDescriptor(regs->at(0));

        //DV[x].reg = new_list(Rx); DV[x].mem = false;
        dstDV->removeAllRegisters();
        dstDV->addRegister(regs->at(0));
        dstDV->setInMemory(false);

        //DR[Rx] = new_list(x);
        dstDR->removeAllVariables();
        dstDR->addVariable(dstIdentifierInfo);
    }
}

void MIPSArchitecture::genNegation(NegationInstruction *negationInstruction)
{
    vector<int> * regs = this->getRegisters(negationInstruction);
    vector<ArgumentInformation *> *args = negationInstruction->getArgumentsInformation();

    int dstReg = regs->at(0);
    int srcReg = regs->at(1);

    ArgumentInformation * dst = args->at(0);
    ArgumentInformation * src = args->at(1);

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());
    IdentifierInformation * srcIdentifierInfo = this->getInfoFromArgument(src->getInstructionArgument());

    string MIPSInstruction ;

// geração do código


//if (Rx != Ry)
//then gen_MIPS("movl " • Ry • "," • Rx);

    if(dstReg!=NO_REGISTER && srcReg!=NO_REGISTER && dstReg != srcReg) {
        MIPSInstruction = "\tmovl ";

        MIPSInstruction += getRegister(srcReg);
        MIPSInstruction += ", ";
        MIPSInstruction += getRegister(dstReg);

        gen(MIPSInstruction);
    }

    MIPSInstruction  = "\tnegl ";

    if(regs->at(0) == NO_REGISTER) {
        if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
            MIPSInstruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
            MIPSInstruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        MIPSInstruction += getRegister(regs->at(0));
    }

    gen(MIPSInstruction);

// atualização das informações
    if(dstReg == srcReg) {

// DV[y].reg.remove(Ry);

        VariableDescriptor * srcDV  = this->getVariableDescriptor(srcIdentifierInfo);
        srcDV->removeRegister(srcReg);
    }

    VariableDescriptor * dstDV  = this->getVariableDescriptor(dstIdentifierInfo);
    RegisterDescriptor * dstDR  = this->getRegisterDescriptor(dstReg);

    //DV[x].reg = new_list(Rx); DV[x].mem = false;
    dstDV->removeAllRegisters();
    dstDV->addRegister(dstReg);
    dstDV->setInMemory(false);

//DR[Rx] = new_list(x);
    dstDR->removeAllVariables();
    dstDR->addVariable(dstIdentifierInfo);

}

void MIPSArchitecture::pushRegisters()
{
    string MIPSInstruction;
    for(int reg = 0; reg<getTotalRegisters(); reg++) {
        if(!getRegisterDescriptor(reg)->getVariablesList()->empty()) {
            //MIPSInstruction = "\tpushl ";
            //MIPSInstruction += getRegister(reg);

	    //addi $sp, $sp, -4  # Decrement stack pointer by 4
            //sw   $r3, 0($sp)
            MIPSInstruction = "\taddi $sp, $sp, -";
            MIPSInstruction += getMachineImmediate(WORD_SIZE);
            gen(MIPSInstruction);
            MIPSInstruction = "\tsw ";
            MIPSInstruction += getRegister(reg);
            MIPSInstruction += ", 0($sp)";
            gen(MIPSInstruction);

        }
    }
}

void MIPSArchitecture::popRegisters()
{
    string MIPSInstruction;
    for(int reg = getTotalRegisters()-1; reg>=0; reg--) {
        if(!getRegisterDescriptor(reg)->getVariablesList()->empty()) {
            MIPSInstruction = "\tpopl ";
            MIPSInstruction += getRegister(reg);
            gen(MIPSInstruction);
        }
    }
}

void MIPSArchitecture::genWrite(WriteInstruction *instruction)
{
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    ArgumentInformation *argumentInformation = args->at(1);

    InstructionArgument *instructionArgument = argumentInformation->getInstructionArgument();

   // pushRegisters(); //printf changes all registers but esi

    if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER || instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY) {
        IdentifierArgument *identifierArgument = (IdentifierArgument *)instructionArgument;

        int reg = NO_REGISTER;
        if( getVariableDescriptor(identifierArgument->getIdentifierInformation())->getRegistersList()->size()==0 ) {
            if(argumentInformation->getStatus()>=0) {
                //reg = getNewRegister();
            } else {
                reg = NO_REGISTER;
            }
        } else {
            reg = *(getVariableDescriptor(identifierArgument->getIdentifierInformation())->getRegistersList()->begin());
        }
        if(reg==NO_REGISTER) {
            genWrite(identifierArgument->getIdentifierInformation());
        } else {
            genWrite(reg);
        }
    } else if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_STRING) {
        StringArgument *stringArgument = (StringArgument *)instructionArgument;
        genWrite(stringArgument->getStringValue());
    } else if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
        ImmediateArgument *immediateArgument = (ImmediateArgument *)instructionArgument;
        genWrite(immediateArgument);

    }

    //popRegisters(); //printf changes all registers but esi

    delete args;
}

void MIPSArchitecture::genRead(ReadInstruction *instruction)
{
    InstructionArgument *instructionArgument = instruction->getDestinationArgument();
    if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
        IdentifierArgument *identifierArgument = (IdentifierArgument *)instructionArgument;

        //pushRegisters(); //printf change all registers but esi
        genRead(identifierArgument->getIdentifierInformation());
        //popRegisters(); //printf change all registers but esi
    }

}

void MIPSArchitecture::genLoad(IdentifierInformation *identifierInformation, int registerNumber)
{
	string MIPSInstruction = "\tla ";
	MIPSInstruction += getRegister(registerNumber);
	MIPSInstruction += ", ";
	MIPSInstruction += getVariableAddress( identifierInformation );
	gen(MIPSInstruction);

	MIPSInstruction = "\tlw ";
	MIPSInstruction += getRegister(registerNumber);
	MIPSInstruction += ", 0("+getRegister(registerNumber)+")";
	//MIPSInstruction += getVariableAddress( identifierInformation );
	gen(MIPSInstruction);

    list<IdentifierInformation *> *identifiers = getRegisterDescriptor(registerNumber)->getVariablesList();
    for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {
        getVariableDescriptor(*it)->removeRegister(registerNumber);
    }


    list<int> *registers = getVariableDescriptor(identifierInformation)->getRegistersList();
    for(list<int>::iterator it = registers->begin(); it!=registers->end(); it++) {
        getRegisterDescriptor(*it)->removeVariable(identifierInformation);
    }

    getVariableDescriptor(identifierInformation)->removeAllRegisters();
    getVariableDescriptor(identifierInformation)->addRegister(registerNumber);

    getRegisterDescriptor(registerNumber)->removeAllVariables();
    getRegisterDescriptor(registerNumber)->addVariable(identifierInformation);


    //  foreach v in DR[reg] do
    //	    DV[v].reg.remove(reg);
    //  foreach r in DV[var].reg do
    //	    DR[r].remove(var);
    //  DV[var].reg = new_list(reg);
    //  DR[reg] = new_list(var);
    //
}

void MIPSArchitecture::genStore(int registerNumber, IdentifierInformation *identifierInformation)
{
    string MIPSInstruction = "\tsw ";
    MIPSInstruction += getRegister(registerNumber);
    MIPSInstruction += ", ";

    string address = getVariableAddress( identifierInformation );

	 if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
		  string MIPSInstruction = "\tla $t9, ";
		  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
		  gen(MIPSInstruction);
		  address = "0($t9)";
	 }
    MIPSInstruction += address;

    gen( MIPSInstruction );
    //cout << MIPSInstruction << endl;

    getVariableDescriptor(identifierInformation)->setInMemory(true);
}

void MIPSArchitecture::initDescriptorTables()
{
    list<IdentifierInformation*>  * identifierInfoList = this->symbolTable_->getIdentifierInfoList();

    for(list<IdentifierInformation*>::iterator it = identifierInfoList->begin(); it != identifierInfoList->end(); it++) {
        IdentifierInformation * identifierInfo = (*it);

        if(identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_VARIABLE || identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER || identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_TEMPORARY) {
            VariableDescriptor * variableDescriptor = new VariableDescriptor();

            variableDescriptor->setInMemory(false); // Explicitando
            variableDescriptor->setAlive(false);

            if(this->variableDescriptorTable_.contains((int)identifierInfo)) {
                delete this->variableDescriptorTable_.get((int)identifierInfo);
            }

            this->variableDescriptorTable_.set((int)identifierInfo, variableDescriptor);
        }
    }

    for(int reg = 0; reg<getTotalRegisters(); reg++) {
        RegisterDescriptor * registerDescriptor = new RegisterDescriptor();

        if(this->variableDescriptorTable_.contains(reg)) {
            delete this->variableDescriptorTable_.get(reg);
        }

        this->registerDescriptorTable_.set(reg, registerDescriptor);
    }
}

void MIPSArchitecture::updateVariablesStatus(Instruction * instruction)
{
    vector<ArgumentInformation *> * args = instruction->getArgumentsInformation();

    ArgumentInformation * dst = args->at(0);

    if( dst != NULL ) {
        IdentifierInformation * identifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());

        if(identifierInfo != NULL) {
            bool alive = (dst->getStatus() != ARGUMENT_INFORMATION_STATUS_NOT_ALIVE);
            this->variableDescriptorTable_.get((int)identifierInfo)->setAlive(alive);
        }
    }

    for(size_t k = 1; k < args->size(); k++ ) {
        ArgumentInformation * src = args->at(k);

        if(src != NULL) {
            IdentifierInformation * identifierInfo = this->getInfoFromArgument(src->getInstructionArgument());

            if(identifierInfo != NULL) {
                bool alive = (src->getStatus() != ARGUMENT_INFORMATION_STATUS_NOT_ALIVE);
                this->variableDescriptorTable_.get((int)identifierInfo)->setAlive(alive);
            }
        }
    }

}

void MIPSArchitecture::genWrite(const char *str)
{
    char temp[64];
    string MIPSInstruction = "\tli $v0, 4"; // system call code for printing string = 4
    gen(MIPSInstruction);

    MIPSInstruction = "\tla $a0, ";
    MIPSInstruction += getStringLabel(str); // load address of string to be printed into $a0
    gen(MIPSInstruction);

    gen("\tsyscall");
}

void MIPSArchitecture::genWrite(IdentifierInformation *identifierInformation)
{
	char temp[64];
	string MIPSInstruction = "\tli $v0, 1"; // system call code for printing string = 4
	gen(MIPSInstruction);
 
   VariableDescriptor *varDescriptor = getVariableDescriptor(identifierInformation);
   if(varDescriptor->getRegistersList()->empty()){
			if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
				  //movl	$_a, 4(%esp)
				  MIPSInstruction = "\tla $a0, ";
				  MIPSInstruction += getGlobalVariableLabel(identifierInformation);
				  gen(MIPSInstruction);			
				  MIPSInstruction = "\tlw $a0, 0($a0)";
				  MIPSInstruction += ", ";
				  gen(MIPSInstruction);
			 } else {
				  MIPSInstruction = "\tlw $a0, ";
				  MIPSInstruction += getVariableAddress(identifierInformation);
				  gen(MIPSInstruction);
			 }
    } else {
		MIPSInstruction = "\tmove $a0, ";
		MIPSInstruction += getRegister(varDescriptor->getRegistersList()->front());
		gen(MIPSInstruction);
	 }
    gen("\tsyscall");
}

void MIPSArchitecture::genWrite(int registerNumber)
{

	 string MIPSInstruction = "\tli $v0, 1"; // system call code for printing integer = 1
    gen(MIPSInstruction);

    MIPSInstruction = "\tmove $a0, "; // move from register the integer to be printed into $a0
    MIPSInstruction += getRegister(registerNumber);
    gen(MIPSInstruction);

    gen("\tsyscall");
}

void MIPSArchitecture::genWrite(ImmediateArgument * immediateArgument)
{

    long value =   immediateArgument->getImmediateValue();

    string MIPSInstruction = "\tli $v0, 1"; // system call code for printing integer = 1
    gen(MIPSInstruction);

    MIPSInstruction = "\taddi $a0, $zero, "; // move the integer to be printed into $a0
    MIPSInstruction += getMachineImmediate(value);
    gen(MIPSInstruction);

    gen("\tsyscall");
}

void MIPSArchitecture::genRead(IdentifierInformation *identifierInformation)
{
    char temp[64];
	//li $v0, 5 # system call code for reading integer = 5
	//syscall # call operating system to perform operation;
	//move $a0, $v0

    string MIPSInstruction = "\tli $v0, 5"; //system call code for reading integer = 5, result in $v0
    gen(MIPSInstruction);
    gen("\tsyscall");

    if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
        //movl	$_a, 4(%esp)
        MIPSInstruction = "\tla $a0, ";
        MIPSInstruction += getGlobalVariableLabel(identifierInformation);
        gen(MIPSInstruction);			
		  MIPSInstruction = "\tsw $v0, 0($a0)";
        MIPSInstruction += ", ";
        gen(MIPSInstruction);
    } else {
        MIPSInstruction = "\tsw $v0, ";
        MIPSInstruction += getVariableAddress(identifierInformation);
        gen(MIPSInstruction);
    }

    //foreach (r in DV[z].reg)
    //DR[r].remove(z);
    list<int> *registers = getVariableDescriptor(identifierInformation)->getRegistersList();
    for(list<int>::iterator it = registers->begin(); it!=registers->end(); it++) {
        getRegisterDescriptor(*it)->removeVariable(identifierInformation);
    }

    //DV[z].reg = new_list();
    getVariableDescriptor(identifierInformation)->removeAllRegisters();

    //DV[z].mem = true;
    getVariableDescriptor(identifierInformation)->setInMemory(true);
}

void MIPSArchitecture::genMove(long immediate, int reg)
{
    string MIPSInstruction = "\tli ";
    MIPSInstruction += getRegister(reg);
    MIPSInstruction += ", ";
    MIPSInstruction += getMachineImmediate(immediate);
    gen(MIPSInstruction);
}

string MIPSArchitecture::getMachineImmediate(long immediate)
{
    char temp[64];
    //string MIPSImmediate = "$";
    //MIPSImmediate += itoa(immediate, temp, 10);
    sprintf(temp, "%d", (int)immediate);
    string MIPSImmediate = temp;
    return MIPSImmediate;

}
string MIPSArchitecture::getMachineString(string str)
{
    stringstream strMachineString;

    for(size_t i = 0 ; i < str.length()-1; i++) {

        if( isprint(str[i]) ) {
            strMachineString << str[i];
        } else {

            strMachineString << '\\' << oct << (int)str[i];
        }
    }

    //strMachineString << "\\0\"";
	strMachineString << "\"";
    return strMachineString.str();
}


string MIPSArchitecture::getMachineString(const char *c_str)
{
    string machineString = c_str;
    return getMachineString(machineString);
}

string MIPSArchitecture::getStringLabel(string str)
{
    return getStringLabel(str.c_str());
}

string MIPSArchitecture::getStringLabel(const char *c_str)
{
    char temp[128];
    string str = getMachineString(c_str);
    string strLabel;

    list <string> *stringList = symbolTable_->getStringList();


    //cout << "STRING VALUE: " << str << endl;

    if(str=="\"\\n\"") {
        strLabel = "new_line_str";
    } else {
        int strCount = 1;
        for(list<string>::iterator it = stringList->begin(); it!=stringList->end(); it++, strCount++) {
            if(str==getMachineString(*it)) {
                strLabel = "str_";
                //strLabel += itoa( strCount, temp, 10 );
                sprintf(temp, "%d", strCount);
                strLabel += temp;
            }
        }
    }
    return strLabel;
}

string MIPSArchitecture::getRegister(int index)
{
    return registers_.at(index);
}

int MIPSArchitecture::getTotalRegisters()
{
    return registers_.size();
}


string MIPSArchitecture::getFunctionLabel(IdentifierInformation * functionInfo)
{
    string functionLabel;
    if(!strcmp(functionInfo->getIdentifier(),"main")){
	functionLabel = "";
    }else{
        functionLabel = "__";
    }
    functionLabel += functionInfo->getIdentifier();
    return functionLabel;
}

string MIPSArchitecture::getFunctionLabel(string functionName)
{
    string functionLabel;
    if(!strcmp(functionName.c_str(),"main")){
	functionLabel = "";
    }else{
        functionLabel = "__";
    }
    functionLabel += functionName;
    return functionLabel;
}

string MIPSArchitecture::getFunctionLabel(const char *functionName)
{
    string fName = functionName;
    return getFunctionLabel(fName);
}

string MIPSArchitecture::getMachineInstructionLabel(int labelNumber)
{
    char temp[64];
    string label = "L";

    //label += itoa(labelNumber, temp, 10);
    sprintf(temp, "%d", labelNumber);
    label += temp;

    return label;
}

void MIPSArchitecture::genLabel(string label)
{
    string MIPSInstruction = label;
    MIPSInstruction += ":";
    gen(MIPSInstruction);
}

void MIPSArchitecture::genLabel(const char *label)
{
    string MIPSInstruction = label;
    MIPSInstruction += ":";
    gen(MIPSInstruction);
}

void MIPSArchitecture::genPrologue(FunctionInformation * functionInfo)
{
    stringstream sstream;

    //gen("\tpushl %ebp");
    //gen("\tmovl %esp, %ebp");

    if(functionInfo) {
        size_t variablesCount = functionInfo->getVariableList().size() * WORD_SIZE;

        if(variablesCount > 0) {
            sstream << "\taddi $sp, $sp, -" << (int)variablesCount;
            gen(sstream.str());

        }
    }
}


void MIPSArchitecture::genEpilogue(FunctionInformation * functionInfo)
{
    stringstream sstream;
    
    if(functionInfo){
        size_t variablesCount = functionInfo->getVariableList().size() * WORD_SIZE;

        if(variablesCount > 0) {
            sstream << "\taddi $sp, $sp, " << (int)variablesCount;
            gen(sstream.str());
        }
    }
    
    //gen("\tleave");
    if(functionInfo==NULL){// || !strcmp(functionInfo->getIdentifier(), intermediateCode_->getMainFunctionName())){
       gen("\tli $v0, 10"); // system call for exit
       gen("\tsyscall");
    }else 
       gen("\tjr $ra");

}

void MIPSArchitecture::removeGlobalVariablesFromRegisters()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE && info->getScopeLevel()==GLOBAL_SCOPE) {
            variableDescriptor = this->getVariableDescriptor(info);
            variableDescriptor->removeAllRegisters();
            for(int reg = 0; reg<getTotalRegisters(); reg++) {
                getRegisterDescriptor(reg)->removeVariable(info);
            }
        }
    }
}

void MIPSArchitecture::saveGlobalVariables()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE && info->getScopeLevel()==GLOBAL_SCOPE) {
            variableDescriptor = this->getVariableDescriptor(info);

            if(!variableDescriptor->isInMemory() && !variableDescriptor->getRegistersList()->empty()) {
                genStore(variableDescriptor->getRegistersList()->front(), info);
            }
        }
    }
}

void MIPSArchitecture::saveAliveVariables()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
            variableDescriptor = this->getVariableDescriptor(info);

            if(!variableDescriptor->isInMemory() && variableDescriptor->isAlive() && !variableDescriptor->getRegistersList()->empty()) {
                genStore(variableDescriptor->getRegistersList()->front(), info);
            }
        }
    }
}

void MIPSArchitecture::saveVariables()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
            variableDescriptor = this->getVariableDescriptor(info);

            if(!variableDescriptor->isInMemory() && !variableDescriptor->getRegistersList()->empty()) {
                genStore(variableDescriptor->getRegistersList()->front(), info);
            }
        }
    }
}

void MIPSArchitecture::removeVariablesFromRegisters()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
            variableDescriptor = this->getVariableDescriptor(info);
            if(variableDescriptor->getRegistersList()->size()) {
                variableDescriptor->removeAllRegisters();
                for(int reg = 0; reg<getTotalRegisters(); reg++) {
                    getRegisterDescriptor(reg)->removeVariable(info);
                }
            }
        }
    }
}

void MIPSArchitecture::removeVariablesFromRegisters(int registerNumber)
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
            variableDescriptor = this->getVariableDescriptor(info);
            variableDescriptor->removeRegister(registerNumber);
            getRegisterDescriptor(registerNumber)->removeVariable(info);
        }
        /*
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER
           || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_TEMPORARY) {
            variableDescriptor = this->getVariableDescriptor(info);
            variableDescriptor->removeRegister(registerNumber);
            getRegisterDescriptor(registerNumber)->removeVariable(info);
        }
        */
    }
}

void MIPSArchitecture::removeLocalVariablesFromRegisters()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    IdentifierInformation *info;
    VariableDescriptor * variableDescriptor;
    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        //VariableInformation * varInfo = (VariableInformation *)info;
        if(info->getScopeLevel()>GLOBAL_SCOPE) {
            if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE || info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
                variableDescriptor = this->getVariableDescriptor(info);
                if(variableDescriptor->getRegistersList()->size()) {
                    variableDescriptor->removeAllRegisters();
                    for(int reg = 0; reg<getTotalRegisters(); reg++) {
                        getRegisterDescriptor(reg)->removeVariable(info);
                    }
                }
            }
        }

    }
}
