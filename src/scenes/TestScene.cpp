
#include "../Scene.cpp"
#include <iostream>

struct Square : Drawable {
    int x,y,w,h, r,g,b;

    Square() = default;

    Square (int x, int y, int w, int h, int r, int g, int b) :
        x{x}, y{y}, w{w}, h{h}, r{r}, g{g}, b{b}
    {}

    virtual void draw () const override {
        SDL_Rect rect {x,y,w,h};
        SDL_SetRenderDrawColor(screen,r,g,b,SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(screen, &rect);
    }
};

struct TestScene : Scene {

    void begin() {
        std::cout << "Starting scene..." << std::endl;
        bindEvent(SDL_QUIT, [&](SDL_Event) {
            std::cout << "Quitting!" << std::endl;
            stop();
        });
        bindEvent(SDL_KEYDOWN, [&](SDL_Event e) {
            std::cout << "Key pressed: (" << e.key.keysym.sym << ")" << std::endl;
        });
        static Square
            sA (5,5,50,50,   255,0,0),
            sB (45,45,75,75, 1,254,1),
            sC (30,30,60,60, 0,0,255),
            sD (90,10,90,90, 255,255,0)
        ;
        addDrawable(1, sA);
        addDrawable(1, sB);
        addDrawable(1.5, sC);
        addDrawable(2, sD);

        bindEvent(SDL_KEYDOWN, [&](SDL_Event e) {
            if (e.key.keysym.sym == SDLK_UP) sB.y--;
        });
        bindEvent(SDL_KEYDOWN, [&](SDL_Event e) {
            if (e.key.keysym.sym == SDLK_DOWN) sB.y++;
        });
        bindEvent(SDL_KEYDOWN, [&](SDL_Event e) {
            if (e.key.keysym.sym == SDLK_LEFT) sB.x--;
        });
        bindEvent(SDL_KEYDOWN, [&](SDL_Event e) {
            if (e.key.keysym.sym == SDLK_RIGHT) sB.x++;
        });
        
    }
    
    void end() {
        std::cout << "Scene over." << std::endl;
    }

    void doStuff() {

    }
};
