/*
 * Blame - An RCS file annotator
 * Copyright (C) 2004, 2005  Michael Chapman
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
	output = SALLOC(end - s);
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
	output = SALLOC(capacity);
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
 * Outputs <data>, of length <len>, to stdout, replacing each occurence of
 * @@ with @.
 */
static inline void
_keyword_shrink_output(const void *data, size_t len) {
	assert(data);
	
	while (len) {
		char *at = memchr(data, '@', len);
		if (!at) break;
		fwrite(data, VOIDP_DIFF(at, data) + 1, 1, stdout);
		if (*(char *)VOIDP_OFFSET(at, 1) == '@') {
			len -= VOIDP_DIFF(at, data) + 2;
			data = VOIDP_OFFSET(at, 2);
		} else {
			len -= VOIDP_DIFF(at, data) + 1;
			data = VOIDP_OFFSET(at, 1);
		}
	}
	if (len) fwrite(data, len, 1, stdout);
}

/*
 * Annotates <line> and outputs it to stdout.
 */
void
keyword_annotate(
	const line_t *line, const struct rcs *rcs, expand_t expand,
	const char *symbol, long zone_offset
) {
	const void *current, *end, *log_start, *log_end;
	size_t len;
	char prefix[36];
	int do_prefix;
	
	assert(line);
	assert(rcs);
	
	sprintf(prefix, "%-12s (%-8.8s ",
		delta_get_revision(line->delta),
		delta_get_author(line->delta)
	);
	date_sprintf_prefix(delta_get_date(line->delta), prefix + 23, 10);
	strcat(prefix, "): ");
	
	current = line->text;
	len = line->len;
	end = VOIDP_OFFSET(current, len);
	do_prefix = 1;
	
	if (rcs_emulation >= 5) {
		log_start = current;
		log_end = NULL;
	} else {
		log_start = rcs_get_comment(rcs);
		log_end = VOIDP_OFFSET(log_start, strlen((char *)log_start));
	}
	
	while (current < end) {
		size_t chunk_len;
		const void *delim, *delim2, *next;
		
		if (do_prefix) {
			fputs(prefix, stdout);
			do_prefix = 0;
		}
		
		chunk_len = strcspn(current, (
			expand == EXPAND_OLD_STRING || expand == EXPAND_BINARY_STRING
			? "@\n"
			: "$@\n"
		));
		delim = VOIDP_OFFSET(current, chunk_len);
		switch (*(char *)delim) {
		case '$':
			fwrite(current, chunk_len, 1, stdout);
			delim2 = memchr(VOIDP_OFFSET(delim, 1), '$', VOIDP_DIFF(end, delim) - 1);
			if (!delim2) {
				putchar('$');
				current = VOIDP_OFFSET(delim, 1);
				break;
			}
			
			if (!memcmp(delim, "$Author", 7)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Author", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY)
					fputs(delta_get_author(line->delta), stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$Date", 5)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Date", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY) {
					char *t = date_sprintf(delta_get_date(line->delta), zone_offset);
					fputs(t, stdout);
					FREE(t);
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$Header", 7) || !memcmp(delim, "$Id", 3)) {
				if (expand != EXPAND_VALUE_ONLY) {
					if (*(char *)VOIDP_OFFSET(delim, 1) == 'H')
						fputs("$Header", stdout);
					else
						fputs("$Id", stdout);
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY) {
					char *t1 = _keyword_escape(
						(*(char *)VOIDP_OFFSET(delim, 1) == 'H') && (rcs_emulation >= 4)
						? rcs_get_full_filename(rcs)
						: rcs_get_short_filename(rcs)
					);
					char *t2 = date_sprintf(delta_get_date(line->delta), zone_offset);
					const char *t3;
					printf(
						"%s %s %s %s ",
						t1, delta_get_revision(line->delta), t2, delta_get_author(line->delta)
					);
					FREE(t1);
					FREE(t2);
					switch (rcs_emulation) {
					case 3:
						if (rcs_get_locker(rcs, delta_get_revision(line->delta)))
							fputs("Locked", stdout);
						break;
					case 4:
						fputs(delta_get_state(line->delta), stdout);
						if ( (t3 = rcs_get_locker(rcs, delta_get_revision(line->delta))) )
							printf(" Locker: %s", t3);
						break;
					default:
						fputs(delta_get_state(line->delta), stdout);
						if (
							expand == EXPAND_KEY_VALUE_LOCKER &&
							(t3 = rcs_get_locker(rcs, delta_get_revision(line->delta)))
						)
							printf(" %s", t3);
						break;
					}
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$Locker", 7)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Locker", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (rcs_emulation <= 4 || expand == EXPAND_KEY_VALUE_LOCKER) {
					const char *t = rcs_get_locker(rcs, delta_get_revision(line->delta));
					if (t) fputs(t, stdout);
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$Log", 4)) {
				char *t;
				const char *log, *n;
				int local_log_prefix = 0;
			
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Log", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY) {
					if (rcs_emulation >= 5)
						fputs(": ", stdout);
					else
						fputs(":\t", stdout);
				}
				if (expand != EXPAND_KEY_ONLY) {
					t = _keyword_escape(rcs_get_short_filename(rcs));
					fputs(t, stdout);
					FREE(t);
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
				/* Strangely, rcs outputs the log even with if -kk is specified... */

				if (rcs_emulation >= 5) {
					const void *t2;
					log_end = delim;
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

				printf("\n%s", prefix);
				_keyword_shrink_output(log_start, VOIDP_DIFF(log_end, log_start));
				printf("Revision %s  ", delta_get_revision(line->delta));
				t = date_sprintf(delta_get_date(line->delta), zone_offset);
				if (rcs_emulation >= 5) {
					fputs(t, stdout);
				} else {
					char *t2 = strchrnul(t, ' ');
					if (*t2) *t2++ = '\0';
					printf("%s  %s", t, t2);
				}
				FREE(t);
				printf("  %s\n%s", delta_get_author(line->delta), prefix);
				log = delta_get_log(line->delta);
				while ( (n = strchr(log, '\n')) ) {
					_keyword_shrink_output(log_start, VOIDP_DIFF(log_end, log_start));
					_keyword_shrink_output(log, n - log + 1);
					fputs(prefix, stdout);
					log = n + 1;
				}
				_keyword_shrink_output(log_start, VOIDP_DIFF(log_end, log_start));
				fputs(log, stdout);
				if (rcs_emulation >= 5) {
					if (local_log_prefix) {
						void *alias = (void *)log_start;
						FREE(alias);
					}
					current = delim2;
					do {
						current = VOIDP_OFFSET(current, 1);
					} while (
						*(char *)current && ISSPACE(*(char *)current) && *(char *)current != '\n'
					);
					continue;
				}
			} else if (!memcmp(delim, "$Name", 5)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Name", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY && symbol)
					fputs(symbol, stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$RCSfile", 8)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$RCSfile", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY) {
					char *t = _keyword_escape(rcs_get_short_filename(rcs));
					fputs(t, stdout);
					FREE(t);
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$Revision", 9)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Revision", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY)
					fputs(delta_get_revision(line->delta), stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$Source", 7)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$Source", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY) {
					char *t = _keyword_escape(rcs_get_full_filename(rcs));
					fputs(t, stdout);
					FREE(t);
				}
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else if (!memcmp(delim, "$State", 6)) {
				if (expand != EXPAND_VALUE_ONLY)
					fputs("$State", stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					fputs(": ", stdout);
				if (expand != EXPAND_KEY_ONLY)
					fputs(delta_get_state(line->delta), stdout);
				if (expand != EXPAND_KEY_ONLY && expand != EXPAND_VALUE_ONLY)
					putchar(' ');
				if (expand != EXPAND_VALUE_ONLY)
					putchar('$');
			} else {
				putchar('$');
				delim2 = delim;
			}
			
			current = VOIDP_OFFSET(delim2, 1);
			break;
		case '@':
			if (delim >= end) {
				fwrite(current, chunk_len, 1, stdout);
				return;
			}
			next = VOIDP_OFFSET(delim, 1);
			fwrite(current, VOIDP_DIFF(next, current), 1, stdout);
			current = (*(char *)next == '@' ? VOIDP_OFFSET(next, 1) : next);
			break;
		case '\n':
			fwrite(current, chunk_len + 1, 1, stdout);
			current = VOIDP_OFFSET(delim, 1);
			do_prefix = 1;
			break;
		case '\0':
			fwrite(current, chunk_len + 1, 1, stdout);
			current = VOIDP_OFFSET(delim, 1);
			break;
		}
	}
}
