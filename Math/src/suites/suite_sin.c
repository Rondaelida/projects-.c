#include "../test.h"

START_TEST(test_sin_1) {
  double num = 0;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_2) {
  double num = 0.55;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_3) {
  double num = 1;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_4) {
  double num = 0.000001;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_5) {
  double num = -0.000001;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_6) {
  double num = NaNd;
  ck_assert_ldouble_nan(s21_sin(num));
}
END_TEST

START_TEST(test_sin_7) {
  double num = INF_double;
  ck_assert_ldouble_nan(s21_sin(num));
}
END_TEST

START_TEST(test_sin_8) {
  double num = negINF_double;
  ck_assert_ldouble_nan(s21_sin(num));
}
END_TEST

START_TEST(test_sin_9) {
  double num = 174.532925199433;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_10) {
  double num = 174;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_11) {
  double num = 10.99999;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_12) {
  double num = -1025.532925199433;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_13) {
  double num = -1234567890.1234567;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_14) {
  double num = 1234567890.1234567;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_15) {
  double num = M_PI_2;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_16) {
  double num = M_PI;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_sin_17) {
  double num = M_PI_4;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

Suite *suite_sin(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sin");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sin_1);
  tcase_add_test(tc_core, test_sin_2);
  tcase_add_test(tc_core, test_sin_3);
  tcase_add_test(tc_core, test_sin_4);
  tcase_add_test(tc_core, test_sin_5);
  tcase_add_test(tc_core, test_sin_6);
  tcase_add_test(tc_core, test_sin_7);
  tcase_add_test(tc_core, test_sin_8);
  tcase_add_test(tc_core, test_sin_9);
  tcase_add_test(tc_core, test_sin_10);
  tcase_add_test(tc_core, test_sin_11);
  tcase_add_test(tc_core, test_sin_12);
  tcase_add_test(tc_core, test_sin_13);
  tcase_add_test(tc_core, test_sin_14);
  tcase_add_test(tc_core, test_sin_15);
  tcase_add_test(tc_core, test_sin_16);
  tcase_add_test(tc_core, test_sin_17);

  suite_add_tcase(s, tc_core);

  return s;
}
