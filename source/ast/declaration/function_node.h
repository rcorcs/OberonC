/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "declaration_node.h"
#include "../statement/statement_node.h"

#include "../../symbol_table/data_type.h"
#include "../../symbol_table/identifier_category/function_information.h"


class FunctionNode : public DeclarationNode
{
public:

    FunctionNode(FunctionInformation *functionInfo,
                 DeclarationNode *declarations,
                 StatementNode *statements);

    ~FunctionNode();

    const char *getIdentifier();

    DataType getReturnType() const;
    void setReturnType(const DataType returnType);

    void setDeclarations(DeclarationNode *declarations);
    DeclarationNode * getDeclarations() const;

    void setStatements(StatementNode *statements);
    StatementNode * getStatements() const;

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger * astDebugger, int nodeLevel);
    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode);

private:

    FunctionInformation *functionInfo_;
    DeclarationNode *declarations_;
    StatementNode *statements_;

};

#endif
