/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
