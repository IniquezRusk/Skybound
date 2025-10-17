#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H

#include <vector>
#include "asteroid.h"
#include "stats.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class AsteroidManager {
private:
    SDL_Renderer* renderer;
    SDL_Texture* asteroidTexture;
    int currentWave;
    Uint32 waveTimer;
    bool waitingForNextWave;

    float formationX;
    float formationY;
    bool movingDown;

public:
    std::vector<Asteroid> asteroids;

    AsteroidManager(SDL_Renderer* renderer);
    ~AsteroidManager();

    void startNextWave(stats& playerStats);
    void update(stats& playerStats);
    void render();

    bool allAsteroidsDestroyed();
};

#endif
