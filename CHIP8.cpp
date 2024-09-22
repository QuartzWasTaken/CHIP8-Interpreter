#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "opcodes.h"

// Le jeu s'exécute de 0x200 à 0x1FF

BYTE m_GameMemory[0xFFF]; // Le système a 0xFFF octets de mémoire
BYTE m_Registers[16]; // 16 registers de 1 byte
WORD m_AdressI ;
WORD m_ProgramCounter; // L'adresse de la prochaine instruction à exécuter

WORD opcode; // Nous donne l'opcode à exécuter

BYTE m_ScreenData[64][32];  // La taille de l'écran en pixels
std::vector<int> m_Stack;

void CPUReset()
{
    m_AdressI = 0;
    m_ProgramCounter = 0x200 ; // La prochaine instruction à exécuter sera à l'adresse 0x200 (la première)
    memset(m_Registers, 0, sizeof(m_Registers)); // Mettre les registers à 0

    // Charger le fichier du jeu
    FILE *in;
    in = fopen("/home/gab/projects/CHIP8/Breakout.ch8", "rb"); // Ouvrir le fichier du jeu dans la variable *in
    fread(&m_GameMemory[0x200], 0xfff, 1, in); // Mettre tout le fichier de taille 0xFFF dans la mémoire en "1" fois
    fclose(in); // Fermer le fichier ouvert
}

WORD GetNextOpcode() // Chercher la prochaine instruction à exécuter
{
    // Exemple : on a un opcode 0xABCD
    WORD res = 0; // res désigne l'opcode qu'on va exécuter : 0x0000
    res = m_GameMemory[m_ProgramCounter]; // Dans res charger la première moitié de l'opcode, localisé dans la mémoire à l'addresse de m_ProgramCounter : 0xAB
    res <<= 8; // Shift res de 8 à gauche (rajouter 00 à la fin) : 0xAB00
    res |= m_GameMemory[m_ProgramCounter+1]; // Rajouter la deuxième moitié de l'opcode 0xABCD
    return res; // On a notre opcode, on peut le return
}

void ExecuteOpcode()
{
    opcode = GetNextOpcode(); // Assigne l'opcode à la prochaine instruction

    switch(opcode & 0xF000)
    {
        case 0x1000:
            Opcode1NNN(opcode); // Gérer les opcodes commençant par 1
            break;

        case 0x0000:
            break;

        case 0x2000:
            Opcode2NNN(opcode);
        default: // Opcode pas encore pris en charge
            break;
    }
}

int main()
{
    CPUReset();
    printf("Le CPU a été réinitialisé\n");
    printf("m_ProgramCounter = %d\n",  m_ProgramCounter);
    printf("opcode = %d\n",  opcode);
    for(double lV = 0; lV <= 50; lV++)
    {
        printf("i = %d\n");
        std::cout << GetNextOpcode() << std::endl;
        ExecuteOpcode();
        printf("m_ProgramCounter = %d\n",  m_ProgramCounter);
        printf("opcode boucle = %d\n", opcode);
        printf("Nouveau build");
    }
    
    return 0;
}