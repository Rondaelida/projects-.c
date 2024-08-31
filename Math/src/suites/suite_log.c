#include "../test.h"

START_TEST(log_test_1) {
  double x = -10;
  ck_assert_ldouble_nan(s21_log(x));
}
END_TEST

START_TEST(log_test_2) {
  double x = -0.0001;
  ck_assert_ldouble_nan(s21_log(x));
}
END_TEST

START_TEST(log_test_3) {
  double x = 0;
  ck_assert_ldouble_infinite(s21_log(x));
}
END_TEST

START_TEST(log_test_4) {
  double x = 1;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_5) {
  double x = 10;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_6) {
  double x = 100;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_7) {
  double x = 700;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_8) {
  double x = 1.13435236;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_9) {
  double x = 10.35798347598;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_10) {
  double x = 99.37598;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_11) {
  double x = 123.03244;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_12) {
  double x = INFINITY;
  ck_assert_ldouble_infinite(s21_log(x));
}
END_TEST

START_TEST(log_test_13) {
  double x = INFINITY;
  ck_assert_ldouble_infinite(s21_log(x));
}
END_TEST

START_TEST(log_test_14) {
  double x = NaN;
  ck_assert_ldouble_nan(s21_log(x));
}
END_TEST

START_TEST(log_test_15) {
  double x = 0.0000000000011;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_16) {
  double x = 9999999999999.9;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_17) {
  double x = 1e-13;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_18) {
  double x = 1e13;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_19) {
  double x = 124356.75e21;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_20) {
  double x = 124356.75e-21;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

START_TEST(log_test_21) {
  double x = 4.408680e7;
  ck_assert_ldouble_eq_tol(s21_log(x), (long double)log(x), ACCURACY);
}
END_TEST

Suite *suite_log(void) {
  Suite *suite = suite_create("log");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, log_test_1);
  tcase_add_test(tcase_core, log_test_2);
  tcase_add_test(tcase_core, log_test_3);
  tcase_add_test(tcase_core, log_test_4);
  tcase_add_test(tcase_core, log_test_5);
  tcase_add_test(tcase_core, log_test_6);
  tcase_add_test(tcase_core, log_test_7);
  tcase_add_test(tcase_core, log_test_8);
  tcase_add_test(tcase_core, log_test_9);
  tcase_add_test(tcase_core, log_test_10);
  tcase_add_test(tcase_core, log_test_11);
  tcase_add_test(tcase_core, log_test_12);
  tcase_add_test(tcase_core, log_test_13);
  tcase_add_test(tcase_core, log_test_14);
  tcase_add_test(tcase_core, log_test_15);
  tcase_add_test(tcase_core, log_test_16);
  tcase_add_test(tcase_core, log_test_17);
  tcase_add_test(tcase_core, log_test_18);
  tcase_add_test(tcase_core, log_test_19);
  tcase_add_test(tcase_core, log_test_20);
  tcase_add_test(tcase_core, log_test_21);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
