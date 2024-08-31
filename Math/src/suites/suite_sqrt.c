#include "../test.h"

START_TEST(test_sqrt_1) {
  double x = 21.21;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

START_TEST(test_sqrt_2) {
  double x = -49.7;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_sqrt_3) {
  double x = NaN;
  ck_assert_ldouble_nan(s21_sqrt(x));
  ck_assert_ldouble_nan((long double)sqrt(x));
}
END_TEST

START_TEST(test_sqrt_4) {
  double x = INFINITY;
  ck_assert_ldouble_eq(s21_sqrt(x), sqrt(x));
}
END_TEST

START_TEST(test_sqrt_5) {
  double x = -INFINITY;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_sqrt_6) {
  double x = -0;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

START_TEST(test_sqrt_7) {
  double x = -0.00;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

START_TEST(test_sqrt_8) {
  double x = 1e-10;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

START_TEST(test_sqrt_9) {
  long double x = 0.000001;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

START_TEST(test_sqrt_10) {
  double x = NaNl;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_sqrt_11) {
  long double x = 9999999999.000001;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

START_TEST(test_sqrt_12) {
  long double x = 0.000001;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), (long double)sqrt(x), ACCURACY);
}
END_TEST

Suite *suite_sqrt(void) {
  Suite *suite = suite_create("sqrt");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, test_sqrt_1);
  tcase_add_test(tcase_core, test_sqrt_2);
  tcase_add_test(tcase_core, test_sqrt_3);
  tcase_add_test(tcase_core, test_sqrt_4);
  tcase_add_test(tcase_core, test_sqrt_5);
  tcase_add_test(tcase_core, test_sqrt_6);
  tcase_add_test(tcase_core, test_sqrt_7);
  tcase_add_test(tcase_core, test_sqrt_8);
  tcase_add_test(tcase_core, test_sqrt_9);
  tcase_add_test(tcase_core, test_sqrt_10);
  tcase_add_test(tcase_core, test_sqrt_11);
  tcase_add_test(tcase_core, test_sqrt_12);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
