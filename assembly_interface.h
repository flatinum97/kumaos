#include "types.h"

#ifndef INCLUDE_ASSEMBLY_INTERFACE_H
#define INCLUDE_ASSEMBLY_INTERFACE_H

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
void lgdt(void *gdt);
void load_idt(void *idt);
void interrupt(uint32_t interrupt_number);
void sti();
void set_page_directory();
void enable_paging();

#endif
