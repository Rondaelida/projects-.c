#include "../test.h"

START_TEST(test_acos_1) {
  double num = 0;
  ck_assert_ldouble_eq_tol(s21_acos(num), (long double)acos(num), ACCURACY);
}
END_TEST

START_TEST(test_acos_2) {
  double num = 0.55;
  ck_assert_ldouble_eq_tol(s21_acos(num), (long double)acos(num), ACCURACY);
}
END_TEST

START_TEST(test_acos_3) {
  double num = 1;
  ck_assert_ldouble_eq_tol(s21_acos(num), (long double)acos(num), ACCURACY);
}
END_TEST

START_TEST(test_acos_4) {
  double num = -1;
  ck_assert_ldouble_eq_tol(s21_acos(num), (long double)acos(num), ACCURACY);
}
END_TEST

START_TEST(test_acos_5) {
  double num = 0.000001;
  ck_assert_ldouble_eq_tol(s21_acos(num), (long double)acos(num), ACCURACY);
}
END_TEST

START_TEST(test_acos_6) {
  double num = -0.000001;
  ck_assert_ldouble_eq_tol(s21_acos(num), (long double)acos(num), ACCURACY);
}
END_TEST

START_TEST(test_acos_7) {
  double num = 555555.555555;
  ck_assert_ldouble_nan(s21_acos(num));
}
END_TEST

START_TEST(test_acos_8) {
  double num = -555555.555555;
  ck_assert_ldouble_nan(s21_acos(num));
}
END_TEST

START_TEST(test_acos_9) {
  double num = NaNd;
  ck_assert_ldouble_nan(s21_acos(num));
}
END_TEST

START_TEST(test_acos_10) {
  double num = INF_double;
  ck_assert_ldouble_nan(s21_acos(num));
}
END_TEST

START_TEST(test_acos_11) {
  double num = negINF_double;
  ck_assert_ldouble_nan(s21_acos(num));
}
END_TEST

Suite *suite_acos(void) {
  Suite *suite;
  TCase *tc_core;

  suite = suite_create("acos");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_acos_1);
  tcase_add_test(tc_core, test_acos_2);
  tcase_add_test(tc_core, test_acos_3);
  tcase_add_test(tc_core, test_acos_4);
  tcase_add_test(tc_core, test_acos_5);
  tcase_add_test(tc_core, test_acos_6);
  tcase_add_test(tc_core, test_acos_7);
  tcase_add_test(tc_core, test_acos_8);
  tcase_add_test(tc_core, test_acos_9);
  tcase_add_test(tc_core, test_acos_10);
  tcase_add_test(tc_core, test_acos_11);

  suite_add_tcase(suite, tc_core);

  return suite;
}
