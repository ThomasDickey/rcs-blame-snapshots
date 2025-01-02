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

#ifndef _DELTA_H
#define _DELTA_H

#include <system.h>

#include <hash.h>
#include <lines.h>

/*
 * An RCS delta entry. This contains info from both the delta and deltatext
 * portions of the RCS file.
 */
typedef struct _delta_t {
	int template; /* If true, then all but the revision field is empty. */

	const char *revision; /* The delta's revision.  */
	time_t date;          /* The delta's date.      */
	const char *author;   /* The delta's author.    */
	const char *state;    /* The delta's state.     */

	hash_t *branches; /* Maps (char *) to (delta_t). */

	/* The delta's log entry. */
	const char *log;

	/*
	 * The delta's text. Verbatim for the head revision; otherwise a sequence
	 * of deletions or additions.
	 */
	lines_t *text;

	/*
	 * A pointer to the next revision, or NULL if it is at a branch tip or
	 * the bottom of the trunk. During RCS file parsing this may point to
	 * a template delta.
	 */
	const struct _delta_t *next;
} delta_t;

/*
 * Loop each branch base <B> on delta <D> using hash_iter_t <I>.
 */
#define for_each_branch_base(B, D, I) \
	for ( \
		(I) = ((D)->branches ? hash_iter((D)->branches) : NULL); \
		(I) && ((B) = (const delta_t *)hash_get_value(I), 1); \
		(I) = hash_next(I) \
	)

/*
 * Returns a new delta template for revision <rev>.
 */
static inline delta_t *
delta_new_template(const char *rev) {
	delta_t *delta;

	assert(rev);

	delta = MALLOC(1, delta_t);
	delta->template = 1;
	delta->revision = rev;
	delta->log = NULL;
	delta->text = NULL;

	return delta;
}

/*
 * Completes delta template <delta> using the specified values. <next> may
 * be a delta template.
 */
static inline void
delta_complete_template_nocopy(delta_t *delta,
	time_t date, char *author, char *state, hash_t *branches, const delta_t *next
) {
	assert(delta && delta->template);
	assert(date >= 0);
	assert(author);
	assert(state);

	delta->template = 0;
	delta->date = date;
	delta->author = author;
	delta->state = state;
	delta->branches = branches;
	delta->next = next;
}

/*
 * Completes the log and text fields in delta <delta>. <delta> must not be
 * a template.
 */
static inline void
delta_complete_text_nocopy(delta_t *delta, char *log, lines_t *text) {
	assert(delta && !delta->template);
	assert(log);
	assert(text);

	delta->log = log;
	delta->text = text;
}

delta_t * delta_dup (const delta_t *);
void delta_free (delta_t *);

/*
 * Dup and free functions for data structures that should not own the delta_t.
 */
static inline const delta_t *
delta_ref_dup(const delta_t *delta) { return delta; }
static inline void
delta_ref_free(const delta_t *delta _UNUSED) {}

/*
 * Returns true iff <delta> is a template.
 */
static inline int
delta_is_template(const delta_t *delta) {
	assert(delta);
	return delta->template;
}

/*
 * Returns the revision field in <delta>.
 */
static inline const char *
delta_get_revision(const delta_t *delta) {
	assert(delta && delta->revision);
	return delta->revision;
}

/*
 * Returns the date field in <delta>.
 */
static inline time_t
delta_get_date(const delta_t *delta) {
	assert(delta && !delta_is_template(delta));
	return delta->date;
}

/*
 * Returns the author field in <delta>.
 */
static inline const char *
delta_get_author(const delta_t *delta) {
	assert(delta && !delta_is_template(delta));
	return delta->author;
}

/*
 * Returns the state field in <delta>.
 */
static inline const char *
delta_get_state(const delta_t *delta) {
	assert(delta && !delta_is_template(delta));
	return delta->state;
}

/*
 * Returns the base of branch <branch> in <delta>, or NULL if it doesn't
 * exist.
 */
static inline const delta_t *
delta_get_branch(const delta_t *delta, const char *branch) {
	const delta_t **base;

	assert(delta && !delta_is_template(delta));
	base = (const delta_t **)hash_get(delta->branches, branch);
	return (base ? *base : NULL);
}

/*
 * Returns the log field in <delta>.
 */
static inline const char *
delta_get_log(const delta_t *delta) {
	assert(delta && !delta_is_template(delta));
	return delta->log;
}

/*
 * Returns the text field in <delta>.
 */
static inline const lines_t *
delta_get_text(const delta_t *delta) {
	assert(delta && !delta_is_template(delta));
	return delta->text;
}

/*
 * Returns the next delta after the specified <delta>, or NULL if <delta> is
 * a branch tip or the base of the trunk.
 */
static inline const delta_t *
delta_get_next(const delta_t *delta) {
	assert(delta && !delta_is_template(delta));
	return delta->next;
}

#endif /* _DELTA_H */
