%option noyywrap
%{
	#include<stdio.h>
	#include<string.h>
	#include "y.tab.h"
	int line=1;
	int col=1;
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

IDENTIFIER (({LETTER}|_)({DIGIT}|{LETTER}|_)*)

TYPE ("void"|"int"|"double"|"char")
KEYWORD main|return|if|else|else if|for|while|do|switch|case|break|continue|const|static|sizeof|int|unsigned|signed|static|void|auto|struct|union|inline
OPERATOR ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"="|"=="|"!="|"<="|">="|"<"|">"|"+="|"-="|"*="|"/="|"&"|"|"|"!"|"&&"|"||"|"~"|"^"|">>"|"<<"|"?"|":"|"."|"->")
DELIMITER (";"|","|"("|")"|"["|"]"|"{"|"}"|"#")

Annotation (("//".*)|("/*"(([^\*]|\*+[^\/\*])*)\*+"/"))

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

%%

{NEW_LINE} {
	line++;
	col=1;
}
{TAB} {col+=4;}
{ENTER} {col+=yyleng;}
{SPACE}  {col++;}

{IF} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return IF;}
{ELIF} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return ELIF;}
{ELSE} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return ELSE;}
{WHILE} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return WHILE;}
{DO} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return DO;}
{BREAK} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return BREAK;}
{CONTINUE} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return CONTINUE;}
{FOR} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return FOR;}
{RETURN} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return RETURN;}
{MAIN} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MAIN;}

{SWITCH} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return SWITCH;}
{CASE} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return CASE;}
{UNSIGNED} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return UNSIGNED;}
{SIGNED} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return SIGNED;}
{STATIC} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return STATIC;}
{AUTO} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return AUTO;}
{STRUCT} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return STRUCT;}

{AND} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return AND;}
{OR} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return OR;}
{EQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return EQUAL;}
{NOTEQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return NOTEQUAL;}
{LESSEQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return LESSEQUAL;}
{GREATEREQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return GREATEREQUAL;}
{GREATER} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return GREATER;}
{LESS} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return LESS;}

{CONST} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return CONST;}

{PLUS} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return PLUS;}
{MINUS} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MINUS;}
{MULTI} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MULTI;}
{DIVIDE} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return DIVIDE;}
{MOD} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MOD;}
{ASSIGN} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return ASSIGN;}
{BITAND} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return BITAND;}
{BITOR} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return BITOR;}
{BITNOT} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return BITNOT;}
{XOR} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return XOR;}
{NOT} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return NOT;}
{LEFTSHIFT} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return LEFTSHIFT;}
{RIGHTSHIFT} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return RIGHTSHIFT;}
{PLUSPLUS} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return PLUSPLUS;}
{MINUSMINUS} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MINUSMINUS;}
{PLUSEQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return PLUSEQUAL;}
{MINUSEQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MINUSEQUAL;}
{MULTIEQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return MULTIEQUAL;}
{DIVIDEEQUAL} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return DIVIDEEQUAL;}
{COLON} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return COLON;}
{QUESMARK} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return QUESMARK;}
{FULLSTP} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return FULLSTP;}
{PTO} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return PTO;}

{COMMA} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return COMMA;}
{SEMICOLON} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return SEMICOLON;}

{TYPE} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return TYPE;}
{IDENTIFIER} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return IDENTIFIER;}
{CONST_NUM} {col+=yyleng; yylval=++cnt;strcpy(L[cnt], yytext);return CONST_NUM;}
{Annotation} {col+=yyleng;}
. {col+=1; yylval=++cnt;strcpy(L[cnt], yytext);return yytext[0];}
%%

