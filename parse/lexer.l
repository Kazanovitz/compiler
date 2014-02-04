%option yylineno
%pointer

%{
#include <stdlib.h>
#include <string.h>
#include "parser.hpp"

void yyerror(const char *);
%}

/* 
  WRITE ME: put any definitions you need here.  Add your own regular expressions
            below for ALL tokens defined in the manual. You can choose not to use
	    definitions here.

*/

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
(<=)                    { return *yytext; }          
(return)                { return T_return;}
(true)|(false)          { return T_Bool;}
{type}                  { return T_Type;}
(not)                   { return T_Not;}
(from)                  { return T_From;}
(Nothing)               { return T_Nothing;}
(and)                   { return T_And;}
(print)                 { return T_Print;}
(then)                  { return T_Then;}
(if)                    { return T_If;}
{integer}               { return T_Int;}
{comment}               ;
{Videntifier}           { return T_Vid;}
{Assignment}            { return T_AssVid;}
{Cidentifier}           { return T_Cid;}
{Midentifier}           { return T_Mid;}

[ \t\n]        ; /* skip whitespace */

.              yyerror((char *) "invalid character");

%%


/* You shouldn't need to edit any part of this*/

int yywrap(void) {
	return 1;
}
