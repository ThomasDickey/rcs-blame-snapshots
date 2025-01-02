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

/*
 * I've taken this from RCS v5.7, cleaned it up (a bit), bugfixed it (a bit)
 * and simplified it (a bit). Still don't fully understood though.
 *
 * Original copyright:
 * Copyright 1993, 1994, 1995 Paul Eggert
 * Distributed under license by the Free Software Foundation, Inc.
 */

#include <system.h>

#if HAVE_LANGINFO_H
# include <langinfo.h>
#endif /* HAVE_LANGINFO_H */

#include <setenv.h>
#include <strftime.h>

#include <date.h>

#define TM_UNDEFINED (-1)
#define TM_DEFINED(x) (0 <= (x))

#define TM_YEAR_ORIGIN 1900

extern unsigned int rcs_emulation;

struct parse_state {
	struct tm tm;
	int ymodulus;
	int yweek;
	long zone;
};

struct time_zone {
	const char *name;
	int offset;
};

/* Taken from PostgreSQL docs, merged with original RCS list. */
static const struct time_zone zones[] = {
	{ "NZDT", +1300 },
	{ "IDLE", +1200 },
	{ "NZST", +1200 },
	{ "NZT", +1200 },
	{ "AESST", +1100 },
	{ "ACSST", +1030 },
	{ "CADT", +1030 },
	{ "SADT", +1030 },
	{ "AEST", +1000 },
	{ "EAST", +1000 },
	{ "GST", +1000 },
	{ "LIGT", +1000 },
	{ "JDT", +1000 },
	{ "KDT", +900 },
	{ "SAST", +930 },
	{ "CAST", +930 },
	{ "AWSST", +900 },
	{ "JST", +900 },
	{ "KST", +900 },
	{ "MHT", +900 },
	{ "WDT", +900 },
	{ "MT", +830 },
	{ "AWST", +800 },
	{ "CCT", +800 },
	{ "WADT", +800 },
	{ "WST", +800 },
	{ "JT", +730 },
	{ "ALMST", +700 },
	{ "WAST", +700 },
	{ "CXT", +700 },
	{ "MMT", +630 },
	{ "ALMT", +600 },
	{ "MAWT", +600 },
	{ "IOT", +500 },
	{ "MVT", +500 },
	{ "TFT", +500 },
	{ "AFT", +430 },
	{ "EAST", +400 },
	{ "MUT", +400 },
	{ "RET", +400 },
	{ "SCT", +400 },
	{ "IRT", +330 },
	{ "IT", +330 },
	{ "EAT", +300 },
	{ "BT", +300 },
	{ "HMT", +300 },
	{ "BDST", +200 },
	{ "CEST", +200 },
	{ "EET", +200 },
	{ "FWT", +200 },
	{ "IST", +200 },
	{ "MEST", +200 },
	{ "SST", +200 },
	{ "BST", +100 },
	{ "CET", +100 },
	{ "DNT", +100 },
	{ "FST", +100 },
	{ "MET", +100 },
	{ "MEWT", +100 },
	{ "MEZ", +100 },
	{ "NOR", +100 },
	{ "SET", +100 },
	{ "SWT", +100 },
	{ "BST", 000 },
	{ "GMT", 000 },
	{ "UT", 000 },
	{ "UTC", 000 },
	{ "CUT", 000 },
	{ "Z", 000 },
	{ "ZULU", 000 },
	{ "WET", 000 },
	{ "WAT", -100 },
	{ "FNST", -100 },
	{ "FNT", -200 },
	{ "BRST", -200 },
	{ "NDT", -230 },
	{ "ADT", -300 },
	{ "AWT", -300 },
	{ "BRT", -300 },
	{ "NFT", -330 },
	{ "NST", -330 },
	{ "AST", -400 },
	{ "ACST", -400 },
	{ "EDT", -400 },
	{ "ACT", -500 },
	{ "CDT", -500 },
	{ "EST", -500 },
	{ "CST", -600 },
	{ "MDT", -600 },
	{ "MST", -700 },
	{ "PDT", -700 },
	{ "AKDT", -800 },
	{ "PST", -800 },
	{ "YDT", -800 },
	{ "AKST", -900 },
	{ "HDT", -900 },
	{ "HADT", -900 },
	{ "YST", -900 },
	{ "MART", -930 },
	{ "AHST", -1000 },
	{ "HST", -1000 },
	{ "HAST", -1000 },
	{ "CAT", -1000 },
	{ "NT", -1100 },
	{ "IDLW", -1200 },
	{ "LT", 1 },
	{ NULL, 0 }
};

#if ! HAVE_NL_LANGINFO
static const char * const standard_months[] = {
	"January", "February", "March",
	"April", "May", "June",
	"July", "August", "September",
	"October", "November", "December",
	0
};
static const char * const standard_ab_months[] = {
	"Jan", "Feb", "Mar",
	"Apr", "May", "Jun",
	"Jul", "Aug", "Sep",
	"Oct", "Nov", "Dec",
	0
};
static const char * const standard_days[] = {
	"Sunday", "Monday", "Tuesday",
	"Wednesday", "Thursday", "Friday",
	"Saturday", "Sunday",
	0
};
static const char * const standard_ab_days[] = {
	"Sun", "Mon", "Tue",
	"Wed", "Thu", "Fri",
	"Sat", "Sun",
	0
};
#endif /* ! HAVE_NL_LANGINFO */

/*
 * Array of patterns to look for in a date string.
 * Order is important: we look for the first matching pattern
 * whose values do not contradict values that we already know about.
 * See `parse_pattern_letter' below for the meaning of the pattern codes.
 */
static const char * const patterns[] = {
	/*
	* These traditional patterns must come first,
	* to prevent an ISO 8601 format from misinterpreting their prefixes.
	*/
	"E_n_y", "x", /* RFC 822 */
	"E_n", "n_E", "n", "t:m:s_A", "t:m_A", "t_A", /* traditional */
	"y/N/D$", /* traditional RCS */

	/* ISO 8601:1988 formats, generalized a bit.  */
	"y-N-D$", "4ND$", "Y-N$",
	"RND$", "-R=N$", "-R$", "--N=D$", "N=DT",
	"--N$", "---D$", "DT",
	"Y-d$", "4d$", "R=d$", "-d$", "dT",
	"y-W-X", "yWX", "y=W",
	"-r-W-X", "r-W-XT", "-rWX", "rWXT", "-W=X", "W=XT", "-W",
	"-w-X", "w-XT", "---X$", "XT", "4$",
	"T",
	"h:m:s$", "hms$", "h:m$", "hm$", "h$", "-m:s$", "-ms$", "-m$", "--s$",
	"Y", "Z",

	NULL
};

/*
* Parse an initial prefix of S of length DIGITS; it must be a number.
* Store the parsed number into *RES.
* Return the first character after the prefix, or 0 if it couldn't be parsed.
*/
static const char *
_date_parse_fixed(const char *s, int digits, int *res) {
	int n;
	char const *lim;

	assert(s);
	assert(res);

	n = 0;
	lim = s + digits;
	while (s < lim) {
		unsigned int d = (unsigned) (*s++ - '0');
		if (9 < d)
			return NULL;
		n = 10 * n + (int) d;
	}
	*res = n;
	return s;
}

/*
* Parse an initial prefix of S of length DIGITS;
* it must be a number in the range LO through HI.
* Store the parsed number into *RES.
* Return the first character after the prefix, or 0 if it couldn't be parsed.
*/
static const char *
_date_parse_ranged(const char *s, int digits, int lo, int hi, int *res) {
	assert(s);
	assert(res);

	s = _date_parse_fixed(s, digits, res);
	return (s && lo <= *res && *res <= hi) ? s : NULL;
}

/*
* Parse an initial prefix of S of length DIGITS;
* it must be a number in the range LO through HI
* and it may be followed by a fraction that is to be computed using RESOLUTION.
* Store the parsed number into *RES; store the fraction times RESOLUTION,
* rounded to the nearest integer, into *FRES.
* Return the first character after the prefix, or 0 if it couldn't be parsed.
*/
static const char *
_date_parse_decimal(
	const char *s, int digits, int lo, int hi, int resolution, int *res,
	int *fres
) {
	const char *dp;
	size_t dpl;

	assert(s);
	assert(res);
	assert(fres);

#if HAVE_NL_LANGINFO
# ifdef NL_LANGINFO_DP
	dp = nl_langinfo(NL_LANGINFO_DP);
# else /* ! defined(NL_LANGINFO_DP) */
	dp = ".";
# endif /* ! defined(NL_LANGINFO_DP) */
#else /* ! HAVE_NL_LANGINFO */
	dp = ".";
#endif /* ! HAVE_NL_LANGINFO */
	dpl = strlen(dp);

	s = _date_parse_fixed(s, digits, res);
	if (s && lo <= *res && *res <= hi) {
		int f = 0;
		if (*dp && !strncasecmp(s, dp, dpl) && ISDIGIT(s[dpl])) {
			const char *s1 = s + dpl;
			int num10 = 0, denom10 = 10, product;
			s = s1;
			while (ISDIGIT(*++s))
				denom10 *= 10;
			s = _date_parse_fixed(s1, (int) (s - s1), &num10);
			product = num10 * resolution;
			f = (product + (denom10 >> 1)) / denom10;
			f -= f & (product % denom10 == denom10 >> 1); /* round to even */
			if (f < 0 || product / resolution != num10)
				return NULL; /* overflow */
		}
		*fres = f;
		return s;
	}
	return NULL;
}

/*
* Parse an initial prefix of S; it must denote a time zone.
* Set *ZONE to the number of seconds east of GMT,
* or to TM_LOCAL_ZONE if it is the local time zone.
* Return the first character after the prefix, or 0 if it couldn't be parsed.
*/
const char *
date_parse_zone(const char *s, long *zone) {
	char sign;
	int hh, mm, ss;
	int minutesEastOfUTC;
	long offset, z;
	const struct time_zone *tz;

	assert(s);
	assert(zone);

	/*
	* The formats are LT, n, n DST, nDST, no, o
	* where n is a time zone name
	* and o is a time zone offset of the form [-+]hh[:mm[:ss]].
	*/
	switch (*s) {
	case '-': case '+':
		z = 0;
		break;
	default:
		minutesEastOfUTC = -1;
		for (tz = zones; tz->name; tz++) {
			if (!strncasecmp(s, tz->name, strlen(tz->name))) {
				s += strlen(tz->name);
#define hr60nonnegative(t) ((t) / 100 * 60  +  (t)%100)
#define hr60(t) ((t) < 0 ? -hr60nonnegative(-(t)) : hr60nonnegative(t))
				minutesEastOfUTC = hr60(tz->offset);
				break;
			}
		}

		if (minutesEastOfUTC == -1)
			return NULL;

		/* Don't bother to check rest of spelling.  */
		while (ISALPHA(*s))
			s++;

		/* Don't modify LT.  */
		if (minutesEastOfUTC == 1) {
			*zone = TM_LOCAL_ZONE;
			return s;
		}

		z = minutesEastOfUTC * 60L;

		/* Look for trailing " DST".  */
		if (
			(s[-1]=='T' || s[-1]=='t') &&
			(s[-2]=='S' || s[-2]=='s') &&
			(s[-3]=='D' || s[-3]=='t')
		)
			goto TRAILING_DST;
		while (ISSPACE(*s))
			s++;
		if (
			(s[0]=='D' || s[0]=='d') &&
			(s[1]=='S' || s[1]=='s') &&
			(s[2]=='T' || s[2]=='t')
		) {
			s += 3;
TRAILING_DST:
			*zone = z + 60*60;
			return s;
		}

		*zone = z;
		switch (*s) {
			case '-': case '+': break;
			default: return s;
		}
	}
	sign = *s++;

	if (!(s = _date_parse_ranged(s, 2, 0, 23, &hh)))
		return NULL;
	mm = ss = 0;
	if (*s == ':')
		s++;
	if (ISDIGIT(*s)) {
		if (!(s = _date_parse_ranged(s, 2, 0, 59, &mm)))
			return NULL;
		if (*s == ':' && s[-3] == ':' && ISDIGIT(s[1])) {
			if (!(s = _date_parse_ranged(s + 1, 2, 0, 59, &ss)))
				return NULL;
		}
	}
	if (ISDIGIT(*s))
		return NULL;
	offset = (hh * 60 + mm) * 60L + ss;
	*zone = z + (sign == '-' ? -offset : offset);
	/*
	* ?? Are fractions allowed here?
	* If so, they're not implemented.
	*/
	return s;
}

#if ! HAVE_NL_LANGINFO
# define nl_item int
# define   MON_1   1
# define   MON_12 11
# define ABMON_1   1
# define ABMON_12 11
# define   DAY_1   1
# define   DAY_7   7
# define ABDAY_1   1
# define ABDAY_7   7
#endif /* ! HAVE_NL_LANGINFO */

static const char *
parse_pattern_letter(const char *s, char c, struct parse_state *state) {
	assert(s);
	assert(c);
	assert(state);

	switch (c) {
	case '$': /* The next character must be a non-digit.  */
		if (ISDIGIT(*s))
			return NULL;
		break;
	case '-': case '/': case ':':
		/* These characters stand for themselves.  */
		if (*s++ != c)
			return NULL;
		break;
	case '4': /* 4-digit year */
		s = _date_parse_fixed(s, 4, &state->tm.tm_year);
		break;
	case '=': /* optional '-' */
		s += *s == '-';
		break;
	case 'A': /* AM or PM */
		/*
		 * This matches either enough of AM_STR or PM_STR to be unambiguous,
		 * or the whole lot.
		 */
		{
#if HAVE_NL_LANGINFO
			const char *am = nl_langinfo(AM_STR);
			const char *pm = nl_langinfo(PM_STR);
#else /* ! HAVE_NL_LANGINFO */
			const char *am = NULL;
			const char *pm = NULL;
#endif /* ! HAVE_NL_LANGINFO */
			size_t aml, pml, length;

			if (!am || !*am) am = "AM";
			if (!pm || !*pm) pm = "PM";

			aml = strlen(am);
			pml = strlen(pm);

			/* Find unambiguous length */
			for (length = 1; am[length - 1] == pm[length - 1]; length++)
				;

			if (!strncasecmp(s, am, aml)) {
				if (state->tm.tm_hour == 12)
					state->tm.tm_hour = 0;
				s += aml;
			} else if (!strncasecmp(s, pm, pml)) {
				if (state->tm.tm_hour < 12)
					state->tm.tm_hour += 12;
				s += pml;
			} else if (!strncasecmp(s, am, length)) {
				if (state->tm.tm_hour == 12)
					state->tm.tm_hour = 0;
				s += length;
			} else if (!strncasecmp(s, pm, length)) {
				if (state->tm.tm_hour < 12)
					state->tm.tm_hour += 12;
				s += length;
			} else
				return NULL;

			if (ISALNUM(*s))
				return NULL;
		}
		break;
	case 'D': /* day of month [01-31] */
		s = _date_parse_ranged(s, 2, 1, 31, &state->tm.tm_mday);
		break;
	case 'd': /* day of year [001-366] */
		s = _date_parse_ranged(s, 3, 1, 366, &state->tm.tm_yday);
		state->tm.tm_yday--;
		break;
	case 'E': /* extended day of month [1-9, 01-31] */
		s = _date_parse_ranged(s, (
			ISDIGIT(s[0]) &&
			ISDIGIT(s[1])
		) + 1, 1, 31, &state->tm.tm_mday);
		break;
	case 'h': /* hour [00-23 followed by optional fraction] */
		{
			int frac;
			s = _date_parse_decimal(s, 2, 0, 23, 60 * 60, &state->tm.tm_hour, &frac);
			state->tm.tm_min = frac / 60;
			state->tm.tm_sec = frac % 60;
		}
		break;
	case 'm': /* minute [00-59 followed by optional fraction] */
		s = _date_parse_decimal(
			s, 2, 0, 59, 60, &state->tm.tm_min, &state->tm.tm_sec
		);
		break;
	case 'n': /* month name [e.g. "Jan"] */
		{
			nl_item item;
			int found;

			found = 0;
			for (item = MON_1; item <= MON_12; item++) {
#if HAVE_NL_LANGINFO
				const char *month = nl_langinfo(item);
#else /* ! HAVE_NL_LANGINFO */
				const char *month = standard_months[item - MON_1];
#endif /* ! HAVE_NL_LANGINFO */
				if (!*month)
					continue;
				if (!strncasecmp(s, month, strlen(month))) {
					s += strlen(month);
					state->tm.tm_mon = item - MON_1;
					found = 1;
					break;
				}
			}
			if (found) {
				if (ISALPHA(*s))
					return NULL;
				break;
			}
			found = 0;
			for (item = ABMON_1; item <= ABMON_12; item++) {
#if HAVE_NL_LANGINFO
				const char *month = nl_langinfo(item);
#else /* ! HAVE_NL_LANGINFO */
				const char *month = standard_ab_months[item - ABMON_1];
#endif /* ! HAVE_NL_LANGINFO */
				if (!*month)
					continue;
				if (!strncasecmp(s, month, strlen(month))) {
					s += strlen(month);
					state->tm.tm_mon = item - ABMON_1;
					found = 1;
					break;
				}
			}
			if (found) {
				if (ISALPHA(*s))
					return NULL;
				break;
			}
			return NULL;
		}
		assert(0);
	case 'N': /* month [01-12] */
		s = _date_parse_ranged(s, 2, 1, 12, &state->tm.tm_mon);
		state->tm.tm_mon--;
		break;
	case 'r': /* year % 10 (remainder in origin-0 decade) [0-9] */
		s = _date_parse_fixed(s, 1, &state->tm.tm_year);
		state->ymodulus = 10;
		break;
CASE_R:
	case 'R': /* year % 100 (remainder in origin-0 century) [00-99] */
		s = _date_parse_fixed(s, 2, &state->tm.tm_year);
		state->ymodulus = 100;
		break;
	case 's': /* second [00-60 followed by optional fraction] */
		{
			int frac;
			s = _date_parse_decimal(s, 2, 0, 60, 1, &state->tm.tm_sec, &frac);
			state->tm.tm_sec += frac;
		}
		break;
	case 'T': /* 'T' or 't' */
		switch (*s++) {
			case 'T': case 't': break;
			default: return NULL;
		}
		break;
	case 't': /* traditional hour [1-9 or 01-12] */
		s = _date_parse_ranged(s, (
			ISDIGIT(s[0]) && ISDIGIT(s[1])
		) + 1, 1, 12, &state->tm.tm_hour);
		break;
	case 'w': /* 'W' or 'w' only (stands for current week) */
		switch (*s++) {
			case 'W': case 'w': break;
			default: return NULL;
		}
		break;
	case 'W': /* 'W' or 'w', followed by a week of year [00-53] */
		switch (*s++) {
			case 'W': case 'w': break;
			default: return NULL;
		}
		s = _date_parse_ranged(s, 2, 0, 53, &state->yweek);
		break;
	case 'X': /* weekday (1=Mon ... 7=Sun) [1-7] */
		s = _date_parse_ranged(s, 1, 1, 7, &state->tm.tm_wday);
		state->tm.tm_wday--;
		break;
	case 'x': /* weekday name [e.g. "Sun"] */
		{
			nl_item item;
			int found;

			found = 0;
			for (item = DAY_1; item <= DAY_7; item++) {
#if HAVE_NL_LANGINFO
				const char *day = nl_langinfo(item);
#else /* ! HAVE_NL_LANGINFO */
				const char *day = standard_days[item - DAY_1];
#endif /* ! HAVE_NL_LANGINFO */
				if (!*day)
					continue;
				if (!strncasecmp(s, day, strlen(day))) {
					s += strlen(day);
					state->tm.tm_wday = item - DAY_1;
					found = 1;
					break;
				}
			}
			if (found) {
				if (ISALPHA(*s))
					return NULL;
				break;
			}
			found = 0;
			for (item = ABDAY_1; item <= ABDAY_7; item++) {
#if HAVE_NL_LANGINFO
				const char *day = nl_langinfo(item);
#else /* ! HAVE_NL_LANGINFO */
				const char *day = standard_ab_days[item - ABDAY_1];
#endif /* ! HAVE_NL_LANGINFO */
				if (!*day)
					continue;
				if (!strncasecmp(s, day, strlen(day))) {
					s += strlen(day);
					state->tm.tm_wday = item - ABDAY_1;
					found = 1;
					break;
				}
			}
			if (found) {
				if (ISALPHA(*s))
					return NULL;
				break;
			}
			return NULL;
		}
		assert(0);
	case 'y': /* either R or Y */
		if (
			ISDIGIT(s[0]) &&
			ISDIGIT(s[1]) &&
			!ISDIGIT(s[2])
		)
			goto CASE_R;
		/* fall through */
	case 'Y': /* year in full [4 or more digits] */
		{
			int len = 0;
			while (ISDIGIT(s[len]))
				len++;
			if (len < 4)
				return NULL;
			s = _date_parse_fixed(s, len, &state->tm.tm_year);
		}
		break;
	case 'Z': /* time zone */
		s = date_parse_zone(s, &state->zone);
		break;
	case '_': /* possibly empty sequence of non-alphanumerics */
		while (!ISALNUM(*s) && *s)
			s++;
		break;
	default: /* bad pattern */
		return NULL;
	}

	return s;
}

static inline void
undefine(struct parse_state *state) {
	state->tm.tm_sec = state->tm.tm_min = state->tm.tm_hour =
		state->tm.tm_mday = state->tm.tm_mon = state->tm.tm_year =
		state->tm.tm_wday = state->tm.tm_yday = state->ymodulus = state->yweek =
		state->tm.tm_isdst = TM_UNDEFINED;
	state->zone = TM_UNDEFINED_ZONE;
}

static int const month_yday[] = {
	/* days in year before start of months 0-12 */
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

static int
isleap(int y) {
	return (y & 3) == 0 && (y % 100 != 0 || y % 400 == 0);
}

/*
* Convert UNIXTIME to struct tm form.
* Use gmtime if available and if !LOCALZONE, localtime otherwise.
*/
static struct tm *
time2tm(time_t unixtime, int localzone) {
	struct tm *tm;
	if (localzone || !(tm = gmtime(&unixtime)))
		tm = localtime(&unixtime);
	return tm;
}

/* Yield A - B, measured in seconds.  */
static time_t
difftm(const struct tm *a, const struct tm *b) {
	int ay = a->tm_year + (TM_YEAR_ORIGIN - 1);
	int by = b->tm_year + (TM_YEAR_ORIGIN - 1);
	int difference_in_day_of_year = a->tm_yday - b->tm_yday;
	int intervening_leap_days = (
		((ay >> 2) - (by >> 2))
		- (ay / 100 - by / 100)
		+ ((ay / 100 >> 2) - (by / 100 >> 2))
	);
	time_t difference_in_years = ay - by;
	time_t difference_in_days = (
		difference_in_years * 365
		+ (intervening_leap_days + difference_in_day_of_year)
	);
	return
		(
			(
				24 * difference_in_days
				+ (a->tm_hour - b->tm_hour)
			) * 60 + (a->tm_min - b->tm_min)
		) * 60 + (a->tm_sec - b->tm_sec);
}

/*
* Convert TM to time_t, using localtime if LOCALZONE and gmtime otherwise.
* Use only TM's year, mon, mday, hour, min, and sec members.
* Ignore TM's old tm_yday and tm_wday, but fill in their correct values.
* Yield -1 on failure (e.g. a member out of range).
* Posix 1003.1-1990 doesn't allow leap seconds, but some implementations
* have them anyway, so allow them if localtime/gmtime does.
*/
static time_t
tm2time(struct tm *tm, int localzone) {
	/* Cache the most recent t,tm pairs; 1 for gmtime, 1 for localtime.  */
	static time_t t_cache[2];
	static struct tm tm_cache[2];

	time_t d, gt;
	const struct tm *gtm;

	/*
	* The maximum number of iterations should be enough to handle any
	* combinations of leap seconds, time zone rule changes, and solar time.
	* 4 is probably enough; we use a bigger number just to be safe.
	*/
	int remaining_tries = 8;

	/* Avoid subscript errors.  */
	if (12 <= (unsigned int)tm->tm_mon)
	    return -1;

	tm->tm_yday = month_yday[tm->tm_mon] + tm->tm_mday
		- (tm->tm_mon < 2 || !isleap(tm->tm_year + TM_YEAR_ORIGIN));

	/* Make a first guess.  */
	gt = t_cache[localzone];
	gtm = gt ? &tm_cache[localzone] : time2tm(gt, localzone);

	/* Repeatedly use the error from the guess to improve the guess.  */
	while ((d = difftm(tm, gtm)) != 0) {
		if (--remaining_tries == 0)
			return -1;
		gt += d;
		gtm = time2tm(gt,localzone);
	}
	t_cache[localzone] = gt;
	tm_cache[localzone] = *gtm;

	/*
	* Check that the guess actually matches;
	* overflow can cause difftm to yield 0 even on differing times,
	* or tm may have members out of range (e.g. bad leap seconds).
	*/
	if ((tm->tm_year ^ gtm->tm_year)
		| (tm->tm_mon  ^ gtm->tm_mon)
		| (tm->tm_mday ^ gtm->tm_mday)
		| (tm->tm_hour ^ gtm->tm_hour)
		| (tm->tm_min  ^ gtm->tm_min)
		| (tm->tm_sec  ^ gtm->tm_sec))
		return -1;

	tm->tm_wday = gtm->tm_wday;
	return gt;
}

/* Yield the number of days in TM's month.  */
static int
month_days(const struct tm *tm) {
	int m = tm->tm_mon;
	return month_yday[m+1] - month_yday[m]
		+ (m == 1 && isleap(tm->tm_year + TM_YEAR_ORIGIN));
}

/*
* Adjust time T by adding SECONDS.  SECONDS must be at most 24 hours' worth.
* Adjust only T's year, mon, mday, hour, min and sec members;
* plus adjust wday if it is defined.
*/
static void
adjzone(register struct tm *t, long seconds) {
	/*
	* This code can be off by a second if SECONDS is not a multiple of 60,
	* if T is local time, and if a leap second happens during this minute.
	* But this bug has never occurred, and most likely will not ever occur.
	* Liberia, the last country for which SECONDS % 60 was nonzero,
	* switched to UTC in May 1972; the first leap second was in June 1972.
	*/
	int leap_second = t->tm_sec == 60;
	long sec = seconds + (t->tm_sec - leap_second);
	if (sec < 0) {
		if ((t->tm_min -= (int) ((59 - sec) / 60)) < 0) {
			if ((t->tm_hour -= (59 - t->tm_min) / 60) < 0) {
				t->tm_hour += 24;
				if (TM_DEFINED(t->tm_wday) && --t->tm_wday < 0)
					t->tm_wday = 6;
				if (--t->tm_mday <= 0) {
					if (--t->tm_mon < 0) {
						--t->tm_year;
						t->tm_mon = 11;
					}
					t->tm_mday = month_days(t);
				}
			}
			t->tm_min += 24 * 60;
		}
		sec += 24L * 60 * 60;
	} else if (60 <= (t->tm_min += (int) (sec / 60)))
		if (24 <= (t->tm_hour += t->tm_min / 60)) {
			t->tm_hour -= 24;
			if (TM_DEFINED(t->tm_wday) && ++t->tm_wday == 7)
				t->tm_wday = 0;
			if (month_days(t) < ++t->tm_mday) {
				if (11 < ++t->tm_mon) {
					++t->tm_year;
					t->tm_mon = 0;
				}
				t->tm_mday = 1;
			}
		}
	t->tm_min %= 60;
	t->tm_sec = (int)(sec % 60) + leap_second;
}

time_t
date_parse(const char *s, int use_zone_offset, long zone_offset) {
	struct parse_state state;
	struct tm tm, *tm0;
	int localzone, wday;
	time_t r;

	assert(s);

	if (!use_zone_offset)
		zone_offset = (rcs_emulation < 5 ? TM_LOCAL_ZONE : 0);

	memset(&state, '\0', sizeof(state));
	undefine(&state);

	while (*s) {
		char c;
		const char * const *pattern;

		for (; !ISALNUM(c = *s) && c && c != '-' && c != '+'; s++)
			;
		if (!c)
			break;

		/* Find first pattern that can merge successfully */
		for (pattern = patterns; *pattern; pattern++) {
			struct parse_state temp;
			const char *s2, *c2;

			s2 = s;
			undefine(&temp);
			for (c2 = *pattern; s2 && *c2; c2++)
				s2 = parse_pattern_letter(s2, *c2, &temp);
			if (s2) {
				/* The pattern was fully matched */
#define conflict(a,b) ((a) != (b) && TM_DEFINED(a) && TM_DEFINED(b))
#define merge(a,b) do { if (TM_DEFINED(b)) (a) = (b); } while (0)
				if (
					!conflict(state.tm.tm_sec, temp.tm.tm_sec) &&
					!conflict(state.tm.tm_min, temp.tm.tm_min) &&
					!conflict(state.tm.tm_hour, temp.tm.tm_hour) &&
					!conflict(state.tm.tm_mday, temp.tm.tm_mday) &&
					!conflict(state.tm.tm_mon, temp.tm.tm_mon) &&
					!conflict(state.tm.tm_year, temp.tm.tm_year) &&
					!conflict(state.tm.tm_wday, temp.tm.tm_wday) &&
					!conflict(state.tm.tm_yday, temp.tm.tm_yday) &&
					!conflict(state.ymodulus, temp.ymodulus) &&
					!conflict(state.yweek, temp.yweek) &&
					!(
						state.zone != temp.zone &&
						state.zone != TM_UNDEFINED_ZONE &&
						temp.zone != TM_UNDEFINED_ZONE
					)
				) {
					/* The pattern does not conflict */
					s = s2;
					merge(state.tm.tm_sec, temp.tm.tm_sec);
					merge(state.tm.tm_min, temp.tm.tm_min);
					merge(state.tm.tm_hour, temp.tm.tm_hour);
					merge(state.tm.tm_mday, temp.tm.tm_mday);
					merge(state.tm.tm_mon, temp.tm.tm_mon);
					merge(state.tm.tm_year, temp.tm.tm_year);
					merge(state.tm.tm_wday, temp.tm.tm_wday);
					merge(state.tm.tm_yday, temp.tm.tm_yday);
					merge(state.ymodulus, temp.ymodulus);
					merge(state.yweek, temp.yweek);
					if (temp.zone != TM_UNDEFINED_ZONE) state.zone = temp.zone;
					goto OUTER;
				}
			}
#undef conflict
#undef merge
		}

		return -1;
OUTER:
		;
	}

	if (state.zone == TM_UNDEFINED_ZONE)
		state.zone = zone_offset;

	tm0 = NULL;
	localzone = state.zone == TM_LOCAL_ZONE;
	tm = state.tm;

	if (TM_DEFINED(state.ymodulus) || !TM_DEFINED(tm.tm_year)) {
		/* Get tm corresponding to current time.  */
		tm0 = time2tm(time(NULL), localzone);
		if (!localzone) adjzone(tm0, state.zone);
	}

	if (TM_DEFINED(state.ymodulus))
		tm.tm_year += (tm0->tm_year + TM_YEAR_ORIGIN) /
			state.ymodulus * state.ymodulus;
	else if (!TM_DEFINED(tm.tm_year)) {
		/* Set default year, month, day from current time.  */
		tm.tm_year = tm0->tm_year + TM_YEAR_ORIGIN;
		if (!TM_DEFINED(tm.tm_mon)) {
			tm.tm_mon = tm0->tm_mon;
			if (!TM_DEFINED(tm.tm_mday))
				tm.tm_mday = tm0->tm_mday;
		}
	}

	/* Convert from partime year (Gregorian) to Posix year.  */
	tm.tm_year -= TM_YEAR_ORIGIN;

	/* Set remaining default fields to be their minimum values.  */
	if (!TM_DEFINED(tm.tm_mon)) tm.tm_mon = 0;
	if (!TM_DEFINED(tm.tm_mday)) tm.tm_mday = 1;
	if (!TM_DEFINED(tm.tm_hour)) tm.tm_hour = 0;
	if (!TM_DEFINED(tm.tm_min)) tm.tm_min = 0;
	if (!TM_DEFINED(tm.tm_sec)) tm.tm_sec = 0;

	if (!localzone)
		adjzone(&tm, -state.zone);
	wday = tm.tm_wday;

	/* Convert and fill in the rest of the tm.  */
	r = tm2time(&tm, localzone);

	/* Check weekday.  */
	if (r != -1 && TM_DEFINED(wday) && wday != tm.tm_wday)
		return -1;

	return r;
}

time_t
date_parse_rev(const char *rev) {
	struct tm tm;

	assert(rev);

	if (
		sscanf(rev, "%d.%d.%d.%d.%d.%d",
			&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
			&tm.tm_hour, &tm.tm_min, &tm.tm_sec
		) == 6
	) {
		char *tz;
		time_t result;

		/* Dates can be on the form "99.12.15.08.09.04" before year 2000,
		 * only subtract 1900 years if year >= 1900
		 */
		if (tm.tm_year >= 1900) {
			tm.tm_year -= 1900;
		}

		tm.tm_mon--;
		tm.tm_wday = tm.tm_yday = tm.tm_isdst = 0;

		tz = getenv("TZ");
		if (setenv("TZ", "UTC", 1))
			return -1;
		tzset();
		result = mktime(&tm);
		if (tz)
			setenv("TZ", tz, 1);
		else
			unsetenv("TZ");

		return result;
	} else
		return -1;
}

char *
date_format(time_t date) {
	struct tm *tm;
	char *result;

	assert(date >= 0);

	tm = gmtime(&date); /* if RCS version < 5 then localtime ? */
	result = MALLOC(20, char);
	sprintf(result, "%04u.%02u.%02u.%02u.%02u.%02u",
		(tm->tm_year + 1900) % 10000,
		(tm->tm_mon % 12) + 1,
		(tm->tm_mday % 31),
		(tm->tm_hour % 24),
		(tm->tm_min % 60),
		(tm->tm_sec > 60 ? 60 : tm->tm_sec)
	);
	return result;
}

char *
date_sprintf(time_t date, long zone) {
	struct tm tm;
	char *result;
	size_t len;

	assert(date >= 0);

	result = MALLOC(40, char);
	switch (zone) {
	case TM_UNDEFINED_ZONE:
		/* if RCS version < 5 then localtime ? */
		strftime(result, 40, "%Y/%m/%d %H:%M:%S", gmtime(&date));
		break;
	case TM_LOCAL_ZONE:
#if HAVE_TM_GMTOFF
		memcpy(&tm, localtime(&date), sizeof(struct tm));
		zone = tm.tm_gmtoff;
		goto format_time;
#else /* ! HAVE_TM_GMTOFF */
		zone = -timezone; /* Huh? timezone is seconds west of UTC! */
#endif /* ! HAVE_TM_GMTOFF */
		/* Fall through */
	default:
		memcpy(&tm, gmtime(&date), sizeof(struct tm));
		adjzone(&tm, zone);

format_time: _UNUSED_LABEL
		len = strftime(result, 40, "%Y-%m-%d %H:%M:%S", &tm);
		if (zone >= 0)
			len += (size_t) sprintf(result + len, "+%02ld", zone / 3600);
		else {
			zone = -zone;
			len += (size_t) sprintf(result + len, "-%02ld", zone / 3600);
		}
		zone %= 3600;
		if (zone) {
			len += (size_t) sprintf(result + len, ":%02ld", zone / 60);
			zone %= 60;
		}
		if (zone)
			len += (size_t) sprintf(result + len, ":%02ld", zone);
		break;
	}
	return result;
}

char *format_dates = NULL;

size_t
date_sprintf_prefix(time_t date, char *buffer, size_t len) {
	size_t result;
	char my_buffer[MAX_FORMAT_DATE + 1];
	char *format = format_dates;
	assert(date >= 0);

	if (format == NULL)
		format = "%d-%b-%y";

	/* if RCS version < 5 then localtime ? */
	result = strftime(my_buffer, sizeof(my_buffer) - 1, format, gmtime(&date));
	buffer[0] = '\0';
	if (result != 0) {
		/* see keyword_annotate() usage... */
		if (result <= len) {
			memcpy(buffer, my_buffer, result);
			buffer[result] = '\0';
		}
	}
	return result;
}
