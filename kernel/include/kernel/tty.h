#pragma once

#include <stddef.h>

#include <sys/cdefs.h>

__BEGIN_EXTERN_C

void tty_initialize(void);
void tty_clear_screen(void);
void tty_putchar(char c);
void tty_print_at(const char* message, int col, int row);
void tty_print(const char* message);

__END_EXTERN_C
