#include <stdio.h>
#include <stdlib.h>
#define s21_M_PI 3.1415926535897932
#define s21_EXP 2.7182818284590452353602874713526624
#define DOUBLE_MAX 1.7976931348623157e+308
#define ACCURACY 0.000001
#define NaN (int)(0.0 / 0.0)
#define NaNd (0.0 / 0.0)
#define NaNl (0.0 / 0.0)
#define INF_int (int)(1.0 / 0.0)
#define INF_double (1.0 / 0.0)
#define INF_ld (1.0 / 0.0)
#define negINF_int (int)(-1.0 / 0.0)
#define negINF_double (-1.0 / 0.0)

int s21_abs(int x);
long double s21_max(double a, double b);
long double s21_fabs(double x);
long double s21_sqrt(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_floor(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_powint(double base, int exp);
long double s21_fmod(double x, double y);
long double s21_sin(double x);
long double s21_atan(double x);
long double s21_fact(long double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_tan(double x);
int isNaN(double x);
