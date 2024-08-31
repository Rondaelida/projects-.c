#ifdef __cplusplus
extern "C" {
#endif
#ifndef S21_CALC_H_
#define S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct first {
  int priority;
  char symbol;
  struct first *next;
} prior;

typedef struct second {
  double value;
  struct second *next;
} val;

// =============================================
//           ОСНОВНЫЕ ФУНКЦИИ
// =============================================

// Функция для парсинга строки и выполнения математических операций
double s21_parser(char *input, double x_value);
// проверка наличия операторов цифр и скобок во входной строке
int s21_check_operators(char *input);
// функция для сравнения строки и мат функций -> пуш
void s21_func_calc(prior **top, char *func_res);
// проверка при обработке и вычислении арифметических выражений
void s21_operator_calc(prior **top, char operator_res);
// считаем ))
double s21_calculating(char *output);
// проверка входных данных
int s21_input_data(char *input);

// =============================================
//           ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// =============================================

// проврка инпута на число
int is_digit(char *input);
// проврка инпута на оператора
char is_operator(char *input);
// проверка импута на функции
char *is_function(char *input);
// Функция для добавления нового элемента в стек
void push(prior **top, int priority, char symbol);
// Функция для извлечения элемента из стека и возврата его символа
char pop(prior **top);
// возвращаем верхний элемент стека
int peek(const prior *top);
// функция для приоритета оператора
int peek_priority(char operator_res);
// Функция для добавления нового элемента в стек_2
void push_second(val **top, double value);
// Функция для извлечения элемента из стека_2 и возврата его символа
double pop_second(val **top);
// считаем операторы
double calculating_operators(double a, double b, char symbol);
// считаем функции
double calculating_functions(double a, char function);

#endif
#ifdef __cplusplus
}
#endif