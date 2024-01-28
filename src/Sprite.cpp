
#include "Drawable.hpp"
#include "Global.cpp"
#include <SDL_render.h>
#pragma once

struct Sprite : Drawable
{
private:
    SDL_Texture* tex;
public:
    SDL_FRect pos;
    double angle;

    Sprite() = delete;

    Sprite (char C) {
        
        // tex = SDL_CreateTextureFromSurface(screen, surf);
    }


    virtual void draw() const {
        SDL_RenderCopyExF(screen, tex, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
    }
};
