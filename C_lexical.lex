%{
    #include <string>
    #include <iostream>
    #include "AST_node.h"
    #include "C_syntax.hpp"
    #define TOKEN(t)    (yylval.token = t)
    extern int lineNumber;
%}

%option noyywrap

%%

"extern"                        return TOKEN(EXTERN);
"return"                        return TOKEN(RETURN);

"int"                           { yylval.stringvalue = new string(yytext, yyleng); return INT; }
"double"                        { yylval.stringvalue = new string(yytext, yyleng); return DOUBLE; }
"char"                          { yylval.stringvalue = new string(yytext, yyleng); return CHAR; }
"void"                          { yylval.stringvalue = new string(yytext, yyleng); return VOID; }
"auto"                          { yylval.stringvalue = new string(yytext, yyleng); return AUTO; }

"if"                            return TOKEN(IF);
"else"                          return TOKEN(ELSE);
"for"                           return TOKEN(FOR);
"while"                         return TOKEN(WHILE);

"sync"                          return TOKEN(SYNC);
"spawn"                         return TOKEN(SPAWN);
\/\/.*$                         return TOKEN(COMMENT);

["].*["]                        {
                                    yylval.stringvalue = new string(yytext, yyleng);
                                    yylval.stringvalue->erase(yylval.stringvalue->begin());
                                    yylval.stringvalue->erase(yylval.stringvalue->end() - 1);
                                    return CSTR;
                                }
[_A-Za-z][_0-9A-Za-z]*          { yylval.stringvalue = new string(yytext, yyleng); return VAR; }
[0-9]+                          { yylval.stringvalue = new string(yytext, yyleng); return CINT; }
[0-9]+\.[0-9]*                  { yylval.stringvalue = new string(yytext, yyleng); return CDOUBLE; }
['].[']                         {
                                    yylval.stringvalue = new string(yytext, yyleng);
                                    yylval.stringvalue->erase(yylval.stringvalue->begin());
                                    yylval.stringvalue->erase(yylval.stringvalue->end() - 1);
                                    return CCHAR;
                                }

"("                             return TOKEN(LPAREN);
")"                             return TOKEN(RPAREN);
"["                             return TOKEN(LBRACK);
"]"                             return TOKEN(RBRACK);
"{"                             return TOKEN(LBRACE);
"}"                             return TOKEN(RBRACE);

"="                             return TOKEN(EQUAL);

"=="                            return TOKEN(EQ);
"!="                            return TOKEN(NE);
">"                             return TOKEN(GR);
">="                            return TOKEN(GE);
"<"                             return TOKEN(LW);
"<="                            return TOKEN(LE);

"&&"                            return TOKEN(AND);
"||"                            return TOKEN(OR);


"+"                             return TOKEN(ADD);
"-"                             return TOKEN(SUB);
"*"                             return TOKEN(MUL);
"/"                             return TOKEN(DIV);

"+="                            return TOKEN(SADD);
"-="                            return TOKEN(SSUB);
"*="                            return TOKEN(SMUL);
"/="                            return TOKEN(SDIV);

"."                             return TOKEN(DOT);
","                             return TOKEN(COMMA);
":"                             return TOKEN(COLON);
";"                             return TOKEN(SEMICOLON);

[ \t\r]*                        ;

"\n"                            lineNumber += 1;

^"#include ".+                  ;

.                               cout << "Unknown token! " << yytext << endl; yyterminate();

%%
