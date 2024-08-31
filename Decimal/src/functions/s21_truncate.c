#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (NULL == result) return 1;

  make_zero(result);
  big_decimal temp, zero;
  temp = decimal_to_big_dec(value);
  temp.ar_round = 0;
  make_zero_bd(&zero);

  temp = get_mantissa_with_scale_bd(0, temp);
  if (compare_mantiss_only_bd(temp, zero) == 0) {
    temp.sign = 0;
  }

  big_dec_to_decimal(temp, result);
  return 0;
}
