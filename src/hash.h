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

#ifndef _HASH_H
#define _HASH_H

#include <system.h>

#include <data.h>
#include <vector.h>

/*
 * A hash table entry.
 */
typedef struct {
	/* Local copies of the hash table's dup and free functions. */
	dup_fn_t dup_fn;
	free_fn_t free_fn;

	char *key; /* The (immutable) key for this entry. */
	unsigned int hash; /* The key's hash value. */
	void *value;       /* The entry's value.    */
} hash_entry_t;

/*
 * A hash table.
 *
 * Each slot in the hash table consists of a linked list.
 */
typedef struct {
	dup_fn_t dup_fn;
	free_fn_t free_fn;

	unsigned int capacity; /* Number of slots in hash table.   */
	unsigned int count;    /* Number of entries in hash table. */

	vector_t **data;       /* The slot array. */
} hash_t;

hash_t * hash_new (dup_fn_t, free_fn_t);
hash_t * hash_dup (const hash_t *);
void hash_expand (hash_t *, unsigned int);

void hash_insert_nocopy (hash_t *, const char *, void *);

/*
 * Maps <key> to <value> in the hash table <hash>. <key> and <value> are
 * both duplicated.
 */
static inline void
hash_insert(hash_t *hash, const char *key, const void *value) {
	assert(hash);

	if (hash->dup_fn)
		hash_insert_nocopy(hash, key, (hash->dup_fn)(value));
	else
		hash_insert_nocopy(hash, key, (void *)value);
}

void ** hash_get(hash_t *, const char *);
void hash_free(hash_t *);

/*
 * Returns the number of entries in <hash>.
 */
static inline unsigned int
hash_count(const hash_t *hash) { assert(hash); return hash->count; }

/*
 * A hash table iterator.
 *
 * This points to the current slot, the end of the slot array, and the
 * current element in the current slot.
 */
typedef struct {
	vector_t **base;
	vector_t **end;
	unsigned int i;
} hash_iter_struct_t;

typedef hash_iter_struct_t *hash_iter_t;
hash_iter_t hash_iter (hash_t *);

/*
 * Returns the key of the hash table element pointed to by <iter>.
 */
static inline const char *
hash_get_key(hash_iter_t iter) {
	assert(iter);
	return ((hash_entry_t *)vector_get(*iter->base, iter->i))->key;
}

/*
 * Returns the value of the hash table element pointed to by <iter>.
 */
static inline void *
hash_get_value(hash_iter_t iter) {
	assert(iter);
	return ((hash_entry_t *)vector_get(*iter->base, iter->i))->value;
}

hash_iter_t hash_next(hash_iter_t);

/*
 * Frees <iter> (for use when the last element may or may not have been
 * reached through hash_next).
 */
static inline void
hash_iter_free(hash_iter_t iter) {
	if (iter)
		FREE(iter);
}

#endif /* _HASH_H */
