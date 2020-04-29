#include "frame_buffer.h"
#include "io.h"

char *fb = (char *) 0x000B8000;

void fb_write_cell(unsigned int cell, char c, unsigned char fg, unsigned char bg)
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

void print(char *s)
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

void fb_move_cursor(unsigned short pos)
{
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT,    pos & 0x00FF);
}