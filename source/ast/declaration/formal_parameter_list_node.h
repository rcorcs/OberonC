/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FORMAL_PARAMETER_LIST_NODE_H
#define FORMAL_PARAMETER_LIST_NODE_H

#include "declaration_node.h"
#include "declaration_sequence_node.h"
#include "formal_parameter_node.h"

#include "../../symbol_table/data_type.h"

#include <list>
using namespace std;

class FormalParameterListNode : public DeclarationNode
{

public:

    FormalParameterListNode();
    ~FormalParameterListNode();

    void addFormalParameterSequence(DeclarationSequenceNode *formalParameterSequence,
                                    DataType type);

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);
    void generateCCode(ostream &out);


private:

    list<FormalParameterNode *> formalParameterList_;

};

#endif
