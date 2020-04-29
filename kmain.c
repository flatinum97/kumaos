#include "drivers/frame_buffer.h"

void kmain() {
  clear_screen();
  print("Hello, World!");
  while(1);
}
