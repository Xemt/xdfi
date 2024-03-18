# Xemt 3/18/24. Customize the output path yourself.

CC = clang
CFLAGS = -O0 -v -pedantic -Wall -Weverything -Wextra

xdfi:
	$(CC) $(CFLAGS) -std=c99 main.c -o xdfi

.PHONY: clean

clean: xdfi
	rm xdfi
