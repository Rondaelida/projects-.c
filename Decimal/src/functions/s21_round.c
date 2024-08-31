#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int return_value = 0;
  if (NULL == result) {
    return_value = 1;
  } else {
    big_decimal temp, temp2, temp3, four, temp0, zero;
    temp = decimal_to_big_dec(value);
    temp.ar_round = 1;
    make_zero_bd(&temp3);
    make_zero_bd(&temp2);
    make_zero_bd(&four);
    make_zero_bd(&zero);
    make_zero(result);
    temp3 = temp;
    temp3.ar_round = 0;
    four.bits[0] = 4;

    temp0 = get_mantissa_with_scale_bd(0, temp);
    temp2 = get_mantissa_with_scale_bd(1, temp3);
    // получаем старшый десяток, если он = 4, то truncate
    temp3 = get_mantissa_with_scale_bd(0, temp3);
    increase_in_degree_bd(temp2.scale, temp3.scale, &temp3);
    temp3 = simple_help_minus_bd(temp2, temp3);

    if (compare_mantiss_only_bd(temp3, four) == 0) {
      make_zero_bd(&temp0);
      temp.ar_round = 0;
      temp0 = get_mantissa_with_scale_bd(0, temp);
    }
    if (compare_mantiss_only_bd(temp0, zero) == 0) {
      temp0.sign = 0;
    }
    big_dec_to_decimal(temp0, result);
  }
  return return_value;
}
