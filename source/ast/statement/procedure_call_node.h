/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef PROCEDURE_CALL_NODE_H
#define PROCEDURE_CALL_NODE_H

#include "statement_node.h"
#include "../expression/expression_node.h"
#include "../expression/actual_parameter_list_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_category/function_information.h"


class ProcedureCallNode : public StatementNode
{

public:

    ProcedureCallNode(FunctionInformation *functionInfo, ActualParameterListNode* actualParameterList);
    ~ProcedureCallNode();

    const char *getIdentifier();

    void typeCheck(SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);
private:

    FunctionInformation * functionInfo_;
    ActualParameterListNode * actualParameterList_;

};

#endif
