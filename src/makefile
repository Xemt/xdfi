# Xemt <https://github.com/Xemt>, 3/18/24 - 7/10/24.

CC = clang
CFLAGS = -O0 -v -pedantic -Wall -Weverything -Wextra -Wno-unsafe-buffer-usage -Wno-disabled-macro-expansion

# Customize this yourself.
OUTPUT_BIN = ./xdfi

xdfi:
	$(CC) $(CFLAGS) -std=c99 main.c -o $(OUTPUT_BIN)

.PHONY: clean

clean: $(OUTPUT_BIN)
	rm $(OUTPUT_BIN)
