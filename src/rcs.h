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

#ifndef _RCS_H
#define _RCS_H

#include <system.h>

#include <delta.h>
#include <hash.h>
#include <keyword.h>
#include <vector.h>

/*
 * An RCS file.
 */
typedef struct rcs {
	char *filename;       /* Absolute/relative RCS filename. */
	char *full_filename;  /* Absolute RCS filename.          */
	char *short_filename; /* Last component of RCS filename. */
	
	char *start;
	size_t length;
	
	delta_t *head;        /* The head revision; NULL if RCS file is empty.   */
	char *branch;         /* The default branch (NULL if RCS file is empty). */
	hash_t *branches;     /* Branches on the trunk.                          */
	vector_t *access;     /* Access list; parsed but not used.               */
	hash_t *symbols;      /* Symbol table.                                   */
	hash_t *locks;        /* Lock table; parsed but not used.                */
	int strict;           /* Strict locking; parsed but not used.            */
	const char *comment;  /* Comment prefix.                                 */
	expand_t expand;      /* Default expansion mode.                         */
	
	hash_t *delta_list;   /* Mapping of revision to delta.                   */
	
	unsigned int lines;
} rcs_t;

rcs_t * rcs_parse PARAMS((const char *));
void rcs_free PARAMS((rcs_t *));

/*
 * Returns the filename field in <rcs>.
 */
static inline const char *
rcs_get_filename(const rcs_t *rcs) {
	assert(rcs);
	return rcs->filename;
}

/*
 * Returns the full_filename field in <rcs>.
 */
static inline const char *
rcs_get_full_filename(const rcs_t *rcs) {
	assert(rcs);
	return rcs->full_filename;
}

/*
 * Returns the short_filename field in <rcs>.
 */
static inline const char *
rcs_get_short_filename(const rcs_t *rcs) {
	assert(rcs);
	return rcs->short_filename;
}

/*
 * Returns this RCS file's head revision.
 */
static inline const delta_t *
rcs_get_head(const rcs_t *rcs) {
	assert(rcs);
	return rcs->head;
}

/*
 * Returns the branch field in <rcs>.
 */
static inline const char *
rcs_get_branch(const rcs_t *rcs) {
	assert(rcs);
	return rcs->branch;
}

/*
 * Returns the revision for symbol <symbol> in <rcs>, if it exists.
 */
static inline const char *
rcs_get_symbol(const rcs_t *rcs, const char *symbol) {
	const char **rev;
	
	assert(rcs);
	assert(symbol);
	
	rev = (const char **)hash_get(rcs->symbols, symbol);
	return (rev ? *rev : NULL);
}

const char * rcs_get_locker PARAMS((const rcs_t *, const char *));

/*
 * Returns the comment field in <rcs>.
 */
static inline const char *
rcs_get_comment(const rcs_t *rcs) {
	assert(rcs);
	return rcs->comment;
}

/*
 * Returns the expand field in <rcs>.
 */
static inline expand_t
rcs_get_expand(const rcs_t *rcs) {
	assert(rcs);
	return rcs->expand;
}

/*
 * Returns delta <rev> in <rcs>, if it exists.
 */
static inline const delta_t *
rcs_get_delta(const rcs_t *rcs, const char *rev) {
	const delta_t **d;
	
	assert(rcs);
	assert(rev);
	
	d = (const delta_t **)hash_get(rcs->delta_list, rev);
	return (d ? *d : NULL);
}

/*
 * Returns a new delta template for delta <rev> in <rcs>,
 * or an existing delta if it already exists.
 */
static inline delta_t *
rcs_get_delta_template(const rcs_t *rcs, const char *rev) {
	delta_t **d, *delta;
	
	assert(rcs);
	assert(rev);
	
	d = (delta_t **)hash_get(rcs->delta_list, rev);
	if (d) return *d;
	delta = delta_new_template(rev);
	hash_insert_nocopy(rcs->delta_list, rev, delta);
	return delta;
}

char * rcs_resolve_tag PARAMS((
	const rcs_t *, const char *, time_t, long,
	const char *, const char *
));

int rcs_rev_is_valid PARAMS((const char *));
int rcs_branch_is_valid PARAMS((const char *));
char * rcs_rev_to_branch PARAMS((const char *));

#endif /* _RCS_H */
