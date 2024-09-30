#pragma once

typedef unsigned char BYTE;
typedef unsigned short int WORD;

const int SCREEN_WIDTH = 8;
const int SCREEN_HEIGHT = 32;
const int SPRITE_WIDTH = 8;
const int SCALE_FACTOR = 10;

bool isBitSet (int num, int bit);
SDL_Rect* CalculateRect(SDL_Rect* rect, WORD sprite, WORD opcode);

void Handle8Opcodes(WORD opcode);

void Opcode00E0 (WORD opcode);
void Opcode00EE (WORD opcode);
void Opcode1NNN (WORD opcode);
void Opcode2NNN (WORD opcode);
void Opcode3XNN (WORD opcode);
void Opcode4XNN (WORD opcode);
void Opcode5XY0 (WORD opcode);
void Opcode6XNN (WORD opcode);
void Opcode7XNN (WORD opcode);
void Opcode8XY0 (WORD opcode);
void Opcode8XY1 (WORD opcode);
void Opcode8XY2 (WORD opcode);
void Opcode8XY3 (WORD opcode);
void Opcode8XY4 (WORD opcode);
void Opcode8XY5 (WORD opcode);
void Opcode8XY6 (WORD opcode);
void Opcode8XY7 (WORD opcode);
void Opcode8XYE (WORD opcode);
void Opcode8XY0 (WORD opcode);
void OpcodeANNN (WORD opcode);
void OpcodeDXYN (WORD opcode);
