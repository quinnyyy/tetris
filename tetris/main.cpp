#include "SDL2/SDL.h"
#include "window.hpp"
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

windowFunctions fxns; //class containing helper functions

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* background = NULL; //renderer for the background
SDL_Renderer* blocks = NULL; //renderer for blocks


int main(int argc, char* args[]) {
    if (fxns.init(&window, &surface, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        background = SDL_CreateRenderer(window, -1, 0);

        fxns.setBackground(background, WHITE);
        
        
        
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                }
            }
            SDL_UpdateWindowSurface(window);
        }
        
    }
    
    fxns.close(&window);
    return 0;
}
