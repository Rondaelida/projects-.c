#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (NULL == result) return 1;

  *result = value;

  big_decimal temp, zero;
  make_zero_bd(&zero);
  temp = decimal_to_big_dec(value);

  if (get_bit(127, value) == 0 && compare_mantiss_only_bd(zero, temp) != 0) {
    set_bit(127, 1, result);
  } else {
    set_bit(127, 0, result);
  }

  return 0;
}
