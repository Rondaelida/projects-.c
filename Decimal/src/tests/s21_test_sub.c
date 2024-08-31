#include "../test.h"
#define SIZE_OF_DECIMAL 3

void run_sub_test(s21_decimal decimal_a, s21_decimal decimal_b,
                  int correct_answer, s21_decimal *result) {
  int tested_value = s21_sub(decimal_a, decimal_b, &(*result));
  ck_assert_msg(tested_value == correct_answer,
                "FALSE: correct is '%d', but given is '%d'."
                "decimal_a is '%c%u:%u:%u:%u'. decimal_b is '%c%u:%u:%u:%u'",
                correct_answer, tested_value,
                get_bit(127, decimal_a) == 0 ? '+' : '-', get_scale(decimal_a),
                decimal_a.bits[2], decimal_a.bits[1], decimal_a.bits[0],
                get_bit(127, decimal_b) == 0 ? '+' : '-', get_scale(decimal_b),
                decimal_b.bits[2], decimal_b.bits[1], decimal_b.bits[0]);
}

START_TEST(test_suite_1_simple_level) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906
  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  s21_sub(a, b, &result);
  // 1101011111001000 10100111111111111010000000010101
  // 01010100100110100111101001101011 == 1019010248202052500617835
  ck_assert_msg(result.bits[0] == 0b01010100100110100111101001101011 and
                    result.bits[1] == 0b10100111111111111010000000010101 and
                    result.bits[2] == 0b1101011111001000 and
                    get_scale(result) == 0 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906

  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  s21_sub(b, a, &result);
  // 1101011111001000 10100111111111111010000000010101
  // 01010100100110100111101001101011 == -1019010248202052500617835
  ck_assert_msg(result.bits[0] == 0b01010100100110100111101001101011 and
                    result.bits[1] == 0b10100111111111111010000000010101 and
                    result.bits[2] == 0b1101011111001000 and
                    get_scale(result) == 0 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[3] = 0b00000000000000000000000000000001;
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906

  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  set_bit(127, 1, &a);
  s21_sub(a, b, &result);
  // -10111110011010000 01111010101001011111010100111111
  // 11010110000110101011101000111111 == -1798345023997295076227647
  ck_assert_msg(result.bits[0] == 0b11010110000110101011101000111111 and
                    result.bits[1] == 0b01111010101001011111010100111111 and
                    result.bits[2] == 0b10111110011010000 and
                    get_scale(result) == 0 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906

  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  set_bit(127, 1, &b);
  s21_sub(a, b, &result);
  // 10111110011010000 01111010101001011111010100111111
  // 11010110000110101011101000111111 == 1798345023997295076227647
  ck_assert_msg(result.bits[0] == 0b11010110000110101011101000111111 and
                    result.bits[1] == 0b01111010101001011111010100111111 and
                    result.bits[2] == 0b10111110011010000 and
                    get_scale(result) == 0 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  set_bit(127, 1, &a);
  s21_sub(a, b, &result);
  // 1101011111001000 10100111111111111010000000010101
  // 01010100100110100111101001101011 == -1019010248202052500617835
  ck_assert_msg(result.bits[0] == 0b01010100100110100111101001101011 and
                    result.bits[1] == 0b10100111111111111010000000010101 and
                    result.bits[2] == 0b1101011111001000 and
                    get_scale(result) == 0 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);
}

START_TEST(test_suite_2_average_level) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b00000000000000000000011100101010;
  b.bits[2] = 0b11111100000;
  // b(2) 11111100000  00000000000000000000000000000000
  // 00000000000000000000011100101010
  //  b(10) 37188636052598456059690
  set_scale(2, &a);
  set_scale(4, &b);
  s21_sub(a, b, &result);
  // a(10) 1294961434266897796302900
  // result = 1257772798214299340243210
  // 10000101001011000 00000000000000010000101000000100
  // 00000000000000000000000100001010
  ck_assert_msg(result.bits[0] == 0b00000000000000000000000100001010 and
                    result.bits[1] == 0b00000000000000010000101000000100 and
                    result.bits[2] == 0b10000101001011000 and
                    get_scale(result) == 4 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b00000000000000000000011100101010;
  b.bits[2] = 0b11111100000;
  // b(2) 11111100000  00000000000000000000000000000000
  // 00000000000000000000011100101010
  //  b(10) 37188636052598456059690
  set_scale(29, &a);
  set_scale(28, &b);
  s21_sub(a, b, &result);
  // a(10) 1294961434266897796302,9 ~ 1294961434266897796303
  // result = -35893674618331558263387
  // 11110011001 11001100110011001100110010001000
  // 10110011001100110011101001011011
  ck_assert_msg(result.bits[0] == 0b10110011001100110011101001011011 and
                    result.bits[1] == 0b11001100110011001100110010001000 and
                    result.bits[2] == 0b11110011001 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b00000000000000000000011100101010;
  b.bits[2] = 0b11111100000;
  // b(2) 11111100000  00000000000000000000000000000000
  // 00000000000000000000011100101010
  //  b(10) 37188636052598456059690
  set_scale(28, &a);
  set_scale(33, &b);
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  // b-a = -result
  s21_sub(a, b, &result);
  // b(10) 371886360525984560,59690 ~ 371886360525984561
  // result = -12949242456308451978468
  // -1010111101 11111010110101101100110111111100
  // 01010000000010010010110011100100
  ck_assert_msg(result.bits[0] == 0b01010000000010010010110011100100 and
                    result.bits[1] == 0b11111010110101101100110111111100 and
                    result.bits[2] == 0b1010111101 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b11111111111111111110010000000010;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111011111;
  // b(2)
  // 111110111111111111111111111111111111111111111111111111111111110010000000010
  //  b(10) 37188636052598456050690
  set_scale(28, &a);
  set_scale(33, &b);
  set_bit(127, 1, &a);
  // -a-b = -result
  s21_sub(a, b, &result);
  // b(10) 371886360525984560,50690 ~ 371886360525984561
  // result = -12949986229029503947590 = -1010111110
  // 00000101001010010011011101010101 10101111111101101101001101000110
  ck_assert_msg(result.bits[0] == 0b10101111111101101101001101000110 and
                    result.bits[1] == 0b00000101001010010011011101010101 and
                    result.bits[2] == 0b1010111110 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);
}

START_TEST(test_suite_3_hard_level) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  // 79,228,162,514,264,337,593,543,950,335 - 0.6 =
  // 79,228,162,514,264,337,593,543,950,334
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000110;
  set_scale(29, &b);
  set_scale(28, &a);
  s21_sub(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111110 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  // -79,228,162,514,264,337,593,543,950,335 - 0.6 =
  // -79,228,162,514,264,337,593,543,950,33|6 =
  // -79,228,162,514,264,337,593,543,950,34
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000110;
  set_scale(29, &b);
  set_scale(28, &a);
  set_bit(127, 1, &a);
  s21_sub(a, b, &result);
  // 11001100110011001100110011001 10011001100110011001100110011001
  // 10011001100110011001100110011010
  ck_assert_msg(result.bits[0] == 0b10011001100110011001100110011010 and
                    result.bits[1] == 0b10011001100110011001100110011001 and
                    result.bits[2] == 0b11001100110011001100110011001 and
                    get_scale(result) == 27 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  // b-a = -result
  set_bit(127, 1, &b);
  s21_sub(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111110 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  // -full -rand_value (= -big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b001111;
  b.bits[1] = 0b100111111111111111111;
  b.bits[2] = 0b110011111111111111111111;
  set_bit(127, 1, &a);
  s21_sub(a, b, &result);
  run_sub_test(a, b, 2, &result);

  // full +rand_value (= +big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b001111;
  b.bits[1] = 0b100111111111111111111;
  b.bits[2] = 0b110011111111111111111111;
  set_bit(127, 1, &b);
  s21_sub(a, b, &result);
  run_sub_test(a, b, 1, &result);

  // -full -full (= -big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b11111111111111111111111111111111;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111111111111111111111111111111;
  set_bit(127, 1, &a);
  s21_sub(a, b, &result);
  run_sub_test(a, b, 2, &result);

  make_zero(&a);
  make_zero(&b);
  // 79,228,162,514,264,337,593,543,950,335 -
  // 79,228,162,514,264,337,593,543,950,334
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b11111111111111111111111111111110;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111111111111111111111111111111;
  set_scale(29, &b);
  set_scale(28, &a);
  // b(10) 7922816251426433759354395033,4 ~ 7922816251426433759354395033
  s21_sub(a, b, &result);
  // result = 71305346262837903834189555302 = 11100110011001100110011001100110
  // 01100110011001100110011001100110 01100110011001100110011001100110
  ck_assert_msg(result.bits[0] == 0b01100110011001100110011001100110 and
                    result.bits[1] == 0b01100110011001100110011001100110 and
                    result.bits[2] == 0b11100110011001100110011001100110 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);
}

START_TEST(test_with_zero) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  s21_sub(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  set_bit(127, 1, &a);
  s21_sub(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  set_bit(127, 0, &a);
  set_bit(127, 1, &b);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  set_bit(127, 1, &a);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  s21_sub(a, b, &result);
  set_scale(28, &a);
  set_scale(33, &b);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  // full -full (= 0)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b11111111111111111111111111111111;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111111111111111111111111111111;
  s21_sub(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  b.bits[0] = 1;
  s21_sub(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b1 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_sub_test(a, b, 0, &result);
}

START_TEST(test_all) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -12344
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003038;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 12346
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000303A;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00010000;  // 0,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000005;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80010000;  // -0,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000005;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80010000;  // -12344,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E235;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00010000;  // 1,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000F;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00010000;  // 12345,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E23F;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00090000;  // 0,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80090000;  // -0,999999999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x3B9AC9FF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80090000;  // -12344,999999999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000B3A;
  val_ans.bits[0] = 0x4B56F9FF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00090000;  // 1,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x3B9ACA01;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00090000;  // 12345,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000B3A;
  val_ans.bits[0] = 0x4B56FA01;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_sub(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

Suite *suite_s21_sub(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_sub\033[0m");
  TCase *tc = tcase_create("s21_add_tc");

  tcase_add_test(tc, test_suite_1_simple_level);
  tcase_add_test(tc, test_suite_2_average_level);
  tcase_add_test(tc, test_suite_3_hard_level);
  tcase_add_test(tc, test_with_zero);
  tcase_add_test(tc, test_all);
  // tcase_add_test(tc, test_all1);
  // tcase_add_test(tc, test_all2);

  suite_add_tcase(s, tc);
  return s;
}