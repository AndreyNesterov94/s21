#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  if (str) {
    res = malloc((s21_strlen(str) + 1) * sizeof(char));
    if (res) {
      s21_strcpy(res, str);
      for (s21_size_t i = 0; i < s21_strlen(str); i++)
        if (res[i] >= 'a' && res[i] <= 'z') {
          res[i] = res[i] - 32;
        }
    }
  }
  return res;
}