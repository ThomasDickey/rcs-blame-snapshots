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

#ifndef _DATA_H
#define _DATA_H

#include <system.h>

/*
 * Dup and free operators for data stored in data structures.
 *
 * Either:
 *  - The dup operator returns a deep duplication of the specified pointer.
 *  - The free operator deeply frees the given pointer.
 * Or:
 *  - The dup operator returns a duplication of the specified pointer.
 *  - The free operator frees the given pointer.
 * Or (if dup and free operators are both NULL):
 *  - The dup operator returns a copy of the specified pointer.
 *  - The free operator does nothing.
 *
 * This lets data structures correctly manage memory. In the first case
 * the entry is completely owned by the data structure. In the second, only
 * the pointer is owned by the data structure. Otherwise the data structure
 * owns nothing.
 */
typedef void * (*dup_fn_t)(const void *);
typedef void (*free_fn_t)(void *);

/*
 * A dup function to duplicate strings or NULL.
 */
static inline char *
string_dup(const char *p) { return p ? strdup(p) : NULL; }

/*
 * A free function to free strings or NULL.
 */
static inline void
string_free(char *p) { if (p) FREE(p); }

#endif /* _DATA_H */
