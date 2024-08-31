#include "../s21_decimal.h"

bool is_zero(s21_decimal decimal) {
  return decimal.bits[0] == 0 and decimal.bits[1] == 0 and decimal.bits[2] == 0;
}

/**
 * Функция сравнивает два числа типа s21_decimal {value_1} и {value_2}
 * @param value_1 первое число
 * @param value_2 второе число
 * @return возвращет 1, если {value_1} == {value_2}, 0 если {value_1} !=
 * {value_2}
 */
int s21_is_equal(s21_decimal decimal_a, s21_decimal decimal_b) {
  if (is_zero(decimal_a) and is_zero(decimal_b)) return 1;
  big_decimal decimal_a_convert, decimal_b_convert;
  decimal_a_convert = decimal_to_big_dec(decimal_a);
  decimal_b_convert = decimal_to_big_dec(decimal_b);
  s21_introdution_to_common_den(&decimal_a_convert, &decimal_b_convert, 1);
  int dec_comprasion =
      decimal_a_convert.bits[0] == decimal_b_convert.bits[0] and
      decimal_a_convert.bits[1] == decimal_b_convert.bits[1] and
      decimal_a_convert.bits[2] == decimal_b_convert.bits[2] and
      decimal_a_convert.bits[3] == decimal_b_convert.bits[3] and
      decimal_a_convert.bits[4] == decimal_b_convert.bits[4] and
      decimal_a_convert.bits[5] == decimal_b_convert.bits[5] and
      decimal_a_convert.bits[6] == decimal_b_convert.bits[6];
  if ((decimal_a_convert.sign > decimal_b_convert.sign) ||
      (decimal_b_convert.sign > decimal_a_convert.sign))
    dec_comprasion = 0;
  return dec_comprasion;
}
