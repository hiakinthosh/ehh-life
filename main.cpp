/*
Trynna to do something like

    *Conway's Game of Life*
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/

#include "s.hpp"

int main(int argc, char *args[]) {

    SDL_Window *window = NULL;
    //SDL_Surface* surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Init the video driver
        printf("SDL_Error: %s\n", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow("uhhh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 655, 655, SDL_WINDOW_SHOWN);
        if (window == NULL)
            printf("SDL_Error: %s\n", SDL_GetError());
        else {
            std::vector<Cell> rects(ARRAY_D * ARRAY_D);

            // init a glider (ship) shape            int m = 10, n = 11, o = 12;            rects[ARRAY_D*m + m].alive = true; // 66
            rects[ARRAY_D*n + m].alive = true; // 76            rects[ARRAY_D*o + m].alive = true; // 86            rects[ARRAY_D*m + n].alive = true; // 67            rects[ARRAY_D*n + o].alive = true; // 78
            // printing to the console the "binary" version of the map
            //binaryDisplay(rects);

            SDL_Event event;
            SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); //renderer used to color rects
            std::vector<Cell> tmpy(rects.size());
            bool quit = false;
            /* main loop */
            while (!quit) {
                SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255); // blue
                SDL_RenderClear(renderer); // fill with color whole window

                // 1 2 3 4 5 6 7 8 9 10

                displayBoard(rects, renderer);
                highlightCell(rects, renderer);

                /* event handling */
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        clickingCell(rects, renderer);                    }

                    /* starting the LIFE! */
                    else if (event.type == SDL_KEYDOWN) {                        if (event.key.keysym.sym == SDLK_SPACE) {
                            clearing(tmpy);
                            for (size_t i = 1; i < ARRAY_D - 1; i++) { // suspicious, TOFIX
                            //for (size_t i = 0; i < ARRAY_D; i++) { // suspicious, TOFIX
                                for (size_t j = 0; j < ARRAY_D; j++) {
                                    switch (countNeighbors(rects, i, j)) {
                                        case 2: if (rects[ARRAY_D*i + j].alive == true) {
                                                    //printf("[%d, %d] on CASE 2\n", i, j);
                                                    tmpy[ARRAY_D*i + j].alive = true;
                                                }
                                                break;
                                        case 3: tmpy[ARRAY_D*i + j].alive = true;
                                                break;
                                        default: tmpy[ARRAY_D*i + j].alive = false;
                                                 break;
                                    }
                                }
                            }
                        }
                        rects = tmpy;
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
