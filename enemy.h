#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <vector>
#include "constant.h"
#include "bullet.h"

class Enemy
{
private:
    int health;

    float baseY;
    float hoverTime;
    float hoverAmplitude;
    float hoverSpeed;
    float hoverPhase;

    float shootTimer;
    float shootCooldown;

public:
    float x, y;
    int w, h;

    float speedX;
    float speedY;

    bool dead;

    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    Enemy(
        float startX,
        float startY,
        int width,
        int height,
        float sX,
        float sY,
        SDL_Renderer* r,
        SDL_Texture* tex
    );

    ~Enemy();

    void update();
    void render(SDL_Renderer* renderer);

    bool takeHit(int damage);
    bool isDead();

    bool canShoot();
    void shoot(std::vector<Bullet>& bullets);
};

#endif