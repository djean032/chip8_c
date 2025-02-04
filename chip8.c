#include "include/chip8.h"
#include <stdio.h>
#include <time.h>

struct chip8
init_chip8 (void)
{
  uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
  struct chip8 *chip8 = malloc (sizeof (struct chip8));
  chip8->counter = START_ADDRESS;
  for (unsigned int i = 0; i < FONTSET_SIZE; i++)
    {
      chip8->memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }
  return *chip8;
}

int
rand_byte (void)
{
  int result = 0;
  srand (time (NULL));
  result = rand () % 255;
  return result;
}

void
load_rom (char const *filename, struct chip8 *chip8)
{
  FILE *fptr;

  fptr = fopen (filename, "rb");

  if (fptr == NULL)
    {
      printf ("The ROM could not be loaded. Program exiting now.");
      exit (0);
    };

  fseek (fptr, 0, SEEK_END);
  long sz = ftell (fptr);
  char *buffer = malloc (sizeof (char) * sz);
  fseek (fptr, 0, SEEK_SET);

  fread (buffer, sizeof (char), sz, fptr);
  fclose (fptr);

  for (long i = 0; i < sz; i++)
    {
      chip8->memory[START_ADDRESS + i] = buffer[i];
    }

  free (buffer);
}
