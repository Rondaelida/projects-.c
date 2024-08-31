#include "../test.h"

START_TEST(test_tan_1) {
  ck_assert_ldouble_eq_tol(s21_tan(1.1), (long double)tan(1.1), ACCURACY);
}
END_TEST

START_TEST(test_tan_2) {
  ck_assert_ldouble_nan(s21_tan(NAN));
  ck_assert_ldouble_nan((long double)tan(NAN));
}
END_TEST

START_TEST(test_tan_3) {
  ck_assert_ldouble_nan(s21_tan(INFINITY));
  ck_assert_ldouble_nan((long double)tan(INFINITY));
}
END_TEST

START_TEST(test_tan_4) {
  ck_assert_ldouble_nan(s21_tan(-INFINITY));
  ck_assert_ldouble_nan((long double)tan(-INFINITY));
}
END_TEST

START_TEST(test_tan_5) {
  ck_assert_ldouble_nan(s21_tan(-NAN));
  ck_assert_ldouble_nan((long double)tan(-NAN));
}
END_TEST

START_TEST(test_tan_6) {
  ck_assert_ldouble_eq_tol(s21_tan(9999.99999), tan(9999.99999), ACCURACY);
}
END_TEST

START_TEST(test_tan_7) {
  ck_assert_ldouble_eq_tol(s21_tan(0.0), tan(0.0), ACCURACY);
}
END_TEST

START_TEST(test_tan_8) {
  ck_assert_ldouble_eq_tol(s21_tan(-0.0), tan(-0.0), ACCURACY);
}
END_TEST

START_TEST(test_tan_9) {
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), ACCURACY);
}
END_TEST

START_TEST(test_tan_10) {
  ck_assert_ldouble_eq_tol(s21_tan(-0), tan(-0), ACCURACY);
}
END_TEST

START_TEST(test_tan_11) {
  ck_assert_ldouble_eq_tol(s21_tan(0.000001), tan(0.000001), ACCURACY);
}
END_TEST

START_TEST(test_tan_12) {
  ck_assert_ldouble_eq_tol(s21_tan(-0.000001), tan(-0.000001), ACCURACY);
}
END_TEST

START_TEST(test_tan_13) {
  ck_assert_ldouble_nan(s21_tan(NaNd));
  ck_assert_ldouble_nan(tan(NaNd));
}
END_TEST

START_TEST(test_tan_14) {
  ck_assert_ldouble_eq_tol(s21_tan(38784.000001), tan(38784.000001), ACCURACY);
}
END_TEST

START_TEST(test_tan_15) {
  long double x = 98887.8;
  ck_assert_ldouble_eq_tol(s21_tan(x), tan(x), ACCURACY);
}
END_TEST

START_TEST(test_tan_16) {
  long double x = 10101010.9876;
  ck_assert_ldouble_eq_tol(s21_tan(x), tan(x), ACCURACY);
}
END_TEST

START_TEST(test_tan_17) {
  long double x = s21_M_PI / 2;
  ck_assert_ldouble_eq_tol(s21_tan(x), tan(x), ACCURACY);
}
END_TEST

START_TEST(test_tan_18) {
  long double x = -s21_M_PI / 2;
  ck_assert_ldouble_eq_tol(s21_tan(x), tan(x), ACCURACY);
}
END_TEST

START_TEST(test_tan_19) {
  long double x = 3 * -s21_M_PI / 2;
  ck_assert_ldouble_eq_tol(s21_tan(x), tan(x), ACCURACY);
}
END_TEST

START_TEST(test_tan_20) {
  long double x = 3 * s21_M_PI / 2;
  ck_assert_ldouble_eq_tol(s21_tan(x), tan(x), ACCURACY);
}
END_TEST

Suite *suite_tan(void) {
  Suite *s15;
  TCase *tc15;

  s15 = suite_create("tan");
  tc15 = tcase_create("Core");

  tcase_add_test(tc15, test_tan_1);
  tcase_add_test(tc15, test_tan_2);
  tcase_add_test(tc15, test_tan_3);
  tcase_add_test(tc15, test_tan_4);
  tcase_add_test(tc15, test_tan_5);
  tcase_add_test(tc15, test_tan_6);
  tcase_add_test(tc15, test_tan_7);
  tcase_add_test(tc15, test_tan_8);
  tcase_add_test(tc15, test_tan_9);
  tcase_add_test(tc15, test_tan_10);
  tcase_add_test(tc15, test_tan_11);
  tcase_add_test(tc15, test_tan_12);
  tcase_add_test(tc15, test_tan_13);
  tcase_add_test(tc15, test_tan_14);
  tcase_add_test(tc15, test_tan_15);
  tcase_add_test(tc15, test_tan_16);
  tcase_add_test(tc15, test_tan_17);
  tcase_add_test(tc15, test_tan_18);
  tcase_add_test(tc15, test_tan_19);
  tcase_add_test(tc15, test_tan_20);

  suite_add_tcase(s15, tc15);

  return s15;
}
