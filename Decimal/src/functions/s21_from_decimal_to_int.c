#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int res = 1;
  if (!(is_zero(src)) && dst != NULL) {
    *dst = src.bits[0];
    *dst *= get_bit(127, src) ? -1 : 1;
    *dst /= (int)pow(10, get_scale(src));
    res = 0;
  }
  return res;
}