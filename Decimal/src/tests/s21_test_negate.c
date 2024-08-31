#include <check.h>
#include <stdio.h>

#include "../test.h"
#define SIZE_OF_DECIMAL 16

START_TEST(null) {
  s21_decimal val;
  val.bits[0] = val.bits[1] = val.bits[2] = 0xFFFFFFFF;
  val.bits[3] = 0x00000000;
  ck_assert_int_eq(s21_negate(val, NULL), 1);
}
END_TEST

START_TEST(plus) {
  s21_decimal val1, val2, val_ans;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -9999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00010000;  // 7922816251426433759354395033,5
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80010000;  // -7922816251426433759354395033,5
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 7,9228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x801C0000;  // -7,9228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,1000000000000000000000000000
  val1.bits[2] = 0x033B2E3C;
  val1.bits[1] = 0x9FD0803C;
  val1.bits[0] = 0xE8000000;
  val_ans.bits[3] = 0x801C0000;  // -0,1000000000000000000000000000
  val_ans.bits[2] = 0x033B2E3C;
  val_ans.bits[1] = 0x9FD0803C;
  val_ans.bits[0] = 0xE8000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0100000000000000000000000000
  val1.bits[2] = 0x0052B7D2;
  val1.bits[1] = 0xDCC80CD2;
  val1.bits[0] = 0xE4000000;
  val_ans.bits[3] = 0x801C0000;  // -0,0100000000000000000000000000
  val_ans.bits[2] = 0x0052B7D2;
  val_ans.bits[1] = 0xDCC80CD2;
  val_ans.bits[0] = 0xE4000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001B0000;  // 9,999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x801B0000;  // -9,999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000B0000;  // 99999999999999999,99999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x800B0000;  // -99999999999999999,99999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,4999999999999999999999999999
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x87FFFFFF;
  val_ans.bits[3] = 0x801C0000;  // -0,4999999999999999999999999999
  val_ans.bits[2] = 0x1027E72F;
  val_ans.bits[1] = 0x1F128130;
  val_ans.bits[0] = 0x87FFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,5000000000000000000000000000
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000000;
  val_ans.bits[3] = 0x801C0000;  // -0,5000000000000000000000000000
  val_ans.bits[2] = 0x1027E72F;
  val_ans.bits[1] = 0x1F128130;
  val_ans.bits[0] = 0x88000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,5000000000000000000000000001
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000001;
  val_ans.bits[3] = 0x801C0000;  // -0,5000000000000000000000000001
  val_ans.bits[2] = 0x1027E72F;
  val_ans.bits[1] = 0x1F128130;
  val_ans.bits[0] = 0x88000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 1,4999999999999999999999999999
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x97FFFFFF;
  val_ans.bits[3] = 0x801C0000;  // -1,4999999999999999999999999999
  val_ans.bits[2] = 0x3077B58D;
  val_ans.bits[1] = 0x5D378391;
  val_ans.bits[0] = 0x97FFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 1,5000000000000000000000000000
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000000;
  val_ans.bits[3] = 0x801C0000;  // -1,5000000000000000000000000000
  val_ans.bits[2] = 0x3077B58D;
  val_ans.bits[1] = 0x5D378391;
  val_ans.bits[0] = 0x98000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 1,5000000000000000000000000001
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000001;
  val_ans.bits[3] = 0x801C0000;  // -1,5000000000000000000000000001
  val_ans.bits[2] = 0x3077B58D;
  val_ans.bits[1] = 0x5D378391;
  val_ans.bits[0] = 0x98000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 2,4999999999999999999999999999
  val1.bits[2] = 0x50C783EB;
  val1.bits[1] = 0x9B5C85F2;
  val1.bits[0] = 0xA7FFFFFF;
  val_ans.bits[3] = 0x801C0000;  // -2,4999999999999999999999999999
  val_ans.bits[2] = 0x50C783EB;
  val_ans.bits[1] = 0x9B5C85F2;
  val_ans.bits[0] = 0xA7FFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00090000;  // 0,123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80090000;  // -0,123456789
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00080000;  // 1,23456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80080000;  // -1,23456789
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00010000;  // 12345678,9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80010000;  // -12345678,9
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -123456789
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80010000;  // -7922816251426433759354395033,5
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00010000;  // 7922816251426433759354395033,5
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -7,9228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x001C0000;  // 7,9228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,1000000000000000000000000000
  val1.bits[2] = 0x033B2E3C;
  val1.bits[1] = 0x9FD0803C;
  val1.bits[0] = 0xE8000000;
  val_ans.bits[3] = 0x001C0000;  // 0,1000000000000000000000000000
  val_ans.bits[2] = 0x033B2E3C;
  val_ans.bits[1] = 0x9FD0803C;
  val_ans.bits[0] = 0xE8000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0100000000000000000000000000
  val1.bits[2] = 0x0052B7D2;
  val1.bits[1] = 0xDCC80CD2;
  val1.bits[0] = 0xE4000000;
  val_ans.bits[3] = 0x001C0000;  // 0,0100000000000000000000000000
  val_ans.bits[2] = 0x0052B7D2;
  val_ans.bits[1] = 0xDCC80CD2;
  val_ans.bits[0] = 0xE4000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801B0000;  // -9,999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x001B0000;  // 9,999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800B0000;  // -99999999999999999,99999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x000B0000;  // 99999999999999999,99999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,4999999999999999999999999999
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x87FFFFFF;
  val_ans.bits[3] = 0x001C0000;  // 0,4999999999999999999999999999
  val_ans.bits[2] = 0x1027E72F;
  val_ans.bits[1] = 0x1F128130;
  val_ans.bits[0] = 0x87FFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,5000000000000000000000000000
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000000;
  val_ans.bits[3] = 0x001C0000;  // 0,5000000000000000000000000000
  val_ans.bits[2] = 0x1027E72F;
  val_ans.bits[1] = 0x1F128130;
  val_ans.bits[0] = 0x88000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,5000000000000000000000000001
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000001;
  val_ans.bits[3] = 0x001C0000;  // 0,5000000000000000000000000001
  val_ans.bits[2] = 0x1027E72F;
  val_ans.bits[1] = 0x1F128130;
  val_ans.bits[0] = 0x88000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,4999999999999999999999999999
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x97FFFFFF;
  val_ans.bits[3] = 0x001C0000;  // 1,4999999999999999999999999999
  val_ans.bits[2] = 0x3077B58D;
  val_ans.bits[1] = 0x5D378391;
  val_ans.bits[0] = 0x97FFFFFF;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,5000000000000000000000000000
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000000;
  val_ans.bits[3] = 0x001C0000;  // 1,5000000000000000000000000000
  val_ans.bits[2] = 0x3077B58D;
  val_ans.bits[1] = 0x5D378391;
  val_ans.bits[0] = 0x98000000;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,5000000000000000000000000001
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000001;
  val_ans.bits[3] = 0x001C0000;  // 1,5000000000000000000000000001
  val_ans.bits[2] = 0x3077B58D;
  val_ans.bits[1] = 0x5D378391;
  val_ans.bits[0] = 0x98000001;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80090000;  // -0,123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00090000;  // 0,123456789
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80010000;  // -12345678,9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00010000;  // 12345678,9
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_negate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

Suite *suite_s21_negate(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_negate\033[0m");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, null);
  tcase_add_test(tc, plus);
  tcase_add_test(tc, minus);

  suite_add_tcase(s, tc);
  return s;
}
