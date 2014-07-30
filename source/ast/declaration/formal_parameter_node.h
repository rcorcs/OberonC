/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FORMAL_PARAMETER_NODE_H
#define FORMAL_PARAMETER_NODE_H

#include "declaration_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_category/formal_parameter_information.h"


class FormalParameterNode : public DeclarationNode
{

public:

    FormalParameterNode(FormalParameterInformation *formalParameterInfo);
    ~FormalParameterNode();

    const char *getIdentifier() const;
    FormalParameterInformation *getIdentifierInformation();

    DataType getType() const;
    void setType(const DataType type);

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);
    void generateCCode(ostream &out);


private:

    FormalParameterInformation * formalParameterInfo_;

};

#endif
