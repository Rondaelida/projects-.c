#include "../test.h"
#define SIZE_OF_DECIMAL 7

START_TEST(div1) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  //   int_ans;
  //   float float_ans;
  // test_div number1
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number2
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number3
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number4
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number5
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number6
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div2) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number7
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number8
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number9
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number10
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div3) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number11
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number12
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number13
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number14
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number19
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div4) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;

  // test_div number16
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number17
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number18
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number19
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number20
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);
}
END_TEST

START_TEST(div5) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number21
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number22
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number23
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number24
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number25
  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div6) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number26
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number27
  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number28
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number29
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number30
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div7) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number31
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number32
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number33
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number34
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number35
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div8) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number36
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number37
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number38
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number39
  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number40
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);
}
END_TEST

START_TEST(div9) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number41
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number42
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number43
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 3);

  // test_div number44
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number45
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div10) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number46
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number47
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number48
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  // test_div number49
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);

  // test_div number50
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 2);
}
END_TEST

START_TEST(div11) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number51
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);

  // test_div number52
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number53
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number54
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number55
  val1.bits[3] = 0x801B0000;  // -0,000000000000000000000000002
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x801B0000;  // -0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div12) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number56
  val1.bits[3] = 0x00000000;  // 2
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x00000000;  // 2
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number57
  val1.bits[3] = 0x00000000;  // 0.00002
  set_scale(5, &val1);
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x00000000;  // 0.0002
  set_scale(4, &val2);
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 0.1
  set_scale(1, &val_ans);
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number58
  val1.bits[3] = 0x00000000;  // 0.0002
  set_scale(4, &val1);
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000002;
  val2.bits[3] = 0x00000000;  // 0.00002
  set_scale(5, &val2);
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 10
  set_scale(0, &val_ans);
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 10;
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  // test_div number59
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number60
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div13) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number61
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number62
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFE;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number64
  val1.bits[3] = 0x00000000;  // 30064771176
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000007;
  val1.bits[0] = 0x00000068;
  val2.bits[3] = 0x00000000;  // 3
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000003;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 10021590392
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000002;
  val_ans.bits[0] = 0x55555578;
  //// 0b  |10|01010101010101010101010101111000|;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number65
  val1.bits[3] = 0x00000000;  // 32768
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00008000;
  val2.bits[3] = 0x80000000;  // -2
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -16384
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00004000;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);
}
END_TEST

START_TEST(div14) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  // test_div number66
  val1.bits[3] = 0x00000000;  // 32768
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00008000;
  val2.bits[3] = 0x00000000;  // 2
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00000000;  // 16384
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00004000;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number67
  val1.bits[3] = 0x00000000;  // 30064771176
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000007;
  val1.bits[0] = 0x00000068;
  val2.bits[3] = 0x80000000;  // -2
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000002;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x80000000;  // -15032385588
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000003;
  val_ans.bits[0] = 0x80000034;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number68
  val1.bits[3] = 0x00000000;  // 442320
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x0006BFD0;
  val2.bits[3] = 0x00000000;  // 28
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x0000001C;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0x00180000;  // 15797,142857142857142857142857
  val_ans.bits[2] = 0x330B171E;
  val_ans.bits[1] = 0x3D290E5D;
  val_ans.bits[0] = 0x35249249;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number69
  val1.bits[3] = 0;
  set_scale(16, &val1);  // -373729266678.2929217788231930
  set_bit(127, 1, &val1);
  val1.bits[2] = 0xC136A81;
  val1.bits[1] = 0x6D5083E0;
  val1.bits[0] = 0x5832C0FA;
  val2.bits[3] = 0;  // 929292932911331.313221231231
  set_scale(12, &val2);
  val2.bits[2] = 0x300B16E;
  val2.bits[1] = 0xD63EB914;
  val2.bits[0] = 0xD4CDE27F;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0;  //-0.0004021651875770289332754622
  set_scale(28, &val_ans);
  set_bit(127, 1, &val_ans);
  val_ans.bits[2] = 0x3539E;
  val_ans.bits[1] = 0x2F5E6C3C;
  val_ans.bits[0] = 0x9AF118BE;  // actual is 3539E 2F5E6C3C 9AF118BE
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);

  // test_div number70
  val1.bits[3] = 0;  // 100000000
  val1.bits[2] = 0;
  val1.bits[1] = 0;
  val1.bits[0] = 0x5F5E100;
  val2.bits[3] = 0;  // 3
  val2.bits[2] = 0;
  val2.bits[1] = 0;
  val2.bits[0] = 3;
  int_res = s21_div(val1, val2, &val3);
  val_ans.bits[3] = 0;  // 33333333.333333333333333333333
  set_scale(21, &val_ans);
  val_ans.bits[2] = 0x6BB4AFE4;
  val_ans.bits[1] = 0xCF2607EE;
  val_ans.bits[0] = 0x35555555;
  // ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_msg(s21_is_equal(val_ans, val3), "Failed!");
  ck_assert_int_eq(int_res, 0);
}
END_TEST

Suite *suite_s21_div(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_div\033[0m");
  TCase *tc = tcase_create("s21_div_tc");

  tcase_add_test(tc, div1);
  tcase_add_test(tc, div2);
  tcase_add_test(tc, div3);
  tcase_add_test(tc, div4);
  tcase_add_test(tc, div5);
  tcase_add_test(tc, div6);
  tcase_add_test(tc, div7);
  tcase_add_test(tc, div8);
  tcase_add_test(tc, div9);
  tcase_add_test(tc, div10);
  tcase_add_test(tc, div11);
  tcase_add_test(tc, div12);
  tcase_add_test(tc, div13);
  tcase_add_test(tc, div14);

  suite_add_tcase(s, tc);
  return s;
}
