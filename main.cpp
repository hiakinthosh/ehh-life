/*
Trynna to do something like

    *Conway's Game of Life*
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life


    Here's a note to me in future:
    "If you need more than 3 levels of indentation, you’re screwed anyway, and should fix your program."

*/

#include "s.hpp"

int main(int argc, char* args[]) {
    //SDL_Delay(5000); // this may be useful

    SDL_Window* window = NULL;
    //SDL_Surface* surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Init the video driver
        printf("SDL_Error: %s\n", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow("uhhh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 655, 655, SDL_WINDOW_SHOWN);
        if (window == NULL) printf("SDL_Error: %s\n", SDL_GetError());
        else {
            cell rects[ARRAY_D * ARRAY_D];

            // init a glider (ship) shape            int m = 6, n = 7, o = 8;            rects[ARRAY_D*m + m].alive = true; // 66
            rects[ARRAY_D*n + m].alive = true; // 76            rects[ARRAY_D*o + m].alive = true; // 86            rects[ARRAY_D*m + n].alive = true; // 67            rects[ARRAY_D*n + o].alive = true; // 78
            /* testing amount of neighbors */
            //printf("neighbors of [%d, %d] = %d\n", c, d, countNeighbors(rects, c, d));
            // printing to the console the "binary" version of the map
            for (size_t i = 0; i < ARRAY_D; i++) {
                for (size_t j = 0; j < ARRAY_D; j++) {
                    /* printing for debug purposes there's needed exchange 'j' for 'i'*/
                    if (rects[ARRAY_D*j + i].alive) printf("1  ");
                    else printf("0  ");
                }
                printf("\n");
            }

            SDL_Event event;
            SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); //renderer used to color rects
            bool quit = false;
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
                    /* cell enlivening by clicking */
                    else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        rects[ARRAY_D * (x/41) + (y/41)].alive = !rects[ARRAY_D * (x/41) + (y/41)].alive;
                        if (rects[ARRAY_D * (x/41) + (y/41)].alive)
                            printf("mouse: [%3d, %3d] | rect: [%2d, %2d] | neighbors: %d\n", x, y, x/41, y/41, countNeighbors(rects, x/41, y/41));
                        else
                            printf("mouse: [%3d, %3d] | rect: [%2d, %2d]\n", x, y, x/41, y/41);
                    }

                    /* starting the LIFE! */
                    else if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            for (size_t i = 1; i < ARRAY_D - 1; i++) { // suspicious
                                for (size_t j = 0; j < ARRAY_D; j++) {
                                    /* conversion from switch */
                                    if (countNeighbors(rects, i, j) == 3) rects[ARRAY_D*i + j].alive = true;
                                    else if ((countNeighbors(rects, i, j) == 2) && rects[ARRAY_D*i + j].alive == true) continue;
                                    else rects[ARRAY_D*i + j].alive = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
