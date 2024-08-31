CC = gcc
FLAG_COV = --coverage
FLAG_ER = -Wall -Werror -Wextra -std=c11
s21_MATH_C = s21_*.c 
s21_MATH_O = s21_*.o
SUITE_CASES_C = suites/suite_*.c
SUITE_CASES_O = suite_*.o

all: s21_math.a

s21_math.a:
	$(CC) -c $(FLAG_ER) s21_math.h $(s21_MATH_C) 
	ar rc s21_math.a $(s21_MATH_O)
	ranlib s21_math.a

test: s21_math.a
	$(CC) -c $(FLAG_ER) $(SUITE_CASES_C) test.h test.c
	ar rc suite_cases.a $(SUITE_CASES_O) test.o
	ranlib suite_cases.a
	$(CC) $(FLAG_ER) $(FLAG_COV) -o test s21_math.a suite_cases.a $(s21_MATH_C) test.o -lcheck
	./test

gcov_report: test
	gcov s21_*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details -o report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt *.gch
	-rm -f test
	-rm -f report
	find . -type d -name 'test.dSYM' -exec rm -r {} +