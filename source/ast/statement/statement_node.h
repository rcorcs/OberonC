/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef STATEMENT_NODE_H
#define STATEMENT_NODE_H

#include "../node.h"
#include "../../symbol_table/data_type.h"

#include "../../code_generator/intermediate/intermediate_code.h"

#include "../../code_generator/intermediate/instruction_argument/instruction_argument.h"
#include "../../code_generator/intermediate/instruction_argument/label_argument.h"
#include "../../code_generator/intermediate/instruction_argument/instruction_label.h"

class StatementNode : public Node
{

public:

    StatementNode(const NodeType nodeType);
    virtual ~StatementNode();

    void setNextLabelNumber(const int nextLabelNumber);
    int getNextLabelNumber() const ;

    void setBreakLabelNumber(const int breakLabelNumber);
    int getBreakLabelNumber() const ;

    void setContinueLabelNumber(const int continueLabelNumber);
    int getContinueLabelNumber() const ;

    virtual void typeCheck(SemanticDebugger *semanticDebugger) = 0;

    // NÃO virtuais puros.
    virtual bool checkRepetition(const bool inRepetition, SemanticDebugger * semanticDebugger);
    virtual bool checkReturn(DataType returnType, SemanticDebugger * semanticDebugger);

    virtual void generateCCode(ostream &out) = 0;
    virtual void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector) = 0;

private:
    int nextLabelNumber_;

    int breakLabelNumber_;
    int continueLabelNumber_;
};

#endif
