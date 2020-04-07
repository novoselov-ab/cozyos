#include "vga.h"

#include <kernel/ports.h>
#include <kernel/tty.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static char* const VGA_MEMORY = (char*)0xB8000;

#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5


extern "C"
{

    int get_offset(int col, int row)
    {
        return 2 * (row * VGA_WIDTH + col);
    }
    int get_offset_row(int offset)
    {
        return offset / (2 * VGA_WIDTH);
    }
    int get_offset_col(int offset)
    {
        return (offset - (get_offset_row(offset) * 2 * VGA_WIDTH)) / 2;
    }

    namespace
    {

    int get_cursor_offset()
    {
        /* Use the VGA ports to get the current cursor position
         * 1. Ask for high byte of the cursor offset (data 14)
         * 2. Ask for low byte (data 15)
         */
        port_byte_out(REG_SCREEN_CTRL, 14);
        int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
        port_byte_out(REG_SCREEN_CTRL, 15);
        offset += port_byte_in(REG_SCREEN_DATA);
        return offset * 2; /* Position * size of character cell */
    }

    void set_cursor_offset(int offset)
    {
        /* Similar to get_cursor_offset, but instead of reading we write data */
        offset /= 2;
        port_byte_out(REG_SCREEN_CTRL, 14);
        port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
        port_byte_out(REG_SCREEN_CTRL, 15);
        port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
    }

    int print_char(char c, int col, int row, char attr)
    {
        unsigned char* vidmem = (unsigned char*)VGA_MEMORY;
        if (!attr)
            attr = WHITE_ON_BLACK;

        /* Error control: print a red 'E' if the coords aren't right */
        if (col >= VGA_WIDTH || row >= VGA_HEIGHT)
        {
            vidmem[2 * (VGA_WIDTH) * (VGA_HEIGHT)-2] = 'E';
            vidmem[2 * (VGA_WIDTH) * (VGA_HEIGHT)-1] = RED_ON_WHITE;
            return get_offset(col, row);
        }

        int offset;
        if (col >= 0 && row >= 0)
            offset = get_offset(col, row);
        else
            offset = get_cursor_offset();

        if (c == '\n')
        {
            row = get_offset_row(offset);
            offset = get_offset(0, row + 1);
        }
        else
        {
            vidmem[offset] = c;
            vidmem[offset + 1] = attr;
            offset += 2;
        }

        /* Check if the offset is over screen size and scroll */
        if (offset >= VGA_HEIGHT * VGA_WIDTH * 2)
        {
            int i;
            for (i = 1; i < VGA_HEIGHT; i++)
                memcpy(get_offset(0, i - 1) + VGA_MEMORY, get_offset(0, i) + VGA_MEMORY, VGA_WIDTH * 2);

            /* Blank last line */
            char* last_line = get_offset(0, VGA_HEIGHT - 1) + VGA_MEMORY;
            for (i = 0; i < VGA_WIDTH * 2; i++)
                last_line[i] = 0;

            offset -= 2 * VGA_WIDTH;
        }

        set_cursor_offset(offset);
        return offset;
    }
    }

    void tty_clear_screen()
    {
        int screen_size = VGA_WIDTH * VGA_HEIGHT;
        int i;
        char* screen = VGA_MEMORY;

        for (i = 0; i < screen_size; i++)
        {
            screen[i * 2] = ' ';
            screen[i * 2 + 1] = WHITE_ON_BLACK;
        }
        set_cursor_offset(get_offset(0, 0));
    }

    void tty_initialize(void)
    {
        tty_clear_screen();
    }

    void tty_putchar(char c)
    {
        int offset = get_cursor_offset();
        int row = get_offset_row(offset);
        int col = get_offset_col(offset);
        print_char(c, col, row, WHITE_ON_BLACK);
    }

    void tty_print(const char* message)
    {
        int i = 0;
        while (message[i] != 0)
        {
            tty_putchar(message[i++]);
        }
    }

    void tty_print_at(const char* message, int col, int row)
    {
        int offset = get_offset(col, row);
        set_cursor_offset(offset);
        tty_print(message);
    }
}