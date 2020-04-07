#pragma once

#include <stddef.h>
#include <sys/cdefs.h>


__BEGIN_EXTERN_C

unsigned char port_byte_in (unsigned short port);
void port_byte_out (unsigned short port, unsigned char data);
unsigned short port_word_in (unsigned short port);
void port_word_out (unsigned short port, unsigned short data);

__END_EXTERN_C
