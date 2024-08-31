#include "../test.h"

START_TEST(test_floor_1) {
  ck_assert_ldouble_eq_tol(s21_floor(6.66), (long double)floor(6.66), ACCURACY);
}
END_TEST

START_TEST(test_floor_2) {
  ck_assert_ldouble_eq_tol(s21_floor(-5.56), (long double)floor(-5.56),
                           ACCURACY);
}
END_TEST

START_TEST(test_floor_3) {
  ck_assert_ldouble_eq_tol(s21_floor(-9999999999.999999),
                           (long double)floor(-9999999999.999999), ACCURACY);
}
END_TEST

START_TEST(test_floor_4) { ck_assert_ldouble_nan(s21_floor(NaNl)); }
END_TEST

START_TEST(test_floor_5) { ck_assert_ldouble_infinite(s21_floor(INF_double)); }
END_TEST

START_TEST(test_floor_6) { ck_assert_ldouble_infinite(s21_floor(-INF_double)); }
END_TEST

Suite *suite_floor(void) {
  Suite *s4;
  TCase *tc_core4;

  s4 = suite_create("floor");
  tc_core4 = tcase_create("Core");

  tcase_add_test(tc_core4, test_floor_1);
  tcase_add_test(tc_core4, test_floor_2);
  tcase_add_test(tc_core4, test_floor_3);
  tcase_add_test(tc_core4, test_floor_4);
  tcase_add_test(tc_core4, test_floor_5);
  tcase_add_test(tc_core4, test_floor_6);

  suite_add_tcase(s4, tc_core4);

  return s4;
}
