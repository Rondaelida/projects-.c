#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <iso646.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_BD 7
#define SIGN 0x80000000
#define TRUE 1
#define FALSE 0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  int ar_round;
  int bnk_round;
  int sign;
  int scale;
  unsigned int bits[SIZE_OF_BD];
} big_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

// Help functions:
int get_bit(int index, s21_decimal decimal);
int set_bit(int index, int value, s21_decimal *decimal);
int get_scale(s21_decimal decimal);
int make_zero(s21_decimal *decimal);
s21_decimal get_mantissa_with_scale(int new_scale, s21_decimal decimal);
s21_decimal simple_help_plus(s21_decimal decimal_a, s21_decimal decimal_b);
int shift_to_left(s21_decimal *decimal);
int set_scale(int new_scale, s21_decimal *decimal);
int s21_control_zero(big_decimal decimal);
void integer_big_div(big_decimal value, big_decimal dividing,
                     big_decimal *big_result, big_decimal *big_reminder);
s21_decimal GET_MAX_MANTISS();
int s21_control_sign(big_decimal dec1, big_decimal dec2, int *dec_comparison);
s21_decimal get_mantissa_with_scale(int new_scale, s21_decimal decimal);
void s21_introdution_to_common_den(big_decimal *dec1, big_decimal *dec2,
                                   int flag);
int s21_decimal_print(s21_decimal dst, char *src);
bool is_zero(s21_decimal decimal);
int getFloatSign(float *src);
int getFloatExp(float *src);

// Main functions:
int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_equal(s21_decimal decimal_a, s21_decimal decimal_b);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_float_to_decimal(float value, s21_decimal *dst);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_is_equal(s21_decimal, s21_decimal);

// Big_decimal
big_decimal decimal_to_big_dec(s21_decimal value);
int big_dec_to_decimal(big_decimal big_value, s21_decimal *value);
big_decimal get_mantissa_with_scale_bd(int new_scale, big_decimal big_value);
int compare_mantiss_only_bd(big_decimal decimal_a, big_decimal decimal_b);
int get_bit_bd(int index, big_decimal decimal);
void increase_in_degree_bd(int new_scale, int old_scale, big_decimal *decimal);
big_decimal simple_help_plus_bd(big_decimal decimal_a, big_decimal decimal_b);
int set_bit_bd(int index, int value, big_decimal *decimal);
int shift_to_left_bd(big_decimal *decimal);
big_decimal simple_help_minus_bd(big_decimal decimal_a, big_decimal decimal_b);
void decrease_in_degree_bd(int new_scale, int old_scale, big_decimal *decimal);
int make_zero_bd(big_decimal *big_value);
int s21_transform_to_96_bit(big_decimal *big_value);

#endif