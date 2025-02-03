#ifndef CHIP8_C
#define CHIP8_C

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define VIDEO_HEIGHT 32
#define VIDEO_WIDTH 64
#define START_ADDRESS 0x200
#define FONTSET_SIZE 80
#define FONTSET_START_ADDRESS 0x50

struct chip8
{
  uint8_t registers[16];
  uint8_t memory[4096];
  uint16_t index;
  uint16_t counter;
  uint16_t stack[16];
  uint8_t stack_pointer;
  uint8_t delay_timer;
  uint8_t sound_timer;
  uint8_t keypad[16];
  uint32_t video[64 * 32];
  uint16_t opcode;
};

int rand_byte (void);

struct chip8 init_chip8 (void);
void load_rom (char const *filename, struct chip8 *chip8);

#endif // !CHIP8_C
