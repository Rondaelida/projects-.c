#include "../s21_decimal.h"

/**
 * Округляет указанное Decimal число до ближайшего
 * целого числа в сторону отрицательной бесконечности.
 * @param value число типа decimal
 * @param result переменная, в которое запишется новое число без дробной части
 * @return 0 - ОК, 1 - ошибка вычисления
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
  int return_value = 0;
  if (NULL == result) {
    return_value = 1;
  } else {
    big_decimal temp, temp2, zero;
    make_zero_bd(&zero);
    temp = decimal_to_big_dec(value);
    temp.ar_round = 0;

    make_zero(result);
    if ((compare_mantiss_only_bd(temp, zero)) == 0) {
      temp2 = zero;
    } else {
      temp2 = get_mantissa_with_scale_bd(0, temp);

      big_decimal decimal_one;
      make_zero_bd(&decimal_one);
      decimal_one.bits[0] = 1;

      if (temp.sign && (compare_mantiss_only_bd(
                           simple_help_minus_bd(temp2, temp), zero)) != 0) {
        temp2 = simple_help_plus_bd(temp2, decimal_one);
        temp2.sign = 1;
      }
    }
    big_dec_to_decimal(temp2, result);
  }

  return return_value;
}
