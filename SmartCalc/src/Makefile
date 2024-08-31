.PHONY: s21_calc.a test gcov_report install uninstall dist dvi check rebuild clean

CC = gcc -Wall -Wextra -Werror -std=c11 -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt
HEADERS = s21_calc.h
SOURCES = $(wildcard *.c)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
endif

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

all: s21_calc.a test

s21_calc.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_calc.a $(OBJ_LIBRARY)
	ranlib s21_calc.a
	rm -rf *.o

test: s21_calc.a TEST/s21_smart_calc_test.c
ifeq ($(OS), Darwin)
	$(CC) TEST/s21_smart_calc_test.c s21_calc.a -o test.out $(LIBS)
else
	$(CC) TEST/s21_smart_calc_test.c s21_calc.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out


gcov_report: s21_calc.a TEST/s21_smart_calc_test.c
ifeq ($(OS), Darwin)
	gcc $(GCOVFLAGS) TEST/s21_smart_calc_test.c $(SOURCES) -o report.out $(LIBS)
else
	gcc $(GCOVFLAGS) TEST/s21_smart_calc_test.c $(SOURCES) -o report.out $(LINUX)
endif
	./report.out
	lcov -t "gcov_report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html

install:
	make clean
	mkdir build
	cd smartcalc && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/smartcalc.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/SmartCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/

dvi:
	open readme_calc.md


check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n TEST/*.c
	rm -rf .clang-format
	#cppcheck *.c
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean
rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf $(EXECUTABLE)
	rm -rf Archive_SmartCalc_v1.0
	rm -rf *tgz
	rm -rf build
	rm -rf gcov_test
