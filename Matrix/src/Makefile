OS := $(shell uname -s)
FLAG_OS = -lcheck
CC = gcc
FLAG_ER = -Wall -Werror -Wextra -Wpedantic -std=c11 -g
FLAG_C = -c
FLAG_O = -o
FLAG_COV = --coverage
MATRIX_C = s21_*.c
MATRIX_O = s21_*.o
TESTS_C = test.c
TESTS_O = test.o

ifeq ($(OS), Linux)
FLAG_OS =  -lcheck -lm -lpthread -lsubunit
endif

all: clean s21_matrix.a test

s21_matrix.a: 
	$(CC) $(FLAG_C) $(FLAG_ER) s21_matrix.h $(MATRIX_C)
	ar rcs s21_matrix.a $(MATRIX_O)
	ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) $(FLAG_C) $(FLAG_ER) test.c 
	ar rc suite_cases.a $(TESTS_O) test.o
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) test s21_matrix.a suite_cases.a $(MATRIX_C) $(FLAG_OS)
	./test
	

# gcov_report: test
# 	rm -rf test-s21_help*.gcno test-s21_help*.gcda 	
# 	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
# 	genhtml -o report/ Coverage_Report.info
# 	rm -f *.gcno *.gcda *.info report.out *.gcov
# 	open ./report/index-sort-f.html

gcov_report: test
ifeq ($(OS), Linux)
	gcov test-s21_*.gcda
	rm -rf test-s21_help*.gcno test-s21_convert*.gcno 
else
	gcov s21_*.gcda
	rm -rf s21_help*.gcno s21_convert*.gcno 
endif
	gcovr -b 
	gcovr
	gcovr --html-details -o coverage_report.html
	open coverage_report.html

clean:
	rm -rf *.o *.a *.out .info *.log *.html *.css s*.gc report *.gcno *.gcda *.info *.gch *.gcov test .clang-format *.txt ../.vscode


clang_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h *.c

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h *.c

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all -s --log-file=valgrind.log ./test 
#	leaks -atExit -- ./test



rebuild: all