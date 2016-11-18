CFLAGS=-std=c99 -Wall -Wextra -Werror

proj2: proj2.c
	gcc $(CFLAGS) proj2.c -lm -o proj2

clean:
	rm proj2 proj2.o
