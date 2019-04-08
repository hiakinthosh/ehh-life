#include "s.hpp"

SDL_Rect createRect(const int xs, const int ys, const int width, const int height) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = width;
    rectangular.h = height;
    return rectangular;
}


unsigned short countNeighbors(cell rects[], const int x, const int y) {
    unsigned short amount = 0;

    for (short i = -1; i < 2; i++) {
        for (short j = -1; j < 2; j++) {
            //if (i =! 0 && j != 0 && x+i >= 0 && x+i <= 16 && y+j >= 0 && y+j <= 16) {
            if (!(i == 0 && j == 0)) {
                //if (rects[ARRAY_D*(x+i) + (y+j)].alive && ((x+i) > -1) && (y+j) > -1) {
                if (rects[ARRAY_D*(x+i) + (y+j)].alive == true) {
                    printf("neighbor at: [%d, %d]\n", x+i, y+j);
                    amount++;
                }
            }
        }
    }
    return amount;
}

