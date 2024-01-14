#include "unit_tests.h"
#define CK_FORK no

/*
ПЛАН ПРОВЕРКИ:
    %с
все флаги (+ -0#): +
все варианты длинны (h l L): +
    %d
все флаги (+ -0#): +
все варианты длинны (h l L): +
    %i
    %e
    %E
    %f
    %g
    %G
    %o
    %s
    %u
    %x
    %X
    %p



*/

#define FORMAT_COUNT 32
#define LENGTH_COUNT 4
char** getListFormatBase(char spec) {
  const char LENGTHS[LENGTH_COUNT][10] = {"l", "h", "ll", "L"};
  const char FORMATS[FORMAT_COUNT][255] = {
      "%+20.10",     "%+10.20",    "%+.20",    "%+10",     "%-20.10",
      "%-10.20",     "%-.20",      "%-10",     "% 20.10",  "% 10.20",
      "% .20",       "% 10",       "%020.10",  "%010.20",  "%0.20",
      "%010",        "%-020.10",   "%-010.20", "%-0.20",   "%-010",
      "%- +020.10",  "%- +010.20", "%- +0.20", "%- +010",  "%- +#020.10",
      "%- +#010.20", "%- +#0.20",  "%- +#010", "%#020.10", "%#010.20",
      "%#0.20",      "%#010"};
  char** formatList = calloc(FORMAT_COUNT * LENGTH_COUNT, sizeof(char*));
  int idx = 0;
  for (int i = 0; i < FORMAT_COUNT; i++) {
    for (int j = 0; j < LENGTH_COUNT; j++) {
      formatList[idx] = calloc(255, sizeof(char));
      strcat(formatList[idx], FORMATS[i]);
      strcat(formatList[idx], LENGTHS[j]);
      char specifierStr[2] = {spec, '\0'};
      strcat(formatList[idx], specifierStr);
      idx++;
    }
  }
  return formatList;
}

void freeListFormatBase(char** formatList) {
  for (int i = 0; i < FORMAT_COUNT * LENGTH_COUNT; i++) {
    free(formatList[i]);
  }
  free(formatList);
}

START_TEST(test_s21_sprintf_c_base) {
  char param = '$';
  const int FORMAT_LIST_LEN = FORMAT_COUNT * LENGTH_COUNT;
  char** formatList = getListFormatBase('c');
  for (int i = 0; i < FORMAT_LIST_LEN; i++) {
    char buffer_s21[255] = "";
    char buffer[255] = "";
    int resultS21sPrintf = s21_sprintf(buffer_s21, formatList[i], param);
    int resultSPrintf = sprintf(buffer, formatList[i], param);
    ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
    ck_assert_str_eq(buffer_s21, buffer);
  }
  freeListFormatBase(formatList);
}
END_TEST

START_TEST(test_s21_sprintf_d_base_1) {
  int param = 98134;
  const int FORMAT_LIST_LEN = FORMAT_COUNT * LENGTH_COUNT;
  char** formatList = getListFormatBase('d');
  for (int i = 0; i < FORMAT_LIST_LEN; i++) {
    char buffer_s21[255] = "";
    char buffer[255] = "";
    int resultS21sPrintf = s21_sprintf(buffer_s21, formatList[i], param);
    int resultSPrintf = sprintf(buffer, formatList[i], param);
    ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
    ck_assert_str_eq(buffer_s21, buffer);
  }
  freeListFormatBase(formatList);
}
END_TEST

START_TEST(test_s21_sprintf_d_base_2) {
  int param = -1898134123;
  const int FORMAT_LIST_LEN = FORMAT_COUNT * LENGTH_COUNT;
  char** formatList = getListFormatBase('d');
  for (int i = 0; i < FORMAT_LIST_LEN; i++) {
    char buffer_s21[255] = "";
    char buffer[255] = "";
    int resultS21sPrintf = s21_sprintf(buffer_s21, formatList[i], param);
    int resultSPrintf = sprintf(buffer, formatList[i], param);
    ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
    ck_assert_str_eq(buffer_s21, buffer);
  }
  freeListFormatBase(formatList);
}
END_TEST

START_TEST(test_s21_sprintf_d_base_3) {
  int long long param = -1898134123132;
  const int FORMAT_LIST_LEN = FORMAT_COUNT * LENGTH_COUNT;
  char** formatList = getListFormatBase('d');
  for (int i = 0; i < FORMAT_LIST_LEN; i++) {
    char buffer_s21[255] = "";
    char buffer[255] = "";
    int resultS21sPrintf = s21_sprintf(buffer_s21, formatList[i], param);
    int resultSPrintf = sprintf(buffer, formatList[i], param);
    ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
    ck_assert_str_eq(buffer_s21, buffer);
  }
  freeListFormatBase(formatList);
}
END_TEST

START_TEST(test_s21_sprintf_d_base_4) {
  int long long param = 189813491923913299;
  const int FORMAT_LIST_LEN = FORMAT_COUNT * LENGTH_COUNT;
  char** formatList = getListFormatBase('d');
  for (int i = 0; i < FORMAT_LIST_LEN; i++) {
    char buffer_s21[255] = "";
    char buffer[255] = "";
    int resultS21sPrintf = s21_sprintf(buffer_s21, formatList[i], param);
    int resultSPrintf = sprintf(buffer, formatList[i], param);
    ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
    ck_assert_str_eq(buffer_s21, buffer);
  }
  freeListFormatBase(formatList);
}
END_TEST

START_TEST(test_s21_sprintf_s1) {
  wchar_t wstr[] = L"KAKA";
  char str[] = "STROKAKA";
  char s21_buf[100] = "";
  char buf[100] = "";

  char* rule = "%ls %2.4s %2s";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, wstr, str, str);
  int resultSPrintf = sprintf(buf, rule, wstr, str, str);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_s2) {
  float data = 20.5430;
  float ddata = 21;
  double ldata = -42.00;
  long double lldata = 42;
  char s21_buf[100] = "";
  char buf[100] = "";

  char* rule = "%f %#f %#lf  %Lf %010f %2.1f";
  int resultS21sPrintf =
      s21_sprintf(s21_buf, rule, data, ddata, ldata, lldata, data, data);
  int resultSPrintf =
      sprintf(buf, rule, data, ddata, ldata, lldata, data, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_s3) {
  int data = 12345;
  long ldata = 42;
  unsigned int lldata = 42;
  unsigned short sdata = 42;
  char s21_buf[100] = "";
  char buf[100] = "";

  char* rule = "%o %#lo %x %hp %#X";
  int resultS21sPrintf =
      s21_sprintf(s21_buf, rule, data, ldata, lldata, &sdata, data);
  int resultSPrintf = sprintf(buf, rule, data, ldata, lldata, &sdata, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_a1) {
  double data = 0.0000012345;
  double data1 = 75.451550054;
  char* rule = "%0lg %.3lG";
  char buf[100] = "";
  char s21_buf[100] = "";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, data1, data);
  int resultSPrintf = sprintf(buf, rule, data1, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_a2) {
  double data = 0.00000412;
  double data1 = 0.000000412;
  char* rule = "%#le %0lE";
  char buf[100] = "";
  char s21_buf[100] = "";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, data1, data);
  int resultSPrintf = sprintf(buf, rule, data1, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_a3) {
  double data = 0.00057;
  char* rule = "%.4g";
  char buf[100] = "";
  char s21_buf[100] = "";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, data);
  int resultSPrintf = sprintf(buf, rule, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_a4) {
  double data = 92;
  char* rule = "%#.lf";
  char buf[100] = "";
  char s21_buf[100] = "";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, data);
  int resultSPrintf = sprintf(buf, rule, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_a5) {
  double data = 0.00000412;
  char* rule = "%e %g";
  char buf[100] = "";
  char s21_buf[100] = "";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, data, data);
  int resultSPrintf = sprintf(buf, rule, data, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

START_TEST(test_s21_sprintf_a6) {
  long double data = 412;
  char* rule = "%Le %Lg";
  char buf[100] = "";
  char s21_buf[100] = "";
  int resultS21sPrintf = s21_sprintf(s21_buf, rule, data, data);
  int resultSPrintf = sprintf(buf, rule, data, data);
  ck_assert_int_eq(resultS21sPrintf, resultSPrintf);
  ck_assert_str_eq(s21_buf, buf);
}
END_TEST

Suite* make_s21_sprintf_suite(void) {
  Suite* s = suite_create("s21_sprintf");
  TCase* tc = tcase_create("s21_sprintf");

  tcase_add_test(tc, test_s21_sprintf_c_base);
  tcase_add_test(tc, test_s21_sprintf_d_base_1);
  tcase_add_test(tc, test_s21_sprintf_d_base_2);
  tcase_add_test(tc, test_s21_sprintf_d_base_3);
  tcase_add_test(tc, test_s21_sprintf_d_base_4);
  tcase_add_test(tc, test_s21_sprintf_s1);
  tcase_add_test(tc, test_s21_sprintf_s2);
  tcase_add_test(tc, test_s21_sprintf_s3);
  tcase_add_test(tc, test_s21_sprintf_a1);
  tcase_add_test(tc, test_s21_sprintf_a2);
  tcase_add_test(tc, test_s21_sprintf_a3);
  tcase_add_test(tc, test_s21_sprintf_a4);
  tcase_add_test(tc, test_s21_sprintf_a5);
  tcase_add_test(tc, test_s21_sprintf_a6);
  suite_add_tcase(s, tc);
  return s;
}
