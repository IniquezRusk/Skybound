#include "bullet.h"

Bullet::Bullet(int startX, int startY, int width, int height, int s, bool playerBullet)
    : x(startX), y(startY), w(width), h(height), speed(s), fromPlayer(playerBullet)
{
    rect = { x, y, w, h };
}

void Bullet::update() {
    if (fromPlayer) x += speed;
    else x -= speed;
    rect.x = x;
    rect.y = y;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, fromPlayer ? 255 : 255, fromPlayer ? 255 : 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Bullet::isOffScreen() {
    return (x + w < 0 || x > SCREEN_WIDTH || y + h < 0 || y > SCREEN_HEIGHT);
}
