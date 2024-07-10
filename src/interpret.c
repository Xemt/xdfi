/* Xemt <https://github.com/Xemt>, 3/18/24 - 7/10/24. 
 
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

#pragma once

#if !defined(INTERPRET_C)
#	define INTERPRET_C

#	include <sys/stat.h>

#	define MAX_BYTES 1024

	/* Deadfish instructions. They correlate to ASCII characters. */
#	define INST_INC 105
#	define INST_DEC 100
#	define INST_SQR 115
#	define INST_OUT 111

	/* Accumulator limits. */
#	define ACC_MIN -1
#	define ACC_MAX 255

	static int acc;

	/* Do something based on the specified character. */
	static void
	Consume_Chr(char c)
	{
		switch (c) {
			case INST_INC:
				acc++;
				break;
			case INST_DEC:
				acc--;
				break;
			case INST_SQR:
				acc = acc * acc;
				break;
			case INST_OUT:
				printf("Accumulator: %d\n", acc);
				break;
		}
	}

	void 
	DF_Interpret_Str(const char *s)
	{
		size_t i;
		acc = 0;

		for (i = 0; s[i] != 0; i++) {
			if ((acc < ACC_MIN) || (acc > ACC_MAX)) {
				acc = 0;
			}

			Consume_Chr(s[i]);
		}
	}

	void
	DF_Interpret_File(const char *filepath)
	{
		struct stat	 st;
		FILE 		*fp = NULL;
		char		 buf[MAX_BYTES] = {0};
		char		*bufptr = NULL;
		acc = 0;

		if ( stat(filepath, &st) != 0 ) {
			return;
		}

		/* We can't interpret anything other than a regular file. */
		if ( !S_ISREG(st.st_mode) ) {
			return;
		}

		fp = fopen(filepath, "r+");

		bufptr = fgets(buf, MAX_BYTES, fp);

		/* What went wrong? */
		if (bufptr == NULL) {
			return;
		}
		
		DF_Interpret_Str(bufptr);

		bufptr = NULL;

		fclose(fp);
		fp = NULL;		
	}
#endif /* !defined(INTERPRET_C) */
