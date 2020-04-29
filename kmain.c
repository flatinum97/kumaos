#include "drivers/frame_buffer.h"

void kmain() {
  clear_screen();
  char *welcome_message = "Welcome to KUMAOS!";
  print(welcome_message);
  move_cursor(1, 0);
  while(1);
}
