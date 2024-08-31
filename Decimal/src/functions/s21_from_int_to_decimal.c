#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int res = TRUE;
  if (dst) {
    make_zero(dst);
    if (src < 0) {
      src *= -1;
      set_bit(127, 1, dst);
    }
    dst->bits[0] = src;
  } else {
    res = FALSE;
  }
  return res;
}