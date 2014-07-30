/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "x86_architecture.h"


#include <sstream>
using namespace std;

//const int X86Architecture::WORD_SIZE = 4;

X86Architecture::X86Architecture(SymbolTable * symbolTable, IntermediateCode * intermediateCode)
    : MachineCode(symbolTable, intermediateCode)
{
    registers_.push_back("%ecx");
    registers_.push_back("%ebx");
    registers_.push_back("%esi");
    registers_.push_back("%edi");
}

void X86Architecture::generateCode()
{

    vector<BasicBlock *> *basicBlocks = this->intermediateCode_->getBasicBlocks();
    genStartingCode();

    for(size_t i = 0; i < basicBlocks->size(); i++) {
        //gen("# basic block");
        this->initDescriptorTables();

        BasicBlock * basicBlock = basicBlocks->at(i);
        basicBlock->optimise();

        FunctionInformation * functionInfo = NULL;

        if(basicBlock->isStartingFunction()) {
            string x86Instruction = "\t.globl ";
            x86Instruction += getFunctionLabel(basicBlock->getFunctionName());
            gen(x86Instruction);
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

    delete basicBlocks;

}


void X86Architecture::genStartingCode()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    list <string> *stringList = symbolTable_->getStringList();
    IdentifierInformation *info;
    char temp[128];
    string x86Instruction;

    x86Instruction = "\t.file \"";
    x86Instruction += baseFileName_;
    x86Instruction += "\"";
    gen(x86Instruction);

    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation * varInfo = (VariableInformation *)info;
            if(varInfo->getScopeLevel()==GLOBAL_SCOPE) { //MODULE SCOPE
                x86Instruction = "\t.comm _";
                x86Instruction += varInfo->getIdentifier();
                //x86Instruction += itoa( varInfo->getOffset(), temp, 10 );
                x86Instruction += ", 16\t#4";
                gen(x86Instruction);
            }
        }
    }
    gen("\t.section .data");
    gen("mask_io_str:");
    gen("\t.ascii \"%d\\0\"");
    gen("new_line_str:");
    gen("\t.ascii \"\\12\\0\"");

    int strCount = 1;
    for(list<string>::iterator it = stringList->begin(); it!=stringList->end(); it++, strCount++) {
        x86Instruction = "str_";
        x86Instruction += itoa( strCount, temp, 10 );
        x86Instruction += ":";
        gen(x86Instruction);

        x86Instruction = "\t.ascii ";
        x86Instruction += getMachineString(*it);
        gen(x86Instruction);
    }

    gen("\t.section .text");

    //x86Instruction = "\t.globl ";
    //x86Instruction += getFunctionLabel(intermediateCode_->getMainFunctionName());
    //gen("\t.globl _main");
    //gen(x86Instruction);
}

/*
void X86Architecture::initDescriptorTables()
{
    for(unsigned int reg = 0; reg<registers_.size(); reg++){
        RegisterDescriptor * registerDescriptor = new RegisterDescriptor();
        this->registerDescriptorTable_.set(reg, registerDescriptor);
    }
}
*/

int X86Architecture::getOffset(IdentifierInformation *identifierInformation)
{
    int offset = 0;
    if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
        FormalParameterInformation *formalParamameter = (FormalParameterInformation *)identifierInformation;
        offset = 4 + formalParamameter->getOffset()*(WORD_SIZE);
    } else if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
        VariableInformation *variable = (VariableInformation *)identifierInformation;
        offset = -( variable->getOffset()*(WORD_SIZE) );
    }
    return offset;
}

string X86Architecture::getVariableAddress(IdentifierInformation *identifierInformation)
{
    char temp[32];
    if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
        //TODO
        string address;
        if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation *variable = (VariableInformation *)identifierInformation;
            address = "_";
            address += variable->getIdentifier();
        }
        return address;

        /*
        x86Instruction = "\tmovl _";
        if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation *variable = (VariableInformation *)identifierInformation;
            //x86Instruction += variable->getOffset();
            x86Instruction += variable->getIdentifier();
        }
        x86Instruction += "@GOTPCREL(%eip), %ebx";
        gen( x86Instruction );
        //gen movl _idV@GOTPCREL(%eip), %ebx
        string address = "(%ebx)";
        return address;
        */
    } else {
        string address = itoa( getOffset(identifierInformation), temp, 10 );
        address += "(%ebp)";
        return address;
    }
}

void X86Architecture::genInstruction(Instruction *instruction)
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
int X86Architecture::getEmptyRegister(list<int> *avoidList, list<int> *avoidSecondList)
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
vector<int> *X86Architecture::getRegisters(Instruction *instruction)
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

void X86Architecture::swapArguments(ArgumentInformation *src1, ArgumentInformation *src2)
{
    InstructionArgument *arg = src2->getInstructionArgument();
    int status = src2->getStatus();
    src2->setInstructionArgument( src1->getInstructionArgument() );
    src2->setStatus( src1->getStatus() );
    src1->setInstructionArgument( arg );
    src1->setStatus( status );
}

void X86Architecture::optmiseArithmeticInstruction(Instruction * instruction)
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

void X86Architecture::optmiseConditionalInstruction(Instruction * instruction)
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

void X86Architecture::genArithmetic(ArithmeticInstruction *instruction)
{
    vector<int> * regs = this->getRegisters(instruction);
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(args->at(0)->getInstructionArgument());
    IdentifierInformation * src1IdentifierInfo = this->getInfoFromArgument( args->at(1)->getInstructionArgument());
    IdentifierInformation * src2IdentifierInfo = this->getInfoFromArgument( args->at(2)->getInstructionArgument());

    string x86Instruction;

    if(instruction->getArithmeticOperator()!=ARITHMETIC_OPERATOR_DIV && instruction->getArithmeticOperator()!=ARITHMETIC_OPERATOR_MOD) {
        if(regs->at(0)!=NO_REGISTER && regs->at(1)!=NO_REGISTER && regs->at(0) != regs->at(1)) {
            x86Instruction = "\tmovl ";

            x86Instruction += getRegister(regs->at(1));
            x86Instruction += ", ";
            x86Instruction += getRegister(regs->at(0));

            gen(x86Instruction);
        }
    }

    switch(instruction->getArithmeticOperator()) {
    case ARITHMETIC_OPERATOR_ADD:
        x86Instruction = "\taddl ";
        break;
    case ARITHMETIC_OPERATOR_SUB:
        x86Instruction = "\tsubl ";
        break;
    case ARITHMETIC_OPERATOR_MULT:
        x86Instruction = "\timull ";
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
                        x86Instruction = "\tincl ";
                    } else {
                        x86Instruction = "\tdecl ";
                    }
                } else {
                    x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
                    x86Instruction += ", ";
                }
            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
                x86Instruction += ", ";
            }
        } else {
            x86Instruction += getRegister(regs->at(2));
            x86Instruction += ", ";
        }

        if(regs->at(0) == NO_REGISTER) {
//            cout << args->at(0) << endl;
            if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
//            else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY){
//
//            }
        } else {
            x86Instruction += getRegister(regs->at(0));
        }

        gen(x86Instruction);
    } else {
        x86Instruction = "\tmovl ";

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x86Instruction += getRegister(regs->at(1));
        }

        x86Instruction += ", %edx";
        gen(x86Instruction);
        gen("\tsarl $63, %edx");

        x86Instruction = "\tmovl ";

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            } else {
//                cout << "What?" << endl;
            }
        } else {
            x86Instruction += getRegister(regs->at(1));
        }

        x86Instruction += ", %eax";
        gen(x86Instruction);

        x86Instruction = "\tidivl ";

        if(regs->at(2) == NO_REGISTER) {
            if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
                int reg = getEmptyRegister();
                x86Instruction = "\tmovl ";
                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
                x86Instruction += ", ";
                x86Instruction += getRegister(reg);
                gen(x86Instruction);

                list<IdentifierInformation *> *identifiers = getRegisterDescriptor(reg)->getVariablesList();
                for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {
                    getVariableDescriptor(*it)->removeRegister(reg);
                }
                getRegisterDescriptor(reg)->removeAllVariables();

                x86Instruction = "\tidivl ";
                x86Instruction += getRegister(reg);

            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x86Instruction += getRegister(regs->at(2));
        }

        gen(x86Instruction);

        x86Instruction = "\tmovl ";

        if(instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_DIV) {
            x86Instruction += "%eax, ";
        } else {
            x86Instruction += "%edx, ";
        }

        if(regs->at(0) == NO_REGISTER) {
            if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x86Instruction += getRegister(regs->at(0));
        }

        gen(x86Instruction);

    }

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

void X86Architecture::genReturn(ReturnInstruction *intruction)
{
    vector<int> * regs;
    vector<ArgumentInformation *> *args = intruction->getArgumentsInformation();
    string x86Instruction;

    if(args->at(1)!=NULL) {
        regs = getRegisters(intruction);
        x86Instruction = "\tmovl ";
        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x86Instruction += getRegister(regs->at(1));
        }
        x86Instruction += ", %eax";
        gen(x86Instruction);
    }
    //removeGlobalVariablesFromRegisters();
    //removeVariablesFromRegisters();
    genEpilogue(0);
    //gen("\tleave");
    //gen("\tret");
}

void X86Architecture::genGoto(GotoInstruction *instruction)
{
    string x86Instruction = "\tjmp ";
    InstructionLabel *label = (InstructionLabel *)instruction->getLabelArgument();
    x86Instruction += getMachineInstructionLabel(label->getLabelNumber());
    gen(x86Instruction);
}

void X86Architecture::genConditionalGoto(ConditionalGotoInstruction *instruction)
{
    vector<int> * regs = this->getRegisters(instruction);
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    string x86Instruction;


    // src2 register
    x86Instruction = "\tcmpl ";

    if(regs->at(2) == NO_REGISTER) {
        if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
            x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
            x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x86Instruction += getRegister(regs->at(2));
    }

    x86Instruction += ", ";

    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
            x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x86Instruction += getRegister(regs->at(1));
    }

    gen(x86Instruction);

    //switch( mirrorRelationalOperator(instruction->getRelationalOperator()) ) {
    switch( instruction->getRelationalOperator() ) {
    case RELATIONAL_OPERATOR_EQUAL:
        x86Instruction = "\tje ";
        break;
    case RELATIONAL_OPERATOR_DIFFERENT:
        x86Instruction = "\tjne ";
        break;
    case RELATIONAL_OPERATOR_GREATER:
        x86Instruction = "\tjg ";
        break;
    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        x86Instruction = "\tjge ";
        break;
    case RELATIONAL_OPERATOR_LESS:
        x86Instruction = "\tjl ";
        break;
    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
        x86Instruction = "\tjle ";
        break;
    }
    InstructionLabel *label = (InstructionLabel *)instruction->getLabelArgument();
    x86Instruction += getMachineInstructionLabel(label->getLabelNumber());
    gen(x86Instruction);
}

void X86Architecture::genCopy(CopyInstruction *copyInstruction)
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

void X86Architecture::genNop(NopInstruction *instruction)
{
    gen("\tnop");
}

void X86Architecture::genParam(ParameterInstruction * paramInstruction)
{
    vector<int> * regs  = getRegisters(paramInstruction);
    vector<ArgumentInformation *> *args = paramInstruction->getArgumentsInformation();
    string x86Instruction;

    // src2 register
    x86Instruction = "\tpushl ";
    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
            x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x86Instruction += getRegister(regs->at(1));
    }
    gen(x86Instruction);
}


void X86Architecture::genCall(CallInstruction * callInstruction)
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

    string x86Instruction = "\tcall ";
    IdentifierInformation * functionInfo = ((IdentifierArgument*)callInstruction->getFirstArgument())->getIdentifierInformation();

    x86Instruction += getFunctionLabel(functionInfo);
    gen(x86Instruction);
    //popRegisters();

    if(callInstruction->getDestinationArgument()) {
        x86Instruction = "\tmovl %eax, ";
        if(regs->at(0) == NO_REGISTER) {

          // NAO DEVERIA SER CHAMADO!!! =0
                        cout << args->at(0)->getInstructionArgument()->getType() << endl;

//            if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
//                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
//                x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
//            } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
//                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
//                x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
//            }
//            else
//            {
//
//
//            }
        } else {
            x86Instruction += getRegister(regs->at(0));
        }
        gen(x86Instruction);
        cout << x86Instruction << endl;

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

void X86Architecture::genNegation(NegationInstruction *negationInstruction)
{
    vector<int> * regs = this->getRegisters(negationInstruction);
    vector<ArgumentInformation *> *args = negationInstruction->getArgumentsInformation();

    int dstReg = regs->at(0);
    int srcReg = regs->at(1);

    ArgumentInformation * dst = args->at(0);
    ArgumentInformation * src = args->at(1);

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());
    IdentifierInformation * srcIdentifierInfo = this->getInfoFromArgument(src->getInstructionArgument());

    string x86Instruction ;

// geração do código


//if (Rx != Ry)
//then gen_x86("movl " • Ry • "," • Rx);

    if(dstReg!=NO_REGISTER && srcReg!=NO_REGISTER && dstReg != srcReg) {
        x86Instruction = "\tmovl ";

        x86Instruction += getRegister(srcReg);
        x86Instruction += ", ";
        x86Instruction += getRegister(dstReg);

        gen(x86Instruction);
    }

    x86Instruction  = "\tnegl ";

    if(regs->at(0) == NO_REGISTER) {
        if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(0)->getInstructionArgument();
            x86Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(0)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(0)->getInstructionArgument();
            x86Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x86Instruction += getRegister(regs->at(0));
    }

    gen(x86Instruction);

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

void X86Architecture::pushRegisters()
{
    string x86Instruction;
    for(int reg = 0; reg<getTotalRegisters(); reg++) {
        if(!getRegisterDescriptor(reg)->getVariablesList()->empty()) {
            x86Instruction = "\tpushl ";
            x86Instruction += getRegister(reg);
            gen(x86Instruction);
        }
    }
}

void X86Architecture::popRegisters()
{
    string x86Instruction;
    for(int reg = getTotalRegisters()-1; reg>=0; reg--) {
        if(!getRegisterDescriptor(reg)->getVariablesList()->empty()) {
            x86Instruction = "\tpopl ";
            x86Instruction += getRegister(reg);
            gen(x86Instruction);
        }
    }
}

void X86Architecture::genWrite(WriteInstruction *instruction)
{
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    ArgumentInformation *argumentInformation = args->at(1);

    InstructionArgument *instructionArgument = argumentInformation->getInstructionArgument();

    pushRegisters(); //printf changes all registers but esi

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

    popRegisters(); //printf changes all registers but esi

    delete args;
}

void X86Architecture::genRead(ReadInstruction *instruction)
{
    InstructionArgument *instructionArgument = instruction->getDestinationArgument();
    if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
        IdentifierArgument *identifierArgument = (IdentifierArgument *)instructionArgument;

        pushRegisters(); //printf change all registers but esi
        genRead(identifierArgument->getIdentifierInformation());
        popRegisters(); //printf change all registers but esi
    }

}

void X86Architecture::genLoad(IdentifierInformation *identifierInformation, int registerNumber)
{
    string x86Instruction = "\tmovl ";

    string address = getVariableAddress( identifierInformation );
    x86Instruction += address;
    x86Instruction += ", ";
    x86Instruction += getRegister(registerNumber);

    gen(x86Instruction);

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

void X86Architecture::genStore(int registerNumber, IdentifierInformation *identifierInformation)
{
    string x86Instruction = "\tmovl ";
    x86Instruction += getRegister(registerNumber);

    string address = getVariableAddress( identifierInformation );
    x86Instruction += ", ";
    x86Instruction += address;

    gen( x86Instruction );
    //cout << x86Instruction << endl;

    getVariableDescriptor(identifierInformation)->setInMemory(true);
}

void X86Architecture::initDescriptorTables()
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

void X86Architecture::updateVariablesStatus(Instruction * instruction)
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

void X86Architecture::genWrite(const char *str)
{
    char temp[64];
    string x86Instruction = "\tsubl $";
    x86Instruction += itoa(WORD_SIZE, temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);

    x86Instruction = "\tmovl $";
    x86Instruction += getStringLabel(str);
    x86Instruction += ", (%esp)";
    gen(x86Instruction);

    gen("\tmovl $0, %eax");
    gen("\tcall _printf");

    x86Instruction = "\taddl $";
    x86Instruction += itoa(WORD_SIZE, temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);
}

void X86Architecture::genWrite(IdentifierInformation *identifierInformation)
{
    char temp[64];
    string x86Instruction = "\tsubl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);

    x86Instruction = "\tmovl ";
    VariableDescriptor *varDescriptor = getVariableDescriptor(identifierInformation);
    if(varDescriptor->getRegistersList()->empty())
        x86Instruction += getVariableAddress(identifierInformation);
    else x86Instruction += getRegister(varDescriptor->getRegistersList()->front());
    x86Instruction += ", %eax";
    gen(x86Instruction);

    x86Instruction = "\tmovl %eax, ";
    x86Instruction += itoa(WORD_SIZE, temp, 10);
    x86Instruction += "(%esp)";
    gen(x86Instruction);

    gen("\tmovl $mask_io_str, (%esp)");
    gen("\tmovl $0, %eax");
    gen("\tcall _printf");

    x86Instruction = "\taddl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);
}

void X86Architecture::genWrite(int registerNumber)
{
    char temp[64];
    string x86Instruction = "\tsubl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);

    x86Instruction = "\tmovl ";
    x86Instruction += getRegister(registerNumber);
    x86Instruction += ", ";
    x86Instruction += itoa(WORD_SIZE, temp, 10);
    x86Instruction += "(%esp)";
    gen(x86Instruction);

    gen("\tmovl $mask_io_str, (%esp)");
    gen("\tmovl $0, %eax");
    gen("\tcall _printf");

    x86Instruction = "\taddl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);
}

void X86Architecture::genWrite(ImmediateArgument * immediateArgument)
{

    long value =   immediateArgument->getImmediateValue();

    char temp[64];
    string x86Instruction = "\tsubl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);

    sprintf(temp, "$%d", value);

    x86Instruction = "\tmovl ";
    x86Instruction += temp;
    x86Instruction += ", ";
    x86Instruction += itoa(WORD_SIZE, temp, 10);
    x86Instruction += "(%esp)";
    gen(x86Instruction);

    gen("\tmovl $mask_io_str, (%esp)");
    gen("\tmovl $0, %eax");
    gen("\tcall _printf");

    x86Instruction = "\taddl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);
}

void X86Architecture::genRead(IdentifierInformation *identifierInformation)
{
    char temp[64];
    string x86Instruction = "\tsubl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);

    if(identifierInformation->getScopeLevel()==GLOBAL_SCOPE) {
        //movl	$_a, 4(%esp)
        x86Instruction = "\tmovl $_";
        x86Instruction += identifierInformation->getIdentifier();
        x86Instruction += ", ";
        x86Instruction += itoa(WORD_SIZE, temp, 10);
        x86Instruction += "(%esp)";
        gen(x86Instruction);
    } else {
        x86Instruction = "\tleal ";
        x86Instruction += getVariableAddress(identifierInformation);
        x86Instruction += ", %eax";
        gen(x86Instruction);

        x86Instruction = "\tmovl %eax, ";
        x86Instruction += itoa(WORD_SIZE, temp, 10);
        x86Instruction += "(%esp)";
        gen(x86Instruction);
    }
    gen("\tmovl $mask_io_str, (%esp)");
    gen("\tmovl $0, %eax");
    gen("\tcall _scanf");

    x86Instruction = "\taddl $";
    x86Instruction += itoa((2*WORD_SIZE), temp, 10);
    x86Instruction += ", %esp";
    gen(x86Instruction);

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

void X86Architecture::genMove(long immediate, int reg)
{
    string x86Instruction = "\tmovl ";
    x86Instruction += getMachineImmediate(immediate);
    x86Instruction += ", ";
    x86Instruction += getRegister(reg);
    gen(x86Instruction);
}

string X86Architecture::getMachineImmediate(long immediate)
{
    char temp[64];
    string x86Immediate = "$";
    x86Immediate += itoa(immediate, temp, 10);
    return x86Immediate;

}
string X86Architecture::getMachineString(string str)
{
    stringstream strMachineString;

    for(size_t i = 0 ; i < str.length()-1; i++) {

        if( isprint(str[i]) ) {
            strMachineString << str[i];
        } else {

            strMachineString << '\\' << oct << (int)str[i];
        }
    }

    strMachineString << "\\0\"";
    return strMachineString.str();
}


string X86Architecture::getMachineString(const char *c_str)
{
    string machineString = c_str;
    return getMachineString(machineString);
}

string X86Architecture::getStringLabel(string str)
{
    return getStringLabel(str.c_str());
}

string X86Architecture::getStringLabel(const char *c_str)
{
    char temp[128];
    string str = getMachineString(c_str);
    string strLabel;

    list <string> *stringList = symbolTable_->getStringList();


    //cout << "STRING VALUE: " << str << endl;

    if(str=="\"\\n\\0\"") { //deveria ser "\\12\\0", não ???? HERE --------------------------------------------------------- HERE_-----------------
        strLabel = "new_line_str";
    } else {
        int strCount = 1;
        for(list<string>::iterator it = stringList->begin(); it!=stringList->end(); it++, strCount++) {
            if(str==getMachineString(*it)) {
                strLabel = "str_";
                strLabel += itoa( strCount, temp, 10 );
            }
        }
    }
    return strLabel;
}

string X86Architecture::getRegister(int index)
{
    return registers_.at(index);
}

int X86Architecture::getTotalRegisters()
{
    return registers_.size();
}


string X86Architecture::getFunctionLabel(IdentifierInformation * functionInfo)
{
    string functionLabel = "__";
    functionLabel += functionInfo->getIdentifier();
    return functionLabel;
}

string X86Architecture::getFunctionLabel(string functionName)
{
    string functionLabel;
    if(functionName=="main")
        functionLabel = "_";
    else
        functionLabel = "__";
    functionLabel += functionName;
    return functionLabel;
}

string X86Architecture::getFunctionLabel(const char *functionName)
{
    string fName = functionName;
    return getFunctionLabel(fName);
}

string X86Architecture::getMachineInstructionLabel(int labelNumber)
{
    char temp[64];
    string label = "L";

    label += itoa(labelNumber, temp, 10);

    return label;
}

void X86Architecture::genLabel(string label)
{
    string x86Instruction = label;
    x86Instruction += ":";
    gen(x86Instruction);
}

void X86Architecture::genLabel(const char *label)
{
    string x86Instruction = label;
    x86Instruction += ":";
    gen(x86Instruction);
}

void X86Architecture::genPrologue(FunctionInformation * functionInfo)
{
    stringstream sstream;

    gen("\tpushl %ebp");
    gen("\tmovl %esp, %ebp");

    if(functionInfo) {
        size_t variablesCount = functionInfo->getVariableList().size() * WORD_SIZE;

        if(variablesCount > 0) {
            sstream << "\tsubl $" << variablesCount << ", %esp";
            gen(sstream.str());

        }
    }
}


void X86Architecture::genEpilogue(FunctionInformation * functionInfo)
{
    stringstream sstream;
    /*
    if(functionInfo){
        size_t variablesCount = functionInfo->getVariableList().size() * WORD_SIZE;

        if(variablesCount > 0) {
            sstream << "\taddl $" << (int)variablesCount << ", %esp";
            gen(sstream.str());
        }
    }
    */
    gen("\tleave");
    gen("\tret");

}

void X86Architecture::removeGlobalVariablesFromRegisters()
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

void X86Architecture::saveGlobalVariables()
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

void X86Architecture::saveAliveVariables()
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

void X86Architecture::saveVariables()
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

void X86Architecture::removeVariablesFromRegisters()
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

void X86Architecture::removeVariablesFromRegisters(int registerNumber)
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

void X86Architecture::removeLocalVariablesFromRegisters()
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
