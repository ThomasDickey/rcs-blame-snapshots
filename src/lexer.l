%{
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

#define YY_NO_UNPUT
typedef struct { unsigned int line; off_t off; off_t next; } loc_t;
#define YYLTYPE loc_t
#define YY_DECL int yylex YY_PROTO((void))

#include <delta.h>
#include <keyword.h>
#include <hash.h>
#include <vector.h>

#include <parser.h>

YYSTYPE yylval;
YYLTYPE yylloc;

%}

%option noyywrap
%option never-interactive

/*
 * Each string returned as STR or STR_FINAL is actually just a single line.
 * STR is returned when a newline is read; STR_FINAL is returned at the
 * terminate "@".
 * The SA state is active when the lexer is at the start of a string line.
 */
%x SA

STRING ([^@\n]*@@)*[^@\n]*

%%

head            { yylloc.off = yylloc.next; yylloc.next += 4; return HEAD; }
branch          { yylloc.off = yylloc.next; yylloc.next += 6; return BRANCH; }
access          { yylloc.off = yylloc.next; yylloc.next += 6; return ACCESS; }
symbols         { yylloc.off = yylloc.next; yylloc.next += 7; return SYMBOLS; }
locks           { yylloc.off = yylloc.next; yylloc.next += 5; return LOCKS; }
strict          { yylloc.off = yylloc.next; yylloc.next += 6; return STRICT; }
comment         { yylloc.off = yylloc.next; yylloc.next += 7; return COMMENT; }
expand          { yylloc.off = yylloc.next; yylloc.next += 6; return EXPAND; }
date            { yylloc.off = yylloc.next; yylloc.next += 4; return DATE; }
author          { yylloc.off = yylloc.next; yylloc.next += 6; return AUTHOR; }
state           { yylloc.off = yylloc.next; yylloc.next += 5; return STATE; }
branches        { yylloc.off = yylloc.next; yylloc.next += 8; return BRANCHES; }
next            { yylloc.off = yylloc.next; yylloc.next += 4; return NEXT; }
desc            { yylloc.off = yylloc.next; yylloc.next += 4; return DESC; }
log             { yylloc.off = yylloc.next; yylloc.next += 3; return LOG; }
text            { yylloc.off = yylloc.next; yylloc.next += 4; return TEXT; }

[^@[:space:];:]+ {
                	char *temp;
                	unsigned int count;
                	int dot = 0, idchar = 0;
                	yylloc.off = yylloc.next;
                	yylloc.next += yyleng;
                	yylval.i = count = yyleng;
                	for (temp = yytext; count--; temp++) {
                		switch (*temp) {
                		case '.':
                			dot = 1;
                			break;
                		case '$': case ',': case ':': case ';': case '@':
                		case '0': case '1': case '2': case '3': case '4':
                		case '5': case '6': case '7': case '8': case '9':
                			break;
                		default:
                			idchar = 1;
                			break;
                		}
                	}
                	return (idchar ? (dot ? ID : SYM) : NUM);
                }
@{STRING}\n     {
                	BEGIN(SA);
                	yylloc.line++;
                	yylloc.off = yylloc.next + 1;
                	yylloc.next += yyleng;
                	yylval.i = yyleng - 1;
                	return STR;
                }
@{STRING}@      {
                	yylloc.off = yylloc.next + 1;
                	yylloc.next += yyleng;
                	yylval.i = yyleng - 2;
                	return STR_FINAL;
                }
@{STRING}       {
                	/* Has to be at EOF */
                	yylloc.line++;
                	yylloc.off = yylloc.next + 1;
                	yylloc.next += yyleng;
                	yylval.i = yyleng - 1;
                	return STR_FINAL;
                }
<SA>{STRING}\n  {
                	yylloc.line++;
                	yylloc.off = yylloc.next;
                	yylloc.next += yyleng;
                	yylval.i = yyleng;
                	return STR;
                }
<SA>{STRING}@   {
                	BEGIN(INITIAL);
                	yylloc.line++;
                	yylloc.off = yylloc.next;
                	yylloc.next += yyleng;
                	yylval.i = yyleng - 1;
                	return STR_FINAL;
                }
<SA>{STRING}    {
                	/* Has to be at EOF */
                	BEGIN(INITIAL);
                	yylloc.line++;
                	yylloc.off = yylloc.next;
                	yylloc.next += yyleng;
                	yylval.i = yyleng;
                	return STR_FINAL;
                }

[;:]            {
                	yylloc.off = yylloc.next;
                	yylloc.next++;
                	return yytext[0];
                }

[ \f\r\t\v]*\n  {
                	yylloc.line++;
                	yylloc.next += yyleng;
                }
[ \f\r\t\v]*    {
                	yylloc.next += yyleng;
                }
