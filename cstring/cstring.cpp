#include <cstddef>

#include "cstring.h"

size_t Strlen(const char* str) {
  size_t l = 0;
  char c = *str;
  while (c != '\0') {
    ++l;
    c = *(++str);
  }
  return l;
}

int Strcmp(const char* first, const char* second) {
  while (*first != '\0' && *second != '\0') {
    if (*first < *second) {
      return -1;
    }
    if (*second < *first) {
      return 1;
    }
    ++first;
    ++second;
  }
  if (*first == '\0' && *second != '\0') {
    return -1;
  }
  if (*first != '\0') {
    return 1;
  }
  return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t i = 0;
  size_t j = 0;
  while (*first != '\0' && *second != '\0' && i < count && j < count) {
    if (*first < *second) {
      return -1;
    }
    if (*second < *first) {
      return 1;
    }
    ++first;
    ++second;
    ++i;
    ++j;
  }
  if (i == count || j == count) {
    return 0;
  }
  if (*first == '\0' && *second != '\0') {
    return -1;
  }
  if (*first != '\0' && *second == '\0') {
    return 1;
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  char* real_dest = dest;
  while (*src != '\0') {
    *(dest++) = *(src++);
  }
  *dest = *src;
  return real_dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  char* real_dest = dest;
  size_t i = 0;
  while (*src != '\0' && i < count) {
    *(dest++) = *(src++);
    ++i;
  }
  while (i < count) {
    *(dest++) = '\0';
    ++i;
  }
  return real_dest;
}

char* Strcat(char* dest, const char* src) {
  size_t l = Strlen(dest);
  char* real_dest = dest;
  dest += l;
  while (*src != '\0') {
    *(dest++) = *(src++);
  }
  *dest = '\0';
  return real_dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  if (Strlen(src) < count) {
    return Strcat(dest, src);
  }
  size_t l = Strlen(dest);
  char* real_dest = dest;
  dest += l;
  size_t i = 0;
  while (i < count) {
    *(dest++) = *(src++);
    ++i;
  }
  *dest = '\0';
  return real_dest;
}

const char* Strchr(const char* str, char symbol) {
  while (*str != '\0') {
    if (*(str++) == symbol) {
      return (--str);
    }
  }
  if (*str == symbol) {
    return str;
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  const char* real_str = str;
  str += Strlen(str);
  while (str >= real_str) {
    if (*(str--) == symbol) {
      return (++str);
    }
  }
  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  size_t amount = 0;
  while (*dest != '\0') {
    if (Strchr(src, *dest) != nullptr) {
      ++amount;
      ++dest;
    } else {
      return amount;
    }
  }
  return amount;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t amount = 0;
  while (*dest != '\0') {
    if (Strchr(src, *dest) == nullptr) {
      ++amount;
      ++dest;
    } else {
      return amount;
    }
  }
  return amount;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  if (*dest == '\0') {
    return nullptr;
  }
  if (*(dest + Strcspn(dest, breakset)) == '\0') {
    return nullptr;
  }
  return dest + Strcspn(dest, breakset);
}

const char* Strstr(const char* str, const char* pattern) {
  size_t l_pattern = Strlen(pattern);
  size_t l_str = Strlen(str);
  if (l_str < l_pattern) {
    return nullptr;
  }
  if (l_pattern == 0) {
    return str;
  }
  while (*str != '\0') {
    const char* str_try = str;
    const char* pattern_try = pattern;
    while (*pattern_try != '\0' && *str_try == *pattern_try) {
      ++str_try;
      ++pattern_try;
    }
    if (*pattern_try == '\0') {
      return str;
    }
    ++str;
  }
  return nullptr;
}
