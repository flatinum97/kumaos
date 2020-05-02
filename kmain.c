#include "drivers/frame_buffer.h"
#include "drivers/serial_port.h"

void kmain() {
  clear_screen();
  char *welcome_message = "Welcome to KUMAOS!";
  print(welcome_message);

  serial_init(SERIAL_COM1_BASE);
  serial_print(SERIAL_COM1_BASE, "Hello, World!\n");

  move_cursor(10, 0);

  while(1);
}
