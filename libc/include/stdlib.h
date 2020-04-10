#pragma once

#include <sys/cdefs.h>

__BEGIN_EXTERN_C

__attribute__((__noreturn__))
void abort(void);
int itoa(int num, char* str, int len, int base);

__END_EXTERN_C