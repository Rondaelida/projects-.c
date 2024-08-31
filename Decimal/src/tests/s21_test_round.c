#include "../test.h"
#define SIZE_OF_DECIMAL 16
START_TEST(null) {
  s21_decimal val;
  val.bits[0] = val.bits[1] = val.bits[2] = 0xFFFFFFFF;
  val.bits[3] = 0x00000000;
  ck_assert_int_eq(s21_round(val, NULL), 1);
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
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00010000;  // 7922816251426433759354395033,5
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433759354395034
  val_ans.bits[2] = 0x19999999;
  val_ans.bits[1] = 0x99999999;
  val_ans.bits[0] = 0x9999999A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus1) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x00020000;  // 792281625142643375935439503,35
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643375935439503
  val_ans.bits[2] = 0x028F5C28;
  val_ans.bits[1] = 0xF5C28F5C;
  val_ans.bits[0] = 0x28F5C28F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00030000;  // 79228162514264337593543950,335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950
  val_ans.bits[2] = 0x00418937;
  val_ans.bits[1] = 0x4BC6A7EF;
  val_ans.bits[0] = 0x9DB22D0E;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00040000;  // 7922816251426433759354395,0335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433759354395
  val_ans.bits[2] = 0x00068DB8;
  val_ans.bits[1] = 0xBAC710CB;
  val_ans.bits[0] = 0x295E9E1B;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00050000;  // 792281625142643375935439,50335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643375935440
  val_ans.bits[2] = 0x0000A7C5;
  val_ans.bits[1] = 0xAC471B47;
  val_ans.bits[0] = 0x84230FD0;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00060000;  // 79228162514264337593543,950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593544
  val_ans.bits[2] = 0x000010C6;
  val_ans.bits[1] = 0xF7A0B5ED;
  val_ans.bits[0] = 0x8D36B4C8;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus2) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x00070000;  // 7922816251426433759354,3950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433759354
  val_ans.bits[2] = 0x000001AD;
  val_ans.bits[1] = 0x7F29ABCA;
  val_ans.bits[0] = 0xF485787A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00080000;  // 792281625142643375935,43950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643375935
  val_ans.bits[2] = 0x0000002A;
  val_ans.bits[1] = 0xF31DC461;
  val_ans.bits[0] = 0x1873BF3F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00090000;  // 79228162514264337593,543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337594
  val_ans.bits[2] = 0x00000004;
  val_ans.bits[1] = 0x4B82FA09;
  val_ans.bits[0] = 0xB5A52CBA;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000A0000;  // 7922816251426433759,3543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426433759
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x6DF37F67;
  val_ans.bits[0] = 0x5EF6EADF;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000B0000;  // 792281625142643375,93543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643376
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0AFEBFF0;
  val_ans.bits[0] = 0xBCB24AB0;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus3) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x000C0000;  // 79228162514264337,593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264338
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01197998;
  val_ans.bits[0] = 0x12DEA112;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000D0000;  // 7922816251426433,7593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426434
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x001C25C2;
  val_ans.bits[0] = 0x68497682;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000E0000;  // 792281625142643,37593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625142643
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0002D093;
  val_ans.bits[0] = 0x70D42573;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000F0000;  // 79228162514264,337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0000480E;
  val_ans.bits[0] = 0xBE7B9D58;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00100000;  // 7922816251426,4337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251426
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000734;
  val_ans.bits[0] = 0xACA5F622;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus4) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x00110000;  // 792281625142,64337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625143
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x000000B8;
  val_ans.bits[0] = 0x77AA3237;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00120000;  // 79228162514,264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000012;
  val_ans.bits[0] = 0x725DD1D2;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00130000;  // 7922816251,4264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816251
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000001;
  val_ans.bits[0] = 0xD83C94FB;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00140000;  // 792281625,14264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792281625
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x2F394219;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00150000;  // 79228162,514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228163
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x04B8ED03;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus5) {
  s21_decimal val1, val2, val_ans;
  val1.bits[3] = 0x00160000;  // 7922816,2514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7922816
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0078E480;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00170000;  // 792281,62514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792282
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000C16DA;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00180000;  // 79228,162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001357C;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00190000;  // 7922,8162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 7923
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00001EF3;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001A0000;  // 792,28162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 792
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000318;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus6) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x001B0000;  // 79,228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000004F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 7,9228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 8
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000008;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,1000000000000000000000000000
  val1.bits[2] = 0x033B2E3C;
  val1.bits[1] = 0x9FD0803C;
  val1.bits[0] = 0xE8000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0100000000000000000000000000
  val1.bits[2] = 0x0052B7D2;
  val1.bits[1] = 0xDCC80CD2;
  val1.bits[0] = 0xE4000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0000000000001000000000000000
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00038D7E;
  val1.bits[0] = 0xA4C68000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus7) {
  s21_decimal val1, val2, val_ans;
  val1.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001B0000;  // 9,999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 10
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x000B0000;  // 99999999999999999,99999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 100000000000000000
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01634578;
  val_ans.bits[0] = 0x5D8A0000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,4999999999999999999999999999
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x87FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus8) {
  s21_decimal val1, val2, val_ans;
  val1.bits[3] = 0x001C0000;  // 0,5000000000000000000000000000
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000000;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 0,5000000000000000000000000001
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000001;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 1,4999999999999999999999999999
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x97FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 1,5000000000000000000000000000
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000000;
  val_ans.bits[3] = 0x00000000;  // 2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x001C0000;  // 1,5000000000000000000000000001
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000001;
  val_ans.bits[3] = 0x00000000;  // 2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00090000;  // 0,123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus9) {
  s21_decimal val1, val2, val_ans;
  val1.bits[3] = 0x00080000;  // 1,23456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00070000;  // 12,3456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 12
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000C;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00060000;  // 123,456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 123
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000007B;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00050000;  // 1234,56789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 1235
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000004D3;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00040000;  // 12345,6789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 12346
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000303A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(plus10) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x00030000;  // 123456,789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 123457
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E241;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00020000;  // 1234567,89
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 1234568
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0012D688;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00010000;  // 12345678,9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 12345679
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00BC614F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x00000000;  // 123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 123456789
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x075BCD15;
  s21_round(val1, &val2);
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
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -9999999999999999999999999999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250261;
  val_ans.bits[0] = 0x0FFFFFFF;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80010000;  // -7922816251426433759354395033,5
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426433759354395034
  val_ans.bits[2] = 0x19999999;
  val_ans.bits[1] = 0x99999999;
  val_ans.bits[0] = 0x9999999A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80020000;  // -792281625142643375935439503,35
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643375935439503
  val_ans.bits[2] = 0x028F5C28;
  val_ans.bits[1] = 0xF5C28F5C;
  val_ans.bits[0] = 0x28F5C28F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus1) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80030000;  // -79228162514264337593543950,335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950
  val_ans.bits[2] = 0x00418937;
  val_ans.bits[1] = 0x4BC6A7EF;
  val_ans.bits[0] = 0x9DB22D0E;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80040000;  // -7922816251426433759354395,0335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426433759354395
  val_ans.bits[2] = 0x00068DB8;
  val_ans.bits[1] = 0xBAC710CB;
  val_ans.bits[0] = 0x295E9E1B;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80050000;  // -792281625142643375935439,50335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643375935440
  val_ans.bits[2] = 0x0000A7C5;
  val_ans.bits[1] = 0xAC471B47;
  val_ans.bits[0] = 0x84230FD0;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80060000;  // -79228162514264337593543,950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593544
  val_ans.bits[2] = 0x000010C6;
  val_ans.bits[1] = 0xF7A0B5ED;
  val_ans.bits[0] = 0x8D36B4C8;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80070000;  // -7922816251426433759354,3950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426433759354
  val_ans.bits[2] = 0x000001AD;
  val_ans.bits[1] = 0x7F29ABCA;
  val_ans.bits[0] = 0xF485787A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus2) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80080000;  // -792281625142643375935,43950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643375935
  val_ans.bits[2] = 0x0000002A;
  val_ans.bits[1] = 0xF31DC461;
  val_ans.bits[0] = 0x1873BF3F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80090000;  // -79228162514264337593,543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337594
  val_ans.bits[2] = 0x00000004;
  val_ans.bits[1] = 0x4B82FA09;
  val_ans.bits[0] = 0xB5A52CBA;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800A0000;  // -7922816251426433759,3543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426433759
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x6DF37F67;
  val_ans.bits[0] = 0x5EF6EADF;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800B0000;  // -792281625142643375,93543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643376
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0AFEBFF0;
  val_ans.bits[0] = 0xBCB24AB0;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800C0000;  // -79228162514264337,593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264338
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01197998;
  val_ans.bits[0] = 0x12DEA112;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus3) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x800D0000;  // -7922816251426433,7593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426434
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x001C25C2;
  val_ans.bits[0] = 0x68497682;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800E0000;  // -792281625142643,37593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625142643
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0002D093;
  val_ans.bits[0] = 0x70D42573;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800F0000;  // -79228162514264,337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x0000480E;
  val_ans.bits[0] = 0xBE7B9D58;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80100000;  // -7922816251426,4337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251426
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000734;
  val_ans.bits[0] = 0xACA5F622;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80110000;  // -792281625142,64337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625143
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x000000B8;
  val_ans.bits[0] = 0x77AA3237;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus4) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80120000;  // -79228162514,264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000012;
  val_ans.bits[0] = 0x725DD1D2;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80130000;  // -7922816251,4264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816251
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000001;
  val_ans.bits[0] = 0xD83C94FB;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80140000;  // -792281625,14264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792281625
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x2F394219;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80150000;  // -79228162,514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228163
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x04B8ED03;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80160000;  // -7922816,2514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7922816
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0078E480;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus5) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80170000;  // -792281,62514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792282
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000C16DA;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80180000;  // -79228,162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001357C;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80190000;  // -7922,8162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -7923
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00001EF3;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801A0000;  // -792,28162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -792
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000318;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801B0000;  // -79,228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000004F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -7,9228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -8
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000008;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus6) {
  s21_decimal val1, val2, val_ans;
  val1.bits[3] = 0x801C0000;  // -0,1000000000000000000000000000
  val1.bits[2] = 0x033B2E3C;
  val1.bits[1] = 0x9FD0803C;
  val1.bits[0] = 0xE8000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0100000000000000000000000000
  val1.bits[2] = 0x0052B7D2;
  val1.bits[1] = 0xDCC80CD2;
  val1.bits[0] = 0xE4000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000010000000000000
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000918;
  val1.bits[0] = 0x4E72A000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801B0000;  // -9,999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -10
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus7) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80110000;  // -99999999999,99999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -100000000000
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000017;
  val_ans.bits[0] = 0x4876E800;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x800B0000;  // -99999999999999999,99999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -100000000000000000
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x01634578;
  val_ans.bits[0] = 0x5D8A0000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,4999999999999999999999999999
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x87FFFFFF;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -0,5000000000000000000000000000
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000000;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus8) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x801C0000;  // -0,5000000000000000000000000001
  val1.bits[2] = 0x1027E72F;
  val1.bits[1] = 0x1F128130;
  val1.bits[0] = 0x88000001;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,4999999999999999999999999999
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x97FFFFFF;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,5000000000000000000000000000
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000000;
  val_ans.bits[3] = 0x80000000;  // -2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x801C0000;  // -1,5000000000000000000000000001
  val1.bits[2] = 0x3077B58D;
  val1.bits[1] = 0x5D378391;
  val1.bits[0] = 0x98000001;
  val_ans.bits[3] = 0x80000000;  // -2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80090000;  // -0,123456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80080000;  // -1,23456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus9) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80070000;  // -12,3456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -12
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000C;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80060000;  // -123,456789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -123
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000007B;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80050000;  // -1234,56789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -1235
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000004D3;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80040000;  // -12345,6789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -12346
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000303A;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80030000;  // -123456,789
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -123457
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E241;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

START_TEST(minus10) {
  s21_decimal val1, val2, val_ans;

  val1.bits[3] = 0x80020000;  // -1234567,89
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -1234568
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0012D688;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);

  val1.bits[3] = 0x80010000;  // -12345678,9
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x075BCD15;
  val_ans.bits[3] = 0x80000000;  // -12345679
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00BC614F;
  s21_round(val1, &val2);
  ck_assert_mem_eq(&val2, &val_ans, SIZE_OF_DECIMAL);
}
END_TEST

Suite *suite_s21_round(void) {
  Suite *s = suite_create("\033[40m\033[94ms21_round\033[0m");
  TCase *tc = tcase_create("round_tc");

  tcase_add_test(tc, null);
  tcase_add_test(tc, plus);
  tcase_add_test(tc, plus1);
  tcase_add_test(tc, plus2);
  tcase_add_test(tc, plus3);
  tcase_add_test(tc, plus4);
  tcase_add_test(tc, plus5);
  tcase_add_test(tc, plus6);
  tcase_add_test(tc, plus7);
  tcase_add_test(tc, plus8);
  tcase_add_test(tc, plus9);
  tcase_add_test(tc, plus10);
  tcase_add_test(tc, minus);
  tcase_add_test(tc, minus1);
  tcase_add_test(tc, minus2);
  tcase_add_test(tc, minus3);
  tcase_add_test(tc, minus4);
  tcase_add_test(tc, minus5);
  tcase_add_test(tc, minus6);
  tcase_add_test(tc, minus7);
  tcase_add_test(tc, minus8);
  tcase_add_test(tc, minus9);
  tcase_add_test(tc, minus10);
  suite_add_tcase(s, tc);
  return s;
}
