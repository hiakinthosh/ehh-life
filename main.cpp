/*

Trynna to do something like

    *Conway's Game of Life*
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life


*/

#include <SDL2/SDL.h>
#include <stdio.h>


class cell {
public:
    SDL_Rect core;
    //SDL_Rect createRect(int xs, int ys, int width, int height);
    bool status = false;
};

/*
SDL_Rect cell::createRect(int xs, int ys, int width, int height) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = width;
    rectangular.h = height;
    return rectangular;
}
*/

SDL_Rect createRect(int xs, int ys, int width, int height) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = width;
    rectangular.h = height;
    return rectangular;
}


int main(int argc, char* args[]) {
    //SDL_Delay(5000); // this may be useful

    SDL_Window* window = NULL;
    //SDL_Surface* surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Init the video driver
        printf("SDL_Error: %s\n", SDL_GetError());
    }

    else {
        window = SDL_CreateWindow("uhhh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 676, 676, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("SDL_Error: %s\n", SDL_GetError());
        }
        else {
            bool quit = false;

            SDL_Event event;

            SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); //renderer used to color rects

            int a = 16;
            int b = 16;

            cell rects[a][b];

            int c = 10;
            int d = 8;

            /*
            cell testin;
            testin.core.h = 200;
            testin.core.w = 200;
            testin.core.x = 200;
            testin.core.y = 200;
            testin.status = true;
            */

            while (!quit) {
                SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
                SDL_RenderClear(renderer); // fill with color whole window

                SDL_SetRenderDrawColor(renderer, 255, 102, 0, 255);
                for (int i = 0; i < a; i++) { // 14; i++
                    for (int j = 0; j < b; j++) { // 12; j++
                        rects[i][j].core = createRect(10 + i*41, 10 + j*41, 40, 40); // (20 + i*42, 20 + j*42, 40, 40)
                        SDL_RenderFillRect(renderer, &rects[i][j].core);
                    }
                }

                // drawing that lonely rect
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                //SDL_RenderFillRect(renderer, &rects[c][d]);
                SDL_RenderFillRect(renderer, &rects[c][d].core);

                SDL_RenderPresent(renderer); // apply to the display

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quit = true;
                    else if(event.type == SDL_KEYDOWN) {
                        switch(event.key.keysym.sym) {
                            case SDLK_UP:    d--; break;
                            case SDLK_DOWN:  d++; break;
                            case SDLK_RIGHT: c++; break;
                            case SDLK_LEFT:  c--; break;
                            //default: break;
                        }
                    printf("position: [%d, %d]\n", c, d);
                    }
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
