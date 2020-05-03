#include "../types.h"

#define SERIAL_COM1_BASE 0x3F8

void serial_init(uint16_t com);
int serial_write(uint16_t com, const char *s);
void serial_write_char(uint16_t com, uint8_t c);
