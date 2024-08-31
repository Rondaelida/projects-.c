#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int result = false;
  int error = false;
  if (src && dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    int sign = getFloatSign(&src), exp = getFloatExp(&src);

    if (isinf(src) || isnan(src)) error = true;

    if (dst && !error && src != 0) {
      double temp = (double)fabs(src);
      int off = 0;
      while (off < 28 && (int)temp / (int)pow(2, 21) == 0) {
        temp *= 10;
        off++;
      }
      temp = round(temp);
      if (off <= 28 && (exp > -94 && exp < 96)) {
        floatbits mant;
        temp = (float)temp;
        while (fmod(temp, 10) == 0 && off > 0) {
          off--;
          temp /= 10;
        }
        mant.fl = temp;
        exp = getFloatExp(&mant.fl);
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--)
          if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
        dst->bits[3] = (sign << 31) | (off << 16);
        result = true;
      }
    }
  }
  return result;
}
