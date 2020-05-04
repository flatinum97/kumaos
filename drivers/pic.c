#include "pic.h"
#include "../stdio.h"
#include "../assembly_interface.h"

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

#define PIC1_DATA_PORT (PIC1_PORT_A + 1)
#define PIC2_DATA_PORT (PIC2_PORT_A + 1)

#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7

#define PIC_ACK 0x20

void pic_init()
{
  outb(PIC1_DATA_PORT, 0b11111101); // Only enable keyboard (IRC 1)
  outb(PIC2_DATA_PORT, 0b11111111); // Don't enable any interrupts on PIC2 (IRC 8-15)
  sti();
}

void pic_acknowledge()
{
  outb(PIC1_PORT_A, PIC_ACK);
  log("ACK sended\n");
}
