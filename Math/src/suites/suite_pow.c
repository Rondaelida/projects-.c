#include "../test.h"

START_TEST(pow_test_1) {
  double base = 10;
  double exp = 2;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_2) {
  double base = 17;
  double exp = 0.7;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_3) {
  double base = 3.4;
  double exp = 0.345;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_4) {
  double base = s21_M_PI;
  double exp = 4.5;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_5) {
  double base = -0.5;
  double exp = 0.5;
  ck_assert_ldouble_nan(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_test_6) {
  double base = -10;
  double exp = 2;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_7) {
  double base = 4;
  double exp = -6.23452;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_8) {
  double base = 12345;
  double exp = 0.14553;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_9) {
  double base = 52;
  double exp = -0.363;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_10) {
  double base = 0.96;
  double exp = 24;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_11) {
  double base = INFINITY;
  double exp = INFINITY;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_test_12) {
  double base = NaN;
  double exp = NaN;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_13) {
  double base = INFINITY;
  double exp = 1.1;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_test_14) {
  double base = +0;
  double exp = 1.1;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
  ;
}
END_TEST

START_TEST(pow_test_15) {
  double base = -0;
  double exp = -1.1;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_test_16) {
  double base = -0;
  double exp = INF_double;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_test_17) {
  long double base = -2;
  long double exp = NaN;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_18) {
  long double base = -1;
  long double exp = NaN;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_19) {
  long double base = -4;
  long double exp = NaN;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_20) {
  long double base = 1;
  long double exp = NaN;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_21) {
  long double base = NaN;
  long double exp = 0;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_22) {
  long double base = 0.55;
  long double exp = INFINITY;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_23) {
  long double base = 0.3535;
  long double exp = -INFINITY;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
}
END_TEST

START_TEST(pow_test_24) {
  long double base = 0;
  long double exp = 0;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_25) {
  long double base = 4.53345;
  long double exp = 0.9;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

START_TEST(pow_test_26) {
  long double base = 4.53345;
  long double exp = 1;
  ck_assert_ldouble_eq_tol(s21_pow(base, exp), (long double)pow(base, exp),
                           ACCURACY);
}
END_TEST

Suite *suite_pow(void) {
  Suite *suite = suite_create("pow");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, pow_test_1);
  tcase_add_test(tcase_core, pow_test_2);
  tcase_add_test(tcase_core, pow_test_3);
  tcase_add_test(tcase_core, pow_test_4);
  tcase_add_test(tcase_core, pow_test_5);
  tcase_add_test(tcase_core, pow_test_6);
  tcase_add_test(tcase_core, pow_test_7);
  tcase_add_test(tcase_core, pow_test_8);
  tcase_add_test(tcase_core, pow_test_9);
  tcase_add_test(tcase_core, pow_test_10);
  tcase_add_test(tcase_core, pow_test_11);
  tcase_add_test(tcase_core, pow_test_12);
  tcase_add_test(tcase_core, pow_test_13);
  tcase_add_test(tcase_core, pow_test_14);
  tcase_add_test(tcase_core, pow_test_15);
  tcase_add_test(tcase_core, pow_test_16);
  tcase_add_test(tcase_core, pow_test_17);
  tcase_add_test(tcase_core, pow_test_18);
  tcase_add_test(tcase_core, pow_test_19);
  tcase_add_test(tcase_core, pow_test_20);
  tcase_add_test(tcase_core, pow_test_21);
  tcase_add_test(tcase_core, pow_test_22);
  tcase_add_test(tcase_core, pow_test_23);
  tcase_add_test(tcase_core, pow_test_24);
  tcase_add_test(tcase_core, pow_test_25);
  tcase_add_test(tcase_core, pow_test_26);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
