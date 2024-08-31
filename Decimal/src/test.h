#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "s21_decimal.h"

Suite *suite_s21_is_less(void);
Suite *suite_s21_is_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_greater_or_equal(void);
Suite *suite_s21_is_not_equal(void);
Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_div(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_negate(void);
Suite *suite_s21_floor(void);
Suite *suite_s21_truncate(void);
Suite *suite_s21_round(void);
Suite *suite_s21_from_float_to_decimal(void);
Suite *suite_s21_from_decimal_to_float(void);
Suite *suite_s21_from_decimal_to_int(void);
Suite *suite_s21_from_int_to_decimal(void);

#endif  // S21_DECIMAL_TEST_H
