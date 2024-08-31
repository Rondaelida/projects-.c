#include <check.h>
#include <stdio.h>

#include "../test.h"
#define SIZE_OF_DECIMAL 16
START_TEST(null) {
  s21_decimal val;
  val.bits[0] = val.bits[1] = val.bits[2] = 0xFFFFFFFF;
  val.bits[3] = 0x00000000;
  ck_assert_int_eq(s21_truncate(val, NULL), 1);
}
END_TEST

START_TEST(plus) {
  s21_decimal val1, val_ans, val2;

  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00010000;  // 7922816251426433759354395033,5
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433759354395033
  val_ans.bits[2] = 0x19999999;
  val_ans.bits[1] = 0x99999999;
  val_ans.bits[0] = 0x99999999;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00040000;  // 7922816251426433759354395,0335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433759354395
  val_ans.bits[2] = 0x00068DB8;
  val_ans.bits[1] = 0xBAC710CB;
  val_ans.bits[0] = 0x295E9E1B;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00050000;  // 792281625142643375935439,50335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643375935439
  val_ans.bits[2] = 0x0000A7C5;
  val_ans.bits[1] = 0xAC471B47;
  val_ans.bits[0] = 0x84230FCF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00060000;  // 79228162514264337593543,950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543
  val_ans.bits[2] = 0x000010C6;
  val_ans.bits[1] = 0xF7A0B5ED;
  val_ans.bits[0] = 0x8D36B4C7;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000C0000;  // 79228162514264337,593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01197998;
  val_ans.bits[0] = 0x12DEA111;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000D0000;  // 7922816251426433,7593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x001C25C2;
  val_ans.bits[0] = 0x68497681;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000E0000;  // 792281625142643,37593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0002D093;
  val_ans.bits[0] = 0x70D42573;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00140000;  // 792281625,14264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x2F394219;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00170000;  // 792281,62514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000C16D9;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00190000;  // 7922,8162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00001EF2;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001B0000;  // 79,228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000004F;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 7,9228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000007;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,1000000000000000000000000000
  val1.bits[2] = 0x033B2E3C;
  val1.bits[1] = 0x9FD0803C;
  val1.bits[0] = 0xE8000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0100000000000000000000000000
  val1.bits[2] = 0x0052B7D2;
  val1.bits[1] = 0xDCC80CD2;
  val1.bits[0] = 0xE4000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0000000000000010000000000000
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000918;
  val1.bits[0] = 0x4E72A000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001B0000;  // 9,999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 9
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000009;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000F0000;  // 9999999999999,999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 9999999999999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000918;
  val_ans.bits[0] = 0x4E729FFF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000B0000;  // 99999999999999999,99999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 99999999999999999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01634578;
  val_ans.bits[0] = 0x5D89FFFF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,4999999999999999999999999999
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x87FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,5000000000000000000000000000
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,5000000000000000000000000001
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 3,4999999999999999999999999999
  val1.bits[2] = 0x71175249;
  val1.bits[1] = 0xD9818853;
  val1.bits[0] = 0xB7FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 3
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000003;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 3,5000000000000000000000000000
  val1.bits[2] = 0x71175249;
  val1.bits[1] = 0xD9818853;
  val1.bits[0] = 0xB8000000;
  val_ans.bits[3] = 0x00000000;  // 3
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000003;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 3,5000000000000000000000000001
  val1.bits[2] = 0x71175249;
  val1.bits[1] = 0xD9818853;
  val1.bits[0] = 0xB8000001;
  val_ans.bits[3] = 0x00000000;  // 3
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000003;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 4,4999999999999999999999999999
  val1.bits[2] = 0x916720A8;
  val1.bits[1] = 0x17A68AB4;
  val1.bits[0] = 0xC7FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 4
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000004;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 4,5000000000000000000000000000
  val1.bits[2] = 0x916720A8;
  val1.bits[1] = 0x17A68AB4;
  val1.bits[0] = 0xC8000000;
  val_ans.bits[3] = 0x00000000;  // 4
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000004;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 4,5000000000000000000000000001
  val1.bits[2] = 0x916720A8;
  val1.bits[1] = 0x17A68AB4;
  val1.bits[0] = 0xC8000001;
  val_ans.bits[3] = 0x00000000;  // 4
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000004;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00090000;  // 0,123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00080000;  // 1,23456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00070000;  // 12,3456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 12
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000C;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00060000;  // 123,456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 123
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000007B;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00050000;  // 1234,56789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 1234
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000004D2;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00040000;  // 12345,6789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00030000;  // 123456,789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 123456
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E240;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00020000;  // 1234567,89
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 1234567
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0012D687;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00010000;  // 12345678,9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 12345678
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00BC614E;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 123456789
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus) {
  s21_decimal val1, val_ans, val2;

  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -9999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80010000;  // -7922816251426433759354395033,5
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426433759354395033
  val_ans.bits[2] = 0x19999999;
  val_ans.bits[1] = 0x99999999;
  val_ans.bits[0] = 0x99999999;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800B0000;  // -792281625142643375,93543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643375
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0AFEBFF0;
  val_ans.bits[0] = 0xBCB24AAF;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800C0000;  // -79228162514264337,593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01197998;
  val_ans.bits[0] = 0x12DEA111;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800E0000;  // -792281625142643,37593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0002D093;
  val_ans.bits[0] = 0x70D42573;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80160000;  // -7922816,2514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0078E480;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80170000;  // -792281,62514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000C16D9;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801B0000;  // -79,228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000004F;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -7,9228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000007;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,1000000000000000000000000000
  val1.bits[2] = 0x033B2E3C;
  val1.bits[1] = 0x9FD0803C;
  val1.bits[0] = 0xE8000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0100000000000000000000000000
  val1.bits[2] = 0x0052B7D2;
  val1.bits[1] = 0xDCC80CD2;
  val1.bits[0] = 0xE4000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801B0000;  // -9,999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -9
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000009;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80170000;  // -99999,99999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -99999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001869F;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,4999999999999999999999999999
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x87FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,5000000000000000000000000000
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,5000000000000000000000000001
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,4999999999999999999999999999
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x97FFFFFF;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,5000000000000000000000000000
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000000;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,5000000000000000000000000001
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000001;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80090000;  // -0,123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80080000;  // -1,23456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80070000;  // -12,3456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -12
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000C;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80060000;  // -123,456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -123
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000007B;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80050000;  // -1234,56789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -1234
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000004D2;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80040000;  // -12345,6789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80030000;  // -123456,789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -123456
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E240;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80020000;  // -1234567,89
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -1234567
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0012D687;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80010000;  // -12345678,9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -12345678
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00BC614E;
  s21_truncate(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

Suite *suite_s21_truncate(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_truncate\033[0m");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, null);
  tcase_add_test(tc, plus);
  tcase_add_test(tc, minus);

  suite_add_tcase(s, tc);
  return s;
}
