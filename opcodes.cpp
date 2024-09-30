#include <stdio.h>
#include <bitset>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "SDL2/SDL.h"
#include "include/opcodes.h"

extern BYTE m_GameMemory[0xFFF]; // Le système a 0xFFF octets de mémoire
extern BYTE m_Registers[16]; // 16 registers de 1 byte
extern WORD m_AdressI ;
extern WORD m_ProgramCounter; // L'adresse de la prochaine instruction à exécuter

extern WORD opcode; // Nous donne l'opcode à exécuter

extern BYTE m_ScreenData[SCREEN_WIDTH][SCREEN_HEIGHT];  // La taille de l'écran en pixels
extern std::vector<int> m_Stack;

void Handle8Opcodes(WORD opcode)
{
    switch(opcode & 0x000F)
    {
        case 0:
            Opcode8XY0(opcode);
            break;
        case 1:
            Opcode8XY1(opcode);
            break;
        case 2:
            Opcode8XY2(opcode);
            break;
        case 3:
            Opcode8XY3(opcode);
            break;
        case 4:
            Opcode8XY4(opcode);
            break;
        case 5:
            Opcode8XY5(opcode);
            break;
        case 6:
            Opcode8XY6(opcode);
            break;
        case 7:
            Opcode8XY7(opcode);
            break;
        case 0xE:
            Opcode8XYE(opcode);
            break;
        default:
            break;
    }
}

void Opcode00E0 (WORD opcode)
{
    memset(m_ScreenData, 0, SCREEN_HEIGHT * SCREEN_WIDTH);
}

void Opcode00EE (WORD opcode) // Retourner d'une fonction
{
    printf("- 00EE -> Retour de la fonction %#x à", m_ProgramCounter);

    m_ProgramCounter = m_Stack.back();
    m_Stack.pop_back();

    printf("%#x", m_ProgramCounter);
}

void Opcode1NNN (WORD opcode) // Changer de prochaine instruction
{
    m_ProgramCounter = opcode & 0x0FFF; // La prochaine instruction à effectuer sera la partie NNN de 1NNN
}

void Opcode2NNN (WORD opcode) // Aller dans une fonction
{
    m_Stack.push_back(m_ProgramCounter); // Prendre l'adresse ou on doit aller dans le stack
    m_ProgramCounter = opcode & 0x0FFF; // Y aller

    printf("- %04X -> Entrée dans la subroutine %04X\n", opcode, m_Stack.back());
}

void Opcode3XNN (WORD opcode) // Si regX == NN, passer la prochaine instruction
{
    WORD reg = opcode & 0x0F00;
    reg >>= 8;
    WORD NN = opcode & 0x00FF;
    if(m_Registers[reg] == NN) // Voir explication au dessus
    {
        m_ProgramCounter += 2;
    }
    printf("- %04X -> Opcode géré\n", opcode);
}

void Opcode4XNN (WORD opcode) // Si regX != NN, passer la prochaine instruction
{
    WORD reg = opcode & 0x0F00;
    reg >>= 8;
    WORD NN = opcode & 0x00FF;
    if(m_Registers[reg] != NN)
    {
        m_ProgramCounter +=2;
    }
    printf("- %04X -> Opcode géré\n", opcode);
}

void Opcode5XY0 (WORD opcode) // Passer la prochaine instruction si regX == regY
{
    WORD regX = opcode & 0x0F00; // On obtient regX = 0x0N00
    regX >>= 8; // On a maintenant 0xN
    WORD regY = opcode & 0x00F0; // On obtient regY = 0x00N0
    regY >>= 4; // On a maintenant 0xN
    //Comparaison simple et skip
    if(m_Registers[regX] == m_Registers[regY])
    {
        m_ProgramCounter += 2;
        printf("- %04X -> regX (%01X) est égal à regY (%01X), tous deux de valeur %04X\n", opcode, regX, regY, m_Registers[regX]);
    } else
    {
        printf("- %04X -> regX (%01X) de valeur (%04X) n'est pas égal à regY (%04X) de valeur %04X\n", opcode, regX, m_Registers[regX], regY, m_Registers[regY]);
    }
}

void Opcode6XNN (WORD opcode) // Mettre la valeur de NN dans regX
{
    WORD X = opcode & 0x0F00;
    X >>= 8;
    WORD NN = opcode & 0x00FF;

    m_Registers[X] = NN;
    printf("- %04X -> Mis la valeur %02X dans le registre 0x%01x\n", opcode, NN, X);
}

void Opcode7XNN (WORD opcode) // Ajouter NN à la valeur de regX et mettre le résultat dans regX
{
    WORD X = opcode & 0x0F00;
    X >>= 8;
    WORD NN = opcode & 0x00FF;
    printf("- %04X -> Ancienne valeur du registre %#x : %#x\n", opcode, X, m_Registers[X]);
    m_Registers[X] = m_Registers[X] + NN;
    printf("- %04X -> Nouvelle valeur du registre %#x : %#x (ajout de %#x)\n", opcode, X, m_Registers[X]);
}

void Opcode8XY0 (WORD opcode) // Met la valeur de regX dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regX] = m_Registers[regY];
    printf("- %04X -> Mis la valeur de regY (0x%01X) dans regX (0x%01X)", opcode, regY, regX);
}

void Opcode8XY1 (WORD opcode) // Fait un bitwise | et met le résultat dans regY
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;
    m_Registers[regX] |= m_Registers[regY];
}

void Opcode8XY2 (WORD opcode) //but like Fait un bitwise & et met le résultat dans regY
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
    
    if(m_Registers[regX] <= m_Registers[regY])
    {
        m_Registers[0xF] = 1;
    }
    else
    {
        m_Registers[0xF] = 0;
    }

    m_Registers[regX] = resultat;
}

void Opcode8XY6 (WORD opcode) // Met le bit faible dans regF et divise par 2
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;

    WORD oldReg = m_Registers[regY];

    m_Registers[regX] = m_Registers[regY] >> 1;
    
    m_Registers[0xF] = oldReg & 0x01;
}

void Opcode8XY7 (WORD opcode) // Soustrait les valeurs de regX et regY, met le résultat dans regX, et la !retenue dans regF si besoin
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;

    BYTE resultat = m_Registers[regY] - m_Registers[regX];

    if(m_Registers[regY] <= m_Registers[regX])
    {
        m_Registers[0xF] = 1;
    }
    else
    {
        m_Registers[0xF] = 0;
    }

    m_Registers[regX] = resultat;
}

void Opcode8XYE (WORD opcode) // regX est égal à regY mais shift d'un à gauche
{
    WORD regX = opcode & 0x0F00;
    regX >>= 8;
    WORD regY = opcode & 0x00F0;
    regY >>= 4;

    m_Registers[regX] = m_Registers[regY] << 1; // Mettre dans regX le regY shift à gauche

    m_Registers[0xF] = m_Registers[regY] >> 7; // Mettre le bit qu'on vient de shift dans regF
}

void OpcodeANNN (WORD opcode)
{
    WORD NNN = opcode & 0x0FFF;
    m_AdressI = NNN;
    printf("- %04X -> Mis le registre I à %#x\n", opcode, NNN);
}

void DoXOR (int X, int Y, BYTE row)
{
    m_Registers[0xF] |= (m_ScreenData[X][Y] & row) != 0;
    m_ScreenData[X][Y] ^= row;
}

void RenderAsText()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            int rangee = m_ScreenData[j][i];
            for (int p = 0; p < 8; p++)
            {
                int pixel = rangee & (0x80 >> p);
                if(pixel != 0)
                {
                    printf("X");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void OpcodeDXYN (WORD opcode) // Dessiner un sprite de N pixels de haut à X, Y
{
    WORD height = opcode & 0x000F; // La hauteur du sprite à dessiner
    WORD x = m_Registers[(opcode & 0x0F00) >> 8] % 64 / 8;
    WORD y = m_Registers[(opcode & 0x00F0) >> 4] % 32;
    int xOffset = m_Registers[(opcode & 0x0F00) >> 8] % 8; // L'offset est la quantité qui dépasse de 8
    

    m_Registers[0xF] = 0;

    for (int _y = 0; _y < height; _y++)
    {
        if(y + _y == SCREEN_HEIGHT)
        {
            break;
        }
        BYTE row = m_GameMemory[m_AdressI + _y]; // Déterminer la rangée à dessiner

        if(xOffset) // Si offset il y a
        {
            BYTE leftByte = row >> xOffset;
            BYTE rightByte = row << 8 - xOffset;
            DoXOR(x, _y + y, leftByte);
            DoXOR(x + 1, _y + y, rightByte);
        }
        else
        {
            DoXOR(x, _y + y, row);
        }
    }
    printf("- %04X -> Dessiné à (%d, %d)\n", opcode, x, y);
    // RenderAsText();
}