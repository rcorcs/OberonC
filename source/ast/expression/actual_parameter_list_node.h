/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef ACTUAL_PARAMETER_LIST_NODE_H
#define ACTUAL_PARAMETER_LIST_NODE_H

#include "expression_node.h"
#include "../../symbol_table/data_type.h"

#include <list>
using namespace std;

class ActualParameterListNode : public ExpressionNode
{

public:

    ActualParameterListNode();
    ~ActualParameterListNode();

    list<ExpressionNode*> & getActualParameterList();
    void addActualParameter(ExpressionNode *expression);

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:

    void checkConstant();

private:

    list<ExpressionNode *> actualParameterList_;

};

#endif
