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

#ifndef _LINES_H
#define _LINES_H

#include <system.h>

/*
 * A line in a line buffer.
 */
typedef struct {
	const struct _delta_t *delta; /* The delta that owns this line. */
	const char *text;     /* The text on this line.         */
	size_t len;           /* The length of the line.        */
} line_t;

/*
 * A line buffer is a vector. The standard vector_t type isn't used
 * since we don't need (or want) any fancy memory management business.
 */
typedef struct {
	unsigned int capacity;
	unsigned int count;
	
	line_t **lines; /* The line pointers in the buffer.     */
} lines_t;

lines_t * lines_new PARAMS((void));
lines_t * lines_new_with_capacity PARAMS((unsigned int));
lines_t * lines_dup PARAMS((const lines_t *, unsigned int));
void lines_free PARAMS((lines_t *));

void lines_append_nocopy PARAMS((lines_t *, const char *, size_t));

int lines_apply PARAMS((const lines_t *, lines_t *, const struct _delta_t *, const struct _delta_t *, int));
void lines_finalize PARAMS((lines_t *, const struct _delta_t *));

#define lines_count(L) ((L)->count)
#define lines_get(L, X) ((line_t *)((L)->lines[X]))

#endif /* _LINES_H */
