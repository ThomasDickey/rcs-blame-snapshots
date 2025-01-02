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

#define DEFAULT_VECTOR_CAPACITY 50

#include <data.h>
#include <vector.h>

/*
 * Returns a new vector with the specified dup and free functions.
 */
vector_t *
vector_new(dup_fn_t dup_fn, free_fn_t free_fn) {
	vector_t *vector;

	vector = MALLOC(1, vector_t);
	vector->dup_fn = dup_fn;
	vector->free_fn = free_fn;
	vector->capacity = DEFAULT_VECTOR_CAPACITY;
	vector->count = 0;
	vector->data = MALLOC(vector->capacity, void *);

	return vector;
}

/*
 * Returns a deep duplicate of <vector>.
 */
vector_t *
vector_dup(const vector_t *vector) {
	vector_t *result;
	unsigned int i;

	assert(vector);

	result = MALLOC(1, vector_t);
	result->dup_fn = vector->dup_fn;
	result->free_fn = vector->free_fn;
	result->capacity = vector->capacity;
	result->count = vector->count;
	result->data = MALLOC(result->capacity, void *);
	if (result->dup_fn)
		for (i = 0; i < result->count; i++)
			result->data[i] = (result->dup_fn)(vector->data[i]);
	else
		memcpy(result->data, vector->data, result->count * sizeof(void *));

	return result;
}

/*
 * Ensures <vector> can contain at least <c> entries.
 */
void
vector_expand(vector_t *vector, unsigned int c) {
	assert(vector);

	if (c <= vector->capacity)
		return;

	vector->capacity = c;
	vector->data = REALLOC(vector->data, vector->capacity, void *);
}

/*
 * Appends <x> to <vector> without duplicating.
 */
void
vector_append_nocopy(vector_t *vector, void *x) {
	assert(vector);

	if (vector->count == vector->capacity)
		vector_expand(vector, 2 * vector->count);
	vector->data[vector->count] = x;
	vector->count++;
}

/*
 * Deeply frees <vector>.
 */
void
vector_free(vector_t *vector) {
	unsigned int i;

	assert(vector);

	if (vector->free_fn)
		for (i = 0; i < vector->count; i++)
			(vector->free_fn)(vector->data[i]);
	FREE(vector->data);
	FREE(vector);
}

/*
 * Frees <vector>, but DOES NOT free each entry. Use with caution.
 */
void
vector_free_nofree(vector_t *vector) {
	assert(vector);
	FREE(vector->data);
	FREE(vector);
}
