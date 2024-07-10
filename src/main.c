/* Xemt <https://github.com/Xemt>, 3/13/24 - 7/10/24. 
 
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

extern void DF_Interpret_Str(const char*);
extern void DF_Interpret_File(const char*);

#include "interpret.c"

#define PROGRAM_NAME	"xdfi"
#define PROGRAM_VERSION "1.1.1"

#define OPT_PREFIX_CHR *"-"

#define USAGE() printf("USAGE:\n\t%s [opts]\nOPTIONS:\n\thelp, usage -- Output the usage.\n\tversion -- Output the current version of %s.\n\tauthor -- Output the author of %s\n\t-f filepath -- Interpret the contents of filepath as deadfish code.\n\t-e expr -- Interpret a string as deadfish code.\n", PROGRAM_NAME, PROGRAM_NAME, PROGRAM_NAME)
#define VERSION() printf("VERSION: %s\n", PROGRAM_VERSION)
#define AUTHOR() printf("AUTHOR: Xemt <https://www.github.com/Xemt>\n")

#define STR_EQL(s1, s2) !strcmp(s1, s2)

int main(int argc, char *argv[])
{
	char *errmsg = NULL;
	int i;

	if (argc == 1) {
		USAGE();
		goto _main_end;
	}

	/* Parse args, but avoid the program name. */
	for (i = 1; i != argc; i++) {
		if ( STR_EQL(argv[i], "help") || STR_EQL(argv[i], "usage") ) {
			USAGE();
			break;
		} else if ( STR_EQL(argv[i], "version") ) {
			VERSION();
			break;
		} else if ( STR_EQL(argv[i], "author") ) {
			AUTHOR();
			break;
		} else if (argv[i][0] == OPT_PREFIX_CHR) {
			/* We don't want to go out of bounds accidentally. Besides, all our options require a param. */
			if ((i + 1) > (argc - 1)) {
				fprintf(stderr, "%s: Param required for '%s'!\n", PROGRAM_NAME, argv[i]);
				break;
			}
			
			if ( STR_EQL(argv[i], "-f") ) {
				DF_Interpret_File(argv[i + 1]);
			} else if ( STR_EQL(argv[i], "-e") ) {
				DF_Interpret_Str(argv[i + 1]);
			}

			break;
		} else {
			fprintf(stderr, "%s: Unknown command '%s'.\n", PROGRAM_NAME, argv[i]);
			break;
		}
	}
	
	goto _main_end;
_main_end:
	if (errno != 0) {
		errmsg = strerror(errno);
		fprintf(stderr, "%s: %s\n", PROGRAM_NAME, errmsg);
		errmsg = NULL;
	}
	
	return (errno);
}
