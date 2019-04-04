#ifndef window_hpp
#define window_hpp
#include "SDL2/SDL.h"
#include <vector>
using namespace std;

enum Color {RED, GREEN, BLUE, WHITE, BLACK, YELLOW, PURPLE, ORANGE, CYAN};
enum Piece {LONG,SQUARE,L1,L2,S1,S2,T};
enum Direction {LEFT,DOWN,RIGHT};

class windowFunctions;
class grid;
class block;

class windowFunctions {
public:
    bool init(SDL_Window** window, SDL_Surface** surface , const int WIDTH, const int HEIGHT);
    void close(SDL_Window** window);
    void setBackground(SDL_Renderer* renderer, Color color);
};

class grid {
private:
    int* mapColor(Color c);
public:
    Color squares[10][20];
    grid();
    void updateXY(int X, int Y, Color c);
    void updateBlock(block* b, bool deleting);
    void paintBoard(SDL_Renderer* renderer, const int W, const int H);
};

class block {
private:
    pair<int,int>* coords;
    Color color;
    Piece piece;
    Color mapColor(Piece p);
    pair<int,int>* mapStartingCoords(Piece p);
public:
    block(Piece p);
    pair<int,int>* getCoords();
    Color getColor();
    bool move(Direction d, grid* g);
    ~block();
};

#endif /* window_hpp */
