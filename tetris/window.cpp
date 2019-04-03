#include "window.hpp"
#include "SDL2/SDL.h"
#include <iostream>
using namespace::std;
 
bool windowFunctions :: init(SDL_Window** window, SDL_Surface** surface, const int WIDTH, const int HEIGHT) {
    bool success = true;
    if ( SDL_Init (SDL_INIT_VIDEO) < 0) {
        cout << SDL_GetError() << endl;
        success = false;
    } else {
        *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (*window == NULL) {
            cout << SDL_GetError() << endl;
            success = false;
        }
    }
    return success;
}

void windowFunctions :: close(SDL_Window** window) {
    SDL_DestroyWindow(*window);
    *window = NULL;
    SDL_Quit();
}

void windowFunctions :: setBackground(SDL_Renderer* renderer, Color color) {
    // RGB vector
    int rgb[3] = {0,0,0};
    // Set the color
    if (color == RED) rgb[0] = 255;
    if (color == GREEN) rgb[1] = 255;
    if (color == BLUE) rgb[2] = 255;
    if (color == WHITE) {
        for (int i = 0; i < 3; i++)
            rgb[i] = 255;
    }

    // call SDL_RenderClear() to set background to desired color
    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
