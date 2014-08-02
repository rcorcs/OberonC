/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 19 "yy_parser.y"


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
 


/* Line 268 of yacc.c  */
#line 90 "yy_parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 288 of yacc.c  */
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




/* Line 288 of yacc.c  */
#line 132 "yy_parser.cpp"

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

/* Line 293 of yacc.c  */
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



/* Line 293 of yacc.c  */
#line 220 "yy_parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 245 "yy_parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   382

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNRULES -- Number of states.  */
#define YYNSTATES  216

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    13,    22,    24,    26,    30,    33,    36,
      38,    41,    47,    48,    54,    58,    60,    63,    69,    70,
      74,    76,    78,    80,    82,    85,    86,    89,    94,   101,
     105,   111,   116,   118,   120,   127,   133,   138,   140,   144,
     146,   147,   153,   157,   161,   163,   165,   169,   170,   173,
     177,   179,   183,   185,   189,   191,   193,   195,   197,   199,
     201,   203,   207,   211,   213,   217,   221,   225,   227,   230,
     233,   236,   238,   242,   244,   246,   248,   251,   253,   255,
     257,   260,   263,   267,   270,   274,   276,   278,   280,   282,
     284,   286,   288,   290,   292,   295,   299,   306,   312,   318,
     321,   322,   327,   333,   338,   346,   351,   358,   365,   370,
     372,   376,   381,   386,   388
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    10,    56,    43,    58,    15,    80,    16,
      57,    44,    -1,    10,    56,    43,    58,    15,    80,    16,
      57,    -1,     3,    -1,     3,    -1,    59,    63,    68,    -1,
      59,    68,    -1,    63,    68,    -1,    68,    -1,    13,    60,
      -1,    60,    61,    42,    67,    43,    -1,    -1,    61,    45,
      62,    48,    81,    -1,    62,    48,    81,    -1,     3,    -1,
      14,    64,    -1,    64,    65,    42,    67,    43,    -1,    -1,
      65,    45,    66,    -1,    66,    -1,     3,    -1,     4,    -1,
       5,    -1,    68,    69,    -1,    -1,    70,    73,    -1,    11,
      71,    75,    43,    -1,    12,    72,    75,    42,    67,    43,
      -1,    11,    71,    75,    -1,    12,    72,    75,    42,    67,
      -1,    12,    72,    75,    43,    -1,     3,    -1,     3,    -1,
      63,    15,    80,    16,    74,    43,    -1,    15,    80,    16,
      74,    43,    -1,    15,    80,    16,    74,    -1,     3,    -1,
      46,    76,    47,    -1,    77,    -1,    -1,    77,    43,    78,
      42,    67,    -1,    78,    42,    67,    -1,    78,    45,    79,
      -1,    79,    -1,     3,    -1,    80,    96,    43,    -1,    -1,
      80,    96,    -1,    81,    31,    82,    -1,    82,    -1,    82,
      30,    83,    -1,    83,    -1,    85,    84,    85,    -1,    85,
      -1,    40,    -1,    36,    -1,    41,    -1,    37,    -1,    38,
      -1,    39,    -1,    85,    49,    86,    -1,    85,    50,    86,
      -1,    86,    -1,    86,    51,    87,    -1,    86,    53,    87,
      -1,    86,    52,    87,    -1,    87,    -1,    49,    88,    -1,
      50,    88,    -1,    32,    88,    -1,    88,    -1,    46,    81,
      47,    -1,    91,    -1,    90,    -1,    89,    -1,    46,    81,
      -1,     3,    -1,     7,    -1,     8,    -1,     3,    93,    -1,
       3,    93,    -1,    46,    94,    47,    -1,    46,    47,    -1,
      94,    45,    95,    -1,    95,    -1,    81,    -1,    97,    -1,
      98,    -1,   100,    -1,    92,    -1,   101,    -1,    25,    -1,
      26,    -1,    27,    81,    -1,    89,    48,    81,    -1,    17,
      81,    18,    80,    99,    16,    -1,    17,    81,    80,    99,
      16,    -1,    19,    81,    18,    80,    99,    -1,    20,    80,
      -1,    -1,    19,    81,    80,    99,    -1,    21,    81,    28,
      80,    16,    -1,    22,    80,    23,    81,    -1,    24,    97,
      29,    81,    28,    80,    16,    -1,    21,    81,    80,    16,
      -1,    24,    97,    81,    28,    80,    16,    -1,    24,    97,
      29,    81,    80,    16,    -1,    33,    46,   102,    47,    -1,
      34,    -1,    34,    46,    47,    -1,    34,    46,   102,    47,
      -1,    35,    46,    89,    47,    -1,    95,    -1,     9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   177,   177,   188,   208,   232,   268,   278,   285,   292,
     302,   311,   323,   332,   341,   355,   379,   394,   406,   422,
     430,   448,   482,   488,   503,   510,   527,   557,   570,   583,
     596,   609,   637,   670,   701,   711,   723,   745,   789,   801,
     807,   822,   835,   854,   861,   880,   912,   919,   926,   944,
     953,   968,   977,   991,  1000,  1015,  1021,  1027,  1033,  1039,
    1045,  1062,  1071,  1080,  1096,  1105,  1114,  1123,  1139,  1145,
    1154,  1163,  1183,  1189,  1195,  1201,  1207,  1224,  1259,  1268,
    1287,  1313,  1361,  1367,  1383,  1392,  1412,  1434,  1440,  1446,
    1452,  1458,  1464,  1473,  1482,  1501,  1527,  1537,  1549,  1559,
    1565,  1572,  1594,  1616,  1631,  1668,  1673,  1678,  1695,  1705,
    1714,  1724,  1742,  1762,  1768
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_TYPE_IDENTIFIER",
  "TOKEN_TYPE_BOOLEAN", "TOKEN_TYPE_INTEGER", "TOKEN_TYPE_STRING",
  "TOKEN_TYPE_BOOLEAN_LITERAL", "TOKEN_TYPE_INTEGER_LITERAL",
  "TOKEN_TYPE_STRING_LITERAL", "TOKEN_TYPE_MODULE", "TOKEN_TYPE_PROCEDURE",
  "TOKEN_TYPE_FUNCTION", "TOKEN_TYPE_CONST", "TOKEN_TYPE_VAR",
  "TOKEN_TYPE_BEGIN", "TOKEN_TYPE_END", "TOKEN_TYPE_IF", "TOKEN_TYPE_THEN",
  "TOKEN_TYPE_ELSIF", "TOKEN_TYPE_ELSE", "TOKEN_TYPE_WHILE",
  "TOKEN_TYPE_REPEAT", "TOKEN_TYPE_UNTIL", "TOKEN_TYPE_FOR",
  "TOKEN_TYPE_CONTINUE", "TOKEN_TYPE_BREAK", "TOKEN_TYPE_RETURN",
  "TOKEN_TYPE_DO", "TOKEN_TYPE_TO", "TOKEN_TYPE_AND", "TOKEN_TYPE_OR",
  "TOKEN_TYPE_NOT", "TOKEN_TYPE_WRITE", "TOKEN_TYPE_WRITELN",
  "TOKEN_TYPE_READ", "TOKEN_TYPE_LESS", "TOKEN_TYPE_LESS_EQUAL",
  "TOKEN_TYPE_EQUAL", "TOKEN_TYPE_NOT_EQUAL", "TOKEN_TYPE_GREATER",
  "TOKEN_TYPE_GREATER_EQUAL", "TOKEN_TYPE_COLON", "TOKEN_TYPE_SEMICOLON",
  "TOKEN_TYPE_FULL_STOP", "TOKEN_TYPE_COMMA", "TOKEN_TYPE_LEFT_BRACKET",
  "TOKEN_TYPE_RIGHT_BRACKET", "TOKEN_TYPE_ASSIGN", "TOKEN_TYPE_PLUS",
  "TOKEN_TYPE_MINUS", "TOKEN_TYPE_ASTERISK", "TOKEN_TYPE_MOD",
  "TOKEN_TYPE_SLASH", "$accept", "module", "module_create_scope",
  "module_remove_scope", "declarations", "constdecl", "constdecl_list",
  "constlist", "const_addinfo", "vardecl", "vardecl_list", "varlist",
  "var_addinfo", "datatype", "procdecl_list", "procdecl", "procheader",
  "procheader_create_scope", "funcheader_create_scope", "procbody",
  "procbody_remove_scope", "formalpars", "fpardecl_opt_list",
  "fpardecl_list", "fparlist", "fpar_addinfo", "statements", "expression",
  "andexp", "relexp", "rel_op", "aritexp", "term", "factor", "primary",
  "checkIdentifier", "literal", "funccall", "proccall", "actualpar",
  "parameters_list", "parameter", "statement", "assignment", "conditional",
  "elseif_opt_list", "repetition", "io_statement", "io_parameter", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    57,    58,    58,    58,    58,
      59,    60,    60,    61,    61,    62,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    70,    70,    70,
      70,    70,    71,    72,    73,    73,    73,    74,    75,    76,
      76,    77,    77,    78,    78,    79,    80,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    84,    84,    84,
      84,    85,    85,    85,    86,    86,    86,    86,    87,    87,
      87,    87,    88,    88,    88,    88,    88,    89,    90,    90,
      91,    92,    93,    93,    94,    94,    95,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    98,    98,    99,    99,
      99,    99,   100,   100,   100,   100,   100,   100,   101,   101,
     101,   101,   101,   102,   102
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     9,     8,     1,     1,     3,     2,     2,     1,
       2,     5,     0,     5,     3,     1,     2,     5,     0,     3,
       1,     1,     1,     1,     2,     0,     2,     4,     6,     3,
       5,     4,     1,     1,     6,     5,     4,     1,     3,     1,
       0,     5,     3,     3,     1,     1,     3,     0,     2,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       2,     1,     3,     1,     1,     1,     2,     1,     1,     1,
       2,     2,     3,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     6,     5,     5,     2,
       0,     4,     5,     4,     7,     4,     6,     6,     4,     1,
       3,     4,     4,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,    25,    12,    18,     0,
      25,    25,     9,    10,    16,    47,    25,     7,     8,     0,
       0,    24,     0,    15,     0,     0,    21,     0,    20,     0,
       6,    32,     0,    33,     0,    47,     0,    26,     0,     0,
       0,     0,     0,    77,     0,     0,     0,    47,     0,    92,
      93,     0,     0,   109,     0,     0,    90,    48,    87,    88,
      89,    91,    40,    29,     0,     0,    47,    22,    23,     0,
       0,    77,    78,    79,     0,     0,     0,     0,    14,    50,
      52,    54,    63,    67,    71,    75,    74,    73,     0,    19,
       0,    81,     5,     3,    47,    47,     0,    77,     0,    94,
       0,     0,     0,     0,    46,    45,     0,    39,     0,    44,
      27,     0,    31,     0,     0,    11,     0,    80,    70,    76,
      68,    69,     0,     0,    56,    58,    59,    60,    55,    57,
       0,     0,     0,     0,     0,     0,    17,    83,    86,     0,
      85,     2,    47,   100,    47,     0,     0,     0,     0,   114,
     113,     0,   110,     0,     0,    95,    38,     0,     0,     0,
      30,    37,    36,     0,    13,    72,    49,    51,    61,    62,
      53,    64,    66,    65,     0,    82,   100,     0,    47,     0,
       0,   105,   103,    47,    47,   108,   111,   112,     0,    42,
      43,    28,    35,     0,    84,     0,    47,    99,    97,   102,
      47,     0,     0,     0,    34,    96,    47,   100,     0,   107,
     106,    41,   100,   101,   104,    98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     4,    93,     9,    10,    13,    24,    25,    11,
      14,    27,    28,    69,    12,    21,    22,    32,    34,    37,
     162,    63,   106,   107,   108,   109,    29,   138,    79,    80,
     132,    81,    82,    83,    84,    85,    86,    87,    56,    91,
     139,   150,    57,    58,    59,   179,    60,    61,   151
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -165
static const yytype_int16 yypact[] =
{
      -6,    23,    38,  -165,    25,  -165,    86,  -165,  -165,    47,
      65,  -165,    93,    63,    81,  -165,  -165,    93,    93,    83,
     104,  -165,   107,  -165,   -36,    48,  -165,    -3,  -165,   182,
      93,  -165,    69,  -165,    69,  -165,    98,  -165,   133,    63,
      94,   133,    81,    79,   124,    94,    94,  -165,   147,  -165,
    -165,    94,   106,   110,   111,   112,  -165,   118,  -165,  -165,
    -165,  -165,   159,   121,   103,   202,  -165,  -165,  -165,   122,
     119,    79,  -165,  -165,    17,    94,    17,    17,   135,   139,
    -165,    92,    59,  -165,  -165,  -165,  -165,  -165,   131,  -165,
      42,  -165,  -165,   132,    -4,    28,   217,  -165,    74,   135,
      44,     8,   147,    94,  -165,  -165,   130,   137,    19,  -165,
    -165,   133,  -165,   179,   242,  -165,    94,  -165,  -165,   -26,
    -165,  -165,    94,    94,  -165,  -165,  -165,  -165,  -165,  -165,
      94,    94,    94,    94,    94,    94,  -165,  -165,   135,    -1,
    -165,  -165,  -165,   167,  -165,   257,    94,    94,    52,  -165,
    -165,   143,  -165,   148,   149,   135,  -165,   159,   133,   159,
     154,  -165,   168,   179,   135,  -165,   139,  -165,    59,    59,
      99,  -165,  -165,  -165,    94,  -165,   167,    94,  -165,   194,
     277,  -165,   135,    67,  -165,  -165,  -165,  -165,    30,  -165,
    -165,  -165,  -165,   169,  -165,   197,     0,   347,  -165,  -165,
    -165,   292,   312,   133,  -165,  -165,  -165,   167,   327,  -165,
    -165,  -165,   167,  -165,  -165,  -165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   175,    13,
    -165,  -165,   180,   -40,    18,  -165,  -165,  -165,  -165,  -165,
      58,   191,  -165,  -165,    73,    72,   -25,   -38,   125,   109,
    -165,   101,    24,     1,   -44,   -29,  -165,  -165,  -165,   177,
    -165,   -87,  -165,   198,  -165,  -164,  -165,  -165,   152
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    88,    78,   140,     1,   122,    38,    94,    95,    39,
      65,    71,   195,    99,   142,    72,    73,   149,   206,    55,
      71,   165,    96,    16,    72,    73,     3,   122,    17,    18,
     118,   122,   120,   121,    30,    36,    55,   119,     5,    41,
      74,   114,    42,   213,   174,    71,   175,    71,   215,    72,
      73,    72,    73,   149,    75,   152,   144,    76,    77,   122,
     148,   158,    15,    75,   159,   155,    23,    55,     6,   143,
     145,   160,   203,   154,    74,   159,    74,    71,   164,     8,
     184,    72,    73,   122,    26,    55,    31,   194,    75,   137,
      75,    76,    77,    76,    77,   200,    40,    71,   122,     7,
       8,    72,    73,   147,    19,    20,    74,    33,   182,   183,
     133,   134,   135,    66,    55,    62,    55,   176,   189,   180,
      75,     8,    35,    76,    77,    90,    74,    92,   124,   125,
     126,   127,   128,   129,   171,   172,   173,    67,    68,   196,
      75,   130,   131,    76,    77,   111,   112,    55,   130,   131,
      97,    55,   100,   197,   168,   169,   101,   102,   201,   202,
     103,   104,   105,   211,   110,   115,   122,   116,    55,   123,
      43,   207,    55,    55,   136,   208,   141,   156,    55,    55,
     157,   212,   161,    55,    45,    43,   177,   178,    46,    47,
     185,    48,    49,    50,    51,   186,   187,   191,    44,    45,
      52,    53,    54,    46,    47,    43,    48,    49,    50,    51,
     198,   192,   204,   205,    70,    52,    53,    54,   113,    45,
      43,   193,    89,    46,    47,    64,    48,    49,    50,    51,
     188,   190,   167,   170,    45,    52,    53,    54,    46,    47,
     146,    48,    49,    50,    51,    43,    98,   166,   117,     0,
      52,    53,    54,   153,     0,     0,     0,     0,   163,    45,
      43,     0,     0,    46,    47,     0,    48,    49,    50,    51,
       0,     0,     0,   181,    45,    52,    53,    54,    46,    47,
      43,    48,    49,    50,    51,     0,     0,     0,     0,     0,
      52,    53,    54,   199,    45,    43,     0,     0,    46,    47,
       0,    48,    49,    50,    51,     0,     0,     0,   209,    45,
      52,    53,    54,    46,    47,    43,    48,    49,    50,    51,
       0,     0,     0,     0,     0,    52,    53,    54,   210,    45,
      43,     0,     0,    46,    47,     0,    48,    49,    50,    51,
       0,     0,     0,   214,    45,    52,    53,    54,    46,    47,
      43,    48,    49,    50,    51,     0,     0,     0,     0,     0,
      52,    53,    54,     0,    45,     0,     0,     0,    46,    47,
       0,    48,    49,    50,    51,     0,     0,     0,     0,     0,
      52,    53,    54
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-165))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      29,    41,    40,    90,    10,    31,    42,    45,    46,    45,
      35,     3,   176,    51,    18,     7,     8,     9,    18,    48,
       3,    47,    47,    10,     7,     8,     3,    31,    10,    11,
      74,    31,    76,    77,    16,    22,    65,    75,     0,    42,
      32,    66,    45,   207,    45,     3,    47,     3,   212,     7,
       8,     7,     8,     9,    46,    47,    28,    49,    50,    31,
      98,    42,    15,    46,    45,   103,     3,    96,    43,    94,
      95,   111,    42,   102,    32,    45,    32,     3,   116,    14,
      28,     7,     8,    31,     3,   114,     3,   174,    46,    47,
      46,    49,    50,    49,    50,    28,    48,     3,    31,    13,
      14,     7,     8,    29,    11,    12,    32,     3,   146,   147,
      51,    52,    53,    15,   143,    46,   145,   142,   158,   144,
      46,    14,    15,    49,    50,    46,    32,     3,    36,    37,
      38,    39,    40,    41,   133,   134,   135,     4,     5,   177,
      46,    49,    50,    49,    50,    42,    43,   176,    49,    50,
       3,   180,    46,   178,   130,   131,    46,    46,   183,   184,
      48,    43,     3,   203,    43,    43,    31,    48,   197,    30,
       3,   196,   201,   202,    43,   200,    44,    47,   207,   208,
      43,   206,     3,   212,    17,     3,    19,    20,    21,    22,
      47,    24,    25,    26,    27,    47,    47,    43,    16,    17,
      33,    34,    35,    21,    22,     3,    24,    25,    26,    27,
      16,    43,    43,    16,    39,    33,    34,    35,    16,    17,
       3,   163,    42,    21,    22,    34,    24,    25,    26,    27,
     157,   159,   123,   132,    17,    33,    34,    35,    21,    22,
      23,    24,    25,    26,    27,     3,    48,   122,    71,    -1,
      33,    34,    35,   101,    -1,    -1,    -1,    -1,    16,    17,
       3,    -1,    -1,    21,    22,    -1,    24,    25,    26,    27,
      -1,    -1,    -1,    16,    17,    33,    34,    35,    21,    22,
       3,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    16,    17,     3,    -1,    -1,    21,    22,
      -1,    24,    25,    26,    27,    -1,    -1,    -1,    16,    17,
      33,    34,    35,    21,    22,     3,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    16,    17,
       3,    -1,    -1,    21,    22,    -1,    24,    25,    26,    27,
      -1,    -1,    -1,    16,    17,    33,    34,    35,    21,    22,
       3,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,    17,    -1,    -1,    -1,    21,    22,
      -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    55,     3,    56,     0,    43,    13,    14,    58,
      59,    63,    68,    60,    64,    15,    63,    68,    68,    11,
      12,    69,    70,     3,    61,    62,     3,    65,    66,    80,
      68,     3,    71,     3,    72,    15,    63,    73,    42,    45,
      48,    42,    45,     3,    16,    17,    21,    22,    24,    25,
      26,    27,    33,    34,    35,    89,    92,    96,    97,    98,
     100,   101,    46,    75,    75,    80,    15,     4,     5,    67,
      62,     3,     7,     8,    32,    46,    49,    50,    81,    82,
      83,    85,    86,    87,    88,    89,    90,    91,    67,    66,
      46,    93,     3,    57,    81,    81,    80,     3,    97,    81,
      46,    46,    46,    48,    43,     3,    76,    77,    78,    79,
      43,    42,    43,    16,    80,    43,    48,    93,    88,    81,
      88,    88,    31,    30,    36,    37,    38,    39,    40,    41,
      49,    50,    84,    51,    52,    53,    43,    47,    81,    94,
      95,    44,    18,    80,    28,    80,    23,    29,    81,     9,
      95,   102,    47,   102,    89,    81,    47,    43,    42,    45,
      67,     3,    74,    16,    81,    47,    82,    83,    86,    86,
      85,    87,    87,    87,    45,    47,    80,    19,    20,    99,
      80,    16,    81,    81,    28,    47,    47,    47,    78,    67,
      79,    43,    43,    74,    95,    99,    81,    80,    16,    16,
      28,    80,    80,    42,    43,    16,    18,    80,    80,    16,
      16,    67,    80,    99,    16,    99
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 178 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("module", "\"Module\" ID \";\" declarations \"Begin\""
                                                                "statements \"End\" ID \".\"", (yylsp[(1) - (9)]).first_line);

        ModuleNode *moduleRoot = new ModuleNode( (ModuleInformation*)(yyvsp[(2) - (9)].identifier_info), (yyvsp[(4) - (9)].declaration), (yyvsp[(6) - (9)].statement) );
        
        ::oberonc.setASTRoot(moduleRoot);

}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 189 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugRecoveredError("missing a \".\" at the end of the module.",
                                                                                        (yylsp[(8) - (8)]).first_line);
        
        ModuleNode *moduleRoot = new ModuleNode( (ModuleInformation*)(yyvsp[(2) - (8)].identifier_info), (yyvsp[(4) - (8)].declaration), (yyvsp[(6) - (8)].statement) );
        
        ::oberonc.setASTRoot(moduleRoot);
}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 208 "yy_parser.y"
    {

        symbolTable.createScope("GLOBAL");

        ModuleInformation *moduleInformation = new ModuleInformation((yyvsp[(1) - (1)].identifier));
        symbolTable.insertAtCurrentScope(moduleInformation);
        
        symbolTable.createScope((yyvsp[(1) - (1)].identifier));

        (yyval.identifier_info) = moduleInformation;
}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 232 "yy_parser.y"
    {

        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (1)].identifier));
        
        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_MODULE)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
        
        Scope * moduleScope  = symbolTable.removeScope(); // Remove escopo do Módulo
        Scope * globalScope  = symbolTable.removeScope(); // Remove escopo GLOBAL
        
        moduleScope->debug( ::oberonc.getSymbolTableDebugger() );
        globalScope->debug( ::oberonc.getSymbolTableDebugger() );

        delete moduleScope;
        delete globalScope;
        
        delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 268 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("declarations", "constdecl vardecl procdecl_list", (yylsp[(1) - (3)]).first_line);

		DeclarationSequenceNode *varAndConstLists = new DeclarationSequenceNode((yyvsp[(1) - (3)].declaration), (yyvsp[(2) - (3)].declaration));
		(yyval.declaration) = new DeclarationSequenceNode(varAndConstLists, (yyvsp[(3) - (3)].declaration));

		::oberonc.addNodeToCleanUpList(varAndConstLists);
		::oberonc.addNodeToCleanUpList((yyval.declaration));
        
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 278 "yy_parser.y"
    {
        
        ::oberonc.getParserDebugger()->debugReduction("declarations", "constdecl procdecl_list", (yylsp[(1) - (2)]).first_line);
        
        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(1) - (2)].declaration), (yyvsp[(2) - (2)].declaration));
		::oberonc.addNodeToCleanUpList((yyval.declaration));
		
}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 285 "yy_parser.y"
    {
        
        ::oberonc.getParserDebugger()->debugReduction("declarations", "vardecl procdecl_list", (yylsp[(1) - (2)]).first_line);
        
        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(1) - (2)].declaration), (yyvsp[(2) - (2)].declaration));
		::oberonc.addNodeToCleanUpList((yyval.declaration));
		
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 292 "yy_parser.y"
    {
        
        ::oberonc.getParserDebugger()->debugReduction("declarations", "procdecl_list", (yylsp[(1) - (1)]).first_line);
        
        (yyval.declaration) = (yyvsp[(1) - (1)].declaration);
}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 302 "yy_parser.y"
    {
	
		::oberonc.getParserDebugger()->debugReduction("constdecl", "\"const\" constdecl_list", (yylsp[(1) - (2)]).first_line);
		
		(yyval.declaration) = (yyvsp[(2) - (2)].declaration);
		
}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 311 "yy_parser.y"
    {
		
		::oberonc.getParserDebugger()->debugReduction("constdecl_list", "constdecl_list constlist \":\""
		                                                                "datatype \";\"", (yylsp[(0) - (5)]).first_line);
		
        ConstantListNode *constantList = (ConstantListNode*)(yyvsp[(1) - (5)].declaration);
        DeclarationSequenceNode *constantSequence = (DeclarationSequenceNode*)(yyvsp[(2) - (5)].declaration);
        
        constantList->addConstantSequence(constantSequence, (yyvsp[(4) - (5)].dataType));
        
        (yyval.declaration) = (yyvsp[(1) - (5)].declaration);		
		
}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 323 "yy_parser.y"
    {
		
		::oberonc.getParserDebugger()->debugReduction("constdecl_list", "/* */ ", (yylsp[(0) - (0)]).first_line);
		
        (yyval.declaration) = new ConstantListNode();
		::oberonc.addNodeToCleanUpList((yyval.declaration)); 
}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 332 "yy_parser.y"
    {
		
		::oberonc.getParserDebugger()->debugReduction("constlist", "constlist \",\" ID \":=\" expression", 
		                                                                                   (yylsp[(0) - (5)]).first_line);
		
		((ConstantNode *)(yyvsp[(3) - (5)].declaration))->setExpressionValue((yyvsp[(5) - (5)].expression));
		(yyval.declaration) = new DeclarationSequenceNode((yyvsp[(3) - (5)].declaration), (yyvsp[(1) - (5)].declaration));
		::oberonc.addNodeToCleanUpList((yyval.declaration)); 
		
}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 341 "yy_parser.y"
    {

 		::oberonc.getParserDebugger()->debugReduction("const_addinfo", "ID \":=\" expression", (yylsp[(1) - (3)]).first_line);
		
		((ConstantNode *)(yyvsp[(1) - (3)].declaration))->setExpressionValue((yyvsp[(3) - (3)].expression));
        
		(yyval.declaration) = new DeclarationSequenceNode((yyvsp[(1) - (3)].declaration), NULL); 
		::oberonc.addNodeToCleanUpList((yyval.declaration)); 
		
}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 355 "yy_parser.y"
    {
		
        if(symbolTable.isAtCurrentScope((yyvsp[(1) - (1)].identifier)))
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
      
        ConstantInformation *constantInformation = new ConstantInformation((yyvsp[(1) - (1)].identifier));
        symbolTable.insertAtCurrentScope(constantInformation);
        
        (yyval.declaration) = new ConstantNode(constantInformation, NULL); 
        (yyval.declaration)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 

        delete [] (yyvsp[(1) - (1)].identifier);
		
}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 379 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("vardecl", "\"var\" vardecl_list", (yylsp[(1) - (2)]).first_line);
        
        (yyval.declaration) = (yyvsp[(2) - (2)].declaration);
		
}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 394 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("vardecl_list", "vardecl_list varlist \":\" datatype \";\"",
                                                                                                  (yylsp[(0) - (5)]).first_line);
        
        VariableListNode *variableList = (VariableListNode*)(yyvsp[(1) - (5)].declaration);
        DeclarationSequenceNode *variableSequence = (DeclarationSequenceNode*)(yyvsp[(2) - (5)].declaration);
        
        variableList->addVariableSequence(variableSequence, (yyvsp[(4) - (5)].dataType));
        
        (yyval.declaration) = (yyvsp[(1) - (5)].declaration);
        
}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 406 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("vardecl_list", "/*  */ ", (yylsp[(0) - (0)]).first_line);
                
        (yyval.declaration) = new VariableListNode();
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 422 "yy_parser.y"
    {
        
        ::oberonc.getParserDebugger()->debugReduction("varlist", "varlist \",\" ID", (yylsp[(3) - (3)]).first_line);

        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(3) - (3)].declaration), (yyvsp[(1) - (3)].declaration));
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
        

}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 430 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("varlist", "ID", (yylsp[(1) - (1)]).first_line);

        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(1) - (1)].declaration), NULL);        
}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 448 "yy_parser.y"
    {

        if(symbolTable.isAtCurrentScope((yyvsp[(1) - (1)].identifier)))
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
      
        VariableInformation *variableInformation = new VariableInformation((yyvsp[(1) - (1)].identifier));
        symbolTable.insertAtCurrentScope(variableInformation);
        
        IdentifierInformation *identifierInfo = symbolTable.lookup( symbolTable.getCurrentScope()->getName() );
        
        if(identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
           FunctionInformation *functionInformation = (FunctionInformation *)identifierInfo;
           functionInformation->getVariableList().push_back(variableInformation);
        }

        (yyval.declaration) = new VariableNode(variableInformation); 
		(yyval.declaration)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 

        delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 482 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("datatype", "\"Boolean\"", (yylsp[(1) - (1)]).first_line);
        
        (yyval.dataType) = DATA_TYPE_BOOLEAN;
        
}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 488 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("datatype", "\"Integer\"", (yylsp[(1) - (1)]).first_line);
        
        (yyval.dataType) = DATA_TYPE_INTEGER;
}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 503 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("procdecl_list", "procdecl_list procdecl", (yylsp[(0) - (2)]).first_line);
        
        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(1) - (2)].declaration), (yyvsp[(2) - (2)].declaration));
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
    
}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 510 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("procdecl_list", "/*  */ ", (yylsp[(0) - (0)]).first_line);
        
        (yyval.declaration) = new SkipDeclarationNode();
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 527 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("procdecl", "procheader procbody", (yylsp[(1) - (2)]).first_line);

        
        FunctionNode * functionNode1 = (FunctionNode*)(yyvsp[(1) - (2)].declaration);
        FunctionNode * functionNode2 = (FunctionNode*)(yyvsp[(2) - (2)].declaration);
        
        DeclarationSequenceNode * declarationSequence = new DeclarationSequenceNode( 
                                                                     functionNode1->getDeclarations(),
                                                                     functionNode2->getDeclarations() 
                                                                   ); 

        functionNode1->setDeclarations(declarationSequence);
        functionNode1->setStatements( functionNode2->getStatements() );

        ::oberonc.addNodeToCleanUpList(declarationSequence); 
        
        (yyval.declaration) = functionNode1;
}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 557 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("procheader", "\"Procedure\" ID formalpars \";\"",  
                                                                                         (yylsp[(1) - (4)]).first_line);
        
        FunctionNode *functionNode = (FunctionNode *)(yyvsp[(2) - (4)].declaration);
        
        functionNode->setReturnType(DATA_TYPE_VOID);
        functionNode->setDeclarations((yyvsp[(3) - (4)].declaration));
        functionNode->setStatements(NULL);
        
        (yyval.declaration) = functionNode;

}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 570 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("procheader", "\"Function\" ID formalpars \":\""
                                                                      "datatype \";\"", (yylsp[(1) - (6)]).first_line);
        
        FunctionNode *functionNode = (FunctionNode *)(yyvsp[(2) - (6)].declaration);
        
        functionNode->setReturnType((yyvsp[(5) - (6)].dataType));
        functionNode->setDeclarations((yyvsp[(3) - (6)].declaration));
        functionNode->setStatements(NULL);
        
        (yyval.declaration) = functionNode;
        
}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 583 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" at the end of the procedure's header.",
                                                                                                    (yylsp[(3) - (3)]).first_line);
        
        FunctionNode *functionNode = (FunctionNode *)(yyvsp[(2) - (3)].declaration);
        
        functionNode->setReturnType(DATA_TYPE_VOID);
        functionNode->setDeclarations((yyvsp[(3) - (3)].declaration));
        functionNode->setStatements(NULL);
        
        (yyval.declaration) = functionNode;
        
}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 596 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" at the end of the function's header.",
                                                                                                   (yylsp[(5) - (5)]).first_line);
        
        FunctionNode *functionNode = (FunctionNode *)(yyvsp[(2) - (5)].declaration);
        
        functionNode->setReturnType((yyvsp[(5) - (5)].dataType));
        functionNode->setDeclarations((yyvsp[(3) - (5)].declaration));
        functionNode->setStatements(NULL);
        
        (yyval.declaration) = functionNode;
        
}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 609 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Function without a return type.", (yylsp[(4) - (4)]).first_line);
        
        FunctionNode *functionNode = (FunctionNode *)(yyvsp[(2) - (4)].declaration);
        
        functionNode->setReturnType(DATA_TYPE_VOID);
        functionNode->setDeclarations((yyvsp[(3) - (4)].declaration));
        functionNode->setStatements(NULL);
        
        (yyval.declaration) = functionNode;
        
}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 637 "yy_parser.y"
    {

        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (1)].identifier));

        if(identifierInfo)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
       
       FunctionInformation *functionInformation = new FunctionInformation((yyvsp[(1) - (1)].identifier));
       symbolTable.insertAtCurrentScope(functionInformation);

       symbolTable.createScope((yyvsp[(1) - (1)].identifier));
       
       (yyval.declaration) = new FunctionNode(functionInformation, NULL, NULL);
	   (yyval.declaration)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
       ::oberonc.addNodeToCleanUpList((yyval.declaration));
       
       delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 670 "yy_parser.y"
    {

        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (1)].identifier));
    
        if(identifierInfo)
        {
           ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
        
        FunctionInformation *functionInformation = new FunctionInformation((yyvsp[(1) - (1)].identifier));
        symbolTable.insertAtCurrentScope(functionInformation);

        symbolTable.createScope((yyvsp[(1) - (1)].identifier));
        
        (yyval.declaration) = new FunctionNode(functionInformation, NULL, NULL);
		(yyval.declaration)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.declaration));
        
        delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 701 "yy_parser.y"
    {

         ::oberonc.getParserDebugger()->debugReduction("procbody", "vardecl \"begin\" statements \"end\" ID \";\"",
                                                                                                     (yylsp[(1) - (6)]).first_line);
        
        (yyval.declaration) = new FunctionNode( NULL, (yyvsp[(1) - (6)].declaration), (yyvsp[(3) - (6)].statement) );
		(yyval.declaration)->setFirstLine((yylsp[(1) - (6)]).first_line);
		
         ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
        
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 711 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("procbody", "\"begin\" statements \"end\" ID \";\"",
                                                                                            (yylsp[(1) - (5)]).first_line);
        
        SkipDeclarationNode * skipDeclaration = new SkipDeclarationNode();
        (yyval.declaration) = new FunctionNode( NULL, skipDeclaration, (yyvsp[(2) - (5)].statement) ); 
        (yyval.declaration)->setFirstLine((yylsp[(1) - (5)]).first_line);
		
         ::oberonc.addNodeToCleanUpList(skipDeclaration); 
         ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
        
}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 723 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" after \"end\".", (yylsp[(4) - (4)]).first_line);
        
        SkipDeclarationNode * skipDeclaration = new SkipDeclarationNode();
        (yyval.declaration) = new FunctionNode( NULL, skipDeclaration, (yyvsp[(2) - (4)].statement) );
        (yyval.declaration)->setFirstLine((yylsp[(1) - (4)]).first_line);
		
         ::oberonc.addNodeToCleanUpList(skipDeclaration); 
         ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 745 "yy_parser.y"
    {
       
        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (1)].identifier));
        Scope *scope = symbolTable.removeScope();
        
        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
        else
        {
            bool equal = true;
            const char *str1 = scope->getName();
            const char *str2 = (yyvsp[(1) - (1)].identifier);

            while(*str1 && equal)
            {
                equal = ( tolower(*str1++) == tolower(*str2++) );
            }
            
            if(!equal)
            {
                ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
            }
        }
                
        scope->debug( ::oberonc.getSymbolTableDebugger() );
        
        delete scope;
        delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 789 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("formalpars", "\"(\" fpardecl_opt_list \")\"",
                                                                                  (yylsp[(1) - (3)]).first_line);
        
        (yyval.declaration) = (yyvsp[(2) - (3)].declaration);
}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 801 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("fpardecl_opt_list", "fpardecl_list", (yylsp[(1) - (1)]).first_line);
        
        (yyval.declaration) = (yyvsp[(1) - (1)].declaration);
        
}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 807 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("fpardecl_opt_list", "/* */", (yylsp[(0) - (0)]).first_line);
        
        (yyval.declaration) = new FormalParameterListNode();
         ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 822 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("fpardecl_list", "fpardecl_list \";\""
                                                       "fparlist \":\" datatype", (yylsp[(0) - (5)]).first_line);
        
        
        FormalParameterListNode *formalParameterList = (FormalParameterListNode*)(yyvsp[(1) - (5)].declaration);
        DeclarationSequenceNode *formalParameterSequence = (DeclarationSequenceNode*)(yyvsp[(3) - (5)].declaration);
    
        formalParameterList->addFormalParameterSequence(formalParameterSequence, (yyvsp[(5) - (5)].dataType));
        
        (yyval.declaration) = (yyvsp[(1) - (5)].declaration);    
        
}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 835 "yy_parser.y"
    {


        FormalParameterListNode *formalParameterList = new FormalParameterListNode();
        DeclarationSequenceNode *formalParameterSequence = (DeclarationSequenceNode*)(yyvsp[(1) - (3)].declaration);
        
        formalParameterList->addFormalParameterSequence(formalParameterSequence, (yyvsp[(3) - (3)].dataType));
        
        (yyval.declaration) = formalParameterList;
          ::oberonc.addNodeToCleanUpList((yyval.declaration));         
}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 854 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("fparlist", "fparlist \",\" ID", (yylsp[(1) - (3)]).first_line);
        
        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(3) - (3)].declaration), (yyvsp[(1) - (3)].declaration));
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
        
}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 861 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("fparlist", "ID", (yylsp[(1) - (1)]).first_line);

        (yyval.declaration) = new DeclarationSequenceNode((yyvsp[(1) - (1)].declaration), NULL);
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 
}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 880 "yy_parser.y"
    {

        if(symbolTable.isAtCurrentScope((yyvsp[(1) - (1)].identifier)))
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierAlreadyDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
        }
       
        FormalParameterInformation *formalParameterInformation = new FormalParameterInformation((yyvsp[(1) - (1)].identifier));
        symbolTable.insertAtCurrentScope(formalParameterInformation);

        IdentifierInformation *identifierInfo = symbolTable.lookup( symbolTable.getCurrentScope()->getName() );
        
        if(identifierInfo->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
           FunctionInformation *functionInformation = (FunctionInformation *)identifierInfo;
           functionInformation->getFormalParameterList().push_back(formalParameterInformation);
        }
       
        (yyval.declaration) = new FormalParameterNode( formalParameterInformation );
		(yyval.declaration)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.declaration)); 

        delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 912 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("statements", "statements statement \";\"", (yylsp[(0) - (3)]).first_line);
        
        (yyval.statement) = new StatementSequenceNode( (yyvsp[(1) - (3)].statement), (yyvsp[(2) - (3)].statement) );
		::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 919 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statements", "/*  */", (yylsp[(0) - (0)]).first_line);
        
        (yyval.statement) = new SkipStatementNode();
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 

}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 926 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \";\" after statement.", (yylsp[(2) - (2)]).first_line);

        (yyval.statement) = new StatementSequenceNode( (yyvsp[(1) - (2)].statement), (yyvsp[(2) - (2)].statement) );
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 

}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 944 "yy_parser.y"
    {
     
        ::oberonc.getParserDebugger()->debugReduction("expression", "expression \"or\" andexp", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new OrNode( (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression) );
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);
		
         ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 953 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("expression", "andexp", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 968 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("andexp", "andexp \"and\" relexp", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new AndNode( (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression) );
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);

         ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 977 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("andexp", "relexp", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 991 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("relexp", "aritexp rel_op aritexp", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new RelationalNode((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].relationalOperator), (yyvsp[(3) - (3)].expression));
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);

		::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 1000 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("relexp", "aritexp", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 1015 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("rel_op", ">", (yylsp[(1) - (1)]).first_line);
        
        (yyval.relationalOperator) = RELATIONAL_OPERATOR_GREATER;
        
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 1021 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "<", (yylsp[(1) - (1)]).first_line);
        
        (yyval.relationalOperator) = RELATIONAL_OPERATOR_LESS;
        
}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 1027 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", ">=", (yylsp[(1) - (1)]).first_line);
        
        (yyval.relationalOperator) = RELATIONAL_OPERATOR_GREATER_OR_EQUAL;
        
}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 1033 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "<=", (yylsp[(1) - (1)]).first_line);
        
        (yyval.relationalOperator) = RELATIONAL_OPERATOR_LESS_OR_EQUAL;
        
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 1039 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "=", (yylsp[(1) - (1)]).first_line);
        
        (yyval.relationalOperator) = RELATIONAL_OPERATOR_EQUAL;
        
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 1045 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("rel_op", "#", (yylsp[(1) - (1)]).first_line);
        
        (yyval.relationalOperator) = RELATIONAL_OPERATOR_DIFFERENT;
        
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 1062 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("aritexp", "aritexp + term", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new ArithmeticNode((yyvsp[(1) - (3)].expression), ARITHMETIC_OPERATOR_ADD, (yyvsp[(3) - (3)].expression));
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
    
}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 1071 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("aritexp", "aritexp - term", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new ArithmeticNode((yyvsp[(1) - (3)].expression), ARITHMETIC_OPERATOR_SUB, (yyvsp[(3) - (3)].expression));
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 1080 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("aritexp", "term", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 1096 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("term", "term * factor", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new ArithmeticNode((yyvsp[(1) - (3)].expression), ARITHMETIC_OPERATOR_MULT, (yyvsp[(3) - (3)].expression));
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 1105 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("term", "term / factor", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new ArithmeticNode((yyvsp[(1) - (3)].expression), ARITHMETIC_OPERATOR_DIV, (yyvsp[(3) - (3)].expression));
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 1114 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("term", "term \"mod\" factor", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = new ArithmeticNode((yyvsp[(1) - (3)].expression), ARITHMETIC_OPERATOR_MOD, (yyvsp[(3) - (3)].expression));
        (yyval.expression)->setFirstLine((yylsp[(1) - (3)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 1123 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("term", "factor", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1139 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("factor", "\"+\" primary", (yylsp[(1) - (2)]).first_line);
        
        (yyval.expression) = (yyvsp[(2) - (2)].expression);
        
}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1145 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("factor", "\"-\" primary", (yylsp[(1) - (2)]).first_line);
        
        (yyval.expression) = new NegationNode( (yyvsp[(2) - (2)].expression) );
        (yyval.expression)->setFirstLine((yylsp[(1) - (2)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1154 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("factor", "\"not\" primary", (yylsp[(1) - (2)]).first_line);
        
        (yyval.expression) = new NotNode( (yyvsp[(2) - (2)].expression) );
        (yyval.expression)->setFirstLine((yylsp[(1) - (2)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1163 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("factor", "primary", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1183 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("primary", "\"(\" expression \")\"", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = (yyvsp[(2) - (3)].expression);
        
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1189 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("primary", "proccall", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
        
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1195 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("primary", "literal", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
        
}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1201 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("primary", "ID", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
        
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1207 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Unbalanced brackets.", (yylsp[(2) - (2)]).first_line);
        
        (yyval.expression) = (yyvsp[(2) - (2)].expression);
}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1224 "yy_parser.y"
    {

        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (1)].identifier));
        
        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
			(yyval.expression) = NULL;
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_CONSTANT &&
	         	identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_VARIABLE &&
                identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier((yyvsp[(1) - (1)].identifier), (yylsp[(1) - (1)]).first_line);
			(yyval.expression) = NULL;
        }
		else
		{
            (yyval.expression) = new IdentifierNode(identifierInfo);
            (yyval.expression)->setFirstLine((yylsp[(1) - (1)]).first_line);
            ::oberonc.addNodeToCleanUpList((yyval.expression)); 
		}
        
        delete [] (yyvsp[(1) - (1)].identifier);
}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1259 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("literal", "BOOLEAN_LITERAL", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = new BooleanLiteralNode((yyvsp[(1) - (1)].bool_value));
        (yyval.expression)->setFirstLine((yylsp[(1) - (1)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1268 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("literal", "INTEGER_LITERAL", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = new IntegerLiteralNode((yyvsp[(1) - (1)].int_value));
        (yyval.expression)->setFirstLine((yylsp[(1) - (1)]).first_line);

		::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1287 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("funccall", "ID actualpar", (yylsp[(1) - (2)]).first_line);
    
        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (2)].identifier));

        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared((yyvsp[(1) - (2)].identifier), (yylsp[(1) - (2)]).first_line);
        }
        else if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FUNCTION)
        {
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier((yyvsp[(1) - (2)].identifier), (yylsp[(1) - (2)]).first_line);
            identifierInfo = (IdentifierInformation*)0;
        }
        
        
        (yyval.expression) = new FunctionCallNode( (FunctionInformation*)identifierInfo, (ActualParameterListNode*)(yyvsp[(2) - (2)].expression) );
        (yyval.expression)->setFirstLine((yylsp[(1) - (2)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
        
        delete [] (yyvsp[(1) - (2)].identifier);
}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1313 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("proccall", "ID actualpar", (yylsp[(1) - (2)]).first_line);

        IdentifierInformation *identifierInfo = symbolTable.lookup((yyvsp[(1) - (2)].identifier));

        if(identifierInfo == (IdentifierInformation*)0)
        {
            ::oberonc.getSymbolTableDebugger()->debugIdentifierNotDeclared((yyvsp[(1) - (2)].identifier), (yylsp[(1) - (2)]).first_line);
        }
        else
        {
            if(identifierInfo->getCategoryType() != IDENTIFIER_CATEGORY_TYPE_FUNCTION)
           {
              ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier((yyvsp[(1) - (2)].identifier), (yylsp[(1) - (2)]).first_line);
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
    
        
        (yyval.statement) = new ProcedureCallNode( (FunctionInformation*)identifierInfo, (ActualParameterListNode*)(yyvsp[(2) - (2)].expression) );
		(yyval.statement)->setFirstLine((yylsp[(1) - (2)]).first_line);
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 

        delete [] (yyvsp[(1) - (2)].identifier);
}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1361 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("actualpar", "\"(\" parameters_list \")\"", (yylsp[(1) - (3)]).first_line);
        
        (yyval.expression) = (yyvsp[(2) - (3)].expression);
        
}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1367 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("actualpar", "\"(\" \")\"", (yylsp[(1) - (2)]).first_line);
        
        (yyval.expression) = new ActualParameterListNode();
        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1383 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("parameters_list", "parameters_list \",\" parameter", 
                                                                                            (yylsp[(0) - (3)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (3)].expression);
        ActualParameterListNode *actualParameterList = (ActualParameterListNode *)(yyvsp[(1) - (3)].expression);
        actualParameterList->addActualParameter((yyvsp[(3) - (3)].expression));
        
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1392 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("parameters_list", "parameter", (yylsp[(1) - (1)]).first_line);
        
        ActualParameterListNode *actualParameterList = new ActualParameterListNode();
        actualParameterList->addActualParameter((yyvsp[(1) - (1)].expression));

        (yyval.expression) = actualParameterList;
        ::oberonc.addNodeToCleanUpList((yyval.expression)); 

}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1412 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("parameter", "expression", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1434 "yy_parser.y"
    {

    ::oberonc.getParserDebugger()->debugReduction("statement", "assignment", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = (yyvsp[(1) - (1)].statement);
        
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1440 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "conditional", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = (yyvsp[(1) - (1)].statement);
        
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1446 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "repetition", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = (yyvsp[(1) - (1)].statement);
        
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1452 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "proccall", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = (yyvsp[(1) - (1)].statement);
        
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1458 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "io_statement", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = (yyvsp[(1) - (1)].statement);
        
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1464 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "\"continue\"", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = new ContinueNode();
		(yyval.statement)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1473 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "\"break\"", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = new BreakNode();
		(yyval.statement)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1482 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("statement", "\"return\" expression", (yylsp[(1) - (2)]).first_line);
        
        (yyval.statement) = new ReturnNode( (yyvsp[(2) - (2)].expression) );
		(yyval.statement)->setFirstLine((yylsp[(1) - (2)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1501 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("assignment", "ID \":=\" expression", (yylsp[(1) - (3)]).first_line);
        
		IdentifierNode* identifierNode = (IdentifierNode*)(yyvsp[(1) - (3)].expression);
		
		if(identifierNode != NULL && identifierNode->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
		{
            ::oberonc.getSymbolTableDebugger()->debugUnexpectedUseOfIdentifier(identifierNode->getIdentifier(),
                                                                        		 	            (yylsp[(1) - (3)]).first_line);
        }
  
        (yyval.statement) = new AssignmentNode( identifierNode, (yyvsp[(3) - (3)].expression) );
		(yyval.statement)->setFirstLine((yylsp[(1) - (3)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1527 "yy_parser.y"
    {

         ::oberonc.getParserDebugger()->debugReduction("conditional", "\"If\" expression \"Then\" statements"
                                                       "elseif_opt_list else_opt \"end\"", (yylsp[(1) - (6)]).first_line);
        
        (yyval.statement) = new ConditionalNode((yyvsp[(2) - (6)].expression), (yyvsp[(4) - (6)].statement), (yyvsp[(5) - (6)].statement));
		(yyval.statement)->setFirstLine((yylsp[(1) - (6)]).first_line);
		
         ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1537 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"then\" after the \"if\" condition.", 
                                                                                             (yylsp[(2) - (5)]).first_line);
        
        (yyval.statement) = new ConditionalNode((yyvsp[(2) - (5)].expression), (yyvsp[(3) - (5)].statement), (yyvsp[(4) - (5)].statement));
		(yyval.statement)->setFirstLine((yylsp[(1) - (5)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1549 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("elseif_opt_list", "elseif_opt_list \"elsif\" expression"
                                                                         "\"then\" statements", (yylsp[(1) - (5)]).first_line);
        
        (yyval.statement) = new ConditionalNode((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].statement), (yyvsp[(5) - (5)].statement));
		(yyval.statement)->setFirstLine((yylsp[(1) - (5)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1559 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("elseif_opt_list", "\"else\" statements", (yylsp[(1) - (2)]).first_line);
        
        (yyval.statement) = (yyvsp[(2) - (2)].statement);
        
}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1565 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("elseif_opt_list", "/*  */", (yylsp[(0) - (0)]).first_line);
        
        (yyval.statement) = new SkipStatementNode();
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1572 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"then\" after the \"elsif\" condition.", 
                                                                                                (yylsp[(2) - (4)]).first_line);
        
        (yyval.statement) = new ConditionalNode((yyvsp[(2) - (4)].expression), (yyvsp[(3) - (4)].statement), (yyvsp[(4) - (4)].statement));
		(yyval.statement)->setFirstLine((yylsp[(1) - (4)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1594 "yy_parser.y"
    {
        
        ::oberonc.getParserDebugger()->debugReduction("repetition", "\"While\" expression \"Do\" statements"
                                                                                  "\"End\"", (yylsp[(1) - (5)]).first_line);
		
		PreTestLoopNode * preTestLoopNode = new PreTestLoopNode((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].statement));
		//RepetitionNode * repetitionNode = new RepetitionNode($4, $2);
		//SkipStatementNode * skipStatement = new SkipStatementNode();
		//SkipStatementNode * sequenceSkipStatement = new SkipStatementNode();
		//StatementSequenceNode *statementSequenceNode = new StatementSequenceNode(sequenceSkipStatement, repetitionNode);
        
        
        //$$ = new ConditionalNode($2, statementSequenceNode, skipStatement);
		(yyval.statement) = preTestLoopNode;
        (yyval.statement)->setFirstLine((yylsp[(1) - (5)]).first_line);
		
        //::oberonc.addNodeToCleanUpList(repetitionNode); 
		//::oberonc.addNodeToCleanUpList(statementSequenceNode); 
		//::oberonc.addNodeToCleanUpList(sequenceSkipStatement); 
        //::oberonc.addNodeToCleanUpList(skipStatement); 
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 

}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1616 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("repetition", "\"Repeat\" statements \"Until\" expression",
                                                                                                   (yylsp[(1) - (4)]).first_line);
        
        NotNode *notNode = new NotNode((yyvsp[(4) - (4)].expression));
		notNode->setFirstLine((yylsp[(1) - (4)]).first_line);

        (yyval.statement) = new PostTestLoopNode((yyvsp[(2) - (4)].statement), notNode);
		(yyval.statement)->setFirstLine((yylsp[(1) - (4)]).first_line);

        ::oberonc.addNodeToCleanUpList(notNode); 
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 


}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1631 "yy_parser.y"
    {
        
        ::oberonc.getParserDebugger()->debugReduction("repetition", "\"For\" ID \"=\" expression \"To\""
                                                      "expression \"Do\" statements \"end\"", (yylsp[(1) - (7)]).first_line);
		
        AssignmentNode *initialAssignment = (AssignmentNode*)(yyvsp[(2) - (7)].statement);
        IdentifierNode *loopIdentifier =  initialAssignment->getIdentifier();
        RelationalNode *guard = new RelationalNode( loopIdentifier, RELATIONAL_OPERATOR_LESS_OR_EQUAL, (yyvsp[(4) - (7)].expression) );
    
        IntegerLiteralNode *offsetInc = new IntegerLiteralNode(1);
        ArithmeticNode *identifierIncrement = new ArithmeticNode( loopIdentifier, ARITHMETIC_OPERATOR_ADD, offsetInc );
        AssignmentNode *step = new AssignmentNode(loopIdentifier, identifierIncrement);
      
        ///StatementSequenceNode * repetitionStatements = new StatementSequenceNode($6, step);
        
		//RepetitionNode *repetition = new RepetitionNode(repetitionStatements, guard);
       
        //SkipStatementNode * skipStatement = new SkipStatementNode();
        //ConditionalNode *loop = new ConditionalNode( guard, repetition, skipStatement );
		///PreTestLoopNode *loop = new PreTestLoopNode(guard, repetitionStatements);
        ///$$ = new StatementSequenceNode( initialAssignment, loop );
		(yyval.statement) = new ForLoopNode(initialAssignment, guard, step, (yyvsp[(6) - (7)].statement));
		
		guard->setFirstLine((yylsp[(4) - (7)]).first_line);
		(yyval.statement)->setFirstLine((yylsp[(1) - (7)]).first_line);
		
		
        ::oberonc.addNodeToCleanUpList(guard); 
        ::oberonc.addNodeToCleanUpList(offsetInc); 
        ::oberonc.addNodeToCleanUpList(identifierIncrement); 
        ::oberonc.addNodeToCleanUpList(step); 
        ::oberonc.addNodeToCleanUpList((yyval.statement));
		//::oberonc.addNodeToCleanUpList(repetitionStatements); 
        //::oberonc.addNodeToCleanUpList(repetition); 
        //::oberonc.addNodeToCleanUpList(skipStatement); 
        //::oberonc.addNodeToCleanUpList(loop); 

}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1668 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"Do\" after the \"While\" condition.",
                                                                                                  (yylsp[(2) - (4)]).first_line);

}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1673 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"To\" in the \"For\" statement.",
                                                                                         (yylsp[(2) - (6)]).first_line);

}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1678 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugRecoveredError("Missing a \"Do\" in the \"For\" statement.",
                                                                                         (yylsp[(4) - (6)]).first_line);

}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1695 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"Write\" \"(\" io_parameter \")\"", 
                                                                                            (yylsp[(1) - (4)]).first_line);

		(yyval.statement) = new WriteNode((yyvsp[(3) - (4)].expression));;
		(yyval.statement)->setFirstLine((yylsp[(1) - (4)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1705 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"WriteLn\"", (yylsp[(1) - (1)]).first_line);
        
        (yyval.statement) = new WriteLineNode();
		(yyval.statement)->setFirstLine((yylsp[(1) - (1)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1714 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"WriteLn\" \"(\" \")\"", 
                                                                                 (yylsp[(1) - (3)]).first_line);
        
        (yyval.statement) = new WriteLineNode();
		(yyval.statement)->setFirstLine((yylsp[(1) - (3)]).first_line);
		
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1724 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"WriteLn\" \"(\" io_parameter \")\"",
                                                                                              (yylsp[(1) - (4)]).first_line);
        
        WriteNode * writeNode = new WriteNode((yyvsp[(3) - (4)].expression));
        WriteLineNode * writeLineNode = new WriteLineNode();

		writeNode->setFirstLine((yylsp[(1) - (4)]).first_line);
		writeLineNode->setFirstLine((yylsp[(1) - (4)]).first_line);

        (yyval.statement) = new StatementSequenceNode( writeNode, writeLineNode );
		(yyval.statement)->setFirstLine((yylsp[(1) - (4)]).first_line);

        ::oberonc.addNodeToCleanUpList(writeNode); 
        ::oberonc.addNodeToCleanUpList(writeLineNode); 
        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
        
}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1742 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("io_statement", "\"Read\" \"(\" ID \")\"", (yylsp[(1) - (4)]).first_line);
        
		(yyval.statement) = new ReadNode( (IdentifierNode*)(yyvsp[(3) - (4)].expression) );
		(yyval.statement)->setFirstLine((yylsp[(1) - (4)]).first_line);

        ::oberonc.addNodeToCleanUpList((yyval.statement)); 
}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1762 "yy_parser.y"
    {
    
        ::oberonc.getParserDebugger()->debugReduction("io_parameter", "parameter", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = (yyvsp[(1) - (1)].expression);
        
}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1768 "yy_parser.y"
    {

        ::oberonc.getParserDebugger()->debugReduction("io_parameter", "STRING_LITERAL", (yylsp[(1) - (1)]).first_line);
        
        (yyval.expression) = new StringLiteralNode((yyvsp[(1) - (1)].str_value));
		(yyval.expression)->setFirstLine((yylsp[(1) - (1)]).first_line);
		
		symbolTable.getStringList()->push_back((string)(yyvsp[(1) - (1)].str_value));
		
        ::oberonc.addNodeToCleanUpList((yyval.expression)); 
		
        
        delete [] (yyvsp[(1) - (1)].str_value);
}
    break;



/* Line 1806 of yacc.c  */
#line 3686 "yy_parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1784 "yy_parser.y"





void yyerror(const char *errmsg)
{
    // Exibe erro.
    printf("\n%s", errmsg);

    // Incrementa número de erros.
    parserErrors++;
}

