/* Xemt, 3/18/24. */

#pragma once

#if !defined(INTERPRET_C)
#	define INTERPRET_C
	
#	include <sys/stat.h>

#	define MAX_BYTES 1024

	/* Deadfish instructions. */
	enum {
		DF_INST_INC = 105,
		DF_INST_DEC = 100,
		DF_INST_SQR = 115,
		DF_INST_OUT = 111
	};

	static int acc;
#	define ACC_MIN -1
#	define ACC_MAX 256

	/* Do something based on the specified
		 character. */
	static void consumech(char c)
	{
		switch (c) {
			case DF_INST_INC:
				acc++;
			break;
			case DF_INST_DEC:
				acc--;
			break;
			case DF_INST_SQR:
				acc = acc * acc;
			break;
			case DF_INST_OUT:
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

	/* Interpret the contents of a file as deadfish
		 code. */
	void finterpret(const char *filepath)
	{
		struct stat st;
		mode_t mode = 0;
		FILE *fp = NULL;
		char buf[MAX_BYTES] = {0};

		if ( stat(filepath, &st) != 0 ) {
			return;
		}

		mode = st.st_mode;

		if ( !S_ISREG(mode) ) {
			return;
		}

		fp = fopen(filepath, "r+");

		(void)fgets(buf, MAX_BYTES, fp);

		sinterpret(buf);

		fclose(fp);
		fp = NULL;		
	}
#endif /* !defined(INTERPRET_C) */
	
