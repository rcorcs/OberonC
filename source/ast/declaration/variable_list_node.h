/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef VARIABLE_LIST_NODE_H
#define VARIABLE_LIST_NODE_H

#include "declaration_node.h"
#include "declaration_sequence_node.h"
#include "variable_node.h"

#include "../../symbol_table/data_type.h"

#include <list>
using namespace std;

class VariableListNode : public DeclarationNode
{

public:

    VariableListNode();
    ~VariableListNode();

    void addVariableSequence(DeclarationSequenceNode *variableSequence,
                             DataType type);

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);



private:

    list<VariableNode *> variableList_;

};

#endif
