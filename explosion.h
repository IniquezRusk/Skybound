#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL2/SDL.h>
#include <vector>

struct ExplosionParticle
{
    float x;
    float y;

    float velocityX;
    float velocityY;

    float size;
    float life;
    float maxLife;
};

class Explosion
{
private:
    float x;
    float y;

    float timer;
    float duration;

    std::vector<ExplosionParticle> particles;

public:
    Explosion(float startX, float startY, int size);

    void update();
    void render(SDL_Renderer* renderer);

    bool isFinished() const;
};

#endif