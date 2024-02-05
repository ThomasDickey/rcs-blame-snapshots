/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

/*
 * Blame - An RCS file annotator
 * Copyright (C) 2004  Michael Chapman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <system.h>

#include <date.h>
#include <delta.h>
#include <hash.h>
#include <rcs.h>
#include <vector.h>

extern int yylex (void);
static void yyerror (const char *, rcs_t *, char const *);
static int _parser_count_deltalist (const rcs_t *, const delta_t *, hash_t *);

typedef struct { unsigned int line; off_t off; off_t next; } loc_t;
#define YYLTYPE loc_t
#define YYLLOC_DEFAULT(Current, Rhs, N) \
	((Current).line = (Rhs)[1].line, \
	 (Current).off = (Rhs)[1].off, \
	 (Current).next = (Rhs)[N].next)

static unsigned int lines;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 199 "parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 224 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   82

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  108

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    25,    24,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,    20,    24,    27,    28,    32,
      35,    39,    43,    47,    48,    51,    52,    56,    59,    60,
      64,    67,    68,    71,    79,    83,    87,    91,    94,    98,
     101,   105,   108,   111,   112,   115,   116,   122,   126,   127,
     130,   134,   135,   138,   139,   142,   144,   147,   148,   153,
     154,   159,   160,   164,   165,   168,   170,   172,   174,   176,
     178,   180,   183,   184
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      27,     0,    -1,    -1,    -1,    28,    30,    31,    32,    33,
      34,    35,    36,    37,    57,    38,    29,    45,    46,    -1,
       8,     3,    24,    -1,     8,    24,    -1,    -1,     9,     3,
      24,    -1,     9,    24,    -1,    10,    53,    24,    -1,    11,
      56,    24,    -1,    12,    55,    24,    -1,    -1,    13,    24,
      -1,    -1,    14,     7,    24,    -1,    14,    24,    -1,    -1,
      15,     7,    24,    -1,    15,    24,    -1,    -1,    38,    39,
      -1,     3,    40,    41,    42,    43,    44,    57,    -1,    16,
       3,    24,    -1,    17,    60,    24,    -1,    18,    60,    24,
      -1,    18,    24,    -1,    19,    54,    24,    -1,    19,    24,
      -1,    20,     3,    24,    -1,    20,    24,    -1,    21,    61,
      -1,    -1,    46,    47,    -1,    -1,     3,    48,    49,    57,
      51,    -1,    22,    50,     7,    -1,    -1,    50,     6,    -1,
      23,    52,     7,    -1,    -1,    52,     6,    -1,    -1,    53,
      60,    -1,     3,    -1,    54,     3,    -1,    -1,    55,    60,
      25,     3,    -1,    -1,    56,     5,    25,     3,    -1,    -1,
      60,    58,    24,    -1,    -1,    58,    59,    -1,     4,    -1,
       3,    -1,    61,    -1,    25,    -1,     4,    -1,     5,    -1,
      62,     7,    -1,    -1,    62,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   117,   101,   159,   160,   164,   165,   166,
     170,   174,   178,   182,   183,   187,   188,   189,   193,   194,
     212,   215,   217,   221,   241,   253,   257,   258,   262,   263,
     267,   272,   276,   279,   281,   285,   285,   303,   312,   313,
     317,   325,   326,   333,   334,   338,   347,   362,   365,   373,
     374,   384,   386,   389,   391,   395,   396,   397,   398,   402,
     403,   407,   410,   412
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "SYM", "STR", "STR_FINAL",
  "HEAD", "BRANCH", "ACCESS", "SYMBOLS", "LOCKS", "STRICT", "COMMENT",
  "EXPAND", "DATE", "AUTHOR", "STATE", "BRANCHES", "NEXT", "DESC", "LOG",
  "TEXT", "';'", "':'", "$accept", "rcstext", "@1", "@2", "admin_head",
  "admin_branch", "admin_access", "admin_symbols", "admin_locks",
  "admin_strict", "admin_comment", "admin_expand", "delta_list", "delta",
  "delta_date", "delta_author", "delta_state", "delta_branches",
  "delta_next", "desc", "deltatext_list", "deltatext", "@3",
  "deltatext_log", "deltatext_log_bit", "deltatext_text",
  "deltatext_text_string", "id_list", "num_list", "id_num_list",
  "sym_num_list", "newphrase_list", "word_list", "word", "id_or_sym",
  "gobble_string", "gobble_string_bit", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    59,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    28,    29,    27,    30,    30,    31,    31,    31,
      32,    33,    34,    35,    35,    36,    36,    36,    37,    37,
      37,    38,    38,    39,    40,    41,    42,    42,    43,    43,
      44,    44,    45,    46,    46,    48,    47,    49,    50,    50,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    61,    62,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,    14,     3,     2,     0,     3,     2,
       3,     3,     3,     0,     2,     0,     3,     2,     0,     3,
       2,     0,     2,     7,     3,     3,     3,     2,     3,     2,
       3,     2,     2,     0,     2,     0,     5,     3,     0,     2,
       3,     0,     2,     0,     2,     1,     2,     0,     4,     0,
       4,     0,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     2,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     7,     0,     6,     0,     0,
       5,     0,     9,    43,     0,     8,     0,    49,     0,    59,
      60,    10,    44,     0,    47,    13,     0,    11,     0,     0,
      15,     0,    12,     0,    14,     0,    18,    50,     0,     0,
      17,     0,    51,    48,    16,     0,    20,    21,    53,    19,
       3,    62,     0,     0,    22,    56,    55,    52,    58,    54,
      57,     0,     0,     0,    62,    33,    63,    61,     0,     0,
       0,    32,     4,    24,     0,     0,     0,    35,    34,    25,
      27,     0,     0,     0,     0,    26,    45,    29,     0,     0,
      51,    38,    51,    46,    28,     0,    31,    23,     0,     0,
      30,    39,    37,    41,    36,     0,    42,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    53,     5,     9,    14,    18,    25,    30,
      36,    42,    50,    54,    63,    70,    76,    83,    90,    65,
      72,    78,    84,    92,    98,   104,   105,    16,    88,    28,
      23,    47,    51,    59,    48,    60,    61
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int8 yypact[] =
{
     -73,     8,    13,   -73,     0,    34,    20,   -73,     1,    36,
     -73,    21,   -73,   -73,    37,   -73,     5,   -73,    38,   -73,
     -73,   -73,   -73,     6,   -73,    39,    22,   -73,     9,    25,
      40,    48,   -73,    30,   -73,    10,    41,   -73,    54,    42,
     -73,    12,    27,   -73,   -73,    43,   -73,   -73,   -73,   -73,
      55,    -2,    44,    47,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,    31,    58,    45,   -73,   -73,   -73,   -73,    46,    27,
      51,   -73,    60,   -73,    49,    11,    52,   -73,   -73,   -73,
     -73,    50,     2,    56,    53,   -73,   -73,   -73,     3,     4,
      27,   -73,    27,   -73,   -73,    57,   -73,   -73,    33,    59,
     -73,   -73,   -73,   -73,   -73,    35,   -73,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -72,   -73,   -73,   -16,    14,   -73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      22,    55,    56,     6,    11,    86,    93,    95,     3,    19,
      20,    26,    33,    19,    20,    19,    20,    39,    97,    45,
      99,     4,    57,    58,     7,    12,    87,    94,    96,    21,
      27,    19,    20,    32,    40,    80,    46,    66,    67,   101,
     102,   106,   107,     8,    10,    15,    13,    31,    17,    34,
      24,    37,    29,    74,    35,    38,    41,    43,    52,    81,
      62,    68,    69,    77,     0,     0,    44,    49,    64,    75,
      73,    82,     0,    79,    85,    91,    89,     0,    71,     0,
       0,   100,   103
};

static const yytype_int8 yycheck[] =
{
      16,     3,     4,     3,     3,     3,     3,     3,     0,     4,
       5,     5,    28,     4,     5,     4,     5,     7,    90,     7,
      92,     8,    24,    25,    24,    24,    24,    24,    24,    24,
      24,     4,     5,    24,    24,    24,    24,     6,     7,     6,
       7,     6,     7,     9,    24,    24,    10,    25,    11,    24,
      12,     3,    13,    69,    14,    25,    15,     3,     3,    75,
      16,     3,    17,     3,    -1,    -1,    24,    24,    21,    18,
      24,    19,    -1,    24,    24,    22,    20,    -1,    64,    -1,
      -1,    24,    23
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    28,     0,     8,    30,     3,    24,     9,    31,
      24,     3,    24,    10,    32,    24,    53,    11,    33,     4,
       5,    24,    60,    56,    12,    34,     5,    24,    55,    13,
      35,    25,    24,    60,    24,    14,    36,     3,    25,     7,
      24,    15,    37,     3,    24,     7,    24,    57,    60,    24,
      38,    58,     3,    29,    39,     3,     4,    24,    25,    59,
      61,    62,    16,    40,    21,    45,     6,     7,     3,    17,
      41,    61,    46,    24,    60,    18,    42,     3,    47,    24,
      24,    60,    19,    43,    48,    24,     3,    24,    54,    20,
      44,    22,    49,     3,    24,     3,    24,    57,    50,    57,
      24,     6,     7,    23,    51,    52,     6,     7
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (filename, rcs, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, filename, rcs); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char *filename, rcs_t *rcs)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, filename, rcs)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    const char *filename;
    rcs_t *rcs;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (filename);
  YYUSE (rcs);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char *filename, rcs_t *rcs)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, filename, rcs)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    const char *filename;
    rcs_t *rcs;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, filename, rcs);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char *filename, rcs_t *rcs)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, filename, rcs)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    const char *filename;
    rcs_t *rcs;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , filename, rcs);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, filename, rcs); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char *filename, rcs_t *rcs)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, filename, rcs)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    const char *filename;
    rcs_t *rcs;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (filename);
  YYUSE (rcs);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (const char *filename, rcs_t *rcs);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (const char *filename, rcs_t *rcs)
#else
int
yyparse (filename, rcs)
    const char *filename;
    rcs_t *rcs;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 101 "parser.y"
    {
			yylloc.line = 1;
			yylloc.off = yylloc.next = 0;
			lines = 0;
			rcs->delta_list = hash_new((dup_fn_t)delta_dup, (free_fn_t)delta_free);
		}
    break;

  case 3:
#line 117 "parser.y"
    {
			if ((yyvsp[(2) - (11)].s)) {
				int count;
				
				(yyval.trunk).head = (delta_t *)rcs_get_delta(rcs, (yyvsp[(2) - (11)].s));
				if (!(yyval.trunk).head) {
					yyerror(filename, rcs, "head revision is missing");
					YYERROR;
				}
				
				(yyval.trunk).branches = hash_new(NULL, NULL);
				count = _parser_count_deltalist(rcs, (yyval.trunk).head, (yyval.trunk).branches);
				if (count < 0) {
					yyerror(filename, rcs, "delta tree is malformed");
					YYERROR;
				}
				if ((unsigned)count != hash_count(rcs->delta_list)) {
					yyerror(filename, rcs, "unreachable deltas exist");
					YYERROR;
				}
			} else {
				(yyval.trunk).head = NULL;
				(yyval.trunk).branches = NULL;
			}
		}
    break;

  case 4:
#line 144 "parser.y"
    {
			rcs->head = (yyvsp[(12) - (14)].trunk).head;
			rcs->branch = ((yyvsp[(3) - (14)].s) ? strdup((yyvsp[(3) - (14)].s)) : ((yyvsp[(2) - (14)].s) ? rcs_rev_to_branch((yyvsp[(2) - (14)].s)) : NULL));
			rcs->branches = (yyvsp[(12) - (14)].trunk).branches;
			rcs->access = (yyvsp[(4) - (14)].vector);
			rcs->symbols = (yyvsp[(5) - (14)].hash);
			rcs->locks = (yyvsp[(6) - (14)].hash);
			rcs->strict = (int) (yyvsp[(7) - (14)].i);
			rcs->comment = (yyvsp[(8) - (14)].s);
			rcs->expand = (yyvsp[(9) - (14)].expand);
			rcs->lines = lines;
		}
    break;

  case 5:
#line 159 "parser.y"
    { (yyval.s) = rcs->start + (yylsp[(2) - (3)]).off; *((yyval.s) + (yyvsp[(2) - (3)].i)) = '\0'; }
    break;

  case 6:
#line 160 "parser.y"
    { (yyval.s) = NULL; }
    break;

  case 7:
#line 164 "parser.y"
    { (yyval.s) = NULL; }
    break;

  case 8:
#line 165 "parser.y"
    { (yyval.s) = rcs->start + (yylsp[(2) - (3)]).off; *((yyval.s) + (yyvsp[(2) - (3)].i)) = '\0'; }
    break;

  case 9:
#line 166 "parser.y"
    { (yyval.s) = NULL; }
    break;

  case 10:
#line 170 "parser.y"
    { (yyval.vector) = (yyvsp[(2) - (3)].vector); }
    break;

  case 11:
#line 174 "parser.y"
    { (yyval.hash) = (yyvsp[(2) - (3)].hash); }
    break;

  case 12:
#line 178 "parser.y"
    { (yyval.hash) = (yyvsp[(2) - (3)].hash); }
    break;

  case 13:
#line 182 "parser.y"
    { (yyval.i) = 0; }
    break;

  case 14:
#line 183 "parser.y"
    { (yyval.i) = 1; }
    break;

  case 15:
#line 187 "parser.y"
    { (yyval.s) = NULL; }
    break;

  case 16:
#line 188 "parser.y"
    { (yyval.s) = rcs->start + (yylsp[(2) - (3)]).off; *((yyval.s) + (yyvsp[(2) - (3)].i)) = '\0'; }
    break;

  case 17:
#line 189 "parser.y"
    { (yyval.s) = NULL; }
    break;

  case 18:
#line 193 "parser.y"
    { (yyval.expand) = EXPAND_UNDEFINED; }
    break;

  case 19:
#line 194 "parser.y"
    {
			if (!strncmp(rcs->start + (yylsp[(2) - (3)]).off, "kv", (yyvsp[(2) - (3)].i)))
				(yyval.expand) = EXPAND_KEY_VALUE;
			else if (!strncmp(rcs->start + (yylsp[(2) - (3)]).off, "kvl", (yyvsp[(2) - (3)].i)))
				(yyval.expand) = EXPAND_KEY_VALUE_LOCKER;
			else if (!strncmp(rcs->start + (yylsp[(2) - (3)]).off, "k", (yyvsp[(2) - (3)].i)))
				(yyval.expand) = EXPAND_KEY_ONLY;
			else if (!strncmp(rcs->start + (yylsp[(2) - (3)]).off, "o", (yyvsp[(2) - (3)].i)))
				(yyval.expand) = EXPAND_OLD_STRING;
			else if (!strncmp(rcs->start + (yylsp[(2) - (3)]).off, "b", (yyvsp[(2) - (3)].i)))
				(yyval.expand) = EXPAND_BINARY_STRING;
			else if (!strncmp(rcs->start + (yylsp[(2) - (3)]).off, "v", (yyvsp[(2) - (3)].i)))
				(yyval.expand) = EXPAND_VALUE_ONLY;
			else {
				yyerror(filename, rcs, "invalid keyword expansion type");
				YYERROR;
			}
		}
    break;

  case 20:
#line 212 "parser.y"
    { (yyval.expand) = EXPAND_UNDEFINED; }
    break;

  case 23:
#line 228 "parser.y"
    {
			char *num = rcs->start + (yylsp[(1) - (7)]).off;
			*(num + (yyvsp[(1) - (7)].i)) = '\0';
			(yyval.delta) = rcs_get_delta_template(rcs, num);
			if (!delta_is_template((yyval.delta))) {
				yyerror(filename, rcs, "delta is multiply defined");
				YYERROR;
			}
			delta_complete_template_nocopy((yyval.delta), (yyvsp[(2) - (7)].date), (yyvsp[(3) - (7)].s), (yyvsp[(4) - (7)].s), (yyvsp[(5) - (7)].hash), (yyvsp[(6) - (7)].delta));
		}
    break;

  case 24:
#line 241 "parser.y"
    {
			char *num = rcs->start + (yylsp[(2) - (3)]).off;
			*(num + (yyvsp[(2) - (3)].i)) = '\0';
			(yyval.date) = date_parse_rev(num);
			if ((yyval.date) < 0) {
				yyerror(filename, rcs, "invalid date");
				YYERROR;
			}
		}
    break;

  case 25:
#line 253 "parser.y"
    { (yyval.s) = (yyvsp[(2) - (3)].s); }
    break;

  case 26:
#line 257 "parser.y"
    { (yyval.s) = (yyvsp[(2) - (3)].s); }
    break;

  case 27:
#line 258 "parser.y"
    { (yyval.s) = NULL; }
    break;

  case 28:
#line 262 "parser.y"
    { (yyval.hash) = (yyvsp[(2) - (3)].hash); }
    break;

  case 29:
#line 263 "parser.y"
    { (yyval.hash) = NULL; }
    break;

  case 30:
#line 267 "parser.y"
    {
			char *num = rcs->start + (yylsp[(2) - (3)]).off;
			*(num + (yyvsp[(2) - (3)].i)) = '\0';
			(yyval.delta) = rcs_get_delta_template(rcs, num);
		}
    break;

  case 31:
#line 272 "parser.y"
    { (yyval.delta) = NULL; }
    break;

  case 35:
#line 285 "parser.y"
    {
			const delta_t *delta;
			char *num = rcs->start + (yylsp[(1) - (1)]).off;
			*(num + (yyvsp[(1) - (1)].i)) = '\0';
			delta = rcs_get_delta(rcs, num);
			if (delta && !delta_is_template(delta))
				(yyval.delta) = (delta_t *)delta;
			else {
				yyerror(filename, rcs, "invalid delta revision");
				YYERROR;
			}
		}
    break;

  case 36:
#line 299 "parser.y"
    { delta_complete_text_nocopy((yyvsp[(2) - (5)].delta), (yyvsp[(3) - (5)].s), (yyvsp[(5) - (5)].lines)); }
    break;

  case 37:
#line 303 "parser.y"
    {
			/* Sigh... Can't rely on @2 because the empty rule below
			 * screws up the location stack. */
			rcs->start[(yylsp[(3) - (3)]).off + (yyvsp[(3) - (3)].i)] = '\0';
			(yyval.s) = rcs->start + (yylsp[(3) - (3)]).off - (yyvsp[(2) - (3)].i);
		}
    break;

  case 38:
#line 312 "parser.y"
    { (yyval.i) = 0; }
    break;

  case 39:
#line 313 "parser.y"
    { (yyval.i) = (yyvsp[(1) - (2)].i) + (yyvsp[(2) - (2)].i); }
    break;

  case 40:
#line 317 "parser.y"
    {
			(yyval.lines) = (yyvsp[(2) - (3)].lines);
			lines_append_nocopy((yyval.lines), rcs->start + (yylsp[(3) - (3)]).off, (yyvsp[(3) - (3)].i));
			lines++;
		}
    break;

  case 41:
#line 325 "parser.y"
    { (yyval.lines) = lines_new(); }
    break;

  case 42:
#line 326 "parser.y"
    {
			lines_append_nocopy((yyval.lines), rcs->start + (yylsp[(2) - (2)]).off, (yyvsp[(2) - (2)].i));
			lines++;
		}
    break;

  case 43:
#line 333 "parser.y"
    { (yyval.vector) = vector_new(NULL, NULL); }
    break;

  case 44:
#line 334 "parser.y"
    { vector_append_nocopy((yyval.vector), (yyvsp[(2) - (2)].s)); }
    break;

  case 45:
#line 338 "parser.y"
    {
			char *branch, *num;
			(yyval.hash) = hash_new(NULL, NULL);
			num = rcs->start + (yylsp[(1) - (1)]).off;
			*(num + (yyvsp[(1) - (1)].i)) = '\0';
			branch = rcs_rev_to_branch(num);
			hash_insert_nocopy((yyval.hash), branch, rcs_get_delta_template(rcs, num));
			FREE(branch);
		}
    break;

  case 46:
#line 347 "parser.y"
    {
			char *branch, *num;
			num = rcs->start + (yylsp[(2) - (2)]).off;
			*(num + (yyvsp[(2) - (2)].i)) = '\0';
			if (!rcs_rev_is_valid(num)) {
				yyerror(filename, rcs, "branch revision is malformed");
				YYERROR;
			}
			branch = rcs_rev_to_branch(num);
			hash_insert_nocopy((yyval.hash), branch, rcs_get_delta_template(rcs, num));
			FREE(branch);
		}
    break;

  case 47:
#line 362 "parser.y"
    {
			(yyval.hash) = hash_new(NULL, NULL);
		}
    break;

  case 48:
#line 365 "parser.y"
    {
			char *num = rcs->start + (yylsp[(4) - (4)]).off;
			*(num + (yyvsp[(4) - (4)].i)) = '\0';
			hash_insert_nocopy((yyval.hash), (yyvsp[(2) - (4)].s), rcs_get_delta_template(rcs, num));
		}
    break;

  case 49:
#line 373 "parser.y"
    { (yyval.hash) = hash_new(NULL, NULL); }
    break;

  case 50:
#line 374 "parser.y"
    {
		char *sym, *num;
		sym = rcs->start + (yylsp[(2) - (4)]).off;
		*(sym + (yyvsp[(2) - (4)].i)) = '\0';
		num = rcs->start + (yylsp[(4) - (4)]).off;
		*(num + (yyvsp[(4) - (4)].i)) = '\0';
		hash_insert_nocopy((yyval.hash), sym, num);
	}
    break;

  case 59:
#line 402 "parser.y"
    { (yyval.s) = rcs->start + (yylsp[(1) - (1)]).off; *((yyval.s) + (yyvsp[(1) - (1)].i)) = '\0'; }
    break;

  case 60:
#line 403 "parser.y"
    { (yyval.s) = rcs->start + (yylsp[(1) - (1)]).off; *((yyval.s) + (yyvsp[(1) - (1)].i)) = '\0'; }
    break;


/* Line 1267 of yacc.c.  */
#line 1911 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (filename, rcs, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (filename, rcs, yymsg);
	  }
	else
	  {
	    yyerror (filename, rcs, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc, filename, rcs);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, filename, rcs);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (filename, rcs, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, filename, rcs);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, filename, rcs);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 415 "parser.y"


static void
yyerror(
	const char *filename, __attribute__((unused)) rcs_t *rcs, char const *err
) {
	assert(filename);
	assert(rcs);
	assert(err);
	
	error(0, 0, "%s: %s at line %u", filename, err, yylloc.line);
}

/*
 * Returns the number of reachable revisions from <delta> in <rcs>.
 * If a loop is detected, -1 is returned.
 */
static int
_parser_count_deltalist(const rcs_t *rcs, const delta_t *delta, hash_t *branches) {
	int count;
	const char *prev;
	
	if (delta_is_template(delta))
		return -1;
	
	prev = NULL;
	count = 0;
	
	while (delta) {
		const delta_t *base;
		hash_iter_t iter;
		
		count++;
		
		if (branches) {
			const char *rev, *dot;
			rev = delta_get_revision(delta);
			dot = strrchr(rev, '.');
			assert(dot);
			
			if (!prev || strncmp(prev, rev, (size_t) (dot - rev + 1))) {
				char *copy = strndup(rev, (size_t) (dot - rev));
				hash_insert(branches, copy, delta);
				FREE(copy);
				prev = rev;
			}
		}
		
		for_each_branch_base(base, delta, iter) {
			int c;
			
			assert(base);
			
			if ((c = _parser_count_deltalist(rcs, base, NULL)) < 0) {
				hash_iter_free(iter);
				return -1;
			}
			
			count += c;
		}
		hash_iter_free(iter);
		
		delta = delta_get_next(delta);
	}
	
	return count;
}

