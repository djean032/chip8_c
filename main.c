#include "include/chip8.h"
#include "include/graphics.h"
#include "include/instructions.h"
#include <Windows.h>
#include <stdio.h>
#include <synchapi.h>
#include <timeapi.h>

void Table0 (struct chip8 *chip8);
void Table8 (struct chip8 *chip8);
void TableE (struct chip8 *chip8);
void TableF (struct chip8 *chip8);
void execute_opcode (struct chip8 *chip8);
void cycle (struct chip8 *chip8);
void init_table (op_func *table_pointer, int size);

op_func table[0xF + 1];
op_func table0[0xE + 1];
op_func table8[0xE + 1];
op_func tableE[0xE + 1];
op_func tableF[0x65 + 1];

int
main (int argc, char *argv[])
{
  if (argc != 4)
    {
      fprintf (stderr, "Provide filename and arguments!\n");
      exit (0);
    }
  int video_scale = atoi (argv[1]);
  int cycle_delay = atoi (argv[2]);
  char const *filename = argv[3];

  init_table (table, 0xF + 1);
  init_table (table0, 0xE + 1);
  init_table (table8, 0xE + 1);
  init_table (tableE, 0xE + 1);
  init_table (tableF, 0x65 + 1);

  table[0x0] = Table0;
  table[0x1] = OP_1nnn;
  table[0x2] = OP_2nnn;
  table[0x3] = OP_3xkk;
  table[0x4] = OP_4xkk;
  table[0x5] = OP_5xy0;
  table[0x6] = OP_6xkk;
  table[0x7] = OP_7xkk;
  table[0x8] = Table8;
  table[0x9] = OP_9xy0;
  table[0xA] = OP_Annn;
  table[0xB] = OP_Bnnn;
  table[0xC] = OP_Cxkk;
  table[0xD] = OP_Dxyn;
  table[0xE] = TableE;
  table[0xF] = TableF;

  table0[0x0] = OP_00E0;
  table0[0xE] = OP_00EE;

  table8[0x0] = OP_8xy0;
  table8[0x1] = OP_8xy1;
  table8[0x2] = OP_8xy2;
  table8[0x3] = OP_8xy3;
  table8[0x4] = OP_8xy4;
  table8[0x5] = OP_8xy5;
  table8[0x6] = OP_8xy6;
  table8[0x7] = OP_8xy7;
  table8[0xE] = OP_8xyE;

  tableE[0x1] = OP_ExA1;
  tableE[0xE] = OP_Ex9E;

  tableF[0x07] = OP_Fx07;
  tableF[0x0A] = OP_Fx0A;
  tableF[0x15] = OP_Fx15;
  tableF[0x18] = OP_Fx18;
  tableF[0x1E] = OP_Fx1E;
  tableF[0x29] = OP_Fx29;
  tableF[0x33] = OP_Fx33;
  tableF[0x55] = OP_Fx55;
  tableF[0x65] = OP_Fx65;

  struct chip8 chip8 = init_chip8 ();
  struct platform platform
      = init_platform ("CHIP-8 Emulator", VIDEO_WIDTH * video_scale,
                       VIDEO_HEIGHT * video_scale, VIDEO_WIDTH, VIDEO_HEIGHT);

  load_rom (filename, &chip8);

  int video_pitch = sizeof (chip8.video[0]) * VIDEO_WIDTH;

  int last_cycle_time = timeGetTime ();

  bool quit = false;

  execute_opcode (&chip8);

  while (!quit)
    {
      quit = process_input (&chip8);

      int current_time = timeGetTime ();
      int diff = current_time - last_cycle_time;

      if (diff > cycle_delay)
        {
          last_cycle_time = current_time;
          cycle (&chip8);
          update_frame (&platform, &chip8, video_pitch);
        }
    }

  return 1;
}

void
Table0 (struct chip8 *chip8)
{
  table0[chip8->opcode & 0x000F](chip8);
}
void
Table8 (struct chip8 *chip8)
{
  table8[chip8->opcode & 0x000F](chip8);
}
void
TableE (struct chip8 *chip8)
{
  tableE[chip8->opcode & 0x000F](chip8);
}
void
TableF (struct chip8 *chip8)
{
  tableF[chip8->opcode & 0x00FF](chip8);
}
void
init_table (op_func *table_pointer, int size)
{
  for (int i = 0; i <= size; i++)
    {
      table_pointer[i] = OP_NULL;
    }
}
void
execute_opcode (struct chip8 *chip8)
{
  table[(chip8->opcode & 0xF000) >> 12](chip8);
}

void
cycle (struct chip8 *chip8)
{
  chip8->opcode = (chip8->memory[chip8->counter] << 8)
                  | chip8->memory[chip8->counter + 1];

  chip8->counter += 2;

  execute_opcode (chip8);

  if (chip8->delay_timer > 0)
    {
      chip8->delay_timer--;
    }

  if (chip8->sound_timer > 0)
    {
      chip8->sound_timer--;
    }
}
