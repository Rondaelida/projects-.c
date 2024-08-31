#include "../s21_decimal.h"

/**
 * Функция зануляет структуру большое число {big_value} и возвращает ее
 * @param big_value структура типа s21_decimal, которую будем занулять
 * return возвращает зануленную структуру
 */
int make_zero_bd(big_decimal *big_value) {
  int return_value = 0;
  if (NULL == big_value) {
    return_value = -1;
  }
  for (int i = 0; i <= SIZE_OF_BD; i++) {
    big_value->bits[i] = 0;
  }
  big_value->scale = 0;
  big_value->sign = 0;
  big_value->ar_round = 1;
  big_value->bnk_round = 0;
  return return_value;
}

/**
 * Функция преобразует число {value} из типа s21_decimal в
 * big_decimal и полученное число записывает в переменную {big_value}
 * @param value переменная типа s21_decimal, которую преобразауем
 * @param big_value переменная типа big_decimal, в которую запишется
 * преобразованное число
 * @return возвращет преобразованнуб переменную типа big_decimal
 */
big_decimal decimal_to_big_dec(s21_decimal value) {
  big_decimal big_value;
  make_zero_bd(&big_value);
  for (int i = 0; i < 3; i++) {
    big_value.bits[i] = value.bits[i];
  }
  big_value.scale = get_scale(value);
  big_value.sign = get_bit(127, value);
  return big_value;
}

/**
 * Функция преобразует число {big_value} из типа big_decimal в
 * s21_decimal и полученное число записывает в переменную {value}
 * @param big_value переменная типа big_decimal, которую преобразауем
 * @param value переменная типа s21_decimal, в которую запишется
 * преобразованное число
 */
int big_dec_to_decimal(big_decimal big_value, s21_decimal *value) {
  make_zero(value);
  for (int i = 0; i < 3; i++) {
    value->bits[i] = big_value.bits[i];
  }
  set_scale(big_value.scale, value);
  set_bit(127, big_value.sign, value);

  return 0;
}

big_decimal get_mantissa_with_scale_bd(int new_scale, big_decimal big_value) {
  if (new_scale >= 0) {
    int old_scale = big_value.scale;
    int sign = big_value.sign;
    int ar_round = big_value.ar_round;
    increase_in_degree_bd(new_scale, old_scale, &big_value);

    big_value.scale = new_scale;
    big_value.sign = sign;
    big_value.ar_round = ar_round;
    decrease_in_degree_bd(new_scale, old_scale, &big_value);

    big_value.scale = new_scale;
    big_value.sign = sign;
    big_value.ar_round = ar_round;
  }
  return big_value;
}

/**
 * Функция получает два числа типа big_decimal{decimal_a} {decimal_b} и
 * сравнивает их мантиссы
 * @param decimal_a - первое число
 * @param decimal_b - второе число
 * @return возвращает результат сравнения
 */
int compare_mantiss_only_bd(big_decimal decimal_a, big_decimal decimal_b) {
  int compare = 0;
  for (int i = 32 * SIZE_OF_BD - 1; i >= 0; i--) {
    if (get_bit_bd(i, decimal_a) + get_bit_bd(i, decimal_b) == 1) {
      if (get_bit_bd(i, decimal_a) == 1) {
        compare = 1;
      } else {
        compare = -1;
      }
      break;
    }
  }
  return compare;
}

/**
 * Функция получает бит, находящийся по индексу {index}
 * из числа {decimal} типа s21_decimal
 * @param decimal - откуда получаем бит
 * @param index - по какому интексу хотим получить бит
 * @return возвращает 1 или 0 в зависимости от того
 * какой бит был по искомому индексу
 */
int get_bit_bd(int index, big_decimal decimal) {
  int return_value = 0;
  if (index < 0 or index > 223) {
    return_value = -1;
  }
  int num_of_int = index / 32;
  int index_of_bit = index % 32;
  unsigned int mask = 1 << (index_of_bit);
  if ((decimal.bits[num_of_int] & mask) == 0) {
    return_value = 0;
  } else {
    return_value = 1;
  }
  return return_value;
}

/**
 * Функция увеличения степени
 * @param new_scale подаваемая степень
 * @param old_scale степень big_value
 * @param decimal переменная, в которую запишется результат
 */
void increase_in_degree_bd(int new_scale, int old_scale, big_decimal *decimal) {
  for (int i = 0; i < new_scale - old_scale; i++) {
    big_decimal decimal_ten;
    big_decimal sum;
    make_zero_bd(&sum);
    make_zero_bd(&decimal_ten);
    decimal_ten.bits[0] = 10;
    for (int j = 0; j < 32 * SIZE_OF_BD; j++) {
      if (get_bit_bd(j, *decimal) == 1) {
        sum = simple_help_plus_bd(sum, decimal_ten);
      }
      shift_to_left_bd(&decimal_ten);
    }
    *decimal = sum;
  }
}

/**
 * Функция получает два числа типа big_decimal{decimal_a} {decimal_b} и
 * складывает их
 * @param decimal_a - первое число
 * @param decimal_b - второе число
 * @return возвращает сумму {decimal_a} и {decimal_b}
 */
big_decimal simple_help_plus_bd(big_decimal decimal_a, big_decimal decimal_b) {
  big_decimal sum;
  make_zero_bd(&sum);
  int buffer = 0;
  for (int i = 0; i < 32 * SIZE_OF_BD; i++) {
    buffer = buffer + get_bit_bd(i, decimal_a) + get_bit_bd(i, decimal_b);
    if (buffer % 2 == 0)
      set_bit_bd(i, 0, &sum);
    else
      set_bit_bd(i, 1, &sum);
    if (buffer > 1)
      buffer = 1;
    else
      buffer = 0;
  }
  sum.scale = decimal_a.scale;
  sum.sign = decimal_a.sign;
  sum.ar_round = decimal_a.ar_round;
  return sum;
}

/**
 * Функция получает и устанавливает бит {bit} по индексу {index} в числе
 * {dst} типа s21_decimal
 * @param index по какому интексу устанавливаем бит
 * @param value какой бит необходимо установить (0 или 1)
 * @param decimal куда устанавливаем бит
 */
int set_bit_bd(int index, int value, big_decimal *decimal) {
  int return_value = 0;
  if (index < 0 or index > 223 || (value != 0 && value != 1) ||
      decimal == NULL) {
    return_value = -1;
  }
  int num_of_int = index / 32;
  int index_of_bit = index % 32;
  unsigned int mask = 1 << (index_of_bit);
  if (value == 1)
    decimal->bits[num_of_int] |= mask;
  else
    decimal->bits[num_of_int] &= (~mask);
  return return_value;
}

/**
 * Функция сдвигает число {decimal} побитово влево
 * @param decimal число, которое будем сдвигать
 * @return 1 если потеря битов при сдвиге, -1 если сдвига не было,
 * 0 при успешном выполнении
 */
int shift_to_left_bd(big_decimal *decimal) {
  int return_code = 0;
  if (NULL == decimal) {
    return_code = -1;
  }
  if (get_bit_bd(223, *decimal)) {
    return_code = +1;
  }
  int high_bit_of_0 = get_bit_bd(31, *decimal);
  int high_bit_of_1 = get_bit_bd(63, *decimal);
  int high_bit_of_2 = get_bit_bd(95, *decimal);
  int high_bit_of_3 = get_bit_bd(127, *decimal);
  int high_bit_of_4 = get_bit_bd(159, *decimal);
  int high_bit_of_5 = get_bit_bd(191, *decimal);

  (decimal->bits[0]) <<= 1;
  decimal->bits[1] <<= 1;
  decimal->bits[2] <<= 1;
  decimal->bits[3] <<= 1;
  decimal->bits[4] <<= 1;
  decimal->bits[5] <<= 1;
  decimal->bits[6] <<= 1;

  set_bit_bd(32, high_bit_of_0, decimal);
  set_bit_bd(64, high_bit_of_1, decimal);
  set_bit_bd(96, high_bit_of_2, decimal);
  set_bit_bd(128, high_bit_of_3, decimal);
  set_bit_bd(160, high_bit_of_4, decimal);
  set_bit_bd(192, high_bit_of_5, decimal);

  return return_code;
}
/**
 * Функция уменьшения степени
 * @param new_scale подаваемая степень
 * @param old_scale степень big_value
 * @param decimal переменная, в которую запишется результат
 */
void decrease_in_degree_bd(int new_scale, int old_scale, big_decimal *decimal) {
  big_decimal sum;
  make_zero_bd(&sum);

  for (int i = 0; i < old_scale - new_scale; i++) {
    big_decimal result, multiplication, copy_of_decimal = *decimal,
                                        decimal_NINE;
    make_zero_bd(&result);
    result.scale = old_scale;
    result.ar_round = decimal->ar_round;
    make_zero_bd(&multiplication);
    multiplication.bits[0] = 10;
    make_zero_bd(&decimal_NINE);
    decimal_NINE.bits[0] = 9;
    while (compare_mantiss_only_bd(copy_of_decimal, decimal_NINE) > 0) {
      int s = 0;
      make_zero_bd(&multiplication);
      multiplication.bits[0] = 10;
      for (;; s++) {
        big_decimal buffer = multiplication;
        shift_to_left_bd(&buffer);
        if (compare_mantiss_only_bd(buffer, copy_of_decimal) <= 0)
          shift_to_left_bd(&multiplication);
        else
          break;
      }
      set_bit_bd(s, 1, &result);
      copy_of_decimal = simple_help_minus_bd(copy_of_decimal, multiplication);
    }
    if (i != old_scale - new_scale - 1)
      sum = simple_help_plus_bd(sum, copy_of_decimal);
    big_decimal decimal_five;
    make_zero_bd(&decimal_five);
    decimal_five.bits[0] = 5;
    result.ar_round = decimal->ar_round;
    result.bnk_round = decimal->bnk_round;
    if (compare_mantiss_only_bd(copy_of_decimal, decimal_five) >= 0 &&
        result.ar_round == 1) {
      big_decimal decimal_one;
      make_zero_bd(&decimal_one);
      decimal_one.bits[0] = 1;
      result = simple_help_plus_bd(result, decimal_one);
    }
    if ((i == old_scale - new_scale - 1) &&
        ((compare_mantiss_only_bd(copy_of_decimal, decimal_five) > 0) ||
         (compare_mantiss_only_bd(copy_of_decimal, decimal_five) == 0 &&
          get_bit_bd(0, result) == 1) ||
         (compare_mantiss_only_bd(copy_of_decimal, decimal_five) == 0 &&
          s21_control_zero(sum))) &&
        result.ar_round == 0 && result.bnk_round == 1) {
      big_decimal decimal_one;
      make_zero_bd(&decimal_one);
      decimal_one.bits[0] = 1;
      result = simple_help_plus_bd(result, decimal_one);
    }
    *decimal = result;
  }
}
/**
 * Функция получает два числа типа big_decimal decimal_a} {decimal_b} и вычитает
 * их
 * @param decimal_a - первое число
 * @param decimal_b - второе число
 * @return возвращает разницу {decimal_a} и {decimal_b}
 */
big_decimal simple_help_minus_bd(big_decimal decimal_a, big_decimal decimal_b) {
  big_decimal difference;
  make_zero_bd(&difference);
  for (int i = 0; i < 32 * SIZE_OF_BD; i++) {
    if (get_bit_bd(i, decimal_a) == 0 and get_bit_bd(i, decimal_b) == 1) {
      for (int j = i + 1; j < 32 * SIZE_OF_BD; j++) {
        if (get_bit_bd(j, decimal_a) == 1) {
          set_bit_bd(j, 0, &decimal_a);
          break;
        } else {
          set_bit_bd(j, 1, &decimal_a);
        }
      }
      set_bit_bd(i, 1, &difference);
    } else {
      set_bit_bd(i, get_bit_bd(i, decimal_a) - get_bit_bd(i, decimal_b),
                 &difference);
    }
  }
  return difference;
}

/**
 * Функция получает два числа типа s21_decimal{decimal_a} {decimal_b} и
 * складывает их
 * @param decimal_a - первое число
 * @param decimal_b - второе число
 * @return возвращает сумму {decimal_a} и {decimal_b}
 */
s21_decimal simple_help_plus(s21_decimal decimal_a, s21_decimal decimal_b) {
  s21_decimal sum;
  make_zero(&sum);
  int buffer = 0;
  for (int i = 0; i < 96; i++) {
    buffer = buffer + get_bit(i, decimal_a) + get_bit(i, decimal_b);
    if (buffer % 2 == 0)
      set_bit(i, 0, &sum);
    else
      set_bit(i, 1, &sum);
    if (buffer > 1)
      buffer = 1;
    else
      buffer = 0;
  }
  sum.bits[3] = decimal_a.bits[3];
  return sum;
}
