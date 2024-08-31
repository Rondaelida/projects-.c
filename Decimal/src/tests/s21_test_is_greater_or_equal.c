#include "../test.h"

void run_greater_or_equal_test(s21_decimal decimal_a, s21_decimal decimal_b,
                               int correct_answer) {
  int tested_value = s21_is_greater_or_equal(decimal_a, decimal_b);
  ck_assert_msg(tested_value == correct_answer,
                "FALSE: correct is '%s', but given is '%d'."
                "decimal_a is '%c%d:%d:%d:%d'. decimal_b is '%c%d:%d:%d:%d'",
                correct_answer ? "less" : "not less", tested_value,
                get_bit(127, decimal_a) == 0 ? '+' : '-', get_scale(decimal_a),
                decimal_a.bits[2], decimal_a.bits[1], decimal_a.bits[0],
                get_bit(127, decimal_b) == 0 ? '+' : '-', get_scale(decimal_b),
                decimal_b.bits[2], decimal_b.bits[1], decimal_b.bits[0]);
}

START_TEST(test_suite_1_simple_level) {
  s21_decimal decimal_a, decimal_b;
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[0] = 1;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_b.bits[2] = 78797997;
  decimal_a.bits[2] = 78797997;
  decimal_b.bits[1] = 78797997;
  decimal_a.bits[1] = 78797997;
  decimal_b.bits[0] = 111;
  decimal_a.bits[0] = 78797997;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_b.bits[0] = 12333;
  decimal_a.bits[2] = 78797997;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[2] = 78797997;
  decimal_b.bits[2] = 78797997;
  set_bit(127, 1, &decimal_b);
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[2] = 111;
  decimal_b.bits[2] = 1;
  decimal_a.bits[1] = 55555;
  decimal_b.bits[1] = 55555;
  decimal_a.bits[0] = 78797997;
  decimal_b.bits[0] = 78797997;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[1] = 1;
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
}

START_TEST(test_suite_2_average_level) {
  s21_decimal decimal_a, decimal_b;
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[0] = decimal_a.bits[1] = decimal_a.bits[2] = 1;
  decimal_b.bits[0] = decimal_b.bits[1] = decimal_b.bits[2] = 1;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)
  set_scale(0, &decimal_a);
  set_scale(15, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2) 00000100101100100101110010101101 00000100101100100101110010101101
  // 00000000000000000000000001101111 a(10) 1453566484518367847214219375 b(2)
  // 00000100101100100101110010101101 00000100101100100101110010101101
  // 00000000000000000000001100010011 b(10) 1453566484518367847214220051
  decimal_a.bits[2] = 78797997;
  decimal_b.bits[2] = 78797997;
  decimal_a.bits[1] = 78797997;
  decimal_b.bits[1] = 78797997;
  decimal_a.bits[0] = 111;
  decimal_b.bits[0] = 787;
  decimal_a.bits[3] = 0;
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_scale(1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(15, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(15, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 0, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 0, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2) 00000100101100100101110010101101 00000000000000000000000001101111
  // 00000100101100100101110010101101 a(10) 1453566484179933503929081005 b(2)
  // 00000100101100100101110010101101 00000100101100100101110010101101
  // 00000100101100100101110010101101 b(10) 1453566484518367847293017261
  decimal_a.bits[2] = 78797997;
  decimal_b.bits[2] = 78797997;
  decimal_a.bits[1] = 111;
  decimal_b.bits[1] = 78797997;
  decimal_a.bits[0] = 78797997;
  decimal_b.bits[0] = 78797997;
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(0, &decimal_a);
  set_scale(1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2) 00000100101100100101110010101101 00000000000000000000000001101111
  // 00000100101100100101110010101101 a(10) 1453566484179933503929081005 b(2)
  // 00000100101100100101110010101101 00000100101100100101110010101101
  // 00000100101100100101110010101101 b(10) 1453566484518367847293017261
  decimal_a.bits[2] = 78797997;
  decimal_b.bits[2] = 78797997;
  decimal_a.bits[1] = 111;
  decimal_b.bits[1] = 78797997;
  decimal_a.bits[0] = 78797997;
  decimal_b.bits[0] = 78797997;
  set_bit(127, 1, &decimal_a);
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_scale(0, &decimal_a);
  set_scale(1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 0, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 0, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2)  00000000000000000000000000010110 00000100101100100101110010101101
  // 00000100101100100101110010101101 a(10) 406166804441794239661 b(2)
  // 00000100101100100101110010101101 00000100101100100101110010101101
  // 00000100101100100101110010101101 b(10) 1453566484518367847293017261
  decimal_a.bits[2] = 22;
  decimal_b.bits[2] = 78797997;
  decimal_a.bits[1] = 78797997;
  decimal_b.bits[1] = 78797997;
  decimal_a.bits[0] = 78797997;
  decimal_b.bits[0] = 78797997;
  set_scale(3, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(7, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_scale(9, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_b.bits[0] = 0b1111111;  // b(10) = 127
  set_scale(16, &decimal_b);
  decimal_a.bits[0] = 0b11111;                         // a(10) = 31
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
}

START_TEST(test_suite_3_hard_level) {
  s21_decimal decimal_a, decimal_b;
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_b.bits[0] = 1;
  decimal_a.bits[0] = 1;
  set_scale(15, &decimal_b);
  set_scale(7, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2)  00000000101111000110000101001110 00000011011111011110111000001100
  // a(10) 53024283315531276
  // b(2) 00000000000000000000000001100100
  // b(10) 100
  decimal_a.bits[1] = 12345678;
  decimal_a.bits[0] = 58584588;
  decimal_b.bits[0] = 100;
  set_scale(16, &decimal_a);
  set_scale(2, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b

  // (get_scale(*dec1) > get_scale(*dec2)) && (get_scale(*dec1) > 28) &&
  // (get_scale(*dec2) <= 28)
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2)  00000000101111000110000101001110 00000011011111011110111000001100
  // a(10) 53024283315531276
  // b(2) 00000000000000000000000001100100
  // b(10) 100
  decimal_a.bits[1] = 12345678;
  decimal_a.bits[0] = 58584588;
  decimal_b.bits[0] = 100;
  set_scale(35, &decimal_a);  // -> a(10) 5302428331,5531276
  set_scale(1, &decimal_b);   // -> b(10) 100000000000000000000000000000
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2)  00000000000000000000000001100100
  // a(10) 100
  // b(2) 00000000000000000000000001100100
  // b(10) 100
  decimal_a.bits[0] = 100;
  decimal_b.bits[0] = 100;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)
  set_scale(35, &decimal_a);                           // -> a(10) 0,0000100
  set_scale(1, &decimal_b);  // -> b(10) 100000000000000000000000000000
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // a(2)  00000000000000000000000000000001 00000000000000000000000000000001
  // 00000000000000000000000001100100 a(10) 18446744078004519012 b(2)
  // 00000000000000000000000001100100 b(10) 100
  decimal_a.bits[0] = 100;
  decimal_a.bits[1] = 1;
  decimal_a.bits[2] = 1;
  decimal_b.bits[0] = 100;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_scale(31, &decimal_a);  // -> a(10) 18446744078004519,012
  set_scale(18, &decimal_b);  // -> b(10) 1000000000000
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // b(2)  00000000000000000000000000000001 00000000000000000000000000000000
  // 00000000000000000000000000000001 b(10)  18446744073709551617 a(2)
  // 00000000000000000000000001100100 00000000000000000000000000000000
  // 00000000000000000000000001100100 a(10) 1844674407370955161700
  decimal_b.bits[0] = 1;
  decimal_b.bits[2] = 1;
  decimal_a.bits[0] = 100;
  decimal_a.bits[2] = 100;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_scale(31, &decimal_a);  // -> a(10) 1844674407370955161,700
  set_scale(28, &decimal_b);  // -> b(10) 18446744073709551617
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)

  // ((get_scale(*dec2) > get_scale(*dec1)) && (get_scale(*dec2) > 28) &&
  // (get_scale(*dec1) <= 28))
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // b(2)  00000000101111000110000101001110 00000011011111011110111000001100
  // b(10) 53024283315531276
  // a(2) 00000000000000000000000001100100
  // a(10) 100
  decimal_b.bits[1] = 12345678;
  decimal_b.bits[0] = 58584588;
  decimal_a.bits[0] = 100;
  set_scale(35, &decimal_b);  // -> b(10) 5302428331,5531276
  set_scale(1, &decimal_a);   // -> a(10) 100000000000000000000000000000
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // b(2)  00000000000000000000000001100100
  // b(10) 100
  // a(2) 00000000000000000000000001100100
  // a(10) 100
  decimal_a.bits[0] = 100;
  decimal_b.bits[0] = 100;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)
  set_scale(35, &decimal_b);                           // -> b(10) 0,0000100
  set_scale(1, &decimal_a);  // -> a(10) 100000000000000000000000000000
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // a > b
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // a < b

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  // b(2)  00000000000000000000000000000001 00000000000000000000000000000001
  // 00000000000000000000000001100100 b(10) 18446744078004519012 a(2)
  // 00000000000000000000000001100100 a(10) 100
  decimal_b.bits[0] = 100;
  decimal_b.bits[1] = 1;
  decimal_b.bits[2] = 1;
  decimal_a.bits[0] = 100;
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(31, &decimal_b);  // -> b(10) 18446744078004519,012
  set_scale(18, &decimal_a);  // -> a(10) 1000000000000
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)

  // ((get_scale(*dec2) > 28) && (get_scale(*dec1) > 28))
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[0] = 1;
  decimal_a.bits[2] = 100;
  decimal_b.bits[1] = 1;
  decimal_b.bits[2] = 100;
  // a(2) 00000000000000000000000001100100 00000000000000000000000000000000
  // 00000000000000000000000000000001 a(10) 1844674407370955161601 b(2)
  // 00000000000000000000000001100100 00000000000000000000000000000001
  // 00000000000000000000000000000000 b(10) 1844674407375250128896
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(38, &decimal_b);  // -> b(10) 184467440737,5250128896
  set_scale(38, &decimal_a);  // -> a(10) 184467440737,0955161601
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[0] = 1;
  decimal_a.bits[2] = 100;
  decimal_b.bits[1] = 1;
  decimal_b.bits[2] = 100;
  // a(2) 00000000000000000000000001100100 00000000000000000000000000000000
  // 00000000000000000000000000000001 a(10) 1844674407370955161601 b(2)
  // 00000000000000000000000001100100 00000000000000000000000000000001
  // 00000000000000000000000000000000 b(10) 1844674407375250128896
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_scale(38, &decimal_b);  // -> b(10) 184467440737,5250128896
  set_scale(32, &decimal_a);  // -> a(10) 184467440737095516,1601
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)
}

START_TEST(test_with_zero) {
  s21_decimal decimal_a, decimal_b;
  make_zero(&decimal_a);
  make_zero(&decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(14, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  decimal_a.bits[0] = 0b00000000000000000000000000000001;
  set_scale(15, &decimal_b);
  decimal_a.bits[3] = 0;
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a > b)
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 0);  // (a < b)

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(34, &decimal_b);
  set_scale(33, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(32, &decimal_b);
  set_scale(12, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(12, &decimal_b);
  set_scale(32, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(12, &decimal_b);
  set_scale(27, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(27, &decimal_b);
  set_scale(12, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0

  make_zero(&decimal_a);
  make_zero(&decimal_b);
  set_scale(5, &decimal_b);
  set_scale(5, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_a);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
  set_bit(127, 1, &decimal_b);
  run_greater_or_equal_test(decimal_a, decimal_b, 1);  // (a == b) == 0
}

Suite *suite_s21_is_greater_or_equal(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_is_greater_or_equal\033[0m");
  TCase *tc = tcase_create("s21_is_greater_tc");

  tcase_add_test(tc, test_suite_1_simple_level);
  tcase_add_test(tc, test_suite_2_average_level);
  tcase_add_test(tc, test_suite_3_hard_level);
  tcase_add_test(tc, test_with_zero);
  suite_add_tcase(s, tc);
  return s;
}