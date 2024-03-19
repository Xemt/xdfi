/* Xemt, 3/18/24 - 3/19/24. 
 
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

	/* Deadfish instructions. */
	enum {
		INST_INC = 105, /* i */
		INST_DEC = 100, /* d */
		INST_SQR = 115, /* s */
		INST_OUT = 111  /* o */
	};

	/* Accumulator limits. */
	enum {
		ACC_MIN = -1,
		ACC_MAX = 255
	};

	static int acc;

	/* Do something based on the specified character. */
	static void consumech(char c)
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

	/* Interpret a string as deadfish code. */
	void sinterpret(const char *s)
	{
		size_t i;
		acc = 0;

		for (i = 0; s[i] != 0; i++) {
			if ((acc < ACC_MIN) || (acc > ACC_MAX)) {
				acc = 0;
			}

			consumech(s[i]);
		}
	}

	/* Interpret the contents of a file as deadfish code. */
	void finterpret(const char *filepath)
	{
		struct stat st;
		mode_t mode = 0;
		FILE *fp = NULL;
		char buf[MAX_BYTES] = {0};
		char *p = NULL;

		if ( stat(filepath, &st) != 0 ) {
			return;
		}

		mode = st.st_mode;

		if ( !S_ISREG(mode) ) {
			return;
		}

		fp = fopen(filepath, "r+");

		p = fgets(buf, MAX_BYTES, fp);

		if (p == NULL) {
			return;
		}

		p = NULL;
		
		sinterpret(buf);

		fclose(fp);
		fp = NULL;		
	}
#endif /* !defined(INTERPRET_C) */
	
