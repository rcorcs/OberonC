/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

#include "../node.h"

#include "../../symbol_table/data_type.h"

#include "../../code_generator/intermediate/intermediate_code.h"

#include "../../code_generator/intermediate/instruction_argument/instruction_argument.h"
#include "../../code_generator/intermediate/instruction_argument/label_argument.h"
#include "../../code_generator/intermediate/instruction_argument/instruction_label.h"

class ExpressionNode : public Node
{

public:

    ExpressionNode(const NodeType nodeType);
    virtual ~ExpressionNode();

    bool isConstant() const;
    ExpressionNode * getConstantExpression() const;

    void setTrueLabelNumber(const int trueLabelNumber);
    int getTrueLabelNumber() const ;

    void setFalseLabelNumber(const int falseLabelNumber);
    int getFalseLabelNumber() const ;

    InstructionArgument *getAddress();
    void setAddress(InstructionArgument *address);

    virtual void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector) = 0;

    virtual DataType typeCheck(SemanticDebugger *semanticDebugger) = 0;
    DataType getDataType() const;
    void setDataType(const DataType dataType);
    virtual void generateCCode(ostream &out) = 0;

protected:
    InstructionArgument *address_;
    bool isConstant_;
    ExpressionNode * constantExpression_;

    int trueLabelNumber_;
    int falseLabelNumber_;

    DataType dataType_;

    virtual void checkConstant() = 0;

};

#endif
