#include <iostream>
#include "cstring.h"

size_t Strlen(const char* str) {
  size_t cnt = 0;
  while (str[cnt] != '\0') {
    ++cnt;
  }
  return cnt;
}
int Strcmp(const char* first, const char* second) {
  size_t l = 0;
  size_t len = std::min(Strlen(first), Strlen(second));
  while (first[l] == second[l] && l < len) {
    ++l;
  }
  if (first[l] > second[l]) {
    return 1;
  }
  if (first[l] < second[l]) {
    return -1;
  }
  return 0;
}
int Strncmp(const char* first, const char* second, size_t count) {
  size_t l = 0;
  if (count == 0) {
    return 0;
  }
  --count;
  size_t len = std::min(Strlen(first), Strlen(second));
  while (first[l] == second[l] && l < len && count > 0) {
    ++l;
    --count;
  }
  if (first[l] > second[l]) {
    return 1;
  }
  if (first[l] < second[l]) {
    return -1;
  }
  return 0;
}
char* Strcpy(char* dest, const char* src) {
  for (size_t i = 0; i < Strlen(src); ++i) {
    dest[i] = src[i];
  }
  dest[Strlen(src)] = '\0';
  return dest;
}
char* Strncpy(char* dest, const char* src, size_t count) {
  size_t i;
  size_t len = Strlen(src);
  for (i = 0; i < count; ++i) {
    if (i < len) {
      dest[i] = src[i];
    } else {
      break;
    }
  }
  while (i < count) {
    dest[i] = '\0';
    ++i;
  }
  return dest;
}
char* Strcat(char* dest, const char* src) {
  char* ind = dest + Strlen(dest);
  while (*src != '\0') {
    *ind = *src;
    ++ind;
    ++src;
  }
  return dest;
}
char* Strncat(char* dest, const char* src, size_t count) {
  char* ind = dest + Strlen(dest);
  while (*src != '\0' && count != 0) {
    *ind = *src;
    ++ind;
    ++src;
    --count;
  }
  return dest;
}
const char* Strchr(const char* str, char symbol) {
  size_t len = Strlen(str) + 1;
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == symbol) {
      return str + i;
    }
  }
  return nullptr;
}
const char* Strrchr(const char* str, char symbol) {
  size_t len = Strlen(str) + 1;
  for (int i = len - 1; i >= 0; --i) {
    if (str[i] == symbol) {
      return str + i;
    }
  }
  return nullptr;
}
size_t Strspn(const char* dest, const char* src) {
  size_t cnt = 0;
  size_t l1 = Strlen(dest);
  size_t l2 = Strlen(src);
  bool flag = true;
  for (size_t i = 0; i < l1; ++i) {
    for (size_t j = 0; j < l2; ++j) {
      if (dest[i] == src[j]) {
        ++cnt;
        flag = false;
        break;
      }
      flag = true;
    }
    if (flag) {
      return cnt;
    }
  }
  return cnt;
}
size_t Strcspn(const char* dest, const char* src) {
  size_t cnt = 0;
  size_t l1 = Strlen(dest);
  size_t l2 = Strlen(src);
  bool flag = true;
  for (size_t i = 0; i < l1; ++i) {
    for (size_t j = 0; j < l2; ++j) {
      if (dest[i] == src[j]) {
        flag = false;
      }
    }
    if (flag) {
      ++cnt;
    } else {
      return cnt;
    }
  }
  return cnt;
}
const char* Strpbrk(const char* dest, const char* breakset) {
  size_t l1 = Strlen(dest);
  size_t l2 = Strlen(breakset);
  for (size_t i = 0; i < l1; ++i) {
    for (size_t j = 0; j < l2; ++j) {
      if (dest[i] == breakset[j]) {
        return dest + i;
      }
    }
  }
  return nullptr;
}
bool Equal(const char* str, const char* pattern) {
  while (*str != '\0' && *pattern != '\0') {
    if (*str != *pattern) {
      return false;
    }
    str++;
    pattern++;
  }
  return (*pattern == '\0');
}
const char* Strstr(const char* str, const char* pattern) {
  if (Equal(str, pattern)) {
    return str;
  }
  while (*str != '\0') {
    if ((*str == *pattern) && Equal(str, pattern)) {
      return str;
    }
    ++str;
  }
  return nullptr;
}