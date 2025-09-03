#include <cstdio>
#include <optional>

#include <SDL.h>
#include <emscripten.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            emscripten_cancel_main_loop(); // Exit the loop on quit event
        }
        else if (event.type == SDL_KEYDOWN) {
            // Handle arrow key presses
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    std::printf("Arrow key pressed: UP\n");
                    break;
                case SDLK_DOWN:
                    std::printf("Arrow key pressed: DOWN\n");
                    break;
                case SDLK_LEFT:
                    std::printf("Arrow key pressed: LEFT\n");
                    break;
                case SDLK_RIGHT:
                    std::printf("Arrow key pressed: RIGHT\n");
                    break;
                default:
                    // Ignore other keys to save memory
                    break;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_Rect rect = {50, 50, 100, 100}; // A red square
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);    
}

int main(int argc, char* argv[]) {
    
    std::printf("Hello, World of Wasm!\n");    

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Emscripten SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    emscripten_set_main_loop(main_loop, 0, 1); // Call main_loop at browser's frame rate

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::printf("Bye Wasm!\n");

    return 0;
}





