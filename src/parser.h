/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     SYM = 260,
     STR = 261,
     STR_FINAL = 262,
     HEAD = 263,
     BRANCH = 264,
     ACCESS = 265,
     SYMBOLS = 266,
     LOCKS = 267,
     STRICT = 268,
     COMMENT = 269,
     EXPAND = 270,
     DATE = 271,
     AUTHOR = 272,
     STATE = 273,
     BRANCHES = 274,
     NEXT = 275,
     DESC = 276,
     LOG = 277,
     TEXT = 278
   };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define SYM 260
#define STR 261
#define STR_FINAL 262
#define HEAD 263
#define BRANCH 264
#define ACCESS 265
#define SYMBOLS 266
#define LOCKS 267
#define STRICT 268
#define COMMENT 269
#define EXPAND 270
#define DATE 271
#define AUTHOR 272
#define STATE 273
#define BRANCHES 274
#define NEXT 275
#define DESC 276
#define LOG 277
#define TEXT 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 43 "parser.y"
{
	char *s;
	unsigned int i;
	time_t date;
	hash_t *hash;
	vector_t *vector;
	lines_t *lines;
	delta_t *delta;
	struct {
		delta_t *head;
		hash_t *branches;
	} trunk;
	expand_t expand;
}
/* Line 1529 of yacc.c.  */
#line 110 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
