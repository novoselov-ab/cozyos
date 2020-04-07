#include <stdio.h>

#include <kernel/tty.h>

extern "C" 
{

void kernel_main(void) {
	tty_initialize();
	for (int i = 0; i < 100000; i++)
		printf("Hello, kernel World BOOM BOOM %c!\n", (char)(i % 255));
}

}