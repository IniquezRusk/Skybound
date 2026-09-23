#include "enemy_manager.h"
#include "constant.h"

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

void EnemyManager::spawnLineFormation() {
    for (int i = 0; i < 4; i++) {
        spawnEnemy(
            SCREEN_WIDTH + 100 + i * 100,
            150 + i * 60,
            EnemyType::SMALL
        );
    }
}

void EnemyManager::spawnVformation()
{
    spawnEnemy(
        SCREEN_WIDTH + 100,
        100,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 200,
        150,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 300,
        200,
        EnemyType::MEDIUM
    );

    spawnEnemy(
        SCREEN_WIDTH + 400,
        150,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 500,
        100,
        EnemyType::SMALL
    );
}

void EnemyManager::spawnDiamondFormation()
{
    spawnEnemy(
        SCREEN_WIDTH + 200,
        100,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 100,
        200,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 300,
        200,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 200,
        300,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 200,
        200,
        EnemyType::MEDIUM
    );
}

void EnemyManager::spawnHeavyFormation(int wave)
{
    spawnEnemy(
        SCREEN_WIDTH + 100,
        100,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 200,
        150,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 300,
        100,
        EnemyType::SMALL
    );

    spawnEnemy(
        SCREEN_WIDTH + 150,
        250,
        EnemyType::MEDIUM
    );

    spawnEnemy(
        SCREEN_WIDTH + 350,
        250,
        EnemyType::MEDIUM
    );

    // Large enemy
    spawnEnemy(
        SCREEN_WIDTH + 250,
        175,
        EnemyType::LARGE
    );
}

void EnemyManager::spawnEnemy(float x, float y, EnemyType type)
{
    if (type == EnemyType::SMALL)
    {
        enemies.emplace_back(
            x, y,
            40, 40,
            -2, 0,
            renderer,
            smallTexture,
            EnemyType::SMALL
        );
    }
    else if (type == EnemyType::MEDIUM)
    {
        enemies.emplace_back(
            x, y,
            60, 60,
            -2, 0,
            renderer,
            mediumTexture,
            EnemyType::MEDIUM
        );
    }
    else if (type == EnemyType::LARGE)
    {
        enemies.emplace_back(
            x, y,
            90, 90,
            -2, 0,
            renderer,
            largeTexture,
            EnemyType::LARGE
        );
    }
}

void EnemyManager::update()
{
    for (auto& enemy : enemies)
    {
        if (!enemy.isDead())
        {
            enemy.update();
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