#include "enemy_manager.h"
#include "constant.h"
#include "utils.h"
#include "screeneffects.h"
#include "stats.h"
#include "enemy.h"

#include <cstdlib>

EnemyManager::EnemyManager(
    SDL_Renderer* r,
    SDL_Texture* smallTexture,
    SDL_Texture* mediumTexture,
    SDL_Texture* largeTexture
)
    : renderer(r),
      smallTexture(smallTexture),
      mediumTexture(mediumTexture),
      largeTexture(largeTexture)
{
}

void EnemyManager::spawnWave(int wave)
{
    // Enemies spawn every 3rd wave
    if (wave % 3 != 0)
        return;

    // Picks a random formation
    int formation = rand() % 4;

    switch (formation)
    {
        case 0:
            spawnLineFormation();
            break;

        case 1:
            spawnVformation();
            break;

        case 2:
            spawnDiamondFormation();
            break;

        case 3:
            spawnHeavyFormation(wave);
            break;
    }
}

void EnemyManager::spawnLineFormation()
{
    for (int i = 0; i < 4; i++)
    {
        spawnEnemy(
            SCREEN_WIDTH - 500 + i * 100,
            150 + i * 60,
            EnemyType::SMALL
        );
    }
}

void EnemyManager::spawnVformation()
{
    spawnEnemy(SCREEN_WIDTH - 500, 100, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 400, 150, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 300, 200, EnemyType::MEDIUM);
    spawnEnemy(SCREEN_WIDTH - 200, 150, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 100, 100, EnemyType::SMALL);
}

void EnemyManager::spawnDiamondFormation()
{
    spawnEnemy(SCREEN_WIDTH - 300, 100, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 400, 200, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 200, 200, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 300, 300, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 300, 200, EnemyType::MEDIUM);
}

void EnemyManager::spawnHeavyFormation(int wave)
{
    spawnEnemy(SCREEN_WIDTH - 400, 100, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 300, 150, EnemyType::SMALL);
    spawnEnemy(SCREEN_WIDTH - 200, 100, EnemyType::SMALL);

    spawnEnemy(SCREEN_WIDTH - 350, 250, EnemyType::MEDIUM);
    spawnEnemy(SCREEN_WIDTH - 150, 250, EnemyType::MEDIUM);

    spawnEnemy(SCREEN_WIDTH - 250, 175, EnemyType::LARGE);
}

void EnemyManager::spawnEnemy(float x, float y, EnemyType type)
{
    switch (type)
    {
        case EnemyType::SMALL:
            enemies.emplace_back(
                x, y,
                80, 80,
                0, 0,
                renderer,
                smallTexture,
                EnemyType::SMALL
            );
            break;

        case EnemyType::MEDIUM:
            enemies.emplace_back(
                x, y,
                100, 100,
                0, 0,
                renderer,
                mediumTexture,
                EnemyType::MEDIUM
            );
            break;

        case EnemyType::LARGE:
            enemies.emplace_back(
                x, y,
                120, 120,
                0, 0,
                renderer,
                largeTexture,
                EnemyType::LARGE
            );
            break;
    }
}

void EnemyManager::update(std::vector<Bullet>& enemyBullets)
{
    for (auto& enemy : enemies)
    {
        if (!enemy.isDead())
        {
            enemy.update();

            if (enemy.canShoot())
            {
                enemy.shoot(enemyBullets);
            }
        }
    }
}

void EnemyManager::render()
{
    for (auto& enemy : enemies)
    {
        if (!enemy.isDead())
        {
            enemy.render(renderer);
        }
    }
}

bool EnemyManager::allEnemiesDefeated()
{
    for (auto& enemy : enemies)
    {
        if (!enemy.isDead())
        {
            return false;
        }
    }
    return true;
}

void EnemyManager::checkBulletCollisions(std::vector<Bullet>& bullets, stats& playerStats, ScreenEffects& effects)
{
    for (size_t i = 0; i < bullets.size();)
    {
        bool bulletRemoved = false;

        for (auto& enemy : enemies)
        {
            if (!enemy.isDead() && checkCollision(bullets[i].rect, enemy.rect))
            {
                bool justDied = enemy.takeHit(10);
                if (justDied)
                {
                    playerStats.setScore(
                        playerStats.getScore() + 100
                    );

                    effects.addText(
                        "+100",
                        enemy.x + enemy.w / 2,
                        enemy.y,
                        180
                    );
                }

                bullets.erase(bullets.begin() + i);
                bulletRemoved = true;
                break;
            }
        }

        if (!bulletRemoved)
        {
            i++;
        }
    }
}

void EnemyManager::reset() {
    enemies.clear();
}