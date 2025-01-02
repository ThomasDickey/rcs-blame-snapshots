%{
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
%}

%union {
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

%locations
%error-verbose

%parse-param {const char *filename}
%parse-param {rcs_t *rcs}

%token <i> NUM
%token <i> ID
%token <i> SYM
%token <i> STR
%token <i> STR_FINAL

%token HEAD
%token BRANCH
%token ACCESS
%token SYMBOLS
%token LOCKS
%token STRICT
%token COMMENT
%token EXPAND
%token DATE
%token AUTHOR
%token STATE
%token BRANCHES
%token NEXT
%token DESC
%token LOG
%token TEXT

%type <s> admin_head admin_branch admin_comment
%type <s> delta_author delta_state deltatext_log id_or_sym
%type <i> admin_strict deltatext_log_bit
%type <date> delta_date
%type <vector> admin_access id_list
%type <lines> deltatext_text deltatext_text_string
%type <hash> admin_symbols admin_locks delta_branches
%type <hash> num_list id_num_list sym_num_list
%type <delta> delta delta_next
%type <expand> admin_expand

%%

rcstext:
		{
			yylloc.line = 1;
			yylloc.off = yylloc.next = 0;
			lines = 0;
			rcs->delta_list = hash_new((dup_fn_t)delta_dup, (free_fn_t)delta_free);
		}
		admin_head
		admin_branch
		admin_access
		admin_symbols
		admin_locks
		admin_strict
		admin_comment
		admin_expand
		newphrase_list
		delta_list
		{
			if ($2) {
				int count;

				$<trunk>$.head = (delta_t *)rcs_get_delta(rcs, $2);
				if (!$<trunk>$.head) {
					yyerror(filename, rcs, "head revision is missing");
					YYERROR;
				}

				$<trunk>$.branches = hash_new(NULL, NULL);
				count = _parser_count_deltalist(rcs, $<trunk>$.head, $<trunk>$.branches);
				if (count < 0) {
					yyerror(filename, rcs, "delta tree is malformed");
					YYERROR;
				}
				if ((unsigned)count != hash_count(rcs->delta_list)) {
					yyerror(filename, rcs, "unreachable deltas exist");
					YYERROR;
				}
			} else {
				$<trunk>$.head = NULL;
				$<trunk>$.branches = NULL;
			}
		}
		desc
		deltatext_list
		{
			rcs->head = $<trunk>12.head;
			rcs->branch = ($3 ? strdup($3) : ($2 ? rcs_rev_to_branch($2) : NULL));
			rcs->branches = $<trunk>12.branches;
			rcs->access = $4;
			rcs->symbols = $5;
			rcs->locks = $6;
			rcs->strict = (int) $7;
			rcs->comment = $8;
			rcs->expand = $9;
			rcs->lines = lines;
		}
	;

admin_head:
		HEAD NUM ';' { $$ = rcs->start + @2.off; *($$ + $2) = '\0'; }
	|	HEAD ';' { $$ = NULL; }
	;

admin_branch:
		/* empty */ { $$ = NULL; }
	|	BRANCH NUM ';' { $$ = rcs->start + @2.off; *($$ + $2) = '\0'; }
	| BRANCH ';' { $$ = NULL; }
	;

admin_access:
		ACCESS id_list ';' { $$ = $2; }
	;

admin_symbols:
		SYMBOLS sym_num_list ';' { $$ = $2; }
	;

admin_locks:
		LOCKS id_num_list ';' { $$ = $2; }
	;

admin_strict:
		/* empty */ { $$ = 0; }
	|	STRICT ';' { $$ = 1; }
	;

admin_comment:
		/* empty */ { $$ = NULL; }
	|	COMMENT STR_FINAL ';'  { $$ = rcs->start + @2.off; *($$ + $2) = '\0'; }
	|	COMMENT ';' { $$ = NULL; }
	;

admin_expand:
		/* empty */ { $$ = EXPAND_UNDEFINED; }
	| EXPAND STR_FINAL ';' {
			if (!strncmp(rcs->start + @2.off, "kv", $2))
				$$ = EXPAND_KEY_VALUE;
			else if (!strncmp(rcs->start + @2.off, "kvl", $2))
				$$ = EXPAND_KEY_VALUE_LOCKER;
			else if (!strncmp(rcs->start + @2.off, "k", $2))
				$$ = EXPAND_KEY_ONLY;
			else if (!strncmp(rcs->start + @2.off, "o", $2))
				$$ = EXPAND_OLD_STRING;
			else if (!strncmp(rcs->start + @2.off, "b", $2))
				$$ = EXPAND_BINARY_STRING;
			else if (!strncmp(rcs->start + @2.off, "v", $2))
				$$ = EXPAND_VALUE_ONLY;
			else {
				yyerror(filename, rcs, "invalid keyword expansion type");
				YYERROR;
			}
		}
	| EXPAND ';' { $$ = EXPAND_UNDEFINED; }
	;

delta_list:
		/* empty */
	| delta_list delta
	;

delta:
		NUM
		delta_date
		delta_author
		delta_state
		delta_branches
		delta_next
		newphrase_list
		{
			char *num = rcs->start + @1.off;
			*(num + $1) = '\0';
			$$ = rcs_get_delta_template(rcs, num);
			if (!delta_is_template($$)) {
				yyerror(filename, rcs, "delta is multiply defined");
				YYERROR;
			}
			delta_complete_template_nocopy($$, $2, $3, $4, $5, $6);
		}
	;

delta_date:
		DATE NUM ';' {
			char *num = rcs->start + @2.off;
			*(num + $2) = '\0';
			$$ = date_parse_rev(num);
			if ($$ < 0) {
				yyerror(filename, rcs, "invalid date");
				YYERROR;
			}
		}
	;

delta_author:
		AUTHOR id_or_sym ';' { $$ = $2; }
	;

delta_state:
		STATE id_or_sym ';' { $$ = $2; }
	| STATE ';' { $$ = NULL; }
	;

delta_branches:
		BRANCHES num_list ';' { $$ = $2; }
	|	BRANCHES ';' { $$ = NULL; }
	;

delta_next:
		NEXT NUM ';' {
			char *num = rcs->start + @2.off;
			*(num + $2) = '\0';
			$$ = rcs_get_delta_template(rcs, num);
		}
	| NEXT ';' { $$ = NULL; }
	;

desc:
		DESC gobble_string
	;

deltatext_list:
		/* empty */
	|	deltatext_list deltatext
	;

deltatext:
		NUM {
			const delta_t *delta;
			char *num = rcs->start + @1.off;
			*(num + $1) = '\0';
			delta = rcs_get_delta(rcs, num);
			if (delta && !delta_is_template(delta))
				$<delta>$ = (delta_t *)delta;
			else {
				yyerror(filename, rcs, "invalid delta revision");
				YYERROR;
			}
		}
		deltatext_log
		newphrase_list
		deltatext_text { delta_complete_text_nocopy($<delta>2, $3, $5); }
	;

deltatext_log:
		LOG deltatext_log_bit STR_FINAL {
			/* Sigh... Can't rely on @2 because the empty rule below
			 * screws up the location stack. */
			rcs->start[@3.off + $3] = '\0';
			$$ = rcs->start + @3.off - $2;
		}
	;

deltatext_log_bit:
		/* empty */ { $$ = 0; }
	|	deltatext_log_bit STR { $$ = $1 + $2; }
	;

deltatext_text:
		TEXT deltatext_text_string STR_FINAL {
			$$ = $2;
			lines_append_nocopy($$, rcs->start + @3.off, $3);
			lines++;
		}
	;

deltatext_text_string:
		/* empty */ { $$ = lines_new(); }
	|	deltatext_text_string STR {
			lines_append_nocopy($$, rcs->start + @2.off, $2);
			lines++;
		}
	;

id_list:
		/* empty */ { $$ = vector_new(NULL, NULL); }
	|	id_list id_or_sym { vector_append_nocopy($$, $2); }
	;

num_list:
		NUM {
			char *branch, *num;
			$$ = hash_new(NULL, NULL);
			num = rcs->start + @1.off;
			*(num + $1) = '\0';
			branch = rcs_rev_to_branch(num);
			hash_insert_nocopy($$, branch, rcs_get_delta_template(rcs, num));
			FREE(branch);
		}
	| num_list NUM {
			char *branch, *num;
			num = rcs->start + @2.off;
			*(num + $2) = '\0';
			if (!rcs_rev_is_valid(num)) {
				yyerror(filename, rcs, "branch revision is malformed");
				YYERROR;
			}
			branch = rcs_rev_to_branch(num);
			hash_insert_nocopy($$, branch, rcs_get_delta_template(rcs, num));
			FREE(branch);
		}
	;

id_num_list:
		/* empty */ {
			$$ = hash_new(NULL, NULL);
		}
	| id_num_list id_or_sym ':' NUM {
			char *num = rcs->start + @4.off;
			*(num + $4) = '\0';
			hash_insert_nocopy($$, $2, rcs_get_delta_template(rcs, num));
		}
	;

sym_num_list:
		/* empty */ { $$ = hash_new(NULL, NULL); }
	| sym_num_list SYM ':' NUM {
		char *sym, *num;
		sym = rcs->start + @2.off;
		*(sym + $2) = '\0';
		num = rcs->start + @4.off;
		*(num + $4) = '\0';
		hash_insert_nocopy($$, sym, num);
	}
	;

newphrase_list:
		/* empty */
	|	id_or_sym word_list ';'
	;

word_list:
		/* empty */
	| word_list word
	;

word:
		ID
	|	NUM
	|	gobble_string
	|	':'
	;

id_or_sym:
		ID { $$ = rcs->start + @1.off; *($$ + $1) = '\0'; }
	|	SYM { $$ = rcs->start + @1.off; *($$ + $1) = '\0'; }
	;

gobble_string:
		gobble_string_bit STR_FINAL
	;

gobble_string_bit:
		/* empty */
	|	gobble_string_bit STR
	;

%%

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
