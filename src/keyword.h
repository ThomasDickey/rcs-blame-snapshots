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

#ifndef _KEYWORD_H
#define _KEYWORD_H

#include <system.h>

#include <delta.h>

struct rcs;

/*
 * Various types of keyword expansion. EXPAND_BINARY_STING is essentially
 * synonmyous with EXPAND_OLD_STRING since we're always writing on stdout.
 */
typedef enum {
	EXPAND_UNDEFINED,
	EXPAND_KEY_VALUE,
	EXPAND_KEY_VALUE_LOCKER,
	EXPAND_KEY_ONLY,
	EXPAND_OLD_STRING,
	EXPAND_BINARY_STRING,
	EXPAND_VALUE_ONLY
} expand_t;

char * keyword_extract_revision PARAMS((const char *, size_t));
void * keyword_expand PARAMS((
	const void *, size_t *, const delta_t *, const struct rcs *, expand_t,
	const char *, long
));

#endif /* _KEYWORD_H */
