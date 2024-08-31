#include "../test.h"

START_TEST(test_abs_1) {
  int x = 5;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_abs_2) {
  int x = -10;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_abs_3) {
  int x = NaN;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_abs_4) {
  int x = INF_int;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_abs_5) {
  int x = -INF_int;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_abs_6) {
  int x = 0;
  ck_assert_int_eq(s21_abs(x), abs(x));
}
END_TEST

START_TEST(test_abs_7) { ck_assert_int_eq(s21_abs(191435345), abs(191435345)); }
END_TEST

START_TEST(test_abs_8) {
  ck_assert_int_eq(s21_abs(-191435345), abs(-191435345));
}
END_TEST

Suite *suite_abs(void) {
  Suite *s1;
  TCase *tc_core1;

  s1 = suite_create("abs");
  tc_core1 = tcase_create("Core");

  tcase_add_test(tc_core1, test_abs_1);
  tcase_add_test(tc_core1, test_abs_2);
  tcase_add_test(tc_core1, test_abs_3);
  tcase_add_test(tc_core1, test_abs_4);
  tcase_add_test(tc_core1, test_abs_5);
  tcase_add_test(tc_core1, test_abs_6);
  tcase_add_test(tc_core1, test_abs_7);
  tcase_add_test(tc_core1, test_abs_8);

  suite_add_tcase(s1, tc_core1);

  return s1;
}
