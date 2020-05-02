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

struct segment_descriptor_t {
  u_int16 base_0_15;
  u_int16 limit_0_15;
  u_int8 base_24_31;
  u_int8 flags_and_limit_16_19;
  u_int8 access_byte;
  u_int8 base_16_23;
} __attribute__((packed));

enum segment_selector_t {
  NULL_DESCRIPTOR, // Not but has to be here
  KERNEL_CODE_SEGMENT, // Offset 0x8
  KERNEL_DATA_SEGMENT, // Offset 0x10
};

struct segment_descriptor_t segment_descriptors[3];

void initialize_gdt()
{
  struct gdt_t gdt;
  gdt.address = (u_int32) segment_descriptors;
  gdt.size = sizeof(segment_descriptors);

  segment_descriptors[KERNEL_CODE_SEGMENT].base_0_15 = 0x0;
  segment_descriptors[KERNEL_CODE_SEGMENT].base_24_31 = 0x0;
  segment_descriptors[KERNEL_CODE_SEGMENT].limit_0_15 = 0xFFFF;
  segment_descriptors[KERNEL_CODE_SEGMENT].flags_and_limit_16_19 = (0b1000 << 4) & 0xF;
  segment_descriptors[KERNEL_CODE_SEGMENT].access_byte &= 0b10010110;

  segment_descriptors[KERNEL_DATA_SEGMENT].base_0_15 = 0x0;
  segment_descriptors[KERNEL_DATA_SEGMENT].base_24_31 = 0x0;
  segment_descriptors[KERNEL_DATA_SEGMENT].limit_0_15 = 0xFFFF;
  segment_descriptors[KERNEL_CODE_SEGMENT].flags_and_limit_16_19 = (0b1000 << 4) & 0xF;
  segment_descriptors[KERNEL_CODE_SEGMENT].access_byte &= 0b10010110;
  lgdt(&gdt);


  // Grub has already loaded the segment registers
  // with the correct values (0x8 for cs, 0x10 for the others)
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
