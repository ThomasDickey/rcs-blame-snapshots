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

#ifndef _DATE_H
#define _DATE_H

#include <system.h>

#define TM_UNDEFINED_ZONE ((long) -24 * 60 * 60)
#define TM_LOCAL_ZONE (TM_UNDEFINED_ZONE - 1)

const char * date_parse_zone PARAMS((const char *, long *));
time_t date_parse PARAMS((const char *, int, long));
time_t date_parse_rev PARAMS((const char *));

char * date_format PARAMS((time_t));
char * date_sprintf PARAMS((time_t, long));
char * date_sprintf_prefix PARAMS((time_t));

#endif /* _DATE_H */
