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

#include <delta.h>
#include <lines.h>

#define DEFAULT_LINES_CAPACITY 200

extern obstack_t blame_lines_obstack;

/*
 * Ensures <lines> can contain at least <c> entries.
 */
static void
_lines_expand(lines_t *lines, unsigned int c) {
	assert(lines);
	
	if (c <= lines->capacity)
		return;
	
	lines->capacity = c * 2;
	lines->lines = REALLOC(lines->lines, lines->capacity, line_t *);
}

/*
 * Returns a new line buffer.
 */
lines_t *
lines_new() {
	lines_t *lines = lines_new_with_capacity(DEFAULT_LINES_CAPACITY);
	
	return lines;
}

/*
 * Returns a new line buffer.
 */
lines_t *
lines_new_with_capacity(unsigned int capacity) {
	lines_t *lines;
	
	lines = MALLOC(1, lines_t);
	lines->capacity = capacity;
	lines->count = 0;
	lines->lines = MALLOC(capacity, line_t *);

	return lines;
}

/*
 * Returns a duplicate of <lines>.
 */
lines_t *
lines_dup(const lines_t *lines, unsigned int capacity) {
	lines_t *result;
	
	assert(lines);
	
	result = MALLOC(1, lines_t);
	result->capacity = capacity;
	result->count = lines->count;
	result->lines = MALLOC(capacity, line_t *);
	memcpy(result->lines, lines->lines, result->count * sizeof(line_t *));
	
	return result;
}

/*
 * Frees the line buffer <lines>.
 */
void
lines_free(lines_t *lines) {
	assert(lines && lines->lines);
	
	FREE(lines->lines);
	FREE(lines);
}

/*
 * Appends <text> (of length <len>) to <lines>. This should only be called on
 * line buffers created with lines_new (not lines_dup).
 */
void
lines_append_nocopy(lines_t *lines, const char *text, size_t len) {
	line_t *line;
	
	assert(lines);
	assert(text);
	
	line = OALLOC(&blame_lines_obstack, 1, line_t);
	line->delta = NULL; /* Need this? */
	line->text = text;
	line->len = len;
	_lines_expand(lines, lines_count(lines) + 1);
	lines->lines[lines->count++] = line;
}

/*
 * Applies the changes between <prev> and <delta> to <lines>, placing the
 * output in <out>. If we are on the trunk, <on_trunk> should be true. This
 * should only be called on line buffers created with lines_dup (not
 * lines_new).
 */
int
lines_apply(
	const lines_t *in, lines_t *out,
	const delta_t *prev, const delta_t *delta, int on_trunk
) {
	const lines_t *cmds;
	line_t * const *cmd, * const *last, * const *from;
	line_t **to;
	unsigned int from_line;
	
	assert(in);
	assert(out);
	assert(delta);
	assert(!on_trunk || prev); /* Otherwise we don't know who owned deleted lines */
	
	cmds = delta_get_text(delta);
	cmd = cmds->lines;
	last = cmd + lines_count(cmds);
	
	from = in->lines;
	from_line = 0;
	to = out->lines;
	
	while (cmd < last) {
		const char *x;
		
		if (!(*cmd)->len)
			break;
		
		x = (*cmd++)->text;
		switch (*x++) {
		case 'a':
			{
				unsigned int line, count;
				
				line = 0;
				while (*x >= '0' && *x <= '9') {
					line *= 10;
					line += (unsigned) (*x++ - '0');
				}
				x++;
				count = 0;
				while (*x >= '0' && *x <= '9') {
					count *= 10;
					count += (unsigned) (*x++ - '0');
				}
				
				memcpy(to, from + from_line, (line - from_line) * sizeof(line_t *));
				to += line - from_line;
				
				if (on_trunk) {
					memcpy(to, cmd, count * sizeof(line_t *));
					to += count;
					cmd += count;
				} else
					while (count--) {
						assert(!(*cmd)->delta);
						(*cmd)->delta = delta;
						*to++ = *cmd++;
					}
				from_line = line;
			}
			break;
		case 'd':
			{
				unsigned int line, count;
				
				line = 0;
				while (*x >= '0' && *x <= '9') {
					line *= 10;
					line += (unsigned) (*x++ - '0');
				}
				line--;
				x++;
				count = 0;
				while (*x >= '0' && *x <= '9') {
					count *= 10;
					count += (unsigned) (*x++ - '0');
				}
				
				memcpy(to, from + from_line, (line - from_line) * sizeof(line_t *));
				to += line - from_line;
				from_line = line + count;
				
				if (on_trunk) {
					line_t * const *temp = from + line;
					while (count--) {
						assert(!(*temp)->delta);
						(*temp++)->delta = prev;
					}
				}
			}
			break;
		default:
			return -1;
		}
	}
	memcpy(to, from + from_line, (lines_count(in) - from_line) * sizeof(line_t *));
	
	out->count = (unsigned) ((to - out->lines) + (lines_count(in) - from_line));
	return 0;
}

/*
 * Sets all unaccounted lines in <lines> to refer to <delta>. This should only
 * be called on line buffers created with lines_dup (not lines_new).
 */
void
lines_finalize(lines_t *lines, const delta_t *delta) {
	unsigned int i;
	
	assert(lines);
	assert(delta);
	
	for (i = lines_count(lines); i--; ) {
		line_t *line = lines_get(lines, i);
		if (!line->delta) line->delta = delta;
	}
}
