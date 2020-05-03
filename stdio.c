#include "stdio.h"
#include "drivers/frame_buffer.h"
#include "drivers/serial_port.h"

int fprintf(FILE stream, const char *format, ...)
{
  switch (stream) {
    case (SCREEN):
      return fb_write(format);
      break;
    case (LOG):
      return serial_write(SERIAL_COM1_BASE, format);
      break;
  }

  return 0;
}

void printf(char *s)
{
  fprintf(SCREEN, s);
}

int log(char *format, ...)
{
  return serial_write(SERIAL_COM1_BASE, format);
}
