#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL2/SDL.h>
#include "constant.h"

class Asteroid {
private:
    int health;

public:
   float x,y;
   int w, h;
   float speedX, speedY;
   bool dead;
   SDL_Rect rect;
   SDL_Renderer* renderer;
   SDL_Texture* texture;

    // MATCHES enemy.cpp:
    Asteroid(float startX, float startY, int width, int height, float sX, float sY, SDL_Renderer* r, SDL_Texture* texture);
    ~Asteroid();

    void update();
    void render(SDL_Renderer* renderer);
    bool takeHit(int damage);
    bool isDead();
};

#endif
