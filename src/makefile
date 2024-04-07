# Xemt 3/18/24 - 4/7/24.

CC = clang
CFLAGS = -O0 -v -pedantic -Wall -Weverything -Wextra

# Customize this yourself.
OUT_BIN = ./xdfi

xdfi:
	$(CC) $(CFLAGS) -std=c99 main.c -o $(OUT_BIN)

.PHONY: clean

clean: $(OUT_BIN)
	rm $(OUT_BIN)
