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

// to delete
const unsigned short ARRAY_D = 16;


unsigned short countNeighbours(cell rects[], const int x, const int y) { // , cell &rects[][16]
    unsigned short amount = 0;
    //printf("start\n");

    for (short i = -1; i < 2; i++) {
        for (short j = -1; j < 2; j++) {
            if (!(i == 0 && j == 0)) {
                //printf("pos: [%d, %d]\n", x - i, y - j);

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

            cell rects[ARRAY_D * ARRAY_D]; // hardcoded; to change



                int c = 4, d = 5;
                int e = 3, f = 6;
                int g = 3, h = 5;
                rects[ARRAY_D*c + d].alive = true;
                rects[ARRAY_D*e + f].alive = true;
                rects[ARRAY_D*g + h].alive = true;

                printf("neighbours of [%d, %d] = %d\n", c, d, countNeighbours(rects, c, d));



            while (!quit) {
                SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255); // blue
                SDL_RenderClear(renderer); // fill with color whole window

                //SDL_SetRenderDrawColor(renderer, 255, 102, 0, 255); // orange
                for (int i = 0; i < ARRAY_D; i++) {
                    for (int j = 0; j < ARRAY_D; j++) {

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



                // dont know if i could comment the line below,
                // because no events means no coloring but lets try it out

                // highlighting the hovered rect
                int k, l;
                SDL_GetMouseState(&k, &l);
                SDL_SetRenderDrawColor(renderer, 255, 122, 40, 255); // mild orange (?)
                SDL_RenderFillRect(renderer, &rects[ARRAY_D * (k/41) + (l/41)].core);


                SDL_RenderPresent(renderer); // applying everything to the display

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                    else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        printf("mouse position: [%d, %d] | rect coord: [%d, %d]\n", x, y, x/41, y/41);
                        rects[ARRAY_D * (x/41) + (y/41)].alive = !rects[ARRAY_D * (x/41) + (y/41)].alive; // !rects[x/40][y/40].status
                    }

                    /* useless controlling using arrows
                    else if (event.type == SDL_KEYDOWN) {
                        switch(event.key.keysym.sym) {
                            case SDLK_ESCAPE: quit = true; break;
                            case SDLK_UP:    d--; break;
                            case SDLK_DOWN:  d++; break;
                            case SDLK_RIGHT: c++; break;
                            case SDLK_LEFT:  c--; break;
                            //default: break;
                        }
                    //printf("position: [%d, %d]\n", c, d);
                    }
                    */
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// httmp <3
