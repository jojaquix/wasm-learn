#include "hello.hpp"
#include <cstdio>
#include <optional>
#include <vector>
#include <algorithm>
#include <ranges>

#include <SDL.h>
#include <emscripten.h>


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

void main_loop() 
{
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

int app_main(int argc, char* argv[]) 
{
    
    std::printf("Hello, World of Wasm with C++ !\n");    

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


class Object 
{

public:
    //object api
    virtual void doSomething() 
    {
        //implementation
        std::printf("Doing object something!\n");
    }

protected:

    Object() = default;
    Object(const Object&) = default;
    Object & operator=(const Object&) = default;

    Object(Object&&) = default;
    Object & operator=(Object&&) = default;

    virtual ~Object() = default;
};


class Derived : public Object
{   
    using Object::Object; //inherit constructors

public:
    void doSomething() override
    {
        //call base class implementation
        Object::doSomething();
        //additional implementation
        std::printf("Doing derived something! %s\n", "nice");
    }
};


namespace stdv = std::views;

int main(int argc, char* argv[]) 
{
    int status = 0;
    Derived obj;
    obj.doSomething();

    std::vector <int> numbers = {1, 2, 3, 4, 5, 6};
    auto it = std::ranges::find_if(numbers, [](int n) { return n % 2 == 0; });
    auto it2 = std::find_if(numbers.cbegin(), numbers.cend(), [](int n) { return n % 2 == 0; });

    auto dataView = numbers 
                  | std::views::filter([](int n) { return n % 2 == 0; })
                  | std::views::transform([](int n) { return n * n; })
                  | std::views::take(2);

    for (int n : dataView) 
    {
        std::printf("Number: %d\n", n);     
    }

    status = app_main(argc, argv);
    
    return status;
}






