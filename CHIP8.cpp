#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "SDL2/SDL.h"
#include "imgui/imgui.h"

#include "include/opcodes.h"

// Le jeu s'exécute de 0x200 à 0x1FF

BYTE m_GameMemory[0xFFF]; // Le système a 0xFFF octets de mémoire
BYTE m_Registers[16]; // 16 registers de 1 byte
WORD m_AdressI ;
WORD m_ProgramCounter; // L'adresse de la prochaine instruction à exécuter

WORD opcode; // Nous donne l'opcode à exécuter

BYTE m_ScreenData[SCREEN_WIDTH][SCREEN_HEIGHT];  // La taille de l'écran en pixels
std::vector<int> m_Stack;

int CreateSDLWindow()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL n'a pas réussi à initialiser la vidéo.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void CPUReset(char* romPath)
{
    m_AdressI = 0;
    m_ProgramCounter = 0x200 ; // La prochaine instruction à exécuter sera à l'adresse 0x200 (la première)
    memset(m_Registers, 0, sizeof(m_Registers)); // Mettre les registers à 0

    // Charger le fichier du jeu
    FILE *in;
    in = fopen(romPath, "rb"); // Ouvrir le fichier du jeu dans la variable *in
    fread(&m_GameMemory[0x200], 0xfff, 1, in); // Mettre tout le fichier de taille 0xFFF dans la mémoire en "1" fois
    fclose(in); // Fermer le fichier ouvert
}

bool isBitSet(int num, int bit)
{
    return (num >> bit & 1);
}

WORD GetNextOpcode() // Chercher la prochaine instruction à exécuter
{
    // Exemple : on a un opcode 0xABCD
    WORD res = 0; // res désigne l'opcode qu'on va exécuter : 0x0000
    res = m_GameMemory[m_ProgramCounter]; // Dans res charger la première moitié de l'opcode, localisé dans la mémoire à l'addresse de m_ProgramCounter : 0xAB
    res <<= 8; // Shift res de 8 à gauche (rajouter 00 à la fin) : 0xAB00
    res |= m_GameMemory[m_ProgramCounter+1]; // Rajouter la deuxième moitié de l'opcode 0xABCD
    m_ProgramCounter += 2; // Faire avancer le pointeur d'instructions
    return res; // On a notre opcode, on peut le return
}

void ExecuteOpcode(SDL_Renderer* renderer)
{
    opcode = GetNextOpcode(); // Assigne l'opcode à la prochaine instruction

    switch(opcode & 0xF000)
    {
        case 0x0000:
            if(opcode == 0x00EE)
            {
                Opcode00EE(opcode);
            }
            else if(opcode == 0x00E0)
            {
                SDL_RenderClear(renderer);
            }
            break;

        case 0x1000:
            Opcode1NNN(opcode); // Gérer les opcodes commençant par 1
            break;

        case 0x2000:
            Opcode2NNN(opcode);
            break;

        case 0x3000:
            Opcode3XNN(opcode);
            break;
        
        case 0x4000:
            Opcode4XNN(opcode);
            break;

        case 0x5000:
            Opcode5XY0(opcode);
            break;
        
        case 0x6000:
            Opcode6XNN(opcode);
            break;

        case 0x7000:
            Opcode7XNN(opcode);
            break;

        case 0x8000:
            Handle8Opcodes(opcode);
            printf("- %04X -> Opcode géré\n", opcode);
            break;

        case 0xA000:
            OpcodeANNN(opcode);
            break;

        case 0xD000:
            OpcodeDXYN(opcode);
            break;

        default: // Opcode pas encore pris en charge
            printf("- %04X -> Unimplemented\n", opcode);
            break;
    }
}

void RedrawScreen(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_Rect rect;

    for(int y = 0; y < SCREEN_HEIGHT; y++) // Commencer à dessiner le sprite
    {
        for(int x = 0; x < SCREEN_WIDTH; x++)
        {
            int rangee = m_ScreenData[x][y];
            for (int p = 0; p < 8; p++)
            {
                rect.x = (x*8 + p) * SCALE_FACTOR;
                rect.y = y * SCALE_FACTOR;
                rect.w = SCALE_FACTOR;
                rect.h = SCALE_FACTOR;

                WORD pixel = rangee & (0x80 >> p);
                if(pixel)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    CPUReset(argv[1]);
    CreateSDLWindow();
    SDL_Window* window = SDL_CreateWindow("Ma fenêtre", 0, 0, 640, 320, 0);
    SDL_Event event;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

    bool loopShouldStop = false;

    if(!window)
    {
        printf("SDL n'a pas réussi à initialiser la fenêtre.\n");
    }
    else
    {
        printf("Fenêtre initialisée\n");
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    printf("Le CPU a été réinitialisé\n");

    while(!loopShouldStop)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                loopShouldStop = true;
            }
        }

        ExecuteOpcode(renderer);
        RedrawScreen(renderer);
        SDL_RenderPresent(renderer);
    }
    
    return 0;
}