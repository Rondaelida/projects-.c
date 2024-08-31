#include "../test.h"

void run_not_equals_test(s21_decimal decimal_a, s21_decimal decimal_b,
                         int correct_answer) {
  int tested_value = s21_is_not_equal(decimal_a, decimal_b);
  ck_assert_msg(tested_value == correct_answer,
                "FALSE: correct is '%s', but given is '%d'."
                "decimal_a is '%c%d:%d:%d:%d'. decimal_b is '%c%d:%d:%d:%d'",
                correct_answer ? "equals" : "not equals", tested_value,
                get_bit(127, decimal_a) == 0 ? '+' : '-', decimal_a.bits[3],
                decimal_a.bits[2], decimal_a.bits[1], decimal_a.bits[0],
                get_bit(127, decimal_b) == 0 ? '+' : '-', decimal_b.bits[3],
                decimal_b.bits[2], decimal_b.bits[1], decimal_b.bits[0]);
}

START_TEST(a1) {
  s21_decimal decimal_a, decimal_b;
  decimal_a.bits[0] = decimal_a.bits[1] = decimal_a.bits[2] =
      decimal_a.bits[3] = 0;
  decimal_b.bits[0] = decimal_b.bits[1] = decimal_b.bits[2] =
      decimal_b.bits[3] = 0;
  run_not_equals_test(decimal_a, decimal_b, 0);
  decimal_a.bits[0] = 1;
  run_not_equals_test(decimal_a, decimal_b, 1);
  decimal_b.bits[0] = 1;
  run_not_equals_test(decimal_a, decimal_b, 0);
  decimal_a.bits[1] = 123123;
  run_not_equals_test(decimal_a, decimal_b, 1);
  decimal_b.bits[1] = 123122;
  run_not_equals_test(decimal_a, decimal_b, 1);
  decimal_b.bits[1]++;
  run_not_equals_test(decimal_a, decimal_b, 0);
  decimal_a.bits[2] = 876543321;
  decimal_b.bits[1] = 876543321;
  run_not_equals_test(decimal_a, decimal_b, 1);
  decimal_a.bits[0] = 876543321;
  decimal_b.bits[2] = 876543321;
  run_not_equals_test(decimal_a, decimal_b, 1);
  decimal_a.bits[1] = 876543321;
  decimal_b.bits[0] = 876543321;
  run_not_equals_test(decimal_a, decimal_b, 0);
  decimal_b.bits[3] = 1 << 31;
  run_not_equals_test(decimal_a, decimal_b, 1);
}
END_TEST

START_TEST(a2) {
  s21_decimal decimal_a, decimal_b;
  decimal_a.bits[0] = decimal_a.bits[1] = decimal_a.bits[2] =
      decimal_a.bits[3] = 0;
  decimal_b.bits[0] = decimal_b.bits[1] = decimal_b.bits[2] =
      decimal_b.bits[3] = 0;
  decimal_a.bits[0] = 1230;
  set_bit(32 * 3 + 16, 1, &decimal_a);
  decimal_b.bits[0] = 123;
  run_not_equals_test(decimal_a, decimal_b, 0);
  // 1230 / 10^1 == 123 / 10^0

  decimal_a.bits[0] = 12300;
  // set_bit(32 * 3 + 17, 1, &decimal_a);
  set_scale(2, &decimal_a);
  decimal_b.bits[0] = 123;
  run_not_equals_test(decimal_a, decimal_b, 0);

  decimal_a.bits[0] = 9990;
  set_scale(1, &decimal_a);
  decimal_b.bits[0] = 999;
  run_not_equals_test(decimal_a, decimal_b, 0);

  decimal_a.bits[0] = 999;
  set_scale(0, &decimal_a);
  decimal_b.bits[0] = 999;
  run_not_equals_test(decimal_a, decimal_b, 0);

  decimal_a.bits[0] = 9990000;
  set_scale(4, &decimal_a);
  decimal_b.bits[0] = 999;
  run_not_equals_test(decimal_a, decimal_b, 0);

  set_bit(127, 1, &decimal_a);
  run_not_equals_test(decimal_a, decimal_b, 1);

  set_bit(127, 1, &decimal_b);
  run_not_equals_test(decimal_a, decimal_b, 0);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[1] = 87956351;
  set_scale(28, &decimal_a);
  decimal_b.bits[1] = 879563510;
  set_scale(29, &decimal_b);
  run_not_equals_test(decimal_a, decimal_b, 0);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[0] = 81;
  set_scale(28, &decimal_a);
  decimal_b.bits[2] =
      0b11010001011000010100110110111;  // 110100010110000101001101101111101101101001100000011101011101000100100000000000000000000000000
  decimal_b.bits[1] = 0b11011011010011000000111010111010;
  decimal_b.bits[0] = 0b00100100000000000000000000000000;
  set_scale(54, &decimal_b);  // b=8100000000000000000000000000;
  run_not_equals_test(decimal_a, decimal_b, 0);

  set_bit(127, 1, &decimal_b);
  run_not_equals_test(decimal_a, decimal_b, 1);

  set_bit(127, 1, &decimal_a);
  run_not_equals_test(decimal_a, decimal_b, 0);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_b.bits[0] = 0b1110011001100000000;
  decimal_b.bits[1] = 0b11111111111111001111111111000011;
  decimal_b.bits[2] = 0b00111110110010101010101010101101;
  // b=2372202104067414713905920
  set_scale(55, &decimal_b);
  decimal_a.bits[0] = 0b11100111111111100001111100110011;
  decimal_a.bits[1] = 0b10101101111111111111110011111111;
  decimal_a.bits[2] = 0b001111101100101010101010;
  set_scale(65, &decimal_a);
  // a=75910467330157271450525491
  run_not_equals_test(decimal_a, decimal_b, 1);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(55, &decimal_b);
  set_scale(65, &decimal_a);
  run_not_equals_test(decimal_a, decimal_b, 0);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(0, &decimal_b);
  set_scale(15, &decimal_a);
  run_not_equals_test(decimal_a, decimal_b, 0);

  set_bit(127, 1, &decimal_a);
  run_not_equals_test(decimal_a, decimal_b, 0);

  set_bit(127, 1, &decimal_b);
  run_not_equals_test(decimal_a, decimal_b, 0);

  decimal_a.bits[1] = 0b10101101111111111101110011111111;
  run_not_equals_test(decimal_a, decimal_b, 1);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_b.bits[0] = 0b11111111111111111111111111111000;
  decimal_b.bits[1] = 0b01101110001111010010000101011100;
  decimal_b.bits[2] = 0b00001110001111010010000101011100;
  // 0b000011100011110100100001010111000110111000111101001000010101110011111111111111111111111111111000
  //  4406692155633254822441910264
  decimal_b.bits[3] = 0b10000000000011110000000000000000;

  decimal_a.bits[0] = 0b11111111111111111111111110110000;
  decimal_a.bits[1] = 0b01001110011000110100110110100001;
  decimal_a.bits[2] = 0b10001110011000110100110110011100;
  // 0b100011100110001101001101100111000100111001100011010011011010000111111111111111111111111110110000
  //  44066921556332548224419102640
  decimal_a.bits[3] = 0b10000000000100000000000000000000;
  run_not_equals_test(decimal_a, decimal_b, 0);
  decimal_a.bits[0]++;
  run_not_equals_test(decimal_a, decimal_b, 1);
  decimal_a.bits[0]--;
  decimal_a.bits[1] = 0b01001110111000110101110110100001;
  run_not_equals_test(decimal_a, decimal_b, 1);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(0, &decimal_a);
  set_scale(1, &decimal_b);
  decimal_a.bits[0] = 123;
  decimal_b.bits[0] = 1234;
  run_not_equals_test(decimal_a, decimal_b, 1);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(27, &decimal_a);
  set_scale(28, &decimal_b);
  decimal_a.bits[0] = 123;
  decimal_b.bits[0] = 1234;
  run_not_equals_test(decimal_a, decimal_b, 1);

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(28, &decimal_a);
  set_scale(29, &decimal_b);
  decimal_a.bits[0] = 123;
  decimal_b.bits[0] = 1236;
  run_not_equals_test(decimal_a, decimal_b, 1);
}
END_TEST

Suite *suite_s21_is_not_equal(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_is_not_equal\033[0m");
  TCase *tc = tcase_create("s21_is_equal_tc");

  tcase_add_test(tc, a1);
  tcase_add_test(tc, a2);

  suite_add_tcase(s, tc);
  return s;
}
