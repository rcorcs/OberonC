/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CONSTANT_LIST_NODE_H
#define CONSTANT_LIST_NODE_H

#include "declaration_node.h"
#include "declaration_sequence_node.h"
#include "constant_node.h"

#include "../../symbol_table/data_type.h"

#include <list>
using namespace std;

class ConstantListNode : public DeclarationNode
{

public:

    ConstantListNode();
    ~ConstantListNode();

    void addConstantSequence(DeclarationSequenceNode *constSequence, DataType type);

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);


private:

    list<ConstantNode *> constantList_;

};

#endif
