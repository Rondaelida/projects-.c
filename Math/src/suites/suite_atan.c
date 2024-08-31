#include "../test.h"

START_TEST(test_atan_1) {
  double num = 0;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_2) {
  double num = 0.55;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_3) {
  double num = 1;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_4) {
  double num = -1;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_5) {
  double num = -55555555.555555;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_6) {
  double num = -0.000001;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_7) {
  double num = 0.000001;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

START_TEST(test_atan_8) {
  double num = NaNd;
  ck_assert_ldouble_nan(s21_atan(num));
}
END_TEST

START_TEST(test_atan_9) {
  double num = INF_double;
  ck_assert_ldouble_nan(s21_atan(num));
}
END_TEST

START_TEST(test_atan_10) {
  double num = negINF_double;
  ck_assert_ldouble_nan(s21_atan(num));
}
END_TEST

START_TEST(test_atan_11) {
  double num = 55555555.555555;
  ck_assert_ldouble_eq_tol(s21_atan(num), (long double)atan(num), ACCURACY);
}
END_TEST

Suite *suite_atan(void) {
  Suite *suite;
  TCase *tc_core;

  suite = suite_create("atan");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_atan_1);
  tcase_add_test(tc_core, test_atan_2);
  tcase_add_test(tc_core, test_atan_3);
  tcase_add_test(tc_core, test_atan_4);
  tcase_add_test(tc_core, test_atan_5);
  tcase_add_test(tc_core, test_atan_6);
  tcase_add_test(tc_core, test_atan_7);
  tcase_add_test(tc_core, test_atan_8);
  tcase_add_test(tc_core, test_atan_9);
  tcase_add_test(tc_core, test_atan_10);
  tcase_add_test(tc_core, test_atan_11);

  suite_add_tcase(suite, tc_core);

  return suite;
}
