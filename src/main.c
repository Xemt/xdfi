/* Xemt, 3/13/24 - 3/21/24. 
 
   MIT License

   Copyright (c) 2024 Xemt

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE. */

#include <errno.h>
#include <stdio.h>
#include <string.h>

extern void sinterpret(const char*);
extern void finterpret(const char*);

#include "interpret.c"

#define PROGNAME "xdfi"
#define PROGVERS "1.0.1"

#define USAGE() printf("USAGE:\n\t%s [opts]\nOPTIONS:\n\thelp, usage -- Output this usage page.\n\tversion -- Output the current version of %s.\n\tauthor -- Output the author of %s\n\t-f filepath -- Interpret the contents of filepath as deadfish code.\n\t-e expr -- Interpret a string as deadfish code.\n", PROGNAME, PROGNAME, PROGNAME)
#define VERSION() printf("VERSION: %s\n", PROGVERS)
#define AUTHOR() printf("AUTHOR: Xemt <https://www.github.com/Xemt>\n")

#define STREQL(s1, s2) !strcmp(s1, s2)

int main(int argc, char *argv[])
{
	char *errmsg = NULL;
	int i;

	if (argc == 1) {
		USAGE();
		goto main_end;
	}

	/* Avoid the program name. */
	for (i = 1; i != argc; i++) {
		if ( STREQL(argv[i], "help") || STREQL(argv[i], "author") ) {
			USAGE();
			break;
		} else if ( STREQL(argv[i], "version") ) {
			VERSION();
			break;
		} else if ( STREQL(argv[i], "author") ) {
			AUTHOR();
			break;
		} else if ( STREQL(argv[i], "-f") ||
			    STREQL(argv[i], "-e") )
		{
			/* We don't want to go out of bounds accidentally. */
			if ((i + 1) > (argc - 1)) {
				printf("%s: Argument required for '%s'\n", PROGNAME, argv[i]);
				break;
			}

			i++;

			if ( STREQL(argv[i], "-f") ) {
				finterpret(argv[i]);
			} else if ( STREQL(argv[i], "-e") ) {
				sinterpret(argv[i]);
			}
		} else {
			printf("%s: Unknown command '%s'.\n", PROGNAME, argv[i]);
			break;
		}
	}
	
	goto main_end;
main_end:
	if (errno != 0) {
		errmsg = strerror(errno);
		printf("%s: %s\n", PROGNAME, errmsg);
		errmsg = NULL;
	}
	return errno;
}

