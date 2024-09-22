#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "opcodes.h"

extern BYTE m_GameMemory[0xFFF]; // Le système a 0xFFF octets de mémoire
extern BYTE m_Registers[16]; // 16 registers de 1 byte
extern WORD m_AdressI ;
extern WORD m_ProgramCounter; // L'adresse de la prochaine instruction à exécuter

extern WORD opcode; // Nous donne l'opcode à exécuter

extern BYTE m_ScreenData[64][32];  // La taille de l'écran en pixels
extern std::vector<int> m_Stack;

void Opcode1NNN(WORD opcode) // Changer de prochaine instruction
{
    m_ProgramCounter = opcode & 0x0FFF; // La prochaine instruction à effectuer sera la partie NNN de 1NNN
}

void Opcode2NNN(WORD opcode) // Aller dans une fonction
{
    m_Stack.push_back(m_ProgramCounter); // Prendre l'adresse ou on doit aller dans le stack
    m_ProgramCounter = opcode & 0x0FFF; // Y aller
}

void Opcode00EE(WORD opcode) // Retourner d'une fonction
{
    m_ProgramCounter = m_Stack.back();
    m_Stack.pop_back();
}

void Opcode5XY0(WORD opcode) // Passer la prochaine instruction si X == Y
{
    int regX = opcode & 0x0F00; // On obtient regX = 0x0N00
    regX >>= 8; // On a maintenant 0xN
    int regY = opcode & 0x00F0; // On obtient regY = 0x00N0
    regY >>= 4; // On a maintenant 0xN
    //Comparaison simple et skip
    if(m_Registers[regX] == m_Registers[regY])
    {
        m_ProgramCounter += 4;
    }
}

void Opcode3XNN(WORD opcode) // Si regX == NN, passer l'instruction en cours
{
    int reg = opcode & 0x0F00;
    int NN = opcode & 0x00FF;
    if(m_Registers[reg] == NN) // Voir explication au dessus
    {
        m_ProgramCounter += 4;
    }
}