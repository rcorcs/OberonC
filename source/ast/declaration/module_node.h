/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef MODULE_NODE_H
#define MODULE_NODE_H

#include "declaration_node.h"
#include "../statement/statement_node.h"

#include "../../symbol_table/identifier_category/module_information.h"

class ModuleNode : public DeclarationNode
{

public:

    ModuleNode(ModuleInformation *moduleInfo,
               DeclarationNode *declarations,
               StatementNode *statements);

    ~ModuleNode();

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger * astDebugger, int nodeLevel);
    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode);

private:

    ModuleInformation *moduleInfo_;
    DeclarationNode *declarations_;
    StatementNode *statements_;

};

#endif
