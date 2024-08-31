#include "../test.h"

START_TEST(test_ceil_1) {
  ck_assert_ldouble_eq_tol(s21_ceil(6.66), (long double)ceil(6.66), ACCURACY);
}
END_TEST

START_TEST(test_ceil_2) {
  ck_assert_ldouble_eq_tol(s21_ceil(-5.56), (long double)ceil(-5.56), ACCURACY);
}
END_TEST

START_TEST(test_ceil_3) {
  ck_assert_ldouble_eq_tol(s21_ceil(-9999999999.999999),
                           (long double)ceil(-9999999999.999999), ACCURACY);
}
END_TEST

START_TEST(test_ceil_4) { ck_assert_ldouble_nan(s21_ceil(NaNl)); }
END_TEST

START_TEST(test_ceil_5) { ck_assert_ldouble_infinite(s21_ceil(INF_double)); }
END_TEST

START_TEST(test_ceil_6) { ck_assert_ldouble_infinite(s21_ceil(-INF_double)); }
END_TEST

Suite *suite_ceil(void) {
  Suite *s2;
  TCase *tc_core2;

  s2 = suite_create("ceil");
  tc_core2 = tcase_create("Core");

  tcase_add_test(tc_core2, test_ceil_1);
  tcase_add_test(tc_core2, test_ceil_2);
  tcase_add_test(tc_core2, test_ceil_3);
  tcase_add_test(tc_core2, test_ceil_4);
  tcase_add_test(tc_core2, test_ceil_5);
  tcase_add_test(tc_core2, test_ceil_6);

  suite_add_tcase(s2, tc_core2);

  return s2;
}
