/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./grammar.y"

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

#line 321 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WITHOUTELSE = 260,
    WHILE = 261,
    CONTINUE = 262,
    BREAK = 263,
    RETURN = 264,
    CONST = 265,
    INT = 266,
    VOID = 267,
    MAIN = 268,
    LESSEQUAL = 269,
    GREATEREQUAL = 270,
    EQUAL = 271,
    NOTEQUAL = 272,
    AND = 273,
    OR = 274,
    ID = 275,
    CONST_NUM = 276,
    OTHER = 277
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WITHOUTELSE 260
#define WHILE 261
#define CONTINUE 262
#define BREAK 263
#define RETURN 264
#define CONST 265
#define INT 266
#define VOID 267
#define MAIN 268
#define LESSEQUAL 269
#define GREATEREQUAL 270
#define EQUAL 271
#define NOTEQUAL 272
#define AND 273
#define OR 274
#define ID 275
#define CONST_NUM 276
#define OTHER 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
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
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   273

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

#define YYUNDEFTOK  2
#define YYMAXUTOK   277


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,     2,     2,    37,     2,     2,
      30,    31,    35,    32,    24,    33,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
      38,    27,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    29,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   280,   280,   281,   284,   285,   288,   289,   292,   293,
     296,   297,   301,   302,   310,   353,   354,   357,   358,   359,
     362,   363,   366,   367,   372,   423,   516,   523,   532,   533,
     534,   541,   546,   547,   550,   553,   554,   557,   558,   565,
     574,   583,   593,   602,   611,   612,   618,   629,   650,   669,
     695,   730,   731,   732,   735,   736,   737,   738,   742,   750,
     751,   752,   755,   766,   774,   800,   806,   812,   823,   832,
     836,   845,   860,   869,   876,   886,   897,   901,   902,   906,
     970,   971,   972,   977,   986,   997,   999,  1021,  1093,  1094,
    1107,  1121,  1123,  1138,  1154,  1172,  1175,  1190,  1207,  1211,
    1223,  1235,  1247,  1261,  1262,  1274,  1288,  1303,  1311,  1313,
    1321
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WITHOUTELSE", "WHILE",
  "CONTINUE", "BREAK", "RETURN", "CONST", "INT", "VOID", "MAIN",
  "LESSEQUAL", "GREATEREQUAL", "EQUAL", "NOTEQUAL", "AND", "OR", "ID",
  "CONST_NUM", "OTHER", "';'", "','", "'['", "']'", "'='", "'{'", "'}'",
  "'('", "')'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<'", "'>'",
  "$accept", "CompUnits", "CompUnit", "Decl", "ConstDecl", "ConstDefs",
  "ConstArr", "ConstDef", "ConstInitVals", "ConstInitVal", "VarDefs",
  "VarDecl", "VarDef", "InitVals", "InitVal", "FName", "FuncFParams",
  "FuncFParam", "ParaArr", "Array", "FuncDef", "Entry_Main", "Entry_Void",
  "Entry_Int", "Entry_Void_Para", "Entry_Int_Para", "Block", "BlockItem",
  "Stmt", "NewLabel", "BeforeStmt", "AfterStmt", "AfterElse", "WhileBegin",
  "WhileEnd", "Exp", "Cond", "LVal", "PrimaryExp", "FuncRParams",
  "UnaryExp", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp",
  "ConstExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    59,    44,    91,    93,    61,   123,   125,
      40,    41,    43,    45,    33,    42,    47,    37,    60,    62
};
# endif

#define YYPACT_NINF (-174)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-32)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     147,    49,    39,    19,    75,  -174,  -174,  -174,  -174,  -174,
      32,     4,    -1,    21,    47,    77,  -174,    23,    29,  -174,
      46,  -174,  -174,  -174,    69,    83,  -174,  -174,   171,  -174,
      73,   163,    86,  -174,    97,     5,  -174,     7,    93,  -174,
       4,    45,    99,  -174,   111,   117,    98,    28,    65,  -174,
    -174,  -174,   163,   163,   163,   163,  -174,  -174,   205,  -174,
     120,   142,  -174,  -174,   125,    90,  -174,  -174,    90,   145,
     105,    69,  -174,   153,  -174,    25,  -174,  -174,    30,   189,
    -174,  -174,  -174,    11,  -174,  -174,  -174,  -174,   152,   162,
     163,   223,  -174,   155,  -174,  -174,  -174,   164,  -174,  -174,
    -174,  -174,   163,   163,   163,   163,   163,   163,    29,    69,
      50,  -174,  -174,   165,    29,   177,  -174,    29,  -174,    82,
    -174,  -174,  -174,   158,    90,    -4,   129,   180,   183,   188,
    -174,   181,  -174,  -174,    57,  -174,   197,  -174,  -174,  -174,
     125,   125,  -174,  -174,  -174,    67,  -174,   198,  -174,  -174,
    -174,    29,  -174,    29,  -174,    68,  -174,  -174,   163,   163,
     163,   163,   163,   163,   163,   163,    11,   202,   163,  -174,
    -174,   105,  -174,   202,  -174,  -174,   189,  -174,  -174,    90,
      90,    90,    90,    -4,    -4,   129,   180,   199,  -174,  -174,
    -174,  -174,  -174,   239,  -174,  -174,  -174,   225,   239,  -174,
    -174,  -174,  -174,  -174,   239,  -174,  -174,  -174
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     4,     6,     7,     5,
       0,     0,     0,     0,    12,     0,    20,     0,     0,    31,
       0,     1,     3,     9,    12,     0,    10,    23,     0,    44,
       0,     0,    24,    22,     0,     0,    45,     0,     0,     8,
       0,     0,     0,    74,     0,     0,     0,     0,    37,    82,
      60,    51,     0,     0,     0,     0,    54,    61,     0,    55,
       0,    81,    85,    91,    95,    76,    46,    81,   110,     0,
       0,    12,    21,     0,    48,     0,    32,    47,     0,     0,
      11,    69,    53,     0,    71,    66,    65,    68,     0,     0,
       0,     0,    79,     0,    88,    89,    90,     0,    52,    56,
      57,    59,     0,     0,     0,     0,     0,     0,     0,    12,
       0,    25,    28,    35,     0,     0,    50,     0,    49,     0,
      14,    17,    78,     0,    98,   103,   106,   108,    77,     0,
      67,     0,    86,    83,     0,    80,     0,    92,    93,    94,
      96,    97,    43,    13,    29,     0,    26,     0,    34,    40,
      33,     0,    39,     0,    18,     0,    15,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,    87,
      58,     0,    30,    37,    42,    41,     0,    19,    71,   101,
     102,    99,   100,   104,   105,   107,   109,     0,    38,    84,
      27,    36,    16,     0,    75,    72,    70,    62,     0,    73,
      72,    70,    64,    71,     0,    72,    70,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,   227,   -21,  -174,  -174,   -20,   192,  -174,  -114,
    -174,  -174,   207,  -174,  -104,   233,   212,   135,  -174,  -148,
    -174,  -174,  -174,  -174,  -174,  -174,    -9,  -174,   -57,  -173,
    -161,  -107,  -174,  -174,  -174,   -44,    85,   -28,  -174,  -174,
     -40,    61,   -10,     1,    88,    96,  -174,   232
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    25,    32,    26,   155,   120,
      15,     8,    16,   145,   111,    17,    75,    76,   148,    92,
       9,   108,   117,   114,   153,   151,    57,    58,    59,   178,
     129,   197,   201,    84,   196,    60,   123,    67,    62,   134,
      63,    64,    65,   125,   126,   127,   128,   121
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   100,    88,    29,    38,   156,   146,    56,    93,    36,
     158,   159,   122,    94,    95,    96,    73,   193,    73,   188,
      18,    68,    27,   198,    24,   191,   112,    28,   203,    89,
      61,    48,    49,   207,   160,   161,    74,    99,    77,    19,
      12,    52,   204,    53,    54,    55,   131,   133,    71,   115,
      10,    30,    13,    35,   115,    23,   116,    28,   136,    14,
      11,   118,   192,   137,   138,   139,   112,   190,    81,    68,
      48,    49,    31,   124,    82,    21,    37,   -31,   110,   144,
      52,   168,    53,    54,    55,     1,     2,     3,   169,   143,
      90,   171,   176,   202,    31,    91,   172,   177,   206,   142,
      33,    34,    48,    49,    66,   149,    39,    40,   152,    68,
     119,   154,    52,    70,    53,    54,    55,    71,    48,    49,
      79,    87,   106,   107,   189,    48,    49,   112,    52,    83,
      53,    54,    55,   110,    85,    52,   195,    53,    54,    55,
      86,   200,   174,   101,   175,   162,   163,   205,   179,   180,
     181,   182,   124,   124,   124,   124,   124,     1,     2,     3,
     103,   104,   105,   183,   184,    61,    68,   140,   141,   102,
      61,   109,    41,   113,    42,   130,    61,    43,    44,    45,
      46,     1,    47,    48,    49,    27,   135,    81,    73,   157,
     147,    48,    49,    52,    50,    53,    54,    55,   164,    28,
      51,    52,   165,    53,    54,    55,    97,   167,    42,    48,
      49,    43,    44,    45,    46,     1,    47,   119,   166,    52,
     170,    53,    54,    55,   173,    48,    49,    90,    50,   199,
     194,    22,    80,    28,    98,    52,    20,    53,    54,    55,
      97,    72,    42,    48,    49,    43,    44,    45,    46,    78,
     150,   187,   185,    52,   132,    53,    54,    55,     0,    48,
      49,   186,    50,    69,     0,     0,     0,    28,     0,    52,
       0,    53,    54,    55
};

static const yytype_int16 yycheck[] =
{
      28,    58,    46,    12,    24,   119,   110,    28,    52,    18,
      14,    15,     1,    53,    54,    55,    11,   178,    11,   167,
       1,    31,    23,   196,    20,   173,    70,    28,   201,     1,
      58,    20,    21,   206,    38,    39,    31,    58,    31,    20,
       1,    30,   203,    32,    33,    34,    90,    91,    20,    24,
       1,    30,    13,    30,    24,    23,    31,    28,   102,    20,
      11,    31,   176,   103,   104,   105,   110,   171,    23,    79,
      20,    21,    25,    83,    29,     0,    30,    30,    28,    29,
      30,    24,    32,    33,    34,    10,    11,    12,    31,   109,
      25,    24,    24,   200,    25,    30,    29,    29,   205,   108,
      23,    24,    20,    21,    31,   114,    23,    24,   117,   119,
      28,    29,    30,    27,    32,    33,    34,    20,    20,    21,
      27,    23,    32,    33,   168,    20,    21,   171,    30,    30,
      32,    33,    34,    28,    23,    30,   193,    32,    33,    34,
      23,   198,   151,    23,   153,    16,    17,   204,   158,   159,
     160,   161,   162,   163,   164,   165,   166,    10,    11,    12,
      35,    36,    37,   162,   163,   193,   176,   106,   107,    27,
     198,    26,     1,    20,     3,    23,   204,     6,     7,     8,
       9,    10,    11,    20,    21,    23,    31,    23,    11,    31,
      25,    20,    21,    30,    23,    32,    33,    34,    18,    28,
      29,    30,    19,    32,    33,    34,     1,    26,     3,    20,
      21,     6,     7,     8,     9,    10,    11,    28,    30,    30,
      23,    32,    33,    34,    26,    20,    21,    25,    23,     4,
      31,     4,    40,    28,    29,    30,     3,    32,    33,    34,
       1,    34,     3,    20,    21,     6,     7,     8,     9,    37,
     115,   166,   164,    30,    31,    32,    33,    34,    -1,    20,
      21,   165,    23,    31,    -1,    -1,    -1,    28,    -1,    30,
      -1,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    11,    12,    41,    42,    43,    44,    51,    60,
       1,    11,     1,    13,    20,    50,    52,    55,     1,    20,
      55,     0,    42,    23,    20,    45,    47,    23,    28,    66,
      30,    25,    46,    23,    24,    30,    66,    30,    46,    23,
      24,     1,     3,     6,     7,     8,     9,    11,    20,    21,
      23,    29,    30,    32,    33,    34,    43,    66,    67,    68,
      75,    77,    78,    80,    81,    82,    31,    77,    82,    87,
      27,    20,    52,    11,    31,    56,    57,    31,    56,    27,
      47,    23,    29,    30,    73,    23,    23,    23,    75,     1,
      25,    30,    59,    75,    80,    80,    80,     1,    29,    43,
      68,    23,    27,    35,    36,    37,    32,    33,    61,    26,
      28,    54,    75,    20,    63,    24,    31,    62,    31,    28,
      49,    87,     1,    76,    82,    83,    84,    85,    86,    70,
      23,    75,    31,    75,    79,    31,    75,    80,    80,    80,
      81,    81,    66,    46,    29,    53,    54,    25,    58,    66,
      57,    65,    66,    64,    29,    48,    49,    31,    14,    15,
      38,    39,    16,    17,    18,    19,    30,    26,    24,    31,
      23,    24,    29,    26,    66,    66,    24,    29,    69,    82,
      82,    82,    82,    83,    83,    84,    85,    76,    59,    75,
      54,    59,    49,    70,    31,    68,    74,    71,    69,     4,
      68,    72,    71,    69,    70,    68,    71,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    46,    47,    48,    48,    49,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      54,    55,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    61,    62,    63,    64,
      65,    66,    66,    66,    67,    67,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    76,    77,
      78,    78,    78,    79,    79,    80,    80,    80,    80,    80,
      80,    81,    81,    81,    81,    82,    82,    82,    83,    83,
      83,    83,    83,    84,    84,    84,    85,    85,    86,    86,
      87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     4,     3,
       1,     3,     0,     4,     4,     1,     3,     1,     2,     3,
       1,     3,     3,     3,     2,     4,     1,     3,     1,     2,
       3,     1,     1,     3,     3,     0,     3,     0,     4,     6,
       6,     7,     7,     6,     3,     3,     0,     0,     0,     0,
       0,     2,     3,     3,     1,     1,     2,     2,     4,     2,
       1,     1,     8,    15,    10,     2,     2,     3,     2,     2,
       0,     0,     0,     0,     0,     0,     1,     1,     1,     2,
       3,     1,     1,     1,     3,     1,     3,     4,     2,     2,
       2,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 280 "./grammar.y"
                   {}
#line 1746 "y.tab.c"
    break;

  case 3:
#line 281 "./grammar.y"
                            {}
#line 1752 "y.tab.c"
    break;

  case 4:
#line 284 "./grammar.y"
              {}
#line 1758 "y.tab.c"
    break;

  case 5:
#line 285 "./grammar.y"
                 {}
#line 1764 "y.tab.c"
    break;

  case 6:
#line 288 "./grammar.y"
                 {}
#line 1770 "y.tab.c"
    break;

  case 7:
#line 289 "./grammar.y"
                 {}
#line 1776 "y.tab.c"
    break;

  case 8:
#line 292 "./grammar.y"
                                  {}
#line 1782 "y.tab.c"
    break;

  case 9:
#line 293 "./grammar.y"
                         {printf("Const Definition Error\n");}
#line 1788 "y.tab.c"
    break;

  case 10:
#line 296 "./grammar.y"
                   {}
#line 1794 "y.tab.c"
    break;

  case 11:
#line 297 "./grammar.y"
                                {}
#line 1800 "y.tab.c"
    break;

  case 12:
#line 301 "./grammar.y"
                    {yyval = 0;}
#line 1806 "y.tab.c"
    break;

  case 13:
#line 302 "./grammar.y"
                                   {
		if(yyvsp[0]) node[yyval = yyvsp[0]].value = node[yyvsp[-2]].value * node[yyvsp[0]].value;
		else node[yyval = ++cnt].value = node[yyvsp[-2]].value;
		node[yyval].dimension.push_back(node[yyvsp[-2]].value);
	}
#line 1816 "y.tab.c"
    break;

  case 14:
#line 310 "./grammar.y"
                                      {
		//重名，报错
		if(symbol_table[level].find(L[yyvsp[-3]]) != symbol_table[level].end()){
			yyerror("Const Redefinition Error");
			exit(0);
		}
		char tmp[100];
		//全局变量，level==0
		if(level == 0){
			//不是常数，报错
			if(!node[yyvsp[0]].is_const){
				printf("Const Definition Error\n");
				exit(0);
			}
			//没有数组部分
			if (!yyvsp[-2]){
				Assemble.push_back("\t.section\t.rodata\n");
				Assemble.push_back("\t.align\t4\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, 4\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.long\t%d\n", node[yyvsp[0]].value); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[yyvsp[-3]]] = Variable(Int_Const, node[yyvsp[0]].value, 1);
			}
			//else
		}
		//局部变量
		else{
			if (!yyvsp[-2]){
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				sprintf (tmp, "\tmovl\t$%d, %%edi\n", node[yyvsp[0]].value); Assemble.push_back(tmp);
				sprintf (tmp, "\tmovl\t%%edi, %d(%rbp)\n", offset); Assemble.push_back(tmp);
				symbol_table[level][L[yyvsp[-3]]] = Variable(Int_Const, node[yyvsp[0]].value, offset);
			}
			//else
		}
		
	}
#line 1861 "y.tab.c"
    break;

  case 15:
#line 353 "./grammar.y"
                           {}
#line 1867 "y.tab.c"
    break;

  case 16:
#line 354 "./grammar.y"
                                        {}
#line 1873 "y.tab.c"
    break;

  case 17:
#line 357 "./grammar.y"
                      {yyval = yyvsp[0];}
#line 1879 "y.tab.c"
    break;

  case 18:
#line 358 "./grammar.y"
                 {}
#line 1885 "y.tab.c"
    break;

  case 19:
#line 359 "./grammar.y"
                               {}
#line 1891 "y.tab.c"
    break;

  case 20:
#line 362 "./grammar.y"
               {}
#line 1897 "y.tab.c"
    break;

  case 21:
#line 363 "./grammar.y"
                            {}
#line 1903 "y.tab.c"
    break;

  case 22:
#line 366 "./grammar.y"
                        {}
#line 1909 "y.tab.c"
    break;

  case 23:
#line 367 "./grammar.y"
                        {printf("Variable Definition Error\n");}
#line 1915 "y.tab.c"
    break;

  case 24:
#line 372 "./grammar.y"
                   {
		//判断是否重名
		if(symbol_table[level].find(L[yyvsp[-1]]) != symbol_table[level].end()){
			yyerror("Variable Redefinition Error");
			exit(0);
		}
		char tmp[100];
		//全局变量/数组
		if(level == 0){
			//全局变量，计算相应的 size，对于变量初值设为.long 0 或.zero 4 即可
			if(!yyvsp[0]){
				sprintf (tmp, "\t.globl\t%s\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t4\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, 4\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				Assemble.push_back("\t.long\t0\n");
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[yyvsp[-1]]] = Variable(Int, 0, 1);
			}
			//全局数组，计算相应的 size，对于数组初始化值为.zero 4 * size
			else{
				sprintf (tmp, "\t.globl\t%s\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t32\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, %d\n", L[yyvsp[-1]], node[yyvsp[0]].value * 4); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[yyvsp[-1]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.zero\t%d\n", node[yyvsp[0]].value * 4); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[yyvsp[-1]]] = Variable(Array, 0, 1, node[yyvsp[0]].dimension);
			}
		}
		//局部变量/数组
		else{
			//局部变量，栈上分配相应空间即可
			if(!yyvsp[0]){
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				symbol_table[level][L[yyvsp[-1]]] = Variable(Int, 0, offset);
			}
			//局部数组
			else{
				offset -= 4 * node[yyvsp[0]].value;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", node[yyvsp[0]].value * 4); Assemble.push_back(tmp);
				symbol_table[level][L[yyvsp[-1]]] = Variable(Array, 0, offset, node[yyvsp[0]].dimension);
			}
		}
	}
#line 1970 "y.tab.c"
    break;

  case 25:
#line 423 "./grammar.y"
                                 {
		if(symbol_table[level].find(L[yyvsp[-3]]) != symbol_table[level].end()){
			yyerror("Variable Redefinition Error");
			exit(0);
		}
		char tmp[100];
		//全局变量/数组
		if(!level){
			//全局变量，根据 InitVal 的返回值情况判断类型是否匹配
			if (!yyvsp[-2]){
				if(!yyvsp[0] || !node[yyvsp[0]].is_const){
					yyerror("Initializer Error");
					exit(0);
				}
				sprintf (tmp, "\t.globl\t%s\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t4\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, 4\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.long\t%d\n", node[yyvsp[0]].value); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[yyvsp[-3]]] = Variable(Int, node[yyvsp[0]].value, 1);
			}
			//全局数组，数组应判断赋值的个数是否超过了数组大小
			else {
				if(yyvsp[0]){
					yyerror("Initializer Error");
					exit(0);
				}
				if(ArrInitVal.size() > node[yyvsp[-2]].value){
					yyerror("Too Many Initializers Error");
					exit(0);
				}
				sprintf (tmp, "\t.globl\t%s\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				Assemble.push_back("\t.data\n");
				Assemble.push_back("\t.align\t32\n");
				sprintf (tmp, "\t.type\t%s, @object\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				sprintf (tmp, "\t.size\t%s, %d\n", L[yyvsp[-3]], node[yyvsp[-2]].value * 4); Assemble.push_back(tmp);
				sprintf (tmp, "%s:\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
				for(auto x : ArrInitVal) {
					sprintf (tmp, "\t.long\t%d\n", node[x].value);  Assemble.push_back(tmp);
				}
				sprintf (tmp, "\t.zero\t%d\n", node[yyvsp[-2]].value * 4 - ArrInitVal.size() * 4); Assemble.push_back(tmp);
				Assemble.push_back("\t.text\n");
				symbol_table[0][L[yyvsp[-3]]] = Variable(Array, 0, 1, node[yyvsp[-2]].dimension);
				ArrInitVal.clear();
			}
		}
		//局部变量/数组
		else{
			//局部变量，这里的赋值可能不是常数
			//需要按照地址通过 var2reg 函数计算，然后放置到相应的地址位置
			if (!yyvsp[-2]){
				if(!yyvsp[0]){
					yyerror("Initializer Error");
					exit(0);
				}
				var2reg(yyvsp[0], "edi");
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				//将该值存入栈中
				sprintf (tmp, "\tmovl\t%%edi, %d(%rbp)\n", offset); Assemble.push_back(tmp);
				symbol_table[level][L[yyvsp[-3]]] = Variable(Int, node[yyvsp[0]].value, offset);
			}
			//数组
			else {
				if(yyvsp[0]){
					yyerror("Initializer Error");
					exit(0);
				}
				if(ArrInitVal.size() > node[yyvsp[-2]].value){
					yyerror("Too Many Initializers Error");
					exit(0);
				}
				//一次性减offset
				offset -= 4 * node[yyvsp[-2]].value;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", 4 * node[yyvsp[-2]].value); Assemble.push_back(tmp);
				//从下至上存入数组的值到栈中
				for(int i = 0; i < ArrInitVal.size(); ++i){
					var2reg(ArrInitVal[i], "edi");
					sprintf (tmp, "\tmovl\t%%edi, %d(%rbp)\n", offset + i * 4);  Assemble.push_back(tmp);
				}
				symbol_table[level][L[yyvsp[-3]]] = Variable(Array, 0, offset, node[yyvsp[-2]].dimension);
				ArrInitVal.clear();
			} 
		}
	}
#line 2063 "y.tab.c"
    break;

  case 26:
#line 516 "./grammar.y"
                  {
		if(!level && !node[yyvsp[0]].is_const){		
			yyerror("Initializer Error");
			exit(0);
		}
		ArrInitVal.push_back(yyvsp[0]);
	}
#line 2075 "y.tab.c"
    break;

  case 27:
#line 523 "./grammar.y"
                               {
		if(!level && !node[yyvsp[0]].is_const){		
			yyerror("Initializer Error");
			exit(0);
		}
		ArrInitVal.push_back(yyvsp[0]);
	}
#line 2087 "y.tab.c"
    break;

  case 28:
#line 532 "./grammar.y"
            {yyval = yyvsp[0];}
#line 2093 "y.tab.c"
    break;

  case 29:
#line 533 "./grammar.y"
                 {yyval = 0;}
#line 2099 "y.tab.c"
    break;

  case 30:
#line 534 "./grammar.y"
                          {yyval = 0;}
#line 2105 "y.tab.c"
    break;

  case 31:
#line 541 "./grammar.y"
          {
		strcpy(funcname, L[yyvsp[0]]);
		Para.clear();
	}
#line 2114 "y.tab.c"
    break;

  case 32:
#line 546 "./grammar.y"
                        {}
#line 2120 "y.tab.c"
    break;

  case 33:
#line 547 "./grammar.y"
                                    {}
#line 2126 "y.tab.c"
    break;

  case 34:
#line 550 "./grammar.y"
                          {Para.push_back(L[yyvsp[-1]]);}
#line 2132 "y.tab.c"
    break;

  case 35:
#line 553 "./grammar.y"
                   {}
#line 2138 "y.tab.c"
    break;

  case 36:
#line 554 "./grammar.y"
                       {if(yyvsp[0]) yyval = yyvsp[0];}
#line 2144 "y.tab.c"
    break;

  case 37:
#line 557 "./grammar.y"
                  {yyval = 0;}
#line 2150 "y.tab.c"
    break;

  case 38:
#line 558 "./grammar.y"
                           {
		yyval = (yyvsp[0]) ? yyvsp[0] : ++cnt;
		node[yyval].dimension.push_back(yyvsp[-2]);
	}
#line 2159 "y.tab.c"
    break;

  case 39:
#line 565 "./grammar.y"
                                            {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
#line 2173 "y.tab.c"
    break;

  case 40:
#line 574 "./grammar.y"
                                           {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
#line 2187 "y.tab.c"
    break;

  case 41:
#line 583 "./grammar.y"
                                                              {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
#line 2201 "y.tab.c"
    break;

  case 42:
#line 593 "./grammar.y"
                                                            {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0, is_func_void = false;
	}
#line 2215 "y.tab.c"
    break;

  case 43:
#line 602 "./grammar.y"
                                           {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		sprintf(tmp, "\taddq\t$%d, %rsp\n", -offset); 
		Assemble.push_back(tmp);
		ret_func_pop();
		offset = 0;
	}
#line 2229 "y.tab.c"
    break;

  case 44:
#line 611 "./grammar.y"
                         {printf("Function Parameter Error\n");}
#line 2235 "y.tab.c"
    break;

  case 45:
#line 612 "./grammar.y"
                          {printf("Function Parameter Error\n");}
#line 2241 "y.tab.c"
    break;

  case 46:
#line 618 "./grammar.y"
                      {
		++level;
		map<string, Variable> x;
		symbol_table.push_back(x);
		Assemble.push_back("\t.globl\tmain\n");
		Assemble.push_back("\t.type\tmain, @function\n");
		Assemble.push_back("main:\n");
		call_func_push();
	}
#line 2255 "y.tab.c"
    break;

  case 47:
#line 629 "./grammar.y"
                      {
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
#line 2279 "y.tab.c"
    break;

  case 48:
#line 650 "./grammar.y"
                     {
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
#line 2301 "y.tab.c"
    break;

  case 49:
#line 669 "./grammar.y"
                           {
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
#line 2330 "y.tab.c"
    break;

  case 50:
#line 695 "./grammar.y"
                          {
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
#line 2359 "y.tab.c"
    break;

  case 51:
#line 730 "./grammar.y"
               {}
#line 2365 "y.tab.c"
    break;

  case 52:
#line 731 "./grammar.y"
                           {}
#line 2371 "y.tab.c"
    break;

  case 53:
#line 732 "./grammar.y"
                       {printf("Block Error\n");}
#line 2377 "y.tab.c"
    break;

  case 54:
#line 735 "./grammar.y"
                    {}
#line 2383 "y.tab.c"
    break;

  case 55:
#line 736 "./grammar.y"
              {}
#line 2389 "y.tab.c"
    break;

  case 56:
#line 737 "./grammar.y"
                        {}
#line 2395 "y.tab.c"
    break;

  case 57:
#line 738 "./grammar.y"
                        {}
#line 2401 "y.tab.c"
    break;

  case 58:
#line 742 "./grammar.y"
                        {
		if(node[yyvsp[-3]].is_const){
			yyerror("Const Error");
			exit(0);
		}
		var2reg(yyvsp[-1], "r9d");
		reg2var("r9d", yyvsp[-3]);
	}
#line 2414 "y.tab.c"
    break;

  case 59:
#line 750 "./grammar.y"
                 {}
#line 2420 "y.tab.c"
    break;

  case 60:
#line 751 "./grammar.y"
             {}
#line 2426 "y.tab.c"
    break;

  case 61:
#line 752 "./grammar.y"
               {}
#line 2432 "y.tab.c"
    break;

  case 62:
#line 755 "./grammar.y"
                                                                               {
		--level;
		symbol_table.pop_back();
		char tmp[100];
		++num_of_assem;
		sprintf (tmp, ".L%d:\n", num_of_assem); 
		Assemble.push_back(tmp);
		for(auto x : node[yyvsp[-5]].truelist) Assemble[x] += ".L" + to_string(yyvsp[-3]) + "\n";
		for(auto x : node[yyvsp[-5]].falselist) Assemble[x] += ".L" + to_string(num_of_assem) + "\n";
	}
#line 2447 "y.tab.c"
    break;

  case 63:
#line 766 "./grammar.y"
                                                                                                                       { 
		--level;
		symbol_table.pop_back();
		for(auto x : node[yyvsp[-12]].truelist) Assemble[x] += ".L" + to_string(yyvsp[-10]) + "\n";
		for(auto x : node[yyvsp[-12]].falselist) Assemble[x] += ".L" + to_string(yyvsp[-4]) + "\n";
		Assemble[node[yyvsp[-5]].truelist[0]] += ".L" + to_string(yyvsp[0]) + "\n";
	}
#line 2459 "y.tab.c"
    break;

  case 64:
#line 774 "./grammar.y"
                                                                                     {
		--level;
		symbol_table.pop_back();
		backpatch(node[yyvsp[-5]].truelist, yyvsp[-2]);
		char tmp[100];
		sprintf (tmp, "\tjmp\t.L%d\n", yyvsp[-8]); Assemble.push_back(tmp);
		++num_of_assem;
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		backpatch(node[yyvsp[-5]].falselist, node[yyvsp[-3]].quad);
		backpatch(node[yyvsp[-3]].truelist, num_of_assem);
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
			Assemble[it.first] += ".L" + to_string(yyvsp[-8]) + "\n";
		}
        	continuelist.pop_back();
 	}
#line 2489 "y.tab.c"
    break;

  case 65:
#line 800 "./grammar.y"
                   {
		Assemble.push_back("wait");
		Assemble.push_back("\tjmp\t");
		(*breaklist.rbegin()).push_back(make_pair(Assemble.size() - 1, offset));
	}
#line 2499 "y.tab.c"
    break;

  case 66:
#line 806 "./grammar.y"
                      {
		Assemble.push_back("wait");
		Assemble.push_back("\tjmp\t");
		(*continuelist.rbegin()).push_back(make_pair(Assemble.size() - 1, offset));
	}
#line 2509 "y.tab.c"
    break;

  case 67:
#line 812 "./grammar.y"
                        {
		if(is_func_void){
			yyerror("Return Value Error");
			exit(0);
		}
		char tmp[100];
		var2reg(yyvsp[-1], "eax");
		sprintf (tmp, "\taddq\t$%d, %rsp\n", -offset); Assemble.push_back(tmp);
		ret_func_pop();
	}
#line 2524 "y.tab.c"
    break;

  case 68:
#line 823 "./grammar.y"
                    {
		if(!is_func_void){
			yyerror("Return Value Error");
			exit(0);
		}
		char tmp[100];
		sprintf (tmp, "\taddq\t$%d, %rsp\n", -offset); Assemble.push_back(tmp);
		ret_func_pop();
	}
#line 2538 "y.tab.c"
    break;

  case 69:
#line 832 "./grammar.y"
                   {printf("Statement Error\n");}
#line 2544 "y.tab.c"
    break;

  case 70:
#line 836 "./grammar.y"
                    {
		yyval = ++num_of_assem;
		char tmp[100];
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
	}
#line 2554 "y.tab.c"
    break;

  case 71:
#line 845 "./grammar.y"
                      {
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
#line 2571 "y.tab.c"
    break;

  case 72:
#line 860 "./grammar.y"
                     {
		char tmp[100];
		int last = *p_offset.rbegin();
		sprintf (tmp, "\taddq\t$%d, %rsp\n", last - offset); Assemble.push_back(tmp);
		p_offset.pop_back();
		offset = last;
	}
#line 2583 "y.tab.c"
    break;

  case 73:
#line 869 "./grammar.y"
                     {
		Assemble.push_back("\tjmp\t");
		node[yyval = ++cnt].truelist.push_back(Assemble.size() - 1);
	}
#line 2592 "y.tab.c"
    break;

  case 74:
#line 876 "./grammar.y"
                      {
		yyval = ++num_of_assem;
		char tmp[100];
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		vector< pair<int, int> > x, y;
		breaklist.push_back(x);
		continuelist.push_back(y);
	}
#line 2605 "y.tab.c"
    break;

  case 75:
#line 886 "./grammar.y"
                    {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf (tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		int last = *p_offset.rbegin();
		sprintf (tmp, "\taddq\t$%d, %rsp\n", last - offset); Assemble.push_back(tmp);
		Assemble.push_back("\tjmp\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
	}
#line 2619 "y.tab.c"
    break;

  case 76:
#line 897 "./grammar.y"
              {yyval = yyvsp[0];}
#line 2625 "y.tab.c"
    break;

  case 77:
#line 901 "./grammar.y"
              {yyval = yyvsp[0];}
#line 2631 "y.tab.c"
    break;

  case 78:
#line 902 "./grammar.y"
               {printf("Condition Error\n");}
#line 2637 "y.tab.c"
    break;

  case 79:
#line 906 "./grammar.y"
                {
		bool used = false;
		//非数组，int 型变量/常量元素直接从符号表中读取即可
		if(!yyvsp[0]){
			for(int i = level; i >= 0; --i)
				if(symbol_table[i].find(L[yyvsp[-1]]) != symbol_table[i].end()){
					used = true;
					Variable cur = symbol_table[i][L[yyvsp[-1]]];
					yyval = ++cnt;
					if(cur.type == Int_Const) {
						node[yyval].is_const = true;
						node[yyval].value = cur.value;
					}
					else {
						node[yyval].is_const = false;
						node[yyval].offset = cur.offset;
						if(!i) node[yyval].name = string(L[yyvsp[-1]]);
					}
					break;
				}
		}
		//数组，计算数组偏移地址
		else{
			char tmp[100];
			//在最后一层找到最近一次更新的值
			for(int i = level; i >= 0; --i)
				if(symbol_table[i].find(L[yyvsp[-1]]) != symbol_table[i].end()){
					Variable cur = symbol_table[i][L[yyvsp[-1]]];
					if(cur.type != Array || node[yyvsp[0]].dimension.size() != cur.dimension.size()) continue;
					used = true;
					int x = 1;
					offset -= 4;
					Assemble.push_back("\tsubq\t$4, %rsp\n");
					sprintf (tmp, "\tmovl\t$0, %d(%rbp)\n", offset); Assemble.push_back(tmp);
					int z = offset;
					for(int j = 0; j < cur.dimension.size(); ++j){
						var2reg(node[yyvsp[0]].dimension[j], "r8d");
						sprintf (tmp, "\timull\t$%d, %r8d\n", x); Assemble.push_back(tmp);
						sprintf (tmp, "\taddl\t%d(%rbp), %r8d\n", z); Assemble.push_back(tmp);
						sprintf (tmp, "\tmovl\t%%r8d, %d(%rbp)\n", z); Assemble.push_back(tmp);
						x *= cur.dimension[j];
					}
					yyval = ++cnt;
					node[yyval].is_arr = true;
					if(cur.type == Int_Const){
						node[yyval].is_const = true;
						node[yyval].value = cur.value;
					}
					else{
						node[yyval].is_const = false;
						node[yyval].offset = cur.offset;
						node[yyval].offset_of_arr = z;
						if(!i) node[yyval].name = string(L[yyvsp[-1]]);
					}
					break;
				}
		}
		if(!used){
			yyerror("Reference Undefined Variable");
			exit(0);
		}
	}
#line 2704 "y.tab.c"
    break;

  case 80:
#line 970 "./grammar.y"
                       {yyval = yyvsp[-1];}
#line 2710 "y.tab.c"
    break;

  case 81:
#line 971 "./grammar.y"
              {yyval = yyvsp[0];}
#line 2716 "y.tab.c"
    break;

  case 82:
#line 972 "./grammar.y"
                   {node[yyval = ++cnt].value = yyvsp[0], node[yyval].is_const = true;}
#line 2722 "y.tab.c"
    break;

  case 83:
#line 977 "./grammar.y"
                {
		yyval = yyvsp[0];
		node[yyval].para_name.push_back(node[yyvsp[0]].name);
		node[yyval].para_val.push_back(node[yyvsp[0]].value);
		node[yyval].para_offset.push_back(node[yyvsp[0]].offset);
		node[yyval].para_offset_of_arr.push_back(node[yyvsp[0]].offset_of_arr);
		node[yyval].const_para.push_back(node[yyvsp[0]].is_const);
		node[yyval].arr_para.push_back(node[yyvsp[0]].is_arr);
	}
#line 2736 "y.tab.c"
    break;

  case 84:
#line 986 "./grammar.y"
                             {
		yyval = yyvsp[-2];
		node[yyval].para_name.push_back(node[yyvsp[0]].name);
		node[yyval].para_val.push_back(node[yyvsp[0]].value);
		node[yyval].para_offset.push_back(node[yyvsp[0]].offset);
		node[yyval].para_offset_of_arr.push_back(node[yyvsp[0]].offset_of_arr);
		node[yyval].const_para.push_back(node[yyvsp[0]].is_const);
		node[yyval].arr_para.push_back(node[yyvsp[0]].is_arr);
	}
#line 2750 "y.tab.c"
    break;

  case 85:
#line 997 "./grammar.y"
                    {yyval = yyvsp[0];}
#line 2756 "y.tab.c"
    break;

  case 86:
#line 999 "./grammar.y"
                    {
		if(symbol_table[0].find(L[yyvsp[-2]]) == symbol_table[0].end()){
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
		sprintf (tmp, "\tcall\t%s\n", L[yyvsp[-2]]); Assemble.push_back(tmp);
		Variable function = symbol_table[0][L[yyvsp[-2]]];
		if(function.type == int_Function){
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n"); 
			sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}	 
	}
#line 2782 "y.tab.c"
    break;

  case 87:
#line 1021 "./grammar.y"
                                {
		//scanf函数
		if(!strcmp(L[yyvsp[-3]], "scanf")){
			if(node[yyvsp[-1]].para_name.size() != 1){
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
			lea_para2reg(yyvsp[-1], 0, "rsi");
			Assemble.push_back("\tleaq\t.LC0(%rip), %rdi\n");
			Assemble.push_back("\tmovl\t$0, %eax\n");
			Assemble.push_back("\tcall\t__isoc99_scanf@PLT\n");
		}
		//printf 函数
		else if(!strcmp(L[yyvsp[-3]], "printf")){
			if(node[yyvsp[-1]].para_name.size() != 1){
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
			para2reg(yyvsp[-1], 0, "esi");
			Assemble.push_back("\tleaq\t.LC1(%rip), %rdi\n");
			Assemble.push_back("\tmovl\t$0, %eax\n");
			Assemble.push_back("\tcall\tprintf@PLT\n");
		}
		//其他函数
		//对齐， 将每个参数逐一插入栈中
		//有返回值的函数还应在调用后将 eax 寄存器的值存入栈中：
		else{
			//查询是否已经定义
			if(symbol_table[0].find(L[yyvsp[-3]]) == symbol_table[0].end()){
				yyerror("Funciton Undefined Error");
				exit(0);
			}
			char tmp[100];
			//对齐
			if((-(offset - 4 * node[yyvsp[-1]].para_name.size())) % 16){
				int padding = 16 - abs(offset) % 16;
				offset -= padding;
				sprintf (tmp, "\tsubq\t$%d, %rsp\n", padding); Assemble.push_back(tmp);	 
			}
			//参数逐一入栈
			for(int i = node[yyvsp[-1]].para_name.size() - 1; i >= 0 ; --i){
				para2reg(yyvsp[-1], i, "r8d");
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				sprintf (tmp, "\tmovl\t%%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			}
			//调用函数
			sprintf (tmp, "\tcall\t%s\n", L[yyvsp[-3]]); Assemble.push_back(tmp);
			Variable function = symbol_table[0][L[yyvsp[-3]]];
			//传返回地址
			if(function.type == int_Function){
				offset -= 4;
				Assemble.push_back("\tsubq\t$4, %rsp\n");
				sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
				node[yyval = ++cnt].offset = offset;
			}	
		}
	}
#line 2859 "y.tab.c"
    break;

  case 88:
#line 1093 "./grammar.y"
                      {yyval = yyvsp[0];}
#line 2865 "y.tab.c"
    break;

  case 89:
#line 1094 "./grammar.y"
                      {
		if(node[yyvsp[0]].is_const) node[yyval = yyvsp[0]].value = -node[yyvsp[0]].value;
		else{
			char tmp[100];
			var2reg(yyvsp[0], "r8d");
			Assemble.push_back("\tnegl\t%r8d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}
	}
#line 2882 "y.tab.c"
    break;

  case 90:
#line 1107 "./grammar.y"
                      {
		char tmp[100];
		var2reg(yyvsp[0], "eax");	
		Assemble.push_back("\ttestl\t%eax, %eax\n");
		Assemble.push_back("\tsete\t%al\n");
		Assemble.push_back("\tmovzbl\t%al, %eax\n");
		offset -= 4;
		Assemble.push_back("\tsubq\t$4, %rsp\n");
		sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
		node[yyval = ++cnt].offset = offset;
	}
#line 2898 "y.tab.c"
    break;

  case 91:
#line 1121 "./grammar.y"
                {yyval = yyvsp[0];}
#line 2904 "y.tab.c"
    break;

  case 92:
#line 1123 "./grammar.y"
                             {
		if(node[yyvsp[-2]].is_const && node[yyvsp[0]].is_const)
			node[yyval = ++cnt].value = node[yyvsp[-2]].value * node[yyvsp[0]].value, node[yyval].is_const = 1;
		else{
			char tmp[100];
			var2reg(yyvsp[-2], "r8d");
			var2reg(yyvsp[0], "r9d");
			Assemble.push_back("\timull\t%r8d, %r9d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r9d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}
	}
#line 2923 "y.tab.c"
    break;

  case 93:
#line 1138 "./grammar.y"
                             {
		if(node[yyvsp[-2]].is_const && node[yyvsp[0]].is_const)
			node[yyval = ++cnt].value = node[yyvsp[-2]].value / node[yyvsp[0]].value, node[yyval].is_const = 1;
		else{
			char tmp[100];
			var2reg(yyvsp[-2], "eax");
			var2reg(yyvsp[0], "r9d");
			Assemble.push_back("\tcltd\n");
			Assemble.push_back("\tidivl\t%r9d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%%eax, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}
	}
#line 2943 "y.tab.c"
    break;

  case 94:
#line 1154 "./grammar.y"
                             {
		if(node[yyvsp[-2]].is_const && node[yyvsp[0]].is_const)
			node[yyval = ++cnt].value = node[yyvsp[-2]].value % node[yyvsp[0]].value, node[yyval].is_const = 1;
		else{
			char tmp[100];
			var2reg(yyvsp[-2], "eax");
			var2reg(yyvsp[0], "r9d");
			Assemble.push_back("\tcltd\n");
			Assemble.push_back("\tidivl\t%r9d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%%edx, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}
	}
#line 2963 "y.tab.c"
    break;

  case 95:
#line 1172 "./grammar.y"
               {yyval = yyvsp[0];}
#line 2969 "y.tab.c"
    break;

  case 96:
#line 1175 "./grammar.y"
                           {
		if(node[yyvsp[-2]].is_const && node[yyvsp[0]].is_const)
			node[yyval = ++cnt].value = node[yyvsp[-2]].value + node[yyvsp[0]].value, node[yyval].is_const = 1;
		else{
			char tmp[100];
			var2reg(yyvsp[-2], "r8d");
			var2reg(yyvsp[0], "r9d");
			Assemble.push_back("\taddl\t%r9d, %r8d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}
	}
#line 2988 "y.tab.c"
    break;

  case 97:
#line 1190 "./grammar.y"
                           {
		if(node[yyvsp[-2]].is_const && node[yyvsp[0]].is_const)
			node[yyval = ++cnt].value = node[yyvsp[-2]].value - node[yyvsp[0]].value, node[yyval].is_const = 1;
		else{
			char tmp[100];
			var2reg(yyvsp[-2], "r8d");
			var2reg(yyvsp[0], "r9d");
			Assemble.push_back("\tsubl\t%r9d, %r8d\n");
			offset -= 4;
			Assemble.push_back("\tsubq\t$4, %rsp\n");
			sprintf (tmp, "\tmovl\t%r8d, %d(%rbp)\n", offset); Assemble.push_back(tmp);
			node[yyval = ++cnt].offset = offset;
		}
	}
#line 3007 "y.tab.c"
    break;

  case 98:
#line 1207 "./grammar.y"
               {yyval = yyvsp[0];}
#line 3013 "y.tab.c"
    break;

  case 99:
#line 1211 "./grammar.y"
                           {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg(yyvsp[-2], "r8d");
		var2reg(yyvsp[0], "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjl\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjge\t");
		node[yyval].falselist.push_back(Assemble.size() - 1);
	}
#line 3030 "y.tab.c"
    break;

  case 100:
#line 1223 "./grammar.y"
                           {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg(yyvsp[-2], "r8d");
		var2reg(yyvsp[0], "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjg\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjle\t");
		node[yyval].falselist.push_back(Assemble.size() - 1);
	}
#line 3047 "y.tab.c"
    break;

  case 101:
#line 1235 "./grammar.y"
                                 {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg(yyvsp[-2], "r8d");
		var2reg(yyvsp[0], "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjle\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjg\t");
		node[yyval].falselist.push_back(Assemble.size() - 1);
	}
#line 3064 "y.tab.c"
    break;

  case 102:
#line 1247 "./grammar.y"
                                    {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg(yyvsp[-2], "r8d");
		var2reg(yyvsp[0], "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjge\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjl\t");
		node[yyval].falselist.push_back(Assemble.size() - 1);
	}
#line 3081 "y.tab.c"
    break;

  case 103:
#line 1261 "./grammar.y"
               {yyval = yyvsp[0];}
#line 3087 "y.tab.c"
    break;

  case 104:
#line 1262 "./grammar.y"
                            {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg(yyvsp[-2], "r8d");
		var2reg(yyvsp[0], "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tje\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tjne\t");
		node[yyval].falselist.push_back(Assemble.size() - 1);
	}
#line 3104 "y.tab.c"
    break;

  case 105:
#line 1274 "./grammar.y"
                               {
		char tmp[100];
		node[yyval = ++cnt].quad = ++num_of_assem;
		sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
		var2reg(yyvsp[-2], "r8d");
		var2reg(yyvsp[0], "r9d");
		Assemble.push_back("\tcmpl\t%r9d, %r8d\n");
		Assemble.push_back("\tjne\t");
		node[yyval].truelist.push_back(Assemble.size() - 1);
		Assemble.push_back("\tje\t");
		node[yyval].falselist.push_back(Assemble.size() - 1);
	}
#line 3121 "y.tab.c"
    break;

  case 106:
#line 1288 "./grammar.y"
              {
		yyval = yyvsp[0];
		if(!node[yyval].quad){
			char tmp[100];
			node[yyval = ++cnt].quad = ++num_of_assem;
			sprintf(tmp, ".L%d:\n", num_of_assem); Assemble.push_back(tmp);
			var2reg(yyvsp[0], "r8d");
			Assemble.push_back("\tcmpl\t$0, %r8d\n");
			Assemble.push_back("\tjne\t");
			node[yyval].truelist.push_back(Assemble.size() - 1);
			Assemble.push_back("\tje\t");
			node[yyval].falselist.push_back(Assemble.size() - 1);
		}
	}
#line 3140 "y.tab.c"
    break;

  case 107:
#line 1303 "./grammar.y"
                           {
		backpatch(node[yyvsp[-2]].truelist, node[yyvsp[0]].quad);
		node[yyval].falselist = merge(node[yyvsp[-2]].falselist, node[yyvsp[0]].falselist);
		node[yyval].truelist = node[yyvsp[0]].truelist;
		node[yyval].quad = node[yyvsp[-2]].quad;
	}
#line 3151 "y.tab.c"
    break;

  case 108:
#line 1311 "./grammar.y"
               { yyval = yyvsp[0]; }
#line 3157 "y.tab.c"
    break;

  case 109:
#line 1313 "./grammar.y"
                           {
		backpatch(node[yyvsp[-2]].falselist, node[yyvsp[0]].quad);
		node[yyval].truelist = merge(node[yyvsp[-2]].truelist, node[yyvsp[0]].truelist);
		node[yyval].falselist = node[yyvsp[0]].falselist;
		node[yyval].quad = node[yyvsp[-2]].quad;
	}
#line 3168 "y.tab.c"
    break;

  case 110:
#line 1321 "./grammar.y"
                {
		yyval = yyvsp[0];
		if(node[yyval].is_const == false){
			yyerror("Const Error");	
			exit(0);
		}
	}
#line 3180 "y.tab.c"
    break;


#line 3184 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 1329 "./grammar.y"


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
