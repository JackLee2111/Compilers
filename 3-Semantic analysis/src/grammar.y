%{
#include <iostream>
#include <algorithm>
#include <math.h> 
#include<string.h>
#include<list>
#include<map>
#include<queue>
#include<iterator>
#include<stack>
using namespace std;
extern int yylex(void); 
extern int yyparse(void); 
extern int line, col;
extern int yyleng;
extern char *yytext;

FILE *f;

void yyerror(const char *s){
	printf("%s:\t(%d, %d)\t %s\n", s, line, col - yyleng, yytext);
}

//存储数据结构

int cnt = 0; //节点个数
int num_of_assem = 0; //汇编语句条数
int offset = 0; //全局偏移量
int level = 0; //层数（嵌套）
bool is_func_void = false;
char L[100000][50]; //lable
char funcname[100]; //函数名

// 属性节点
struct State{
	int value, offset, offset_of_arr;
	int quad;
	bool is_const;
	bool is_arr;
	string name;
	vector<bool> const_para, arr_para; //参数类型
	vector<int> truelist, falselist;
	vector<int> dimension;
	vector<int> para_val, para_offset, para_offset_of_arr;
	vector<string> para_name;
}node[100000];


//变量类型：整形、常量、数组、函数
enum Type {Int, Int_Const, Array, int_Function, void_Function};
//变量结构体，存储变量的信息
struct Variable{
	Type type; //类型
	int value; //值，当且仅当为常量时，该值有效
	int offset; //偏移
	vector<int> dimension; //维数，当且仅当该变量为数组时，该值有效
	Variable() {}
	//构造函数
	Variable(Type _type, int _val) : type(_type), value(_val){}
	Variable(Type _type, int _val, int _offset) : type(_type), value(_val), offset(_offset){}
	Variable(Type _type, int _val, int _offset, vector<int> _dim) : type(_type), value(_val), offset(_offset), dimension(_dim){}
};
vector<map<string, Variable> > symbol_table; //符号表


vector<int> p_offset;//记录每一层嵌套的偏移量，在出来时pop
vector<int> ArrInitVal; //记录初始化的数组值

vector<string> Assemble; //存储汇编指令
vector<string> Para; //存储参数，参数列表
vector<vector<pair <int, int> > > breaklist, continuelist; 

//回填，用pos填充vector（truelist，falselist，nextlist）中的所有语句跳转地址
//回填之处：if while语句，新建一个标签；与/或表达式的回填和合并，使用backpatch和merge函数
void backpatch(vector<int> &a, int pos){
	for(auto x : a) Assemble[x] += ".L" + to_string(pos) + "\n";
}

//merge合并操作，将两个向量中的值合并到一个向量中
vector<int> merge(const vector<int> &a, const vector<int> &b){
	vector<int> res;
	for(auto x : a) res.push_back(x);
	for(auto x : b) res.push_back(x);
	return res;
}


//寄存器
//变量存进寄存器
//%rdi、%rsi、%rdx，%rcx、%r8、%r9 函数传参
//rsp rbp 栈
//偏移量固定用rbx rdx来计算（不用eax，否则冲突）
//eax 返回值
//除法、取模运算，被除数存入eax
//计算（加减乘）用r8，r9进行操作，存入r8中


//局部变量存入寄存器
//局部变量的定义
//函数体进去，push，保存寄存器；出来pop，恢复栈，弹出寄存器 594


//将变量移入寄存器
//不使用 eax 寄存器用于计算数组偏移量，否则在数组元素的除、取模中 eax 寄存器存在冲突
void var2reg(int x, const char* reg){
	char tmp[100];
	//常量直接 mov 数值
	if(node[x].is_const){
		sprintf(tmp, "\tmovl\t$%d, %%%s\n", node[x].value, reg); Assemble.push_back(tmp);
	}
	//全局变量或数组
	else if(node[x].offset == 1){
		if(node[x].is_arr){//数组，用 rip 寄存器和变量名定位
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].offset_of_arr); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			Assemble.push_back("\tleaq\t0(, %rbx, 4), %rdx\n");
			sprintf(tmp, "\tleaq\t%s(%rip), %rbx\n", node[x].name.c_str()); Assemble.push_back(tmp);
			sprintf(tmp, "\tmovl\t(%rdx, %rbx), %%%s\n", reg); Assemble.push_back(tmp);
		}
		//全局变量，用 rip 寄存器和变量名定位
		else{
			sprintf(tmp, "\tmovl\t%s(%rip), %%%s\n", node[x].name.c_str(), reg); Assemble.push_back(tmp);
		}
	}
	// 局部变量 用栈内偏移量定位
	else{
		//数组
		if(node[x].is_arr){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].offset_of_arr); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			sprintf(tmp, "\tmovl\t%d(%rbp, %rbx, 4), %%%s\n", node[x].offset, reg); Assemble.push_back(tmp);
			
		}
		//值
		else{
			sprintf(tmp, "\tmovl\t%d(%rbp), %%%s\n", node[x].offset, reg); Assemble.push_back(tmp);
		}
	}
}

//将寄存器移入内存，同上
void reg2var(const char* reg, int x){
	char tmp[100];
	if(node[x].is_const){
		yyerror("Const Error");
		exit(0);
	}
	if(node[x].offset == 1){
		if(node[x].is_arr){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].offset_of_arr); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			Assemble.push_back("\tleaq\t0(, %rbx, 4), %rdx\n");
			sprintf(tmp, "\tleaq\t%s(%rip), %rbx\n", node[x].name.c_str()); Assemble.push_back(tmp);
			sprintf(tmp, "\tmovl\t%%%s, (%rdx, %rbx)\n", reg); Assemble.push_back(tmp);
		}
		else{
			sprintf(tmp, "\tmovl\t%%%s, %s(%rip)\n",  reg, node[x].name.c_str()); Assemble.push_back(tmp);
		}
	}
	else{
		if(node[x].is_arr){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].offset_of_arr); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			sprintf(tmp, "\tmovl\t%%%s, %d(%rbp, %rbx, 4)\n", reg, node[x].offset); Assemble.push_back(tmp);
		}
		else{
			sprintf(tmp, "\tmovl\t%%%s, %d(%rbp)\n", reg, node[x].offset); Assemble.push_back(tmp);
		}
	}
}

//将参数 mov/lea 进寄存器，分类讨论同上
void para2reg(int x, int pos, const char *reg){
	char tmp[100];
	if(node[x].const_para[pos]){
		sprintf(tmp, "\tmovl\t$%d, %%%s\n", node[x].para_val[pos], reg); Assemble.push_back(tmp);
	}
	else if(node[x].para_offset[pos] == 1){
		if(node[x].arr_para[pos]){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].para_offset_of_arr[pos]); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			Assemble.push_back("\tleaq\t0(, %rbx, 4), %rdx\n");
			sprintf(tmp, "\tleaq\t%s(%rip), %rbx\n", node[x].para_name[pos].c_str()); Assemble.push_back(tmp);
			sprintf(tmp, "\tmovl\t(%rdx, %rbx), %%%s\n", reg); Assemble.push_back(tmp);
		}
		else{
			sprintf(tmp, "\tmovl\t%s(%rip), %%%s\n", node[x].para_name[pos].c_str(), reg); Assemble.push_back(tmp);
		}
	}
	else{
		if(node[x].arr_para[pos]){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].para_offset_of_arr[pos]); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			sprintf(tmp, "\tmovl\t%d(%rbp, %rbx, 4), %%%s\n", node[x].para_offset[pos], reg); Assemble.push_back(tmp);
			
		}
		else{
			sprintf(tmp, "\tmovl\t%d(%rbp), %%%s\n", node[x].para_offset[pos], reg); Assemble.push_back(tmp);
		}
	}
}

//用于 scanf 的操作，分类讨论同上
void lea_para2reg(int x, int pos, const char *reg){
	char tmp[100];
	if(node[x].const_para[pos]){
		yyerror("Const Error");
		exit(0);
	}
	if(node[x].para_offset[pos] == 1){
		if(node[x].arr_para[pos]){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].para_offset_of_arr[pos]); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			Assemble.push_back("\tleaq\t0(, %rbx, 4), %rdx\n");
			sprintf(tmp, "\tleaq\t%s(%rip), %rbx\n", node[x].para_name[pos].c_str()); Assemble.push_back(tmp);
			sprintf(tmp, "\tleaq\t(%rdx, %rbx), %%%s\n", reg); Assemble.push_back(tmp);
		}
		else{
			sprintf(tmp, "\tleaq\t%s(%rip), %%%s\n", node[x].para_name[pos].c_str(), reg); Assemble.push_back(tmp);
		}
	}
	else{
		if(node[x].arr_para[pos]){
			sprintf(tmp, "\tmovl\t%d(%rbp), %%ebx\n", node[x].para_offset_of_arr[pos]); Assemble.push_back(tmp);
			Assemble.push_back("\tcltq\n");
			sprintf(tmp, "\tleaq\t%d(%rbp, %rbx, 4), %%%s\n", node[x].para_offset[pos], reg); Assemble.push_back(tmp);
			
		}
		else{
			sprintf(tmp, "\tleaq\t%d(%rbp), %%%s\n", node[x].para_offset[pos], reg); Assemble.push_back(tmp);
		}
	}
}

//调用函数，固定语句
void call_func_push(){
	Assemble.push_back("\tpushq\t%rbp\n");
	Assemble.push_back("\tpushq\t%r8\n");
	Assemble.push_back("\tpushq\t%r9\n");
	Assemble.push_back("\tmovq\t%rsp, %rbp\n");
}

//从函数中返回，固定语句
void ret_func_pop(){
	Assemble.push_back("\tpopq\t%r9\n");
	Assemble.push_back("\tpopq\t%r8\n");
	Assemble.push_back("\tpopq\t%rbp\n");
	Assemble.push_back("\tret\n");
}
%}

%token IF
%token ELSE WITHOUTELSE
%token WHILE
%token CONTINUE
%token BREAK
%token RETURN
%token CONST
%token INT
%token VOID
%token MAIN

%token LESSEQUAL
%token GREATEREQUAL
%token EQUAL
%token NOTEQUAL

%token AND
%token OR
%token ID
%token CONST_NUM
%token OTHER 

%nonassoc WITHOUTELSE
%nonassoc ELSE

%%

//常量定义
CompUnits: CompUnit{}
	| CompUnits CompUnit{}
	;

CompUnit: Decl{}
	| FuncDef{}
	;

Decl:	ConstDecl{}
	| VarDecl{}
	;

ConstDecl: CONST INT ConstDefs ';'{}
	| CONST error ';'{printf("Const Definition Error\n");}
	;

ConstDefs: ConstDef{}
	| ConstDefs ',' ConstDef{}
	;

//数组部分的定义，右递归
ConstArr: /*empty*/ {$$ = 0;}
	| '[' ConstExp ']' ConstArr{
		if($4) node[$$ = $4].value = node[$2].value * node[$4].value;
		else node[$$ = ++cnt].value = node[$2].value;
		node[$$].dimension.push_back(node[$2].value);
	}
	;

//常量的定义，满足赋的值必须是常数
ConstDef: ID ConstArr '=' ConstInitVal{
		//重名，报错
		if(symbol_table[level].find(L[$1]) != symbol_table[level].end()){
			yyerror("Const Redefinition Error");
			exit(0);
		}
		char tmp[100];
		//全局变量，level==0
		if(level == 0){
			//不是常数，报错
			if(!node[$4].is_const){
				printf("Const Definition Error\n");
				exit(0);
			}
			//没有数组部分
			if (!$2){
				Assemble.push_back("\t.section\t.rodata\n");
				Assemble.push_back("\t.align\t4\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, 4\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.long\t%d\n", node[$4].value); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[$1]] = Variable(Int_Const, node[$4].value, 1);
			}
			//else
		}
		//局部变量
		else{
			if (!$2){
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				sprintf (tmp, "\tmovl\t$%d, %%edi\n", node[$4].value); Assemble.push_back(tmp);
				sprintf (tmp, "\tmovl\t%%edi, %d(%rbp)\n", offset); Assemble.push_back(tmp);
				symbol_table[level][L[$1]] = Variable(Int_Const, node[$4].value, offset);
			}
			//else
		}
		
	}
	;

//变量定义
ConstInitVals: ConstInitVal{}
	| ConstInitVals ',' ConstInitVal{}
	;

ConstInitVal: ConstExp{$$ = $1;}
	| '{' '}'{}
	| '{' ConstInitVals '}'{}
	;

VarDefs: VarDef{}
	| VarDefs ',' VarDef{}
	;

VarDecl: INT VarDefs ';'{}
	| INT error ';' {printf("Variable Definition Error\n");}
	;	

//变量定义——————————————
//只定义不赋值，未赋值，统一放在.data 段
VarDef: ID ConstArr{
		//判断是否重名
		if(symbol_table[level].find(L[$1]) != symbol_table[level].end()){
			yyerror("Variable Redefinition Error");
			exit(0);
		}
		char tmp[100];
		//全局变量/数组
		if(level == 0){
			//全局变量，计算相应的 size，对于变量初值设为.long 0 或.zero 4 即可
			if(!$2){
				sprintf (tmp, "\t.globl\t%s\n", L[$1]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t4\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, 4\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[$1]); Assemble.push_back(tmp);
				Assemble.push_back("\t.long\t0\n");
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[$1]] = Variable(Int, 0, 1);
			}
			//全局数组，计算相应的 size，对于数组初始化值为.zero 4 * size
			else{
				sprintf (tmp, "\t.globl\t%s\n", L[$1]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t32\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, %d\n", L[$1], node[$2].value * 4); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.zero\t%d\n", node[$2].value * 4); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[$1]] = Variable(Array, 0, 1, node[$2].dimension);
			}
		}
		//局部变量/数组
		else{
			//局部变量，栈上分配相应空间即可
			if(!$2){
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				symbol_table[level][L[$1]] = Variable(Int, 0, offset);
			}
			//局部数组
			else{
				offset -= 4 * node[$2].value;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", node[$2].value * 4); Assemble.push_back(tmp);
				symbol_table[level][L[$1]] = Variable(Array, 0, offset, node[$2].dimension);
			}
		}
	}
	//有赋初值的变量定义
	| ID ConstArr '=' InitVal{
		if(symbol_table[level].find(L[$1]) != symbol_table[level].end()){
			yyerror("Variable Redefinition Error");
			exit(0);
		}
		char tmp[100];
		//全局变量/数组
		if(!level){
			//全局变量，根据 InitVal 的返回值情况判断类型是否匹配
			if (!$2){
				if(!$4 || !node[$4].is_const){
					yyerror("Initializer Error");
					exit(0);
				}
				sprintf (tmp, "\t.globl\t%s\n", L[$1]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t4\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, 4\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.long\t%d\n", node[$4].value); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[$1]] = Variable(Int, node[$4].value, 1);
			}
			//全局数组，数组应判断赋值的个数是否超过了数组大小
			else {
				if($4){
					yyerror("Initializer Error");
					exit(0);
				}
				if(ArrInitVal.size() > node[$2].value){
					yyerror("Too Many Initializers Error");
					exit(0);
				}
				sprintf (tmp, "\t.globl\t%s\n", L[$1]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t32\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[$1]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, %d\n", L[$1], node[$2].value * 4); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[$1]); Assemble.push_back(tmp);
				for(auto x : ArrInitVal) {
					sprintf (tmp, "\t.long\t%d\n", node[x].value);  Assemble.push_back(tmp);
				}
				sprintf (tmp, "\t.zero\t%d\n", node[$2].value * 4 - ArrInitVal.size() * 4); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[$1]] = Variable(Array, 0, 1, node[$2].dimension);
				ArrInitVal.clear();
			}
		}
		//局部变量/数组
		else{
			//局部变量，这里的赋值可能不是常数
			//需要按照地址通过 var2reg 函数计算，然后放置到相应的地址位置
			if (!$2){
				if(!$4){
					yyerror("Initializer Error");
					exit(0);
				}
				var2reg($4, "edi");
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				//将该值存入栈中
				sprintf (tmp, "\tmovl\t%%edi, %d(%rbp)\n", offset); Assemble.push_back(tmp);
				symbol_table[level][L[$1]] = Variable(Int, node[$4].value, offset);
			}
			//数组
			else {
				if($4){
					yyerror("Initializer Error");
					exit(0);
				}
				if(ArrInitVal.size() > node[$2].value){
					yyerror("Too Many Initializers Error");
					exit(0);
				}
				//一次性减offset
				offset -= 4 * node[$2].value;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", 4 * node[$2].value); Assemble.push_back(tmp);
				//从下至上存入数组的值到栈中
				for(int i = 0; i < ArrInitVal.size(); ++i){
					var2reg(ArrInitVal[i], "edi");
					sprintf (tmp, "\tmovl\t%%edi, %d(%rbp)\n", offset + i * 4);  Assemble.push_back(tmp);
				}
				symbol_table[level][L[$1]] = Variable(Array, 0, offset, node[$2].dimension);
				ArrInitVal.clear();
			} 
		}
	}
	; 

//vector(ArrInitVal)来记录初始化的数组值
//用不同的返回值判断是变量还是数组的赋值
//规定对于全局变量/数组的的初始化赋值必须是常量
InitVals: InitVal {
		if(!level && !node[$1].is_const){		
			yyerror("Initializer Error");
			exit(0);
		}
		ArrInitVal.push_back($1);
	}
	| InitVals ',' InitVal {
		if(!level && !node[$3].is_const){		
			yyerror("Initializer Error");
			exit(0);
		}
		ArrInitVal.push_back($3);
	}
	;

InitVal: Exp{$$ = $1;}
	| '{' '}'{$$ = 0;}
	| '{' InitVals '}'{$$ = 0;}
	;


//函数定义
//对于参数部分， 在匹配到函数名后， 匹配参数前需将参数列表清空
//每次匹配到一个参数时将其 push_back 到参数列表中
FName: ID {
		strcpy(funcname, L[$1]);
		Para.clear();
	}
	;
FuncFParams: FuncFParam {}        
	| FuncFParams ',' FuncFParam{}        
	;

FuncFParam: INT ID ParaArr{Para.push_back(L[$2]);}        
	;

ParaArr: /*empty*/ {}
	| '[' ']' Array{if($3) $$ = $3;}
	;

Array:	/*empty*/ {$$ = 0;}
	| '[' Exp ']' Array{
		$$ = ($4) ? $4 : ++cnt;
		node[$$].dimension.push_back($2);
	}
	;

//函数体归约
FuncDef: VOID FName '(' ')' Entry_Void Block{
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}	
	| INT FName '(' ')' Entry_Int Block{
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
	| VOID FName '(' FuncFParams ')' Entry_Void_Para Block{
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
	//函数结束归约时，将栈恢复，弹出旧寄存器值
	| INT FName '(' FuncFParams ')' Entry_Int_Para Block{
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
	| INT MAIN '(' ')' Entry_Main Block{
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0;
	}
	| INT error Block{printf("Function Parameter Error\n");}
	| VOID error Block{printf("Function Parameter Error\n");}
	;


//进入函数
//进入函数前，新建一个符号表并将参数定义在符号表中，同时将寄存器和参数压入栈
Entry_Main: /*empty*/ {
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		Assemble.push_back("\t.globl\tmain\n");
		Assemble.push_back("\t.type\tmain, @function\n");
		Assemble.push_back("main:\n");
		call_func_push();
	}
	;

Entry_Void: /*empty*/ {
		is_func_void = true;
		//查看每一层是否有重名函数
		for(int i = level; i >= 0; --i)
			if(symbol_table[i].find(funcname) != symbol_table[i].end()){
				yyerror("Function Redefinition Error");
				exit(0);
			}
		symbol_table[level][funcname] = Variable(void_Function, 0, 0);
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		char tmp[100];
		sprintf(tmp, "\t.globl\t%s\n", funcname); Assemble.push_back(tmp);
		Assemble.push_back("\t.type\tmain, @function\n");
		//新开一个函数体
		sprintf(tmp, "%s:\n", funcname); Assemble.push_back(tmp);
		call_func_push();
	}
	;

Entry_Int: /*empty*/ {
		is_func_void = false;
		for(int i = level; i >= 0; --i)
			if(symbol_table[i].find(funcname) != symbol_table[i].end()){
				yyerror("Function Redefinition Error");
				exit(0);
			}
		symbol_table[level][funcname] = Variable(int_Function, 0, 0);
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		char tmp[100];
		sprintf(tmp, "\t.globl\t%s\n", funcname); Assemble.push_back(tmp);
		Assemble.push_back("\t.type\tmain, @function\n");
		sprintf(tmp, "%s:\n", funcname); Assemble.push_back(tmp);
		call_func_push();
	}
	;

Entry_Void_Para: /*empty*/ {
		is_func_void = true;
		for(int i = level; i >= 0; --i)
			if(symbol_table[i].find(funcname) != symbol_table[i].end()){
				yyerror("Function Redefinition Error");
				exit(0);
			}
		symbol_table[level][funcname] = Variable(void_Function, 0, 0);
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		char tmp[100];
		sprintf(tmp, "\t.globl\t%s\n", funcname); Assemble.push_back(tmp);
		Assemble.push_back("\t.type\tmain, @function\n");
		sprintf(tmp, "%s:\n", funcname); Assemble.push_back(tmp);
		call_func_push();
		for(int i = 0; i < Para.size(); ++i) {
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf(tmp, "\tmovl\t%d(%rbp), %r8d\n", 32 + i * 4); Assemble.push_back(tmp);
			sprintf(tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			symbol_table[level][Para[i].c_str()] = Variable(Int, 0, offset);
		}
	}
	;

Entry_Int_Para: /*empty*/ {
		is_func_void = false;
		for(int i = level; i >= 0; --i)
			if(symbol_table[i].find(funcname) != symbol_table[i].end()){
				yyerror("Function Redefinition Error");
				exit(0);
			}
		symbol_table[level][funcname] = Variable(int_Function, 0, 0);
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		char tmp[100];
		sprintf(tmp, "\t.globl\t%s\n", funcname); Assemble.push_back(tmp);
		Assemble.push_back("\t.type\tmain, @function\n");
		sprintf(tmp, "%s:\n", funcname); Assemble.push_back(tmp);
		call_func_push();
		for(int i = 0; i < Para.size(); ++i) {
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf(tmp, "\tmovl\t%d(%rbp), %r8d\n", 32 + i * 4); Assemble.push_back(tmp);
			sprintf(tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			symbol_table[level][Para[i].c_str()] = Variable(Int, 0, offset);
		}
	}
	;

//条件控制语句模块
//语法修改：
/*
IF '(' Cond ')' NewLabel BeforeStmt Stmt AfterStmt %prec WITHOUTELSE
IF '(' Cond ')' NewLabel BeforeStmt Stmt AfterStmt ELSE AfterElse NewLabel BeforeStmt Stmt AfterStmt NewLabel
WHILE WhileBegin BeforeStmt '(' Cond ')' WhileEnd NewLabel Stmt AfterStmt
*/

//代码块，{}
Block:	'{' '}'{}        
	| '{' BlockItem '}'{}    
	| '{' error '}'{printf("Block Error\n");}
	;
//{}中的代码块（包括各种表达式	
BlockItem:	Decl{}
	| Stmt{}     
	| BlockItem Decl{}
	| BlockItem Stmt{} 
	;

//各种表达式的块（条件控制）
Stmt:	LVal '=' Exp ';'{
		if(node[$1].is_const){
			yyerror("Const Error");
			exit(0);
		}
		var2reg($3, "r9d");
		reg2var("r9d", $1);
	}       
	| Exp ';'{}       
	| ';'{}       
	| Block{}
	//if语句1
	//通过使用 NewLabel 完成回填操作      
	| IF '(' Cond ')' NewLabel BeforeStmt Stmt AfterStmt %prec WITHOUTELSE {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		++num_of_assem;
		sprintf (tmp, ".L%d:\n", num_of_assem); 
		Assemble.push_back(tmp);
		for(auto x : node[$3].truelist) Assemble[x] += ".L" + to_string($5) + "\n";
		for(auto x : node[$3].falselist) Assemble[x] += ".L" + to_string(num_of_assem) + "\n";
	} 
	//if语句2   
	| IF '(' Cond ')' NewLabel BeforeStmt Stmt AfterStmt ELSE AfterElse NewLabel BeforeStmt Stmt AfterStmt NewLabel{ 
		--level;
		symbol_table.pop_back();
		for(auto x : node[$3].truelist) Assemble[x] += ".L" + to_string($5) + "\n";
		for(auto x : node[$3].falselist) Assemble[x] += ".L" + to_string($11) + "\n";
		Assemble[node[$10].truelist[0]] += ".L" + to_string($15) + "\n";
	} 
	//while语句
	| WHILE WhileBegin BeforeStmt '('  Cond  ')' WhileEnd NewLabel Stmt AfterStmt{
		--level;
		symbol_table.pop_back();
		backpatch(node[$5].truelist, $8);
		char tmp[100];
		sprintf (tmp, "\tjmp\t.L%d\n", $2); Assemble.push_back(tmp);
		++num_of_assem;
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		backpatch(node[$5].falselist, node[$7].quad);
		backpatch(node[$7].truelist, num_of_assem);
		//在有breaklist的地方加上无条件跳转，恢复栈内容后跳转
		for(auto it : *breaklist.rbegin()){
			sprintf(tmp, "\taddq\t$%d, %rsp\n", offset - it.second);
			Assemble[it.first - 1] = string(tmp);
			Assemble[it.first] += ".L" + to_string(num_of_assem) + "\n";
		}
        	breaklist.pop_back();
		//在有continuelist的地方加上无条件跳转
		for(auto it : *continuelist.rbegin()){
			sprintf(tmp, "\taddq\t$%d, %rsp\n", offset - it.second);
			Assemble[it.first - 1] = string(tmp);
			Assemble[it.first] += ".L" + to_string($2) + "\n";
		}
        	continuelist.pop_back();
 	}  
	//break跳出循环，标记当前的位置
	| BREAK ';'{
		Assemble.push_back("wait");
		Assemble.push_back("\tjmp\t");
		(*breaklist.rbegin()).push_back(make_pair(Assemble.size() - 1, offset));
	} 
	//继续循环，恢复栈内容后跳转
	| CONTINUE ';'{
		Assemble.push_back("wait");
		Assemble.push_back("\tjmp\t");
		(*continuelist.rbegin()).push_back(make_pair(Assemble.size() - 1, offset));
	}
	//返回  
	| RETURN Exp ';'{
		if(is_func_void){
			yyerror("Return Value Error");
			exit(0);
		}
		char tmp[100];
		var2reg($2, "eax");
		sprintf (tmp, "\taddq\t$%d, %rsp\n", -offset); Assemble.push_back(tmp);
		ret_func_pop();
	} 
	//返回
	| RETURN ';'{
		if(!is_func_void){
			yyerror("Return Value Error");
			exit(0);
		}
		char tmp[100];
		sprintf (tmp, "\taddq\t$%d, %rsp\n", -offset); Assemble.push_back(tmp);
		ret_func_pop();
	}  
	| error ';'{printf("Statement Error\n");}
	;

//新建一个标签，用于backbatch
NewLabel: /*empty*/ {
		$$ = ++num_of_assem;
		char tmp[100];
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
	}
	;

//进入新一层的嵌套作准备
//新建符号表，对齐
BeforeStmt: /*empty*/ {
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		p_offset.push_back(offset);
		if(abs(offset) % 16 != 0){
			int padding = 16 - abs(offset) % 16;
			offset -= padding;
			char tmp[100];
			sprintf (tmp, "\tsubq\t$%d, %rsp\n", padding); Assemble.push_back(tmp);
		}
	}
	;

//从上一层的嵌套中恢复偏移量
AfterStmt: /*empty*/ {
		char tmp[100];
		int last = *p_offset.rbegin();
		sprintf (tmp, "\taddq\t$%d, %rsp\n", last - offset); Assemble.push_back(tmp);
		p_offset.pop_back();
		offset = last;
	}
	;
//执行完 true 的部分后新增一条 jmp 指令，无条件跳转
AfterElse: /*empty*/ {
		Assemble.push_back("\tjmp\t");
		node[$$ = ++cnt].truelist.push_back(Assemble.size() - 1);
	}
	;

//标记每趟循环判断语句之前的位置， 新建一个标签和break/continue list 层
WhileBegin: /*empty*/ {
		$$ = ++num_of_assem;
		char tmp[100];
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		vector< pair<int, int> > x, y;
		breaklist.push_back(x);
		continuelist.push_back(y);
	}
	;
//标记循环判断语句后的位置，恢复栈偏移量
WhileEnd: /*empty*/ {
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		int last = *p_offset.rbegin();
		sprintf (tmp, "\taddq\t$%d, %rsp\n", last - offset); Assemble.push_back(tmp);
		Assemble.push_back("\tjmp\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
	}
	;
	
Exp: 	AddExp{$$ = $1;}  
	;

//布尔表达式
Cond:	LOrExp{$$ = $1;}  
	| error{printf("Condition Error\n");}
	;

//左值表达式，相当于值的综合属性传递
LVal:	ID Array{
		bool used = false;
		//非数组，int 型变量/常量元素直接从符号表中读取即可
		if(!$2){
			for(int i = level; i >= 0; --i)
				if(symbol_table[i].find(L[$1]) != symbol_table[i].end()){
					used = true;
					Variable cur = symbol_table[i][L[$1]];
					$$ = ++cnt;
					if(cur.type == Int_Const) {
						node[$$].is_const = true;
						node[$$].value = cur.value;
					}
					else {
						node[$$].is_const = false;
						node[$$].offset = cur.offset;
						if(!i) node[$$].name = string(L[$1]);
					}
					break;
				}
		}
		//数组，计算数组偏移地址
		else{
			char tmp[100];
			//在最后一层找到最近一次更新的值
			for(int i = level; i >= 0; --i)
				if(symbol_table[i].find(L[$1]) != symbol_table[i].end()){
					Variable cur = symbol_table[i][L[$1]];
					if(cur.type != Array || node[$2].dimension.size() != cur.dimension.size()) continue;
					used = true;
					int x = 1;
					offset -= 4;
					Assemble.push_back("\tsubq\t$4, %rsp\n");
					sprintf (tmp, "\tmovl\t$0, %d(%rbp)\n", offset); Assemble.push_back(tmp);
					int z = offset;
					for(int j = 0; j < cur.dimension.size(); ++j){
						var2reg(node[$2].dimension[j], "r8d");
						sprintf (tmp, "\timull\t$%d, %r8d\n", x); Assemble.push_back(tmp);
						sprintf (tmp, "\taddl\t%d(%rbp), %r8d\n", z); Assemble.push_back(tmp);
						sprintf (tmp, "\tmovl\t%%r8d, %d(%rbp)\n", z); Assemble.push_back(tmp);
						x *= cur.dimension[j];
					}
					$$ = ++cnt;
					node[$$].is_arr = true;
					if(cur.type == Int_Const){
						node[$$].is_const = true;
						node[$$].value = cur.value;
					}
					else{
						node[$$].is_const = false;
						node[$$].offset = cur.offset;
						node[$$].offset_of_arr = z;
						if(!i) node[$$].name = string(L[$1]);
					}
					break;
				}
		}
		if(!used){
			yyerror("Reference Undefined Variable");
			exit(0);
		}
	}  
	;

PrimaryExp: '(' Exp ')'{$$ = $2;}  
	| LVal{$$ = $1;}  
	| CONST_NUM{node[$$ = ++cnt].value = $1, node[$$].is_const = true;}  
	;

//函数调用
//函数的参数，首先记录参数状态
FuncRParams: Exp{
		$$ = $1;
		node[$$].para_name.push_back(node[$1].name);
		node[$$].para_val.push_back(node[$1].value);
		node[$$].para_offset.push_back(node[$1].offset);
		node[$$].para_offset_of_arr.push_back(node[$1].offset_of_arr);
		node[$$].const_para.push_back(node[$1].is_const);
		node[$$].arr_para.push_back(node[$1].is_arr);
	}  
	| FuncRParams ',' Exp{
		$$ = $1;
		node[$$].para_name.push_back(node[$3].name);
		node[$$].para_val.push_back(node[$3].value);
		node[$$].para_offset.push_back(node[$3].offset);
		node[$$].para_offset_of_arr.push_back(node[$3].offset_of_arr);
		node[$$].const_para.push_back(node[$3].is_const);
		node[$$].arr_para.push_back(node[$3].is_arr);
	}  
	;

UnaryExp: PrimaryExp{$$ = $1;}
	//无参函数，调用
	| ID '(' ')'{
		if(symbol_table[0].find(L[$1]) == symbol_table[0].end()){
			yyerror("Funciton Not Defined Error");
			exit(0);
		}
		char tmp[100];
		//对齐
		if(abs(offset) % 16){
			int padding = 16 - abs(offset) % 16;
			offset -= padding;
			sprintf (tmp, "\tsubq\t$%d, %rsp\n", padding); Assemble.push_back(tmp);	 
		}
		sprintf (tmp, "\tcall\t%s\n", L[$1]); Assemble.push_back(tmp);
		Variable function = symbol_table[0][L[$1]];
		if(function.type == int_Function){
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n"); 
			sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}	 
	} 
	//有参函数，调用
	| ID '(' FuncRParams ')'{
		//scanf函数
		if(!strcmp(L[$1], "scanf")){
			if(node[$3].para_name.size() != 1){
				yyerror("Scanf Error");
				exit(0);
			}
			char tmp[100];
			//对齐
			if(abs(offset) % 16){
				int padding = 16 - abs(offset) % 16;
				offset -= padding;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", padding); Assemble.push_back(tmp);	 
			}		
			lea_para2reg($3, 0, "rsi");
			Assemble.push_back("\tleaq\t.LC0(%rip), %rdi\n");
			Assemble.push_back("\tmovl\t$0, %eax\n");
			Assemble.push_back("\tcall\t__isoc99_scanf@PLT\n");
		}
		//printf 函数
		else if(!strcmp(L[$1], "printf")){
			if(node[$3].para_name.size() != 1){
				yyerror("Printf Error");
				exit(0);
			}
			char tmp[100];
			//对齐
			if(abs(offset) % 16){
				int padding = 16 - abs(offset) % 16;
				offset -= padding;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", padding); Assemble.push_back(tmp);	 
			}
			para2reg($3, 0, "esi");
			Assemble.push_back("\tleaq\t.LC1(%rip), %rdi\n");
			Assemble.push_back("\tmovl\t$0, %eax\n");
			Assemble.push_back("\tcall\tprintf@PLT\n");
		}
		//其他函数
		//对齐， 将每个参数逐一插入栈中
		//有返回值的函数还应在调用后将 eax 寄存器的值存入栈中：
		else{
			//查询是否已经定义
			if(symbol_table[0].find(L[$1]) == symbol_table[0].end()){
				yyerror("Funciton Undefined Error");
				exit(0);
			}
			char tmp[100];
			//对齐
			if((-(offset - 4 * node[$3].para_name.size())) % 16){
				int padding = 16 - abs(offset) % 16;
				offset -= padding;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", padding); Assemble.push_back(tmp);	 
			}
			//参数逐一入栈
			for(int i = node[$3].para_name.size() - 1; i >= 0 ; --i){
				para2reg($3, i, "r8d");
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				sprintf (tmp, "\tmovl\t%%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			}
			//调用函数
			sprintf (tmp, "\tcall\t%s\n", L[$1]); Assemble.push_back(tmp);
			Variable function = symbol_table[0][L[$1]];
			//传返回地址
			if(function.type == int_Function){
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
				node[$$ = ++cnt].offset = offset;
			}	
		}
	}  
	| '+' UnaryExp{$$ = $2;}  
	| '-' UnaryExp{
		if(node[$2].is_const) node[$$ = $2].value = -node[$2].value;
		else{
			char tmp[100];
			var2reg($2, "r8d");
			Assemble.push_back("\tnegl\t%r8d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}
	} 
	//取非运算
	| '!' UnaryExp{
		char tmp[100];
		var2reg($2, "eax");	
		Assemble.push_back("\ttestl\t%eax, %eax\n");
		Assemble.push_back("\tsete\t%al\n");
		Assemble.push_back("\tmovzbl\t%al, %eax\n");
		offset -= 4;
		Assemble.push_back("\tsubq\t$4, %rsp\n");
		sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
		node[$$ = ++cnt].offset = offset;
	}  
	;

//计算语句1：乘除法
MulExp: UnaryExp{$$ = $1;}  
	//乘法
	| MulExp '*' UnaryExp{
		if(node[$1].is_const && node[$3].is_const)
			node[$$ = ++cnt].value = node[$1].value * node[$3].value, node[$$].is_const = 1;
		else{
			char tmp[100];
			var2reg($1, "r8d");
			var2reg($3, "r9d");
			Assemble.push_back("\timull\t%r8d, %r9d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r9d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}
	}  
	//除法
	| MulExp '/' UnaryExp{
		if(node[$1].is_const && node[$3].is_const)
			node[$$ = ++cnt].value = node[$1].value / node[$3].value, node[$$].is_const = 1;
		else{
			char tmp[100];
			var2reg($1, "eax");
			var2reg($3, "r9d");
			Assemble.push_back("\tcltd\n");
			Assemble.push_back("\tidivl\t%r9d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}
	}  
	//求余数
	| MulExp '%' UnaryExp{
		if(node[$1].is_const && node[$3].is_const)
			node[$$ = ++cnt].value = node[$1].value % node[$3].value, node[$$].is_const = 1;
		else{
			char tmp[100];
			var2reg($1, "eax");
			var2reg($3, "r9d");
			Assemble.push_back("\tcltd\n");
			Assemble.push_back("\tidivl\t%r9d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%%edx, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}
	}  
	;

//计算语句2：加减法
AddExp: MulExp {$$ = $1;}  
	//加法：如果操作数是常数则直接计算即可
	//否则转移至寄存器中进行相应计算后再存入内存
	| AddExp '+' MulExp{
		if(node[$1].is_const && node[$3].is_const)
			node[$$ = ++cnt].value = node[$1].value + node[$3].value, node[$$].is_const = 1;
		else{
			char tmp[100];
			var2reg($1, "r8d");
			var2reg($3, "r9d");
			Assemble.push_back("\taddl\t%r9d, %r8d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}
	}  
	//减法
	| AddExp '-' MulExp{
		if(node[$1].is_const && node[$3].is_const)
			node[$$ = ++cnt].value = node[$1].value - node[$3].value, node[$$].is_const = 1;
		else{
			char tmp[100];
			var2reg($1, "r8d");
			var2reg($3, "r9d");
			Assemble.push_back("\tsubl\t%r9d, %r8d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[$$ = ++cnt].offset = offset;
		}
	}  
	;

//布尔表达式
RelExp: AddExp {$$ = $1;}  
	//比较操作
	//将两个操作数放入寄存器中进行相应比较
	//然后将分支加入true/false list
	| RelExp '<' AddExp{
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg($1, "r8d");
		var2reg($3, "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjl\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjge\t");
		node[$$].falselist.push_back(Assemble.size() - 1);
	}  
	| RelExp '>' AddExp{
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg($1, "r8d");
		var2reg($3, "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjg\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjle\t");
		node[$$].falselist.push_back(Assemble.size() - 1);
	}  
	| RelExp LESSEQUAL AddExp{
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg($1, "r8d");
		var2reg($3, "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjle\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjg\t");
		node[$$].falselist.push_back(Assemble.size() - 1);
	}  
	| RelExp GREATEREQUAL AddExp{
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg($1, "r8d");
		var2reg($3, "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjge\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjl\t");
		node[$$].falselist.push_back(Assemble.size() - 1);
	}  
	;
	
EqExp:	RelExp {$$ = $1;}  
	| EqExp EQUAL RelExp{
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg($1, "r8d");
		var2reg($3, "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tje\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjne\t");
		node[$$].falselist.push_back(Assemble.size() - 1);
	}  
	| EqExp NOTEQUAL RelExp{
		char tmp[100];
		node[$$ = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg($1, "r8d");
		var2reg($3, "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjne\t");
		node[$$].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tje\t");
		node[$$].falselist.push_back(Assemble.size() - 1);
	}  
	;

LAndExp: EqExp{
		$$ = $1;
		if(!node[$$].quad){
			char tmp[100];
			node[$$ = ++cnt].quad = ++num_of_assem;
			sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
			var2reg($1, "r8d");
			Assemble.push_back("\tcmpl\t$0, %r8d\n");
			Assemble.push_back("\tjne\t");
			node[$$].truelist.push_back(Assemble.size() - 1);
			Assemble.push_back("\tje\t");
			node[$$].falselist.push_back(Assemble.size() - 1);
		}
	}  
	//与操作的回填，合并
	| LAndExp AND EqExp{
		backpatch(node[$1].truelist, node[$3].quad);
		node[$$].falselist = merge(node[$1].falselist, node[$3].falselist);
		node[$$].truelist = node[$3].truelist;
		node[$$].quad = node[$1].quad;
	}  
	;
	
LOrExp:	LAndExp{ $$ = $1; }  
	//或操作的回填，合并
	| LOrExp OR LAndExp{
		backpatch(node[$1].falselist, node[$3].quad);
		node[$$].truelist = merge(node[$1].truelist, node[$3].truelist);
		node[$$].falselist = node[$3].falselist;
		node[$$].quad = node[$1].quad;
	}  
	;

ConstExp: AddExp{
		$$ = $1;
		if(node[$$].is_const == false){
			yyerror("Const Error");	
			exit(0);
		}
	}  
	;
%%

int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	freopen (argv[1], "r", stdin);
    	f = fopen("assemble.s", "w");
    	
   	Assemble.push_back(".LC0:\n");
   	Assemble.push_back("\t.string\t\"\%d\"\n");
	Assemble.push_back(".LC1:\n");
	Assemble.push_back("\t.string\t\"\%d\\n\"\n");
	map<string, Variable> x;
	symbol_table.push_back(x);
	p_offset.push_back(0);
	
	yyparse();
	
	for(auto x : Assemble) fprintf(f, "%s", x.c_str());
    	
	fclose(f);
	return 0;
}
