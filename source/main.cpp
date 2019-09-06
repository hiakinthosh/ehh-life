/*
Trynna to do something like

    *Conway's Game of Life*
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/

#include "s.hpp"

int main(int argc, char *args[]) {

    SDL_Window *window = nullptr;
    //SDL_Surface* surface = nullptr; // will be used for generating bottom bar of input

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Init the video driver
        printf("SDL_Error: %s\n", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow("uhhh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 655, 655, SDL_WINDOW_SHOWN);
        if (window == NULL)
            printf("SDL_Error: %s\n", SDL_GetError());
        else {
            std::vector<Cell> rects(ARRAY_D * ARRAY_D);

            // init a glider (ship) shape
            int m = 10, n = 11, o = 12;
            rects.at(ARRAY_D*m + m).alive = true; // 66
            rects.at(ARRAY_D*n + m).alive = true; // 66
            rects.at(ARRAY_D*o + m).alive = true; // 66
            rects.at(ARRAY_D*m + n).alive = true; // 66
            rects.at(ARRAY_D*n + o).alive = true; // 66

            SDL_Event event;
            SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); //renderer used to color rects
            std::vector<Cell> tmpy(rects.size());
            bool quit = false;
            /* main loop */
            while (!quit) {
                SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255); // blue
                SDL_RenderClear(renderer); // fill with color whole window

                displayBoard(rects, renderer);
                highlightCell(rects, renderer);

                /* event handling */
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) { // 256
                        printf("event type: quit (%d)\n", SDL_QUIT);
                        quit = true;
                    }
                    else if (event.type == SDL_MOUSEBUTTONDOWN) { // 1025
                        printf("event type: mouse_button_down (%d)\n", SDL_MOUSEBUTTONDOWN);
                        clickingCell(rects, renderer);
                    }
                    else if (event.type == SDL_KEYDOWN) { // 768
		      printf("event type: keydown (%d)\n", SDL_KEYDOWN);
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            clearing(tmpy);
                            enlivening(rects, tmpy);
                        }
                        rects = tmpy;
                    }
                }
            }
            SDL_DestroyRenderer(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
