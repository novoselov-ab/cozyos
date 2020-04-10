#pragma once

#include <sys/cdefs.h>

#include <stddef.h>

__BEGIN_EXTERN_C

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict dst, const void* __restrict src, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
void strrev(char*);

__END_EXTERN_C
