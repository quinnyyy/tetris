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
    //SDL_RenderPresent(renderer);
}

block :: block(Piece p) {
    color = mapColor(p);
    piece = p;
    coords = mapStartingCoords(p);
}

block :: ~block() {
    delete coords;
}

pair<int,int>* block :: mapStartingCoords(Piece p) {
    pair<int,int>* coordinates = new pair<int,int>[4];
    switch(p) {
        case LONG: {
            coordinates[0] = {3,0};
            coordinates[1] = {4,0};
            coordinates[2] = {5,0};
            coordinates[3] = {6,0};
            break;
        }
        case SQUARE: {
            coordinates[0] = {4,0};
            coordinates[1] = {4,1};
            coordinates[2] = {5,0};
            coordinates[3] = {5,1};
            break;
        }
        case S1: {
            coordinates[0] = {3,0};
            coordinates[1] = {4,0};
            coordinates[2] = {4,1};
            coordinates[3] = {5,1};
            break;
        }
        case S2: {
            coordinates[0] = {3,1};
            coordinates[1] = {4,1};
            coordinates[2] = {4,0};
            coordinates[3] = {5,0};
            break;
        }
        case L1: {
            coordinates[0] = {3,0};
            coordinates[1] = {3,1};
            coordinates[2] = {4,1};
            coordinates[3] = {5,1};
            break;
        }
        case L2: {
            coordinates[0] = {3,1};
            coordinates[1] = {4,1};
            coordinates[2] = {5,1};
            coordinates[3] = {5,0};
            break;
        }
        case T: {
            coordinates[0] = {3,1};
            coordinates[1] = {4,1};
            coordinates[2] = {4,0};
            coordinates[3] = {5,1};
            break;
        }
    }
    return coordinates;
}

Color block :: mapColor(Piece p) {
    Color c;
    switch(p) {
        case LONG: {
            c = BLUE;
            break;
        }
        case SQUARE: {
            c = RED;
            break;
        }
        case L1: {
            c = GREEN;
            break;
        }
        case L2: {
            c = YELLOW;
            break;
        }
        case S1: {
            c = PURPLE;
            break;
        }
        case S2: {
            c = ORANGE;
            break;
        }
        case T: {
            c = CYAN;
            break;
        }
    }
    return c;
}

pair<int,int>* block :: getCoords(){
    return coords;
}

Color block :: getColor(){
    return color;
}

bool block :: move(Direction d, grid* g) {
    bool legal = true;
    if (d == DOWN) {
        for (int i = 0; i < 4; i++) {
            bool sameBlock = false;
            for (int j = 0; j < 4; j++)
                if (coords[i].first == coords[j].first && coords[i].second + 1 == coords[j].second) sameBlock = true;
            if ((g -> squares[coords[i].first][coords[i].second + 1] != WHITE && sameBlock == false) || coords[i].second == 19) {
                legal = false;
                break;
            }
        }
        if (legal == true) {
            g -> updateBlock(this, true);
            for (int i = 0; i < 4; i++) {
                coords[i].second++;
            }
            g -> updateBlock(this, false);
        }
        
    }
    
    return legal ? false : true;
}

/*
void block :: paintBlock(SDL_Renderer *renderer) {
    int rgb[3] = {0,0,0};
    if (color == RED) rgb[0] = 255;
    if (color == GREEN) rgb[1] = 255;
    if (color == BLUE) rgb[2] = 255;
    if (color == WHITE) {
        for (int i = 0; i < 3; i++)
            rgb[i] = 255;
    }
    
    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderFillRects(renderer, squares, 4);
}
*/
grid :: grid() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 20; j++)
            squares[i][j] = WHITE;
}

void grid :: updateXY(int X, int Y, Color c) {
    squares[X][Y] = c;
}

void grid :: updateBlock(block* b, bool deleting) {
    cout << "hello world" << endl;
    pair<int,int>* coords = b -> getCoords();
    Color c = deleting ? WHITE : b -> getColor();
    for (int i = 0; i < 4; i++) {
        cout << coords[i].first << " " << coords[i].second << endl;
        squares[coords[i].first][coords[i].second] = c;
    }
}

void grid :: paintBoard(SDL_Renderer *renderer, const int W, const int H) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            int* rgb = mapColor(squares[i][j]);
            //cout << *(rgb) << endl;
            //cout << *(rgb + sizeof(int)) << endl;
            //cout << *(rgb + sizeof(int)*2) << endl;
            //SDL_SetRenderDrawColor(renderer, *(rgb), *(rgb + sizeof(int)), *(rgb + sizeof(int)*2), 255);
            SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
            SDL_Rect rect = {i * W, j * H, W, H};
            SDL_RenderFillRect(renderer, &rect);
            delete rgb;
            }
    }
    SDL_RenderPresent(renderer);
}

int* grid :: mapColor(Color c) {
    int* rgb = new int[3];
    switch (c) {
        case RED: {
            rgb[0] = 255;
            rgb[1] = 0;
            rgb[2] = 0;
            break;
        }
        case GREEN: {
            rgb[0] = 0;
            rgb[1] = 255;
            rgb[2] = 0;
            break;
        }
        case BLUE: {
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 255;
            break;
        }
        case WHITE: {
            rgb[0] = 255;
            rgb[1] = 255;
            rgb[2] = 255;
            break;
        }
        case BLACK: {
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 0;
            break;
        }
        case PURPLE: {
            rgb[0] = 203;
            rgb[1] = 66;
            rgb[2] = 244;
            break;
        }
        case YELLOW: {
            rgb[0] = 241;
            rgb[1] = 244;
            rgb[2] = 66;
            break;
        }
        case ORANGE: {
            rgb[0] = 244;
            rgb[1] = 152;
            rgb[2] = 66;
            break;
        }
        case CYAN: {
            rgb[0] = 66;
            rgb[1] = 238;
            rgb[2] = 244;
            break;
        }
    }
    return rgb;
}

