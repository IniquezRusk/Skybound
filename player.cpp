#include "player.h"
#include <iostream>
#include <SDL2/SDL_image.h>

Plane::Plane(int startX, int startY, int width, int height, int s, SDL_Renderer* r)
    : x(startX), y(startY), w(width), h(height), speed(s), renderer(r), renderScale(2.5f)
{
    rect = {x, y, w, h};
    texture = nullptr;

    // Load from assets folder
    SDL_Surface* surface = IMG_Load("assets/ship.png");
    if (!surface) {
        std::cout << "Failed to load plane sprite: " << IMG_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Plane texture loaded successfully!\n";
    }
}

void Plane::update(const Uint8* keystates) {
    if (keystates[SDL_SCANCODE_W] && y - speed >= 0)
        y -= speed;

    if (keystates[SDL_SCANCODE_S] && y + h + speed <= SCREEN_HEIGHT)
        y += speed;

    if (keystates[SDL_SCANCODE_A] && x - speed >= 0)
        x -= speed;

    if (keystates[SDL_SCANCODE_D] && x + w + speed <= SCREEN_WIDTH)
        x += speed;

    rect.x = x;
    rect.y = y;
}

void Plane::render(SDL_Renderer* renderer) {
    if (texture) {
        // Scale up slightly (20% larger than hitbox)
        float scale = 1.4f;
        SDL_Rect renderRect = {
            static_cast<int>(x - (w * (scale - 1) / 2)),  // center horizontally
            static_cast<int>(y - (h * (scale - 1) / 2)),  // center vertically
            static_cast<int>(w * scale),
            static_cast<int>(h * scale)
        };
        SDL_RenderCopy(renderer, texture, nullptr, &renderRect);
    } else {
        SDL_RenderFillRect(renderer, &rect);
    }
}




Plane::~Plane() {
    if (texture)
        SDL_DestroyTexture(texture);
}

