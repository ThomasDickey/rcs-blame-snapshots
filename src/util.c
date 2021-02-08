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

#include <dirname.h>

#include <util.h>

/*
 * Returns true iff <working_filename> and <rcs_filename> constitute a valid
 * working file/RCS file pair.
 */
int
does_working_filename_match_rcs_filename(
	const char *working_filename, const char *rcs_filename
) {
	const char *from, *to;
	char *a, *b;
	size_t al, bl;
	int result;
	
	assert(working_filename && rcs_filename);
	
	a = base_name(working_filename);
	al = base_len(a);
	b = base_name(rcs_filename);
	bl = base_len(b);
	
	result = 1;
	
	from = (suffixes ? suffixes : SUFFIXES);
	while (1) {
		to = strchrnul(from, DIRECTORY_SEPARATOR);
		if (al + (to - from) == bl &&
			!strncmp(a, b, al) &&
			!strncmp(from, b + bl - (to - from), to - from)) goto out;
		if (!*to)
			break;
		from = to + 1;
	}
	
	result = 0;
	
out:
	
	FREE(a);
	FREE(b);
	
	return result;
}

/*
 * Returns true iff <filename> is a valid RCS filename.
 */
int
is_rcs_filename(const char *filename) {
	const char *from, *to;
	
	assert(filename);
	
	from = (suffixes ? suffixes : SUFFIXES);
	while (1) {
		to = strchrnul(from, DIRECTORY_SEPARATOR);
		if (from == to) {
			if (!strncmp(filename, "RCS" SSLASH, 4)) return 1;
			if (strstr(filename, SSLASH "RCS" SSLASH)) return 1;
		} else {
			if (!strncmp(from, filename + strlen(filename) - (to - from), to - from))
				return 1;
		}
		if (!*to)
			break;
		from = to + 1;
	}
	
	return 0;
}

/*
 * Returns the RCS filename that best matches <working_filename>, or NULL if
 * it could not be found. This function will print any error messages.
 */
char *
find_matching_rcs_filename(const char *working_filename) {
	const char *from, *to, *a;
	char *first;
	int first_error;
	
	assert(working_filename);
	
	a = last_component(working_filename);
	
	first = NULL; first_error = 0;
	from = (suffixes ? suffixes : SUFFIXES);
	while (1) {
		char *buffer;
		size_t length;
		
		to = strchrnul(from, DIRECTORY_SEPARATOR);
		
		length = strlen(working_filename) + (to - from) + 4;
		
		buffer = SALLOC(length);
		strncat(buffer, working_filename, (a - working_filename));
		strcat(buffer, "RCS" SSLASH);
		strncat(buffer, a, base_len(a));
		strncat(buffer, from, to - from);
		
		if (!access(buffer, F_OK)) {
			if (first) FREE(first);
			return buffer;
		}
		
		if (!first) {
			first_error = errno;
			first = strdup(buffer);
		}
		
		if (from != to) {
			memset(buffer, '\0', length);
			strncpy(buffer, working_filename, (a - working_filename));
			strncat(buffer, a, base_len(a));
			strncat(buffer, from, to - from);

			if (!access(buffer, F_OK)) {
				if (first) FREE(first);
				return buffer;
			}
		}
		
		FREE(buffer);
		
		if (!*to)
			break;
		from = to + 1;
	}
	
	assert(first);
	assert(first_error);
	error(0, first_error, "%s", first);
	FREE(first);
	
	return NULL;
}

/*
 * Returns the working filename that best matches <rcs_filename>, or NULL if
 * it could not be determined.
 */
char *
find_matching_working_filename(const char *rcs_filename) {
	const char *from, *to;
	char *a;
	size_t al;
	
	assert(rcs_filename);
	
	a = base_name(rcs_filename);
	al = base_len(a);
	
	from = (suffixes ? suffixes : SUFFIXES);
	while (1) {
		to = strchrnul(from, DIRECTORY_SEPARATOR);
		if (!strncmp(from, a + al - (to - from), to - from)) {
			char *result = strndup(a, al - (to - from));
			FREE(a);
			return result;
		}
		if (!*to)
			break;
		from = to + 1;
	}
	
	FREE(a);
	
	return NULL;
}
