/*
 * Blame - An RCS file annotator
 * Copyright (C) 2004, 2005  Michael Chapman
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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <canonicalize.h>
#include <dirname.h>

#include <date.h>
#include <rcs.h>

typedef unsigned int yy_size_t;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse (const char *, rcs_t *);
extern void yy_switch_to_buffer (YY_BUFFER_STATE);
extern void yy_delete_buffer (YY_BUFFER_STATE);
extern YY_BUFFER_STATE yy_scan_bytes (char *, yy_size_t);
#define YY_CURRENT_BUFFER yy_current_buffer

/*
 * Parses and returns the RCS file specified by <rcs_filename>.
 */
rcs_t *
rcs_parse(const char *rcs_filename) {
	rcs_t *rcs;
	FILE *stream;
	struct stat stat_buf;
	YY_BUFFER_STATE current_buffer;

	assert(rcs_filename);

	stream = fopen(rcs_filename, "r");
	if (!stream) {
		error(0, errno, "%s", rcs_filename);
		return NULL;
	}

	rcs = CALLOC(1, rcs_t);
	rcs->filename = strdup(rcs_filename);
	rcs->full_filename = canonicalize_file_name(rcs_filename);
	if (!rcs->full_filename) {
		FREE(rcs->filename);
		FREE(rcs);
		error(0, errno, "%s", rcs_filename);
		return NULL;
	}
	rcs->short_filename = base_name(rcs_filename);

	if (fstat(fileno(stream), &stat_buf)) {
		FREE(rcs->full_filename);
		FREE(rcs->filename);
		FREE(rcs);
		error(0, errno, "Could not stat %s", rcs_filename);
		return NULL;
	}
	rcs->length = (size_t) stat_buf.st_size;
	rcs->start = (char *)mmap(
		NULL, rcs->length, PROT_WRITE | PROT_READ, MAP_PRIVATE, fileno(stream), 0
	);
	if (!rcs->start) {
		FREE(rcs->full_filename);
		FREE(rcs->filename);
		FREE(rcs);
		error(0, errno, "Could not mmap %s", rcs_filename);
		return NULL;
	}
	current_buffer = yy_scan_bytes(rcs->start, (yy_size_t)rcs->length);
	yy_switch_to_buffer(current_buffer);

	if (yyparse(rcs_filename, rcs)) {
		if (fclose(stream))
			error(0, errno, "%s", rcs_filename);
		rcs_free(rcs);
		return NULL;
	}
	yy_delete_buffer(current_buffer);

	if (fclose(stream))
		error(0, errno, "%s", rcs_filename);

	if (!rcs->head)
		return rcs;

	return rcs;
}

/*
 * Deeply frees <rcs>.
 */
void
rcs_free(rcs_t *rcs) {
	assert(rcs);
	assert(rcs->filename);
	assert(rcs->full_filename);
	assert(rcs->short_filename);

	FREE(rcs->filename);
	FREE(rcs->short_filename);
	FREE(rcs->full_filename);

	if (rcs->head) delta_ref_free(rcs->head);
	if (rcs->branch) FREE(rcs->branch);
	if (rcs->branches) hash_free(rcs->branches);
	if (rcs->access) vector_free(rcs->access);
	if (rcs->symbols) hash_free(rcs->symbols);
	if (rcs->locks) hash_free(rcs->locks);

	if (rcs->delta_list) hash_free(rcs->delta_list);

	munmap(rcs->start, rcs->length);

	FREE(rcs);
}

/*
 * Returns true iff <c> is a valid RCS ID character.
 */
static inline int
_isidchar(char c) {
	return ISGRAPH(c) && !ISDIGIT(c)
		&& (c != '$') && (c != ',')
		&& (c != '.') && (c != ':')
		&& (c != ';') && (c != '@');
}

/*
 * Returns true iff <rev> is a valid RCS revision.
 */
int
rcs_rev_is_valid(const char *rev) {
	unsigned int dots;
	const char *c;

	assert(rev);

	dots = 0;
	for (c = rev; *c; c++)
		if (*c == '.')
			dots++;
		else if (!ISDIGIT(*c))
			return 0;

	return dots % 2;
}

/*
 * Returns true iff <rev> is a valid RCS branch.
 */
int
rcs_branch_is_valid(const char *branch) {
	unsigned int dots;
	const char *c;

	assert(branch);

	dots = 0;
	for (c = branch; *c; c++)
		if (*c == '.')
			dots++;
		else if (!ISDIGIT(*c))
			return 0;

	return !(dots % 2);
}

/*
 * Returns the branch on which revision <rev> is found.
 */
char *
rcs_rev_to_branch(const char *rev) {
	char *branch;

	assert(rev && rcs_rev_is_valid(rev));

	branch = strdup(rev);
	*(strrchr(branch, '.')) = '\0';
	return branch;
}

/*
 * Returns the base of branch <branch> in RCS file <rcs>.
 */
static const delta_t *
_rcs_get_base(const rcs_t *rcs, const char *branch) {
	char *rev, *dot;
	const delta_t *result;

	assert(rcs);
	assert(branch && rcs_branch_is_valid(branch));

	result = NULL;

	rev = strdup(branch);
	dot = strrchr(rev, '.');
	if (dot) {
		const delta_t *from, **base;

		*dot = '\0';
		from = rcs_get_delta(rcs, rev);

		if (!from) {
			error(0, 0, "%s: revision %s absent", rcs->filename, rev);
			FREE(rev);
			return NULL;
		}

		FREE(rev);

		if (from->branches) {
			base = (const delta_t **)hash_get(from->branches, branch);
			if (base) result = *base;
		}
	} else {
		const delta_t **base;

		FREE(rev);

		base = (const delta_t **)hash_get(
			rcs->branches, branch
		);
		if (base) result = *base;
	}

	if (!result)
		error(0, 0, "%s: branch %s absent", rcs->filename, branch);

	return result;
}

/*
 * Returns the earliest revision on branch <branch> in RCS file <rcs> that has
 * date equal or after <date> (if it is not -1), author <author> (if it is not
 * NULL), and state <state> (if it is not NULL). Returns NULL if no such
 * revision is found.
 */
static char *
_rcs_find_rev(
	const rcs_t *rcs,
	const char *branch,
	time_t date,
	const char *author,
	const char *state,
	long zone_offset
) {
	const delta_t *delta, *result;
	int trunk;
	char *cond;
	size_t len;

	assert(rcs && rcs->delta_list);
	assert(branch && rcs_branch_is_valid(branch));

	/* The trunk is in reverse. */
	trunk = (strchr(branch, '.') == NULL);

	delta = _rcs_get_base(rcs, branch);
	if (!delta)
		return NULL;

	result = NULL;

	while (delta && (!trunk || !result)) {
		int ok = ((date == -1) || (delta_get_date(delta) <= date));
		ok = ok && (!author || !strcmp(delta_get_author(delta), author));
		ok = ok && (!state || !strcmp(delta_get_state(delta), state));

		if (ok)
			result = delta;

		delta = delta_get_next(delta);
	}

	if (result)
		return strdup(delta_get_revision(result));

	cond = SALLOC(1);
	len = 0;

	if ((date >= 0) || author || state) {
		len += 5;
		cond = SREALLOC(cond, len);
		strcat(cond, " has");
	}

	if (date >= 0) {
		char *date_str = date_sprintf(date, zone_offset);
		len += 15 + strlen(date_str);
		cond = SREALLOC(cond, len);
		strcat(cond, " a date before ");
		strcat(cond, date_str);
		FREE(date_str);
	}

	if (author) {
		if (date >= 0) len += 4;
		len += 8 + strlen(author);
		cond = SREALLOC(cond, len);
		if (date >= 0) strcat(cond, " and");
		strcat(cond, " author ");
		strcat(cond, author);
	}

	if (state) {
		if ((date >= 0) || author) len += 4;
		len += 7 + strlen(state);
		cond = SREALLOC(cond, len);
		if ((date >= 0) || author) strcat(cond, " and");
		strcat(cond, " state ");
		strcat(cond, state);
	}

	error(0, 0, "%s: no revision on branch %s%s",
		rcs->filename, branch, cond);

	FREE(cond);
	return NULL;
}

/*
 * Compares revision numbers <a> and <b>.
 */
static inline int
_revcmp(const char *a, const char *b) {
	long int d = 0;
	while (a && b && !(d = (long) (strtoul(a, NULL, 0) - strtoul(b, NULL, 0))) ) {
		a = strchr(a, '.'); if (a) a++;
		b = strchr(b, '.'); if (b) b++;
	}
	return (int) d;
}

/*
 * Returns the latest revision on or before <rev> in RCS file <rcs>.
 */
static const delta_t *
_rcs_find_rev_before(const rcs_t *rcs, const char *rev) {
	char *branch;
	const delta_t *delta, *result;
	int trunk;

	assert(rcs && rcs->delta_list);
	assert(rev && rcs_rev_is_valid(rev));

	branch = rcs_rev_to_branch(rev);

	/* The trunk is in reverse. */
	trunk = (strchr(branch, '.') == NULL);

	delta = _rcs_get_base(rcs, branch);
	FREE(branch);
	if (!delta)
		return NULL;

	result = NULL;

	while (delta && (!trunk || !result)) {
		const char *r, *dot;

		r = delta_get_revision(delta);
		dot = strrchr(r, '.');
		assert(dot);
		if (strncmp(rev, r, (size_t) (dot - r + 1)))
			break;

		if (_revcmp(r, rev) <= 0)
			result = delta;

		delta = delta_get_next(delta);
	}

	if (!result)
		error(0, 0, "%s: revision %s is too low", rcs->filename, rev);

	return result;
}

/*
 * Returns <symbol> if it is not a valid symbol in RCS file <rcs>, or the
 * corresponding revision if it is. In the last case it also checks that
 * <symbol> consists only of valid RCS ID characters.
 */
static const char *
_rcs_resolve_symbol(const rcs_t *rcs, const char *symbol) {
	const char *rev, *c;

	assert(rcs);
	assert(rcs->symbols);
	assert(symbol);

	rev = rcs_get_symbol(rcs, symbol);
	if (rev)
		return rev;

	for (c = symbol; *c && !_isidchar(*c); c++)
		;
	if (*c)
		return NULL;
	return symbol;
}

/*
 * Appends the resolved value of symbol <symbol> to <rev>, updating length
 * *<len>. RCS file <rcs> is used to look up the <symbol>. Returns -1 on error,
 * otherwise 0.
 */
static int
_rcs_append_component(
	const rcs_t *rcs, const char *symbol, char **rev, size_t *len
) {
	const char *r;

	assert(rcs);
	assert(symbol);
	assert(rev && *rev);
	assert(len);

	r = _rcs_resolve_symbol(rcs, symbol);
	if (!r)
		return -1;
	*len += strlen(r) + ((*rev)[0] ? 1 : 0);
	*rev = REALLOC(*rev, *len + 1, char);
	if ((*rev)[0]) strcat(*rev, ".");
	strcat(*rev, r);

	return 0;
}

/*
 * Returns the locker of revision <rev> for RCS file <rcs>, or NULL if that
 * revision is not locked.
 */
const char *
rcs_get_locker(const rcs_t *rcs, const char *rev) {
	hash_iter_t iter;

	assert(rcs);
	assert(rev && rcs_rev_is_valid(rev));

	for (iter = hash_iter(rcs->locks); iter; iter = hash_next(iter))
		if (
			!strcmp(rev, delta_get_revision((const delta_t *)hash_get_value(iter)))
		) {
			const char *locker = hash_get_key(iter);
			hash_iter_free(iter);
			return locker;
		}
	hash_iter_free(iter);

	return NULL;
}

/*
 * Returns a resolved version of RCS revision <tag> for RCS file <rcs>, given
 * additional restrictions <date>, <author> and <state>, or NULL on error.
 */
char *
rcs_resolve_tag(
	const rcs_t *rcs,
	const char *tag,
	time_t date,
	long zone_offset,
	const char *author,
	const char *state
) {
	char *rev;
	int is_branch;

	assert(rcs);

	is_branch = 0;
	if (!tag || !*tag) {
		/* If tag wasn't specified, choose the default branch. */
		rev = strdup(rcs->branch);
		is_branch = 1;
	} else {
		char *copy, *dot, *start, *end;
		size_t len;

		if (tag[0] == '.') {
			/* Start with the default branch. */
			rev = strdup(rcs->branch);
			len = strlen(rev);
			tag++;
		} else {
			/* Start with nothing. */
			rev = strdup("");
			len = 0;
		}

		/*
		 * We're going to inch our way along tag, marking off each
		 * component in turn.
		 */
		start = copy = strdup(tag);
		end = copy + strlen(copy);

		for (start = copy; (dot = strchr(start, '.')); start = dot + 1) {
			*dot = '\0';
			if (_rcs_append_component(rcs, start, &rev, &len)) {
				error(0, 0, "%s: could not resolve symbol %s", rcs->filename, start);
				FREE(copy);
				FREE(rev);
				return NULL;
			}
		}

		/*
		 * We're at the last component. If it's not empty, resolve
		 * it, then extract the branch.
		 */
		if (start != end) {
			if (_rcs_append_component(rcs, start, &rev, &len)) {
				error(0, 0, "%s: could not resolve symbol %s", rcs->filename, start);
				FREE(copy);
				FREE(rev);
				return NULL;
			}
			is_branch = rcs_branch_is_valid(rev);
		} else {
			/*
			 * Otherwise, we have any empty final component. The rev
			 * is only valid if we have collected a branch so far.
			 */
			if (!rcs_branch_is_valid(rev)) {
				error(0, 0, "%s: %s is not a valid branch", rcs->filename, rev);
				FREE(copy);
				FREE(rev);
				return NULL;
			}
			is_branch = 1;
		}
		FREE(copy);
	}

	/*
	 * If it's a branch, find the appropriate rev.
	 */
	if (is_branch) {
		char *result = _rcs_find_rev(rcs, rev, date, author, state, zone_offset);
		FREE(rev);
		return result;
	} else {
		const delta_t *delta;

		delta = rcs_get_delta(rcs, rev);
		if (!delta) {
			delta = _rcs_find_rev_before(rcs, rev);
			if (!delta) {
				FREE(rev);
				return NULL;
			}
		}
		if ((date >= 0) && (delta_get_date(delta) > date)) {
			char *date_str = date_sprintf(delta_get_date(delta), zone_offset);
			error(
				0, 0, "%s: revision %s has date %s",
				rcs->filename, rev, date_str
			);
			FREE(date_str);
			FREE(rev);
			return NULL;
		}
		if (author && strcmp(delta_get_author(delta), author)) {
			error(
				0, 0, "%s: revision %s has author %s",
				rcs->filename, rev, delta_get_author(delta)
			);
			FREE(rev);
			return NULL;
		}
		if (state && strcmp(delta_get_state(delta), state)) {
			error(
				0, 0, "%s: revision %s has state %s",
				rcs->filename, rev, delta_get_state(delta)
			);
			FREE(rev);
			return NULL;
		}
		FREE(rev);
		return strdup(delta_get_revision(delta));
	}
}
