#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int out_value = 0;
  big_decimal value_1_convert, value_2_convert;
  value_1_convert = decimal_to_big_dec(value_1);
  value_2_convert = decimal_to_big_dec(value_2);
  make_zero(&(*result));
  if (value_1_convert.scale != value_2_convert.scale) {
    s21_introdution_to_common_den(&value_1_convert, &value_2_convert, 0);
  }
  if (!value_1_convert.sign && !value_2_convert.sign) {
    big_decimal result_convert = decimal_to_big_dec(*result);
    if (s21_is_less(value_1, value_2)) {
      big_decimal exchange = value_1_convert;
      value_1_convert = value_2_convert;
      value_2_convert = exchange;
      result_convert.sign = 1;
    }
    for (int i = 0; i < 224; i++) {
      if (get_bit_bd(i, value_1_convert) == 0 and
          get_bit_bd(i, value_2_convert) == 1) {
        for (int j = i + 1; j < 224; j++) {
          if (get_bit_bd(j, value_1_convert) == 1) {
            set_bit_bd(j, 0, &value_1_convert);
            break;
          } else
            set_bit_bd(j, 1, &value_1_convert);
        }
        set_bit_bd(i, 1, &result_convert);
      } else
        set_bit_bd(
            i, get_bit_bd(i, value_1_convert) - get_bit_bd(i, value_2_convert),
            &result_convert);
    }
    result_convert.ar_round = 0;
    result_convert.bnk_round = 1;
    result_convert.scale = value_1_convert.scale;
    out_value = s21_transform_to_96_bit(&result_convert);
    big_dec_to_decimal(result_convert, &(*result));
  } else if (get_bit(127, value_1) && get_bit(127, value_2)) {
    set_bit(127, 0, &value_2);
    set_bit(127, 0, &value_1);
    s21_sub(value_2, value_1, &(*result));
  } else if (!get_bit(127, value_1) && get_bit(127, value_2)) {
    set_bit(127, 0, &value_2);
    out_value = s21_add(value_2, value_1, &(*result));
  } else if (get_bit(127, value_1) && !get_bit(127, value_2)) {
    set_bit(127, 0, &value_1);
    out_value = s21_add(value_2, value_1, &(*result));
    if ((*result).bits[0] != 0 || (*result).bits[1] != 0 ||
        (*result).bits[2] != 0)
      set_bit(127, 1, &(*result));
    if (out_value == 1) out_value = 2;
  }
  return out_value;
}
