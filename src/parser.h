/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 43 "parser.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 98 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
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


