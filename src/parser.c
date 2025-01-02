/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

#line 113 "parser.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    ID = 259,                      /* ID  */
    SYM = 260,                     /* SYM  */
    STR = 261,                     /* STR  */
    STR_FINAL = 262,               /* STR_FINAL  */
    HEAD = 263,                    /* HEAD  */
    BRANCH = 264,                  /* BRANCH  */
    ACCESS = 265,                  /* ACCESS  */
    SYMBOLS = 266,                 /* SYMBOLS  */
    LOCKS = 267,                   /* LOCKS  */
    STRICT = 268,                  /* STRICT  */
    COMMENT = 269,                 /* COMMENT  */
    EXPAND = 270,                  /* EXPAND  */
    DATE = 271,                    /* DATE  */
    AUTHOR = 272,                  /* AUTHOR  */
    STATE = 273,                   /* STATE  */
    BRANCHES = 274,                /* BRANCHES  */
    NEXT = 275,                    /* NEXT  */
    DESC = 276,                    /* DESC  */
    LOG = 277,                     /* LOG  */
    TEXT = 278                     /* TEXT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 43 "parser.y"

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

#line 224 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (const char *filename, rcs_t *rcs);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_SYM = 5,                        /* SYM  */
  YYSYMBOL_STR = 6,                        /* STR  */
  YYSYMBOL_STR_FINAL = 7,                  /* STR_FINAL  */
  YYSYMBOL_HEAD = 8,                       /* HEAD  */
  YYSYMBOL_BRANCH = 9,                     /* BRANCH  */
  YYSYMBOL_ACCESS = 10,                    /* ACCESS  */
  YYSYMBOL_SYMBOLS = 11,                   /* SYMBOLS  */
  YYSYMBOL_LOCKS = 12,                     /* LOCKS  */
  YYSYMBOL_STRICT = 13,                    /* STRICT  */
  YYSYMBOL_COMMENT = 14,                   /* COMMENT  */
  YYSYMBOL_EXPAND = 15,                    /* EXPAND  */
  YYSYMBOL_DATE = 16,                      /* DATE  */
  YYSYMBOL_AUTHOR = 17,                    /* AUTHOR  */
  YYSYMBOL_STATE = 18,                     /* STATE  */
  YYSYMBOL_BRANCHES = 19,                  /* BRANCHES  */
  YYSYMBOL_NEXT = 20,                      /* NEXT  */
  YYSYMBOL_DESC = 21,                      /* DESC  */
  YYSYMBOL_LOG = 22,                       /* LOG  */
  YYSYMBOL_TEXT = 23,                      /* TEXT  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 26,                  /* $accept  */
  YYSYMBOL_rcstext = 27,                   /* rcstext  */
  YYSYMBOL_28_1 = 28,                      /* $@1  */
  YYSYMBOL_29_2 = 29,                      /* @2  */
  YYSYMBOL_admin_head = 30,                /* admin_head  */
  YYSYMBOL_admin_branch = 31,              /* admin_branch  */
  YYSYMBOL_admin_access = 32,              /* admin_access  */
  YYSYMBOL_admin_symbols = 33,             /* admin_symbols  */
  YYSYMBOL_admin_locks = 34,               /* admin_locks  */
  YYSYMBOL_admin_strict = 35,              /* admin_strict  */
  YYSYMBOL_admin_comment = 36,             /* admin_comment  */
  YYSYMBOL_admin_expand = 37,              /* admin_expand  */
  YYSYMBOL_delta_list = 38,                /* delta_list  */
  YYSYMBOL_delta = 39,                     /* delta  */
  YYSYMBOL_delta_date = 40,                /* delta_date  */
  YYSYMBOL_delta_author = 41,              /* delta_author  */
  YYSYMBOL_delta_state = 42,               /* delta_state  */
  YYSYMBOL_delta_branches = 43,            /* delta_branches  */
  YYSYMBOL_delta_next = 44,                /* delta_next  */
  YYSYMBOL_desc = 45,                      /* desc  */
  YYSYMBOL_deltatext_list = 46,            /* deltatext_list  */
  YYSYMBOL_deltatext = 47,                 /* deltatext  */
  YYSYMBOL_48_3 = 48,                      /* @3  */
  YYSYMBOL_deltatext_log = 49,             /* deltatext_log  */
  YYSYMBOL_deltatext_log_bit = 50,         /* deltatext_log_bit  */
  YYSYMBOL_deltatext_text = 51,            /* deltatext_text  */
  YYSYMBOL_deltatext_text_string = 52,     /* deltatext_text_string  */
  YYSYMBOL_id_list = 53,                   /* id_list  */
  YYSYMBOL_num_list = 54,                  /* num_list  */
  YYSYMBOL_id_num_list = 55,               /* id_num_list  */
  YYSYMBOL_sym_num_list = 56,              /* sym_num_list  */
  YYSYMBOL_newphrase_list = 57,            /* newphrase_list  */
  YYSYMBOL_word_list = 58,                 /* word_list  */
  YYSYMBOL_word = 59,                      /* word  */
  YYSYMBOL_id_or_sym = 60,                 /* id_or_sym  */
  YYSYMBOL_gobble_string = 61,             /* gobble_string  */
  YYSYMBOL_gobble_string_bit = 62          /* gobble_string_bit  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   82

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "ID", "SYM",
  "STR", "STR_FINAL", "HEAD", "BRANCH", "ACCESS", "SYMBOLS", "LOCKS",
  "STRICT", "COMMENT", "EXPAND", "DATE", "AUTHOR", "STATE", "BRANCHES",
  "NEXT", "DESC", "LOG", "TEXT", "';'", "':'", "$accept", "rcstext", "$@1",
  "@2", "admin_head", "admin_branch", "admin_access", "admin_symbols",
  "admin_locks", "admin_strict", "admin_comment", "admin_expand",
  "delta_list", "delta", "delta_date", "delta_author", "delta_state",
  "delta_branches", "delta_next", "desc", "deltatext_list", "deltatext",
  "@3", "deltatext_log", "deltatext_log_bit", "deltatext_text",
  "deltatext_text_string", "id_list", "num_list", "id_num_list",
  "sym_num_list", "newphrase_list", "word_list", "word", "id_or_sym",
  "gobble_string", "gobble_string_bit", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,   -72,   -73,   -73,   -16,    14,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    53,     5,     9,    14,    18,    25,    30,
      36,    42,    50,    54,    63,    70,    76,    83,    90,    65,
      72,    78,    84,    92,    98,   104,   105,    16,    88,    28,
      23,    47,    51,    59,    48,    60,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    26,    28,    29,    27,    30,    30,    31,    31,    31,
      32,    33,    34,    35,    35,    36,    36,    36,    37,    37,
      37,    38,    38,    39,    40,    41,    42,    42,    43,    43,
      44,    44,    45,    46,    46,    48,    47,    49,    50,    50,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,    14,     3,     2,     0,     3,     2,
       3,     3,     3,     0,     2,     0,     3,     2,     0,     3,
       2,     0,     2,     7,     3,     3,     3,     2,     3,     2,
       3,     2,     2,     0,     2,     0,     5,     3,     0,     2,
       3,     0,     2,     0,     2,     1,     2,     0,     4,     0,
       4,     0,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     2,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (filename, rcs, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, filename, rcs); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char *filename, rcs_t *rcs)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (filename);
  YY_USE (rcs);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char *filename, rcs_t *rcs)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, filename, rcs);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char *filename, rcs_t *rcs)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), filename, rcs);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, filename, rcs); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char *filename, rcs_t *rcs)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (filename);
  YY_USE (rcs);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char *filename, rcs_t *rcs)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 101 "parser.y"
                {
			yylloc.line = 1;
			yylloc.off = yylloc.next = 0;
			lines = 0;
			rcs->delta_list = hash_new((dup_fn_t)delta_dup, (free_fn_t)delta_free);
		}
#line 1743 "parser.c"
    break;

  case 3: /* @2: %empty  */
#line 117 "parser.y"
                {
			if ((yyvsp[-9].s)) {
				int count;

				(yyval.trunk).head = (delta_t *)rcs_get_delta(rcs, (yyvsp[-9].s));
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
#line 1773 "parser.c"
    break;

  case 4: /* rcstext: $@1 admin_head admin_branch admin_access admin_symbols admin_locks admin_strict admin_comment admin_expand newphrase_list delta_list @2 desc deltatext_list  */
#line 144 "parser.y"
                {
			rcs->head = (yyvsp[-2].trunk).head;
			rcs->branch = ((yyvsp[-11].s) ? strdup((yyvsp[-11].s)) : ((yyvsp[-12].s) ? rcs_rev_to_branch((yyvsp[-12].s)) : NULL));
			rcs->branches = (yyvsp[-2].trunk).branches;
			rcs->access = (yyvsp[-10].vector);
			rcs->symbols = (yyvsp[-9].hash);
			rcs->locks = (yyvsp[-8].hash);
			rcs->strict = (int) (yyvsp[-7].i);
			rcs->comment = (yyvsp[-6].s);
			rcs->expand = (yyvsp[-5].expand);
			rcs->lines = lines;
		}
#line 1790 "parser.c"
    break;

  case 5: /* admin_head: HEAD NUM ';'  */
#line 159 "parser.y"
                             { (yyval.s) = rcs->start + (yylsp[-1]).off; *((yyval.s) + (yyvsp[-1].i)) = '\0'; }
#line 1796 "parser.c"
    break;

  case 6: /* admin_head: HEAD ';'  */
#line 160 "parser.y"
                         { (yyval.s) = NULL; }
#line 1802 "parser.c"
    break;

  case 7: /* admin_branch: %empty  */
#line 164 "parser.y"
                            { (yyval.s) = NULL; }
#line 1808 "parser.c"
    break;

  case 8: /* admin_branch: BRANCH NUM ';'  */
#line 165 "parser.y"
                               { (yyval.s) = rcs->start + (yylsp[-1]).off; *((yyval.s) + (yyvsp[-1].i)) = '\0'; }
#line 1814 "parser.c"
    break;

  case 9: /* admin_branch: BRANCH ';'  */
#line 166 "parser.y"
                     { (yyval.s) = NULL; }
#line 1820 "parser.c"
    break;

  case 10: /* admin_access: ACCESS id_list ';'  */
#line 170 "parser.y"
                                   { (yyval.vector) = (yyvsp[-1].vector); }
#line 1826 "parser.c"
    break;

  case 11: /* admin_symbols: SYMBOLS sym_num_list ';'  */
#line 174 "parser.y"
                                         { (yyval.hash) = (yyvsp[-1].hash); }
#line 1832 "parser.c"
    break;

  case 12: /* admin_locks: LOCKS id_num_list ';'  */
#line 178 "parser.y"
                                      { (yyval.hash) = (yyvsp[-1].hash); }
#line 1838 "parser.c"
    break;

  case 13: /* admin_strict: %empty  */
#line 182 "parser.y"
                            { (yyval.i) = 0; }
#line 1844 "parser.c"
    break;

  case 14: /* admin_strict: STRICT ';'  */
#line 183 "parser.y"
                           { (yyval.i) = 1; }
#line 1850 "parser.c"
    break;

  case 15: /* admin_comment: %empty  */
#line 187 "parser.y"
                            { (yyval.s) = NULL; }
#line 1856 "parser.c"
    break;

  case 16: /* admin_comment: COMMENT STR_FINAL ';'  */
#line 188 "parser.y"
                                       { (yyval.s) = rcs->start + (yylsp[-1]).off; *((yyval.s) + (yyvsp[-1].i)) = '\0'; }
#line 1862 "parser.c"
    break;

  case 17: /* admin_comment: COMMENT ';'  */
#line 189 "parser.y"
                            { (yyval.s) = NULL; }
#line 1868 "parser.c"
    break;

  case 18: /* admin_expand: %empty  */
#line 193 "parser.y"
                            { (yyval.expand) = EXPAND_UNDEFINED; }
#line 1874 "parser.c"
    break;

  case 19: /* admin_expand: EXPAND STR_FINAL ';'  */
#line 194 "parser.y"
                               {
			if (!strncmp(rcs->start + (yylsp[-1]).off, "kv", (yyvsp[-1].i)))
				(yyval.expand) = EXPAND_KEY_VALUE;
			else if (!strncmp(rcs->start + (yylsp[-1]).off, "kvl", (yyvsp[-1].i)))
				(yyval.expand) = EXPAND_KEY_VALUE_LOCKER;
			else if (!strncmp(rcs->start + (yylsp[-1]).off, "k", (yyvsp[-1].i)))
				(yyval.expand) = EXPAND_KEY_ONLY;
			else if (!strncmp(rcs->start + (yylsp[-1]).off, "o", (yyvsp[-1].i)))
				(yyval.expand) = EXPAND_OLD_STRING;
			else if (!strncmp(rcs->start + (yylsp[-1]).off, "b", (yyvsp[-1].i)))
				(yyval.expand) = EXPAND_BINARY_STRING;
			else if (!strncmp(rcs->start + (yylsp[-1]).off, "v", (yyvsp[-1].i)))
				(yyval.expand) = EXPAND_VALUE_ONLY;
			else {
				yyerror(filename, rcs, "invalid keyword expansion type");
				YYERROR;
			}
		}
#line 1897 "parser.c"
    break;

  case 20: /* admin_expand: EXPAND ';'  */
#line 212 "parser.y"
                     { (yyval.expand) = EXPAND_UNDEFINED; }
#line 1903 "parser.c"
    break;

  case 23: /* delta: NUM delta_date delta_author delta_state delta_branches delta_next newphrase_list  */
#line 228 "parser.y"
                {
			char *num = rcs->start + (yylsp[-6]).off;
			*(num + (yyvsp[-6].i)) = '\0';
			(yyval.delta) = rcs_get_delta_template(rcs, num);
			if (!delta_is_template((yyval.delta))) {
				yyerror(filename, rcs, "delta is multiply defined");
				YYERROR;
			}
			delta_complete_template_nocopy((yyval.delta), (yyvsp[-5].date), (yyvsp[-4].s), (yyvsp[-3].s), (yyvsp[-2].hash), (yyvsp[-1].delta));
		}
#line 1918 "parser.c"
    break;

  case 24: /* delta_date: DATE NUM ';'  */
#line 241 "parser.y"
                             {
			char *num = rcs->start + (yylsp[-1]).off;
			*(num + (yyvsp[-1].i)) = '\0';
			(yyval.date) = date_parse_rev(num);
			if ((yyval.date) < 0) {
				yyerror(filename, rcs, "invalid date");
				YYERROR;
			}
		}
#line 1932 "parser.c"
    break;

  case 25: /* delta_author: AUTHOR id_or_sym ';'  */
#line 253 "parser.y"
                                     { (yyval.s) = (yyvsp[-1].s); }
#line 1938 "parser.c"
    break;

  case 26: /* delta_state: STATE id_or_sym ';'  */
#line 257 "parser.y"
                                    { (yyval.s) = (yyvsp[-1].s); }
#line 1944 "parser.c"
    break;

  case 27: /* delta_state: STATE ';'  */
#line 258 "parser.y"
                    { (yyval.s) = NULL; }
#line 1950 "parser.c"
    break;

  case 28: /* delta_branches: BRANCHES num_list ';'  */
#line 262 "parser.y"
                                      { (yyval.hash) = (yyvsp[-1].hash); }
#line 1956 "parser.c"
    break;

  case 29: /* delta_branches: BRANCHES ';'  */
#line 263 "parser.y"
                             { (yyval.hash) = NULL; }
#line 1962 "parser.c"
    break;

  case 30: /* delta_next: NEXT NUM ';'  */
#line 267 "parser.y"
                             {
			char *num = rcs->start + (yylsp[-1]).off;
			*(num + (yyvsp[-1].i)) = '\0';
			(yyval.delta) = rcs_get_delta_template(rcs, num);
		}
#line 1972 "parser.c"
    break;

  case 31: /* delta_next: NEXT ';'  */
#line 272 "parser.y"
                   { (yyval.delta) = NULL; }
#line 1978 "parser.c"
    break;

  case 35: /* @3: %empty  */
#line 285 "parser.y"
                    {
			const delta_t *delta;
			char *num = rcs->start + (yylsp[0]).off;
			*(num + (yyvsp[0].i)) = '\0';
			delta = rcs_get_delta(rcs, num);
			if (delta && !delta_is_template(delta))
				(yyval.delta) = (delta_t *)delta;
			else {
				yyerror(filename, rcs, "invalid delta revision");
				YYERROR;
			}
		}
#line 1995 "parser.c"
    break;

  case 36: /* deltatext: NUM @3 deltatext_log newphrase_list deltatext_text  */
#line 299 "parser.y"
                               { delta_complete_text_nocopy((yyvsp[-3].delta), (yyvsp[-2].s), (yyvsp[0].lines)); }
#line 2001 "parser.c"
    break;

  case 37: /* deltatext_log: LOG deltatext_log_bit STR_FINAL  */
#line 303 "parser.y"
                                                {
			/* Sigh... Can't rely on @2 because the empty rule below
			 * screws up the location stack. */
			rcs->start[(yylsp[0]).off + (yyvsp[0].i)] = '\0';
			(yyval.s) = rcs->start + (yylsp[0]).off - (yyvsp[-1].i);
		}
#line 2012 "parser.c"
    break;

  case 38: /* deltatext_log_bit: %empty  */
#line 312 "parser.y"
                            { (yyval.i) = 0; }
#line 2018 "parser.c"
    break;

  case 39: /* deltatext_log_bit: deltatext_log_bit STR  */
#line 313 "parser.y"
                                      { (yyval.i) = (yyvsp[-1].i) + (yyvsp[0].i); }
#line 2024 "parser.c"
    break;

  case 40: /* deltatext_text: TEXT deltatext_text_string STR_FINAL  */
#line 317 "parser.y"
                                                     {
			(yyval.lines) = (yyvsp[-1].lines);
			lines_append_nocopy((yyval.lines), rcs->start + (yylsp[0]).off, (yyvsp[0].i));
			lines++;
		}
#line 2034 "parser.c"
    break;

  case 41: /* deltatext_text_string: %empty  */
#line 325 "parser.y"
                            { (yyval.lines) = lines_new(); }
#line 2040 "parser.c"
    break;

  case 42: /* deltatext_text_string: deltatext_text_string STR  */
#line 326 "parser.y"
                                          {
			lines_append_nocopy((yyval.lines), rcs->start + (yylsp[0]).off, (yyvsp[0].i));
			lines++;
		}
#line 2049 "parser.c"
    break;

  case 43: /* id_list: %empty  */
#line 333 "parser.y"
                            { (yyval.vector) = vector_new(NULL, NULL); }
#line 2055 "parser.c"
    break;

  case 44: /* id_list: id_list id_or_sym  */
#line 334 "parser.y"
                                  { vector_append_nocopy((yyval.vector), (yyvsp[0].s)); }
#line 2061 "parser.c"
    break;

  case 45: /* num_list: NUM  */
#line 338 "parser.y"
                    {
			char *branch, *num;
			(yyval.hash) = hash_new(NULL, NULL);
			num = rcs->start + (yylsp[0]).off;
			*(num + (yyvsp[0].i)) = '\0';
			branch = rcs_rev_to_branch(num);
			hash_insert_nocopy((yyval.hash), branch, rcs_get_delta_template(rcs, num));
			FREE(branch);
		}
#line 2075 "parser.c"
    break;

  case 46: /* num_list: num_list NUM  */
#line 347 "parser.y"
                       {
			char *branch, *num;
			num = rcs->start + (yylsp[0]).off;
			*(num + (yyvsp[0].i)) = '\0';
			if (!rcs_rev_is_valid(num)) {
				yyerror(filename, rcs, "branch revision is malformed");
				YYERROR;
			}
			branch = rcs_rev_to_branch(num);
			hash_insert_nocopy((yyval.hash), branch, rcs_get_delta_template(rcs, num));
			FREE(branch);
		}
#line 2092 "parser.c"
    break;

  case 47: /* id_num_list: %empty  */
#line 362 "parser.y"
                            {
			(yyval.hash) = hash_new(NULL, NULL);
		}
#line 2100 "parser.c"
    break;

  case 48: /* id_num_list: id_num_list id_or_sym ':' NUM  */
#line 365 "parser.y"
                                        {
			char *num = rcs->start + (yylsp[0]).off;
			*(num + (yyvsp[0].i)) = '\0';
			hash_insert_nocopy((yyval.hash), (yyvsp[-2].s), rcs_get_delta_template(rcs, num));
		}
#line 2110 "parser.c"
    break;

  case 49: /* sym_num_list: %empty  */
#line 373 "parser.y"
                            { (yyval.hash) = hash_new(NULL, NULL); }
#line 2116 "parser.c"
    break;

  case 50: /* sym_num_list: sym_num_list SYM ':' NUM  */
#line 374 "parser.y"
                                   {
		char *sym, *num;
		sym = rcs->start + (yylsp[-2]).off;
		*(sym + (yyvsp[-2].i)) = '\0';
		num = rcs->start + (yylsp[0]).off;
		*(num + (yyvsp[0].i)) = '\0';
		hash_insert_nocopy((yyval.hash), sym, num);
	}
#line 2129 "parser.c"
    break;

  case 59: /* id_or_sym: ID  */
#line 402 "parser.y"
                   { (yyval.s) = rcs->start + (yylsp[0]).off; *((yyval.s) + (yyvsp[0].i)) = '\0'; }
#line 2135 "parser.c"
    break;

  case 60: /* id_or_sym: SYM  */
#line 403 "parser.y"
                    { (yyval.s) = rcs->start + (yylsp[0]).off; *((yyval.s) + (yyvsp[0].i)) = '\0'; }
#line 2141 "parser.c"
    break;


#line 2145 "parser.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (filename, rcs, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, filename, rcs);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, filename, rcs);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (filename, rcs, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, filename, rcs);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, filename, rcs);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
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

			if (!prev || strncmp(prev, rev, (size_t)(dot - rev + 1))) {
				char *copy = strndup(rev, (size_t)(dot - rev));
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
