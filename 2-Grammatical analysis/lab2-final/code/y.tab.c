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

#line 106 "y.tab.c"

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
    IDENTIFIER = 258,
    CONST_NUM = 259,
    MAIN = 260,
    TYPE = 261,
    IF = 262,
    ELSE = 263,
    ELIF = 264,
    WHILE = 265,
    DO = 266,
    BREAK = 267,
    CONTINUE = 268,
    FOR = 269,
    RETURN = 270,
    AND = 271,
    OR = 272,
    EQUAL = 273,
    NOTEQUAL = 274,
    LESS = 275,
    LESSEQUAL = 276,
    GREATER = 277,
    GREATEREQUAL = 278,
    SWITCH = 279,
    CASE = 280,
    UNSIGNED = 281,
    SIGNED = 282,
    STATIC = 283,
    VOID = 284,
    AUTO = 285,
    STRUCT = 286,
    CONST = 287,
    PLUS = 288,
    MINUS = 289,
    MULTI = 290,
    DIVIDE = 291,
    MOD = 292,
    ASSIGN = 293,
    BITAND = 294,
    BITOR = 295,
    BITNOT = 296,
    XOR = 297,
    NOT = 298,
    LEFTSHIFT = 299,
    RIGHTSHIFT = 300,
    PLUSPLUS = 301,
    MINUSMINUS = 302,
    PLUSEQUAL = 303,
    MINUSEQUAL = 304,
    MULTIEQUAL = 305,
    DIVIDEEQUAL = 306,
    COLON = 307,
    QUESMARK = 308,
    FULLSTP = 309,
    PTO = 310,
    COMMA = 311,
    SEMICOLON = 312
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONST_NUM 259
#define MAIN 260
#define TYPE 261
#define IF 262
#define ELSE 263
#define ELIF 264
#define WHILE 265
#define DO 266
#define BREAK 267
#define CONTINUE 268
#define FOR 269
#define RETURN 270
#define AND 271
#define OR 272
#define EQUAL 273
#define NOTEQUAL 274
#define LESS 275
#define LESSEQUAL 276
#define GREATER 277
#define GREATEREQUAL 278
#define SWITCH 279
#define CASE 280
#define UNSIGNED 281
#define SIGNED 282
#define STATIC 283
#define VOID 284
#define AUTO 285
#define STRUCT 286
#define CONST 287
#define PLUS 288
#define MINUS 289
#define MULTI 290
#define DIVIDE 291
#define MOD 292
#define ASSIGN 293
#define BITAND 294
#define BITOR 295
#define BITNOT 296
#define XOR 297
#define NOT 298
#define LEFTSHIFT 299
#define RIGHTSHIFT 300
#define PLUSPLUS 301
#define MINUSMINUS 302
#define PLUSEQUAL 303
#define MINUSEQUAL 304
#define MULTIEQUAL 305
#define DIVIDEEQUAL 306
#define COLON 307
#define QUESMARK 308
#define FULLSTP 309
#define PTO 310
#define COMMA 311
#define SEMICOLON 312

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

#define YYUNDEFTOK  2
#define YYMAXUTOK   312


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    59,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   105,   105,   110,   117,   122,   129,   134,   139,   146,
     151,   158,   163,   170,   175,   180,   185,   190,   195,   200,
     205,   210,   215,   220,   227,   232,   239,   246,   253,   258,
     263,   268,   275,   280,   287,   292,   297,   302,   309,   314,
     319,   324,   332,   337,   342,   349,   354,   359,   364,   371,
     376,   381,   388,   393,   398,   405,   410,   417,   422,   427,
     434,   439,   446,   453,   458,   465,   470,   475,   480,   485,
     490,   495,   502,   507,   514,   519,   526
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONST_NUM", "MAIN",
  "TYPE", "IF", "ELSE", "ELIF", "WHILE", "DO", "BREAK", "CONTINUE", "FOR",
  "RETURN", "AND", "OR", "EQUAL", "NOTEQUAL", "LESS", "LESSEQUAL",
  "GREATER", "GREATEREQUAL", "SWITCH", "CASE", "UNSIGNED", "SIGNED",
  "STATIC", "VOID", "AUTO", "STRUCT", "CONST", "PLUS", "MINUS", "MULTI",
  "DIVIDE", "MOD", "ASSIGN", "BITAND", "BITOR", "BITNOT", "XOR", "NOT",
  "LEFTSHIFT", "RIGHTSHIFT", "PLUSPLUS", "MINUSMINUS", "PLUSEQUAL",
  "MINUSEQUAL", "MULTIEQUAL", "DIVIDEEQUAL", "COLON", "QUESMARK",
  "FULLSTP", "PTO", "COMMA", "SEMICOLON", "'('", "')'", "'{'", "'}'",
  "'['", "']'", "$accept", "CompUnit", "OtherCompUnit", "FuncDef",
  "FuncFParam", "FuncFParams", "Stmt", "StmtOrBlock", "IfBlock", "Block",
  "BlockItem", "Decl", "VarDecl", "SeqVarDecl", "ConstArrayIndex",
  "ArrayIndex", "AddExp", "MulExp", "PrimaryExp", "UnaryExp", "LOrExp",
  "Cond", "LAndExp", "CompExp", "FuncRParams", "LVal", "RelExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,    40,    41,
     123,   125,    91,    93
};
# endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,    22,    28,    38,   -73,   -73,   -73,    -8,    -7,   -16,
      50,   -73,   -73,    56,   -73,   107,    -5,     1,   -73,    53,
      48,    42,    20,   -73,   -19,   -73,    86,   102,   -73,   -73,
     -73,   109,    49,    61,    62,    68,    12,   107,    49,   -73,
      56,   -73,    83,     8,   -73,   107,   107,   107,   107,    42,
      82,   -73,   137,    49,   -73,    68,    86,   -73,   -73,    56,
     -73,   -73,    67,    87,   102,   102,   -73,   -73,   -73,   144,
      90,    91,    49,    93,    94,    95,    17,    82,   146,    98,
      82,    45,    42,   -73,   -73,   -73,   -73,   107,   -73,    42,
     107,   107,   142,   -73,   -73,   107,   -73,    65,   -73,     3,
     -73,   -73,   -73,    99,   -73,    86,   138,   101,   141,   106,
     -73,   104,   100,   105,   -73,   -73,   -73,   -73,   -73,   107,
       3,   107,   107,   107,   107,   107,   107,   107,     3,   107,
       3,   141,   -73,   106,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   108,   -73,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     5,     4,     0,    36,     0,
       0,     1,     3,     0,    33,     0,     0,     0,    37,    44,
       0,    35,     0,    32,    75,    56,    42,    51,    57,    54,
      55,     0,     0,    11,     0,    48,     0,     0,     0,    34,
       0,    41,     0,     0,    74,     0,     0,     0,     0,     9,
       0,     7,     0,     0,    46,    45,    43,     6,    39,     0,
      40,    58,    73,     0,    49,    50,    52,    53,    10,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    14,     0,
      31,     0,    55,    12,     8,    47,    38,     0,    59,    36,
       0,     0,     0,    21,    22,     0,    19,     0,    28,     0,
      27,    29,    23,     0,    72,    76,    62,     0,    60,    63,
      71,     0,     0,     0,    20,    24,    15,    25,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    26,    64,    67,    70,    66,    68,    65,    69,
      16,     0,    18,    17
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   158,   -73,   -73,   110,    -9,   -12,   -73,    -6,
      10,   103,   -73,    -3,   -13,     5,   -15,    96,   -73,    97,
     -73,   -72,    46,    47,    79,   -47,     9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    33,    34,   115,   116,    78,   117,
      79,    80,     7,    23,    18,    19,   105,    27,    28,    29,
     106,   107,   108,   109,    63,    30,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      26,    31,    36,    82,    24,    25,    24,    25,    39,    42,
      70,    24,    25,    71,    72,    73,    74,    75,    76,   111,
      24,    25,    56,   113,     1,     8,    51,     9,    62,    44,
      82,    15,    57,    82,    10,    81,    68,    58,    11,    43,
      54,    77,    20,    17,     1,    45,    46,    84,    13,    14,
       2,    16,    82,    21,    32,    17,    86,   141,    15,    22,
      85,    97,    81,    50,    35,    81,    92,    61,    77,   103,
       2,    77,    62,    82,    96,    55,    40,    41,    45,    46,
      15,    82,    17,    82,    81,    24,    25,    98,    69,    70,
     101,    37,    71,    72,    73,    74,    75,    76,    45,    46,
      45,    46,   102,     6,    17,    81,     6,    38,   132,    50,
      24,    25,    49,    81,     2,    81,   140,    52,   142,    45,
      46,    53,   114,    87,   122,   123,   124,   125,   126,   127,
      17,   134,   135,   136,   137,   138,   139,    47,    48,    59,
      60,    64,    65,    31,    66,    67,    88,    89,    90,    91,
      93,    94,   112,    95,    99,   119,   118,   121,   129,   100,
     120,    12,    83,   128,   130,   131,   104,   143,   133
};

static const yytype_uint8 yycheck[] =
{
      15,     6,    17,    50,     3,     4,     3,     4,    21,    22,
       7,     3,     4,    10,    11,    12,    13,    14,    15,    91,
       3,     4,    37,    95,     6,     3,    32,     5,    43,    24,
      77,    38,    38,    80,     6,    50,    49,    40,     0,    58,
      35,    50,    58,    62,     6,    33,    34,    53,    56,    57,
      32,    58,    99,     3,    59,    62,    59,   129,    38,     3,
      55,    76,    77,    60,    63,    80,    72,    59,    77,    82,
      32,    80,    87,   120,    57,    63,    56,    57,    33,    34,
      38,   128,    62,   130,    99,     3,     4,    77,     6,     7,
      80,    38,    10,    11,    12,    13,    14,    15,    33,    34,
      33,    34,    57,     0,    62,   120,     3,    59,   120,    60,
       3,     4,     3,   128,    32,   130,   128,    56,   130,    33,
      34,    59,    57,    56,    18,    19,    20,    21,    22,    23,
      62,   122,   123,   124,   125,   126,   127,    35,    36,    56,
      57,    45,    46,     6,    47,    48,    59,     3,    58,    58,
      57,    57,    10,    58,     8,    17,    57,    16,    58,    61,
      59,     3,    52,    59,    59,   119,    87,    59,   121
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    32,    65,    66,    67,    75,    76,     3,     5,
       6,     0,    66,    56,    57,    38,    58,    62,    78,    79,
      58,     3,     3,    77,     3,     4,    80,    81,    82,    83,
      89,     6,    59,    68,    69,    63,    80,    38,    59,    78,
      56,    57,    78,    58,    79,    33,    34,    35,    36,     3,
      60,    73,    56,    59,    79,    63,    80,    73,    77,    56,
      57,    59,    80,    88,    81,    81,    83,    83,    78,     6,
       7,    10,    11,    12,    13,    14,    15,    70,    72,    74,
      75,    80,    89,    69,    73,    79,    77,    56,    59,     3,
      58,    58,    73,    57,    57,    58,    57,    80,    74,     8,
      61,    74,    57,    78,    88,    80,    84,    85,    86,    87,
      90,    85,    10,    85,    57,    70,    71,    73,    57,    17,
      59,    16,    18,    19,    20,    21,    22,    23,    59,    58,
      59,    86,    71,    87,    90,    90,    90,    90,    90,    90,
      71,    85,    71,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    73,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    76,    77,    77,
      77,    77,    78,    78,    78,    79,    79,    79,    79,    80,
      80,    80,    81,    81,    81,    82,    82,    83,    83,    83,
      84,    84,    85,    86,    86,    87,    87,    87,    87,    87,
      87,    87,    88,    88,    89,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     5,     5,     6,     2,
       3,     1,     3,     3,     1,     3,     5,     6,     5,     2,
       3,     2,     2,     2,     1,     1,     5,     3,     2,     2,
       1,     1,     3,     2,     4,     3,     2,     3,     4,     3,
       3,     2,     2,     3,     1,     3,     3,     4,     2,     3,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     4,
       1,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     2,     1,     1
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
#line 105 "./grammar.y"
                  { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompUnit");
        printf ("%d:CompUnit -> %d:OtherCompUnit\n", yyval, yyvsp[0]);
    }
#line 1556 "y.tab.c"
    break;

  case 3:
#line 110 "./grammar.y"
                             { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompUnit");
        printf ("%d:CompUnit -> %d:CompUnit %d:OtherCompUnit\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1566 "y.tab.c"
    break;

  case 4:
#line 117 "./grammar.y"
         { 
        yyval = ++cnt;
        strcpy(L[yyval], "OtherCompUnit");
        printf ("%d:OtherCompUnit -> %d:Decl\n", yyval, yyvsp[0]);
    }
#line 1576 "y.tab.c"
    break;

  case 5:
#line 122 "./grammar.y"
              { 
        yyval = ++cnt;
        strcpy(L[yyval], "OtherCompUnit");
        printf ("%d:OtherCompUnit -> %d:FuncDef\n", yyval, yyvsp[0]);
    }
#line 1586 "y.tab.c"
    break;

  case 6:
#line 129 "./grammar.y"
                            { 
        yyval = ++cnt;
        strcpy(L[yyval], "FuncDef");
        printf ("%d:FuncDef -> %d:%s %d:main %d:\\( %d:\\) %d:Block\n", yyval, yyvsp[-4], L[yyvsp[-4]], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1596 "y.tab.c"
    break;

  case 7:
#line 134 "./grammar.y"
                                    { 
        yyval = ++cnt;
        strcpy(L[yyval], "FuncDef");
        printf ("%d:FuncDef -> %d:%s %d:%s %d:\\( %d:\\) %d:Block\n", yyval, yyvsp[-4], L[yyvsp[-4]], yyvsp[-3], L[yyvsp[-3]], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1606 "y.tab.c"
    break;

  case 8:
#line 139 "./grammar.y"
                                                { 
        yyval = ++cnt;
        strcpy(L[yyval], "FuncDef");
        printf ("%d:FuncDef -> %d:%s %d:%s %d:\\( %d:FuncFParams %d:\\) %d:Block\n", yyval, yyvsp[-5], L[yyvsp[-5]], yyvsp[-4], L[yyvsp[-4]], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1616 "y.tab.c"
    break;

  case 9:
#line 146 "./grammar.y"
                    {
        yyval = ++cnt;
        strcpy(L[yyval], "FuncFParam");
        printf ("%d:FuncFParam -> %d:%s %d:%s\n", yyval, yyvsp[-1], L[yyvsp[-1]], yyvsp[0], L[yyvsp[0]]);
    }
#line 1626 "y.tab.c"
    break;

  case 10:
#line 151 "./grammar.y"
                                      {
        yyval = ++cnt;
        strcpy(L[yyval], "FuncFParam");
        printf ("%d:FuncFParam -> %d:%s %d:%s %d:ConstArrayIndex\n", yyval, yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], L[yyvsp[-1]], yyvsp[0]);
    }
#line 1636 "y.tab.c"
    break;

  case 11:
#line 158 "./grammar.y"
               {
        yyval = ++cnt;
        strcpy(L[yyval], "FuncFParams");
        printf ("%d:FuncFParams -> %d:FuncFParam\n", yyval, yyvsp[0]);
    }
#line 1646 "y.tab.c"
    break;

  case 12:
#line 163 "./grammar.y"
                                   {
        yyval = ++cnt;
        strcpy(L[yyval], "FuncFParams");
        printf ("%d:FuncFParams -> %d:FuncFParam %d:\\, %d:FuncFParams\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1656 "y.tab.c"
    break;

  case 13:
#line 170 "./grammar.y"
                                   {
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:LVal %d:ConstArrayIndex %d:\\;\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1666 "y.tab.c"
    break;

  case 14:
#line 175 "./grammar.y"
              { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:IfBlock\n", yyval, yyvsp[0]);
    }
#line 1676 "y.tab.c"
    break;

  case 15:
#line 180 "./grammar.y"
                               { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:IfBlock %d:else %d:StmtOrBlock\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1686 "y.tab.c"
    break;

  case 16:
#line 185 "./grammar.y"
                                     { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:while %d:\\( %d:Cond %d:\\) %d:StmtOrBlock\n", yyval, yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1696 "y.tab.c"
    break;

  case 17:
#line 190 "./grammar.y"
                                  { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:do %d:Block %d:while %d:\\( %d:Cond %d:\\)\n", yyval, yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1]);
    }
#line 1706 "y.tab.c"
    break;

  case 18:
#line 195 "./grammar.y"
                                   { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:for %d:\\( %d:Cond %d:\\) %d:StmtOrBlock\n", yyval, yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1716 "y.tab.c"
    break;

  case 19:
#line 200 "./grammar.y"
                       { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:return %d:\\;\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1726 "y.tab.c"
    break;

  case 20:
#line 205 "./grammar.y"
                              { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:return %d:AddExp %d:\\;\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1736 "y.tab.c"
    break;

  case 21:
#line 210 "./grammar.y"
                      { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:break %d:\\;\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1746 "y.tab.c"
    break;

  case 22:
#line 215 "./grammar.y"
                         { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:continue %d:\\;\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1756 "y.tab.c"
    break;

  case 23:
#line 220 "./grammar.y"
                       { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:Stmt -> %d:AddExp %d:\\;\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1766 "y.tab.c"
    break;

  case 24:
#line 227 "./grammar.y"
         {
        yyval = ++cnt;
        strcpy(L[yyval], "StmtOrBlock");
        printf ("%d:StmtOrBlock -> %d:Stmt\n", yyval, yyvsp[0]);
    }
#line 1776 "y.tab.c"
    break;

  case 25:
#line 232 "./grammar.y"
            {
        yyval = ++cnt;
        strcpy(L[yyval], "StmtOrBlock");
        printf ("%d:StmtOrBlock -> %d:Block\n", yyval, yyvsp[0]);
    }
#line 1786 "y.tab.c"
    break;

  case 26:
#line 239 "./grammar.y"
                                { 
        yyval = ++cnt;
        strcpy(L[yyval], "Stmt");
        printf ("%d:IfBlock -> %d:if %d:\\( %d:Cond %d:\\) %d:StmtOrBlock\n", yyval, yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1796 "y.tab.c"
    break;

  case 27:
#line 246 "./grammar.y"
                      { 
        yyval = ++cnt;
        strcpy(L[yyval], "Block");
        printf ("%d:Block -> %d:\\{ %d:BlockItem %d:\\}\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1806 "y.tab.c"
    break;

  case 28:
#line 253 "./grammar.y"
                   {
        yyval = ++cnt;
        strcpy(L[yyval], "BlockItem");
        printf ("%d:BlockItem -> %d:Stmt %d:BlockItem\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1816 "y.tab.c"
    break;

  case 29:
#line 258 "./grammar.y"
                     { 
        yyval = ++cnt;
        strcpy(L[yyval], "BlockItem");
        printf ("%d:BlockItem -> %d:Decl %d:BlockItem\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1826 "y.tab.c"
    break;

  case 30:
#line 263 "./grammar.y"
           {
        yyval = ++cnt;
        strcpy(L[yyval], "BlockItem");
        printf ("%d:BlockItem -> %d:Stmt\n", yyval, yyvsp[0]);
    }
#line 1836 "y.tab.c"
    break;

  case 31:
#line 268 "./grammar.y"
           { 
        yyval = ++cnt;
        strcpy(L[yyval], "BlockItem");
        printf ("%d:BlockItem -> %d:Decl\n", yyval, yyvsp[0]);
    }
#line 1846 "y.tab.c"
    break;

  case 32:
#line 275 "./grammar.y"
                             { 
        yyval = ++cnt;
        strcpy(L[yyval], "Decl");
        printf ("%d:Decl -> %d:VarDecl %d:\\, %d:SeqVarDecl\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1856 "y.tab.c"
    break;

  case 33:
#line 280 "./grammar.y"
                        { 
        yyval = ++cnt;
        strcpy(L[yyval], "Decl");
        printf ("%d:Decl -> %d:VarDecl %d:\\;\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1866 "y.tab.c"
    break;

  case 34:
#line 287 "./grammar.y"
                                          {
        yyval = ++cnt;
        strcpy(L[yyval], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s %d:%s %d:ConstArrayIndex\n", yyval, yyvsp[-3], L[yyvsp[-3]], yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], L[yyvsp[-1]], yyvsp[0]);
    }
#line 1876 "y.tab.c"
    break;

  case 35:
#line 292 "./grammar.y"
                            {
        yyval = ++cnt;
        strcpy(L[yyval], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s %d:%s\n", yyval, yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], L[yyvsp[-1]], yyvsp[0], L[yyvsp[0]]);
    }
#line 1886 "y.tab.c"
    break;

  case 36:
#line 297 "./grammar.y"
                      {
        yyval = ++cnt;
        strcpy(L[yyval], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s\n", yyval, yyvsp[-1], L[yyvsp[-1]], yyvsp[0], L[yyvsp[0]]);
    }
#line 1896 "y.tab.c"
    break;

  case 37:
#line 302 "./grammar.y"
                                      {
        yyval = ++cnt;
        strcpy(L[yyval], "VarDecl");
        printf ("%d:VarDecl -> %d:%s %d:%s %d:ConstArrayIndex\n", yyval, yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], L[yyvsp[-1]], yyvsp[0]);
    }
#line 1906 "y.tab.c"
    break;

  case 38:
#line 309 "./grammar.y"
                                                {
        yyval = ++cnt;
        strcpy(L[yyval], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:ConstArrayIndex %d:\\, %d:SeqVarDecl\n", yyval, yyvsp[-3], L[yyvsp[-3]], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1916 "y.tab.c"
    break;

  case 39:
#line 314 "./grammar.y"
                                  {
        yyval = ++cnt;
        strcpy(L[yyval], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:\\, %d:SeqVarDecl\n", yyval, yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], yyvsp[0]);
    }
#line 1926 "y.tab.c"
    break;

  case 40:
#line 319 "./grammar.y"
                                           {
        yyval = ++cnt;
        strcpy(L[yyval], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:ConstArrayIndex %d:\\;\n", yyval, yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], yyvsp[0]);
    }
#line 1936 "y.tab.c"
    break;

  case 41:
#line 324 "./grammar.y"
                           {
        yyval = ++cnt;
        strcpy(L[yyval], "SeqVarDecl");
        printf ("%d:SeqVarDecl -> %d:%s %d:\\;\n", yyval, yyvsp[-1], L[yyvsp[-1]], yyvsp[0]);
    }
#line 1946 "y.tab.c"
    break;

  case 42:
#line 332 "./grammar.y"
                  {
        yyval = ++cnt;
        strcpy(L[yyval], "ConstArrayIndex");
        printf ("%d:ConstArrayIndex -> %d:\\= %d:AddExp\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 1956 "y.tab.c"
    break;

  case 43:
#line 337 "./grammar.y"
                               {
        yyval = ++cnt;
        strcpy(L[yyval], "ConstArrayIndex");
        printf ("%d:ConstArrayIndex -> %d:ArrayIndex %d:\\= %d:AddExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1966 "y.tab.c"
    break;

  case 44:
#line 342 "./grammar.y"
                 {
        yyval = ++cnt;
        strcpy(L[yyval], "ConstArrayIndex");
        printf ("%d:ConstArrayIndex -> %d:ArrayIndex\n", yyval, yyvsp[0]);
    }
#line 1976 "y.tab.c"
    break;

  case 45:
#line 349 "./grammar.y"
                   {
        yyval = ++cnt;
        strcpy(L[yyval], "ArrayIndex");
        printf ("%d:ArrayIndex -> %d:\\[ %d:AddExp %d:\\]\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1986 "y.tab.c"
    break;

  case 46:
#line 354 "./grammar.y"
                         {
        yyval = ++cnt;
        strcpy(L[yyval], "ArrayIndex");
        printf ("%d:ArrayIndex -> %d:\\[ %d:\\] %d:ArrayIndex\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 1996 "y.tab.c"
    break;

  case 47:
#line 359 "./grammar.y"
                                {
        yyval = ++cnt;
        strcpy(L[yyval], "ArrayIndex");
        printf ("ArrayIndex -> %d:\\[ %d:AddExp %d:\\] %d:ArrayIndex\n", yyval, yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2006 "y.tab.c"
    break;

  case 48:
#line 364 "./grammar.y"
              {
        yyval = ++cnt;
        strcpy(L[yyval], "ArrayIndex");
        printf ("%d:ArrayIndex -> %d:\\[ %d:\\]\n", yyval, yyvsp[-1], yyvsp[0]);
    }
#line 2016 "y.tab.c"
    break;

  case 49:
#line 371 "./grammar.y"
                       { 
        yyval = ++cnt;
        strcpy(L[yyval], "AddExp");
        printf ("%d:AddExp -> %d:AddExp %d:\\+ %d:MulExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2026 "y.tab.c"
    break;

  case 50:
#line 376 "./grammar.y"
                          { 
        yyval = ++cnt;
        strcpy(L[yyval], "AddExp");
        printf ("%d:AddExp -> %d:AddExp %d:\\- %d:MulExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2036 "y.tab.c"
    break;

  case 51:
#line 381 "./grammar.y"
             { 
        yyval = ++cnt;
        strcpy(L[yyval], "AddExp");
        printf ("%d:AddExp -> %d:MulExp\n", yyval, yyvsp[0]);
    }
#line 2046 "y.tab.c"
    break;

  case 52:
#line 388 "./grammar.y"
                          { 
        yyval = ++cnt;
        strcpy(L[yyval], "MulExp");
        printf ("%d:MulExp -> %d:MulExp %d:\\* %d:UnaryExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2056 "y.tab.c"
    break;

  case 53:
#line 393 "./grammar.y"
                             { 
        yyval = ++cnt;
        strcpy(L[yyval], "MulExp");
        printf ("%d:MulExp -> %d:MulExp %d:\\/ %d:UnaryExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2066 "y.tab.c"
    break;

  case 54:
#line 398 "./grammar.y"
               { 
        yyval = ++cnt;
        strcpy(L[yyval], "MulExp");
        printf ("%d:MulExp -> %d:UnaryExp\n", yyval, yyvsp[0]);
    }
#line 2076 "y.tab.c"
    break;

  case 55:
#line 405 "./grammar.y"
         { 
        yyval = ++cnt;
        strcpy(L[yyval], "PrimaryExp");
        printf ("%d:PrimaryExp -> %d:LVal\n", yyval, yyvsp[0]);
    }
#line 2086 "y.tab.c"
    break;

  case 56:
#line 410 "./grammar.y"
                { 
        yyval = ++cnt;
        strcpy(L[yyval], "PrimaryExp");
        printf ("%d:PrimaryExp -> %d:%s\n", yyval, yyvsp[0], L[yyvsp[0]]);
    }
#line 2096 "y.tab.c"
    break;

  case 57:
#line 417 "./grammar.y"
               { 
        yyval = ++cnt;
        strcpy(L[yyval], "UnaryExp");
        printf ("%d:UnaryExp -> %d:PrimaryExp\n", yyval, yyvsp[0]);
    }
#line 2106 "y.tab.c"
    break;

  case 58:
#line 422 "./grammar.y"
                         { 
        yyval = ++cnt;
        strcpy(L[yyval], "UnaryExp");
        printf ("%d:UnaryExp -> %d:%s %d:\\( %d:)\n", yyval, yyvsp[-2], L[yyvsp[-2]], yyvsp[-1], yyvsp[0]);
    }
#line 2116 "y.tab.c"
    break;

  case 59:
#line 427 "./grammar.y"
                                     { 
        yyval = ++cnt;
        strcpy(L[yyval], "UnaryExp");
        printf ("%d:UnaryExp -> %d:%s %d:\\( %d:FuncRParams %d:\\)\n", yyval, yyvsp[-3], L[yyvsp[-3]], yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2126 "y.tab.c"
    break;

  case 60:
#line 434 "./grammar.y"
            { 
        yyval = ++cnt;
        strcpy(L[yyval], "LOrExp");
        printf ("%d:LOrExp -> %d:LAndExp\n", yyval, yyvsp[0]);
    }
#line 2136 "y.tab.c"
    break;

  case 61:
#line 439 "./grammar.y"
                        { 
        yyval = ++cnt;
        strcpy(L[yyval], "LOrExp");
        printf ("%d:LOrExp -> %d:LOrExp %d:\\|\\| %d:LAndExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2146 "y.tab.c"
    break;

  case 62:
#line 446 "./grammar.y"
           { 
        yyval = ++cnt;
        strcpy(L[yyval], "Cond");
        printf ("%d:Cond -> %d:LOrExp\n", yyval, yyvsp[0]);
    }
#line 2156 "y.tab.c"
    break;

  case 63:
#line 453 "./grammar.y"
            { 
        yyval = ++cnt;
        strcpy(L[yyval], "LAndExp");
        printf ("%d:LAndExp -> %d:CompExp\n", yyval, yyvsp[0]);
    }
#line 2166 "y.tab.c"
    break;

  case 64:
#line 458 "./grammar.y"
                          { 
        yyval = ++cnt;
        strcpy(L[yyval], "LAndExp");
        printf ("%d:LAndExp -> %d:LAndExp %d:\\&\\& %d:CompExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2176 "y.tab.c"
    break;

  case 65:
#line 465 "./grammar.y"
                           { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\> %d:RelExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2186 "y.tab.c"
    break;

  case 66:
#line 470 "./grammar.y"
                          { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\< %d:RelExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2196 "y.tab.c"
    break;

  case 67:
#line 475 "./grammar.y"
                           { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\=\\= %d:RelExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2206 "y.tab.c"
    break;

  case 68:
#line 480 "./grammar.y"
                               { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\<\\= %d:RelExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2216 "y.tab.c"
    break;

  case 69:
#line 485 "./grammar.y"
                                  { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\>\\= %d:RelExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2226 "y.tab.c"
    break;

  case 70:
#line 490 "./grammar.y"
                              { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:CompExp %d:\\!\\= %d:RelExp\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2236 "y.tab.c"
    break;

  case 71:
#line 495 "./grammar.y"
             { 
        yyval = ++cnt;
        strcpy(L[yyval], "CompExp");
        printf ("%d:CompExp -> %d:RelExp\n", yyval, yyvsp[0]);
    }
#line 2246 "y.tab.c"
    break;

  case 72:
#line 502 "./grammar.y"
                             {
        yyval = ++cnt;
        strcpy(L[yyval], "FuncRParams");
        printf ("%d:FuncRParams -> %d:AddExp %d:\\, %d:FuncRParams\n", yyval, yyvsp[-2], yyvsp[-1], yyvsp[0]);
    }
#line 2256 "y.tab.c"
    break;

  case 73:
#line 507 "./grammar.y"
             { 
        yyval = ++cnt;
        strcpy(L[yyval], "FuncRParams");
        printf ("%d:FuncRParams -> %d:AddExp\n", yyval, yyvsp[0]);
    }
#line 2266 "y.tab.c"
    break;

  case 74:
#line 514 "./grammar.y"
                          {
        yyval = ++cnt;
        strcpy(L[yyval], "LVal");
        printf ("%d:LVal -> %d:%s %d:ArrayIndex\n", yyval, yyvsp[-1], L[yyvsp[-1]], yyvsp[0]);
    }
#line 2276 "y.tab.c"
    break;

  case 75:
#line 519 "./grammar.y"
                 {
        yyval = ++cnt;
        strcpy(L[yyval], "LVal");
        printf ("%d:LVal -> %d:%s\n", yyval, yyvsp[0], L[yyvsp[0]]);
    }
#line 2286 "y.tab.c"
    break;

  case 76:
#line 526 "./grammar.y"
           { 
        yyval = ++cnt;
        strcpy(L[yyval], "RelExp");
        printf ("%d:RelExp -> %d:AddExp\n", yyval, yyvsp[0]);
    }
#line 2296 "y.tab.c"
    break;


#line 2300 "y.tab.c"

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
#line 532 "./grammar.y"
