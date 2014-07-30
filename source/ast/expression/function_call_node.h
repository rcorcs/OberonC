/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H

#include "expression_node.h"
#include "actual_parameter_list_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_category/function_information.h"


class FunctionCallNode : public ExpressionNode
{

public:

    FunctionCallNode(FunctionInformation *functionInfo,  ActualParameterListNode *actualParameterList);
    ~FunctionCallNode();


    const char *getIdentifier();

    void setReturnType(const DataType type);
    DataType getReturnType() const;

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:


    void checkConstant();

private:

    FunctionInformation * functionInfo_;
    ActualParameterListNode * actualParameterList_;

};

#endif
