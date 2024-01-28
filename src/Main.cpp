
#include <iostream>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "Global.cpp"
#include "scenes/TestScene.cpp"
#include "prettyprint.hpp"

using std::string;



int main () {
    int result, flags;

    std::cout << "Initializing SDL..." << std::endl;
    result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result != 0) {
        std::cout << "ERROR (" << result << "): Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    atexit(SDL_Quit);

    std::cout << "Initializing SDL_image..." << std::endl;
    flags = IMG_INIT_PNG;
    result = IMG_Init(flags);
    if (result != IMG_INIT_PNG) {
        string msg = "ERROR: Failed to initialize SDL_image: ";
        msg += IMG_GetError() + '\n';
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Space13: Error", msg.c_str(), NULL);
        return -4;
    }
    atexit(IMG_Quit);

    std::cout << "Creating window..." << std::endl;
    flags = 0;
    window = SDL_CreateWindow("Space 13", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, flags);
    if (window == NULL) {
        string msg = "ERROR: Failed to create window: ";
        msg += SDL_GetError() + '\n';        
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Space13: Error", msg.c_str(), NULL);
        return -2;
    }
    atexit([]{SDL_DestroyWindow(window);});

    std::cout << "Creating renderer..." << std::endl;
    flags = SDL_RENDERER_ACCELERATED;
    screen = SDL_CreateRenderer(window, -1, flags);
    if (screen == NULL) {
        string msg = "ERROR: Failed to create renderer: ";
        msg += SDL_GetError() + '\n';
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Space13: Error", msg.c_str(), window);
        return -3;
    }
    atexit([]{SDL_DestroyRenderer(screen);});

    TestScene s = TestScene();
    s.play();

    SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
