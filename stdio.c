#include "stdio.h"
#include "drivers/frame_buffer.h"
#include "drivers/serial_port.h"

int fprintf(FILE stream, const char *s)
{
  switch (stream) {
    case (SCREEN):
      return fb_write(s);
      break;
    case (LOG):
      return serial_write(SERIAL_COM1_BASE, s);
      break;
  }

  return 0;
}

void printf(char *s)
{
  fprintf(SCREEN, s);
}

int log(char *s)
{
  return fprintf(LOG, s);
}
