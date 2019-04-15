/*
Trynna to do something like

    *Conway's Game of Life*
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/

#include "s.hpp"

int main(int argc, char* args[]) {

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

            // printing to the console the "binary" version of the map
            for (size_t i = 0; i < ARRAY_D; i++) {
                for (size_t j = 0; j < ARRAY_D; j++) {
                    /* print for debug purposes there's needed exchange 'j' for 'i'*/
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

                displayBoard(renderer, rects);
                highlightCell(renderer, rects);

                /* event handling */
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quit = true;
                    else if (event.type == SDL_MOUSEBUTTONDOWN) enliveningCell(renderer, rects);
                    /* starting the LIFE! */
                    else if (event.type == SDL_KEYDOWN) {                        if (event.key.keysym.sym == SDLK_SPACE) {                            for (size_t i = 1; i < ARRAY_D - 1; i++) { // suspicious
                                for (size_t j = 0; j < ARRAY_D; j++) {                                    if (countNeighbors(rects, i, j) == 2) rects[ARRAY_D*i + j].alive = true;                                    //else if ((countNeighbors(rects, i, j) == 2) && rects[ARRAY_D*i + j].alive == true) continue;
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
//SDL_Delay(5000); // this may be useful
