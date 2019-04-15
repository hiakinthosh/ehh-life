#ifndef s_hpp
#define s_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

#define ARRAY_D 16

class cell {
public:
    SDL_Rect core;
    //cell() // I don't know how to use constructors and destructors :(  yet...
    //SDL_Rect createRect(int xs, int ys, int width, int height);
    bool alive = false;
};

SDL_Rect createRect(const int xs, const int ys, const int width, const int height);
unsigned short countNeighbors(cell rects[], const int x, const int y);
void displayBoard(SDL_Renderer *renderer, cell rects[]);
void highlightCell(SDL_Renderer *renderer, cell rects[]);
void enliveningCell(SDL_Renderer *renderer, cell rects[]);

#endif
