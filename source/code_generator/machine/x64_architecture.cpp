/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "x64_architecture.h"


#include <sstream>
using namespace std;

//const int X64Architecture::WORD_SIZE = 8;

X64Architecture::X64Architecture(SymbolTable * symbolTable, IntermediateCode * intermediateCode)
    : MachineCode(symbolTable, intermediateCode)
{

    registers_.push_back("%rcx");
    registers_.push_back("%r8");
    registers_.push_back("%r9");
    registers_.push_back("%r10");
    registers_.push_back("%r11");
    registers_.push_back("%r12");
    registers_.push_back("%r13");
    registers_.push_back("%r14");
    registers_.push_back("%r15");
}

void X64Architecture::generateCode()
{

    vector<BasicBlock *> *basicBlocks = this->intermediateCode_->getBasicBlocks();

    genStartingCode();

    for(size_t i = 0; i < basicBlocks->size(); i++) {
        this->initDescriptorTables();

        BasicBlock * basicBlock = basicBlocks->at(i);
        FunctionInformation * functionInfo = NULL;

        if(basicBlock->isStartingFunction()) {
            string x64Instruction = "\t.globl ";
            x64Instruction += getFunctionLabel(basicBlock->getFunctionName());
            gen(x64Instruction);
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
            }else if(!strcmp(basicBlock->getFunctionName(), intermediateCode_->getMainFunctionName())){
                genPrologue(0);
            }

        }

        vector<Instruction *> * instructionVector = basicBlock->getInstructionVector();

        for(size_t j = 0; j < instructionVector->size() ; j++) {
            Instruction * instruction = instructionVector->at( j );

            this->updateVariablesStatus(instruction);
            this->genInstruction(instruction);
        }

        if(functionInfo != NULL) {

            genEpilogue(functionInfo);

        }else if(!strcmp(basicBlock->getFunctionName(), intermediateCode_->getMainFunctionName())){
            genEpilogue(0);
        }


        delete instructionVector;
        delete basicBlock;
    }

    delete basicBlocks;

    /*
    genStartingCode();
    vector<const char *> *functionNames = this->intermediateCode_->getFunctionNames();

    vector<Instruction *> *instructionVector;
    for(size_t i = 0; i<functionNames->size(); i++)
    {
        instructionVector = this->intermediateCode_->getInstructionVector(functionNames->at(i));

        genLabel( getFunctionLabel(functionNames->at(i)) );

        for(size_t j = 0; j < instructionVector->size() ; j++) {
            Instruction * instruction = instructionVector->at( j );

            this->updateVariablesStatus(instruction);
            this->genInstruction(instruction);
        }
    }
    */
}


void X64Architecture::genStartingCode()
{
    list <IdentifierInformation *> *IdentifierList = symbolTable_->getIdentifierInfoList();
    list <string> *stringList = symbolTable_->getStringList();
    IdentifierInformation *info;
    char temp[128];
    string x64Instruction;

    x64Instruction = "\t.file \"";
    x64Instruction += baseFileName_;
    x64Instruction += "\"";
    gen(x64Instruction);

    for(list <IdentifierInformation *>::iterator it = IdentifierList->begin(); it!=IdentifierList->end(); it++) {
        info = (*it);
        if(info->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation * varInfo = (VariableInformation *)info;
            if(varInfo->getScopeLevel()==2) { //MODULE SCOPE
                x64Instruction = "\t.comm _";
                x64Instruction += varInfo->getIdentifier();
                //x64Instruction += itoa( varInfo->getOffset(), temp, 10 );
                x64Instruction += ", 8, 3";
                gen(x64Instruction);
            }
        }
    }
    gen("\t.section .data");
    gen("mask_io_str:");
    gen("\t.ascii \"%ld\\0\"");
    gen("new_line_str:");
    gen("\t.ascii \"\\12\\0\"");

    int strCount = 1;
    for(list<string>::iterator it = stringList->begin(); it!=stringList->end(); it++, strCount++) {
        x64Instruction = "str_";
        //x64Instruction += itoa( strCount, temp, 10 );
        sprintf(temp, "%d", strCount);
        x64Instruction += temp;
        x64Instruction += ":";
        gen(x64Instruction);

        x64Instruction = "\t.ascii ";
        x64Instruction += getMachineString(*it);
        gen(x64Instruction);
    }

    gen("\t.section .text");

    //x64Instruction = "\t.globl ";
    //x64Instruction += getFunctionLabel(intermediateCode_->getMainFunctionName());
    //gen("\t.globl _main");
    //gen(x64Instruction);
}

/*
void X64Architecture::initDescriptorTables()
{
    for(unsigned int reg = 0; reg<registers_.size(); reg++){
        RegisterDescriptor * registerDescriptor = new RegisterDescriptor();
        this->registerDescriptorTable_.set(reg, registerDescriptor);
    }
}
*/

int X64Architecture::getOffset(IdentifierInformation *identifierInformation)
{
    int offset = 0;
    if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER) {
        FormalParameterInformation *formalParamameter = (FormalParameterInformation *)identifierInformation;
        offset = formalParamameter->getOffset()*(-8);
    } else if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
        VariableInformation *variable = (VariableInformation *)identifierInformation;
        offset = variable->getOffset()*(8);
    }
    return offset;
}

string X64Architecture::getVariableAddress(IdentifierInformation *identifierInformation)
{
    char temp[32];
    if(identifierInformation->getScopeLevel()==2) {
        //TODO
        string x64Instruction = "\tmovq _";
        if(identifierInformation->getCategoryType()==IDENTIFIER_CATEGORY_TYPE_VARIABLE) {
            VariableInformation *variable = (VariableInformation *)identifierInformation;
            //x64Instruction += variable->getOffset();
            x64Instruction += variable->getIdentifier();
        }
        x64Instruction += "@GOTPCREL(%rip), %rbx";
        gen( x64Instruction );
        //gen movq _idV@GOTPCREL(%rip), %rbx
        string address = "(%rbx)";
        return address;
    } else {
        //string address = itoa( getOffset(identifierInformation), temp, 10 );
        sprintf(temp, "%d", getOffset(identifierInformation));
        string address = temp;
        address += "(%rbp)";
        return address;
    }
}

void X64Architecture::genInstruction(Instruction *instruction)
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

    case INSTRUCTION_TYPE_WRITE:
          genWrite((WriteInstruction*)instruction);
        break;

    default:
        break;
    }
}

//FAZER
int X64Architecture::getEmptyRegister(list<int> *avoidList, list<int> *avoidSecondList)
{
    int min_cost = 0x80000000, best_reg = NO_REGISTER;
    list<IdentifierInformation *> *identifiers;
    for(int reg = 0; reg<getTotalRegisters(); reg++) {
        //ha registrador livre?
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
                return reg;
            }
        }

        identifiers = getRegisterDescriptor(reg)->getVariablesList();

        //ha registrador que armazena apenas variaveis nao vivas?
        bool useRegister = isAllowed;
        for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {

            useRegister = useRegister && !getVariableDescriptor(*it)->isAlive();
        }
        if(useRegister)
            return reg;

        //ha registrador que armazena apenas variaveis salvas?
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
            if(!getVariableDescriptor(*it)->isInMemory())
                cost++;
        }
        if(cost<min_cost) {
            best_reg = reg;
            min_cost = cost;
        }

    }
    if(best_reg!=NO_REGISTER) {
        identifiers = getRegisterDescriptor(best_reg)->getVariablesList();
        for(list<IdentifierInformation *>::iterator it = identifiers->begin(); it!=identifiers->end(); it++) {

            //quando fazer o alive no DV
            if(getVariableDescriptor(*it)->isAlive() && !getVariableDescriptor(*it)->isInMemory()) {
                genStore(best_reg, (*it));
            }
        }
    }

    return best_reg;
}

//FUNCAO get_reg( instruction(op, x, y, z) )
//FAZER AQUI: FAZER DE ACORDO COM OS SLIDES
vector<int> *X64Architecture::getRegisters(Instruction *instruction)
{
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    vector<int> * regs = new vector<int>();

    int destinationRegister = NO_REGISTER;
    int firstSourceRegister = NO_REGISTER;
    int secondSourceRegister = NO_REGISTER;

    switch(instruction->getInstructionType()) {

        // Otimiza acesso para operacao comutativa
    case INSTRUCTION_TYPE_ARITHMETIC:
        this->optmiseArithmeticInstruction(instruction);
        break;

    case INSTRUCTION_TYPE_CONDITIONAL_GOTO:
        this->optmiseConditionalInstruction(instruction);
        break;

    default:
        break;
    }

    ArgumentInformation * src1 = args->at(1);
    ArgumentInformation * src2 = 0;
    if(args->size()==3)
        src2 = args->at(2);

    bool isFirstValidArgument = (src1->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER || src1->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY);
    IdentifierInformation * firstSourceInfo = 0;
    VariableDescriptor * firstSourceDescriptor = 0;
    if(isFirstValidArgument) {
        firstSourceInfo = this->getInfoFromArgument(src1->getInstructionArgument());
        firstSourceDescriptor = this->getVariableDescriptor(firstSourceInfo);
    }

    IdentifierInformation * secondSourceInfo = 0;
    VariableDescriptor * secondSourceDescriptor = 0;

    if(src2) {
        if(src2->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER || src2->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_TEMPORARY) {
            secondSourceInfo = this->getInfoFromArgument(src2->getInstructionArgument());
            secondSourceDescriptor = this->getVariableDescriptor(firstSourceInfo);
        }
    }

    // aloca registrador Ry para y
    //caso 1: y nao esta em registrador
    if(isFirstValidArgument) {
        if(firstSourceDescriptor->getRegistersList()->empty()) {
            if(secondSourceDescriptor)
                firstSourceRegister = getEmptyRegister( secondSourceDescriptor->getRegistersList() );
            else firstSourceRegister = getEmptyRegister( );
            genLoad(firstSourceInfo, firstSourceRegister);
        } else { //caso 2: y esta no registrador R1
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
        //caso 1: z nao esta em registrador
        if(secondSourceDescriptor->getRegistersList()->empty()) {
            if(src2->getStatus()>=0) { //z e' usado novamente
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


    if(args->at(0)!=NULL) {
        if(isFirstValidArgument && instruction->getInstructionType()!=INSTRUCTION_TYPE_COPY) {
            if(src1->getStatus()>=0) {
                destinationRegister = getEmptyRegister( firstSourceDescriptor->getRegistersList(), secondSourceDescriptor->getRegistersList() );
            } else if(!firstSourceDescriptor->isInMemory() && src1->getStatus()==ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT) {
                genStore(firstSourceRegister, firstSourceInfo);
            }
        }
        destinationRegister = firstSourceRegister;
    }

    regs->push_back(destinationRegister);
    regs->push_back(firstSourceRegister);
    regs->push_back(secondSourceRegister);

    delete args;
    return regs;
}

void X64Architecture::optmiseArithmeticInstruction(Instruction * instruction)
{

    ArithmeticInstruction * arithmeticInstruction = (ArithmeticInstruction*)instruction;
    ArithmeticOperator op = arithmeticInstruction->getArithmeticOperator();

    if(op == ARITHMETIC_OPERATOR_ADD || op == ARITHMETIC_OPERATOR_MULT) {



        vector<ArgumentInformation *> *args = arithmeticInstruction->getArgumentsInformation();

        ArgumentInformation * src1 = args->at(1);
        ArgumentInformation * src2 = args->at(2);

        if(src1->getInstructionArgument()->getType() == INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            arithmeticInstruction->setFirstArgument(src2->getInstructionArgument());
            arithmeticInstruction->setSecondArgument(src1->getInstructionArgument());
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
                arithmeticInstruction->setFirstArgument(src2->getInstructionArgument());
                arithmeticInstruction->setSecondArgument(src1->getInstructionArgument());
            }

        }
    }


}

void X64Architecture::optmiseConditionalInstruction(Instruction * instruction)
{
    ConditionalGotoInstruction * conditionalGotoInstruction = (ConditionalGotoInstruction*)instruction;
    RelationalOperator op = conditionalGotoInstruction->getRelationalOperator();

    op = mirrorRelationalOperator(op);
    vector<ArgumentInformation *> *args = conditionalGotoInstruction->getArgumentsInformation();

    ArgumentInformation * src1 = args->at(1);
    ArgumentInformation * src2 = args->at(2);

    if(src1->getInstructionArgument()->getType() == INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
        conditionalGotoInstruction->setFirstArgument(src2->getInstructionArgument());
        conditionalGotoInstruction->setSecondArgument(src1->getInstructionArgument());
        conditionalGotoInstruction->setRelationalOperator(op);
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
            conditionalGotoInstruction->setFirstArgument(src2->getInstructionArgument());
            conditionalGotoInstruction->setSecondArgument(src1->getInstructionArgument());
            conditionalGotoInstruction->setRelationalOperator(op);
        }
    }
}

void X64Architecture::genArithmetic(ArithmeticInstruction *instruction)
{
    vector<int> * regs = this->getRegisters(instruction);
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(args->at(0)->getInstructionArgument());
    IdentifierInformation * src1IdentifierInfo = this->getInfoFromArgument( args->at(1)->getInstructionArgument());
    IdentifierInformation * src2IdentifierInfo = this->getInfoFromArgument( args->at(2)->getInstructionArgument());

    string x64Instruction;

    switch(instruction->getArithmeticOperator()) {
    case ARITHMETIC_OPERATOR_ADD:
        x64Instruction = "\taddq ";
        break;
    case ARITHMETIC_OPERATOR_SUB:
        x64Instruction = "\tsubq ";
        break;
    case ARITHMETIC_OPERATOR_MULT:
        x64Instruction = "\timulq ";
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
                        x64Instruction = "\tincq ";
                    } else {
                        x64Instruction = "\tdecq ";
                    }
                } else {
                    x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
                    x64Instruction += ", ";
                }
            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
                x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
                x64Instruction += ", ";
            }
        } else {
            x64Instruction += getRegister(regs->at(2));
            x64Instruction += ", ";
        }

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x64Instruction += getRegister(regs->at(1));
        }

        gen(x64Instruction);
    } else {
        x64Instruction = "\tmovq ";

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x64Instruction += getRegister(regs->at(1));
        }

        x64Instruction += ", %rdx";
        gen(x64Instruction);
        gen("\tsarq $63, %rdx");

        x64Instruction = "\tmovq ";

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x64Instruction += getRegister(regs->at(1));
        }

        x64Instruction += ", %rax";
        gen(x64Instruction);

        x64Instruction = "\tidivq ";

        if(regs->at(2) == NO_REGISTER) {
            if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
                x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());

            } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
                x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x64Instruction += getRegister(regs->at(2));
        }

        gen(x64Instruction);

        x64Instruction = "\tmovq ";

        if(instruction->getArithmeticOperator()==ARITHMETIC_OPERATOR_DIV) {
            x64Instruction += "%rax, ";
        } else {
            x64Instruction += "%rdx, ";
        }

        if(regs->at(1) == NO_REGISTER) {
            if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
                ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
            } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
                IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
                x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
            }
        } else {
            x64Instruction += getRegister(regs->at(1));
        }

        gen(x64Instruction);

    }

    if(regs->at(0) == regs->at(1)) {

        // DV[y].reg.remove(Ry);

        VariableDescriptor * srcDV  = this->getVariableDescriptor(src1IdentifierInfo);
        srcDV->removeRegister(regs->at(1));
    }

    VariableDescriptor * dstDV  = this->getVariableDescriptor(dstIdentifierInfo);
    RegisterDescriptor * dstDR  = this->getRegisterDescriptor(regs->at(0));

    //DV[x].reg = new_list(Rx); DV[x].mem = false;
    dstDV->removeAllRegisters();
    dstDV->addRegister(regs->at(0));
    dstDV->setInMemory(false);

//DR[Rx] = new_list(x);
    dstDR->removeAllVariables();
    dstDR->addVariable(dstIdentifierInfo);

    if(regs->at(1)!=regs->at(0)) {
        cout << "ERROR: Arithmetic Instruction: destination register is not right! " << x64Instruction;
    }


}

void X64Architecture::genGoto(GotoInstruction *instruction)
{
    string x64Instruction = "\tjmp ";
    InstructionLabel *label = (InstructionLabel *)instruction->getLabelArgument();
    x64Instruction += getMachineInstructionLabel(label->getLabelNumber());
    gen(x64Instruction);
}

void X64Architecture::genConditionalGoto(ConditionalGotoInstruction *instruction)
{
    vector<int> * regs = this->getRegisters(instruction);
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    string x64Instruction;

    // src2 register
    x64Instruction = "\tcmpq ";
    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
            x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x64Instruction += getRegister(regs->at(1));
    }

    x64Instruction += ", ";
    if(regs->at(2) == NO_REGISTER) {
        if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(2)->getInstructionArgument();
            x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(2)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(2)->getInstructionArgument();
            x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x64Instruction += getRegister(regs->at(2));
    }
    gen(x64Instruction);

    switch(instruction->getRelationalOperator()) {
    case RELATIONAL_OPERATOR_EQUAL:
        x64Instruction = "\tje ";
        break;
    case RELATIONAL_OPERATOR_DIFFERENT:
        x64Instruction = "\tjne ";
        break;
    case RELATIONAL_OPERATOR_GREATER:
        x64Instruction = "\tjg ";
        break;
    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        x64Instruction = "\tjge ";
        break;
    case RELATIONAL_OPERATOR_LESS:
        x64Instruction = "\tjl ";
        break;
    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
        x64Instruction = "\tjle ";
        break;
    }
    InstructionLabel *label = (InstructionLabel *)instruction->getLabelArgument();
    x64Instruction += getMachineInstructionLabel(label->getLabelNumber());
    gen(x64Instruction);
}

void X64Architecture::genCopy(CopyInstruction *copyInstruction)
{

    vector<int> * regs = this->getRegisters(copyInstruction);
    vector<ArgumentInformation *> *args = copyInstruction->getArgumentsInformation();

    int dstReg = regs->at(0);

    ArgumentInformation * dst = args->at(0);

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());

    VariableDescriptor * dstDV = this->getVariableDescriptor(dstIdentifierInfo);
    RegisterDescriptor * dstDR  = this->getRegisterDescriptor(dstReg);

    // atualizacao das informacoes (Rx = Ry)

//DV[x].reg = new_list(Rx); DV[x].mem = false;
    dstDV->removeAllRegisters();
    dstDV->addRegister(dstReg);
    dstDV->setInMemory(false);

//DR[Rx].add(x);
    dstDR->addVariable(dstIdentifierInfo);


// nao e' necessario gerar codigo



}

void X64Architecture::genNop(NopInstruction *instruction)
{
    gen("\tnop");
}

void X64Architecture::genParam(ParameterInstruction * paramInstruction)
{
    vector<int> * regs  = getRegisters(paramInstruction);
    vector<ArgumentInformation *> *args = paramInstruction->getArgumentsInformation();
    string x64Instruction;

    // src2 register
    x64Instruction = "\tpushq ";
    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
            x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x64Instruction += getRegister(regs->at(1));
    }
    gen(x64Instruction);
}


void X64Architecture::genCall(CallInstruction * callInstruction)
{
    gen("\tpushq $0");
    //gen("pushq %rip");

    string x64Instruction = "\tcall ";
    IdentifierInformation * functionInfo = ((IdentifierArgument*)callInstruction->getFirstArgument())->getIdentifierInformation();

    x64Instruction += getFunctionLabel(functionInfo);
    gen(x64Instruction);
}

void X64Architecture::genNegation(NegationInstruction *negationInstruction)
{
    vector<int> * regs = this->getRegisters(negationInstruction);
    vector<ArgumentInformation *> *args = negationInstruction->getArgumentsInformation();

    int dstReg = regs->at(0);
    int srcReg = regs->at(1);

    ArgumentInformation * dst = args->at(0);
    ArgumentInformation * src = args->at(1);

    IdentifierInformation * dstIdentifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());
    IdentifierInformation * srcIdentifierInfo = this->getInfoFromArgument(src->getInstructionArgument());

    string x64Instruction ;

// geracao do codigo


//if (Rx != Ry)
//then gen_x64("movq " ? Ry ? "," ? Rx);
    /*
    if(dstReg != srcReg) {
        x64Instruction = "\tmovq ";

        x64Instruction += getRegister(srcReg);
        x64Instruction += ", ";
        x64Instruction += getRegister(dstReg);

        gen(x64Instruction);
    }
    */

    x64Instruction  = "\tnegq ";

    if(regs->at(1) == NO_REGISTER) {
        if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE) {
            ImmediateArgument * immediateArgument = (ImmediateArgument*)args->at(1)->getInstructionArgument();
            x64Instruction += getMachineImmediate(immediateArgument->getImmediateValue());
        } else if(args->at(1)->getInstructionArgument()->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
            IdentifierArgument * identifierArgument = (IdentifierArgument*)args->at(1)->getInstructionArgument();
            x64Instruction += getVariableAddress(identifierArgument->getIdentifierInformation());
        }
    } else {
        x64Instruction += getRegister(regs->at(1));
    }

    gen(x64Instruction);

// atualizacao das informacoes
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


void X64Architecture::genWrite(WriteInstruction *instruction)
{
    vector<ArgumentInformation *> *args = instruction->getArgumentsInformation();
    ArgumentInformation *argumentInformation = args->at(1);

    InstructionArgument *instructionArgument = argumentInformation->getInstructionArgument();
    if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
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
    }else if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_STRING) {
        StringArgument *stringArgument = (StringArgument *)instructionArgument;
        genWrite(stringArgument->getStringValue());
    }

    delete args;
}

void X64Architecture::genRead(ReadInstruction *instruction)
{
    InstructionArgument *instructionArgument = instruction->getDestinationArgument();
    if(instructionArgument->getType()==INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER) {
        IdentifierArgument *identifierArgument = (IdentifierArgument *)instructionArgument;
        genRead(identifierArgument->getIdentifierInformation());
    }
}

void X64Architecture::genLoad(IdentifierInformation *identifierInformation, int registerNumber)
{
    string x64Instruction = "\tmovq ";

    string address = getVariableAddress( identifierInformation );
    x64Instruction += address;
    x64Instruction += ", ";
    x64Instruction += getRegister(registerNumber);

    gen(x64Instruction);

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

void X64Architecture::genStore(int registerNumber, IdentifierInformation *identifierInformation)
{
    string x64Instruction = "\tmovq ";
    x64Instruction += getRegister(registerNumber);

    string address = getVariableAddress( identifierInformation );
    x64Instruction += ", ";
    x64Instruction += address;

    gen( x64Instruction );
    //cout << x64Instruction << endl;

    getVariableDescriptor(identifierInformation)->setInMemory(true);
}

void X64Architecture::initDescriptorTables()
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

void X64Architecture::updateVariablesStatus(Instruction * instruction)
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

void X64Architecture::genWrite(const char *str)
{
    string x64Instruction = "\tleaq ";

    //ALTERAR AQUI
    x64Instruction += getStringLabel(str);

    x64Instruction += "(%rip), %rdi";
    gen(x64Instruction);

    gen("\tmovq $0, %rax");
    gen("\tcall _printf");
}

void X64Architecture::genWrite(IdentifierInformation *identifierInformation)
{
    string x64Instruction = "\tmovq ";
    x64Instruction += getVariableAddress(identifierInformation);
    x64Instruction += "%rsi";
    gen(x64Instruction);

    gen("\tleaq mask_io_str(%rip), %rdi");
    gen("\tmovq $0, %rax");
    gen("\tcall _printf");
}

void X64Architecture::genWrite(int registerNumber)
{
    char temp[32];
    string x64Instruction = "\tmovq ";
    //x64Instruction += itoa(registerNumber, temp, 10);
    x64Instruction += getRegister(registerNumber);
    x64Instruction += "%rsi";
    gen(x64Instruction);

    gen("\tleaq mask_io_str(%rip), %rdi");
    gen("\tmovq $0, %rax");
    gen("\tcall _printf");
}

void X64Architecture::genRead(IdentifierInformation *identifierInformation)
{
    string x64Instruction = "\tleaq ";
    x64Instruction += getVariableAddress(identifierInformation);
    x64Instruction += ", %rsi";
    gen(x64Instruction);

    gen("\tleaq mask_io_str(%rip), %rdi");
    gen("\tmovq $0, %rax");
    gen("\tcall _scanf");

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

void X64Architecture::genMove(long immediate, int reg)
{
    string x64Instruction = "\tmovq ";
    x64Instruction += getMachineImmediate(immediate);
    x64Instruction += ", ";
    x64Instruction += getRegister(reg);
    gen(x64Instruction);
}

string X64Architecture::getMachineImmediate(long immediate)
{
    char temp[64];
    string x64Immediate = "$";
    //x64Immediate += itoa(immediate, temp, 10);
    sprintf(temp, "%d", immediate);
    x64Immediate += temp;
    return x64Immediate;

}
string X64Architecture::getMachineString(string str)
{
    stringstream strMachineString;

    for(size_t i = 0 ; i < str.length(); i++) {

        if( isprint(str[i]) ) {
            strMachineString << str[i];
        } else {

            strMachineString << '\\' << oct << (int)str[i];
        }
    }

    return strMachineString.str();
}


string X64Architecture::getMachineString(const char *c_str)
{
    string machineString = c_str;
    return getMachineString(machineString);
}

string X64Architecture::getStringLabel(string str)
{
    return getStringLabel(str.c_str());
}

string X64Architecture::getStringLabel(const char *c_str)
{
    char temp[128];
    string str = getMachineString(c_str);
    string strLabel;

    list <string> *stringList = symbolTable_->getStringList();

    int strCount = 1;
    for(list<string>::iterator it = stringList->begin(); it!=stringList->end(); it++, strCount++) {
        if((*it)==str) {
            strLabel = "str_";
            //strLabel += itoa( strCount, temp, 10 );
            sprintf(temp, "%d", strCount);
            strLabel += temp;
        }
    }
    return strLabel;
}

string X64Architecture::getRegister(int index)
{
    return registers_.at(index);
}

int X64Architecture::getTotalRegisters()
{
    return registers_.size();
}


string X64Architecture::getFunctionLabel(IdentifierInformation * functionInfo)
{
    string functionLabel = "__";
    functionLabel += functionInfo->getIdentifier();
    return functionLabel;
}

string X64Architecture::getFunctionLabel(string functionName)
{
    string functionLabel;
    if(functionName=="main")
        functionLabel = "_";
    else
        functionLabel = "__";
    functionLabel += functionName;
    return functionLabel;
}

string X64Architecture::getFunctionLabel(const char *functionName)
{
    string fName = functionName;
    return getFunctionLabel(fName);
}

string X64Architecture::getMachineInstructionLabel(int labelNumber)
{
    char temp[64];
    string label = "L";

    //label += itoa(labelNumber, temp, 10);
    sprintf(temp, "%d", labelNumber);
    label += temp;

    return label;
}

void X64Architecture::genLabel(string label)
{
    string x64Instruction = label;
    x64Instruction += ":";
    gen(x64Instruction);
}

void X64Architecture::genLabel(const char *label)
{
    string x64Instruction = label;
    x64Instruction += ":";
    gen(x64Instruction);
}

void X64Architecture::genPrologue(FunctionInformation * functionInfo)
{
    stringstream sstream;

    gen("\tpushq %rbp");
    gen("\tmovq %rsp, %rbp");

    if(functionInfo){
        size_t variablesCount = functionInfo->getVariableList().size() * 8;

        if(variablesCount > 0) {
            sstream << "\tsubq $" << variablesCount << ", %rsp";
            gen(sstream.str());

        }
    }

}


void X64Architecture::genEpilogue(FunctionInformation * functionInfo)
{
    stringstream sstream;

    if(functionInfo){
        size_t variablesCount = functionInfo->getVariableList().size() * 8;

        if(variablesCount > 0) {
            sstream << "\taddq $" << (int)variablesCount << ", %rsp";
            gen(sstream.str());
        }
    }

    gen("\tleave");
    gen("\tret");

}
