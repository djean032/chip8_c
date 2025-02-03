#include "include/instructions.h"
#include "include/chip8.h"

void
OP_00E0 (struct chip8 *chip8)
{
  memset (chip8->video, 0, sizeof (chip8->video));
}

void
OP_00EE (struct chip8 *chip8)
{
  chip8->stack_pointer--;
  chip8->counter = chip8->stack[chip8->stack_pointer];
}

void
OP_1nnn (struct chip8 *chip8)
{
  uint16_t address = chip8->opcode & 0x0FFF;
  chip8->counter = address;
}

void
OP_2nnn (struct chip8 *chip8)
{
  uint16_t address = chip8->opcode & 0x0FFF;
  chip8->stack[chip8->stack_pointer] = chip8->counter;
  chip8->stack_pointer++;
  chip8->counter = address;
}

void
OP_3xkk (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t byte = chip8->opcode & 0x00FF;
  if (chip8->registers[Vx] == byte)
    {
      chip8->counter += 2;
    }
}

void
OP_4xkk (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t byte = chip8->opcode & 0x00FF;
  if (chip8->registers[Vx] != byte)
    {
      chip8->counter += 2;
    }
}

void
OP_5xy0 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  if (chip8->registers[Vx] == chip8->registers[Vy])
    {
      chip8->counter += 2;
    }
}

void
OP_6xkk (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t byte = chip8->opcode & 0x00FF;
  chip8->registers[Vx] = byte;
}

void
OP_7xkk (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t byte = chip8->opcode & 0x00FF;
  chip8->registers[Vx] += byte;
}

void
OP_8xy0 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  chip8->registers[Vx] = chip8->registers[Vy];
}

void
OP_8xy1 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  chip8->registers[Vx] |= chip8->registers[Vy];
}

void
OP_8xy2 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  chip8->registers[Vx] &= chip8->registers[Vy];
}

void
OP_8xy3 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  chip8->registers[Vx] ^= chip8->registers[Vy];
}

void
OP_8xy4 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  uint16_t sum = chip8->registers[Vx] + chip8->registers[Vy];
  if (sum > 255)
    {
      chip8->registers[0xF] = 1;
    }
  else
    {
      chip8->registers[0xF] = 0;
    }
  chip8->registers[Vx] = sum & 0xFF;
}

void
OP_8xy5 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  if (chip8->registers[Vx] > chip8->registers[Vy])
    {
      chip8->registers[0xF] = 1;
    }
  else
    {
      chip8->registers[0xF] = 0;
    }
  chip8->registers[Vx] -= chip8->registers[Vy];
}

void
OP_8xy6 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  chip8->registers[0xF] = chip8->registers[Vx] & 0x1;
  chip8->registers[Vx] >>= 1;
}

void
OP_8xy7 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  if (chip8->registers[Vy] > chip8->registers[Vx])
    {
      chip8->registers[0xF] = 1;
    }
  else
    {
      chip8->registers[0xF] = 0;
    }
  chip8->registers[Vx] = chip8->registers[Vy] - chip8->registers[Vx];
}

void
OP_8xyE (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  chip8->registers[0xF] = (chip8->registers[Vx] & 0x80) >> 7;
  chip8->registers[Vx] <<= 1;
}

void
OP_9xy0 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  if (chip8->registers[Vx] != chip8->registers[Vy])
    {
      chip8->counter += 2;
    }
}

void
OP_Annn (struct chip8 *chip8)
{
  uint16_t address = chip8->opcode & 0x0FFF;
  chip8->index = address;
}

void
OP_Bnnn (struct chip8 *chip8)
{
  uint16_t address = chip8->opcode & 0x0FFF;
  chip8->counter = chip8->registers[0] + address;
}

void
OP_Cxkk (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t byte = chip8->opcode & 0x00FF;
  chip8->registers[Vx] = rand_byte () & byte;
}

void
OP_Dxyn (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip8->opcode & 0x00F0) >> 4;
  uint8_t height = (chip8->opcode & 0x000F);

  uint8_t x_pos = chip8->registers[Vx] % VIDEO_WIDTH;
  uint8_t y_pos = chip8->registers[Vy] % VIDEO_HEIGHT;

  chip8->registers[0xF] = 0;
  for (unsigned int row = 0; row < height; row++)
    {
      uint8_t spryte_byte = chip8->memory[chip8->index + row];
      for (unsigned int col = 0; col < 8; col++)
        {
          uint8_t sprite_pixel = spryte_byte & (0x80 >> col);
          uint32_t *screen_pixel
              = &chip8->video[(y_pos + row) * VIDEO_WIDTH + (x_pos + col)];

          if (sprite_pixel)
            {
              if (*screen_pixel == 0xFFFFFFFF)
                {
                  chip8->registers[0xF] = 1;
                }
              *screen_pixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void
OP_Ex9E (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t key = chip8->registers[Vx];
  if (chip8->keypad[key])
    {
      chip8->counter += 2;
    }
}

void
OP_ExA1 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t key = chip8->registers[Vx];
  if (!chip8->keypad[key])
    {
      chip8->counter += 2;
    }
}

void
OP_Fx07 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  chip8->registers[Vx] = chip8->delay_timer;
}

void
OP_Fx0A (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  if (chip8->keypad[0])
    {
      chip8->registers[Vx] = 0;
    }
  else if (chip8->keypad[1])
    {
      chip8->registers[Vx] = 1;
    }
  else if (chip8->keypad[1])
    {
      chip8->registers[Vx] = 1;
    }
  else if (chip8->keypad[2])
    {
      chip8->registers[Vx] = 2;
    }
  else if (chip8->keypad[3])
    {
      chip8->registers[Vx] = 3;
    }
  else if (chip8->keypad[4])
    {
      chip8->registers[Vx] = 4;
    }
  else if (chip8->keypad[5])
    {
      chip8->registers[Vx] = 5;
    }
  else if (chip8->keypad[6])
    {
      chip8->registers[Vx] = 6;
    }
  else if (chip8->keypad[7])
    {
      chip8->registers[Vx] = 7;
    }
  else if (chip8->keypad[8])
    {
      chip8->registers[Vx] = 8;
    }
  else if (chip8->keypad[9])
    {
      chip8->registers[Vx] = 9;
    }
  else if (chip8->keypad[10])
    {
      chip8->registers[Vx] = 10;
    }
  else if (chip8->keypad[11])
    {
      chip8->registers[Vx] = 11;
    }
  else if (chip8->keypad[12])
    {
      chip8->registers[Vx] = 12;
    }
  else if (chip8->keypad[13])
    {
      chip8->registers[Vx] = 13;
    }
  else if (chip8->keypad[14])
    {
      chip8->registers[Vx] = 14;
    }
  else if (chip8->keypad[15])
    {
      chip8->registers[Vx] = 15;
    }
  else
    {
      chip8->counter -= 2;
    }
}

void
OP_Fx15 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  chip8->delay_timer = chip8->registers[Vx];
}

void
OP_Fx18 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  chip8->sound_timer = chip8->registers[Vx];
}

void
OP_Fx1E (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  chip8->index += chip8->registers[Vx];
}

void
OP_Fx29 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t digit = chip8->registers[Vx];
  chip8->index = FONTSET_START_ADDRESS + (5 * digit);
}

void
OP_Fx33 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  uint8_t value = chip8->registers[Vx];

  chip8->memory[chip8->index + 2] = value % 10;
  value /= 10;

  chip8->memory[chip8->index + 1] = value % 10;
  value /= 10;

  chip8->memory[chip8->index] = value % 10;
}

/*
  void OP_Fx55_quirk(struct chip8 *chip8) {
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  for (uint8_t i = 0; i <= Vx; i++) {
    chip8->memory[chip8->index + i] = chip8->registers[i];
  }
  chip8->index += Vx + 1;
}
*/

void
OP_Fx55 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  for (uint8_t i = 0; i <= Vx; i++)
    {
      chip8->memory[chip8->index + i] = chip8->registers[i];
    }
}

/*
void OP_Fx65_quirk(struct chip8 *chip8) {
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  for (uint8_t i = 0; i <= Vx; i++) {
    chip8->registers[i] = chip8->memory[chip8->index + i];
  }
  chip8->index += Vx + 1;
}
*/

void
OP_Fx65 (struct chip8 *chip8)
{
  uint8_t Vx = (chip8->opcode & 0x0F00) >> 8;
  for (uint8_t i = 0; i <= Vx; i++)
    {
      chip8->registers[i] = chip8->memory[chip8->index + i];
    }
}

void
OP_NULL (struct chip8 *chip8)
{
}

void
OP_Test (struct chip8 *chip8)
{
  printf ("Test successful\n");
}
