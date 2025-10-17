#include "asteroid.h"
#include "constant.h"
#include <cstdlib>

Asteroid::Asteroid(float startX, float startY, int width, int height, float sX, float sY, SDL_Renderer* r, SDL_Texture* tex)
    : x(startX), y(startY), w(width), h(height), speedX(sX), speedY(sY), renderer(r), texture(tex), health(40), dead(false)
{
    rect = { (int)x, (int)y, w, h };
}

Asteroid::~Asteroid() {}

void Asteroid::update() {
    x -= speedX;
    y += speedY;

    // Bounce slightly off top/bottom for variety
    if (y < 0 || y + h > SCREEN_HEIGHT)
        speedY = -speedY * 0.8f;

    rect.x = (int)x;
    rect.y = (int)y;

    // Mark dead when off-screen
    if (x + w < 0)
        dead = true;
}

void Asteroid::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    } else {
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &rect);
    }
}

bool Asteroid::takeHit(int damage) {
    health -= damage;
    if (health <= 0) {
        dead = true;
        return true;
    }
    return false;
}

bool Asteroid::isDead() { return dead; }