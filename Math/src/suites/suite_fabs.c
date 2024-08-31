#include "../test.h"

START_TEST(test_fabs_1) {
  ck_assert_ldouble_eq(s21_fabs(1.12345), (long double)fabs(1.12345));
}
END_TEST

START_TEST(test_fabs_2) {
  ck_assert_ldouble_eq(s21_fabs(-3.14295), (long double)fabs(-3.14295));
}
END_TEST

START_TEST(test_fabs_3) {
  ck_assert_ldouble_eq(s21_fabs(-9999999999.999999),
                       (long double)fabs(-9999999999.999999));
}
END_TEST

START_TEST(test_fabs_4) {
  ck_assert_ldouble_eq(s21_fabs(1567.89), (long double)fabs(1567.89));
}
END_TEST

START_TEST(test_fabs_5) {
  ck_assert_ldouble_eq(s21_fabs(-1567.8913), (long double)fabs(-1567.8913));
}
END_TEST

START_TEST(test_fabs_6) { ck_assert_ldouble_nan(s21_fabs(NaNl)); }
END_TEST

START_TEST(test_fabs_7) {
  ck_assert_ldouble_eq(s21_fabs(INF_ld), (long double)fabs(INF_ld));
}
END_TEST

START_TEST(test_fabs_8) {
  ck_assert_ldouble_eq(s21_fabs(-INF_ld), (long double)fabs(-INF_ld));
}
END_TEST

START_TEST(test_fabs_9) {
  ck_assert_ldouble_eq(s21_fabs(s21_M_PI), (long double)fabs(s21_M_PI));
}
END_TEST

START_TEST(test_fabs_10) {
  ck_assert_ldouble_eq(s21_fabs(s21_EXP), (long double)fabs(s21_EXP));
}
END_TEST

START_TEST(test_fabs_11) {
  ck_assert_ldouble_eq(s21_fabs(DOUBLE_MAX), (long double)fabs(DOUBLE_MAX));
}
END_TEST

START_TEST(test_fabs_12) {
  ck_assert_ldouble_eq(s21_fabs(ACCURACY), (long double)fabs(ACCURACY));
}
END_TEST

START_TEST(test_fabs_13) {
  ck_assert_ldouble_eq(s21_fabs(0.0), (long double)fabs(0.0));
}
END_TEST

START_TEST(test_fabs_14) {
  ck_assert_ldouble_eq(s21_fabs(-0.0), (long double)fabs(-0.0));
}
END_TEST

START_TEST(test_fabs_15) {
  ck_assert_ldouble_eq(s21_fabs(s21_EXP), (long double)fabs(s21_EXP));
}
END_TEST

START_TEST(test_fabs_16) {
  ck_assert_ldouble_eq(s21_fabs(-ACCURACY), (long double)fabs(-ACCURACY));
}
END_TEST

Suite *suite_fabs(void) {
  Suite *s3;
  TCase *tc_core3;

  s3 = suite_create("fabs");
  tc_core3 = tcase_create("Core");

  tcase_add_test(tc_core3, test_fabs_1);
  tcase_add_test(tc_core3, test_fabs_2);
  tcase_add_test(tc_core3, test_fabs_3);
  tcase_add_test(tc_core3, test_fabs_4);
  tcase_add_test(tc_core3, test_fabs_5);
  tcase_add_test(tc_core3, test_fabs_6);
  tcase_add_test(tc_core3, test_fabs_7);
  tcase_add_test(tc_core3, test_fabs_8);
  tcase_add_test(tc_core3, test_fabs_9);
  tcase_add_test(tc_core3, test_fabs_10);
  tcase_add_test(tc_core3, test_fabs_11);
  tcase_add_test(tc_core3, test_fabs_12);
  tcase_add_test(tc_core3, test_fabs_13);
  tcase_add_test(tc_core3, test_fabs_14);
  tcase_add_test(tc_core3, test_fabs_15);
  tcase_add_test(tc_core3, test_fabs_16);

  suite_add_tcase(s3, tc_core3);

  return s3;
}
