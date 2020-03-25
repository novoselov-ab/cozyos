#include <stdio.h>

#include <kernel/tty.h>

char x = 'A';

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World BOOM BOOM %c!\n", x);
}
