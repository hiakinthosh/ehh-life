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
                    //printf("neighbor at: [%d, %d]\n", x+i, y+j); // turned of because of too much informations
                    amount++;
                }
            }
        }
    }
    return amount;
}


void displayBoard(SDL_Renderer *renderer, cell rects[]) {
    for (size_t i = 0; i < ARRAY_D; i++) {
        for (size_t j = 0; j < ARRAY_D; j++) {
            SDL_SetRenderDrawColor(renderer, 255, 102, 0, 255); // orange
            rects[ARRAY_D*i + j].core = createRect(i*41, j*41, 40, 40); // 656 x 656
            SDL_RenderFillRect(renderer, &rects[ARRAY_D*i + j].core);

            // neighbours counting *here*
            if (rects[ARRAY_D*i + j].alive) {
                SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255); // blue
                SDL_RenderFillRect(renderer, &rects[ARRAY_D*i + j].core);
            }
        }
    }
}

void highlightCell(SDL_Renderer *renderer, cell rects[]) {
     /* hovered rectangular highlighting */
    int k, l;
    SDL_GetMouseState(&k, &l);
    if (rects[ARRAY_D * (k/41) + (l/41)].alive)
        SDL_SetRenderDrawColor(renderer, 63, 128, 193, 255); // brighter blue
    else //if (!rects[ARRAY_D * (k/41) + (l/41)].alive)
        SDL_SetRenderDrawColor(renderer, 255, 122, 40, 255); // brighter orange
    SDL_RenderFillRect(renderer, &rects[ARRAY_D * (k/41) + (l/41)].core);
    SDL_RenderPresent(renderer); // applying everything to the display
}

void enliveningCell(SDL_Renderer *renderer, cell rects[]) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    rects[ARRAY_D * (x/41) + (y/41)].alive = !rects[ARRAY_D * (x/41) + (y/41)].alive;
    printf("mouse: [%3d, %3d] | rect: [%2d, %2d] | neighbors: %d | status: %s\n",
        x, y,
        x/41, y/41,
        countNeighbors(rects, x/41, y/41),
        (rects[ARRAY_D * (x/41) + (y/41)].alive ? "alive" : "dead"));
}
