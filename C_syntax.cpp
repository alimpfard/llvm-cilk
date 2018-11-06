/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */


    #include <cstdio>
    #include <cstdlib>
    #include <iostream>
    #include <map>
    #include "AST_node.h"

    BlockExprNode *root;

    void yyerror(char *) {};
    void yyerror(const char *) {};

    int yylex(void);

    int lineNumber = 1;
    map<string, E_TYPE> varTable;
    void addNewVar(string name, E_TYPE type);
    void setOldVarType(VariableExprNode* var, E_TYPE type);
    string typeStr(E_TYPE type);

    // enclose: 1 unpack, 0 leave unmodified, -1 pack
    void setVarType(VariableExprNode *node, int enclose = 0, R_TYPE plain=R_UNKNOWN);
    E_TYPE checkExprType(ExprNode *lhs, ExprNode *rhs);
    void printVarTable();
    void noSemicolonError();



# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "C_syntax.hpp".  */
#ifndef YY_YY_C_SYNTAX_HPP_INCLUDED
# define YY_YY_C_SYNTAX_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    DOUBLE = 259,
    CHAR = 260,
    VOID = 261,
    AUTO = 262,
    CSTR = 263,
    CINT = 264,
    CDOUBLE = 265,
    CCHAR = 266,
    VAR = 267,
    IF = 268,
    ELSE = 269,
    FOR = 270,
    WHILE = 271,
    LPAREN = 272,
    RPAREN = 273,
    LBRACK = 274,
    RBRACK = 275,
    LBRACE = 276,
    RBRACE = 277,
    EQ = 278,
    NE = 279,
    GR = 280,
    GE = 281,
    LW = 282,
    LE = 283,
    AND = 284,
    OR = 285,
    EQUAL = 286,
    ADD = 287,
    SUB = 288,
    MUL = 289,
    DIV = 290,
    SADD = 291,
    SSUB = 292,
    SMUL = 293,
    SDIV = 294,
    DOT = 295,
    COMMA = 296,
    COLON = 297,
    SEMICOLON = 298,
    EXTERN = 299,
    RETURN = 300,
    SYNC = 301,
    SPAWN = 302,
    COMMENT = 303,
    LOWER_THAN_ELSE = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{


    int token;
    string *stringvalue;
    VariableExprNode *var;
    ExprNode *expr;
    vector<VarDecStatementNode*> *vars;
    vector<ExprNode*> *exprs;
    BlockExprNode *block;
    StatementNode *statement;
    VarDecStatementNode *var_dec;


};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_SYNTAX_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   359

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    76,    77,    80,    81,    82,    83,    84,
      85,    88,    90,    92,    93,    94,    95,    96,    99,   101,
     102,   103,   106,   107,   110,   111,   114,   115,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   156,   157,   158,   161,   162,   165,   166,   169,
     170,   171,   172,   173,   176,   177,   178,   179,   180,   181,
     184,   185,   186,   189,   190,   191
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "DOUBLE", "CHAR", "VOID", "AUTO",
  "CSTR", "CINT", "CDOUBLE", "CCHAR", "VAR", "IF", "ELSE", "FOR", "WHILE",
  "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "EQ", "NE",
  "GR", "GE", "LW", "LE", "AND", "OR", "EQUAL", "ADD", "SUB", "MUL", "DIV",
  "SADD", "SSUB", "SMUL", "SDIV", "DOT", "COMMA", "COLON", "SEMICOLON",
  "EXTERN", "RETURN", "SYNC", "SPAWN", "COMMENT", "LOWER_THAN_ELSE",
  "$accept", "program", "global_block", "global_statement",
  "function_declaration", "extern_function_declaration", "type",
  "variable", "function_args", "block", "variable_declaration",
  "local_block", "local_statement", "expr", "array_declaration",
  "condition", "loop", "const", "compare", "invoke_args", "logic_expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -85

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-85)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     217,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     232,    76,   248,    16,   217,   -85,   -85,     2,    14,   194,
     243,    28,   -85,    13,   282,   -85,   -85,    14,   -85,   -85,
     -85,   -85,     6,   152,   152,    -5,   152,   152,   152,   152,
     -85,   -85,   -85,   -85,   -85,   -85,   152,   152,   152,   152,
     -85,   152,   -85,   -85,   152,   -85,     7,   248,   136,   324,
       9,   311,    14,   324,    78,    78,   -85,   -85,    78,    78,
     -85,   -85,   324,   324,   248,    14,    12,   -85,    35,    26,
     -85,   152,   209,    42,    38,    46,    57,   248,   -85,   138,
     324,   152,   152,   152,   152,   152,   152,   -85,   152,    63,
      72,    99,   171,   -85,   152,    75,   -85,    14,   -85,    39,
     -85,   166,    40,   -85,   -85,   -85,   -85,   152,   324,    78,
      78,   -85,   -85,    58,   324,   152,   152,   152,   125,   -85,
     256,   -85,   102,   -85,   -85,   -85,   -85,   -85,   -85,    65,
     -85,   324,    -9,   269,    93,   -85,   -85,   -85,   -85,    57,
     152,   152,   152,    57,   105,   -85,   -85,   114,   -85,    57,
     152,   -85,   295,    57,   -85
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    13,    14,    15,    16,    17,    69,    70,    71,    18,
       0,     0,     0,     0,     2,     3,     5,     0,     0,    40,
       0,     0,    41,     0,     0,    72,    73,     0,     1,     4,
       7,     6,     0,    80,     0,     0,     0,     0,     0,     0,
      74,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       8,     0,    10,     9,     0,    59,     0,    19,     0,    81,
       0,     0,     0,    51,    46,    47,    48,    49,    42,    43,
      44,    45,    50,    60,    19,     0,     0,    20,     0,     0,
      52,     0,    53,     0,     0,    24,     0,     0,    62,     0,
      82,     0,     0,     0,     0,     0,    80,    12,     0,     0,
       0,     0,     0,    35,     0,     0,    36,     0,    11,     0,
      23,     0,     0,    30,    31,    21,    63,    80,    54,    55,
      56,    57,    58,     0,    25,     0,     0,     0,     0,    26,
       0,    34,    24,    37,    28,    39,    32,    38,    29,     0,
      61,    85,     0,     0,     0,    22,    27,    33,    64,     0,
       0,     0,     0,     0,    65,    84,    83,     0,    68,     0,
       0,    66,     0,     0,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,   -85,   134,   -85,   -85,     1,   -10,    79,   -39,
     -55,   -85,   -84,     0,   101,   -85,   -85,   -85,   -85,   -74,
     -43
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,    17,   107,    19,    76,   108,
     109,   128,   110,   111,   112,   113,   114,    22,    51,    60,
     142
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      20,    18,    77,    30,     6,     7,     8,     9,    32,   149,
      24,    23,    10,    27,    20,    18,    28,    56,   129,    77,
     150,   151,   123,    57,    74,    58,     9,    80,    11,    52,
      86,    54,   115,    59,    61,    63,    64,    65,    66,    67,
     133,   137,    62,   139,   146,    31,    68,    69,    70,    71,
      81,    72,    83,    87,    73,    88,    97,    89,    75,    96,
       1,     2,     3,     4,     5,    85,     6,     7,     8,     9,
      99,    53,   100,   101,    10,    75,   140,    98,   102,    87,
     125,    90,   134,   138,   144,    25,    26,   148,    75,   126,
      11,   118,   119,   120,   121,   122,    59,   132,   124,    81,
     103,    21,   104,   105,   130,   106,    81,   155,   156,   157,
     154,   153,    48,    49,   158,    21,   127,    59,   131,   159,
     161,    58,   150,   151,   164,   141,   143,   141,     1,     2,
       3,     4,     5,    98,     6,     7,     8,     9,    99,     0,
     100,   101,    10,   150,   151,    78,   116,   145,    29,     0,
     141,   141,   141,    84,     0,     0,    79,   160,    11,   117,
     162,     6,     7,     8,     9,     0,     0,   135,   103,    10,
     104,   105,     0,   106,     1,     2,     3,     4,     5,     0,
       6,     7,     8,     9,    99,    11,   100,   101,    10,    40,
      41,    42,    43,    44,    45,     0,     0,     0,    46,    47,
      48,    49,     0,     0,    11,     0,     0,     0,     0,   136,
       0,    33,     0,    34,   103,     0,   104,   105,     0,   106,
       1,     2,     3,     4,     5,    35,     6,     7,     8,     9,
      36,    37,    38,    39,    10,     1,     2,     3,     4,     5,
      91,     6,     7,     8,     9,    92,    93,    94,    95,    10,
      11,     1,     2,     3,     4,     5,     0,     0,     0,     0,
       0,    12,     0,     0,     0,    11,    40,    41,    42,    43,
      44,    45,     0,     0,     0,    46,    47,    48,    49,    40,
      41,    42,    43,    44,    45,     0,    50,     0,    46,    47,
      48,    49,    40,    41,    42,    43,    44,    45,     0,   147,
      55,    46,    47,    48,    49,    40,    41,    42,    43,    44,
      45,     0,   152,   163,    46,    47,    48,    49,    40,    41,
      42,    43,    44,    45,     0,     0,     0,    46,    47,    48,
      49,    82,     0,     0,    40,    41,    42,    43,    44,    45,
       0,     0,     0,    46,    47,    48,    49,    40,    41,    42,
      43,    44,    45,     0,     0,     0,    46,    47,    48,    49
};

static const yytype_int16 yycheck[] =
{
       0,     0,    57,     1,     9,    10,    11,    12,    18,    18,
      10,    10,    17,    12,    14,    14,     0,    27,   102,    74,
      29,    30,    96,    17,    17,    19,    12,    18,    33,     1,
      18,    18,    87,    33,    34,    35,    36,    37,    38,    39,
       1,     1,    47,   117,   128,    43,    46,    47,    48,    49,
      41,    51,    62,    41,    54,    20,    18,    31,    57,    17,
       3,     4,     5,     6,     7,    75,     9,    10,    11,    12,
      13,    43,    15,    16,    17,    74,    18,    31,    21,    41,
      17,    81,    43,    43,   127,     9,    10,    22,    87,    17,
      33,    91,    92,    93,    94,    95,    96,   107,    98,    41,
      43,     0,    45,    46,   104,    48,    41,   150,   151,   152,
     149,    18,    34,    35,   153,    14,    17,   117,    43,    14,
     159,    19,    29,    30,   163,   125,   126,   127,     3,     4,
       5,     6,     7,    31,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    29,    30,     9,     8,    22,    14,    -1,
     150,   151,   152,    74,    -1,    -1,    20,    43,    33,    21,
     160,     9,    10,    11,    12,    -1,    -1,     1,    43,    17,
      45,    46,    -1,    48,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    33,    15,    16,    17,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    32,    33,
      34,    35,    -1,    -1,    33,    -1,    -1,    -1,    -1,    43,
      -1,    17,    -1,    19,    43,    -1,    45,    46,    -1,    48,
       3,     4,     5,     6,     7,    31,     9,    10,    11,    12,
      36,    37,    38,    39,    17,     3,     4,     5,     6,     7,
      31,     9,    10,    11,    12,    36,    37,    38,    39,    17,
      33,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    33,    23,    24,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    33,    34,    35,    23,
      24,    25,    26,    27,    28,    -1,    43,    -1,    32,    33,
      34,    35,    23,    24,    25,    26,    27,    28,    -1,    43,
      18,    32,    33,    34,    35,    23,    24,    25,    26,    27,
      28,    -1,    43,    18,    32,    33,    34,    35,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    33,    34,
      35,    20,    -1,    -1,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    33,    34,    35,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      17,    33,    44,    51,    52,    53,    54,    55,    56,    57,
      63,    64,    67,    56,    63,     9,    10,    56,     0,    53,
       1,    43,    57,    17,    19,    31,    36,    37,    38,    39,
      23,    24,    25,    26,    27,    28,    32,    33,    34,    35,
      43,    68,     1,    43,    18,    18,    57,    17,    19,    63,
      69,    63,    47,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    17,    56,    58,    60,     9,    20,
      18,    41,    20,    57,    58,    57,    18,    41,    20,    31,
      63,    31,    36,    37,    38,    39,    17,    18,    31,    13,
      15,    16,    21,    43,    45,    46,    48,    56,    59,    60,
      62,    63,    64,    65,    66,    60,     8,    21,    63,    63,
      63,    63,    63,    69,    63,    17,    17,    17,    61,    62,
      63,    43,    57,     1,    43,     1,    43,     1,    43,    69,
      18,    63,    70,    63,    70,    22,    62,    43,    22,    18,
      29,    30,    43,    18,    59,    70,    70,    70,    59,    14,
      43,    59,    63,    18,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    54,    55,    56,    56,    56,    56,    56,    57,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    64,    65,    65,    66,    66,    67,
      67,    67,    67,    67,    68,    68,    68,    68,    68,    68,
      69,    69,    69,    70,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     2,     2,
       2,     6,     6,     1,     1,     1,     1,     1,     1,     0,
       1,     3,     3,     1,     2,     4,     1,     2,     2,     2,
       1,     1,     2,     3,     2,     1,     1,     2,     2,     2,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     6,     6,     6,     6,     6,     3,
       4,     7,     5,     6,     8,     5,     7,     9,     5,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       0,     1,     3,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    { root = (yyvsp[0].block); printVarTable(); }

    break;

  case 3:

    { (yyval.block) = new BlockExprNode(); (yyval.block)->statements->push_back((yyvsp[0].statement)); }

    break;

  case 4:

    { (yyval.block)->statements->push_back((yyvsp[0].statement)); }

    break;

  case 5:

    { (yyval.statement) = (yyvsp[0].statement); }

    break;

  case 6:

    { (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 7:

    { noSemicolonError(); (yyval.statement) = (yyvsp[-1].statement);}

    break;

  case 8:

    { (yyval.statement) = new ExprStatementNode((yyvsp[-1].expr)); }

    break;

  case 9:

    { (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 10:

    { noSemicolonError(); (yyval.statement) = ((yyvsp[-1].statement)); }

    break;

  case 11:

    { (yyvsp[-4].var)->_type = (yyvsp[-5].var)->_type; addNewVar((yyvsp[-4].var)->name, E_TYPE{R_FUNC, &(yyvsp[-5].var)->_type}); (yyval.statement) = new FuncDecStatementNode((yyvsp[-5].var), (yyvsp[-4].var), (yyvsp[-2].vars), (yyvsp[0].block)); }

    break;

  case 12:

    { (yyval.statement) = new ExternFuncDecStatementNode((yyvsp[-4].var), (yyvsp[-3].var), (yyvsp[-1].vars)); }

    break;

  case 13:

    { (yyval.var) = new VariableExprNode(*(yyvsp[0].stringvalue), E_INT); delete (yyvsp[0].stringvalue); }

    break;

  case 14:

    { (yyval.var) = new VariableExprNode(*(yyvsp[0].stringvalue), E_DOUBLE); delete (yyvsp[0].stringvalue); }

    break;

  case 15:

    { (yyval.var) = new VariableExprNode(*(yyvsp[0].stringvalue), E_CHAR); delete (yyvsp[0].stringvalue); }

    break;

  case 16:

    { (yyval.var) = new VariableExprNode(*(yyvsp[0].stringvalue), E_VOID); delete (yyvsp[0].stringvalue); }

    break;

  case 17:

    { (yyval.var) = new VariableExprNode(*(yyvsp[0].stringvalue), E_UNKNOWN); delete (yyvsp[0].stringvalue); }

    break;

  case 18:

    { (yyval.var) = new VariableExprNode(*(yyvsp[0].stringvalue)); delete (yyvsp[0].stringvalue); }

    break;

  case 19:

    { (yyval.vars) = new vector<VarDecStatementNode*>(); }

    break;

  case 20:

    { (yyval.vars) = new vector<VarDecStatementNode*>(); (yyval.vars)->push_back((yyvsp[0].var_dec)); }

    break;

  case 21:

    { (yyvsp[-2].vars)->push_back((yyvsp[0].var_dec)); (yyval.vars) = (yyvsp[-2].vars); }

    break;

  case 22:

    { (yyval.block) = (yyvsp[-1].block); }

    break;

  case 23:

    { (yyval.block) = new BlockExprNode(); (yyval.block)->statements->push_back((yyvsp[0].statement)); }

    break;

  case 24:

    { (yyvsp[0].var)->_type = (yyvsp[-1].var)->_type; (yyval.statement) = new VarDecStatementNode((yyvsp[-1].var), (yyvsp[0].var)); addNewVar((yyvsp[0].var)->name, (yyvsp[0].var)->_type);}

    break;

  case 25:

    { (yyvsp[-2].var)->_type = (yyvsp[-3].var)->_type;  addNewVar((yyvsp[-2].var)->name, (yyvsp[-2].var)->_type); setOldVarType((yyvsp[-2].var), ((yyvsp[-3].var)->_type = checkExprType((yyvsp[-2].var), (yyvsp[0].expr)))); (yyval.statement) = new VarDecStatementNode((yyvsp[-3].var), (yyvsp[-2].var), (yyvsp[0].expr));}

    break;

  case 26:

    { (yyval.block) = new BlockExprNode(); (yyval.block)->statements->push_back((yyvsp[0].statement)); }

    break;

  case 27:

    { (yyval.block)->statements->push_back((yyvsp[0].statement)); }

    break;

  case 28:

    { (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 29:

    { (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 30:

    { (yyval.statement) = (yyvsp[0].statement); }

    break;

  case 31:

    { (yyval.statement) = (yyvsp[0].statement); }

    break;

  case 32:

    { (yyval.statement) = new ExprStatementNode((yyvsp[-1].expr)); }

    break;

  case 33:

    { (yyval.statement) = new ReturnStatementNode((yyvsp[-1].expr)); }

    break;

  case 34:

    { (yyval.statement) = new SyncStatementNode(); }

    break;

  case 35:

    { /* NULL */ }

    break;

  case 36:

    { /* NULL */ }

    break;

  case 37:

    { noSemicolonError(); (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 38:

    { noSemicolonError(); (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 39:

    { noSemicolonError(); (yyval.statement) = new ExprStatementNode((yyvsp[-1].expr)); }

    break;

  case 40:

    { (yyval.var) = (yyvsp[0].var); }

    break;

  case 41:

    { (yyval.expr) = (yyvsp[0].expr); }

    break;

  case 42:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr)->_type = checkExprType((yyvsp[-2].expr), (yyvsp[0].expr)); }

    break;

  case 43:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr)->_type = checkExprType((yyvsp[-2].expr), (yyvsp[0].expr)); }

    break;

  case 44:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr)->_type = checkExprType((yyvsp[-2].expr), (yyvsp[0].expr)); }

    break;

  case 45:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr)->_type = checkExprType((yyvsp[-2].expr), (yyvsp[0].expr)); }

    break;

  case 46:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].var), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new AssignExprNode((yyvsp[-2].var), (yyval.expr)); setVarType((yyvsp[-2].var)); (yyval.expr)->_type = checkExprType((yyvsp[-2].var), (yyvsp[0].expr));}

    break;

  case 47:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].var), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new AssignExprNode((yyvsp[-2].var), (yyval.expr)); setVarType((yyvsp[-2].var)); (yyval.expr)->_type = checkExprType((yyvsp[-2].var), (yyvsp[0].expr));}

    break;

  case 48:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].var), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new AssignExprNode((yyvsp[-2].var), (yyval.expr)); setVarType((yyvsp[-2].var)); (yyval.expr)->_type = checkExprType((yyvsp[-2].var), (yyvsp[0].expr));}

    break;

  case 49:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].var), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new AssignExprNode((yyvsp[-2].var), (yyval.expr)); setVarType((yyvsp[-2].var)); (yyval.expr)->_type = checkExprType((yyvsp[-2].var), (yyvsp[0].expr));}

    break;

  case 50:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr)->_type = E_INT; }

    break;

  case 51:

    { (yyval.expr) = new AssignExprNode((yyvsp[-2].var), (yyvsp[0].expr)); setVarType((yyvsp[-2].var)); checkExprType((yyvsp[-2].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-2].var)->_type;}

    break;

  case 52:

    { (yyval.expr) = new FuncExprNode((yyvsp[-3].var), (yyvsp[-1].exprs)); addNewVar((yyvsp[-3].var)->name, E_FUNC); setVarType((yyvsp[-3].var)); (yyval.expr)->_type = (yyvsp[-3].var)->_type;}

    break;

  case 53:

    { (yyval.expr) = new IndexExprNode((yyvsp[-3].var), (yyvsp[-1].expr)); (yyval.expr)->_type = (yyvsp[-3].var)->_type; }

    break;

  case 54:

    { (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr), (yyvsp[0].expr)); checkExprType((yyvsp[-5].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-5].var)->_type; }

    break;

  case 55:

    { (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr)); (yyval.expr) = new OperatorExprNode((yyval.expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr), (yyval.expr)); checkExprType((yyvsp[-5].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-5].var)->_type; }

    break;

  case 56:

    { (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr)); (yyval.expr) = new OperatorExprNode((yyval.expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr), (yyval.expr)); checkExprType((yyvsp[-5].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-5].var)->_type; }

    break;

  case 57:

    { (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr)); (yyval.expr) = new OperatorExprNode((yyval.expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr), (yyval.expr)); checkExprType((yyvsp[-5].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-5].var)->_type; }

    break;

  case 58:

    { (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr)); (yyval.expr) = new OperatorExprNode((yyval.expr), (yyvsp[-1].token), (yyvsp[0].expr)); (yyval.expr) = new IndexExprNode((yyvsp[-5].var), (yyvsp[-3].expr), (yyval.expr)); checkExprType((yyvsp[-5].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-5].var)->_type; }

    break;

  case 59:

    { (yyval.expr) = (yyvsp[-1].expr); }

    break;

  case 60:

    { (yyval.expr) = new CastExprNode((yyvsp[-2].var), (yyvsp[0].expr)); (yyval.expr)->_type = (yyvsp[-2].var)->_type;}

    break;

  case 61:

    { (yyval.expr) = new SpawnExprNode((yyvsp[-6].var), (yyvsp[-3].var), (yyvsp[-1].exprs)); (yyval.expr)->_type = E_TYPE {R_LAZY, &(yyvsp[-3].var)->_type}; addNewVar((yyvsp[-6].var)->name, E_UNKNOWN); }

    break;

  case 62:

    { (yyval.statement) = new ArrayDecStatementNode((yyvsp[-4].var), (yyvsp[-3].var), atol((yyvsp[-1].stringvalue)->c_str())); }

    break;

  case 63:

    { (yyvsp[-4].var)->_type = (yyvsp[-5].var)->_type; (yyval.statement) = new ArrayDecStatementNode((yyvsp[-5].var), (yyvsp[-4].var), *(yyvsp[0].stringvalue)); }

    break;

  case 64:

    { (yyvsp[-6].var)->_type = (yyvsp[-7].var)->_type; (yyval.statement) = new ArrayDecStatementNode((yyvsp[-7].var), (yyvsp[-6].var), (yyvsp[-1].exprs)); }

    break;

  case 65:

    { (yyval.statement) = new IfStatementNode((yyvsp[-2].expr), (yyvsp[0].block)); }

    break;

  case 66:

    { (yyval.statement) = new IfStatementNode((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[0].block)); }

    break;

  case 67:

    { (yyval.statement) = new ForStatementNode((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].block)); }

    break;

  case 68:

    { (yyval.statement) = new WhileStatementNode((yyvsp[-2].expr), (yyvsp[0].block)); }

    break;

  case 69:

    { (yyval.expr) = new IntExprNode(atoi((yyvsp[0].stringvalue)->c_str())); delete (yyvsp[0].stringvalue); }

    break;

  case 70:

    { (yyval.expr) = new DoubleExprNode(atoi((yyvsp[0].stringvalue)->c_str())); delete (yyvsp[0].stringvalue); }

    break;

  case 71:

    { (yyval.expr) = new CharExprNode((yyvsp[0].stringvalue)->front()); delete (yyvsp[0].stringvalue); }

    break;

  case 72:

    { (yyval.expr) = new IntExprNode(-atol((yyvsp[0].stringvalue)->c_str())); delete (yyvsp[0].stringvalue); }

    break;

  case 73:

    { (yyval.expr) = new IntExprNode(-atof((yyvsp[0].stringvalue)->c_str())); delete (yyvsp[0].stringvalue); }

    break;

  case 74:

    { (yyval.token) = (yyvsp[0].token); }

    break;

  case 75:

    { (yyval.token) = (yyvsp[0].token); }

    break;

  case 76:

    { (yyval.token) = (yyvsp[0].token); }

    break;

  case 77:

    { (yyval.token) = (yyvsp[0].token); }

    break;

  case 78:

    { (yyval.token) = (yyvsp[0].token); }

    break;

  case 79:

    { (yyval.token) = (yyvsp[0].token); }

    break;

  case 80:

    { (yyval.exprs) = new vector<ExprNode*>(); }

    break;

  case 81:

    { (yyval.exprs) = new vector<ExprNode*>(); (yyval.exprs)->push_back((yyvsp[0].expr)); }

    break;

  case 82:

    { (yyvsp[-2].exprs)->push_back((yyvsp[0].expr)); (yyval.exprs) = (yyvsp[-2].exprs); }

    break;

  case 83:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); }

    break;

  case 84:

    { (yyval.expr) = new OperatorExprNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr)); }

    break;

  case 85:

    { (yyval.expr) = (yyvsp[0].expr); }

    break;



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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
                      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}



void addNewVar(string name, E_TYPE type) {
  map<string, E_TYPE>::iterator it;
  it = varTable.find(name);
  if (it == varTable.end()) {
    varTable[name] = type;
  } else if (type.plain == R_FUNC) {
    if (it->second.enclosing && it->second.enclosing->plain == R_UNKNOWN)
      varTable[name] = type;
    else
      cout << "line " << lineNumber << ": refusing to redeclare a function from (" << typeStr(it->second) << ") to (" << typeStr(type) << ")." << endl;
  } else {
    cout << "line " << lineNumber << ": redefinition of variable " << name << " from (" << typeStr((*it).second) << ") to (" << typeStr(type) << ")." << endl;
    varTable[name] = type;
  }
}

void setOldVarType(VariableExprNode* var, E_TYPE type) {
    map<string, E_TYPE>::iterator it;
    it = varTable.find(var->name);
    varTable[var->name] = type;
    var->_type = type;
}

string typeStr(E_TYPE type) {
    switch (type.plain) {
    case R_VOID:
        return "void";
    case R_INT:
        return "int";
    case R_CHAR:
        return "char";
    case R_DOUBLE:
        return "double";
    case R_PTR:
        return "pointer";
    case R_FUNC:
        return "function part returning " + typeStr(type.enclosing?*type.enclosing:E_UNKNOWN);
    default:
        return "unknown";
    }
}

E_TYPE checkExprType(ExprNode *lhs, ExprNode *rhs) {
  if (lhs->_type == E_UNKNOWN) {
    cout << "line " << lineNumber << ": unknown expression type on lhs" << endl;
    if (rhs->_type == E_UNKNOWN)
      return E_INT;
    else
      return rhs->_type;
  }
  if (rhs->_type == E_UNKNOWN) {
    cout << "line " << lineNumber << ": unknown expression type on rhs" << endl;
    return E_INT; // C's default
  }
  E_TYPE i, j;
  i = (int)lhs->_type > (int)rhs->_type ? rhs->_type : lhs->_type;   // smaller one
  j = (int)lhs->_type < (int)rhs->_type ? rhs->_type : lhs->_type;   // bigger one

  if (j == E_FUNC) {
    return i;
  }
  if (i != j) {
    cout << "line " << lineNumber << ": implicitly convert type " << typeStr(i) << " to " << typeStr(j) << "." << endl;
  }
  return j;
}

void noSemicolonError() {
  cout << "line " << lineNumber << ": missed Semicolon." << endl;
}

void setVarType(VariableExprNode *var, int enclose, R_TYPE plain){
  map<string, E_TYPE>::iterator it;
  it = varTable.find(var->name);
  if (it == varTable.end()) {
    var->_type = E_UNKNOWN;
  } else {
    var->_type = (*it).second;
    if (enclose == -1)
      var->_type = E_TYPE {plain, var->_type.enclosing};
    if (enclose == 1)
      var->_type = *var->_type.enclosing;
  }
 }


void printVarTable() {
  std::map<std::string, E_TYPE>::iterator it;
  for (it = varTable.begin(); it != varTable.end(); it++) {
    cout << (*it).first << " : " << typeStr((*it).second) << std::endl;
  }
}
