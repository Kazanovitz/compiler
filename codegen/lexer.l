%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <string.h>
    #include "ast.hpp"
    #include "primitive.hpp"
    #include "symtab.hpp"
    #include "classhierarchy.hpp"
    #include "parser.hpp"
    
    void yyerror(const char *);
%}

/* Put your definitions here, if you have any */

integer           0|[1-9][0-9]*

negative          [\-][1-9][0-9]*

symbols         [\+\-\.\{\}\:\;\,\(\)\=\-\*\<\/]

Cidentifier       [A-Z][A-Za-z0-9_]*

Midentifier       [a-z_][A-Za-z0-9_]*\(

Videntifier       [a-z_][A-Za-z0-9_]*

Assignment        [a-z_][A-Za-z0-9_]*[ \t]*[\=]

comments           [\/\*(?!\*\/)\d{2} \*\/] 

comment           \/\*([^*]|\*[^/])*\*+\/

type              (Bool|Int)
/*
Videntifier

type

Rtype
*/



/*
  The example below is very simple, but it shows almost everything you will need
  to do for this first part.

  The syntax is as follows:

  regular_expression      {  c code  }

  The lexer will try to match each regular expression.  When it does it will execute
  the c code.
*/

%%

{symbols}               { return *yytext; }
(<=)                    { yylval.u_base_charptr = strdup(yytext); return T_Loet; }          
(return)                { return T_return;}
(true)          		{ yylval.u_base_charptr = strdup(yytext); return T_BoolT;}
(false)         		 { yylval.u_base_charptr = strdup(yytext); return T_BoolF;}

(Bool)                  { yylval.u_base_charptr = strdup(yytext); return T_Boolean;}
(Int)                  { yylval.u_base_charptr = strdup(yytext); return T_Integer;}

(not)                   { yylval.u_base_charptr = strdup(yytext); return T_Not;}
(from)                  { yylval.u_base_charptr = strdup(yytext); return T_From;}
(Nothing)               { yylval.u_base_charptr = strdup(yytext); return T_Nothing;}
(and)                   { yylval.u_base_charptr = strdup(yytext); return T_And;}
(print)                 { yylval.u_base_charptr = strdup(yytext); return T_Print;}
(then)                  { yylval.u_base_charptr = strdup(yytext); return T_Then;}
(if)                    { yylval.u_base_charptr = strdup(yytext); return T_If;}
{integer}               { yylval.u_base_int = atoi(yytext); return T_Int;}
{comment}               ;
{Videntifier}           { yylval.u_base_charptr = strdup(yytext); return T_Vid;}
{Assignment}            { char* h = strtok(yytext, " =");yylval.u_base_charptr = strdup(h); return T_AssVid;}
{Cidentifier}           {yylval.u_base_charptr = strdup(yytext); return T_Cid;}
{Midentifier}           { char* h = strtok(yytext, " (");yylval.u_base_charptr = strdup(h); return T_Mid;}


[ \t\n]                   ; /* Put your rules with attached Lexer actions here. */

.                         { yyerror("invalid character"); }

%%

int yywrap(void) {
    return 1;
}
