#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t src_len = s21_strlen(src);

  s21_size_t copy_len;
  if (src_len < n) {
    copy_len = src_len;
  } else {
    copy_len = n;
  }

  s21_memcpy(dest, src, copy_len);
  dest[copy_len] = '\0';

  return dest;
}
