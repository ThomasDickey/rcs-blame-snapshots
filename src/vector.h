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

#ifndef _VECTOR_H
#define _VECTOR_H

#include <system.h>

#include <data.h>

/*
 * A vector.
 */
typedef struct {
	dup_fn_t dup_fn;
	free_fn_t free_fn;
	
	unsigned int capacity; /* Number of slots in vector.   */
	unsigned int count;    /* Number of entries in vector. */
	
	void **data;           /* The slot array.              */
} vector_t;

vector_t * vector_new PARAMS((dup_fn_t, free_fn_t));
vector_t * vector_dup PARAMS((const vector_t *));
void vector_expand PARAMS((vector_t *, unsigned int));
void vector_append_nocopy PARAMS((vector_t *, void *));

/*
 * Appends a duplication of <x> to <vector>.
 */
static inline void
vector_append(vector_t *vector, const void *x) {
	assert(vector);
	
	if (vector->dup_fn)
		vector_append_nocopy(vector, (vector->dup_fn)(x));
	else
		vector_append_nocopy(vector, (void *)x);
}

void vector_free PARAMS((vector_t *));
void vector_free_nofree PARAMS((vector_t *));

/*
 * Returns the number of entries in <vector>.
 */
static inline unsigned int
vector_count(const vector_t *vector) { assert(vector); return vector->count; }

/*
 * Returns the <i>-th vector entry in <vector>.
 */
static inline void *
vector_get(vector_t *vector, unsigned int i) {
	assert(vector);
	return vector->data[i];
}

#endif /* _VECTOR_H */
