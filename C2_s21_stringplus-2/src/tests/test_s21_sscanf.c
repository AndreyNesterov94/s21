#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_sscanf_test_1) {
  char str[] = "   321Lets start";
  char c1;
  char c2;
  int i1;
  int i2;
  int cnt1 = s21_sscanf(str, "%c%d", &c1, &i1);
  int cnt2 = sscanf(str, "%c%d", &c2, &i2);

  ck_assert_int_eq(cnt1, cnt2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq((int)c1, (int)c2);
}
END_TEST

START_TEST(test_s21_sscanf_test_2) {
  char str[] = "   321Lets start";
  char c1;
  char c2;
  char c11;
  char c21;
  char c12;
  char c22;
  char c13;
  char c23;
  char c14;
  char c24;
  char c15;
  char c25;

  s21_sscanf(str, "%c%c%c%c%c%c", &c1, &c11, &c12, &c13, &c14, &c15);
  sscanf(str, "%c%c%c%c%c%c", &c2, &c21, &c22, &c23, &c24, &c25);

  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
  ck_assert_int_eq(c14, c24);
  ck_assert_int_eq(c15, c25);
}
END_TEST

START_TEST(test_s21_sscanf_test_3) {
  char str[] = "0x12";
  int* i1;
  int* i2;

  s21_sscanf(str, "%p", &i1);
  sscanf(str, "%p", &i2);

  ck_assert_ptr_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_4) {
  char str[] = "012";
  unsigned int i1;
  unsigned int i2;

  s21_sscanf(str, "%o", &i1);
  sscanf(str, "%o", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_5) {
  char str[] = "-4321.564E-2";
  float i1;
  float i2;

  s21_sscanf(str, "%e", &i1);
  sscanf(str, "%e", &i2);

  ck_assert_float_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_6) {
  char str[] = "-0x43215642";
  int i1;
  int i2;

  s21_sscanf(str, "%i", &i1);
  sscanf(str, "%i", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_7) {
  char str[100] = "    -0x43215642    ";
  char i1[100] = "";
  char i2[100] = "";

  s21_sscanf(str, "%99s", i1);
  sscanf(str, "%99s", i2);

  ck_assert_pstr_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_8) {
  char str[] = "abc 123456";
  unsigned int i1;
  unsigned int i2;

  s21_sscanf(str, "abc%u", &i1);
  sscanf(str, "abc%u", &i2);

  ck_assert_uint_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_9) {
  char str[] = "abc 123456";
  wchar_t i1[100];
  wchar_t i2[100];

  s21_sscanf(str, "abc%3ls", i1);
  sscanf(str, "abc%3ls", i2);

  // ck_assert_uint_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_10) {
  char str[] = "abc% 123456";
  int i1;
  int i2;

  s21_sscanf(str, "abc%%%n", &i1);
  sscanf(str, "abc%%%n", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_11) {
  char str[] = " 987324abc% 123456";
  long int i1;
  long int i2;

  i1 = s21_sscanf(str, "%ld", &i1);
  i2 = sscanf(str, "%ld ", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_12) {
  char str[] = "abc% 123456";
  int i1;
  int i2;
  wchar_t c1;
  wchar_t c2;

  i1 = s21_sscanf(str, "a %lc %*c x", &c1);
  i2 = sscanf(str, "a %lc %*c x", &c2);

  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_test_13) {
  char str[] = "a   bc% 123456";
  int i1;
  int i2;

  i1 = s21_sscanf(str, "a b%n", &i1);
  i2 = sscanf(str, "a b%n", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_14) {
  char str[] = "a   b12c% 123456";
  short int i1;
  short int i2;

  s21_sscanf(str, "a b%2hd %*u", &i1);
  sscanf(str, "a b%2hd %*u", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_15) {
  char str[] = "0x2133421";
  unsigned short int i1 = 0;
  unsigned short int i2 = 0;

  s21_sscanf(str, "%4hx %*1x%*1o%*1e%*1i%*1s", &i1);
  sscanf(str, "%4hx %*1x%*1o%*1e%*1i%*1s", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(test_s21_sscanf_test_16) {
  char str[] = "-0x21a31 0123";
  short int i1 = 0;
  short int i2 = 0;
  long int i21 = 0;
  long int i22 = 0;

  s21_sscanf(str, "%hi %li", &i1, &i21);
  sscanf(str, "%hi %li", &i2, &i22);

  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i21, i22);
}
END_TEST

START_TEST(test_s21_sscanf_test_17) {
  char str[] = "-0x2 0x3d";
  unsigned short int i1 = 0;
  unsigned short int i2 = 0;
  int i21 = 0;
  int i22 = 0;

  s21_sscanf(str, "%hx %i", &i1, &i21);
  sscanf(str, "%hx %i", &i2, &i22);

  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i21, i22);
}
END_TEST

START_TEST(test_s21_sscanf_test_18) {
  char str[] = "-033 ";
  unsigned short int i1 = 0;
  unsigned short int i2 = 0;
  int i21 = 0;
  int i22 = 0;

  s21_sscanf(str, "%ho %i", &i1, &i21);
  sscanf(str, "%ho %i", &i2, &i22);

  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i21, i22);
}
END_TEST

START_TEST(test_s21_sscanf_test_19) {
  char str[] = "-033.123 ";
  float i1 = 0;
  float i2 = 0;

  s21_sscanf(str, "%7f %*c", &i1);
  sscanf(str, "%7f %*c", &i2);

  ck_assert_int_eq(i1, i2);
}
END_TEST

Suite* make_s21_sscanf_suite(void) {
  Suite* s = suite_create("s21_sscanf");
  TCase* tc = tcase_create("s21_sscanf");

  tcase_add_test(tc, test_s21_sscanf_test_1);
  tcase_add_test(tc, test_s21_sscanf_test_2);
  tcase_add_test(tc, test_s21_sscanf_test_3);
  tcase_add_test(tc, test_s21_sscanf_test_4);
  tcase_add_test(tc, test_s21_sscanf_test_5);
  tcase_add_test(tc, test_s21_sscanf_test_6);
  tcase_add_test(tc, test_s21_sscanf_test_7);
  tcase_add_test(tc, test_s21_sscanf_test_8);
  tcase_add_test(tc, test_s21_sscanf_test_9);
  tcase_add_test(tc, test_s21_sscanf_test_10);
  tcase_add_test(tc, test_s21_sscanf_test_11);
  tcase_add_test(tc, test_s21_sscanf_test_12);
  tcase_add_test(tc, test_s21_sscanf_test_13);
  tcase_add_test(tc, test_s21_sscanf_test_14);
  tcase_add_test(tc, test_s21_sscanf_test_15);
  tcase_add_test(tc, test_s21_sscanf_test_16);
  tcase_add_test(tc, test_s21_sscanf_test_17);
  tcase_add_test(tc, test_s21_sscanf_test_18);
  tcase_add_test(tc, test_s21_sscanf_test_19);

  suite_add_tcase(s, tc);
  return s;
}
