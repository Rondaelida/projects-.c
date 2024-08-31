#include "../test.h"

START_TEST(test_exp_1) {
  double x = 1;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_2) {
  double x = 0.5;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_3) {
  double x = 0.345678;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_4) {
  double x = 4.5;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_5) {
  double x = -4;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_6) {
  double x = -6.23452;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_7) {
  double x = 13456576786564634.2435;
  ck_assert_int_eq(s21_exp(x), exp(x));
}
END_TEST

START_TEST(test_exp_8) {
  double x = -13456576786564634.2435;
  ck_assert_int_eq(s21_exp(x), exp(x));
}
END_TEST

START_TEST(test_exp_9) {
  double x = INFINITY;
  ck_assert_ldouble_infinite(s21_exp(x));
}
END_TEST

START_TEST(test_exp_10) {
  double x = NaN;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_11) {
  double x = -1e11;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_12) {
  double x = 1e20;
  ck_assert_ldouble_infinite(s21_exp(x));
}
END_TEST

START_TEST(test_exp_13) {
  double x = INF_double;
  ck_assert_ldouble_infinite(s21_exp(x));
}
END_TEST

START_TEST(test_exp_14) {
  long double x = NaNl;
  ck_assert_ldouble_nan(s21_exp(x));
}
END_TEST

START_TEST(test_exp_15) {
  long double x = 0;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_16) {
  double x = -INFINITY;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_17) {
  long double x = 0.9;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

START_TEST(test_exp_18) {
  long double x = 0.0000000001;
  ck_assert_ldouble_eq_tol(s21_exp(x), (long double)exp(x), ACCURACY);
}
END_TEST

Suite *suite_exp(void) {
  Suite *suite = suite_create("exp");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, test_exp_1);
  tcase_add_test(tcase_core, test_exp_2);
  tcase_add_test(tcase_core, test_exp_3);
  tcase_add_test(tcase_core, test_exp_4);
  tcase_add_test(tcase_core, test_exp_5);
  tcase_add_test(tcase_core, test_exp_6);
  tcase_add_test(tcase_core, test_exp_7);
  tcase_add_test(tcase_core, test_exp_8);
  tcase_add_test(tcase_core, test_exp_9);
  tcase_add_test(tcase_core, test_exp_10);
  tcase_add_test(tcase_core, test_exp_11);
  tcase_add_test(tcase_core, test_exp_12);
  tcase_add_test(tcase_core, test_exp_13);
  tcase_add_test(tcase_core, test_exp_14);
  tcase_add_test(tcase_core, test_exp_15);
  tcase_add_test(tcase_core, test_exp_16);
  tcase_add_test(tcase_core, test_exp_17);
  tcase_add_test(tcase_core, test_exp_18);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
