#include <math.h>

#include "unit_tests.h"
#define CK_FORK no
#define EPS 0.0000001
#define EPS1 1

START_TEST(test_1) {
  int count = 5;
  char *tokens[] = {"2", "*", "3", "^", "3"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_2) {
  int count = 4;
  char *tokens[] = {"2", "3", "*", "3"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_3) {
  int count = 4;
  char *tokens[] = {"2", "*", "3", "+"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_4) {
  int count = 2;
  char *tokens[] = {"sin", "2"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_5) {
  int count = 3;
  char *tokens[] = {"sin", "cos", "3"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_6) {
  int count = 2;
  char *tokens[] = {"-", "3"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_7) {
  int count = 5;
  char *tokens[] = {"-", "(", "-", "3", ")"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_8) {
  int count = 3;
  char *tokens[] = {"-", "-", "3"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_9) {
  int count = 3;
  char *tokens[] = {")", "-", "3"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_10) {
  int count = 3;
  char *tokens[] = {")", "(", "3"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_11) {
  int count = 2;
  char *tokens[] = {"(", "3"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_12) {
  int count = 3;
  char *tokens[] = {"3", "+", "y"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_13) {
  int count = 88;
  char *tokens[] = {
      "(", "sin",  "(",    "x",  ")",   "+",    "cos", "(", "sqrt", "(",
      "x", "+",    "3",    ")",  ")",   "/",    "tan", "(", "x",    "-",
      "2", ")",    ")",    "*",  "log", "(",    "x",   "/", "2",    ")",
      "-", "sqrt", "(",    "ln", "(",   "x",    "^",   "2", "+",    "1",
      ")", ")",    "+",    "x",  "^",   "3.5",  "mod", "7", "-",    "tan",
      "(", "(",    "x",    "-",  "5",   ")",    "/",   "(", "x",    "+",
      "2", ")",    ")",    "+",  "(",   "asin", "(",   "x", "/",    "10",
      ")", "-",    "acos", "(",  "x",   "/",    "10",  ")", "/",    "atan",
      "(", "x",    "/",    "4",  ")",   ")",    "^",   "2"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_14) {
  int count = 3;
  char *tokens[] = {"/", "x", "1"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_15) {
  int count = 4;
  char *tokens[] = {"-", "x", "-", "x"};
  int isValid = 1;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_16) {
  int count = 3;
  char *tokens[] = {"1..2", "+", "1"};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_17) {
  int count = 3;
  char *tokens[] = {"x", "+", ""};
  int isValid = 0;
  ck_assert_int_eq(s21_isValidExpression(tokens, count), isValid);
}
END_TEST

START_TEST(test_18) {
  int count = 7;
  char *tokens[] = {"x", "cos", "acos", "asin", "sin", "tan", "atan"};
  for (double x = -2; x < 5; x += 0.2) {
    double result = s21_calculateExample(tokens, count, x);
    if (fabs(x) > 1) {
      ck_assert_int_eq(isnan(result), 1);
    } else {
      ck_assert_int_eq(fabs(result - fabs(x)) < EPS, 1);
    }
  }
}
END_TEST

START_TEST(test_19) {
  int count = 58;
  char *tokens[] = {
      "x",   "sin", "x",    "3",  "+",    "sqrt", "cos", "x",   "2",    "-",
      "tan", "/",   "+",    "x",  "2",    "/",    "log", "*",   "x",    "2",
      "^",   "1",   "+",    "ln", "sqrt", "-",    "x",   "3.5", "^",    "7",
      "mod", "+",   "x",    "5",  "-",    "x",    "2",   "+",   "/",    "tan",
      "-",   "x",   "10",   "/",  "asin", "x",    "10",  "/",   "acos", "x",
      "4",   "/",   "atan", "/",  "-",    "2",    "^",   "+"};
  double result = s21_calculateExample(tokens, count, 0.5);
  double check = 143.36350808764774;
  ck_assert_int_eq(fabs(result - check) < EPS, 1);
}
END_TEST

START_TEST(test_20) {
  int count = 19;
  char *tokens[] = {"x",   "~", "x", "-", "x", "~", "~",   "x", "-", "~",
                    "sin", "-", "x", "-", "x", "~", "cos", "~", "-"};
  double result = s21_calculateExample(tokens, count, 17.157);
  double check = -51.59245896191992;
  ck_assert_int_eq(fabs(result - check) < EPS, 1);
}
END_TEST

START_TEST(test_21) {
  int count = 11;
  char *tokens[] = {"3", "x", "2", "^", "cos", "*", "x", "5", "+", "ln", "/"};
  for (double x = -10; x < 10; x += 0.1) {
    double result = s21_calculateExample(tokens, count, x);
    double check = 3 * cos(pow(x, 2)) / log(x + 5);
    if (isnan(check)) {
      ck_assert_int_eq(isnan(result), 1);
    } else {
      ck_assert_int_eq(fabs(result - check) < EPS, 1);
    }
  }
}
END_TEST

START_TEST(test_22) {
  int count = 2;
  char *tokens[] = {"123", "log10"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_23) {
  int count = 3;
  char *tokens[] = {"12", "~", "55"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_24) {
  int count = 3;
  char *tokens[] = {"15", "*", "x"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_25) {
  int count = 2;
  char *tokens[] = {"-100", "sqrt"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_26) {
  int count = 2;
  char *tokens[] = {"-100", "ln"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_27) {
  int count = 2;
  char *tokens[] = {"-100", "log"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_28) {
  int count = 3;
  char *tokens[] = {"10", "/", "0"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_29) {
  int count = 3;
  char *tokens[] = {"10", "mod", "0"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_30) {
  int count = 3;
  char *tokens[] = {"(", "x", ")"};
  double result = s21_calculateExample(tokens, count, 13);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_31) {
  int count = 1;
  char *tokens[] = {""};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_32) {
  int count = 1;
  char *tokens[] = {"123"};
  double result = s21_calculateExample(tokens, count, NAN);
  double check = 123;
  ck_assert_int_eq(fabs(result - check) < EPS, 1);
}
END_TEST

START_TEST(test_33) {
  int count = 2;
  char *tokens[] = {"10", "mod"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_34) {
  int count = 2;
  char *tokens[] = {"-"};
  double result = s21_calculateExample(tokens, count, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_35) {
  char *example =
      "(sin(x) + cos(sqrt(x + 3)) / tan(x - 2)) * log(x / 2) - sqrt(ln(x^2 + "
      "1)) + x^3.5 mod 7 - tan((x - 5) / (x + 2)) + (asin(x / 10) - acos(x / "
      "10) / atan(x / 4))^2";
  double result = s21_calculate(example, 0.5);
  double check = 143.36350808764774;
  ck_assert_int_eq(fabs(result - check) < EPS, 1);
}
END_TEST

START_TEST(test_36) {
  char *example = "((x - 11)) - ";
  double result = s21_calculate(example, 0.5);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_37) {
  char *example = "%x";
  double result = s21_calculate(example, 0.5);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_39) {
  char *example = "";
  double result = s21_calculate(example, NAN);
  ck_assert_int_eq(isnan(result), 1);
}
END_TEST

START_TEST(test_41) {
  const char *example = "sin(x^2)+asin(x)";
  int count = 0;
  char **tokens = s21_getTokensList(example, &count);
  int checkCount = 11;
  char *check[] = {"sin", "(", "x", "^", "2", ")", "+", "asin", "(", "x", ")"};
  ck_assert_int_eq(count, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], tokens[i]);
  }
  s21_freeStringArray(tokens, count);
}
END_TEST

START_TEST(test_42) {
  const char *example = "acos(x^2)+cos(x)";
  int count = 0;
  char **tokens = s21_getTokensList(example, &count);
  int checkCount = 11;
  char *check[] = {"acos", "(", "x", "^", "2", ")", "+", "cos", "(", "x", ")"};
  ck_assert_int_eq(count, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], tokens[i]);
  }
  s21_freeStringArray(tokens, count);
}
END_TEST

START_TEST(test_43) {
  const char *example = "+-*/modsincostanasinacosatanlogln^sqrt()";
  int count = 0;
  char **tokens = s21_getTokensList(example, &count);
  int checkCount = 17;
  char *check[] = {"+",   "-",   "*",    "/",    "mod",  "sin",
                   "cos", "tan", "asin", "acos", "atan", "log",
                   "ln",  "^",   "sqrt", "(",    ")"};
  ck_assert_int_eq(count, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], tokens[i]);
  }
  s21_freeStringArray(tokens, count);
}
END_TEST

START_TEST(test_44) {
  const char *example = "sinerror)+NAN*";
  int count = 0;
  char **tokens = s21_getTokensList(example, &count);
  int checkCount = 6;
  char *check[] = {"sin", "error", ")", "+", "NAN", "*"};
  ck_assert_int_eq(count, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], tokens[i]);
  }
  s21_freeStringArray(tokens, count);
}
END_TEST

START_TEST(test_45) {
  const char *example =
      "       asin(x)          +     x        * arccos(x)    ";
  int count = 0;
  char **tokens = s21_getTokensList(example, &count);
  int checkCount = 12;
  char *check[] = {"asin", "(",   "x",   ")", "+", "x",
                   "*",    "arc", "cos", "(", "x", ")"};
  ck_assert_int_eq(count, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], tokens[i]);
  }
  s21_freeStringArray(tokens, count);
}
END_TEST

START_TEST(test_46) {
  const char *example = "";
  int count = 0;
  char **tokens = s21_getTokensList(example, &count);
  int checkCount = 0;
  ck_assert_int_eq(count, checkCount);
  s21_freeStringArray(tokens, count);
}
END_TEST

START_TEST(test_49) {
  int count = 15;
  char *tokens[] = {"3", "*",  "cos", "(", "x", "^", "2", ")",
                    "/", "ln", "(",   "x", "+", "5", ")"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 11;
  char *check[] = {"3", "x", "2", "^", "cos", "*", "x", "5", "+", "ln", "/"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_50) {
  int count = 13;
  char *tokens[] = {"2", "*",   "x", "^", "2", "+", "3",
                    "*", "sin", "(", "-", "x", ")"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 11;
  char *check[] = {"2", "x", "2", "^", "*", "3", "x", "~", "sin", "*", "+"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_51) {
  int count = 29;
  char *tokens[] = {"-", "x", "-", "x",   "-", "sin", "(", "-", "(", "-",
                    "(", "-", "x", ")",   "-", "x",   ")", ")", "-", "x",
                    "-", "(", "-", "cos", "(", "-",   "x", ")", ")"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 19;
  char *check[] = {"x",   "~", "x", "-", "x", "~", "~",   "x", "-", "~",
                   "sin", "-", "x", "-", "x", "~", "cos", "~", "-"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_52) {
  int count = 5;
  char *tokens[] = {"2", "*", "3", "^", "3"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 5;
  char *check[] = {"2", "3", "3", "^", "*"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_53) {
  int count = 4;
  char *tokens[] = {"sin", "x", "^", "3"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 4;
  char *check[] = {"x", "sin", "3", "^"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_54) {
  int count = 6;
  char *tokens[] = {"sin", "(", "x", "^", "3", ")"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 4;
  char *check[] = {"x", "3", "^", "sin"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_55) {
  int count = 23;
  char *tokens[] = {"(", ")", "(", "12", ")", "*",   "(", "(",
                    ")", "(", ")", "(",  "-", "sin", "(", "x",
                    ")", ")", "^", "2",  "(", ")",   ")"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 7;
  char *check[] = {"12", "x", "sin", "~", "2", "^", "*"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_56) {
  int count = 10;
  char *tokens[] = {")", ")", "sin", ")", "(", ")", "(", ")", "(", "("};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 3;
  char *check[] = {"sin", "(", "("};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_57) {
  int count = 88;
  char *tokens[] = {
      "(", "sin",  "(",    "x",  ")",   "+",    "cos", "(", "sqrt", "(",
      "x", "+",    "3",    ")",  ")",   "/",    "tan", "(", "x",    "-",
      "2", ")",    ")",    "*",  "log", "(",    "x",   "/", "2",    ")",
      "-", "sqrt", "(",    "ln", "(",   "x",    "^",   "2", "+",    "1",
      ")", ")",    "+",    "x",  "^",   "3.5",  "mod", "7", "-",    "tan",
      "(", "(",    "x",    "-",  "5",   ")",    "/",   "(", "x",    "+",
      "2", ")",    ")",    "+",  "(",   "asin", "(",   "x", "/",    "10",
      ")", "-",    "acos", "(",  "x",   "/",    "10",  ")", "/",    "atan",
      "(", "x",    "/",    "4",  ")",   ")",    "^",   "2"};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);

  int checkCount = 58;
  char *check[] = {
      "x",   "sin", "x",    "3",  "+",    "sqrt", "cos", "x",   "2",    "-",
      "tan", "/",   "+",    "x",  "2",    "/",    "log", "*",   "x",    "2",
      "^",   "1",   "+",    "ln", "sqrt", "-",    "x",   "3.5", "^",    "7",
      "mod", "+",   "x",    "5",  "-",    "x",    "2",   "+",   "/",    "tan",
      "-",   "x",   "10",   "/",  "asin", "x",    "10",  "/",   "acos", "x",
      "4",   "/",   "atan", "/",  "-",    "2",    "^",   "+"};

  ck_assert_int_eq(outputLen, checkCount);
  for (int i = 0; i < checkCount; i++) {
    ck_assert_str_eq(check[i], polishNotation[i]);
  }
  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_58) {
  int count = 1;
  char *tokens[] = {""};
  int outputLen = 0;
  char **polishNotation = s21_convertToRPN(tokens, count, &outputLen);
  ck_assert_str_eq(polishNotation[0], "");
  int checkCount = 1;
  ck_assert_int_eq(outputLen, checkCount);

  s21_freeStringArray(polishNotation, count);
}
END_TEST

START_TEST(test_59) {
  double principal = 5000000;
  double interestRate = 7.5;
  int months = 36;

  double resultAnnuityLoan =
      calculateAnnuityLoan(principal, interestRate, months);
  double resultDifferentiatedLoan =
      calculateDifferentiatedLoan(principal, interestRate, months);

  double checkAnnuityLoan = 5599119.26;
  double checkDifferentiatedLoan = 5578125.00;
  ck_assert_int_eq(fabs(resultAnnuityLoan - checkAnnuityLoan) < EPS1, 1);
  ck_assert_int_eq(
      fabs(resultDifferentiatedLoan - checkDifferentiatedLoan) < EPS1, 1);
}
END_TEST

START_TEST(test_60) {
  double principal = 50000000;
  double interestRate = 17.5;
  int months = 600;

  double resultAnnuityLoan =
      calculateAnnuityLoan(principal, interestRate, months);
  double resultDifferentiatedLoan =
      calculateDifferentiatedLoan(principal, interestRate, months);

  double checkAnnuityLoan = 437573861.32;
  double checkDifferentiatedLoan = 269114583.33;
  ck_assert_int_eq(fabs(resultAnnuityLoan - checkAnnuityLoan) < EPS1, 1);
  ck_assert_int_eq(
      fabs(resultDifferentiatedLoan - checkDifferentiatedLoan) < EPS1, 1);
}
END_TEST

START_TEST(test_61) {
  double principal = 50000000;
  double interestRate = 1;
  int months = 12;

  double resultAnnuityLoan =
      calculateAnnuityLoan(principal, interestRate, months);
  double resultDifferentiatedLoan =
      calculateDifferentiatedLoan(principal, interestRate, months);

  double checkAnnuityLoan = 50271246.93;
  double checkDifferentiatedLoan = 50270833.33;
  ck_assert_int_eq(fabs(resultAnnuityLoan - checkAnnuityLoan) < EPS1, 1);
  ck_assert_int_eq(
      fabs(resultDifferentiatedLoan - checkDifferentiatedLoan) < EPS1, 1);
}
END_TEST

START_TEST(test_62) {
  int changesCount = 0;
  double **listDepositChanges = NULL;

  double totalCapitalization = 0.0;
  double accruedInterest = 0.0;

  double depositAmount = 100000;
  int term = 12;
  double percents = 18;
  int frequencyPayments = 12 * DAYS_IN_MONTH;
  int capitalization = 1;
  int code = calculateDeposit(depositAmount, term, percents, frequencyPayments,
                              capitalization, listDepositChanges, changesCount,
                              &totalCapitalization, &accruedInterest);

  int codeCheck = 0;
  double totalCapitalizationCheck = 118000;
  double accruedInterestCheck = 18000;

  ck_assert_int_eq(code, codeCheck);
  ck_assert_int_eq(fabs(totalCapitalization - totalCapitalizationCheck) < EPS,
                   1);

  ck_assert_int_eq(fabs(accruedInterest - accruedInterestCheck) < EPS, 1);
}
END_TEST

START_TEST(test_63) {
  int changesCount = 0;
  double **listDepositChanges = NULL;

  double totalCapitalization = 0.0;
  double accruedInterest = 0.0;

  double depositAmount = 100000;
  int term = 12;
  double percents = 18;
  int frequencyPayments = 1;
  int capitalization = 1;
  int code = calculateDeposit(depositAmount, term, percents, frequencyPayments,
                              capitalization, listDepositChanges, changesCount,
                              &totalCapitalization, &accruedInterest);

  int codeCheck = 0;
  double totalCapitalizationCheck = 119717;
  double accruedInterestCheck = 19717;

  ck_assert_int_eq(code, codeCheck);
  ck_assert_int_eq(fabs(totalCapitalization - totalCapitalizationCheck) < EPS1,
                   1);

  ck_assert_int_eq(fabs(accruedInterest - accruedInterestCheck) < EPS1, 1);
}
END_TEST

START_TEST(test_64) {
  int changesCount = 0;
  double **listDepositChanges = NULL;

  double totalCapitalization = 0.0;
  double accruedInterest = 0.0;

  double depositAmount = 100000;
  int term = 12;
  double percents = 18;
  double frequencyPayments = 32;
  int capitalization = 0;
  int code = calculateDeposit(depositAmount, term, percents, frequencyPayments,
                              capitalization, listDepositChanges, changesCount,
                              &totalCapitalization, &accruedInterest);

  int codeCheck = 0;
  double totalCapitalizationCheck = 100000;
  double accruedInterestCheck = 18000;

  ck_assert_int_eq(code, codeCheck);
  ck_assert_int_eq(fabs(totalCapitalization - totalCapitalizationCheck) < EPS1,
                   1);

  ck_assert_int_eq(fabs(accruedInterest - accruedInterestCheck) < EPS1, 1);
}
END_TEST

START_TEST(test_65) {
  int changesCount = 3;
  double **listDepositChanges = calloc(changesCount, sizeof(double *));
  for (int i = 0; i < changesCount; i++) {
    listDepositChanges[i] = calloc(2, sizeof(double));
  }

  listDepositChanges[0][0] = 1;
  listDepositChanges[0][1] = 1000;

  listDepositChanges[1][0] = 2;
  listDepositChanges[1][1] = 1000;

  listDepositChanges[2][0] = 3;
  listDepositChanges[2][1] = 1000;

  double totalCapitalization = 0.0;
  double accruedInterest = 0.0;

  double depositAmount = 100000;
  int term = 3;
  double percents = 12;
  double frequencyPayments = DAYS_IN_MONTH;
  int capitalization = 1;
  int code = calculateDeposit(depositAmount, term, percents, frequencyPayments,
                              capitalization, listDepositChanges, changesCount,
                              &totalCapitalization, &accruedInterest);

  int codeCheck = 0;
  double totalCapitalizationCheck = 105070;
  double accruedInterestCheck = 3070;

  ck_assert_int_eq(code, codeCheck);
  ck_assert_int_eq(fabs(totalCapitalization - totalCapitalizationCheck) < EPS1,
                   1);

  ck_assert_int_eq(fabs(accruedInterest - accruedInterestCheck) < EPS1, 1);

  for (int i = 0; i < changesCount; i++) {
    free(listDepositChanges[i]);
  }
  free(listDepositChanges);
}
END_TEST

Suite *make_calculate_suite(void) {
  Suite *s = suite_create("calculate");
  TCase *tc = tcase_create("calculate");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);

  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  tcase_add_test(tc, test_22);
  tcase_add_test(tc, test_23);
  tcase_add_test(tc, test_24);
  tcase_add_test(tc, test_25);
  tcase_add_test(tc, test_26);
  tcase_add_test(tc, test_27);
  tcase_add_test(tc, test_28);
  tcase_add_test(tc, test_29);
  tcase_add_test(tc, test_30);
  tcase_add_test(tc, test_31);
  tcase_add_test(tc, test_32);
  tcase_add_test(tc, test_33);
  tcase_add_test(tc, test_34);

  tcase_add_test(tc, test_35);
  tcase_add_test(tc, test_36);
  tcase_add_test(tc, test_37);
  tcase_add_test(tc, test_39);

  tcase_add_test(tc, test_41);
  tcase_add_test(tc, test_42);
  tcase_add_test(tc, test_43);
  tcase_add_test(tc, test_44);
  tcase_add_test(tc, test_45);
  tcase_add_test(tc, test_46);

  tcase_add_test(tc, test_49);
  tcase_add_test(tc, test_50);
  tcase_add_test(tc, test_51);
  tcase_add_test(tc, test_52);
  tcase_add_test(tc, test_53);
  tcase_add_test(tc, test_54);
  tcase_add_test(tc, test_55);
  tcase_add_test(tc, test_56);
  tcase_add_test(tc, test_57);
  tcase_add_test(tc, test_58);

  tcase_add_test(tc, test_59);
  tcase_add_test(tc, test_60);
  tcase_add_test(tc, test_61);

  tcase_add_test(tc, test_62);
  tcase_add_test(tc, test_63);
  tcase_add_test(tc, test_64);
  tcase_add_test(tc, test_65);

  suite_add_tcase(s, tc);
  return s;
}