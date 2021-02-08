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

#include <argp.h>
#if HAVE_LOCALE_H
# include <locale.h>
#endif /* HAVE_LOCALE_H */
#include <obstack.h>
#include <progname.h>
#include <pwd.h>

#include <date.h>
#include <keyword.h>
#include <lines.h>
#include <rcs.h>
#include <util.h>
#include <vector.h>
#include <working.h>

/*
 * Program name for errors.
 */
extern const char *program_name;

/*
 * Package name/bug address for argp
 */
const char *argp_program_version = PACKAGE_STRING "; emulating RCS version 5";
const char *argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

/*
 * A slash-separated list of RCS suffixes.
 * If NULL, the macro SUFFIXES will be used instead.
 */
char *suffixes;

/*
 * The version of RCS to emulate.
 */
unsigned int rcs_emulation;

/*
 * A global obstack for lines read in from RCS files.
 */
obstack_t blame_lines_obstack;

/*
 * The time zone to use for date parsing and printing.
 * If NULL, use localtime.
 */
static char *zone;

static vector_t *filenames;
                         /* Non-option arguments     */

static char *tag_arg;    /* Argument to -r, --rev    */
static char *date_arg;   /* Argument to -d, --date   */
static char *author_arg; /* Argument to -w, --author */
static char *state_arg;  /* Argument to -s, --state  */

static expand_t expand;  /* Argument to -k, --expand */
static char *symbol;     /* Argument to -r, --rev
                            (only if it was a single symbol) */

static time_t date;      /* Parsed value of date_arg */
static long zone_offset; /* Parsed value of zone     */

static int failures;     /* True iff a failure occurred */

static int parsing_rcsinit;
                         /* True iff argument parsing is not strict */

/*
 * Whether we should free everything at the end.
 */
static int cleanup;

/*
 * Annotate revision <rev> of <rcs> (with working filename <filename>).
 * Returns -1 on error, 0 otherwise.
 */
static int
annotate_revision(const char *filename, const rcs_t *rcs, const char *rev) {
	char *copy, *dot;
	size_t length, total_length;
	const delta_t *delta, *save, *target;
	lines_t *lines, *spare, *dup;
	unsigned int i;
	expand_t rcs_expand;
	int result;
	
	result = -1;
	
	assert(rcs);
	assert(rev && rcs_rev_is_valid(rev));
	
	rcs_expand = expand;
	if (rcs_expand == EXPAND_UNDEFINED)
		rcs_expand = rcs_get_expand(rcs);
	if (rcs_expand == EXPAND_UNDEFINED)
		rcs_expand = EXPAND_KEY_VALUE;
	
	/*
	 * Print the banner immediately after parsing the RCS file.
	 * TODO: Add a -q, --quiet option?
	 */
	fprintf(stderr, "\nAnnotations for %s\n***************\n", filename);
	
	total_length = strlen(rev);
	copy = strdup(rev);
	
	/*
	 * Find the second dot (or end-of-string). All deltas with a single dot
	 * are on the trunk.
	 */
	dot = strchr(copy, '.');
	assert(dot); /* since rcs_rev_is_valid(rev) */
	dot = strchrnul(dot + 1, '.');
	*dot = '\0';
	length = dot - copy;
	
	/*
	 * Start from the head revision.
	 */
	delta = rcs_get_head(rcs);
	
	lines = lines_dup(delta->text, rcs->lines);
	spare = lines_new_with_capacity(rcs->lines);
	
	target = rcs_get_delta(rcs, copy);
	while (delta != target) {
		lines_t *temp;
		const delta_t *next = delta_get_next(delta);
		assert(next); /* since rev exists and is reachable */
		
		if (lines_apply(lines, spare, delta, next, 1)) {
			error(
				0, 0, "%s: could not apply diff between revisions %s and %s",
				rcs_get_filename(rcs), delta_get_revision(delta),
				delta_get_revision(next)
			);
			goto fail;
		}
		temp = lines;
		lines = spare;
		spare = temp;
		
		delta = next;
	}
	
	/*
	 * We've found the branch point. Duplicate the line buffer, and continue
	 * on the trunk until we hit the end. This will update the original line
	 * buffer with ownership info for each line.
	 */
	dup = lines_dup(lines, rcs->lines);
	save = delta;
	
	while (delta) {
		const delta_t *next = delta_get_next(delta);
		
		if (next) {
			lines_t *temp;
			
			if (lines_apply(dup, spare, delta, next, 1)) {
				error(
					0, 0, "%s: could not apply diff between revisions %s and %s",
					rcs_get_filename(rcs), delta_get_revision(delta),
					delta_get_revision(next)
				);
				lines_free(dup);
				goto fail;
			}
			temp = dup;
			dup = spare;
			spare = temp;
		} else
			lines_finalize(dup, delta);
		
		delta = next;
	}
	
	lines_free(dup);
	delta = save;
	
	/*
	 * Back to the branch point.
	 */
	while (length != total_length) {
		lines_t *temp;
		const delta_t *next;
		
		*dot = '.';
		dot = strchr(dot + 1, '.');
		assert(dot); /* since rcs_rev_is_valid(rev) */
		
		/*
		 * Look up the branch.
		 */
		*dot = '\0';
		next = delta_get_branch(delta, copy);
		assert(next); /* since rev exists and is reachable */
		
		if (lines_apply(lines, spare, delta, next, 0)) {
			error(
				0, 0, "%s: could not apply diff between revisions %s and %s",
				rcs_get_filename(rcs), delta_get_revision(delta),
				delta_get_revision(next)
			);
			goto fail;
		}
		temp = lines;
		lines = spare;
		spare = temp;
		
		delta = next;
		
		*dot = '.';
		dot = strchrnul(dot + 1, '.');
		*dot = '\0';
		length = dot - copy;
		
		/*
		 * Continue along this branch until we find the correct revision or another
		 * branch point.
		 */
		target = rcs_get_delta(rcs, copy);
		while (delta != target) {
			next = delta_get_next(delta);
			
			if (lines_apply(lines, spare, delta, next, 0)) {
				error(
					0, 0, "%s: could not apply diff between revisions %s and %s",
					rcs_get_filename(rcs), delta_get_revision(delta),
					delta_get_revision(next)
				);
				goto fail;
			}
			temp = lines;
			lines = spare;
			spare = temp;
			
			delta = next;
		}
	}
	
	/*
	 * OK, should have ownership info for each line in the selected revision.
	 * For each line, we print out the owner's revision, author and date,
	 * followed by an expanded version of the line.
	 */
	for (i = 0; i < lines_count(lines); i++) {
		const line_t *line = lines_get(lines, i);
		
		/*
		 * If the final line is empty, don't print anything.
		 */
		if ((i + 1 == lines_count(lines)) && !line->len)
			break;
		
		keyword_annotate(line, rcs, rcs_expand, symbol, zone_offset);
	}
	
	result = 0;
	
fail:
	if (cleanup) {
		lines_free(lines);
		lines_free(spare);
		FREE(copy);
	}
	
	return result;
}

/*
 * Annotate <working_filename>/<rcs_filename> (one of which must be specified).
 * Returns -1 on error, 0 otherwise.
 */
static int
annotate(const char *working_filename, const char *rcs_filename) {
	rcs_t *rcs;
	char *working_filename2, *rcs_filename2;
	char *tag, *rev;
	int result;
	
	OINIT(&blame_lines_obstack);
	
	result = -1;
	
	assert(working_filename || rcs_filename);
	
	rcs = NULL;
	working_filename2 = rcs_filename2 = NULL;
	tag = rev = NULL;
	
	/*
	 * Resolve a missing working_filename or rcs_filename.
	 */
	
	if (!rcs_filename)
		rcs_filename2 = find_matching_rcs_filename(working_filename);
	else
		rcs_filename2 = strdup(rcs_filename);
	if (!rcs_filename2)
		goto fail;
	
	if (!working_filename)
		working_filename2 = find_matching_working_filename(rcs_filename);
	else
		working_filename2 = strdup(working_filename);
	
	assert(is_rcs_filename(rcs_filename2));
	assert(!is_rcs_filename(working_filename2));
	
	/*
	 * If a tag is specified, extract it from the working file if it is "$".
	 * The value in the working file can have symbols in it, but it can't
	 * contain "..".
	 */
	tag = NULL;
	if (tag_arg) {
		if (!strcmp(tag_arg, "$")) {
			tag = working_extract_revision(working_filename2);
			if (!tag)
				goto fail;
			if (!rcs_rev_is_valid(tag)) {
				error(0, 0, "%s: %s is not a revision number", working_filename2, tag);
				goto fail;
			}
		} else
			tag = strdup(tag_arg);
	}
	
	/*
	 * Read in the RCS file. If this succeeds, the delta tree is guaranteed to
	 * be valid (no loops, all deltas reachable, branches on appropriate
	 * deltas, etc.).
	 */
	rcs = rcs_parse(rcs_filename2);
	if (!rcs)
		goto fail;
	
	/*
	 * If there's no head revision, the RCS file is empty (created with
	 * "rcs -i"). No point in going any further.
	 */
	if (!rcs_get_head(rcs)) {
		error(0, 0, "%s: no revisions present", working_filename2);
		goto fail;
	}
	
	/*
	 * Try to resolve the specified tag.
	 */
	rev = rcs_resolve_tag(rcs, tag, date, zone_offset, author_arg, state_arg);
	if (!rev)
		goto fail;
	
	/*
	 * Save the tag if it was a single symbol. We need this in case we expand
	 * any Symbol keywords.
	 */
	if (tag && rcs_get_symbol(rcs, tag))
		symbol = tag;
	else
		symbol = NULL;
	
	/*
	 * We know the numerical revision we want, and we know it's somewhere in
	 * delta tree. Annotate it.
	 */
	result = annotate_revision(working_filename2, rcs, rev);
	
fail:
	if (cleanup) {
		if (rcs) rcs_free(rcs);
		if (working_filename2) FREE(working_filename2);
		if (rcs_filename2) FREE(rcs_filename2);
		if (tag) FREE(tag);
		if (rev) FREE(rev);
		OFREEALL(&blame_lines_obstack);
	}
	
	return result;
}

/*
 * Parse command line option <key>, with argument <arg>. Current parser state
 * is in <state>.
 */
static error_t
parse_options(int key, char *arg, struct argp_state *state) {
	static const char *working_filename;
	static const char *rcs_filename;
	
	switch (key) {
	case '?':
		argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
		break;
	case 0x80:
		argp_state_help(state, state->out_stream, ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK);
		break;
	case 'V':
		if (arg) {
			switch (*arg) {
			case '3': case '4': case '5':
				if (!*(arg + 1)) {
					rcs_emulation = *arg - '0';
					break;
				}
				/* FALLTHRU */
			default:
				argp_failure(
					state, EXIT_FAILURE, 0,
					"invalid RCS emulation version %s", arg
				);
				assert(parsing_rcsinit);
				break;
			}
		} else {
			fprintf(state->out_stream, "%s\n", argp_program_version);
			if (!(state->flags & ARGP_NO_EXIT))
				exit(EXIT_SUCCESS);
		}
		break;
	case 'r': /* --rev */
		if (tag_arg) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple revision options may not be specified"
			);
			assert(parsing_rcsinit);
			FREE(tag_arg);
		}
		tag_arg = (arg ? strdup(arg) : strdup(""));
		break;
	case 'd': /* --date */
		assert(arg); /* argument is mandatory */
		if (date_arg) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple date options may not be specified"
			);
			assert(parsing_rcsinit);
			FREE(date_arg);
		}
		date_arg = strdup(arg);
		break;
	case 'w': /* --author */
		if (author_arg) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple author options may not be specified"
			);
			assert(parsing_rcsinit);
			FREE(author_arg);
			author_arg = NULL;
		}
		if (arg)
			author_arg = strdup(arg);
		else {
			struct passwd *pw;
			
			/*
			 * Use the user's username.
			 */
			pw = getpwuid(getuid());
			if (!pw) {
				/* They've probably disappeared out of /etc/passwd. */
				argp_failure(state, EXIT_FAILURE, 0, "could not determine username");
				break;
			}
			
			author_arg = strdup(pw->pw_name);
		}
		break;
	case 's': /* --state */
		assert(arg); /* argument is mandatory */
		if (state_arg) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple state options may not be specified"
			);
			assert(parsing_rcsinit);
			FREE(state_arg);
		}
		state_arg = strdup(arg);
		break;
	case 'x': /* --suffixes */
		assert(arg); /* argument is mandatory */
		if (suffixes) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple suffixes options may not be specified"
			);
			assert(parsing_rcsinit);
			FREE(suffixes);
		}
		suffixes = strdup(arg);
		break;
	case 'z': /* --zone */
		assert(arg); /* argument is mandatory */
		if (zone) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple default time zone options may not be specified"
			);
			assert(parsing_rcsinit);
			FREE(zone);
		}
		zone = strdup(arg);
		break;
	case 'k': /* --expand */
		assert(arg); /* argument is mandatory */
		if (expand != EXPAND_UNDEFINED) {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"multiple keyword substitution types may not be specified"
			);
			assert(parsing_rcsinit);
		}
		if (!strcmp(arg, "kv")) {
			expand = EXPAND_KEY_VALUE;
			break;
		} else if (!strcmp(arg, "kvl")) {
			expand = EXPAND_KEY_VALUE_LOCKER;
			break;
		} else if (!strcmp(arg, "k")) {
			expand = EXPAND_KEY_ONLY;
			break;
		} else if (!strcmp(arg, "o")) {
			expand = EXPAND_OLD_STRING;
			break;
		} else if (!strcmp(arg, "b")) {
			expand = EXPAND_BINARY_STRING;
			break;
		} else if (!strcmp(arg, "v")) {
			expand = EXPAND_VALUE_ONLY;
			break;
		} else {
			argp_failure(
				state, EXIT_FAILURE, 0,
				"invalid keyword substitution type %s", arg
			);
			break;
		}
	case ARGP_KEY_ARG:
		assert(arg); /* argument is mandatory */
		vector_append(filenames, arg);
		break;
	case ARGP_KEY_END:
		if (!parsing_rcsinit) {
			unsigned int i;
			
			if (!vector_count(filenames)) {
				argp_failure(state, EXIT_FAILURE, 0, "no files specified");
				assert(0);
			}
			
			/*
			 * Resolve the zone, if it was specified.
			 */
			zone_offset = TM_UNDEFINED_ZONE;
			if (zone && !date_parse_zone(zone, &zone_offset)) {
				argp_failure(state, EXIT_FAILURE, 0, "invalid time zone: %s", zone);
				break;
			}
	
			/*
			 * Check the tag doesn't contain "..", if it was specified.
			 */
			if (tag_arg) {
				if (strstr(tag_arg, "..")) {
					argp_failure(
						state, EXIT_FAILURE, 0, "missing tag component: %s", tag_arg
					);
					break;
				}
			}
			
			/*
			 * Resolve the date, if it was specified.
			 */
			if (date_arg) {
				date = date_parse(date_arg, !!zone, zone_offset);
				if (date < 0) {
					argp_failure(state, EXIT_FAILURE, 0, "invalid date: %s", date_arg);
					break;
				}
			}
			
			/*
			 * If a matching working filename and RCS filename are beside each
			 * other on the command line, we pair them together.
			 */
			for (i = 0; i < vector_count(filenames); i++) {
				const char *filename;
				
				filename = (const char *)vector_get(filenames, i);
				assert(filename);
				
				if (is_rcs_filename(filename)) {
					if (rcs_filename)
						failures |= annotate(NULL, rcs_filename);
					rcs_filename = filename;
					if (working_filename) {
						if (
							does_working_filename_match_rcs_filename(
								working_filename, rcs_filename
							)
						) {
#if FASTEXIT
							if (i == vector_count(filenames) - 1) cleanup = 0;
#endif /* FASTEXIT */
							failures |= annotate(working_filename, rcs_filename);
							working_filename = rcs_filename = NULL;
						} else {
							failures |= annotate(working_filename, NULL);
							working_filename = NULL;
						}
					}
				} else {
					if (working_filename)
						failures |= annotate(working_filename, NULL);
					working_filename = filename;
					if (rcs_filename) {
						if (
							does_working_filename_match_rcs_filename(
								working_filename, rcs_filename
							)
						) {
#if FASTEXIT
							if (i == vector_count(filenames) - 1) cleanup = 0;
#endif /* FASTEXIT */
							failures |= annotate(working_filename, rcs_filename);
							working_filename = rcs_filename = NULL;
						} else {
							failures |= annotate(NULL, rcs_filename);
							rcs_filename = NULL;
						}
					}
				}
				
				/*
				 * If we had both working_filename and rcs_filename we should
				 * have processed at least one of them.
				 */
				assert(!working_filename || !rcs_filename);
			}
			
			/*
			 * Handle any remaining working filename or RCS filename.
			 */
#if FASTEXIT
			cleanup = 0;
#endif /* FASTEXIT */
			if (working_filename) failures |= annotate(working_filename, NULL);
			if (rcs_filename)     failures |= annotate(NULL, rcs_filename);
		}
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	
	return 0;
}

int
main(int argc, char **argv) {
	char *rcsinit;
	struct argp_option options[] = {
		{       NULL,   0,       NULL,                   0,
		                                  "Revision specification options:", 0  },
		{ "revision", 'r',      "REV", OPTION_ARG_OPTIONAL,
		                                             "Revision to annotate", 0  },
		{      "rev",   0,       NULL, OPTION_HIDDEN | OPTION_ALIAS,   NULL, 0  },
		{     "date", 'd',     "DATE",                   0,
		                                     "Date of revision to annotate", 0  },
		{   "author", 'w',    "LOGIN", OPTION_ARG_OPTIONAL,
		                                   "Author of revision to annotate", 0  },
		{    "state", 's',    "STATE",                   0,
		                                    "State of revision to annotate", 0  },
		{       NULL,   0,       NULL,                   0,
		                                    "Keyword substitution options:", 0  },
		{   "expand", 'k',    "SUBST",                   0,
		                    "Substitutions performed (kv, kvl, k, o, b, v)", 0  },
		{       NULL,   0,       NULL,                   0,
		                                                   "Other options:", 0  },
		{ "suffixes", 'x', "SUFFIXES",                   0,
		 SSLASH "-separated list of RCS suffixes (default: '" SUFFIXES "')", 0  },
		{     "zone", 'z',     "ZONE",                   0,
		                               "Default time zone (default: 'UTC')", 0  },
		{       NULL,   0,       NULL,                   0, "Help options:", -1 },
		{     "help", '?',       NULL,                   0,
		                                              "Give this help list", -1 },
		{    "usage", 0x80,      NULL,                   0,
		                                       "Give a short usage message", -1 },
		{  "version", 'V',      "VER", OPTION_ARG_OPTIONAL,
		                                 "Print program version; or\n"
		                                 "Emulate RCS version (default: 5)", -1 },
		{ NULL, '\0', NULL, 0, NULL, 0 }
	};
	struct argp parser = {
		NULL, parse_options, "FILE ...",
		"Annotate RCS files with the last revision where each line was modified.",
		NULL, NULL, NULL
	};
	parser.options = options;
	
#if HAVE_LOCALE_H && HAVE_SETLOCALE
	/*
	 * Use the environment's locale, not "C".
	 */
	setlocale(LC_ALL, "");
#endif /* HAVE_LOCALE_H && HAVE_SETLOCALE */
	
	set_program_name(argv[0]);
	
	argp_err_exit_status = EXIT_FAILURE;
	
	failures = 0;
	rcs_emulation = 5;
	filenames = vector_new((dup_fn_t)string_dup, (free_fn_t)string_free);
	tag_arg = date_arg = author_arg = state_arg = NULL;
	expand = EXPAND_UNDEFINED;
	suffixes = zone = NULL;
	date = (time_t)(-1);
	cleanup = 1;
	
	/*
	 * Parse RCSINIT environment variable first, if it exists.
	 * We try to ignore arguments we don't expect.
	 */
	parsing_rcsinit = 1;
	if ( (rcsinit = getenv("RCSINIT")) ) {
		char *copy, **rcsinit_argv;
		char *a, *b, *c;
		int escape, rcsinit_argc;
		unsigned int spaces = 0;
		
		copy = strdup(rcsinit);
		
		/* Count spaces */
		for (c = copy; *c; c++)
			if (ISSPACE(*c))
				spaces++;
		
		rcsinit_argv = MALLOC(spaces + 2, char *);
		rcsinit_argv[0] = argv[0];
		rcsinit_argc = 1;
		
		escape = 0;
		a = b = c = copy;
		while (1) {
			if (!*b) {
				if (a != c)
					rcsinit_argv[rcsinit_argc++] = c;
				*a = '\0';
				break;
			} else if (!escape && ISSPACE(*b)) {
				if (a != c)
					rcsinit_argv[rcsinit_argc++] = c;
				*a++ = '\0';
				c = a;
			} else if (!escape && *b == '\\') {
				escape = 1;
			} else {
				escape = 0;
				*a++ = *b;
			}
				
			b++;
		}
		
		argp_parse(
			&parser, rcsinit_argc, rcsinit_argv,
			ARGP_NO_HELP | ARGP_NO_EXIT, /* Warn but don't exit on argp_failure */
			NULL, NULL
		); /* ignore errors */
		FREE(rcsinit_argv);
		FREE(copy);
	}
	parsing_rcsinit = 0;
	
	/*
	 * Annotations occur in the parser function's ARGP_KEY_END state.
	 */
	failures |= argp_parse(&parser, argc, argv, ARGP_NO_HELP, NULL, NULL);
	
	if (cleanup) {
		vector_free(filenames);
		if (suffixes) FREE(suffixes);
		if (zone) FREE(zone);
		if (tag_arg) FREE(tag_arg);
		if (date_arg) FREE(date_arg);
		if (author_arg) FREE(author_arg);
		if (state_arg) FREE(state_arg);
	}
	
	return (failures ? EXIT_FAILURE : EXIT_SUCCESS);
}
