#include "explosion.h"
#include <cstdlib>
#include <cmath>

Explosion::Explosion(float startX, float startY, int size)
    : x(startX),
      y(startY),
      timer(0.0f),
      duration(0.5f)
{
    int particleCount = size / 3;

    if (particleCount < 12)
        particleCount = 12;

    if (particleCount > 35)
        particleCount = 35;

    for (int i = 0; i < particleCount; i++)
    {
        float angle =
            static_cast<float>(rand() % 628) / 100.0f;

        float speed =
            1.5f + static_cast<float>(rand() % 350) / 100.0f;

        ExplosionParticle particle;

        particle.x = x;
        particle.y = y;

        particle.velocityX = cos(angle) * speed;
        particle.velocityY = sin(angle) * speed;

        particle.size =
            3.0f + static_cast<float>(rand() % 5);

        particle.maxLife =
            0.25f + static_cast<float>(rand() % 25) / 100.0f;

        particle.life = particle.maxLife;

        particles.push_back(particle);
    }
}

void Explosion::update()
{
    timer += 0.016f;

    for (auto& particle : particles)
    {
        particle.x += particle.velocityX;
        particle.y += particle.velocityY;

        particle.velocityX *= 0.97f;
        particle.velocityY *= 0.97f;

        particle.life -= 0.016f;

        particle.size *= 0.96f;
    }
}

void Explosion::render(SDL_Renderer* renderer)
{
    for (auto& particle : particles)
    {
        if (particle.life <= 0.0f)
            continue;

        float lifePercent =
            particle.life / particle.maxLife;

        Uint8 alpha =
            static_cast<Uint8>(255 * lifePercent);

        SDL_SetRenderDrawBlendMode(
            renderer,
            SDL_BLENDMODE_BLEND
        );

        SDL_SetRenderDrawColor(
            renderer,
            255,
            140,
            30,
            alpha
        );

        SDL_Rect rect;

        rect.x = static_cast<int>(
            particle.x - particle.size / 2
        );

        rect.y = static_cast<int>(
            particle.y - particle.size / 2
        );

        rect.w = static_cast<int>(particle.size);
        rect.h = static_cast<int>(particle.size);

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255
    );
}

bool Explosion::isFinished() const
{
    if (timer >= duration)
        return true;

    for (auto& particle : particles)
    {
        if (particle.life > 0.0f)
            return false;
    }

    return true;
}