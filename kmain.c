#include "drivers/frame_buffer.h"
#include "drivers/serial_port.h"

enum output_t {
  SCREEN,
  LOG
};

void write(enum output_t output_device, char *s)
{
  switch (output_device) {
    case (SCREEN):
      fb_write(s);
      break;
    case (LOG):
      serial_write(SERIAL_COM1_BASE, s);
      break;
  }
}

void printf(char *s)
{
  write(SCREEN, s);
}

void kmain()
{
  clear_screen();
  static char *welcome_message = "Welcome to KUMAOS!";
  printf(welcome_message);

  serial_init(SERIAL_COM1_BASE);
  write(LOG, "Initialized serial port.\n");

  move_cursor(10, 0);

  while(1);
}
