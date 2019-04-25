#ifndef s_hpp
#define s_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
//#include <algorithm>
#include <vector>

#define ARRAY_D 16

class Cell {
public:
    SDL_Rect core;
    bool alive = false;
};


SDL_Rect createRect(const int xs, const int ys, const int width, const int height);
unsigned short countNeighbors(std::vector<Cell> &rects, const int x, const int y);
void displayBoard(std::vector<Cell> &rects, SDL_Renderer *renderer);
void highlightCell(std::vector<Cell> &rects, SDL_Renderer *renderer);
void clickingCell(std::vector<Cell> &rects, SDL_Renderer *renderer);
std::vector<Cell> clearing(std::vector<Cell> &vec);
void binaryDisplay(std::vector<Cell> &rects);

#endif
