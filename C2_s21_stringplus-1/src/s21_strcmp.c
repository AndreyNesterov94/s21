#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  for (; *str1 && *str1 == *str2; str1++, str2++)
    ;
  int res = 0;
  if (*str1 - *str2 > 0) {
    res = 1;
  } else if (*str1 - *str2 < 0) {
    res = -1;
  }
  return res;
}