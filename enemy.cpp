#include "enemy.h"
#include "constant.h"
#include <cstdlib>
#include <cmath>

Enemy::Enemy(
    float startX,
    float startY,
    int width,
    int height,
    float sX,
    float sY,
    SDL_Renderer* r,
    SDL_Texture* tex
)
    : x(startX),
      y(startY),
      w(width),
      h(height),
      speedX(sX),
      speedY(sY),
      renderer(r),
      texture(tex),
      health(40),
      dead(false),
      baseY(startY),
      hoverTime(0.0f),
      hoverAmplitude(10.0f),
      hoverSpeed(2.0f),
      shootTimer(0.0f),
      shootCooldown(2.0f),
      hoverPhase(static_cast<float>(rand() % 628) / 100.0f)
{
    rect = {
        static_cast<int>(x),
        static_cast<int>(y),
        w,
        h
    };
}

Enemy::~Enemy() {}

void Enemy::update()
{
    // Smooth vertical hovering
    hoverTime += 0.016f;

    y = baseY +
        sin(hoverTime * hoverSpeed + hoverPhase) * hoverAmplitude;

    // Shooting cooldown
    if (shootTimer > 0.0f)
    {
        shootTimer -= 0.016f;

        // Prevent the timer from going negative
        if (shootTimer < 0.0f)
        {
            shootTimer = 0.0f;
        }
    }

    // Update collision/render rectangle
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
}

void Enemy::render(SDL_Renderer* renderer)
{
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool Enemy::takeHit(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        dead = true;
        return true;
    }

    return false;
}

bool Enemy::canShoot()
{
    return shootTimer <= 0.0f;
}

void Enemy::shoot(std::vector<Bullet>& bullets)
{
    bullets.emplace_back(
        x,
        y + h / 2,
        12,     // width
        6,      // height
        7,      // speed
        false   // enemy bullet
    );

    shootTimer = shootCooldown;
}

bool Enemy::isDead()
{
    return dead;
}