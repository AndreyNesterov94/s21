#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src && trim_chars) {
    int start = 0;
    while (src[start] != '\0' &&
           (s21_strchr(trim_chars, src[start]) != s21_NULL)) {
      start++;
    }
    int end = s21_strlen(src) - 1;
    while (start != end && (s21_strchr(trim_chars, src[end]) != s21_NULL)) {
      end--;
    }
    if (end < start) {
      end = start;
    }
    res = (char *)malloc((end - start + 2) * sizeof(char));
    if (res) {
      s21_strncpy(res, src + start, end - start + 1);
      res[end - start + 1] = '\0';
    }
  }
  return res;
}