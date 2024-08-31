#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int result = true;
  if (!is_zero(src) && dst) {
    double temp = 0;
    int off = 0;
    for (int i = 0; i < 96; i++)
      if ((src.bits[i / 32] & (1 << i % 32)) != 0) temp += pow(2, i);
    if ((off = (src.bits[3] & ~SIGN) >> 16) > 0) {
      for (int i = off; i > 0; i--) temp /= 10.0;
    }
    *dst = (float)temp;
    *dst *= src.bits[3] >> 31 ? -1 : 1;
    result = false;
  }
  return result;
}