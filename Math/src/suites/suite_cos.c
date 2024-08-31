#include "../test.h"

START_TEST(test_cos_1) {
  double num = 0;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_2) {
  double num = 0.55;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_3) {
  double num = 1;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_4) {
  double num = 0.000001;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_5) {
  double num = -0.000001;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_6) {
  double num = NaNd;
  ck_assert_ldouble_nan(s21_cos(num));
}
END_TEST

START_TEST(test_cos_7) {
  double num = INF_double;
  ck_assert_ldouble_nan(s21_cos(num));
}
END_TEST

START_TEST(test_cos_8) {
  double num = negINF_double;
  ck_assert_ldouble_nan(s21_cos(num));
}
END_TEST

START_TEST(test_cos_9) {
  double num = 174.532925199433;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_10) {
  double num = 174;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_11) {
  double num = 10.99999;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_12) {
  double num = -1234567890.1234567;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_13) {
  double num = 1234567890.1234567;
  ck_assert_ldouble_eq_tol(s21_cos(num), (long double)cos(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_14) {
  double num = M_PI_4;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_15) {
  double num = M_PI_2;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

START_TEST(test_cos_16) {
  double num = M_PI;
  ck_assert_ldouble_eq_tol(s21_sin(num), (long double)sin(num), ACCURACY);
}
END_TEST

Suite *suite_cos(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("cos");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_cos_1);
  tcase_add_test(tc_core, test_cos_2);
  tcase_add_test(tc_core, test_cos_3);
  tcase_add_test(tc_core, test_cos_4);
  tcase_add_test(tc_core, test_cos_5);
  tcase_add_test(tc_core, test_cos_6);
  tcase_add_test(tc_core, test_cos_7);
  tcase_add_test(tc_core, test_cos_8);
  tcase_add_test(tc_core, test_cos_9);
  tcase_add_test(tc_core, test_cos_10);
  tcase_add_test(tc_core, test_cos_11);
  tcase_add_test(tc_core, test_cos_12);
  tcase_add_test(tc_core, test_cos_13);
  tcase_add_test(tc_core, test_cos_14);
  tcase_add_test(tc_core, test_cos_15);
  tcase_add_test(tc_core, test_cos_16);

  suite_add_tcase(s, tc_core);

  return s;
}