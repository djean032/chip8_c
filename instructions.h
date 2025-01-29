#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "chip8.h"
#include <stdio.h>

typedef void (*op_func)(struct chip8 *);

void OP_00E0(struct chip8 *chip8);
void OP_00EE(struct chip8 *chip8);
void OP_0nnn(struct chip8 *chip8);
void OP_1nnn(struct chip8 *chip8);
void OP_2nnn(struct chip8 *chip8);
void OP_3xkk(struct chip8 *chip8);
void OP_4xkk(struct chip8 *chip8);
void OP_5xy0(struct chip8 *chip8);
void OP_6xkk(struct chip8 *chip8);
void OP_7xkk(struct chip8 *chip8);
void OP_8xy0(struct chip8 *chip8);
void OP_8xy1(struct chip8 *chip8);
void OP_8xy2(struct chip8 *chip8);
void OP_8xy3(struct chip8 *chip8);
void OP_8xy4(struct chip8 *chip8);
void OP_8xy5(struct chip8 *chip8);
void OP_8xy6(struct chip8 *chip8);
void OP_8xy7(struct chip8 *chip8);
void OP_8xyE(struct chip8 *chip8);
void OP_9xy0(struct chip8 *chip8);
void OP_Annn(struct chip8 *chip8);
void OP_Bnnn(struct chip8 *chip8);
void OP_Cxkk(struct chip8 *chip8);
void OP_Dxyn(struct chip8 *chip8);
void OP_Ex9E(struct chip8 *chip8);
void OP_ExA1(struct chip8 *chip8);
void OP_Fx07(struct chip8 *chip8);
void OP_Fx0A(struct chip8 *chip8);
void OP_Fx15(struct chip8 *chip8);
void OP_Fx18(struct chip8 *chip8);
void OP_Fx1E(struct chip8 *chip8);
void OP_Fx29(struct chip8 *chip8);
void OP_Fx33(struct chip8 *chip8);
void OP_Fx55(struct chip8 *chip8);
void OP_Fx65(struct chip8 *chip8);
void OP_NULL(struct chip8 *chip8);
void OP_Test(struct chip8 *chip8);

#endif // !INSTRUCTIONS_H
