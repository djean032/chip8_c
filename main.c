#include "chip8.h"
#include "instructions.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  struct chip8 chip8 = init_chip8();
  load_rom(filename, chip8);
  int rng = rand_byte();
  printf("%d\n", rng);

  op_func table[15];
  table[0x0] = OP_Test;

  table[0x0](&chip8);
  return 1;
}
