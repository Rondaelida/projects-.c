#include "../s21_decimal.h"

/**
 * Функция сравнивает два числа типа s21_decimal {value_1} и {value_2}
 * @param value_1 первое число
 * @param value_2 второе число
 * @return возвращет 1, если {value_1} < {value_2}, 0 если {value_1} >=
 * {value_2}
 */
int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  int dec_comparison = 0;
  big_decimal dec1_convert, dec2_convert;
  dec1_convert = decimal_to_big_dec(dec1);
  dec2_convert = decimal_to_big_dec(dec2);
  if (s21_control_zero(dec1_convert) || s21_control_zero(dec2_convert)) {
    if (!s21_control_sign(dec1_convert, dec2_convert, &dec_comparison)) {
      if (dec1_convert.scale != dec2_convert.scale) {
        s21_introdution_to_common_den(&dec1_convert, &dec2_convert, 1);
      }
      int flag_not_equal = 1;
      for (int i = 223; i >= 0; i--) {
        if (get_bit_bd(i, dec1_convert) + get_bit_bd(i, dec2_convert) == 1) {
          if (get_bit_bd(i, dec2_convert) > get_bit_bd(i, dec1_convert)) {
            dec_comparison = 1;
            flag_not_equal = 0;
          } else {
            flag_not_equal = 0;
          }
          break;
        }
      }
      if (dec1_convert.sign && dec2_convert.sign && !flag_not_equal)  // ??
        dec_comparison = !dec_comparison;
    }
  }
  return dec_comparison;
}