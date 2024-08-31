#include <check.h>
#include <math.h>

#include "../s21_calc.h"
#include "../s21_credit.h"

// Функция создания набора тестов.

START_TEST(s21_smart_calc_1) {
  char input[255] = "2+4*2/(4-7)^2";
  double result = s21_parser(input, 0);
  ck_assert_double_eq(result, 3);
}

END_TEST

START_TEST(s21_smart_calc_2) {
  char *str =
      "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*atan(444)/ln(log(555))";
  int result = s21_parser(str, 0);
  ck_assert_int_eq(result, -2147483648);
}

END_TEST

START_TEST(s21_smart_calc_3) {
  char *str = "2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
  int result = s21_parser(str, 0);
  ck_assert_int_eq(result, -1950983);
}

END_TEST

START_TEST(s21_smart_calc_4) {
  char input[255] = "sin(2)";
  double result = s21_parser(input, 0);
  ck_assert_double_eq_tol(result, 0.909297, 1e-6);
}

END_TEST

START_TEST(s21_smart_calc_5) {
  char input[255] = "2mod2";
  double result = s21_parser(input, 0);
  ck_assert_double_eq(result, 2);
}

END_TEST

START_TEST(s21_credit_1) {
  double sum = 10000;
  int data = 12;
  double procent = 21;
  int type = 1;
  double monthly_payment = 0.0, prepeyment = 0.0, total_payout = 0.0;
  calc_credit(type, sum, data, procent, &total_payout, &prepeyment,
              &monthly_payment);
  ck_assert_double_eq_tol(monthly_payment, 931.14, 1e-2);
  ck_assert_double_eq_tol(prepeyment, 1173.68, 1e-2);
  ck_assert_double_eq_tol(total_payout, 11173.68, 1e-2);
}

END_TEST

START_TEST(s21_credit_2) {
  double sum = 10000;
  int data = 12;
  double procent = 21;
  int type = 2;
  double monthly_payment = 0.0, prepeyment = 0.0, total_payout = 0.0;
  calc_credit(type, sum, data, procent, &total_payout, &prepeyment,
              &monthly_payment);
  ck_assert_double_eq_tol(monthly_payment, 1008.00, 1e-2);
  ck_assert_double_eq_tol(prepeyment, 1134.00, 1e-2);
  ck_assert_double_eq_tol(total_payout, 11134.00, 1e-2);
}

END_TEST

// Функция создания набора тестов.

Suite *

s21_smart_calc_suite(void) {
  Suite *suite;

  suite = suite_create("s21_smart_calc");
  TCase *tcase_core = tcase_create("Core");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_smart_calc_1);
  tcase_add_test(tcase_core, s21_smart_calc_2);
  tcase_add_test(tcase_core, s21_smart_calc_3);
  tcase_add_test(tcase_core, s21_smart_calc_4);
  tcase_add_test(tcase_core, s21_smart_calc_5);
  tcase_add_test(tcase_core, s21_credit_1);
  tcase_add_test(tcase_core, s21_credit_2);

  // Добавление теста в тестовый набор.

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_smart_calc_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);

  // Получаем количество проваленных тестов.

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  // Сигнализируем о том, что тестирование прошло неудачно.

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
