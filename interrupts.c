#include "interrupts.h"
#include "stdio.h"
#include "assembly_interface.h"
#include "drivers/pic.h"
#include "drivers/keyboard.h"
#include "drivers/frame_buffer.h"

char scan_code_table[128] = {
  0,    // 0x00
  0,    // 0x01
  '1',  // 0x02
  '2',  // 0x03
  '3',  // 0x04
  '4',  // 0x05
  '5',  // 0x06
  '6',  // 0x07
  '7',  // 0x08
  '8',  // 0x09
  '9',  // 0x0a
  '0',  // 0x0b
  '-',  // 0x0c
  '=',  // 0x0d
  0,    // 0x0e
  0,    // 0x0f
  'q',  // 0x10
  'w',  // 0x11
  'e',  // 0x12
  'r',  // 0x13
  't',  // 0x14
  'y',  // 0x15
  'u',  // 0x16
  'i',  // 0x17
  'o',  // 0x18
  'p',  // 0x19
  '[',  // 0x1a
  ']',  // 0x1b
  '\n', // 0x1c
  0,    // 0x1d
  'a',  // 0x1e
  's',  // 0x1f
  'd',  // 0x20
  'f',  // 0x21
  'g',  // 0x22
  'h',  // 0x23
  'j',  // 0x24
  'k',  // 0x25
  'l',  // 0x26
  ':',  // 0x27
  '"',  // 0x28
  '`',  // 0x29
  0,    // 0x2a
  '\\', // 0x2b
  'z',  // 0x2c
  'x',  // 0x2d
  'c',  // 0x2e
  'v',  // 0x2f
  'b',  // 0x30
  'n',  // 0x31
  'm',  // 0x32
  ',',  // 0x33
  '.',  // 0x34
  '/',  // 0x35
  0,    // 0x36
  0,    // 0x37
  0,    // 0x38
  ' ',  // 0x39
  0,    // 0x3a
  0,    // 0x3b
  0,    // 0x3c
  0,    // 0x3d
  0,    // 0x3e
  0,    // 0x3f
  0,    // 0x40
  0,    // 0x41
  0,    // 0x42
  0,    // 0x43
  0,    // 0x44
  0,    // 0x45
  0,    // 0x46
  0,    // 0x47
  0,    // 0x48
  0,    // 0x49
  0,    // 0x4a
  0,    // 0x4b
  0,    // 0x4c
  0,    // 0x4d
  0,    // 0x4e
  0,    // 0x4f
  0,    // 0x50
  0,    // 0x51
  0,    // 0x52
  0,    // 0x53
  0,    // 0x54
  0,    // 0x55
  0,    // 0x56
  0,    // 0x57
  0,    // 0x58
  0,    // 0x59
  0,    // 0x5a
  0,    // 0x5b
  0,    // 0x5c
  0,    // 0x5d
  0,    // 0x5e
  0,    // 0x5f
  0,    // 0x60
  0,    // 0x61
  0,    // 0x62
  0,    // 0x63
  0,    // 0x64
  0,    // 0x65
  0,    // 0x66
  0,    // 0x67
  0,    // 0x68
  0,    // 0x69
  0,    // 0x6a
  0,    // 0x6b
  0,    // 0x6c
  0,    // 0x6d
  0,    // 0x6e
  0,    // 0x6f
  0,    // 0x70
  0,    // 0x71
  0,    // 0x72
  0,    // 0x73
  0,    // 0x74
  0,    // 0x75
  0,    // 0x76
  0,    // 0x77
  0,    // 0x78
  0,    // 0x79
  0,    // 0x7a
  0,    // 0x7b
  0,    // 0x7c
  0,    // 0x7d
  0,    // 0x7e
  0,    // 0x7f
};

void keyboard_handler()
{
  uint8_t scan_code = read_scan_code();
  char c = 0;
  if (scan_code < 128) {
    c = scan_code_table[scan_code];
  } else {
    // key up
  }
  if (c != 0) {
    fb_write_byte(c);
  }
}

void interrupt_handler(struct cpu_state cpu, uint32_t interrupt_number, uint32_t error_code) {
  // Avoid unused parameter errors
  (void) cpu;
  (void) error_code;

  switch(interrupt_number) {
    case(0x00000009):
      log("Keyboard interrupt was called.\n");
      keyboard_handler();
      break;
    default:
      log("Unhandled interrupt occured.\n");
      break;
  }

  pic_acknowledge();
}
