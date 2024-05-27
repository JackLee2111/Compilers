%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"

    int line = 1;
    int col = 1;
    extern int cnt;
    extern char L[100000][50];
%}
NEW_LINE "\n"
TAB "\t"
SPACE " "
ENTER "\r"

LETTER [a-zA-Z]
DIGIT [0-9]
POS_DIGIT [1-9]
INTEGER (({POS_DIGIT}{DIGIT}*)|0)

FLOAT [1-9]([0-9])*"."[0-9]+([Ee]+[+-]?[0-9]+)?

OCT_digit [0-7]
OCT_pre 0
OCT_INTEGER ({OCT_pre}{OCT_digit}*)

HEX_digit [0-9a-fA-F]
HEX_pre 0x|0X
HEX_INTEGER ({HEX_pre}{HEX_digit}+)

DECIMAL {INTEGER}("."{DIGIT}*)?
CONST_NUM ({FLOAT}|{DECIMAL}|{OCT_INTEGER}|{HEX_INTEGER}|{INTEGER}|{DIGIT})
BORDER		[\(\)\{\}\"\'\[\]\;\,]

IDENTIFIER (({LETTER}|_)({DIGIT}|{LETTER}|_)*)
AfterNumber	({OPERATOR}|{BORDER}|" "|\n|\t|\v|\r|\f)

RETURN "return" 
MAIN "main" 
IF "if"
ELIF "else if"
ELSE "else"
FOR "for" 
WHILE "while"
DO "do" 
BREAK "break"
CONTINUE "continue" 

SWITCH "switch"
CASE "case"
UNSIGNED "unsigned"
SIGNED "signed"
STATIC "static"
AUTO "auto"
STRUCT "struct"

INT "int"
VOID "void"
CONST "const"

AND "&&"
OR "||" 

EQUAL "=="
NOTEQUAL "!=" 
LESSEQUAL "<=" 
GREATEREQUAL ">=" 
GREATER ">" 
LESS "<"

PLUS "+"
MINUS "-"
MULTI "*"
DIVIDE "/"
MOD "%"
ASSIGN "="
BITAND "&"
BITOR "|"
BITNOT "!"
XOR "^"
NOT "~"
LEFTSHIFT "<<"
RIGHTSHIFT ">>"
PLUSPLUS "++"
MINUSMINUS "--"
PLUSEQUAL "+="
MINUSEQUAL "-="
MULTIEQUAL "*="
DIVIDEEQUAL "/="
COLON ":"
QUESMARK "?"
FULLSTP "."
PTO "->"

COMMA ","
SEMICOLON ";"

TYPE ("void"|"int"|"double"|"char")
KEYWORD main|return|if|else|else if|for|while|do|switch|case|break|continue|const|static|sizeof|int|unsigned|signed|static|void|auto|struct|union|inline
OPERATOR ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"="|"=="|"!="|"<="|">="|"<"|">"|"+="|"-="|"*="|"/="|"&"|"|"|"!"|"&&"|"||"|"~"|"^"|">>"|"<<"|"?"|":"|"."|"->")
DELIMITER (";"|","|"("|")"|"["|"]"|"{"|"}"|"#")

OTHER  [^ \n\t\v\r\f\(\)\{\}\"\'\[\]\;\,\"\'\+\-\*\/\%\<\>\=\&\|\!\^]

Annotation_begin 	"/*"
Annotation_end	"*/"
line_Annotation_begin 	"//"
line_Annotation_end 	\n
%x 		NOTE
%x 		LINENOTE


%%
{IF}		{col += yyleng; yylval = ++cnt; return IF;}
{ELSE} 		{col += yyleng; yylval = ++cnt; return ELSE;}
{WHILE}		{col += yyleng; yylval = ++cnt; return WHILE;}
{CONTINUE} 	{col += yyleng; yylval = ++cnt; return CONTINUE;}
{BREAK}		{col += yyleng; yylval = ++cnt; return BREAK;}
{RETURN} 	{col += yyleng; yylval = ++cnt; return RETURN;}
{CONST} 	{col += yyleng; yylval = ++cnt; return CONST;}
{INT}		{col += yyleng; yylval = ++cnt; return INT;}
{VOID}		{col += yyleng; yylval = ++cnt; return VOID;}
{MAIN}  	{col += yyleng; yylval = ++cnt; return MAIN;}

"+"		{col += yyleng; yylval = ++cnt; return '+';}
"-"		{col += yyleng; yylval = ++cnt; return '-';}
"*"		{col += yyleng; yylval = ++cnt; return '*';}
"/"		{col += yyleng; yylval = ++cnt; return '/';}
"%"		{col += yyleng; yylval = ++cnt; return '%';}
"<"		{col += yyleng; yylval = ++cnt; return '<';}
">"		{col += yyleng; yylval = ++cnt; return '>';}
"!"		{col += yyleng; yylval = ++cnt; return '!';}
"="		{col += yyleng; yylval = ++cnt; return '=';}

"<="		{col += yyleng; yylval = ++cnt; return LESSEQUAL;}
">="		{col += yyleng; yylval = ++cnt; return GREATEREQUAL;}
"=="		{col += yyleng; yylval = ++cnt; return EQUAL;}
"!="		{col += yyleng; yylval = ++cnt; return NOTEQUAL;}
"&&"		{col += yyleng; yylval = ++cnt; return AND;}
"||"		{col += yyleng; yylval = ++cnt; return OR;}

"("		{col += yyleng; yylval = ++cnt; return '(';}
")"		{col += yyleng; yylval = ++cnt; return ')';}
"{"		{col += yyleng; yylval = ++cnt; return '{';}
"}"		{col += yyleng; yylval = ++cnt; return '}';}
"["		{col += yyleng; yylval = ++cnt; return '[';}
"]"		{col += yyleng; yylval = ++cnt; return ']';}
";"		{col += yyleng; yylval = ++cnt; return ';';}
","		{col += yyleng; yylval = ++cnt; return ',';}

{IDENTIFIER} 	{col += yyleng; yylval = ++cnt; strcpy(L[cnt], yytext); return ID;}
{CONST_NUM}	{col += yyleng; yylval = atoi(yytext); strcpy(L[cnt], yytext); return CONST_NUM;}

{NEW_LINE} {
	line++;
	col=1;
}
{TAB} {col+=8;}
{ENTER} {col+=yyleng;}
{SPACE}  {col++;}

{Annotation_begin} 			{BEGIN NOTE; col += yyleng;}
<NOTE>\n			{++line; col = 1;}
<NOTE>\t			{col += 8;}
<NOTE>. 			{col += yyleng;}
<NOTE>{Annotation_end} 		{BEGIN INITIAL; col += yyleng;}
{line_Annotation_begin} 		{BEGIN LINENOTE;}
<LINENOTE>. 			{}
<LINENOTE>{line_Annotation_end} 	{BEGIN INITIAL; ++line; col=1;}

{OTHER}*	{col += yyleng; return OTHER;}
. {col+=1; yylval=++cnt;strcpy(L[cnt], yytext);return yytext[0];}
%%
