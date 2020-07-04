#ifndef STDIO_H
#define STDIO_H

typedef enum output_t {
  SCREEN,
  LOG
} FILE;

int fprintf (FILE stream, const char *s);
void printf(char *s);
int log(char *s);

#endif
