#include "../types.h"

#define SERIAL_COM1_BASE 0x3F8

void serial_init(u_int16 com);
void serial_write(u_int16 com, char *s);
void serial_write_char(u_int16 com, u_int8 c);
