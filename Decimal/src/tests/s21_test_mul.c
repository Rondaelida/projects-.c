#include "../test.h"

void run_mul_test(s21_decimal decimal_a, s21_decimal decimal_b,
                  s21_decimal correct_decimal, int err_code) {
  s21_decimal tested_decimal;
  int tested_value = s21_mul(decimal_a, decimal_b, &tested_decimal);
  ck_assert_msg(
      tested_value == err_code and
          s21_is_equal(correct_decimal, tested_decimal),
      "FALSE: correct_decimal is '%c%u:%u:%u:%u'. tested_decimal is "
      "'%c%u:%u:%u:%u'",
      get_bit(127, decimal_a) == 0 ? '+' : '-', correct_decimal.bits[3],
      correct_decimal.bits[2], correct_decimal.bits[1], correct_decimal.bits[0],
      get_bit(127, decimal_b) == 0 ? '+' : '-', tested_decimal.bits[3],
      tested_decimal.bits[2], tested_decimal.bits[1], tested_decimal.bits[0]);
}

START_TEST(mul) {
  s21_decimal decimal_a = {{7, 0, 0, 0}};
  s21_decimal decimal_b = {{3, 0, 0, 0}};
  s21_decimal correct = {{21, 0, 0, 0}};
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0;
  decimal_b.bits[0] = 3;
  correct.bits[0] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 15;
  decimal_b.bits[0] = 3;
  correct.bits[0] = 45;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 8000;
  decimal_b.bits[0] = 0;
  correct.bits[0] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 12432;
  decimal_b.bits[0] = 123121;
  correct.bits[0] = 1530640272;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0;
  decimal_b.bits[0] = 1232100121;
  decimal_b.bits[1] = 1232100121;
  decimal_b.bits[2] = 3333399888;
  correct.bits[0] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 15;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b1101011100010110010101001010101;
  decimal_b.bits[2] = 0;
  correct.bits[0] = 0b01001011101110110100100100100101;
  correct.bits[1] = 0b01001101001001110111101011111110;
  correct.bits[2] = 0b110;
  // 110 01001101001001110111101011111110 01001011101110110100100100100101
  // 01001101001001110111101011111110 01001011101110110100100100100101
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0b1111;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  decimal_b.bits[0] = 0;
  decimal_b.bits[1] = 0;
  decimal_b.bits[2] =
      0b1011110111100101110011110000;  // 0000000000000000000000000000000000000000000000000000000000000000
  correct.bits[0] = 0;
  correct.bits[1] = 0;
  correct.bits[2] = 0b10110010000001110111001000010000;
  //                 10110010000001110111001000010110
  // 1270565157, 1294433022
  //
  // //  correct =
  // 101100100000011101110010000100000000000000000000000000000000000000000000000000000000000000000000
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0b00001100000000000000001111110111;
  decimal_a.bits[1] = 0b00000101100000000111100000000001;
  decimal_a.bits[2] = 0b00000000000000111111111110101111;
  decimal_b.bits[0] = 5;
  decimal_b.bits[1] = 0;
  decimal_b.bits[2] = 0;
  correct.bits[0] = 0b00111100000000000001001111010011;
  correct.bits[1] = 0b00011011100000100101100000000101;
  correct.bits[2] = 0b100111111111001101011;
  //////
  /// corr=24171047443186296626877395=1001111111110011010110001101110000010010110000000010100111100000000000001001111010011
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 15;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b1101011100010110010101001010101;
  decimal_b.bits[2] = 0b111110111100101110011110000;
  correct.bits[0] = 0b01001011101110110100100100100101;
  correct.bits[1] = 0b01001101001001110111101011111110;
  correct.bits[2] = 0b1110110000001110111001000010110;
  /// 11101100000011101110010000101100100110100100111011110101111111001001011101110110100100100100101
  /////////////10110010000001110111001000011100100110100100111011110101111111001001011101110110100100100100101;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  set_scale(28, &decimal_a);
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b1101011100010110010101001010101;
  decimal_b.bits[2] = 0b111110111100101110011110000;
  set_scale(12, &decimal_b);
  correct.bits[0] = 0;
  correct.bits[1] = 0;
  correct.bits[2] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 1;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  set_scale(14, &decimal_a);
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b1101011100010110010101001010101;
  decimal_b.bits[2] = 0b111110111100101110011110000;
  set_scale(12, &decimal_b);
  correct.bits[0] = 0b00111000001111111010111110001011;
  correct.bits[1] = 0b1101011100010110010101001010101;
  correct.bits[2] = 0b111110111100101110011110000;
  set_scale(26, &correct);
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0b00000000000000000011100001110101;
  decimal_a.bits[1] = 0b00000000000000111100011100011011;
  decimal_a.bits[2] = 0;
  set_scale(20, &decimal_a);
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b00000000000000000000000000010101;
  decimal_b.bits[2] = 0;
  set_scale(8, &decimal_b);
  correct.bits[0] = 0b10100011100000011010001010000111;
  correct.bits[1] = 0b01111110110100100011111010101001;
  correct.bits[2] = 0b10100000010100110110101;
  set_scale(28, &correct);
  ///////96911030594080823060832903=10100000010100110110101
  /// 01111110110100100011111010101001 10100011100000011010001010000111
  run_mul_test(decimal_a, decimal_b, correct, 0);

  decimal_a.bits[0] = 0b00000000000000000011100001110101;
  decimal_a.bits[1] = 0b00000000000000111100011100011011;
  decimal_a.bits[2] = 0;
  set_scale(20, &decimal_a);
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b00000000000000000000000000010101;
  decimal_b.bits[2] = 0;
  set_scale(8, &decimal_b);
  correct.bits[0] = 0b10100011100000011010001010000111;
  correct.bits[1] = 0b01111110110100100011111010101001;
  correct.bits[2] = 0b10100000010100110110101;
  set_scale(28, &correct);
  ///////96911030594080823060832903=10100000010100110110101
  /// 01111110110100100011111010101001 10100011100000011010001010000111
  run_mul_test(decimal_a, decimal_b, correct, 0);

  set_scale(0, &decimal_a);
  decimal_a.bits[0] = 15;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  set_scale(0, &decimal_b);
  decimal_b.bits[0] = 0b00111000001111111010111110001011;
  decimal_b.bits[1] = 0b01101011100010110010101001010101;
  decimal_b.bits[2] = 0b00001011110111100101110011110000;
  set_scale(0, &correct);
  correct.bits[0] = 0b01001011101110110100100100100101;
  // tested with no _  1001011101110110100100100100101;
  // tested is        11010100010111111000011101010001;
  correct.bits[1] = 0b01001101001001110111101011111110;
  // tested is        10100001010100001011111101111111;
  correct.bits[2] = 0b10110010000001110111001000010110;
  // tested with no _  0101010000001110111001000010110;
  // tested is        00011101110011011000101101101000;
  ///////////101100100000011101110010000101100100110100100111011110101111111001001011101110110100100100100101
  run_mul_test(decimal_a, decimal_b, correct, 0);

  set_scale(5, &decimal_a);
  decimal_a.bits[0] = 123450000;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  set_scale(28, &decimal_b);
  decimal_b.bits[0] = 1;
  decimal_b.bits[1] = 0;
  decimal_b.bits[2] = 0;
  set_scale(28, &correct);
  correct.bits[0] = 1234;
  correct.bits[1] = 0;
  correct.bits[2] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);

  set_scale(5, &decimal_a);
  decimal_a.bits[0] = 123550000;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  set_scale(28, &decimal_b);
  decimal_b.bits[0] = 1;
  decimal_b.bits[1] = 0;
  decimal_b.bits[2] = 0;
  set_scale(28, &correct);
  correct.bits[0] = 1236;
  correct.bits[1] = 0;
  correct.bits[2] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;

  // test number 0
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 1
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 2
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 3
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 4
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 5
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;

  // test number 6
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 7
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 8
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 9
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 10
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 11
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 12
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 13
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 14
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 15
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00010000;  // 0,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000005;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 16
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00010000;  // 6172,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000F11D;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 17
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80010000;  // -0,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000005;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 18
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80010000;  // -6172,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000F11D;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 19
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 39614081257132168796771975168
  val_ans.bits[2] = 0x80000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 20
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -39614081257132168796771975168
  val_ans.bits[2] = 0x80000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 21
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // #test test_mul22
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00090000;  // 0,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 23
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00090000;  // 0,000012345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // #test test_mul24
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80090000;  // -0,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 25
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80090000;  // -0,000012345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 26
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00090000;  // 79228162514264337593,543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 27
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80090000;  // -79228162514264337593,543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 28
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 29
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 30
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 31
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 32
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // #test test_mul33
  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 34
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 35
  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 36
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 37
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // #test test_mul38
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  /// #test test_mul39
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // #test test_mul40
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 41
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test number 42
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test number 43
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  // test number 44
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 45
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 46
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 47
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 48
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 49
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 50
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 51
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 52
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x001B0000;  // 79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 53
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x801B0000;  // -79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 54
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x801B0000;  // -79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 55
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x001B0000;  // 79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 56
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x001B0000;  // 79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 57
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x801B0000;  // -79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 58
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x801B0000;  // -79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 59
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x001B0000;  // 79,228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 60
  val1.bits[3] = 0x00000000;  // 9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000009;
  val2.bits[3] = 0x00000000;  // 10
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x0000000A;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 90
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000005A;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 61
  val1.bits[3] = 0x00000000;  // 9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000009;
  val2.bits[3] = 0x00000000;  // 10
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x0000000A;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 90
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000005A;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 62
  val1.bits[3] = 0x00000000;  // 9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000009;
  val2.bits[3] = 0x00000000;  // 10
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x0000000A;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 90
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000005A;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 63
  val1.bits[3] = 0x00000000;  // 9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000009;
  val2.bits[3] = 0x00000000;  // 10
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x0000000A;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 90
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000005A;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 64
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 65
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_14) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 66
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000002
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 67
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000002
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 68
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 69
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 70
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(mul_15) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;  // int_ans;
  // float float_ans;
  int SIZE_OF_DECIMAL = 7;
  // test number 71
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_mul(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test number 72
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  // test number 73
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test number 74
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test number 75
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);
}
END_TEST

START_TEST(mul_16) {
  s21_decimal val1, val2, val3;
  int int_res;  // int_ans;
  // float float_ans;
  // int SIZE_OF_DECIMAL = 7;
  // test number 76
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  // test number 77
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test number 78
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test number 79
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_mul(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);
}
END_TEST

START_TEST(last_test_for_debug) {
  s21_decimal decimal_a = {{7, 0, 0, 0}};
  s21_decimal decimal_b = {{3, 0, 0, 0}};
  s21_decimal correct = {{21, 0, 0, 0}};

  set_scale(5, &decimal_a);
  decimal_a.bits[0] = 123450000;
  decimal_a.bits[1] = 0;
  decimal_a.bits[2] = 0;
  set_scale(28, &decimal_b);
  decimal_b.bits[0] = 1;
  decimal_b.bits[1] = 0;
  decimal_b.bits[2] = 0;
  set_scale(28, &correct);
  correct.bits[0] = 1234;
  correct.bits[1] = 0;
  correct.bits[2] = 0;
  run_mul_test(decimal_a, decimal_b, correct, 0);
}
END_TEST

Suite *suite_s21_mul(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_mul\033[0m");
  TCase *tc = tcase_create("s21_mul_tc");

  tcase_add_test(tc, mul);

  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);

  tcase_add_test(tc, last_test_for_debug);

  suite_add_tcase(s, tc);
  return s;
}
