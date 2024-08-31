#include "s21_calc.h"

//=====================================================================
// Функция для парсинга строки и выполнения математических операций
//                         РЕЙДБОСС
//=====================================================================
double s21_parser(char *input, double x_value) {
  double result = 0;
  // память для промежуточных результатов
  char *output = calloc(512, sizeof(char));
  // проверка для корректности входных данных
  if (!s21_input_data(input)) {
    char x_str[256] = "\0";
    snprintf(x_str, 255, "%lf", x_value);
    prior *top = NULL;
    int digit_result = 0;
    char operator_result = 0;
    char *func_result = NULL;
    char pop_result = 0;
    char last_symbol = ' ';
    char *digit = calloc(512, sizeof(char));
    int j = 0, i = 0, dot_count = 0;
    // перебираем входную строку
    while (*input) {
      // для чисел
      digit_result = is_digit(input);
      // для операторов
      operator_result = is_operator(input);
      // для функций
      func_result = is_function(input);
      // если перед скобкой - или +
      if (top != NULL && last_symbol == '(' &&
          (operator_result == '-' || operator_result == '+')) {
        output[i++] = '0';
        output[i++] = ' ';
      }
      // если ошибка
      if (func_result != NULL) {
        if (strncmp(func_result, "error", 5) == 0) {
          output = NULL;
          func_result = NULL;
          break;
        }
        // идём по строке дальше
        input += (strlen(func_result) - 1);
        // если уже было умножение
        if (strncmp(func_result, "mod", 3) == 0) {
          operator_result = 'm';
          func_result = NULL;
        }
        if (func_result != NULL) {
          // Если есть результат функции, вызываем функцию вычисления
          s21_func_calc(&top, func_result);
        }
      }
      // Добавляем цифру к числу
      if (digit_result == 1) {
        digit = strncat(digit, input, 1);
      }
      if (digit_result == 2) {
        if (dot_count == 0) {
          // Добавляем цифру к числу, если не была встречена точка
          digit = strncat(digit, input, 1);
          dot_count++;
        }
      }
      if (digit_result == 3) {
        for (j = 0; j < (int)strlen(x_str); j++) {
          // Добавляем цифры из строки в вывод
          output[i++] = x_str[j];
        }
        // Добавляем пробел
        output[i++] = ' ';
      }
      if (digit_result == 0 && strlen(digit) > 0) {
        // Добавляем число из переменной "digit" в вывод
        for (j = 0; j < (int)strlen(digit); j++) output[i++] = digit[j];
        // Сбрасываем счетчик точек
        dot_count = 0;
        // Добавляем пробел
        output[i++] = ' ';
        // Обнуляем строку с числом
        digit[0] = '\0';
      }
      if (operator_result != 0) {
        if (operator_result == ')') {
          // Обрабатываем закрывающую скобку
          while (top != NULL && peek_priority(operator_result) <= peek(top)) {
            // Извлекаем элемент из стека
            pop_result = pop(&top);
            if (pop_result != '(') {
              // Добавляем оператор в
              output[i++] = pop_result;
              // Добавляем пробел
              output[i++] = ' ';
            }
            if (pop_result == '(') {
              break;
            }
          }
        } else {
          // Обрабатываем другие операторы
          if (operator_result != '(') {
            while (top != NULL && peek_priority(operator_result) <= peek(top)) {
              // Извлекаем элемент из стека
              pop_result = pop(&top);
              if (pop_result != '(') {
                // Добавляем оператор в вывод
                output[i++] = pop_result;
                // Добавляем пробел
                output[i++] = ' ';
              }
              if (pop_result == '(') {
                break;
              }
            }
          }
        }
        // Вызываем функцию для вычисления оператора
        s21_operator_calc(&top, operator_result);
      }
      // Сохраняем последний символ
      last_symbol = operator_result;
      // Переходим к следующему символу
      input++;
    }
    if (output != NULL) {
      // Если есть незавершенное число, добавляем его в вывод
      if (digit[0] != '\0') {
        for (j = 0; j < (int)strlen(digit); j++, i++) {
          output[i] = digit[j];
          output[i++] = ' ';
        }
      }
      // Извлекаем оставшиеся элементы из стека
      while (top != NULL) {
        pop_result = pop(&top);
        if (pop_result != '(') {
          // Добавляем оператор в вывод
          output[i++] = pop_result;
          // Добавляем пробел
          output[i++] = ' ';
        }
      }
    }
    // Вычисляем результат
    result = s21_calculating(output);
    // Освобождаем память, выделенную под числа
    free(digit);
    // Освобождаем память, выделенную под стек
    free(top);
    // Освобождаем память, выделенную для результата функции
    free(func_result);
  }
  // Освобождаем память, выделенную под вывод
  free(output);
  return result;
}

// проверка входных данных
int s21_input_data(char *input) {
  int result = 0;
  // считаем длинну строки
  int len = (int)strlen(input);
  // проверяем что не больше памяти
  if (len > 255) {
    result = 1;
  }
  if (result == 0) {
    // переменная для отслеживания скобок
    int bracket = 0;
    // переменная для проверки наличия разрешенных символов
    int possible;
    // массив
    char normal_symbols[40] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                               '9', '+', '-', '(', ')', '*', '/', '^', '=',
                               'a', 'c', 'd', 'o', 's', 't', 'i', 'q', 'r',
                               'n', 'l', 'm', 'x', 'g', '.', ' '};
    while (*input) {
      // Инициализируем переменную для проверки наличия разрешенных символов
      possible = 0;
      for (size_t j = 0; j < strlen(normal_symbols); j++) {
        if (*input == normal_symbols[j]) {
          possible = 1;
        }
      }
      if (possible == 0) {
        result = 1;
        break;
      }
      // Обновляем счетчик скобок
      if (*input == '(') {
        bracket++;
      }
      if (*input == ')') {
        bracket--;
      }
      // проверяем операторы
      result += s21_check_operators(input);
      input++;
    }
    if (bracket != 0) {
      result = 1;
    }
  }
  return result + 0.0;
}

// проверка наличия операторов цифр и скобок во входной строке
int s21_check_operators(char *input) {
  int result = 0;
  static int operation_count = 0;
  static int digit_count = 0;
  static int bracket_count = 0;
  static int counter = 0;
  // Проверяем, является ли текущий символ оператором
  char isop = is_operator(input);
  // Проверяем, является ли текущий символ цифрой
  int isdig = is_digit(input);
  // Проверяем входные символы и обновляем счетчики
  if (isdig != 0 && isop != '(' && isop != ')') {
    operation_count++;
    digit_count = 0;
  }
  if (isop == '(' || isop == ')') {
    digit_count = 0;
  }
  if (isdig > 0) {
    digit_count++;
    operation_count = 0;
  }
  // Обрабатываем скобки и операторы
  if (isop == '(') {
    bracket_count++;
  } else if ((isop == '-' || isop == '+') && bracket_count > 0 &&
             counter == 0) {
    operation_count--;
    counter++;
  } else if (isop == ')') {
    bracket_count = 0;
    counter = 0;
  }
  if (operation_count > 1 && digit_count == 0) {
    result = 1;
  }
  return result;
}

// функция для сравнения строки и мат функций
void s21_func_calc(prior **top, char *func_res) {
  if (strcmp(func_res, "sin") == 0) {
    push(top, 4, 'q');
  }
  if (strcmp(func_res, "cos") == 0) {
    push(top, 4, 'w');
  }
  if (strcmp(func_res, "tan") == 0) {
    push(top, 4, 'e');
  }
  if (strcmp(func_res, "asin") == 0) {
    push(top, 4, 'r');
  }
  if (strcmp(func_res, "acos") == 0) {
    push(top, 4, 't');
  }
  if (strcmp(func_res, "atan") == 0) {
    push(top, 4, 'y');
  }
  if (strcmp(func_res, "sqrt") == 0) {
    push(top, 4, 'u');
  }
  if (strcmp(func_res, "ln") == 0) {
    push(top, 4, 'i');
  }
  if (strcmp(func_res, "log") == 0) {
    push(top, 4, 'o');
  }
}

// проверка при обработке и вычислении арифметических выражений
void s21_operator_calc(prior **top, char operator_res) {
  if (operator_res == '+') {
    push(top, 1, '+');
  }
  if (operator_res == '-') {
    push(top, 1, '-');
  }
  if (operator_res == '*') {
    push(top, 2, '*');
  }
  if (operator_res == '/') {
    push(top, 2, '/');
  }
  if (operator_res == 'm') {
    push(top, 2, 'm');
  }
  if (operator_res == '^') {
    push(top, 3, '^');
  }
  if (operator_res == '(') {
    push(top, 0, '(');
  }
}

// считаем))
double s21_calculating(char *output) {
  double result;
  double calc_operation_result = 0;
  double calc_function_result = 0;
  val *val = NULL;
  while (*output) {
    // Если текущий символ является цифрой
    if (is_digit(output) == 1) {
      // Добавляем текущее значение в стек val
      push_second(&val, atof(output));
      // Пока текущий символ не является пробелом
      while (*output != ' ') {
        // Переходим к следующему символу
        output++;
      }
      continue;
    }
    // Если текущий символ является оператором или 'm' и не является пробелом
    if ((is_operator(output) != 0 || *output == 'm') && *output != ' ') {
      // Вычисляем результат операции над двумя значениями из стека val
      calc_operation_result =
          calculating_operators(pop_second(&val), pop_second(&val), *output);
      // Добавляем результат в стек val
      push_second(&val, calc_operation_result);
    }
    // Если текущий символ является буквой между a и z и не является 'm' или
    // пробелом
    if (*output >= 'a' && *output <= 'z' && *output != 'm' && *output != ' ') {
      // Вычисляем результат функции над значением из стека val
      calc_function_result = calculating_functions(pop_second(&val), *output);
      // Добавляем результат в стек val
      push_second(&val, calc_function_result);
    }
    // Переходим к следующему символу в строке output
    output++;
  }
  // Получаем результат из вершины стека val
  result = pop_second(&val);
  // Цикл, пока стек val не станет пустым
  while (val != NULL) {
    // Извлекаем элемент из стека
    pop_second(&val);
  }
  return result;
}

// =============================================
//           ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// =============================================

// проврка инпута на число
int is_digit(char *input) {
  int result = 0;
  char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (size_t i = 0; i < strlen(digits); i++) {
    if (*input == digits[i]) {
      result = 1;
    }
  }
  if (*input == '.') {
    result = 2;
  }
  if (*input == 'x') {
    result = 3;
  }
  return result;
}

// проврка инпута на оператора
char is_operator(char *input) {
  char result = 0;
  char operators[7] = {'+', '-', '*', '/', '(', ')', '^'};
  for (size_t i = 0; i < strlen(operators); i++) {
    if (*input == operators[i]) {
      result = operators[i];
    }
  }
  return result;
}

// проверка импута на функции
char *is_function(char *input) {
  char *result = NULL;
  if (*input == 'l') {
    if (strncmp(input, "ln", 2) == 0) {
      result = "ln";
    } else if (strncmp(input, "log", 3) == 0) {
      result = "log";
    } else {
      result = "error";
    }
  }
  if (*input == 'm') {
    if (strncmp(input, "mod", 3) == 0) {
      result = "mod";
    } else {
      result = "error";
    }
  }
  if (*input == 's') {
    if (strncmp(input, "sin", 3) == 0) {
      result = "sin";
    } else if (strncmp(input, "sqrt", 4) == 0) {
      result = "sqrt";
    } else {
      result = "error";
    }
  }
  if (*input == 'c') {
    if (strncmp(input, "cos", 3) == 0) {
      result = "cos";
    } else {
      result = "error";
    }
  }
  if (*input == 't') {
    if (strncmp(input, "tan", 3) == 0) {
      result = "tan";
    } else {
      result = "error";
    }
  }
  if (*input == 'a') {
    if (strncmp(input, "asin", 4) == 0) {
      result = "asin";
    } else if (strncmp(input, "acos", 4) == 0) {
      result = "acos";
    } else if (strncmp(input, "atan", 4) == 0) {
      result = "atan";
    } else {
      result = "error";
    }
  }
  return result;
}

// Функция для добавления нового элемента в стек
void push(prior **top, int priority, char symbol) {
  prior *a = calloc(1, sizeof(prior));
  // Установка приоритета и символа для нового элемента
  a->priority = priority;
  a->symbol = symbol;
  if (*top == NULL) {
    // новый элемент - вершина стека
    *top = a;
  } else {
    // делаем новый элемент вершиной стека
    a->next = *top;
    *top = a;
  }
}

// Функция для извлечения элемента из стека и возврата его символа
char pop(prior **top) {
  char symbol = 0;
  // Проверка, не пуст ли стек
  if (*top != NULL) {
    // Создание указателя на элемент стека для хранения результатов извлечения
    prior *result = NULL;
    result = (*top);
    // Обновление указателя на вершину стека
    (*top) = (*top)->next;
    // Получение символа извлеченного элемента
    symbol = result->symbol;
    free(result);
  }
  return symbol;
}
// возвращаем верхний элемент стека
int peek(const prior *top) { return top->priority; }

// функция для приоритета оператора
int peek_priority(char operator_res) {
  int result = 0;
  if (operator_res == '+') {
    result = 1;
  }
  if (operator_res == '-') {
    result = 1;
  }
  if (operator_res == '*') {
    result = 2;
  }
  if (operator_res == '/') {
    result = 2;
  }
  if (operator_res == 'm') {
    result = 2;
  }
  if (operator_res == '^') {
    result = 3;
  }
  if (operator_res == '(') {
    result = 0;
  }
  if (operator_res == ')') {
    result = 0;
  }
  return result;
}

// Функция для добавления нового элемента в стек_2
void push_second(val **top, double value) {
  val *a = calloc(1, sizeof(val));
  // установка значения для нового элемента
  a->value = value;
  if (*top == NULL) {
    // новый элемент - вершина стека
    *top = a;
  } else {
    // делаем новый элемент вершиной стека
    a->next = *top;
    *top = a;
  }
}

// Функция для извлечения элемента из стека_2 и возврата его символа
double pop_second(val **top) {
  double value = 0;
  if (*top != NULL) {
    // Создание указателя на элемент стека для хранения результатов извлечения
    val *result = NULL;
    result = (*top);
    // Обновление указателя на вершину стека
    // Обновление указателя на вершину стека
    (*top) = (*top)->next;
    // Получение символа извлеченного элемента
    value = result->value;
    free(result);
  }
  return value;
}

// считаем операторы
double calculating_operators(double a, double b, char symbol) {
  double result = 0;
  if (symbol == '+') result = b + a;
  if (symbol == '-') result = b - a;
  if (symbol == '*') result = b * a;
  if (symbol == '/') result = b / a;
  if (symbol == 'm') result = fmod(b, a);
  if (symbol == '^') result = pow(b, a);
  return result;
}

// считаем функции
double calculating_functions(double a, char function) {
  double result = 0;
  if (function == 'q') result = sin(a);
  if (function == 'w') result = cos(a);
  if (function == 'e') result = tan(a);
  if (function == 'r') result = asin(a);
  if (function == 't') result = acos(a);
  if (function == 'y') result = atan(a);
  if (function == 'u') result = sqrt(a);
  if (function == 'i') result = log(a);
  if (function == 'o') result = log10(a);
  return result;
}