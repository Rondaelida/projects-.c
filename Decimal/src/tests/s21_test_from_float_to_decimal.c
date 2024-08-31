#include <check.h>
#include <stdio.h>

#include "../test.h"

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal val;

  s21_from_float_to_decimal(0.03, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 131072);

  s21_from_float_to_decimal(127.1234, &val);
  ck_assert_int_eq(val.bits[0], 1271234);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 262144);
}
END_TEST
START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal val;
  s21_from_float_to_decimal(-128.023, &val);
  ck_assert_int_eq(val.bits[0], 12802299);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
}
START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val;
  s21_from_float_to_decimal(-2.1474836E+09, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST
START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val;
  s21_from_float_to_decimal(22.14836E+03, &val);
  ck_assert_int_eq(val.bits[0], 2214836);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 131072);
}
END_TEST
START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal val;
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal val;
  s21_from_float_to_decimal(-333.2222, &val);
  ck_assert_int_eq(val.bits[0], 3332222);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal val;
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal val;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_9) {
  s21_decimal val;
  float a = 0.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

Suite *suite_s21_from_float_to_decimal(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[40m\033[94ms21_from_float_to_decimal\033[0m");
  tc = tcase_create("s21_from_float_to_decimal");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, s21_from_float_to_decimal_1);
    tcase_add_test(tc, s21_from_float_to_decimal_2);
    tcase_add_test(tc, s21_from_float_to_decimal_3);
    tcase_add_test(tc, s21_from_float_to_decimal_4);
    tcase_add_test(tc, s21_from_float_to_decimal_5);
    tcase_add_test(tc, s21_from_float_to_decimal_6);
    tcase_add_test(tc, s21_from_float_to_decimal_7);
    tcase_add_test(tc, s21_from_float_to_decimal_8);
    tcase_add_test(tc, s21_from_float_to_decimal_9);
    suite_add_tcase(s, tc);
  }

  return (s);
}