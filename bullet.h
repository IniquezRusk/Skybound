#ifndef BULLET_H
#define BULLET_H
#include <SDL2/SDL.h>
#include "constant.h"

class Bullet {
public:
    int x, y, w, h, speed;
    bool fromPlayer;
    SDL_Rect rect;

    Bullet(int startX, int startY, int width, int height, int s, bool playerBullet);
    void update();
    void render(SDL_Renderer* renderer);
    bool isOffScreen();
};
#endif
