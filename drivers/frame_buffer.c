#include "frame_buffer.h"
#include "../assembly_interface.h"
#include "../types.h"

u_int8 *fb = (u_int8 *) 0x000B8000;

void fb_write_cell(u_int32 cell, u_int8 c, u_int8 fg, u_int8 bg)
{
  int i = cell*2;
  fb[i] = c;
  fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void clear_screen()
{
  for (int i = 0; i < FB_CELLS; i++) {
    fb_write_cell(i, ' ', FB_BLACK, FB_BLACK);
  }
}

void fb_write(char *s)
{
  int i = 0;
  while(s[i]) {
    fb_write_cell(i, s[i], FB_WHITE, FB_BLACK);
    i++;
  }
}

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

void move_cursor_to_pos(unsigned short pos)
{
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT,    pos & 0x00FF);
}

void move_cursor(unsigned short row, unsigned short col)
{
  move_cursor_to_pos(row*FB_COLS + col);
}
