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

#include <date.h>
#include <keyword.h>
#include <rcs.h>

extern unsigned int rcs_emulation;

/*
 * Returns a newly allocated string containing <s> unescaped.
 */
static char *
_keyword_unescape(const char *s) {
	const char *end, *escape;
	char *output;
	
	assert(s);
	
	end = s + strlen(s);
	output = SALLOC(end - s + 1);
	while ( (escape = strchr(s, '\\')) ) {
		strncat(output, s, escape - s);
		switch (escape[1]) {
		case 't':
			strcat(output, "\t");
			s = escape + 2;
			break;
		case 'n':
			strcat(output, "\n");
			s = escape + 2;
			break;
		case '\\':
			strcat(output, "\\");
			s = escape + 2;
			break;
		case '0':
			if (
				(escape + 3 < end) &&
				(escape[2] == '4') &&
				(escape[3] == '0')
			) {
				strcat(output, " ");
				s = escape + 4;
			} else if (
				(escape + 3 < end) &&
				(escape[2] == '4') &&
				(escape[3] == '4')
			) {
				strcat(output, "$");
				s = escape + 4;
			}
			break;
		}
	}
	strcat(output, s);
	
	return output;
}

/*
 * Returns a newly allocated string containing <s> escaped.
 */
static char *
_keyword_escape(const char *s) {
	const char *magic;
	char *output;
	size_t capacity, len;
	
	assert(s);
	
	capacity = strlen(s);
	output = SALLOC(capacity + 1);
	len = 0;
	
	while ( (magic = strpbrk(s, (rcs_emulation >= 5 ? "\t\n $\\" : "\t\n $"))) ) {
		len += magic - s;
		switch (*magic) {
		case '\t':
			len += 2;
			if (len > capacity) {
				capacity = len + 16;
				output = REALLOC(output, capacity + 1, char);
			}
			strncat(output, s, magic - s);
			strcat(output, "\\t");
			break;
		case '\n':
			len += 2;
			if (len > capacity) {
				capacity = len + 16;
				output = REALLOC(output, capacity + 1, char);
			}
			strncat(output, s, magic - s);
			strcat(output, "\\n");
			break;
		case ' ':
			len += 4;
			if (len > capacity) {
				capacity = len + 16;
				output = REALLOC(output, capacity + 1, char);
			}
			strncat(output, s, magic - s);
			strcat(output, "\\040");
			break;
		case '$':
			len += 4;
			if (len > capacity) {
				capacity = len + 16;
				output = REALLOC(output, capacity + 1, char);
			}
			strncat(output, s, magic - s);
			strcat(output, "\\044");
			break;
		case '\\':
			len += 2;
			if (len > capacity) {
				capacity = len + 16;
				output = REALLOC(output, capacity + 1, char);
			}
			strncat(output, s, magic - s);
			strcat(output, "\\\\");
			break;
		}
		s = magic + 1;
	}
	
	len += strlen(s);
	if (len > capacity) {
		capacity = len + 16;
		output = REALLOC(output, capacity + 1, char);
	}
	strcat(output, s);
	
	return output;
}

/*
 * Looks for a revision in <line> of length <len>. Returns a newly allocated
 * string, or NULL if no revision was found.
 */
char *
keyword_extract_revision(const char *line, size_t len) {
	const char *end, *dollar;
	char *buffer, *rev;
	
	assert(line);
	
	end = line + len;
	rev = NULL;
	buffer = ALLOCA(256, char);
	
	while (
		!rev && line && (dollar = (const char *)memchr(line, '$', end - line))
	) {
		if (sscanf(dollar, "$Id: %*s %255s %*s %*s %*s $", buffer) == 1)
			rev = _keyword_unescape(buffer);
		else if (sscanf(dollar, "$Id: %*s %255s %*s %*s %*s %*s $", buffer) == 1)
			rev = _keyword_unescape(buffer);
		else if (sscanf(dollar, "$Header: %*s %255s %*s %*s %*s $", buffer) == 1)
			rev = _keyword_unescape(buffer);
		else if (
			sscanf(dollar, "$Header: %*s %255s %*s %*s %*s %*s $", buffer) == 1
		)
			rev = _keyword_unescape(buffer);
		else if (sscanf(dollar, "$Revision: %255s $", buffer) == 1)
			rev = _keyword_unescape(buffer);
		else if (sscanf(dollar, "$Name: %255s $", buffer) == 1)
			rev = _keyword_unescape(buffer);
		dollar = (const char *)memchr(dollar + 1, '$', end - dollar - 1);
		if (dollar) dollar++;
		line = dollar;
	}
	
	return rev;
}

/*
 * Appends memory from <p>, for length <l> to <buffer> (with current capacity
 * *<capacity> and length *<len>). Returns <buffer>, or a reallocated buffer
 * if its capacity had to be increased (in which case *<capacity> will be
 * updated). *<len> is increased by <l>.
 */
static inline void *
_keyword_append_mem(
	void *buffer, size_t *capacity, size_t *len, const void *p, size_t l
) {
	void *x;
	void *at;
	
	assert(buffer);
	assert(capacity);
	assert(len);
	assert(p);
	
	if (*len + l > *capacity) {
		*capacity = *len + l + 32;
		buffer = REALLOC(buffer, *capacity, void *);
	}
	x = VOIDP_OFFSET(buffer, *len);
	while ( (at = memchr(p, '@', l)) && *(char *)VOIDP_OFFSET(at, 1) == '@') {
		memcpy(x, p, VOIDP_DIFF(at, p) + 1);
		x = VOIDP_OFFSET(x, at - p + 1);
		*len += VOIDP_DIFF(at, p) + 1;
		l -= VOIDP_DIFF(at, p) + 2;
		p = VOIDP_OFFSET(at, 2);
	}
	memcpy(x, p, l);
	*len += l;
	
	return buffer;
}

/*
 * Appends the string <s> to <buffer> (with current capacity *<capacity> and
 * length <len>). Returns <buffer>, or a reallocated buffer if its capacity had
 * to be increased (in which case *<capacity> will be updated). *<len> is
 * increased by the length of <s>.
 */
static inline void *
_keyword_append(void *buffer, size_t *capacity, size_t *len, const char *s) {
	return _keyword_append_mem(buffer, capacity, len, s, strlen(s));
}

/*
 * If <expand> is EXPAND_OLD_STRING or EXPAND_BINARY_STRING, returns a duplicate
 * of <line>.
 *
 * Otherwise a newly allocated buffer is returned. *<len> is set to the length
 * of the buffer. The buffer consists of <line> (of length *<len>) expanded
 * according to the value of <expand>.
 */
void *
keyword_expand(
	const void *line, size_t *len, const delta_t *delta, const rcs_t *rcs,
	expand_t expand, const char *symbol, long zone_offset
) {
	const void *end, *d1, *d2, *log_start, *log_end;
	void *output;
	char *t;
	const char *tt, *log, *n;
	size_t capacity;
	int local_log_prefix;
	
	assert(line);
	assert(len);
	assert(delta);
	assert(rcs);
	
	if (expand == EXPAND_OLD_STRING || expand == EXPAND_BINARY_STRING) {
		output = MALLOC_VOIDP(*len);
		memcpy(output, line, *len);
		return output;
	}
	
	end = VOIDP_OFFSET(line, *len);
	if (rcs_emulation >= 5) {
		log_start = line;
		log_end = NULL;
	} else {
		log_start = rcs_get_comment(rcs);
		log_end = VOIDP_OFFSET(log_start, strlen((char *)log_start));
	}
	
	capacity = *len;
	output = MALLOC_VOIDP(capacity);
	*len = 0;
	
	while ( (line < end) && (d1 = memchr(line, '$', VOIDP_DIFF(end, line))) ) {
		d2 = memchr(VOIDP_OFFSET(d1, 1), '$', VOIDP_DIFF(end, d1) - 1);
		if (!d2)
			break;
		
		output = _keyword_append_mem(
			output, &capacity, len, line, VOIDP_DIFF(d1, line)
		);
		
		if (!memcmp(d1, "$Author", 7)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Author");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY)
				output = _keyword_append(output, &capacity, len,
					delta_get_author(delta));
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$Date", 5)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Date");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY) {
				t = date_sprintf(delta_get_date(delta), zone_offset);
				output = _keyword_append(output, &capacity, len, t);
				FREE(t);
			}
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$Header", 7) || !memcmp(d1, "$Id", 3)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(
					output, &capacity, len,
					(*(char *)VOIDP_OFFSET(d1, 1) == 'H' ? "$Header" : "$Id")
				);
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY) {
				t = _keyword_escape(
					(*(char *)VOIDP_OFFSET(d1, 1) == 'H') && (rcs_emulation >= 4)
					? rcs_get_full_filename(rcs)
					: rcs_get_short_filename(rcs)
				);
				output = _keyword_append(output, &capacity, len, t);
				FREE(t);
				output = _keyword_append(output, &capacity, len, " ");
				output = _keyword_append(output, &capacity, len,
					delta_get_revision(delta));
				output = _keyword_append(output, &capacity, len, " ");
				t = date_sprintf(delta_get_date(delta), zone_offset);
				output = _keyword_append(output, &capacity, len, t);
				FREE(t);
				output = _keyword_append(output, &capacity, len, " ");
				output = _keyword_append(output, &capacity, len,
					delta_get_author(delta));
				output = _keyword_append(output, &capacity, len, " ");
				switch (rcs_emulation) {
				case 3:
					if (rcs_get_locker(rcs, delta_get_revision(delta)))
						output = _keyword_append(output, &capacity, len, "Locked");
					break;
				case 4:
					output = _keyword_append(output, &capacity, len,
						delta_get_state(delta));
					if ( (tt = rcs_get_locker(rcs, delta_get_revision(delta))) ) {
						output = _keyword_append(output, &capacity, len, " Locker: ");
						output = _keyword_append(output, &capacity, len, tt);
					}
					break;
				default:
					output = _keyword_append(output, &capacity, len,
						delta_get_state(delta));
					if (
						expand == EXPAND_KEY_VALUE_LOCKER &&
						(tt = rcs_get_locker(rcs, delta_get_revision(delta)))
					) {
						output = _keyword_append(output, &capacity, len, " ");
						output = _keyword_append(output, &capacity, len, tt);
					}
					break;
				}
			}
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$Locker", 7)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Locker");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (rcs_emulation <= 4 || expand == EXPAND_KEY_VALUE_LOCKER) {
				tt = rcs_get_locker(rcs, delta_get_revision(delta));
				if (tt)
					output = _keyword_append(output, &capacity, len, tt);
			}
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$Log", 4)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Log");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(
					output, &capacity, len, (rcs_emulation >= 5 ? ": " : ":\t")
				);
			if (expand != EXPAND_KEY_ONLY) {
				t = _keyword_escape(rcs_get_short_filename(rcs));
				output = _keyword_append(output, &capacity, len, t);
				FREE(t);
			}
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
			/* Strangely, rcs outputs the log even with if -kk is specified... */
			
			local_log_prefix = 0;
			if (rcs_emulation >= 5) {
				const void *t2;
				log_end = d1;
				for (t2 = log_start; t2 < log_end; t2 = VOIDP_OFFSET(t2, 1))
					if (!ISSPACE(*(char *)t2))
						break;
				if (
					t2 < log_end - 2 &&
					(*(char *)t2 == '/' || *(char *)t2 == '(') && 
					*(char *)VOIDP_OFFSET(t2, 1) == '*'
				) {
					void *t3;
					local_log_prefix = 1;
					t3 = MALLOC(log_end - log_start, char);
					memcpy(t3, log_start, log_end - log_start);
					*(char *)VOIDP_OFFSET(t3, t2 - log_start) = ' ';
					log_end = VOIDP_OFFSET(t3, log_end - log_start);
					log_start = t3;
				}
			}
			
			output = _keyword_append(output, &capacity, len, "\n");
			output = _keyword_append_mem(
				output, &capacity, len, log_start, VOIDP_DIFF(log_end, log_start)
			);
			output = _keyword_append(output, &capacity, len, "Revision ");
			output = _keyword_append(output, &capacity, len,
				delta_get_revision(delta));
			output = _keyword_append(output, &capacity, len, "  ");
			t = date_sprintf(delta_get_date(delta), zone_offset);
			if (rcs_emulation >= 5) {
				output = _keyword_append(output, &capacity, len, t);
			} else {
				char *t2 = strchrnul(t, ' ');
				if (*t2) *t2++ = '\0';
				output = _keyword_append(output, &capacity, len, t);
				output = _keyword_append(output, &capacity, len, "  ");
				output = _keyword_append(output, &capacity, len, t2);
			}
			FREE(t);
			output = _keyword_append(output, &capacity, len, "  ");
			output = _keyword_append(output, &capacity, len,
				delta_get_author(delta));
			output = _keyword_append(output, &capacity, len, "\n");
			log = delta_get_log(delta);
			while ( (n = strchr(log, '\n')) ) {
				output = _keyword_append_mem(
					output, &capacity, len, log_start, VOIDP_DIFF(log_end, log_start)
				);
				output = _keyword_append_mem(output, &capacity, len, log, n - log + 1);
				log = n + 1;
			}
			output = _keyword_append_mem(
				output, &capacity, len, log_start, VOIDP_DIFF(log_end, log_start)
			);
			output = _keyword_append(output, &capacity, len, log);
			if (rcs_emulation >= 5) {
				if (local_log_prefix) {
					void *alias = (void *)log_start;
					FREE(alias);
				}
				line = d2;
				do {
					line = VOIDP_OFFSET(line, 1);
				} while (
					*(char *)line && ISSPACE(*(char *)line) && *(char *)line != '\n'
				);
				continue;
			}
		} else if (!memcmp(d1, "$Name", 5)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Name");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY && symbol)
				output = _keyword_append(output, &capacity, len, symbol);
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$RCSfile", 8)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$RCSfile");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY) {
				t = _keyword_escape(rcs_get_short_filename(rcs));
				output = _keyword_append(output, &capacity, len, t);
				FREE(t);
			}
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$Revision", 9)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Revision");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY)
				output = _keyword_append(output, &capacity, len,
					delta_get_revision(delta));
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$Source", 7)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$Source");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY) {
				t = _keyword_escape(rcs_get_full_filename(rcs));
				output = _keyword_append(output, &capacity, len, t);
				FREE(t);
			}
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else if (!memcmp(d1, "$State", 6)) {
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$State");
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, ": ");
			if (expand != EXPAND_KEY_ONLY)
				output = _keyword_append(output, &capacity, len,
					delta_get_state(delta));
			if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, " ");
			if (expand != EXPAND_VALUE_ONLY)
				output = _keyword_append(output, &capacity, len, "$");
		} else {
			output = _keyword_append(output, &capacity, len, "$");
			line = VOIDP_OFFSET(d1, 1);
			continue;
		}
		line = VOIDP_OFFSET(d2, 1);
	}
	output = _keyword_append_mem(
		output, &capacity, len, line, VOIDP_DIFF(end, line)
	);
		
	return output;
}
