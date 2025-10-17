#ifndef STATS_H
#define STATS_H
#include "constant.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class stats {
    private:
        int lives;
        int score;
        int highScore;
        int multiplier;
        int timer;
        int waveNumber;

    public:
        stats() {
            lives = 0;
            score = 0;
            highScore = 0;
            multiplier = 1;
            timer = 0;
            waveNumber = 1;

        }

        // Setters
        void setLives(int l);
        void setScore(int s);
        void setHighScore(int hs);
        void setMultiplier(int m);
        void setTimer(int t);
        void setWaveNumber(int wan);

        // Getters
        int getLives();
        int getScore();
        int getHighScore();
        int getMultiplier();
        int getTimer();
        int getWaveNumber();


        // Display Functions
        void displayLives(SDL_Renderer* renderer, int x, int y, TTF_Font* font);
        void displayScore(SDL_Renderer* renderer, int x, int y, TTF_Font* font);
        void displayHighScore(SDL_Renderer* renderer, int x, int y, TTF_Font* font);
        void displayMultiplier(SDL_Renderer* renderer, int x, int y, TTF_Font* font);
        void displayTimer(SDL_Renderer* renderer, int x, int y, TTF_Font* font);
        void displayWaveNumber(SDL_Renderer* renderer, int x, int y, TTF_Font* font);
        
};

#endif