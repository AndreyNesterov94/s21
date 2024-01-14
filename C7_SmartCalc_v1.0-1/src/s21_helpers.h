#ifndef HELPERS
#define HELPERS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_settings.h"

int s21_isNumber(char *str);
int s21_getCountChar(const char *str, char ch);
char **s21_createStringArray(int len);
void s21_freeStringArray(char **array, int len);
int s21_getPrecedence(const char *operation);
int s21_isOperator(const char *token);
int s21_isBinaryOperator(const char *oper);
char *s21_addSpacesToOperations(const char *input);
char **s21_convertToRPN(char **tokens, int count, int *outputCount);
char **s21_getTokensList(const char *example, int *outputCount);

#endif
