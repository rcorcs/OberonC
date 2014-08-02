/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 2068 of yacc.c  */
#line 2 "yy_parser.y"


#include "../ast/declaration/declaration_node.h"
#include "../ast/expression/expression_node.h"
#include "../ast/statement/statement_node.h"
#include "../ast/expression/relational_node.h"

#include "../ast/declaration/constant_list_node.h"
#include "../ast/declaration/variable_list_node.h"
#include "../ast/declaration/formal_parameter_list_node.h"
#include "../ast/expression/actual_parameter_list_node.h"

#include "../symbol_table/data_type.h"




/* Line 2068 of yacc.c  */
#line 56 "yy_parser.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_TYPE_IDENTIFIER = 258,
     TOKEN_TYPE_BOOLEAN = 259,
     TOKEN_TYPE_INTEGER = 260,
     TOKEN_TYPE_STRING = 261,
     TOKEN_TYPE_BOOLEAN_LITERAL = 262,
     TOKEN_TYPE_INTEGER_LITERAL = 263,
     TOKEN_TYPE_STRING_LITERAL = 264,
     TOKEN_TYPE_MODULE = 265,
     TOKEN_TYPE_PROCEDURE = 266,
     TOKEN_TYPE_FUNCTION = 267,
     TOKEN_TYPE_CONST = 268,
     TOKEN_TYPE_VAR = 269,
     TOKEN_TYPE_BEGIN = 270,
     TOKEN_TYPE_END = 271,
     TOKEN_TYPE_IF = 272,
     TOKEN_TYPE_THEN = 273,
     TOKEN_TYPE_ELSIF = 274,
     TOKEN_TYPE_ELSE = 275,
     TOKEN_TYPE_WHILE = 276,
     TOKEN_TYPE_REPEAT = 277,
     TOKEN_TYPE_UNTIL = 278,
     TOKEN_TYPE_FOR = 279,
     TOKEN_TYPE_CONTINUE = 280,
     TOKEN_TYPE_BREAK = 281,
     TOKEN_TYPE_RETURN = 282,
     TOKEN_TYPE_DO = 283,
     TOKEN_TYPE_TO = 284,
     TOKEN_TYPE_AND = 285,
     TOKEN_TYPE_OR = 286,
     TOKEN_TYPE_NOT = 287,
     TOKEN_TYPE_WRITE = 288,
     TOKEN_TYPE_WRITELN = 289,
     TOKEN_TYPE_READ = 290,
     TOKEN_TYPE_LESS = 291,
     TOKEN_TYPE_LESS_EQUAL = 292,
     TOKEN_TYPE_EQUAL = 293,
     TOKEN_TYPE_NOT_EQUAL = 294,
     TOKEN_TYPE_GREATER = 295,
     TOKEN_TYPE_GREATER_EQUAL = 296,
     TOKEN_TYPE_COLON = 297,
     TOKEN_TYPE_SEMICOLON = 298,
     TOKEN_TYPE_FULL_STOP = 299,
     TOKEN_TYPE_COMMA = 300,
     TOKEN_TYPE_LEFT_BRACKET = 301,
     TOKEN_TYPE_RIGHT_BRACKET = 302,
     TOKEN_TYPE_ASSIGN = 303,
     TOKEN_TYPE_PLUS = 304,
     TOKEN_TYPE_MINUS = 305,
     TOKEN_TYPE_ASTERISK = 306,
     TOKEN_TYPE_MOD = 307,
     TOKEN_TYPE_SLASH = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 37 "yy_parser.y"

    
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



/* Line 2068 of yacc.c  */
#line 144 "yy_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

