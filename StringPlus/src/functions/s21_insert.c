#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = "";
  s21_size_t len_res = 0;
  int flag = 0;
  if (!src || !str || start_index > s21_strlen(src)) {
    len_res = 1;
    flag = 1;
  } else if (s21_strlen(str) == 0) {
    len_res = s21_strlen(src) + 2;
    flag = 2;
  } else {
    len_res = s21_strlen(str) + s21_strlen(src) + 1;
    flag = 3;
  }
  res = (char *)calloc(len_res, sizeof(char));
  if (flag == 1) {
    free(res);
    res = S21_NULL;
  } else if (flag == 2) {
    s21_size_t i = 0;
    for (; i < s21_strlen(src); i++) res[i] = src[i];
    res[i + 1] = '\0';
  } else if (flag == 3) {
    s21_size_t i = 0;
    for (; i < start_index; i++) res[i] = src[i];
    s21_size_t tmp = i;
    for (s21_size_t j = 0; j < s21_strlen(str); j++, i++) res[i] = str[j];
    for (; tmp < s21_strlen(src); i++, tmp++) res[i] = src[tmp];
    res[i] = '\0';
  }

  return (void *)res;
}
