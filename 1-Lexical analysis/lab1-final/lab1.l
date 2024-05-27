%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
int i = 0;
int num_lines = 1; //行
int num_cols = 1;  //列
%}

NEW_LINE "\n"
TAB "\t"
SPACE " "
LETTER [A-Za-z]
digit [0-9]
POS_digit [1-9]

OCT_digit [0-7]
OCT_pre 0
OCT_INTEGER ({OCT_pre}{OCT_digit}*)

HEX_digit [0-9a-fA-F]
HEX_pre 0x|0X
HEX_INTEGER ({HEX_pre}{HEX_digit}+)

INTEGER (({POS_digit}{digit}*)|0)


CONST_NUM ({INTEGER}|{HEX_INTEGER}|{OCT_INTEGER})

IDENTIFIER (({LETTER}|_)({digit}|{LETTER}|_)*)
KEYWORD main|return|if|else|for|while|do|switch|case|break|continue|const|static|sizeof|int|unsigned|signed|static|void|auto|struct|union|inline
OPERATOR ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"="|"=="|"!="|"<="|">="|"<"|">"|"+="|"-="|"*="|"/="|"&"|"|"|"!"|"&&"|"||"|"~"|"^"|">>"|"<<"|"?"|":"|"."|"->")
DELIMITER (";"|","|"("|")"|"["|"]"|"{"|"}"|"#")

Annotation_Single_Line (("//")(.*))
Annotation_Paragraph ("/*"(([^\*]|\*+[^\/\*])*)\*+"/")


%%

{NEW_LINE} {
    ++num_lines;
    num_cols = 1;
}
{TAB} {num_cols += 4;}
{SPACE} { num_cols++;}

{KEYWORD} { 
    printf("%s: K, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols += yyleng;
}
{IDENTIFIER} { 
    printf("%s: I, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols += yyleng;
}
{CONST_NUM} { 
    printf("%s: C, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols += yyleng;
}
{OPERATOR} { 
    printf("%s: O, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols += yyleng;
}
{DELIMITER} { 
    printf("%s: D, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols += yyleng;
}
{Annotation_Single_Line} {
    printf("%s: T, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols += yyleng;
}
{Annotation_Paragraph} {
    printf("%s: T, (%d, %d)\n", yytext, num_lines, num_cols);
    while(i < yyleng)
    {
        if(yytext[i] == '\n') //换行符
        {
            num_lines++;
            num_cols = 1;
        }
        else if(yytext[i] == '\t') //tab
        {
            num_cols += 4;
        }
        else //其他注释语句
        {
            num_cols++;
        }
        i++;
    }
}
. {
    printf("%s: T, (%d, %d)\n", yytext, num_lines, num_cols);
    num_cols++;
}

%%
int main(int argc, char *argv[]) {
    yyin = stdin;
    yylex();
    return 0;
}