#ifndef STRING_H
#define STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* restrict dest, const void* restrict src, size_t n);
void* memmove(void* dest, const void* src, size_t n);

char* strcpy(char* restrict dest, const char* restrict src);
char* strncpy(char* restrict dest, const char* restrict src, size_t n);
char* strcat(char* restrict dest, const char* restrict src);
char* strncat(char* restrict dest, const char* restrict src, size_t n);

int memcmp(const void* ptr1, const void* ptr2, size_t n);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t n);

void* memchr(const void* src, int c, size_t n);
char* strchr(const char* str, int c);

char* strrchr(const char* str, int c);

void* memset(void* dest, int c, size_t n);
size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif

#endif/* STRING_H */
