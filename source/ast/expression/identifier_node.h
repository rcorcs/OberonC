/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef IDENTIFIER_NODE_H
#define IDENTIFIER_NODE_H

#include "expression_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_information.h"
#include "../../symbol_table/identifier_category/constant_information.h"
#include "../../symbol_table/identifier_category/variable_information.h"
#include "../../symbol_table/identifier_category/formal_parameter_information.h"


class IdentifierNode : public ExpressionNode
{
public:

    IdentifierNode(IdentifierInformation *identifierInfo);
    ~IdentifierNode();

    IdentifierInformation *getIdentifierInformation();
    const char *getIdentifier() const;
    IdentifierCategoryType getCategoryType() const;
    DataType getType() const;

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:

    void checkConstant();

private:

    IdentifierInformation *identifierInfo_;
};

#endif

