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

#include <getline.h>

#include <delta.h>
#include <keyword.h>
#include <working.h>

/*
 * Extracts and returns a revision number out of the working file <filename>.
 * Returns NULL on error or if no revision was found. On an error, an error
 * message is printed.
 */
char *
working_extract_revision(const char *filename) {
	FILE *stream;
	char *rev, *line;
	size_t len;
	ssize_t read;
	
	assert(filename);
	
	stream = fopen(filename, "r");
	if (!stream) {
		error(0, errno, "%s", filename);
		return NULL;
	}
	
	rev = NULL;
	
	line = NULL;
	len = 0;
	while ( (read = getline(&line, &len, stream)) != -1)
		if ( (rev = keyword_extract_revision(line, (size_t) read)) )
			break;
	if (line)
		FREE(line);
	
	if (!rev)
		error(0, 0, "%s: no revision found", filename);
	
	if (fclose(stream))
		error(0, errno, "%s", filename);
	
	return rev;
}
