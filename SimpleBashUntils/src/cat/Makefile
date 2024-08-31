CC = gcc
CF =-Wall -Werror -Wextra

all: s21_cat

s21_cat : s21_cat.c
	$(CC) $(CF) option.h s21_cat.c -o s21_cat

clean:
	rm s21_cat
	rm -rf *.o

rebuild: all clean