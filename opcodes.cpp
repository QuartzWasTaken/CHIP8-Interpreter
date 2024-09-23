#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "include/opcodes.h"

extern BYTE m_GameMemory[0xFFF]; // Le système a 0xFFF octets de mémoire
extern BYTE m_Registers[16]; // 16 registers de 1 byte
extern WORD m_AdressI ;
extern WORD m_ProgramCounter; // L'adresse de la prochaine instruction à exécuter

extern WORD opcode; // Nous donne l'opcode à exécuter

extern BYTE m_ScreenData[64][32];  // La taille de l'écran en pixels
extern std::vector<int> m_Stack;


void Opcode00EE(WORD opcode) // Retourner d'une fonction
{
    m_ProgramCounter = m_Stack.back();
    m_Stack.pop_back();
}

void Opcode1NNN(WORD opcode) // Changer de prochaine instruction
{
    m_ProgramCounter = opcode & 0x0FFF; // La prochaine instruction à effectuer sera la partie NNN de 1NNN
}

void Opcode2NNN(WORD opcode) // Aller dans une fonction
{
    m_Stack.push_back(m_ProgramCounter); // Prendre l'adresse ou on doit aller dans le stack
    m_ProgramCounter = opcode & 0x0FFF; // Y aller
}

void Opcode3XNN(WORD opcode) // Si regX == NN, passer la prochaine instruction
{
    WORD reg = opcode & 0x0F00;
    reg >>= 8;
    WORD NN = opcode & 0x00FF;
    if(m_Registers[reg] == NN) // Voir explication au dessus
    {
        m_ProgramCounter += 2;
    }
}

void Opcode4XNN(WORD opcode) // Si regX != NN, passer la prochaine instruction
{
    WORD reg = opcode & 0x0F00;
    reg >>= 8;
    WORD NN = opcode & 0x00FF;
    if(m_Registers[reg] != NN)
    {
        m_ProgramCounter +=2;
    }
}

void Opcode5XY0(WORD opcode) // Passer la prochaine instruction si regX == regY
{
    WORD regX = opcode & 0x0F00; // On obtient regX = 0x0N00
    regX >>= 8; // On a maintenant 0xN
    WORD regY = opcode & 0x00F0; // On obtient regY = 0x00N0
    regY >>= 4; // On a maintenant 0xN
    //Comparaison simple et skip
    if(m_Registers[regX] == m_Registers[regY])
    {
        m_ProgramCounter += 2;
    }
}

void Opcode6XNN(WORD opcode) // Mettre la valeur de NN dans regX
{
    WORD X = opcode & 0x0F00;
    X >>= 8;
    WORD NN = opcode & 0x00FF;

    m_Registers[X] = NN;
}

void Opcode7XNN (WORD opcode) // Ajouter NN à la valeur de regX et mettre le résultat dans regX
{
    WORD X = opcode & 0x0F00;
    X >>= 8;
    WORD NN = opcode & 0x00FF;
    
    m_Registers[X] += NN;
}

void Opcode8XY0 (WORD opcode) // Met la valeur de regX dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regY] = m_Registers[regX];
}

void Opcode8XY1 (WORD opcode) // Fait un bitwise | et met le résultat dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regX] |= m_Registers[regY];
}

void Opcode8XY2 (WORD opcode) // Fait un bitwise & et met le résultat dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regX] &= m_Registers[regY];
}

void Opcode8XY3 (WORD opcode) // Fait un bitwise ^ et met le résultat dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regX] ^= m_Registers[regY];
}

void Opcode8XY4 (WORD opcode) // Ajoute les valeurs de regX et regY, met le résultat dans regX, et la retenue dans regF si besoin
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;

    BYTE resultat = m_Registers[regX] + m_Registers[regY];
    m_Registers[regX] = resultat;
    if(resultat > 0xFF)
    {
        m_Registers[0xF] = 1;
    }
    else
    {
        m_Registers[0xF] = 0;
    }
}

void Opcode8XY5 (WORD opcode) // Soustrait les valeurs de regX et regY, met le résultat dans regX, et la retenue dans regF si besoin
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;

    BYTE resultat = m_Registers[regX] - m_Registers[regY];
    
    if(m_Registers[regX] > m_Registers[regY])
    {
        m_Registers[0xF] = 1;
    }
    else
    {
        m_Registers[0xF] = 0;
    }

    m_Registers[regX] = resultat;
}

void Opcode8XY6  (WORD opcode) // Met le bit faible dans regF et divise par 2
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    
    m_Registers[0xF] = regX & 0x01;
}
void Opcode8XY7 (WORD opcode) // Soustrait les valeurs de regX et regY, met le résultat dans regX, et la !retenue dans regF si besoin
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;

    BYTE resultat = m_Registers[regX] - m_Registers[regY];
    
    if(m_Registers[regX] < m_Registers[regY])
    {
        m_Registers[0xF] = 1;
    }
    else
    {
        m_Registers[0xF] = 0;
    }

    m_Registers[regX] = resultat;
}
void Opcode8XYE (WORD opcode) // Fait un bitwise & et met le résultat dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regX] &= m_Registers[regY];
}