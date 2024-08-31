#include "../test.h"

START_TEST(test_asin_1) {
  double num = 0;
  ck_assert_ldouble_eq_tol(s21_asin(num), (long double)asin(num), ACCURACY);
}
END_TEST

START_TEST(test_asin_2) {
  double num = 1;
  ck_assert_ldouble_eq_tol(s21_asin(num), (long double)asin(num), ACCURACY);
}
END_TEST

START_TEST(test_asin_3) {
  double num = -1;
  ck_assert_ldouble_eq_tol(s21_asin(num), (long double)asin(num), ACCURACY);
}
END_TEST

START_TEST(test_asin_4) {
  double num = 0.55;
  ck_assert_ldouble_eq_tol(s21_asin(num), (long double)asin(num), ACCURACY);
}
END_TEST

START_TEST(test_asin_5) {
  double num = 0.000001;
  ck_assert_ldouble_eq_tol(s21_asin(num), (long double)asin(num), ACCURACY);
}
END_TEST

START_TEST(test_asin_6) {
  double num = -0.000001;
  ck_assert_ldouble_eq_tol(s21_asin(num), (long double)asin(num), ACCURACY);
}
END_TEST

START_TEST(test_asin_7) {
  double num = NaNd;
  ck_assert_ldouble_nan(s21_asin(num));
}
END_TEST

START_TEST(test_asin_8) {
  double num = INF_double;
  ck_assert_ldouble_nan(s21_asin(num));
}
END_TEST

START_TEST(test_asin_9) {
  double num = negINF_double;
  ck_assert_ldouble_nan(s21_asin(num));
}
END_TEST

START_TEST(test_asin_10) {
  double num = 555555.555555;
  ck_assert_ldouble_nan(s21_asin(num));
}
END_TEST

START_TEST(test_asin_11) {
  double num = -555555.555555;
  ck_assert_ldouble_nan(s21_asin(num));
}
END_TEST

Suite *suite_asin(void) {
  Suite *suite;
  TCase *tc_core;

  suite = suite_create("asin");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_asin_1);
  tcase_add_test(tc_core, test_asin_2);
  tcase_add_test(tc_core, test_asin_3);
  tcase_add_test(tc_core, test_asin_4);
  tcase_add_test(tc_core, test_asin_5);
  tcase_add_test(tc_core, test_asin_6);
  tcase_add_test(tc_core, test_asin_7);
  tcase_add_test(tc_core, test_asin_8);
  tcase_add_test(tc_core, test_asin_9);
  tcase_add_test(tc_core, test_asin_10);
  tcase_add_test(tc_core, test_asin_11);

  suite_add_tcase(suite, tc_core);

  return suite;
}
