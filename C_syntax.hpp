/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

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
