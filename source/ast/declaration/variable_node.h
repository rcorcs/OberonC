/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef VARIABLE_NODE_H
#define VARIABLE_NODE_H

#include "declaration_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_category/variable_information.h"


class VariableNode : public DeclarationNode
{

public:

    VariableNode(VariableInformation *variableInfo);
    ~VariableNode();

    DataType getType() const;
    void setType(const DataType type);

    VariableInformation *getIdentifierInformation();

    const char *getIdentifier() const;

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);



private:

    VariableInformation *variableInfo_;
};

#endif
