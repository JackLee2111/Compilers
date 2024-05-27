%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "y.tab.h"

    extern int yylex(void); 
    extern int yyparse(void); 
    extern int col, line;
    extern char *yytext;

    FILE *ft, *fd;

    int cnt = 0;
    int sum = 0;
    char L[100000][50];

    int yywrap()
    {
        return 1;
    }

    void yyerror(const char *s)
    {
        printf("[error] %s", s);
        printf(" (%d, %d): \"%s\"\n", line, col, yytext);
    }

    int main(int argc, char *argv[])
    {
        freopen (argv[1], "r", stdin);
        yyparse();
        return 0;
    }
%}

%start CompUnit
%token IDENTIFIER 
%token CONST_NUM
%token MAIN
%token TYPE

%token IF 
%token ELSE 
%token ELIF 
%token WHILE 
%token DO 
%token BREAK 
%token CONTINUE 
%token FOR 
%token RETURN
%token AND 
%token OR 
%token EQUAL 
%token NOTEQUAL 
%token LESS 
%token LESSEQUAL 
%token GREATER 
%token GREATEREQUAL

%token SWITCH
%token CASE
%token UNSIGNED 
%token SIGNED 
%token STATIC 
%token AUTO 
%token STRUCT 

%token CONST

%token PLUS
%token MINUS 
%token MULTI 
%token DIVIDE 
%token MOD 
%token ASSIGN
%token BITAND
%token BITOR 
%token BITNOT 
%token XOR 
%token NOT 
%token LEFTSHIFT 
%token RIGHTSHIFT 
%token PLUSPLUS 
%token MINUSMINUS 
%token PLUSEQUAL 
%token MINUSEQUAL 
%token MULTIEQUAL 
%token DIVIDEEQUAL 
%token COLON 
%token QUESMARK 
%token FULLSTP 
%token PTO 

%token COMMA
%token SEMICOLON

%left MINUS PLUS
%left MULTI DIVIDE
%left ELSE 

%%
CompUnit: 
    OtherCompUnit { 
        $$ = ++cnt;
        strcpy(L[$$], "CompUnit");
        printf ("%d:CompUnit -> %d:OtherCompUnit\n", $$, $1);
    }
    | CompUnit OtherCompUnit { 
        $$ = ++cnt;
        strcpy(L[$$], "CompUnit");
        printf ("%d:CompUnit -> %d:CompUnit %d:OtherCompUnit\n", $$, $1, $2);
    }
;
OtherCompUnit:
    Decl { 
        $$ = ++cnt;
        strcpy(L[$$], "OtherCompUnit");
        printf ("%d:OtherCompUnit -> %d:Decl\n", $$, $1);
    }
    | FuncDef { 
        $$ = ++cnt;
        strcpy(L[$$], "OtherCompUnit");
        printf ("%d:OtherCompUnit -> %d:FuncDef\n", $$, $1);
    }
;
FuncDef:
    TYPE MAIN '(' ')' Block { 
        $$ = ++cnt;
        strcpy(L[$$], "FuncDef");
        printf ("%d:FuncDef -> %d:%s %d:main %d:\\( %d:\\) %d:Block\n", $$, $1, L[$1], $2, $3, $4, $5);
    }
    | TYPE IDENTIFIER '(' ')' Block { 
        $$ = ++cnt;
        strcpy(L[$$], "FuncDef");
        printf ("%d:FuncDef -> %d:%s %d:%s %d:\\( %d:\\) %d:Block\n", $$, $1, L[$1], $2, L[$2], $3, $4, $5);
    }
    | TYPE IDENTIFIER '(' FuncFParams ')' Block { 
        $$ = ++cnt;
        strcpy(L[$$], "FuncDef");
        printf ("%d:FuncDef -> %d:%s %d:%s %d:\\( %d:FuncFParams %d:\\) %d:Block\n", $$, $1, L[$1], $2, L[$2], $3, $4, $5, $6);
    }
;
FuncFParam:
    TYPE IDENTIFIER {
        $$ = ++cnt;
        strcpy(L[$$], "FuncFParam");
        printf ("%d:FuncFParam -> %d:%s %d:%s\n", $$, $1, L[$1], $2, L[$2]);
    }
    | TYPE IDENTIFIER ConstArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "FuncFParam");
        printf ("%d:FuncFParam -> %d:%s %d:%s %d:ConstArrayIndex\n", $$, $1, L[$1], $2, L[$2], $3);
    }
;
FuncFParams:
    FuncFParam {
        $$ = ++cnt;
        strcpy(L[$$], "FuncFParams");
        printf ("%d:FuncFParams -> %d:FuncFParam\n", $$, $1);
    }
    | FuncFParam COMMA FuncFParams {
        $$ = ++cnt;
        strcpy(L[$$], "FuncFParams");
        printf ("%d:FuncFParams -> %d:FuncFParam %d:\\, %d:FuncFParams\n", $$, $1, $2, $3);
    }
;
Stmt:
    LVal ConstArrayIndex SEMICOLON {
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:LVal %d:ConstArrayIndex %d:\\;\n", $$, $1, $2, $3);
    }
    | IfBlock { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:IfBlock\n", $$, $1);
    }
    | IfBlock ELSE StmtOrBlock { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:IfBlock %d:else %d:StmtOrBlock\n", $$, $1, $2, $3);
    }
    | WHILE '(' Cond ')' StmtOrBlock { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:while %d:\\( %d:Cond %d:\\) %d:StmtOrBlock\n", $$, $1, $2, $3, $4, $5);
    }
    | DO Block WHILE '(' Cond ')' { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:do %d:Block %d:while %d:\\( %d:Cond %d:\\)\n", $$, $1, $2, $3, $4, $5);
    }
    | FOR '(' Cond ')' StmtOrBlock { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:for %d:\\( %d:Cond %d:\\) %d:StmtOrBlock\n", $$, $1, $2, $3, $4, $5);
    }
    | RETURN SEMICOLON { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:return %d:\\;\n", $$, $1, $2);
    }
    | RETURN AddExp SEMICOLON { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:return %d:AddExp %d:\\;\n", $$, $1, $2, $3);
    }
    | BREAK SEMICOLON { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:break %d:\\;\n", $$, $1, $2);
    }
    | CONTINUE SEMICOLON { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:continue %d:\\;\n", $$, $1, $2);
    }
    | AddExp SEMICOLON { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:Stmt -> %d:AddExp %d:\\;\n", $$, $1, $2);
    }
;
StmtOrBlock:
    Stmt {
        $$ = ++cnt;
        strcpy(L[$$], "StmtOrBlock");
        printf ("%d:StmtOrBlock -> %d:Stmt\n", $$, $1);
    }
    | Block {
        $$ = ++cnt;
        strcpy(L[$$], "StmtOrBlock");
        printf ("%d:StmtOrBlock -> %d:Block\n", $$, $1);
    }
;
IfBlock:
    IF '(' Cond ')' StmtOrBlock { 
        $$ = ++cnt;
        strcpy(L[$$], "Stmt");
        printf ("%d:IfBlock -> %d:if %d:\\( %d:Cond %d:\\) %d:StmtOrBlock\n", $$, $1, $2, $3, $4, $5);
    }
;
Block:
    '{' BlockItem '}' { 
        $$ = ++cnt;
        strcpy(L[$$], "Block");
        printf ("%d:Block -> %d:\\{ %d:BlockItem %d:\\}\n", $$, $1, $2, $3);
    }
;
BlockItem:
    Stmt BlockItem {
        $$ = ++cnt;
        strcpy(L[$$], "BlockItem");
        printf ("%d:BlockItem -> %d:Stmt %d:BlockItem\n", $$, $1, $2);
    }
    | Decl BlockItem { 
        $$ = ++cnt;
        strcpy(L[$$], "BlockItem");
        printf ("%d:BlockItem -> %d:Decl %d:BlockItem\n", $$, $1, $2);
    }
    | Stmt {
        $$ = ++cnt;
        strcpy(L[$$], "BlockItem");
        printf ("%d:BlockItem -> %d:Stmt\n", $$, $1);
    }
    | Decl { 
        $$ = ++cnt;
        strcpy(L[$$], "BlockItem");
        printf ("%d:BlockItem -> %d:Decl\n", $$, $1);
    }
;
Decl:
    VarDecl COMMA SeqVarDecl { 
        $$ = ++cnt;
        strcpy(L[$$], "Decl");
        printf ("%d:Decl -> %d:VarDecl %d:\\, %d:SeqVarDecl\n", $$, $1, $2, $3);
    }
    | VarDecl SEMICOLON { 
        $$ = ++cnt;
        strcpy(L[$$], "Decl");
        printf ("%d:Decl -> %d:VarDecl %d:\\;\n", $$, $1, $2);
    }
;
VarDecl:
    CONST TYPE IDENTIFIER ConstArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s %d:%s %d:ConstArrayIndex\n", $$, $1, L[$1], $2, L[$2], $3, L[$3], $4);
    }
    | CONST TYPE IDENTIFIER {
        $$ = ++cnt;
        strcpy(L[$$], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s %d:%s\n", $$, $1, L[$1], $2, L[$2], $3, L[$3]);
    }
    | TYPE IDENTIFIER {
        $$ = ++cnt;
        strcpy(L[$$], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s\n", $$, $1, L[$1], $2, L[$2]);
    }
    | TYPE IDENTIFIER ConstArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s %d:ConstArrayIndex\n", $$, $1, L[$1], $2, L[$2], $3);
    }
;
SeqVarDecl:
    IDENTIFIER ConstArrayIndex COMMA SeqVarDecl {
        $$ = ++cnt;
        strcpy(L[$$], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:ConstArrayIndex %d:\\, %d:SeqVarDecl\n", $$, $1, L[$1], $2, $3, $4);
    }
    | IDENTIFIER COMMA SeqVarDecl {
        $$ = ++cnt;
        strcpy(L[$$], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:\\, %d:SeqVarDecl\n", $$, $1, L[$1], $2, $3);
    }
    | IDENTIFIER ConstArrayIndex SEMICOLON {
        $$ = ++cnt;
        strcpy(L[$$], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:ConstArrayIndex %d:\\;\n", $$, $1, L[$1], $2, $3);
    }
    | IDENTIFIER SEMICOLON {
        $$ = ++cnt;
        strcpy(L[$$], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:\\;\n", $$, $1, L[$1], $2);
    }
;

ConstArrayIndex:
    ASSIGN AddExp {
        $$ = ++cnt;
        strcpy(L[$$], "ConstArrayIndex");
        printf ("%d:ConstArrayIndex -> %d:\\= %d:AddExp\n", $$, $1, $2);
    }
    | ArrayIndex ASSIGN AddExp {
        $$ = ++cnt;
        strcpy(L[$$], "ConstArrayIndex");
        printf ("%d:ConstArrayIndex -> %d:ArrayIndex %d:\\= %d:AddExp\n", $$, $1, $2, $3);
    }
    | ArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "ConstArrayIndex");
        printf ("%d:ConstArrayIndex -> %d:ArrayIndex\n", $$, $1);
    }
;
ArrayIndex:
    '[' AddExp ']' {
        $$ = ++cnt;
        strcpy(L[$$], "ArrayIndex");
        printf ("%d:ArrayIndex -> %d:\\[ %d:AddExp %d:\\]\n", $$, $1, $2, $3);
    }
    | '[' ']' ArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "ArrayIndex");
        printf ("%d:ArrayIndex -> %d:\\[ %d:\\] %d:ArrayIndex\n", $$, $1, $2, $3);
    }
    | '[' AddExp ']' ArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "ArrayIndex");
        printf ("ArrayIndex -> %d:\\[ %d:AddExp %d:\\] %d:ArrayIndex\n", $$, $1, $2, $3, $4);
    }
    | '[' ']' {
        $$ = ++cnt;
        strcpy(L[$$], "ArrayIndex");
        printf ("%d:ArrayIndex -> %d:\\[ %d:\\]\n", $$, $1, $2);
    }
;
AddExp:
    AddExp PLUS MulExp { 
        $$ = ++cnt;
        strcpy(L[$$], "AddExp");
        printf ("%d:AddExp -> %d:AddExp %d:\\+ %d:MulExp\n", $$, $1, $2, $3);
    }
    | AddExp MINUS MulExp { 
        $$ = ++cnt;
        strcpy(L[$$], "AddExp");
        printf ("%d:AddExp -> %d:AddExp %d:\\- %d:MulExp\n", $$, $1, $2, $3);
    }
    | MulExp { 
        $$ = ++cnt;
        strcpy(L[$$], "AddExp");
        printf ("%d:AddExp -> %d:MulExp\n", $$, $1);
    }
;
MulExp:
    MulExp MULTI UnaryExp { 
        $$ = ++cnt;
        strcpy(L[$$], "MulExp");
        printf ("%d:MulExp -> %d:MulExp %d:\\* %d:UnaryExp\n", $$, $1, $2, $3);
    }
    | MulExp DIVIDE UnaryExp { 
        $$ = ++cnt;
        strcpy(L[$$], "MulExp");
        printf ("%d:MulExp -> %d:MulExp %d:\\/ %d:UnaryExp\n", $$, $1, $2, $3);
    }
    | UnaryExp { 
        $$ = ++cnt;
        strcpy(L[$$], "MulExp");
        printf ("%d:MulExp -> %d:UnaryExp\n", $$, $1);
    }
;
PrimaryExp:
    LVal { 
        $$ = ++cnt;
        strcpy(L[$$], "PrimaryExp");
        printf ("%d:PrimaryExp -> %d:LVal\n", $$, $1);
    } 
    | CONST_NUM { 
        $$ = ++cnt;
        strcpy(L[$$], "PrimaryExp");
        printf ("%d:PrimaryExp -> %d:%s\n", $$, $1, L[$1]);
    } 
;
UnaryExp:
    PrimaryExp { 
        $$ = ++cnt;
        strcpy(L[$$], "UnaryExp");
        printf ("%d:UnaryExp -> %d:PrimaryExp\n", $$, $1);
    }
    | IDENTIFIER '(' ')' { 
        $$ = ++cnt;
        strcpy(L[$$], "UnaryExp");
        printf ("%d:UnaryExp -> %d:%s %d:\\( %d:)\n", $$, $1, L[$1], $2, $3);
    }
    | IDENTIFIER '(' FuncRParams ')' { 
        $$ = ++cnt;
        strcpy(L[$$], "UnaryExp");
        printf ("%d:UnaryExp -> %d:%s %d:\\( %d:FuncRParams %d:\\)\n", $$, $1, L[$1], $2, $3, $4);
    }
;
LOrExp:
    LAndExp { 
        $$ = ++cnt;
        strcpy(L[$$], "LOrExp");
        printf ("%d:LOrExp -> %d:LAndExp\n", $$, $1);
    }
    | LOrExp OR LAndExp { 
        $$ = ++cnt;
        strcpy(L[$$], "LOrExp");
        printf ("%d:LOrExp -> %d:LOrExp %d:\\|\\| %d:LAndExp\n", $$, $1, $2, $3);
    }
;
Cond:
    LOrExp { 
        $$ = ++cnt;
        strcpy(L[$$], "Cond");
        printf ("%d:Cond -> %d:LOrExp\n", $$, $1);
    }
;
LAndExp:
    CompExp { 
        $$ = ++cnt;
        strcpy(L[$$], "LAndExp");
        printf ("%d:LAndExp -> %d:CompExp\n", $$, $1);
    }
    | LAndExp AND CompExp { 
        $$ = ++cnt;
        strcpy(L[$$], "LAndExp");
        printf ("%d:LAndExp -> %d:LAndExp %d:\\&\\& %d:CompExp\n", $$, $1, $2, $3);
    }
;
CompExp:
    CompExp GREATER RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\> %d:RelExp\n", $$, $1, $2, $3);
    }
    | CompExp LESS RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\< %d:RelExp\n", $$, $1, $2, $3);
    }
    | CompExp EQUAL RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\=\\= %d:RelExp\n", $$, $1, $2, $3);
    }
    | CompExp LESSEQUAL RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\<\\= %d:RelExp\n", $$, $1, $2, $3);
    }
    | CompExp GREATEREQUAL RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\>\\= %d:RelExp\n", $$, $1, $2, $3);
    }
    | CompExp NOTEQUAL RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\!\\= %d:RelExp\n", $$, $1, $2, $3);
    }
    | RelExp { 
        $$ = ++cnt;
        strcpy(L[$$], "CompExp");
        printf ("%d:CompExp -> %d:RelExp\n", $$, $1);
    }
;
FuncRParams:
    AddExp COMMA FuncRParams {
        $$ = ++cnt;
        strcpy(L[$$], "FuncRParams");
        printf ("%d:FuncRParams -> %d:AddExp %d:\\, %d:FuncRParams\n", $$, $1, $2, $3);
    }
    | AddExp { 
        $$ = ++cnt;
        strcpy(L[$$], "FuncRParams");
        printf ("%d:FuncRParams -> %d:AddExp\n", $$, $1);
    }
;
LVal:
    IDENTIFIER ArrayIndex {
        $$ = ++cnt;
        strcpy(L[$$], "LVal");
        printf ("%d:LVal -> %d:%s %d:ArrayIndex\n", $$, $1, L[$1], $2);
    }
    | IDENTIFIER {
        $$ = ++cnt;
        strcpy(L[$$], "LVal");
        printf ("%d:LVal -> %d:%s\n", $$, $1, L[$1]);
    }
;
RelExp:
    AddExp { 
        $$ = ++cnt;
        strcpy(L[$$], "RelExp");
        printf ("%d:RelExp -> %d:AddExp\n", $$, $1);
    }
;
%%