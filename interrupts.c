#include "interrupts.h"
#include "stdio.h"

void interrupt_handler(struct cpu_state cpu, uint32_t interrupt_number, uint32_t error_code) {
  // Avoid unused parameter errors
  (void) cpu;
  (void) interrupt_number;
  (void) error_code;
  return;
}
