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

#ifndef _SYSTEM_H
#define _SYSTEM_H

#if HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

/*
 * These headers should exist. Even gnulib assumes they do...
 */
#include <assert.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>
#ifndef errno
extern int errno;
#endif
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

#include <alloca.h>
#include <obstack.h>
#include <strchrnul.h>
#include <strdup.h>
#include <string.h>
#include <strndup.h>
#include <strpbrk.h>
#include <strstr.h>
#include <unlocked-io.h>

#if TM_IN_SYS_TIME
# if TIME_WITH_SYS_TIME
#  include <sys/time.h>
#  include <time.h>
# else /* ! TIME_WITH_SYS_TIME */
#  if HAVE_SYS_TIME_H
#   include <sys/time.h>
#  else /* ! HAVE_SYS_TIME_H */
#   include <time.h>
#  endif /* ! HAVE_SYS_TIME_H */
# endif /* ! HAVE_SYS_TIME_H */
#else /* ! TIME_WITH_SYS_TIME */
# include <time.h>
#endif /* ! TM_IN_SYS_TIME */

#if HAVE_UNISTD_H
# include <unistd.h>
#endif /* ! HAVE_UNISTD_H */

#define ALLOCA(C, T) ((T *)alloca((C) * sizeof(T)))
#define MALLOC(C, T) ((T *)malloc((C) * sizeof(T)))
#define MALLOC_VOIDP(C) ((void *)malloc(C))
#define CALLOC(C, T) ((T *)calloc((C), sizeof(T)))
#define REALLOC(P, C, T) ((T *)realloc((P), (C) * sizeof(T)))

static inline char *
SALLOC(size_t c) {
	char *p;
	assert(c);
	p = MALLOC(c + 1, char);
	*p = *(p + c) = '\0';
	return p;
}

static inline char *
SREALLOC(char *p, size_t c) {
	assert(c);
	p = REALLOC(p, c + 1, char);
	*(p + c) = '\0';
	return p;
}

#define obstack_chunk_alloc malloc
#define obstack_chunk_free free
typedef struct obstack obstack_t;

#define OINIT(O) obstack_init(O)
static inline void *
_OALLOC(obstack_t *o, size_t s) {
	assert(o);
	return obstack_alloc(o, s);
}
#define OALLOC(O, C, T) ((T *)_OALLOC((O), (C) * sizeof(T)))

#ifdef NDEBUG
#define xfree(P) free(P)
#else /* ! NDEBUG */
#define xfree(P) do { assert(P); free(P); (P) = NULL; } while (0)
#endif /* ! NDEBUG */

#define FREE(P) xfree(P)

#define OFREEALL(O) obstack_free((O), NULL)

#define VOIDP_DIFF(P, Q) ((ptrdiff_t)((char *)(P) - (char *)(Q)))
#define VOIDP_OFFSET(P, O) ((void *)((char *)(P) + (ptrdiff_t)(O)))

/* No, we don't handle EOF. */
#define ISALNUM(C) isalnum((unsigned char)(C))
#define ISALPHA(C) isalpha((unsigned char)(C))
#define ISDIGIT(C) isdigit((unsigned char)(C))
#define ISGRAPH(C) isgraph((unsigned char)(C))
#define ISSPACE(C) isspace((unsigned char)(C))

#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
	((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(2, 4) && !defined(__STRICTANSI__)
# define _UNUSED __attribute__((unused))
#else /* !__GNUC_PREREQ(2, 4) || defined(__STRICTANSI__) */
# define _UNUSED
#endif /* !__GNUC_PREREQ(2, 4) || defined(__STRICTANSI__) */

#if __GNUC_PREREQ(3, 0) /* I think */
# define _UNUSED_LABEL __attribute__((unused))
#else /*  ! __GNUC_PREREQ(3, 0) */
# define _UNUSED_LABEL
#endif /*  ! __GNUC_PREREQ(3, 0) */

#endif /* _SYSTEM_H */
