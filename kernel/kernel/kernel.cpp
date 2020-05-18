#include <kernel/tty.h>
#include <isr.h>

#include <stdio.h>

extern "C"
{

    void kernel_main(void)
    {
        isr_install();
        tty_initialize();

        for (int i = 0; i < 10; i++)
            printf("Hello, kernel World BOOM BOOM %d!\n", i);


        /* Test the interrupts */
        __asm__ __volatile__("int $1");
         //__asm__ __volatile__("int $3");
    }
}