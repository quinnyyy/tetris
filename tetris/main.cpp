#include "SDL2/SDL.h"
#include "window.hpp"
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 600;
const int BLOCK_WIDTH = SCREEN_WIDTH/10;
const int BLOCK_HEIGHT = SCREEN_HEIGHT/20;
const int frameRate = 30;
const int frameMs = 1000 / frameRate;

windowFunctions fxns; //class containing helper functions

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;

grid Board;

int main(int argc, char* args[]) {
    if (fxns.init(&window, &surface, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        renderer = SDL_CreateRenderer(window, 0, 0);
        
        //block test(SQUARE);
        //Board.updateBlock(&test, false);

        
        bool quit = false;
        SDL_Event e;
        
        bool newBlock = true;
        block* myBlock = nullptr;
        
        while (!quit) {
            if (newBlock == true) {
                if (myBlock == nullptr) delete myBlock;
                myBlock = new block(SQUARE);
                Board.updateBlock(myBlock, false);
                newBlock = false;
            }
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP: {
                            quit = true;
                            break;
                        }
                        case SDLK_DOWN: {
                            //Board.updateBlock(&test,false);
                            newBlock = myBlock -> move(DOWN, &Board);
                            Board.paintBoard(renderer, BLOCK_WIDTH, BLOCK_HEIGHT);
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                }
            }
            
            SDL_Delay(frameMs);
            Board.paintBoard(renderer, BLOCK_WIDTH, BLOCK_HEIGHT);
            //SDL_UpdateWindowSurface(window);
        }
        
    }
    
    fxns.close(&window);
    return 0;
}
