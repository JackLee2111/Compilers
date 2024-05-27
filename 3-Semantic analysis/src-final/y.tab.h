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
