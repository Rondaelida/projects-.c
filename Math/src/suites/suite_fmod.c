#include "../test.h"

START_TEST(test_fmod_1) {
  double x = 16.3536;
  double y = 4.36;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_2) {
  double x = -56.14;
  double y = -7.45376;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_3) {
  double x = 56.14;
  double y = -7.45376;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_4) {
  double x = -16.3536;
  double y = 4.36;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_5) {
  double x = 1234567;
  double y = 3;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_6) {
  double x = -1234567;
  double y = -3;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_7) {
  double x = -3;
  double y = -1234567;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_8) {
  double x = -1234567;
  double y = -1234567;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_9) {
  double x = 1024;
  double y = 2;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_10) {
  double x = INF_ld;
  double y = INF_ld;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_11) {
  double x = NaNd;
  double y = NaNd;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_12) {
  double x = 24.5;
  double y = 0;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_13) {
  double x = 0;
  double y = 0;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_14) {
  double x = INF_ld;
  double y = 0;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_15) {
  double x = NaNd;
  double y = 5;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_16) {
  double x = 5;
  double y = NaNd;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_17) {
  double x = 1024;
  double y = INF_ld;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

START_TEST(test_fmod_18) {
  double x = INF_ld;
  double y = 7.86;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_19) {
  double x = -INF_ld;
  double y = 7.86;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_20) {
  double x = -INF_ld;
  double y = INF_ld;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(test_fmod_21) {
  double x = 0;
  double y = -666.666;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), ACCURACY);
}
END_TEST

Suite *suite_fmod(void) {
  Suite *s5;
  TCase *tc_core5;

  s5 = suite_create("fmod");
  tc_core5 = tcase_create("Core");

  tcase_add_test(tc_core5, test_fmod_1);
  tcase_add_test(tc_core5, test_fmod_2);
  tcase_add_test(tc_core5, test_fmod_3);
  tcase_add_test(tc_core5, test_fmod_4);
  tcase_add_test(tc_core5, test_fmod_5);
  tcase_add_test(tc_core5, test_fmod_6);
  tcase_add_test(tc_core5, test_fmod_7);
  tcase_add_test(tc_core5, test_fmod_8);
  tcase_add_test(tc_core5, test_fmod_9);
  tcase_add_test(tc_core5, test_fmod_10);
  tcase_add_test(tc_core5, test_fmod_11);
  tcase_add_test(tc_core5, test_fmod_12);
  tcase_add_test(tc_core5, test_fmod_13);
  tcase_add_test(tc_core5, test_fmod_14);
  tcase_add_test(tc_core5, test_fmod_15);
  tcase_add_test(tc_core5, test_fmod_16);
  tcase_add_test(tc_core5, test_fmod_17);
  tcase_add_test(tc_core5, test_fmod_18);
  tcase_add_test(tc_core5, test_fmod_19);
  tcase_add_test(tc_core5, test_fmod_20);
  tcase_add_test(tc_core5, test_fmod_21);

  suite_add_tcase(s5, tc_core5);

  return s5;
}
