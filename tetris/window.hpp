#ifndef window_hpp
#define window_hpp
#include "SDL2/SDL.h"

enum Color {RED, GREEN, BLUE, WHITE, BLACK};

class windowFunctions {
public:
    bool init(SDL_Window** window, SDL_Surface** surface , const int WIDTH, const int HEIGHT);
    void close(SDL_Window** window);
    void setBackground(SDL_Renderer* renderer, Color color);
};

#endif /* window_hpp */
