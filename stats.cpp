#include "stats.h"
#include <string>

// Setter Functions

void stats::setLives(int l) {
    lives = l;
} 
void stats::setScore(int s) {
    score = s;
}
void stats::setHighScore(int hs) {
    highScore = hs;
}
void stats::setMultiplier(int m) {
    multiplier = m;
}
void stats::setTimer(int t) {
    timer = t;
}
void stats::setWaveNumber(int wN) {
    waveNumber = wN;
}

// Getter Functions

int stats::getLives() {
    return lives;
}
int stats::getScore() {
    return score;
}
int stats::getHighScore() {
    return highScore;
}
int stats::getMultiplier() {
    return multiplier;
}
int stats::getTimer() {
    return timer;
}
int stats::getWaveNumber() {
    return waveNumber;
}

void stats::displayLives(SDL_Renderer* renderer, int x, int y, TTF_Font* font) {
    renderText(renderer, "Lives: " + std::to_string(lives), x, y, font);
}

void stats::displayScore(SDL_Renderer* renderer, int x, int y, TTF_Font* font) {
    renderText(renderer, "Score: " + std::to_string(score), x, y, font);
}

void stats::displayHighScore(SDL_Renderer* renderer, int x, int y, TTF_Font* font) {
    renderText(renderer, "High Score: " + std::to_string(highScore), x, y, font);
}

void stats::displayMultiplier(SDL_Renderer* renderer, int x, int y, TTF_Font* font) {
    renderText(renderer, "Multiplier: " + std::to_string(multiplier), x, y, font);
}

void stats::displayTimer(SDL_Renderer* renderer, int x, int y, TTF_Font* font) {
    renderText(renderer, "Timer: " + std::to_string(timer), x, y, font);
}

void stats::displayWaveNumber(SDL_Renderer* renderer, int x, int y, TTF_Font* font) {
    renderText(renderer, "Wave: " + std::to_string(waveNumber), x, y, font);
}

