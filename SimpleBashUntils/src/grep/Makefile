CC = gcc
CF =-Wall -Werror -Wextra

all: s21_grep

s21_grep : s21_grep.c
	$(CC) $(CF) option_grep.h s21_grep.c -o s21_grep

clean:
	rm s21_grep
	rm -rf *.o

rebuild: all clean