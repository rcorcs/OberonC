%code requires
{

#include "../ast/declaration/declaration_node.h"
#include "../ast/expression/expression_node.h"
#include "../ast/statement/statement_node.h"
#include "../ast/expression/relational_node.h"

#include "../ast/declaration/constant_list_node.h"
#include "../ast/declaration/variable_list_node.h"
#include "../ast/declaration/formal_parameter_list_node.h"
#include "../ast/expression/actual_parameter_list_node.h"

#include "../symbol_table/data_type.h"

}


%{

#include "../global/global.h"
#include <iostream>
using namespace std;

// Analisador léxico que será chamado pelo Parser.
extern int yylex();

// Contagem e saída de erros.
unsigned int parserErrors = 0;
void yyerror(const char *errmsg);

Parser      & parser      = ::oberonc.getParser();
SymbolTable & symbolTable = ::oberonc.getSymbolTable();
 
%}

%union {
    
    bool    bool_value;
    long    int_value;
    char *  str_value;
    char *  identifier;
    
    IdentifierInformation *identifier_info;
    ExpressionNode *expression;
    StatementNode *statement;
    DeclarationNode *declaration;
    
    DataType dataType;
    RelationalOperator relationalOperator;
}
 
%type <declaration> module                   declarations
					constdecl                constdecl_list            constlist       const_addinfo 
                    vardecl                  vardecl_list              varlist         var_addinfo
                    procdecl                 procdecl_list             procheader      procbody
                    formalpars               fpardecl_opt_list         fpardecl_list   fparlist        fpar_addinfo
                    procheader_create_scope  funcheader_create_scope
    
%type <statement>   statements statement assignment conditional elseif_opt_list repetition
                    io_statement proccall
                    
%type <dataType>    datatype

%type <expression>  expression andexp relexp aritexp term factor primary literal actualpar
                    parameters_list parameter io_parameter funccall checkIdentifier

%type <identifier_info> module_create_scope

%type <relationalOperator> rel_op
 
%token

 
    // Identificador.
    <identifier> TOKEN_TYPE_IDENTIFIER

    
    // Tipos de variáveis. 

    TOKEN_TYPE_BOOLEAN
    TOKEN_TYPE_INTEGER
    TOKEN_TYPE_STRING


    // Literais.
    
    <bool_value> TOKEN_TYPE_BOOLEAN_LITERAL
    <int_value>  TOKEN_TYPE_INTEGER_LITERAL
    <str_value>  TOKEN_TYPE_STRING_LITERAL


    // Delimitadores de escopo/bloco.
    
    TOKEN_TYPE_MODULE
    TOKEN_TYPE_PROCEDURE
    TOKEN_TYPE_FUNCTION
	TOKEN_TYPE_CONST
    TOKEN_TYPE_VAR
    TOKEN_TYPE_BEGIN
    TOKEN_TYPE_END

 
    // Condicionais.
    
    TOKEN_TYPE_IF
    TOKEN_TYPE_THEN
    TOKEN_TYPE_ELSIF
    TOKEN_TYPE_ELSE
    
    // Repetições/controle de fluxo.

    TOKEN_TYPE_WHILE
    TOKEN_TYPE_REPEAT
    TOKEN_TYPE_UNTIL
    TOKEN_TYPE_FOR
    TOKEN_TYPE_CONTINUE
    TOKEN_TYPE_BREAK
    TOKEN_TYPE_RETURN
    TOKEN_TYPE_DO
    TOKEN_TYPE_TO


    // Operadores lógicos.

    TOKEN_TYPE_AND
    TOKEN_TYPE_OR
    TOKEN_TYPE_NOT
    
    
    // Funções I/O nativas.
    
    TOKEN_TYPE_WRITE
    TOKEN_TYPE_WRITELN
    TOKEN_TYPE_READ

    
    // Operadores relacionais.
    
    TOKEN_TYPE_LESS
    TOKEN_TYPE_LESS_EQUAL
    TOKEN_TYPE_EQUAL
    TOKEN_TYPE_NOT_EQUAL
    TOKEN_TYPE_GREATER
    TOKEN_TYPE_GREATER_EQUAL

    
    // Símbolos delimitadores
    
    TOKEN_TYPE_COLON
    TOKEN_TYPE_SEMICOLON
    TOKEN_TYPE_FULL_STOP
    TOKEN_TYPE_COMMA
    TOKEN_TYPE_LEFT_BRACKET
    TOKEN_TYPE_RIGHT_BRACKET
    

    // Operadores aritiméticos/atribuição.
    
    TOKEN_TYPE_ASSIGN
    TOKEN_TYPE_PLUS
    TOKEN_TYPE_MINUS
    TOKEN_TYPE_ASTERISK
    TOKEN_TYPE_MOD
    TOKEN_TYPE_SLASH
    
%%




/*
   module ::= "Module" ID ";" declarations "Begin" statements "End" ID "."
*/

module :
    TOKEN_TYPE_MODULE module_create_scope TOKEN_TYPE_SEMICOLON declarations
    TOKEN_TYPE_BEGIN statements TOKEN_TYPE_END module_remove_scope TOKEN_TYPE_FULL_STOP {
    
        ::oberonc.getParserDebugger()->debugReduction("module", "\"Module\" ID \";\" declarations \"Begin\""
                                                                "statements \"End\" ID \".\"", @1.first_line);

        ModuleNode *moduleRoot = new ModuleNode( (ModuleInformation*)$2, $4, $6 );
        
        ::oberonc.setASTRoot(moduleRoot);

} |
    TOKEN_TYPE_MODULE module_create_scope TOKEN_TYPE_SEMICOLON declarations
    TOKEN_TYPE_BEGIN statements TOKEN_TYPE_END module_remove_scope  {
    
        ::oberonc.getParserDebugger()->debugRecoveredError("missing a \".\" at the end of the module.",
                                                                                        @8.first_line);
        
        ModuleNode *moduleRoot = new ModuleNode( (ModuleInformation*)$2, $4, $6 );
        
        ::oberonc.setASTRoot(moduleRoot);
};



/*

    Cria um escopo global, bem como atualiza a tabela de símbolos inserindo as respectivas informações
    sobre o módulo. Cria-se, também, um novo escopo para o respectivo módulo do programa.
*/

module_create_scope :
    TOKEN_TYPE_IDENTIFIER {

        symbolTable.createScope("GLOBAL");

        ModuleInformation *moduleInformation = new ModuleInformation($1);
        symbolTable.insertAtCurrentScope(moduleInformation);
        
        symbolTable.createScope($1);

        $$ = moduleInformation;
};




/*

    Remove escopo referente a um módulo previamente declarado.
    É verificado se o identificador que sucede a palavra chave "end" 
    corresponde a um identificador de fato declarado e, caso, contrário,
    um erro de "identificador não declarado" é exibido.
*/

module_remove_scope : 
    TOKEN_TYPE_IDENTIFIER {

        IdentifierInformation *identifierInfo = symbolTable.lookup($1);
        
        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared($1, @1.first_line);
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_MODULE)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
        }
        
        Scope * moduleScope  = symbolTable.removeScope(); // Remove escopo do Módulo
        Scope * globalScope  = symbolTable.removeScope(); // Remove escopo GLOBAL
        
        moduleScope->debug( ::oberonc.getSymbolTableDebugger() );
        globalScope->debug( ::oberonc.getSymbolTableDebugger() );

        delete moduleScope;
        delete globalScope;
        
        delete [] $1;
};




/*
    declarations ::= constdecl vardecl procdecl_list |
                     constdecl procdecl_list |
                     vardecl procdecl_list |
					 procdecl_list
*/

declarations :
    constdecl vardecl procdecl_list {
    
        ::oberonc.getParserDebugger()->debugReduction("declarations", "constdecl vardecl procdecl_list", @1.first_line);

		DeclarationSequenceNode *varAndConstLists = new DeclarationSequenceNode($1, $2);
		$$ = new DeclarationSequenceNode(varAndConstLists, $3);

		::oberonc.addNodeToCleanUpList(varAndConstLists);
		::oberonc.addNodeToCleanUpList($$);
        
} | constdecl procdecl_list {
        
        ::oberonc.getParserDebugger()->debugReduction("declarations", "constdecl procdecl_list", @1.first_line);
        
        $$ = new DeclarationSequenceNode($1, $2);
		::oberonc.addNodeToCleanUpList($$);
		
} | vardecl procdecl_list {
        
        ::oberonc.getParserDebugger()->debugReduction("declarations", "vardecl procdecl_list", @1.first_line);
        
        $$ = new DeclarationSequenceNode($1, $2);
		::oberonc.addNodeToCleanUpList($$);
		
} | procdecl_list {
        
        ::oberonc.getParserDebugger()->debugReduction("declarations", "procdecl_list", @1.first_line);
        
        $$ = $1;
};



constdecl :
	TOKEN_TYPE_CONST constdecl_list {
	
		::oberonc.getParserDebugger()->debugReduction("constdecl", "\"const\" constdecl_list", @1.first_line);
		
		$$ = $2;
		
};

constdecl_list :
	constdecl_list constlist TOKEN_TYPE_COLON datatype TOKEN_TYPE_SEMICOLON {
		
		::oberonc.getParserDebugger()->debugReduction("constdecl_list", "constdecl_list constlist \":\""
		                                                                "datatype \";\"", @0.first_line);
		
        ConstantListNode *constantList = (ConstantListNode*)$1;
        DeclarationSequenceNode *constantSequence = (DeclarationSequenceNode*)$2;
        
        constantList->addConstantSequence(constantSequence, $4);
        
        $$ = $1;		
		
} | /* epsilon */ {
		
		::oberonc.getParserDebugger()->debugReduction("constdecl_list", "/* */ ", @0.first_line);
		
        $$ = new ConstantListNode();
		::oberonc.addNodeToCleanUpList($$); 
};

constlist :
	constlist TOKEN_TYPE_COMMA const_addinfo TOKEN_TYPE_ASSIGN expression {
		
		::oberonc.getParserDebugger()->debugReduction("constlist", "constlist \",\" ID \":=\" expression", 
		                                                                                   @0.first_line);
		
		((ConstantNode *)$3)->setExpressionValue($5);
		$$ = new DeclarationSequenceNode($3, $1);
		::oberonc.addNodeToCleanUpList($$); 
		
} | const_addinfo TOKEN_TYPE_ASSIGN expression {

 		::oberonc.getParserDebugger()->debugReduction("const_addinfo", "ID \":=\" expression", @1.first_line);
		
		((ConstantNode *)$1)->setExpressionValue($3);
        
		$$ = new DeclarationSequenceNode($1, NULL); 
		::oberonc.addNodeToCleanUpList($$); 
		
};



const_addinfo :
	TOKEN_TYPE_IDENTIFIER {
		
        if(symbolTable.isAtCurrentScope($1))
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared($1, @1.first_line);
        }
      
        ConstantInformation *constantInformation = new ConstantInformation($1);
        symbolTable.insertAtCurrentScope(constantInformation);
        
        $$ = new ConstantNode(constantInformation, NULL); 
        $$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 

        delete [] $1;
		
};

/*
    vardecl ::= "var" vardecl_list
*/

vardecl :
    TOKEN_TYPE_VAR vardecl_list {
    
        ::oberonc.getParserDebugger()->debugReduction("vardecl", "\"var\" vardecl_list", @1.first_line);
        
        $$ = $2;
		
};

  

/*
    vardecl_list ::= vardecl_list varlist ":" datatype ";" | &
*/

vardecl_list :
    vardecl_list varlist TOKEN_TYPE_COLON datatype TOKEN_TYPE_SEMICOLON {

        ::oberonc.getParserDebugger()->debugReduction("vardecl_list", "vardecl_list varlist \":\" datatype \";\"",
                                                                                                  @0.first_line);
        
        VariableListNode *variableList = (VariableListNode*)$1;
        DeclarationSequenceNode *variableSequence = (DeclarationSequenceNode*)$2;
        
        variableList->addVariableSequence(variableSequence, $4);
        
        $$ = $1;
        
} | /* epsilon */ {

        ::oberonc.getParserDebugger()->debugReduction("vardecl_list", "/*  */ ", @0.first_line);
                
        $$ = new VariableListNode();
        ::oberonc.addNodeToCleanUpList($$); 
};




/*
    varlist ::= varlist "," ID | ID
*/

 varlist :
    varlist TOKEN_TYPE_COMMA var_addinfo {
        
        ::oberonc.getParserDebugger()->debugReduction("varlist", "varlist \",\" ID", @3.first_line);

        $$ = new DeclarationSequenceNode($3, $1);
        ::oberonc.addNodeToCleanUpList($$); 
        

} | var_addinfo {

        ::oberonc.getParserDebugger()->debugReduction("varlist", "ID", @1.first_line);

        $$ = new DeclarationSequenceNode($1, NULL);        
};




/*
    Insere informação relativa uma variável declarada na seção "var" do módulo do programa,
    de um procedimento ou de uma função. Uma verificação é feita dentro do escopo corrente
    para detectar se o identificador da variável foi declarado mais de uma vez - um erro
    é exibido neste caso.
*/

var_addinfo :
    TOKEN_TYPE_IDENTIFIER {

        if(symbolTable.isAtCurrentScope($1))
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared($1, @1.first_line);
        }
      
        VariableInformation *variableInformation = new VariableInformation($1);
        symbolTable.insertAtCurrentScope(variableInformation);
        
        IdentifierInformation *identifierInfo = symbolTable.lookup( symbolTable.getCurrentScope()->getName() );
        
        if(identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
           FunctionInformation *functionInformation = (FunctionInformation *)identifierInfo;
           functionInformation->getVariableList().push_back(variableInformation);
        }

        $$ = new VariableNode(variableInformation); 
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 

        delete [] $1;
};




/*
    datatype ::= "Boolean" | "Integer"
*/

datatype :
    TOKEN_TYPE_BOOLEAN {
    
        ::oberonc.getParserDebugger()->debugReduction("datatype", "\"Boolean\"", @1.first_line);
        
        $$ = DATA_TYPE_BOOLEAN;
        
} | TOKEN_TYPE_INTEGER {

        ::oberonc.getParserDebugger()->debugReduction("datatype", "\"Integer\"", @1.first_line);
        
        $$ = DATA_TYPE_INTEGER;
};




/*
    procdecl_list ::= procdecl_list procdecl | &
*/

procdecl_list :
    procdecl_list procdecl {
    
        ::oberonc.getParserDebugger()->debugReduction("procdecl_list", "procdecl_list procdecl", @0.first_line);
        
        $$ = new DeclarationSequenceNode($1, $2);
        ::oberonc.addNodeToCleanUpList($$); 
    
} | /* epsilon */ {

        ::oberonc.getParserDebugger()->debugReduction("procdecl_list", "/*  */ ", @0.first_line);
        
        $$ = new SkipDeclarationNode();
        ::oberonc.addNodeToCleanUpList($$); 
};





/*
    procdecl ::= procheader procbody
*/

procdecl :
    procheader procbody {
    
        ::oberonc.getParserDebugger()->debugReduction("procdecl", "procheader procbody", @1.first_line);

        
        FunctionNode * functionNode1 = (FunctionNode*)$1;
        FunctionNode * functionNode2 = (FunctionNode*)$2;
        
        DeclarationSequenceNode * declarationSequence = new DeclarationSequenceNode( 
                                                                     functionNode1->getDeclarations(),
                                                                     functionNode2->getDeclarations() 
                                                                   ); 

        functionNode1->setDeclarations(declarationSequence);
        functionNode1->setStatements( functionNode2->getStatements() );

        ::oberonc.addNodeToCleanUpList(declarationSequence); 
        
        $$ = functionNode1;
};




/*
    procheader ::= "Procedure" ID formalpars ";" |
                   "Function" ID formalpars ":" datatype ";"
*/

procheader :
    TOKEN_TYPE_PROCEDURE procheader_create_scope formalpars TOKEN_TYPE_SEMICOLON {
    
        ::oberonc.getParserDebugger()->debugReduction("procheader", "\"Procedure\" ID formalpars \";\"",  
                                                                                         @1.first_line);
        
        FunctionNode *functionNode = (FunctionNode *)$2;
        
        functionNode->setReturnType(DATA_TYPE_VOID);
        functionNode->setDeclarations($3);
        functionNode->setStatements(NULL);
        
        $$ = functionNode;

} | TOKEN_TYPE_FUNCTION funcheader_create_scope formalpars TOKEN_TYPE_COLON datatype TOKEN_TYPE_SEMICOLON {

        ::oberonc.getParserDebugger()->debugReduction("procheader", "\"Function\" ID formalpars \":\""
                                                                      "datatype \";\"", @1.first_line);
        
        FunctionNode *functionNode = (FunctionNode *)$2;
        
        functionNode->setReturnType($5);
        functionNode->setDeclarations($3);
        functionNode->setStatements(NULL);
        
        $$ = functionNode;
        
} | TOKEN_TYPE_PROCEDURE procheader_create_scope formalpars {
    
        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" at the end of the procedure's header.",
                                                                                                    @3.first_line);
        
        FunctionNode *functionNode = (FunctionNode *)$2;
        
        functionNode->setReturnType(DATA_TYPE_VOID);
        functionNode->setDeclarations($3);
        functionNode->setStatements(NULL);
        
        $$ = functionNode;
        
} | TOKEN_TYPE_FUNCTION funcheader_create_scope formalpars TOKEN_TYPE_COLON datatype {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" at the end of the function's header.",
                                                                                                   @5.first_line);
        
        FunctionNode *functionNode = (FunctionNode *)$2;
        
        functionNode->setReturnType($5);
        functionNode->setDeclarations($3);
        functionNode->setStatements(NULL);
        
        $$ = functionNode;
        
} | TOKEN_TYPE_FUNCTION funcheader_create_scope formalpars TOKEN_TYPE_SEMICOLON {

        ::oberonc.getParserDebugger()->debugRecoveredError("Function without a return type.", @4.first_line);
        
        FunctionNode *functionNode = (FunctionNode *)$2;
        
        functionNode->setReturnType(DATA_TYPE_VOID);
        functionNode->setDeclarations($3);
        functionNode->setStatements(NULL);
        
        $$ = functionNode;
        
};




/*
    Cria um novo escopo referente a um procedimento.
    
    É verificado se o nome (identificador) do procedimento já foi declarado anteriormente e,
    caso afirmativo, um erro de "identificador redeclarado" é exibido. 
    
    A declaração de um procedimento implica na inserção de informações sobre tal procedimento
    no escopo do módulo do programa e também na criação de um novo escopo para este procedimento.
*/

procheader_create_scope :
    TOKEN_TYPE_IDENTIFIER {

        IdentifierInformation *identifierInfo = symbolTable.lookup($1);

        if(identifierInfo)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared($1, @1.first_line);
        }
       
       FunctionInformation *functionInformation = new FunctionInformation($1);
       symbolTable.insertAtCurrentScope(functionInformation);

       symbolTable.createScope($1);
       
       $$ = new FunctionNode(functionInformation, NULL, NULL);
	   $$->setFirstLine(@1.first_line);
		
       ::oberonc.addNodeToCleanUpList($$);
       
       delete [] $1;
};



/*
Cria um novo escopo referente a uma função.
É verificado se o nome (identificador) do função já foi declarado anteriormente e,
caso afirmativo, um erro de "identificador redeclarado" é exibido. 
A declaração de um função implica na inserção de informações sobre tal função
no escopo do módulo do programa e também na criação de um novo escopo para esta função.
*/

funcheader_create_scope :
    TOKEN_TYPE_IDENTIFIER {

        IdentifierInformation *identifierInfo = symbolTable.lookup($1);
    
        if(identifierInfo)
        {
           ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared($1, @1.first_line);
        }
        
        FunctionInformation *functionInformation = new FunctionInformation($1);
        symbolTable.insertAtCurrentScope(functionInformation);

        symbolTable.createScope($1);
        
        $$ = new FunctionNode(functionInformation, NULL, NULL);
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$);
        
        delete [] $1;
};




/*
    procbody ::= vardecl "Begin" statements "End" ID ";" |
                         "Begin" statements "End" ID ";"
*/

procbody :
    vardecl TOKEN_TYPE_BEGIN statements TOKEN_TYPE_END procbody_remove_scope TOKEN_TYPE_SEMICOLON {

         ::oberonc.getParserDebugger()->debugReduction("procbody", "vardecl \"begin\" statements \"end\" ID \";\"",
                                                                                                     @1.first_line);
        
        $$ = new FunctionNode( NULL, $1, $3 );
		$$->setFirstLine(@1.first_line);
		
         ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_BEGIN statements TOKEN_TYPE_END procbody_remove_scope TOKEN_TYPE_SEMICOLON {

        ::oberonc.getParserDebugger()->debugReduction("procbody", "\"begin\" statements \"end\" ID \";\"",
                                                                                            @1.first_line);
        
        SkipDeclarationNode * skipDeclaration = new SkipDeclarationNode();
        $$ = new FunctionNode( NULL, skipDeclaration, $2 ); 
        $$->setFirstLine(@1.first_line);
		
         ::oberonc.addNodeToCleanUpList(skipDeclaration); 
         ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_BEGIN statements TOKEN_TYPE_END procbody_remove_scope {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" after \"end\".", @4.first_line);
        
        SkipDeclarationNode * skipDeclaration = new SkipDeclarationNode();
        $$ = new FunctionNode( NULL, skipDeclaration, $2 );
        $$->setFirstLine(@1.first_line);
		
         ::oberonc.addNodeToCleanUpList(skipDeclaration); 
         ::oberonc.addNodeToCleanUpList($$); 
};



/*
Remove escopo referente a um procedimento/função previamente declarado.
É verificado se o identificador que sucede a palavra chave "end" 
corresponde a um identificador de fato declarado e, caso, contrário,
um erro de "identificador não declarado" é exibido.
*/

procbody_remove_scope :
    TOKEN_TYPE_IDENTIFIER {
       
        IdentifierInformation *identifierInfo = symbolTable.lookup($1);
        Scope *scope = symbolTable.removeScope();
        
        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared($1, @1.first_line);
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
        }
        else
        {
            bool equal = true;
            const char *str1 = scope->getName();
            const char *str2 = $1;

            while(*str1 && equal)
            {
                equal = ( tolower(*str1++) == tolower(*str2++) );
            }
            
            if(!equal)
            {
                ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
            }
        }
                
        scope->debug( ::oberonc.getSymbolTableDebugger() );
        
        delete scope;
        delete [] $1;
};




/*
   formalpars ::= "(" fpardecl_opt_list ")"
*/

formalpars :
    TOKEN_TYPE_LEFT_BRACKET fpardecl_opt_list TOKEN_TYPE_RIGHT_BRACKET {
    
        ::oberonc.getParserDebugger()->debugReduction("formalpars", "\"(\" fpardecl_opt_list \")\"",
                                                                                  @1.first_line);
        
        $$ = $2;
};

/*
    fpardecl_opt_list ::= fpardecl_list | &
*/
fpardecl_opt_list :
    fpardecl_list {
    
        ::oberonc.getParserDebugger()->debugReduction("fpardecl_opt_list", "fpardecl_list", @1.first_line);
        
        $$ = $1;
        
} | /*epsilon*/ {

        ::oberonc.getParserDebugger()->debugReduction("fpardecl_opt_list", "/* */", @0.first_line);
        
        $$ = new FormalParameterListNode();
         ::oberonc.addNodeToCleanUpList($$); 
};



/*
    fpardecl_list ::= fpardecl_list ";" fparlist ":" datatype | fparlist ":" datatype
*/

fpardecl_list :
    fpardecl_list TOKEN_TYPE_SEMICOLON fparlist TOKEN_TYPE_COLON datatype{

        ::oberonc.getParserDebugger()->debugReduction("fpardecl_list", "fpardecl_list \";\""
                                                       "fparlist \":\" datatype", @0.first_line);
        
        
        FormalParameterListNode *formalParameterList = (FormalParameterListNode*)$1;
        DeclarationSequenceNode *formalParameterSequence = (DeclarationSequenceNode*)$3;
    
        formalParameterList->addFormalParameterSequence(formalParameterSequence, $5);
        
        $$ = $1;    
        
} | fparlist TOKEN_TYPE_COLON datatype {


        FormalParameterListNode *formalParameterList = new FormalParameterListNode();
        DeclarationSequenceNode *formalParameterSequence = (DeclarationSequenceNode*)$1;
        
        formalParameterList->addFormalParameterSequence(formalParameterSequence, $3);
        
        $$ = formalParameterList;
          ::oberonc.addNodeToCleanUpList($$);         
};



/*
   fparlist ::= fparlist "," ID | ID
*/

fparlist :
    fparlist TOKEN_TYPE_COMMA fpar_addinfo {

        ::oberonc.getParserDebugger()->debugReduction("fparlist", "fparlist \",\" ID", @1.first_line);
        
        $$ = new DeclarationSequenceNode($3, $1);
        ::oberonc.addNodeToCleanUpList($$); 
        
} | fpar_addinfo {

        ::oberonc.getParserDebugger()->debugReduction("fparlist", "ID", @1.first_line);

        $$ = new DeclarationSequenceNode($1, NULL);
        ::oberonc.addNodeToCleanUpList($$); 
} ;





/*
Insere informação relativa um parâmetro formal de um procedimento ou de uma função.
Uma verificação é feita dentro do escopo corrente para detectar se o identificador
do parâmetro formal foi declarado mais de uma vez - um erro é exibido neste caso.
*/

fpar_addinfo :
    TOKEN_TYPE_IDENTIFIER {

        if(symbolTable.isAtCurrentScope($1))
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared($1, @1.first_line);
        }
       
        FormalParameterInformation *formalParameterInformation = new FormalParameterInformation($1);
        symbolTable.insertAtCurrentScope(formalParameterInformation);

        IdentifierInformation *identifierInfo = symbolTable.lookup( symbolTable.getCurrentScope()->getName() );
        
        if(identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
           FunctionInformation *functionInformation = (FunctionInformation *)identifierInfo;
           functionInformation->getFormalParameterList().push_back(formalParameterInformation);
        }
       
        $$ = new FormalParameterNode( formalParameterInformation );
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 

        delete [] $1;
};


/*
    statements ::= statements statement ";" | &
*/

statements :
    statements statement TOKEN_TYPE_SEMICOLON {
    
        ::oberonc.getParserDebugger()->debugReduction("statements", "statements statement \";\"", @0.first_line);
        
        $$ = new StatementSequenceNode( $1, $2 );
		::oberonc.addNodeToCleanUpList($$); 
        
} | /* epsilon */ {

        ::oberonc.getParserDebugger()->debugReduction("statements", "/*  */", @0.first_line);
        
        $$ = new SkipStatementNode();
        ::oberonc.addNodeToCleanUpList($$); 

} | statements statement {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" after statement.", @2.first_line);

        $$ = new StatementSequenceNode( $1, $2 );
        ::oberonc.addNodeToCleanUpList($$); 

};





/*
    expression ::= expression "or" andexp | andexp
*/

expression :
     expression TOKEN_TYPE_OR andexp {
     
        ::oberonc.getParserDebugger()->debugReduction("expression", "expression \"or\" andexp", @1.first_line);
        
        $$ = new OrNode( $1, $3 );
        $$->setFirstLine(@1.first_line);
		
         ::oberonc.addNodeToCleanUpList($$); 
        
} | andexp {

        ::oberonc.getParserDebugger()->debugReduction("expression", "andexp", @1.first_line);
        
        $$ = $1;
};




/*
   andexp ::= andexp "and" relexp | relexp
*/

andexp :
    andexp TOKEN_TYPE_AND relexp {
    
        ::oberonc.getParserDebugger()->debugReduction("andexp", "andexp \"and\" relexp", @1.first_line);
        
        $$ = new AndNode( $1, $3 );
        $$->setFirstLine(@1.first_line);

         ::oberonc.addNodeToCleanUpList($$); 
        
} | relexp {

        ::oberonc.getParserDebugger()->debugReduction("andexp", "relexp", @1.first_line);
        
        $$ = $1;
};



/*
   relexp ::= aritexp REL_OP aritexp | aritexp
*/

relexp :
    aritexp rel_op aritexp {
    
        ::oberonc.getParserDebugger()->debugReduction("relexp", "aritexp rel_op aritexp", @1.first_line);
        
        $$ = new RelationalNode($1, $2, $3);
        $$->setFirstLine(@1.first_line);

		::oberonc.addNodeToCleanUpList($$); 
        
} | aritexp {

        ::oberonc.getParserDebugger()->debugReduction("relexp", "aritexp", @1.first_line);
        
        $$ = $1;
};




/*
   rel_op ::= ">" | "<" | ">=" | "<=" | "=" | "#"
*/

rel_op : 
    TOKEN_TYPE_GREATER {
    
        ::oberonc.getParserDebugger()->debugReduction("rel_op", ">", @1.first_line);
        
        $$ = RELATIONAL_OPERATOR_GREATER;
        
} | TOKEN_TYPE_LESS {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "<", @1.first_line);
        
        $$ = RELATIONAL_OPERATOR_LESS;
        
} | TOKEN_TYPE_GREATER_EQUAL {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", ">=", @1.first_line);
        
        $$ = RELATIONAL_OPERATOR_GREATER_OR_EQUAL;
        
} | TOKEN_TYPE_LESS_EQUAL {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "<=", @1.first_line);
        
        $$ = RELATIONAL_OPERATOR_LESS_OR_EQUAL;
        
} | TOKEN_TYPE_EQUAL {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "=", @1.first_line);
        
        $$ = RELATIONAL_OPERATOR_EQUAL;
        
} | TOKEN_TYPE_NOT_EQUAL {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "#", @1.first_line);
        
        $$ = RELATIONAL_OPERATOR_DIFFERENT;
        
};




/*
 aritexp ::= aritexp ADD_OP term | term
 ADD_OP  ::= "+" | "-"
*/

aritexp : 
    aritexp TOKEN_TYPE_PLUS term {
    
        ::oberonc.getParserDebugger()->debugReduction("aritexp", "aritexp + term", @1.first_line);
        
        $$ = new ArithmeticNode($1, ARITHMETIC_OPERATOR_ADD, $3);
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
    
} | aritexp TOKEN_TYPE_MINUS term {

        ::oberonc.getParserDebugger()->debugReduction("aritexp", "aritexp - term", @1.first_line);
        
        $$ = new ArithmeticNode($1, ARITHMETIC_OPERATOR_SUB, $3);
        $$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
} | term {

        ::oberonc.getParserDebugger()->debugReduction("aritexp", "term", @1.first_line);
        
        $$ = $1;
};




/*
   term ::= term MULT_OP factor | factor
   MULT_OP ::= "*" | "mod" | "/"
*/

term :
    term TOKEN_TYPE_ASTERISK factor {
    
        ::oberonc.getParserDebugger()->debugReduction("term", "term * factor", @1.first_line);
        
        $$ = new ArithmeticNode($1, ARITHMETIC_OPERATOR_MULT, $3);
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | term TOKEN_TYPE_SLASH factor {

        ::oberonc.getParserDebugger()->debugReduction("term", "term / factor", @1.first_line);
        
        $$ = new ArithmeticNode($1, ARITHMETIC_OPERATOR_DIV, $3);
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | term TOKEN_TYPE_MOD factor {

        ::oberonc.getParserDebugger()->debugReduction("term", "term \"mod\" factor", @1.first_line);
        
        $$ = new ArithmeticNode($1, ARITHMETIC_OPERATOR_MOD, $3);
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | factor {

        ::oberonc.getParserDebugger()->debugReduction("term", "factor", @1.first_line);
        
        $$ = $1;
};




/*
    factor   ::= UNARY_OP primary
    UNARY_OP ::= "+" | "-" | "not" | &
*/

factor :
    TOKEN_TYPE_PLUS primary {
    
        ::oberonc.getParserDebugger()->debugReduction("factor", "\"+\" primary", @1.first_line);
        
        $$ = $2;
        
} | TOKEN_TYPE_MINUS primary {
    
        ::oberonc.getParserDebugger()->debugReduction("factor", "\"-\" primary", @1.first_line);
        
        $$ = new NegationNode( $2 );
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_NOT primary {

        ::oberonc.getParserDebugger()->debugReduction("factor", "\"not\" primary", @1.first_line);
        
        $$ = new NotNode( $2 );
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | primary {

        ::oberonc.getParserDebugger()->debugReduction("factor", "primary", @1.first_line);
        
        $$ = $1;
};




/*

   primary ::= "(" expression ")"
                | proccall
                | literal
                | ID

*/

primary :
    TOKEN_TYPE_LEFT_BRACKET expression TOKEN_TYPE_RIGHT_BRACKET {
    
        ::oberonc.getParserDebugger()->debugReduction("primary", "\"(\" expression \")\"", @1.first_line);
        
        $$ = $2;
        
} | funccall {

        ::oberonc.getParserDebugger()->debugReduction("primary", "proccall", @1.first_line);
        
        $$ = $1;
        
} | literal {

        ::oberonc.getParserDebugger()->debugReduction("primary", "literal", @1.first_line);
        
        $$ = $1;
        
} | checkIdentifier {

        ::oberonc.getParserDebugger()->debugReduction("primary", "ID", @1.first_line);
        
        $$ = $1;
        
} | TOKEN_TYPE_LEFT_BRACKET expression {

        ::oberonc.getParserDebugger()->debugRecoveredError("Unbalanced brackets.", @2.first_line);
        
        $$ = $2;
};




/*
    Verifica se um identificador utilizado em uma expressão e/ou chamada de procedimento/função
    foi declarado e corresponde a um tipo válido de identificador. Erros semânticos são
    exibidos para cada caso contrário.
*/

checkIdentifier:
    TOKEN_TYPE_IDENTIFIER {

        IdentifierInformation *identifierInfo = symbolTable.lookup($1);
        
        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared($1, @1.first_line);
			$$ = NULL;
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_CONSTANT &&
	         	identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_VARIABLE &&
                identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
			$$ = NULL;
        }
		else
		{
            $$ = new IdentifierNode(identifierInfo);
            $$->setFirstLine(@1.first_line);
            ::oberonc.addNodeToCleanUpList($$); 
		}
        
        delete [] $1;
};





/*
   literal ::= BOOLEAN_LITERAL | INTEGER_LITERAL
*/

literal :
    TOKEN_TYPE_BOOLEAN_LITERAL {
    
        ::oberonc.getParserDebugger()->debugReduction("literal", "BOOLEAN_LITERAL", @1.first_line);
        
        $$ = new BooleanLiteralNode($1);
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_INTEGER_LITERAL {

        ::oberonc.getParserDebugger()->debugReduction("literal", "INTEGER_LITERAL", @1.first_line);
        
        $$ = new IntegerLiteralNode($1);
        $$->setFirstLine(@1.first_line);

		::oberonc.addNodeToCleanUpList($$); 
        
};




/*
   proccall ::= ID actualpar
*/

funccall : 
    TOKEN_TYPE_IDENTIFIER actualpar {

        ::oberonc.getParserDebugger()->debugReduction("funccall", "ID actualpar", @1.first_line);
    
        IdentifierInformation *identifierInfo = symbolTable.lookup($1);

        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared($1, @1.first_line);
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
            identifierInfo = (IdentifierInformation*)0;
        }
        
        
        $$ = new FunctionCallNode( (FunctionInformation*)identifierInfo, (ActualParameterListNode*)$2 );
        $$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
        delete [] $1;
};

proccall : 
    TOKEN_TYPE_IDENTIFIER actualpar {

        ::oberonc.getParserDebugger()->debugReduction("proccall", "ID actualpar", @1.first_line);

        IdentifierInformation *identifierInfo = symbolTable.lookup($1);

        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared($1, @1.first_line);
        }
        else
        {
            if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FUNCTION)
           {
              ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
              identifierInfo = (IdentifierInformation*)0;
           }
           else
           {
              /* *****************************************************************************
               * if you want avoid calling a function as if it was a procedure,
               * uncomment the following lines.
               ***************************************************************************** */

               // FunctionInformation * functionInfo = (FunctionInformation*)identifierInfo;
              
               // if(functionInfo->getReturnType () != DATA_TYPE_VOID)
               // {
                 // ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier($1, @1.first_line);
               // }
           }
        }
    
        
        $$ = new ProcedureCallNode( (FunctionInformation*)identifierInfo, (ActualParameterListNode*)$2 );
		$$->setFirstLine(@1.first_line);
        ::oberonc.addNodeToCleanUpList($$); 

        delete [] $1;
};




/*
    actualpar ::= "(" parameters_list ")" | "(" ")"
*/
actualpar :
    TOKEN_TYPE_LEFT_BRACKET parameters_list TOKEN_TYPE_RIGHT_BRACKET {

        ::oberonc.getParserDebugger()->debugReduction("actualpar", "\"(\" parameters_list \")\"", @1.first_line);
        
        $$ = $2;
        
} | TOKEN_TYPE_LEFT_BRACKET TOKEN_TYPE_RIGHT_BRACKET {

        ::oberonc.getParserDebugger()->debugReduction("actualpar", "\"(\" \")\"", @1.first_line);
        
        $$ = new ActualParameterListNode();
        ::oberonc.addNodeToCleanUpList($$); 
};




/*
    parameters_list ::= parameters_list "," expression | expression
*/

parameters_list :
    parameters_list TOKEN_TYPE_COMMA parameter {
    
        ::oberonc.getParserDebugger()->debugReduction("parameters_list", "parameters_list \",\" parameter", 
                                                                                            @0.first_line);
        
        $$ = $1;
        ActualParameterListNode *actualParameterList = (ActualParameterListNode *)$1;
        actualParameterList->addActualParameter($3);
        
} | parameter {

        ::oberonc.getParserDebugger()->debugReduction("parameters_list", "parameter", @1.first_line);
        
        ActualParameterListNode *actualParameterList = new ActualParameterListNode();
        actualParameterList->addActualParameter($1);

        $$ = actualParameterList;
        ::oberonc.addNodeToCleanUpList($$); 

};




/*
    parameter ::= expression
*/

parameter :
    expression {
    
        ::oberonc.getParserDebugger()->debugReduction("parameter", "expression", @1.first_line);
        
        $$ = $1;
};




/*
    statement ::=    assignment
                   | conditional
                   | repetition
                   | proccall
                   | io_statement
                   | "continue"
                   | "break"
                   | "return" expression
*/

statement : 
    assignment {

    ::oberonc.getParserDebugger()->debugReduction("statement", "assignment", @1.first_line);
        
        $$ = $1;
        
} | conditional {

        ::oberonc.getParserDebugger()->debugReduction("statement", "conditional", @1.first_line);
        
        $$ = $1;
        
} | repetition {

        ::oberonc.getParserDebugger()->debugReduction("statement", "repetition", @1.first_line);
        
        $$ = $1;
        
} | proccall {

        ::oberonc.getParserDebugger()->debugReduction("statement", "proccall", @1.first_line);
        
        $$ = $1;
        
} | io_statement {

        ::oberonc.getParserDebugger()->debugReduction("statement", "io_statement", @1.first_line);
        
        $$ = $1;
        
} | TOKEN_TYPE_CONTINUE {

        ::oberonc.getParserDebugger()->debugReduction("statement", "\"continue\"", @1.first_line);
        
        $$ = new ContinueNode();
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_BREAK {

        ::oberonc.getParserDebugger()->debugReduction("statement", "\"break\"", @1.first_line);
        
        $$ = new BreakNode();
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_RETURN expression {

        ::oberonc.getParserDebugger()->debugReduction("statement", "\"return\" expression", @1.first_line);
        
        $$ = new ReturnNode( $2 );
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
};




/*
    assignment ::= ID ":=" expression
*/

assignment :
    checkIdentifier TOKEN_TYPE_ASSIGN expression {
    
        ::oberonc.getParserDebugger()->debugReduction("assignment", "ID \":=\" expression", @1.first_line);
        
		IdentifierNode* identifierNode = (IdentifierNode*)$1;
		
		if(identifierNode != NULL && identifierNode->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
		{
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier(identifierNode->getIdentifier(),
                                                                        		 	            @1.first_line);
        }
  
        $$ = new AssignmentNode( identifierNode, $3 );
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
};




/*
    conditional ::= "if" expression "then" statements elseif_opt_list "end"
*/

conditional :
    TOKEN_TYPE_IF expression TOKEN_TYPE_THEN statements elseif_opt_list TOKEN_TYPE_END {

         ::oberonc.getParserDebugger()->debugReduction("conditional", "\"If\" expression \"Then\" statements"
                                                       "elseif_opt_list else_opt \"end\"", @1.first_line);
        
        $$ = new ConditionalNode($2, $4, $5);
		$$->setFirstLine(@1.first_line);
		
         ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_IF expression statements elseif_opt_list TOKEN_TYPE_END {
    
        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"then\" after the \"if\" condition.", 
                                                                                             @2.first_line);
        
        $$ = new ConditionalNode($2, $3, $4);
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
};

elseif_opt_list :
    TOKEN_TYPE_ELSIF expression TOKEN_TYPE_THEN statements elseif_opt_list {
    
        ::oberonc.getParserDebugger()->debugReduction("elseif_opt_list", "elseif_opt_list \"elsif\" expression"
                                                                         "\"then\" statements", @1.first_line);
        
        $$ = new ConditionalNode($2, $4, $5);
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_ELSE statements {

        ::oberonc.getParserDebugger()->debugReduction("elseif_opt_list", "\"else\" statements", @1.first_line);
        
        $$ = $2;
        
} | /* epsilon */ {

        ::oberonc.getParserDebugger()->debugReduction("elseif_opt_list", "/*  */", @0.first_line);
        
        $$ = new SkipStatementNode();
        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_ELSIF expression statements elseif_opt_list {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"then\" after the \"elsif\" condition.", 
                                                                                                @2.first_line);
        
        $$ = new ConditionalNode($2, $3, $4);
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
};




/*
    repetition ::= "While" expression "Do" statement "End" |
                   "Repeat" statements "Until" expression  |
                   "For" ID "=" expression "To" expression "Do" statement "end"
*/

repetition :
    TOKEN_TYPE_WHILE expression TOKEN_TYPE_DO statements TOKEN_TYPE_END {
        
        ::oberonc.getParserDebugger()->debugReduction("repetition", "\"While\" expression \"Do\" statements"
                                                                                  "\"End\"", @1.first_line);
		
		PreTestLoopNode * preTestLoopNode = new PreTestLoopNode($2, $4);
		//RepetitionNode * repetitionNode = new RepetitionNode($4, $2);
		//SkipStatementNode * skipStatement = new SkipStatementNode();
		//SkipStatementNode * sequenceSkipStatement = new SkipStatementNode();
		//StatementSequenceNode *statementSequenceNode = new StatementSequenceNode(sequenceSkipStatement, repetitionNode);
        
        
        //$$ = new ConditionalNode($2, statementSequenceNode, skipStatement);
		$$ = preTestLoopNode;
        $$->setFirstLine(@1.first_line);
		
        //::oberonc.addNodeToCleanUpList(repetitionNode); 
		//::oberonc.addNodeToCleanUpList(statementSequenceNode); 
		//::oberonc.addNodeToCleanUpList(sequenceSkipStatement); 
        //::oberonc.addNodeToCleanUpList(skipStatement); 
        ::oberonc.addNodeToCleanUpList($$); 

} | TOKEN_TYPE_REPEAT statements TOKEN_TYPE_UNTIL expression {

        ::oberonc.getParserDebugger()->debugReduction("repetition", "\"Repeat\" statements \"Until\" expression",
                                                                                                   @1.first_line);
        
        NotNode *notNode = new NotNode($4);
		notNode->setFirstLine(@1.first_line);

        $$ = new PostTestLoopNode($2, notNode);
		$$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList(notNode); 
        ::oberonc.addNodeToCleanUpList($$); 


} | TOKEN_TYPE_FOR assignment TOKEN_TYPE_TO expression TOKEN_TYPE_DO statements TOKEN_TYPE_END {
        
        ::oberonc.getParserDebugger()->debugReduction("repetition", "\"For\" ID \"=\" expression \"To\""
                                                      "expression \"Do\" statements \"end\"", @1.first_line);
		
        AssignmentNode *initialAssignment = (AssignmentNode*)$2;
        IdentifierNode *loopIdentifier =  initialAssignment->getIdentifier();
        RelationalNode *guard = new RelationalNode( loopIdentifier, RELATIONAL_OPERATOR_LESS_OR_EQUAL, $4 );
    
        IntegerLiteralNode *offsetInc = new IntegerLiteralNode(1);
        ArithmeticNode *identifierIncrement = new ArithmeticNode( loopIdentifier, ARITHMETIC_OPERATOR_ADD, offsetInc );
        AssignmentNode *step = new AssignmentNode(loopIdentifier, identifierIncrement);
      
        ///StatementSequenceNode * repetitionStatements = new StatementSequenceNode($6, step);
        
		//RepetitionNode *repetition = new RepetitionNode(repetitionStatements, guard);
       
        //SkipStatementNode * skipStatement = new SkipStatementNode();
        //ConditionalNode *loop = new ConditionalNode( guard, repetition, skipStatement );
		///PreTestLoopNode *loop = new PreTestLoopNode(guard, repetitionStatements);
        ///$$ = new StatementSequenceNode( initialAssignment, loop );
		$$ = new ForLoopNode(initialAssignment, guard, step, $6);
		
		guard->setFirstLine(@4.first_line);
		$$->setFirstLine(@1.first_line);
		
		
        ::oberonc.addNodeToCleanUpList(guard); 
        ::oberonc.addNodeToCleanUpList(offsetInc); 
        ::oberonc.addNodeToCleanUpList(identifierIncrement); 
        ::oberonc.addNodeToCleanUpList(step); 
        ::oberonc.addNodeToCleanUpList($$);
		//::oberonc.addNodeToCleanUpList(repetitionStatements); 
        //::oberonc.addNodeToCleanUpList(repetition); 
        //::oberonc.addNodeToCleanUpList(skipStatement); 
        //::oberonc.addNodeToCleanUpList(loop); 

} | TOKEN_TYPE_WHILE expression statements TOKEN_TYPE_END {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"Do\" after the \"While\" condition.",
                                                                                                  @2.first_line);

} | TOKEN_TYPE_FOR assignment expression TOKEN_TYPE_DO statements TOKEN_TYPE_END {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"To\" in the \"For\" statement.",
                                                                                         @2.first_line);

} | TOKEN_TYPE_FOR assignment TOKEN_TYPE_TO expression statements TOKEN_TYPE_END {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"Do\" in the \"For\" statement.",
                                                                                         @4.first_line);

};



/*
    io_statement ::= "Write" "(" io_parameter ")" | 
                     "WriteLn" |
                     "WriteLn" "(" io_parameter ")" |
                     "Read" "(" ID ")"
*/

io_statement:
    TOKEN_TYPE_WRITE TOKEN_TYPE_LEFT_BRACKET io_parameter TOKEN_TYPE_RIGHT_BRACKET {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"Write\" \"(\" io_parameter \")\"", 
                                                                                            @1.first_line);

		$$ = new WriteNode($3);;
		$$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_WRITELN {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"WriteLn\"", @1.first_line);
        
        $$ = new WriteLineNode();
		$$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_WRITELN TOKEN_TYPE_LEFT_BRACKET TOKEN_TYPE_RIGHT_BRACKET {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"WriteLn\" \"(\" \")\"", 
                                                                                 @1.first_line);
        
        $$ = new WriteLineNode();
		$$->setFirstLine(@1.first_line);
		
        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_WRITELN TOKEN_TYPE_LEFT_BRACKET io_parameter TOKEN_TYPE_RIGHT_BRACKET {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"WriteLn\" \"(\" io_parameter \")\"",
                                                                                              @1.first_line);
        
        WriteNode * writeNode = new WriteNode($3);
        WriteLineNode * writeLineNode = new WriteLineNode();

		writeNode->setFirstLine(@1.first_line);
		writeLineNode->setFirstLine(@1.first_line);

        $$ = new StatementSequenceNode( writeNode, writeLineNode );
		$$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList(writeNode); 
        ::oberonc.addNodeToCleanUpList(writeLineNode); 
        ::oberonc.addNodeToCleanUpList($$); 
        
} | TOKEN_TYPE_READ TOKEN_TYPE_LEFT_BRACKET checkIdentifier TOKEN_TYPE_RIGHT_BRACKET {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"Read\" \"(\" ID \")\"", @1.first_line);
        
		$$ = new ReadNode( (IdentifierNode*)$3 );
		$$->setFirstLine(@1.first_line);

        ::oberonc.addNodeToCleanUpList($$); 
}




/*

    io_parameter ::= parameter | STRING_LITERAL

*/

io_parameter : 
    parameter {
    
        ::oberonc.getParserDebugger()->debugReduction("io_parameter", "parameter", @1.first_line);
        
        $$ = $1;
        
} | TOKEN_TYPE_STRING_LITERAL {

        ::oberonc.getParserDebugger()->debugReduction("io_parameter", "STRING_LITERAL", @1.first_line);
        
        $$ = new StringLiteralNode($1);
		$$->setFirstLine(@1.first_line);
		
		symbolTable.getStringList()->push_back((string)$1);
		
        ::oberonc.addNodeToCleanUpList($$); 
		
        
        delete [] $1;
};


%%




void yyerror(const char *errmsg)
{
    // Exibe erro.
    printf("\n%s", errmsg);

    // Incrementa número de erros.
    parserErrors++;
}
