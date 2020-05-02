#include "drivers/frame_buffer.h"
#include "drivers/serial_port.h"
#include "assembly_interface.h"
#include "types.h"

enum output_t {
  SCREEN,
  LOG
};

struct gdt_t {
  u_int32 address;
  u_int16 size;
} __attribute__((packed));

struct segment_selector {
  u_int16 address;
  u_int16 size;
} __attribute__((packed));

u_int16 segment_selectors[] = {
  0x0, // null descriptor
  (0x08 << 4), // kernel code segment
  (0x10 << 4), // kernel data segment
};

void initialize_gdt()
{
  struct gdt_t gdt;
  gdt.address = (u_int32) segment_selectors;
  gdt.size = sizeof(segment_selectors);
  lgdt(&gdt);
}

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

void log(char *s)
{
  write(LOG, s);
}

void kmain()
{
  clear_screen();
  static char *welcome_message = "Welcome to KUMAOS!";
  printf(welcome_message);

  serial_init(SERIAL_COM1_BASE);
  log("Initialized serial port.\n");

  initialize_gdt();
  log("Loaded global descriptor table.\n");

  move_cursor(10, 0);

  while(1);
}
