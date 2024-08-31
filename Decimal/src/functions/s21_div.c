#include "../s21_decimal.h"

/**
 * Функция деления двух чисел типа s21_decimal
 * @param value_1 делимое - число типа s21_decimal
 * @param value_2 делитель -  число типа s21_decimal
 * @param result переменная, в которую запишется результат умножения
 * @return возвращает: 0 - ОК, 1 - число больше максимально возможного или равно
 * INF, 2 - число меньше минимально возможного или равно -INF, 3 - деление на 0
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal big_result, big_copy, big_multiplication;
  make_zero_bd(&big_result);
  big_result.sign = get_bit(127, value_1) ^ get_bit(127, value_2);
  big_result.ar_round = 0;
  big_result.bnk_round = 1;
  big_copy = decimal_to_big_dec(value_1);
  big_multiplication = decimal_to_big_dec(value_2);
  if (s21_control_zero(big_multiplication) == 0) return 3;
  big_decimal big_reminder;
  make_zero_bd(&big_reminder);
  integer_big_div(big_copy, big_multiplication, &big_result, &big_reminder);
  if (s21_control_zero(big_reminder) == 1) {
    big_reminder = get_mantissa_with_scale_bd(28, big_reminder);
    big_result = get_mantissa_with_scale_bd(28, big_result);
    big_decimal big_devided, trash_reminder;
    make_zero_bd(&big_devided);
    make_zero_bd(&trash_reminder);
    integer_big_div(big_reminder, big_multiplication, &big_devided,
                    &trash_reminder);
    big_result = simple_help_plus_bd(big_result, big_devided);
  }
  int new_scale = big_result.scale + get_scale(value_1) - get_scale(value_2);
  big_result.scale = new_scale;
  if (big_result.scale < 0) {
    big_result = get_mantissa_with_scale_bd(0, big_result);
  }
  int error_code = s21_transform_to_96_bit(&big_result);
  if (error_code == 0) big_dec_to_decimal(big_result, result);
  return error_code;
}
