/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef NODE_H
#define NODE_H

#include "../debugger/debugger_interfaces/ast_debugger.h"
#include "../debugger/debugger_interfaces/semantic_debugger.h"

enum NodeType
{
    NODE_TYPE_DECLARATION,
    NODE_TYPE_DECLARATION_SEQUENCE,
    NODE_TYPE_FUNCTION,
    NODE_TYPE_MODULE,
    NODE_TYPE_CONSTANT,
    NODE_TYPE_CONSTANT_LIST,
    NODE_TYPE_FORMAL_PARAMETER,
    NODE_TYPE_FORMAL_PARAMETER_LIST,
    NODE_TYPE_SKIP_DECLARATION,
    NODE_TYPE_VARIABLE,
    NODE_TYPE_VARIABLE_LIST,

    NODE_TYPE_EXPRESSION,
    NODE_TYPE_AND,
    NODE_TYPE_ARITHMETIC,
    NODE_TYPE_BOOLEAN_LITERAL,
    NODE_TYPE_ACTUAL_PARAMETER_LIST,
    NODE_TYPE_FUNCTION_CALL,
    NODE_TYPE_IDENTIFIER,
    NODE_TYPE_INTEGER_LITERAL,
    NODE_TYPE_NEGATION,
    NODE_TYPE_NOT,
    NODE_TYPE_OR,
    NODE_TYPE_RELATIONAL,
    NODE_TYPE_STRING_LITERAL,

    NODE_TYPE_STATEMENT,
    NODE_TYPE_ASSIGNMENT,
    NODE_TYPE_BREAK,
    NODE_TYPE_CONDITIONAL,
    NODE_TYPE_CONTINUE,
    NODE_TYPE_FOR_LOOP,
    NODE_TYPE_POST_TEST_LOOP,
    NODE_TYPE_PRE_TEST_LOOP,
    NODE_TYPE_PROCEDURE_CALL,
    NODE_TYPE_READ,
    NODE_TYPE_RETURN,
    NODE_TYPE_SKIP_STATEMENT,
    NODE_TYPE_STATEMENT_SEQUENCE,
    NODE_TYPE_WRITE,
    NODE_TYPE_WRITE_LINE,
    NODE_TYPE_WRITE_STRING
};

class Node
{

public:

    Node(const NodeType nodeType);
    virtual ~Node();

    NodeType getNodeType() const;

    int getFirstLine() const;
    void setFirstLine(int firstLine);

    virtual void debug(ASTDebugger *astDebugger, int nodeLevel) = 0;

protected:

    void setNodeType(const NodeType nodeType);


private:

    NodeType nodeType_;
    int firstLine_;
};

#endif
