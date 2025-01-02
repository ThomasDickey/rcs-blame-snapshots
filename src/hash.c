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

#include <hash.h>
#include <rcs.h>

#define DEFAULT_HASH_CAPACITY 50

/*
 * Returns a hash for <key>.
 */
static inline unsigned int
hash_fn(const char *key) {
	unsigned int h, t;

	h = 0;
	if (key) {
		while (*key) {
			t = h & 0xf8000000;
			h <<= 5;
			h ^= t >> 27;
			h ^= (unsigned) *key++;
		}
	}
	return h;
}

/*
 * Returns a new hash table with the specified dup and free functions.
 */
hash_t *
hash_new(dup_fn_t dup_fn, free_fn_t free_fn) {
	hash_t *hash;

	hash = MALLOC(1, hash_t);
	hash->dup_fn = dup_fn;
	hash->free_fn = free_fn;
	hash->capacity = DEFAULT_HASH_CAPACITY;
	hash->count = 0;
	hash->data = CALLOC(hash->capacity, vector_t *);

	return hash;
}

/*
 * Returns a deep duplicate of <hash>.
 */
hash_t *
hash_dup(const hash_t *hash) {
	hash_t *result;
	unsigned int i;

	assert(hash && hash->data);

	result = MALLOC(1, hash_t);
	result->dup_fn = hash->dup_fn;
	result->free_fn = hash->free_fn;
	result->capacity = hash->capacity;
	result->count = hash->count;
	result->data = MALLOC(hash->capacity, vector_t *);

	for (i = 0; i < hash->capacity; i++)
		result->data[i] = (hash->data[i] ? vector_dup(hash->data[i]) : NULL);

	return result;
}

/*
 * Returns a new hash table entry.
 */
static hash_entry_t *
_hash_entry_new(
	dup_fn_t dup_fn, free_fn_t free_fn, const char *key, void *value
) {
	hash_entry_t *entry;

	entry = MALLOC(1, hash_entry_t);
	entry->dup_fn = dup_fn;
	entry->free_fn = free_fn;
	entry->key = (key ? strdup(key) : NULL);
	entry->hash = hash_fn(key);
	entry->value = value;

	return entry;
}

/*
 * Returns a deep duplicate of <entry>.
 */
static hash_entry_t *
_hash_entry_dup(const hash_entry_t *entry) {
	hash_entry_t *result;

	assert(entry);

	result = MALLOC(1, hash_entry_t);
	result->dup_fn = entry->dup_fn;
	result->free_fn = entry->free_fn;
	result->key = (entry->key ? strdup(entry->key) : NULL);
	result->hash = entry->hash;
	result->value = (
		entry->dup_fn
		? (entry->dup_fn)(entry->value)
		: entry->value
	);

	return result;
}

/*
 * Deeply frees <entry>.
 */
static void
_hash_entry_free(hash_entry_t *entry) {
	assert(entry);

	if (entry->key) FREE(entry->key);
	if (entry->free_fn) (entry->free_fn)(entry->value);
	FREE(entry);
}

/*
 * Inserts a duplicate of <ENTRY> into <HASH>.
 */
#define _hash_insert_entry(HASH, ENTRY) \
	_hash_insert_entry_nocopy((HASH), _hash_entry_dup(ENTRY))

/*
 * Inserts a <entry> into <hash> without duplicating.
 */
static void
_hash_insert_entry_nocopy(hash_t *hash, hash_entry_t *entry) {
	unsigned int slot;
	unsigned int i;
	hash_entry_t *e;

	assert(hash);
	assert(hash->data);
	assert(entry);

	slot = entry->hash % hash->capacity;
	if (!hash->data[slot])
		hash->data[slot] = vector_new(
			(dup_fn_t)_hash_entry_dup, (free_fn_t)_hash_entry_free
		);

	for (i = 0; i < vector_count(hash->data[slot]); i++) {
		e = (hash_entry_t *)vector_get(hash->data[slot], i);
		if (
			e->hash == entry->hash && (
				(e->key == entry->key) || (
					e->key && entry->key && !strcmp(e->key, entry->key)
				)
			)
		) {
			if (hash->free_fn) (hash->free_fn)(e->value);
			e->value = entry->value;
			if (entry->key) FREE(entry->key);
			FREE(entry);
			return;
		}
	}
	vector_append_nocopy(hash->data[slot], entry);
}

/*
 * Ensures <hash> can contain at least <c> entries.
 */
void
hash_expand(hash_t *hash, unsigned int c) {
	unsigned int i, j, cap;
	vector_t **data;

	assert(hash);
	assert(hash->data);

	if (c <= hash->capacity)
		return;

	cap = hash->capacity;
	hash->capacity = c;
	data = hash->data;
	hash->data = CALLOC(hash->capacity, vector_t *);

	for (i = 0; i < cap; i++)
		if (data[i]) {
			for (j = 0; j < vector_count(data[i]); j++)
				_hash_insert_entry_nocopy(hash, (hash_entry_t *)vector_get(data[i], j));
			vector_free_nofree(data[i]);
		}

	FREE(data);
}

/*
 * Maps <key> to <value> in the hash table <hash> without duplicating <value>.
 * <key> is duplicated, however.
 */
void
hash_insert_nocopy(hash_t *hash, const char *key, void *value) {
	hash_entry_t *entry;

	assert(hash);

	if (hash->count++ * 2 > hash->capacity)
		hash_expand(hash, hash->capacity * 2);

	entry = _hash_entry_new(hash->dup_fn, hash->free_fn, key, value);
	_hash_insert_entry_nocopy(hash, entry);
}

/*
 * Returns a pointer to a pointer to the value in <hash> with key <key>, or
 * NULL if no such entry exists.
 */
void **
hash_get(hash_t *hash, const char *key) {
	unsigned int h, i, slot;
	hash_entry_t *e;

	assert(hash);
	assert(hash->data);

	h = hash_fn(key);
	slot = h % hash->capacity;
	if (!hash->data[slot])
		return NULL;
	for (i = 0; i < vector_count(hash->data[slot]); i++) {
		e = (hash_entry_t *)vector_get(hash->data[slot], i);
		if (
			e->hash == h && (
				(e->key == key) || (e->key && key && !strcmp(e->key, key))
			)
		)
			return &e->value;
	}
	return NULL;
}

/*
 * Deeply frees <hash>.
 */
void
hash_free(hash_t *hash) {
	unsigned int i;

	assert(hash);
	assert(hash->data);

	for (i = 0; i < hash->capacity; i++)
		if (hash->data[i]) vector_free(hash->data[i]);

	FREE(hash->data);
	FREE(hash);
}

/*
 * Returns a new iterator on <hash>.
 */
hash_iter_t
hash_iter(hash_t *hash) {
	unsigned int i;
	hash_iter_struct_t *iter;

	assert(hash);
	assert(hash->data);

	for (i = 0; i < hash->capacity; i++)
		if (hash->data[i]) {
			iter = MALLOC(1, hash_iter_struct_t);
			iter->base = &hash->data[i];
			iter->end = &hash->data[hash->capacity];
			iter->i = 0;

			return iter;
		}

	return NULL;
}

/*
 * Advances and returns the iterator <iter>.
 */
hash_iter_t
hash_next(hash_iter_t iter) {
	assert(iter);

	if (++iter->i < vector_count(*iter->base))
		return iter;
	while (++iter->base != iter->end)
		if (*iter->base) {
			iter->i = 0;
			return iter;
		}
	FREE(iter);
	return NULL;
}
