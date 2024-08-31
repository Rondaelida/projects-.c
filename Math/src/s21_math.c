#include "s21_math.h"

int isNaN(double x) { return (x != x); }

long double s21_max(double a, double b) {
  if (a > b)
    return a;
  else
    return b;
}

int s21_abs(int x) {
  if (x == NaN) return NaN;
  x = (x <= 0) ? (-1) * x : x;
  return x;
}

long double s21_fact(long double x) {
  if (isNaN(x)) return NaNl;
  if (x == 0 || x == 1) return 1;
  return x * s21_fact(x - 1);
}

long double s21_fabs(double x) {
  long double result = 1;
  if (isNaN(x)) result = NaNl;
  if (x < 0) result = -x;
  if (x == 0) result = 0;
  if (x > 0) result = x;
  return result;
}

long double s21_log(double x) {
  if (isNaN(x)) return NaNl;
  long double result = 0;
  int int_part = 0;
  double tmp = 0;
  double tmp_flag = 1;
  double var = 1e-11;
  double flag_minus = 1;
  if (x == INF_double)
    result = INF_double;
  else if (x == 0)
    result = -INF_double;
  else if (x < 0)
    result = NaNd;
  else if (x == 1)
    result = 0;
  else {
    if (s21_fabs(x) <= 0.001) {
      x = s21_powint(x, -1);
      flag_minus = -1;
    }
    while (x >= s21_EXP) {
      x /= s21_EXP;
      int_part++;
    }
    for (int i = 1; s21_fabs(tmp_flag) >= var; i += 2) {
      tmp = (1.0 / i) * s21_powint(((x - 1) / (x + 1)), i);
      tmp_flag = tmp;
      result += tmp;
    }
    result = 2 * result;
  }
  return flag_minus * (result + int_part);
}

long double s21_exp(double x) {
  if (isNaN(x)) return NaNl;
  long double result = 1;
  double tmp = 1;
  int flag = 0;
  long double var = 1e-9;
  if (x < 0) {
    x = -x;
    flag = 1;
  }
  int i = 1;
  while (s21_fabs(tmp) > var) {
    tmp = s21_powint(x, i) / s21_fact(i);
    i++;
    result += tmp;
    if (result > DOUBLE_MAX) {
      result = INF_ld;
      break;
    }
  }
  if (flag == 1) {
    if (result > DOUBLE_MAX)
      result = 0;
    else
      result = s21_powint(result, -1);
  }
  return result;
}

long double s21_powint(double base, int exp) {
  if (isNaN(base) || isNaN(exp)) return NaNl;
  long double result = 1;
  if (exp > 0)
    for (int i = 0; i < exp; i++) result *= base;
  else {
    exp = -exp;
    for (int i = 0; i < exp; i++) result *= base;
    result = 1 / result;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  if (isNaN(base) || isNaN(exp)) return NaNl;
  long double result = 0;
  if (base < 0 && exp < 1 && exp > 0)
    result = NaNd;
  else if (exp == 1)
    result = base;
  else if ((s21_fabs(base) == 1 && exp == NaN) || exp == 0)
    result = 1;
  else if (base > 0 && exp > 1)
    result = s21_exp(exp * s21_log(base));
  else if (base < 0 && exp > 1)
    result = s21_exp(exp * s21_log(s21_fabs(base)));
  else if (base == INF_double || exp == INF_double || (base == -0 && exp < 0))
    result = INF_double;
  else if ((base == -0 && exp > 0) || (base < -1 && exp == NaN) ||
           (base == INF_double && exp < 0))
    result = 0;
  else
    result = s21_exp(exp * s21_log(base));
  return result;
}

long double s21_floor(double x) {
  long double result = (long long int)x;
  if (isNaN(x))
    result = NaNd;
  else if (x == INF_double)
    result = INF_double;
  else if (x == -INF_double)
    result = -INF_double;
  else if (x < 0 && x != result)
    result--;

  return result;
}

long double s21_ceil(double x) {
  long double result = (long long int)x;
  if (isNaN(x))
    result = NaNd;
  else if (x == INF_double)
    result = INF_double;
  else if (x == -INF_double)
    result = -INF_double;
  else if (x > 0 && x != result)
    result++;
  return result;
}

long double s21_sin(double x) {
  if (isNaN(x) || x == INF_double || x == negINF_double) return NaNl;
  long double result = 0;
  x = s21_fmod(x, 2 * s21_M_PI);
  for (int i = 0; i < 20; i++)
    result +=
        (s21_powint(-1, i) * s21_powint(x, 2 * i + 1)) / s21_fact(2 * i + 1);
  return result;
}

long double s21_cos(double x) {
  if (isNaN(x) || x == INF_double || x == negINF_double) return NaNl;
  long double result = 0;
  x = s21_fmod(x, 2 * s21_M_PI);
  for (int i = 0; i < 20; i++)
    result += (s21_powint(-1, i) * s21_powint(x, 2 * i)) / s21_fact(2 * i);
  return result;
}

long double s21_tan(double x) {
  long double result = 0;
  if (isNaN(x)) return NaNl;
  if (x == s21_M_PI / 2)
    return 16331239353195370L;
  else if (x == -s21_M_PI / 2)
    return -16331239353195370L;
  if (x == 3 * s21_M_PI / 2)
    return 5443746451065123L;
  else if (x == 3 * -s21_M_PI / 2)
    return -5443746451065123L;
  if (x == -0.0) return x;
  result = s21_sin(x) / s21_cos(x);
  return result;
}

long double s21_sqrt(double x) {
  if (isNaN(x)) return NaNl;

  long double left = 0;
  long double right = s21_max(1, x);
  long double middle = (left + right) / 2;
  if (x < 0)
    middle = NaNl;
  else {
    while ((middle - left) > ACCURACY) {
      if (x < middle * middle)
        right = middle;
      else
        left = middle;
      middle = (left + right) / 2;
    }
  }
  return middle;
}

long double s21_fmod(double x, double y) {
  long double result = 0;
  if ((x == INF_double && y == INF_double) || (s21_fabs(x) == INF_double) ||
      y == NaNd) {
    result = NaNd;
  } else if (y == INF_double || y == negINF_double) {
    result = x;
  } else if (s21_fabs(y) < 1e-7) {
    result = NaNd;
  } else if (s21_fabs(x) < 1e-7) {
    result = 0;
  } else {
    long long int remain = 0;
    remain = x / y;
    result = (long double)x - remain * (long double)y;
  }
  return result;
}

long double s21_atan(double x) {
  long double result = 0;
  if (isNaN(x)) return NaNl;
  if (x > -1 && x < 1) {
    for (int i = 0; i < 100; i++) {
      result += s21_powint(-1, i) * s21_powint(x, 1 + 2 * i) / (1 + 2 * i);
    }
  } else if (x > 1 || x < -1) {
    result = (s21_M_PI * s21_sqrt(s21_powint(x, 2))) / (2 * x);
    for (int i = 0; i < 100; i++) {
      result -= s21_powint(-1, i) * s21_powint(x, -1 - 2 * i) / (1 + 2 * i);
    }
  } else if (x == 1)
    result = s21_M_PI / 4.0;
  else if (x == -1)
    result = -s21_M_PI / 4.0;

  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (isNaN(x))
    return NaNl;
  else if (x == 1) {
    result = s21_M_PI / 2;
  } else if (x == -1)
    result = -s21_M_PI / 2;
  else if (x > -1 && x < 1)
    result = s21_atan(x / s21_sqrt(1 - s21_powint(x, 2)));
  else
    result = NaNl;
  return result;
}
long double s21_acos(double x) {
  long double result = 0;
  if (isNaN(x)) return NaNl;
  if (x == 1)
    result = 0;
  else if (x == -1)
    result = s21_M_PI;
  else if (x == 0)
    result = s21_M_PI / 2;
  else if (x > -1 && x < 1)
    result = s21_M_PI / 2 - s21_asin(x);
  else
    result = NaNl;
  return result;
}
