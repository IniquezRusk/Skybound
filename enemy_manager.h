#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "enemy.h"
#include "stats.h"
#include "screeneffects.h"
#include "bullet.h"

class EnemyManager
{
    public:
        EnemyManager(
            SDL_Renderer* r,
            SDL_Texture* smallTexture,
            SDL_Texture* mediumTexture,
            SDL_Texture* largeTexture
        );

        void spawnWave(int wave);
        void update(std::vector<Bullet>& enemyBullets);
        void render();
        bool allEnemiesDefeated();
        void checkBulletCollisions(
            std::vector<Bullet>& bullets, 
            stats& playerStats,
            ScreenEffects& effects
        );
        void reset();

    private:
        SDL_Renderer* renderer;

        SDL_Texture* smallTexture;
        SDL_Texture* mediumTexture;
        SDL_Texture* largeTexture;

        std::vector<Enemy> enemies;

        // Formation functions

        void spawnLineFormation();
        void spawnVformation();
        void spawnDiamondFormation();
        void spawnHeavyFormation(int wave);
        void spawnSmallSwarm();
        void spawnMixedFormation();

        // Helper for spawning individual enemies
        void spawnEnemy(
            float x,
            float y,
            EnemyType type
        );
    };