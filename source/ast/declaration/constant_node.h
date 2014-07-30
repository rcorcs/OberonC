/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CONSTANT_NODE_H
#define CONSTANT_NODE_H

#include "declaration_node.h"
#include "../expression/expression_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_category/constant_information.h"


class ConstantNode : public DeclarationNode
{

public:

    ConstantNode(ConstantInformation *constantInformation,
                 ExpressionNode *expressionValue);
    ~ConstantNode();

    DataType getType() const;
    void setType(const DataType DataType);

    ExpressionNode *getExpressionValue() const;
    void setExpressionValue(ExpressionNode *expressionValue);

    const char *getIdentifier() const;

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger * astDebugger, int nodeLevel);
    void generateCCode(ostream &out);


private:

    ConstantInformation *constantInformation_;
    ExpressionNode *expressionValue_;

};

#endif
