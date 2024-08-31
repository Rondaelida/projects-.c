OS := $(shell uname -s)
FLAG_OS = -lcheck
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
FLAG_C = -c
FLAG_O = -o
FLAG_COV = --coverage
FLAG_ER = -Wall -Werror -Wextra -g -std=c11 
s21_DECIMAL_C = functions/s21_*.c
s21_DECIMAL_O = s21_*.o
SUITE_CASES_C = tests/s21_test_*.c
SUITE_CASES_O = s21_test_*.o
GCOVFLAGS = -fprofile-arcs -ftest-coverage


ifeq ($(OS), Linux)
FLAG_OS =  -lcheck -lm -lpthread -lsubunit
endif

all: gcov_report

s21_decimal.a:
	$(CC) $(FLAG_C) $(FLAG_ER) s21_decimal.h $(s21_DECIMAL_C) 
	ar rc s21_decimal.a $(s21_DECIMAL_O)
	ranlib s21_decimal.a
test: s21_decimal.a
	$(CC) $(FLAG_C) $(FLAG_ER) $(SUITE_CASES_C) test.h test.c 
	ar rc suite_cases.a $(SUITE_CASES_O) test.o
	ranlib suite_cases.a
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) test s21_decimal.a suite_cases.a $(s21_DECIMAL_C) $(FLAG_OS)  
	./test

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
	gcovr --html-details -o report.html
	open report.html

# gcov_report: test
# 	rm -rf test-s21_help*.gcno test-s21_convert*.gcno	
# 	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
# 	genhtml -o report/ Coverage_Report.info
# 	rm -f *.gcno *.gcda *.info report.out *.gcov
# 	open ./report/index-sort-f.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt *.gch
	-rm -rf test
	-rm -rf report
	-rm -rf tests/gcov tests/obj ../.vscode
	find . -type d -name 'test.dSYM' -exec rm -r {} +
clang:
	clang-format -i *.h *.c 
	clang-format -i functions/s21_*.c
	clang-format -i tests/s21_*.c
	
rebuild: clean all

check_valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./test git 2> valgrind.txt

