/*
Trynna to do something like

    *Conway's Game of Life*
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life


*/

#include <SDL2/SDL.h>
#include <stdio.h>

// to delete
const size_t ARRAY_D = 16;


class cell {
public:
    SDL_Rect core;
    //cell()
    //SDL_Rect createRect(int xs, int ys, int width, int height);
    bool alive = false;
};

SDL_Rect createRect(const int xs, const int ys, const int width, const int height) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = width;
    rectangular.h = height;
    return rectangular;
}


unsigned short countNeighbors(cell rects[], const int x, const int y) { // , cell &rects[][16]
    unsigned short amount = 0;
    //printf("start\n");

    for (short i = -1; i < 2; i++) {
        for (short j = -1; j < 2; j++) {
            if (!(i == 0 && j == 0)) {
                if (rects[ARRAY_D*(x+i) + (y+j)].alive) amount++;
            }
        }
    }
    //printf("stop\n");
    return amount;
}


int main(int argc, char* args[]) {
    //SDL_Delay(5000); // this may be useful

    SDL_Window* window = NULL;
    //SDL_Surface* surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Init the video driver
        printf("SDL_Error: %s\n", SDL_GetError());
    }

    else {
        window = SDL_CreateWindow("uhhh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 656, 656, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("SDL_Error: %s\n", SDL_GetError());
        }
        else {
            bool quit = false;

            SDL_Event event;
            SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); //renderer used to color rects

            cell rects[ARRAY_D * ARRAY_D];


            /* testing amount of neighbors */
            int c = 4, d = 5;
            int e = 3, f = 6;
            int g = 3, h = 5;
            rects[ARRAY_D*c + d].alive = true;
            rects[ARRAY_D*e + f].alive = true;
            rects[ARRAY_D*g + h].alive = true;
            printf("neighbors of [%d, %d] = %d\n", c, d, countNeighbors(rects, c, d));


            /* main loop */
            while (!quit) {
                SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255); // blue
                SDL_RenderClear(renderer); // fill with color whole window

                // wrong place for:
                //SDL_SetRenderDrawColor(renderer, 255, 102, 0, 255); // orange
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


                /* hovered rectangular highlighting */
                int k, l;
                SDL_GetMouseState(&k, &l);

                if (rects[ARRAY_D * (k/41) + (l/41)].alive)
                    SDL_SetRenderDrawColor(renderer, 63, 128, 193, 255); // brighter blue
                else //if (!rects[ARRAY_D * (k/41) + (l/41)].alive)
                    SDL_SetRenderDrawColor(renderer, 255, 122, 40, 255); // brighter orange

                SDL_RenderFillRect(renderer, &rects[ARRAY_D * (k/41) + (l/41)].core);
                SDL_RenderPresent(renderer); // applying everything to the display


                /* event handling */
                while (SDL_PollEvent(&event)) {
                    //if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) quit = true; // SDLK_ESCAPE bugged?
                    if (event.type == SDL_QUIT) quit = true;

                    /* cell enlivening */
                    else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        // informing
                        printf("mouse position: [%3d, %3d] | rect coord: [%2d, %2d] | neighbors: %d\n", x, y, x/41, y/41, countNeighbors(rects, x/41, y/41));
                        rects[ARRAY_D * (x/41) + (y/41)].alive = !rects[ARRAY_D * (x/41) + (y/41)].alive;
                        // unsigned short t =
                    }

                    /* starting the LIFE! */
                    else if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_SPACE) {// to delete probably
                            for (size_t i = 0; i < ARRAY_D; i++) {
                                for (size_t j = 0; j < ARRAY_D; j++) {
                                    switch(countNeighbors(rects, i, j)) {
                                        case 1:
                                        case 2: rects[ARRAY_D*i + j].alive = false; break;
                                        case 3: rects[ARRAY_D*i + j].alive = true; break;
                                        /*
                                        case 4:
                                        case 5:
                                        case 6:
                                        case 7:
                                        case 8: rects[ARRAY_D*i + j].alive = false; break;
                                        */
                                        default: rects[ARRAY_D*i + j].alive = false; break;

                                        /*
                                        okay, now i know where the issue is;
                                        when i initiated the one dimension array, there are
                                        neighbors even on the other sides of window due to
                                        the facts that this array is like a train:

                                        0 0 0 1
                                        1 0 0 0

                                        1 from the first row and 1 from the second are neighbor
                                        to each other, so we have supplied enough neighbor amount
                                        to enliven the cell

                                        one of the solution could be limitation of the columns
                                        to prevent the cells' side-by-side counting
                                        [don't know howdy yet]

                                        another solution could be just deliver array as
                                        a two-dimensional instead of one
                                        it would be prevent problem showed above
                                        but it calls to life other two or more problems
                                        : passing two-dimensional array of objects to function
                                        : slowing down the app
                                        : issue of extension the map (in game of life there is assumption
                                                                      the map is unlimited and like a sandbox)

                                        don't know what to do...
                                        */


                                    } /* END OF switch */
                                    //if (countNeighbors(rects, i, j) == 2 || countNeighbors(rects, i, j) == 3)
                                      //  rects[ARRAY_D*i + j].alive = true;
                                } /* END OF inside for loop */
                            } /* END OF outside for loop */
                        } /* END OF space pressed condition */
                    } /* END OF key pressed down */
                } /* END OF event loop */
            } /* END OF main loop (while) */
        } /* END OF else condition depends on existence of window */
    } /* END OF condition that everything is initiated properly */

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
