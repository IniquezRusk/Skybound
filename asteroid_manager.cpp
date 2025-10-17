#include "asteroid_manager.h"
#include "constant.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

AsteroidManager::AsteroidManager(SDL_Renderer* renderer) : renderer(renderer), currentWave(0), waveTimer(0), waitingForNextWave(false) {
    asteroidTexture = IMG_LoadTexture(renderer, "assets/asteroid.png");
    if (!asteroidTexture)
        printf("Failed to load asteroid texture: %s\n", SDL_GetError());

}

// Starts a new wave of asteroids
void AsteroidManager::startNextWave(stats& playerStats) {
    currentWave++;
    asteroids.clear();

    int numAsteroids = 5 + currentWave * 2;
    if (numAsteroids > 30) numAsteroids = 30;

    // Spawns asteroids at random positions off the right side of the screen
    for (int i = 0; i < numAsteroids; i++) {
        float startX = SCREEN_WIDTH + (rand() % 400); // Spawns it off screen slightly
        float startY = rand() % (SCREEN_HEIGHT - 60); // Random vertical spawn for the asteroid
        float speedX = 2 + (rand() % 3);
        float speedY = ((rand() % 100) - 50) / 80.0f;

        asteroids.push_back(Asteroid(startX, startY, 80, 80, speedX, speedY, renderer, asteroidTexture));
    }

    playerStats.setWaveNumber(currentWave);
    waitingForNextWave = false;
}

// Update and manage all the asteroids each frame
void AsteroidManager::update (stats& playerStats) {
    if (waitingForNextWave) {
    if (SDL_GetTicks() - waveTimer > 2500)
        startNextWave(playerStats);
    return; 
}


    // Update asteroid positions
    for (auto& a : asteroids)
        a.update();

asteroids.erase(
        std::remove_if(asteroids.begin(), asteroids.end(),
                       [](Asteroid& a) {
                           return a.isDead() || (a.rect.x + a.rect.w < 0);
                       }),
        asteroids.end());

    // When all are gone, prepare next wave
    if (allAsteroidsDestroyed()) {
        waitingForNextWave = true;
        waveTimer = SDL_GetTicks();
    }
}

void AsteroidManager::render() {
    for (auto& a : asteroids)
        if (!a.isDead())
            a.render(renderer);
}

bool AsteroidManager::allAsteroidsDestroyed() {
    for (auto& a : asteroids)
        if (!a.isDead()) return false;
    return true;
}

AsteroidManager::~AsteroidManager() {
    if (asteroidTexture)
        SDL_DestroyTexture(asteroidTexture);
}
