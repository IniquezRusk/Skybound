// g++ main.cpp player.cpp asteroid.cpp bullet.cpp stats.cpp screeneffects.cpp utils.cpp asteroid_manager.cpp -Ix86_64-w64-mingw32/include -Lx86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o Skybound.exe

#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "constant.h"
#include "player.h"
#include "asteroid.h"
#include "bullet.h"
#include "stats.h"
#include "screeneffects.h"
#include "asteroid_manager.h"

enum GameState {
    TITLE,
    PLAYING,
    PAUSED,
    GAME_OVER
};

// Function that checks for collisions, Axis-Aligned bounding box
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL2 could not be initialized! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    window = SDL_CreateWindow("Skybound", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* background = IMG_LoadTexture(renderer, "assets/background.png");
    if (!background) {
        printf("Failed to load background: %s\n", SDL_GetError());
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("assets/yourfont.ttf", 12);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return 1;
    }

    // Stats and setup
    stats gameStats;
    ScreenEffects effects;
    gameStats.setLives(3);
    gameStats.setScore(0);
    gameStats.setHighScore(0);
    gameStats.setMultiplier(1);
    gameStats.setTimer(0);
    gameStats.setWaveNumber(1);

    // Game objects
    Plane plane(100, 250, 50, 30, 5, renderer);
    AsteroidManager asteroidManager(renderer);
    asteroidManager.startNextWave(gameStats);

    std::vector<Bullet> bullets;

    int bgX = 0;
    const int scrollSpeed = 5;

    bool quit = false;
    SDL_Event e;

    // Pause control
    bool paused = false;
    Uint32 pauseStart = 0;
    const Uint32 pauseDuration = 1500; // 1.5 seconds

    GameState state = TITLE;

    Uint32 startTime = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            // If any key is pressed, start the game
            if (state == TITLE && e.type == SDL_KEYDOWN) {
                state = PLAYING;
                startTime = SDL_GetTicks();
            }

            // If any key is pressed on GAME OVER, return to title
            if (state == GAME_OVER && e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                // reset stats
                gameStats.setLives(3);
                gameStats.setScore(0);
                gameStats.setWaveNumber(1);
                gameStats.setMultiplier(1);
                gameStats.setTimer(0);
                Uint32 startTime = 0;

                // resets world
                bullets.clear();
                asteroidManager.asteroids.clear();
                effects = ScreenEffects();

                // Resets player position
                plane.x = 100;
                plane.y = SCREEN_HEIGHT / 2 - plane.h / 2;
                plane.rect.x = (int)plane.x;
                plane.rect.y = (int)plane.y;

            state = TITLE;
            }
        }
     } // End of SDL_PollEvent
    
// Title screen state
if (state == TITLE) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 20, 255); // dark background
    SDL_RenderClear(renderer);

    // Title text
    SDL_Color white = {255, 255, 255};
    SDL_Surface* titleSurf = TTF_RenderText_Solid(font, "PROJECT SKYBOUND", white);
    SDL_Texture* titleTex = SDL_CreateTextureFromSurface(renderer, titleSurf);
    SDL_Rect titleRect = {
        SCREEN_WIDTH / 2 - titleSurf->w / 2,
        150,
        titleSurf->w,
        titleSurf->h
    };
    SDL_RenderCopy(renderer, titleTex, nullptr, &titleRect);
    SDL_FreeSurface(titleSurf);
    SDL_DestroyTexture(titleTex);

    // Blinking "Press any key" (only during TITLE)
    if ((SDL_GetTicks() / 500) % 2 == 0) {
        SDL_Color gray = {200, 200, 200};
        SDL_Surface* msgSurf = TTF_RenderText_Solid(font, "PRESS ANY KEY TO START", gray);
        SDL_Texture* msgTex = SDL_CreateTextureFromSurface(renderer, msgSurf);
        SDL_Rect msgRect = {
            SCREEN_WIDTH / 2 - msgSurf->w / 2,
            SCREEN_HEIGHT - 120,
            msgSurf->w,
            msgSurf->h
        };
        SDL_RenderCopy(renderer, msgTex, nullptr, &msgRect);
        SDL_FreeSurface(msgSurf);
        SDL_DestroyTexture(msgTex);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
    continue; // stay in TITLE and skip the gameplay code
}


    // Game over state
    if (state == GAME_OVER) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // White
        SDL_RenderClear(renderer);

        SDL_Color red {255, 0, 0};
        SDL_Surface* overSurf = TTF_RenderText_Solid(font, "GAME OVER", red);
        SDL_Texture* overTex = SDL_CreateTextureFromSurface(renderer, overSurf);
        SDL_Rect overRect = {SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT/2 - 150, 300, 100};
        SDL_RenderCopy(renderer, overTex, nullptr, &overRect);
        SDL_FreeSurface(overSurf);
        SDL_DestroyTexture(overTex);

        SDL_Color white = {255, 255, 255};
        std::string scoreText = "FINAL SCORE: " + std::to_string(gameStats.getScore());
        SDL_Surface* scoreSurf = TTF_RenderText_Solid(font, scoreText.c_str(), white);
        SDL_Texture* scoreTex = SDL_CreateTextureFromSurface(renderer, scoreSurf);
        SDL_Rect scoreRect = {SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 40, 360, 60};
        SDL_RenderCopy(renderer, scoreTex, nullptr, &scoreRect);
        SDL_FreeSurface(scoreSurf);
        SDL_DestroyTexture(scoreTex);
        
        if ((SDL_GetTicks() / 500) % 2 == 0) {
            SDL_Color gray = {200, 200, 200};
            SDL_Surface* msgSurf = TTF_RenderText_Solid(font, "PRESS ENTER TO RETURN TO MENU", gray);
            SDL_Texture* msgTex = SDL_CreateTextureFromSurface(renderer, msgSurf);
            SDL_Rect msgRect = {SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT - 120, 560, 50};
            SDL_RenderCopy(renderer, msgTex, nullptr, &msgRect);
            SDL_FreeSurface(msgSurf);
            SDL_DestroyTexture(msgTex);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        continue;
    } 

        // Handles pause timer
        if (paused) {
            if (SDL_GetTicks() - pauseStart >= pauseDuration) {
                paused = false;
            } else {
                SDL_RenderPresent(renderer);
                SDL_Delay(16);
                continue;
            }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        plane.update(keystates);

        // Scroll background
        bgX -= scrollSpeed;
        if (bgX <= -SCREEN_WIDTH)
            bgX = 0;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render background
        SDL_Rect src = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect dest1 = {bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect dest2 = {bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, background, &src, &dest1);
        SDL_RenderCopy(renderer, background, &src, &dest2);

        // Draw plane
        plane.render(renderer);

        // Update asteroids
        asteroidManager.update(gameStats);
        asteroidManager.render();

        // Plane-Asteroid collision check
        if (!paused) {
            for (auto& a : asteroidManager.asteroids) {
                if (!a.isDead() && checkCollision(plane.rect, a.rect)) {
                    paused = true;
                    pauseStart = SDL_GetTicks();
                    gameStats.setLives(gameStats.getLives() - 1);
                    effects.addText("-1 LIFE", plane.x + plane.w / 2, plane.y - 20, 200);

                    a.takeHit(9999); // instantly destroys the asteroid
                    break;
                }
            }
        }

        if (gameStats.getLives() <= 0) {
            paused = false;
            state = GAME_OVER;

            if (gameStats.getScore() > gameStats.getHighScore()) {
                gameStats.setHighScore(gameStats.getScore());
            }
            continue;
        }

        // Increments the timer inside the game
        if (state == PLAYING) {
            Uint32 elapsedMS = SDL_GetTicks() - startTime;
            gameStats.setTimer(elapsedMS / 1000);
        } 

        // HUD
        gameStats.displayLives(renderer, 20, 20, font);
        gameStats.displayScore(renderer, 20, 50, font);
        gameStats.displayHighScore(renderer, 20, 80, font);
        gameStats.displayMultiplier(renderer, 20, 110, font);
        gameStats.displayTimer(renderer, 20, 140, font);
        gameStats.displayWaveNumber(renderer, 20, 170, font);

        // Fire bullets
        static Uint32 lastFireTime = 0;
        Uint32 currentTime = SDL_GetTicks();
        if (keystates[SDL_SCANCODE_SPACE] && currentTime - lastFireTime > 100) {
            bullets.push_back(Bullet(plane.x + plane.w, plane.y + plane.h / 2, 8, 2, 10, true));
            lastFireTime = currentTime;
        }


        // Update and render bullets
        for (int i = 0; i < bullets.size();) {
            bullets[i].update();
            bullets[i].render(renderer);

            bool bulletRemoved = false;

            for (auto& a : asteroidManager.asteroids) {
                if (!a.isDead() && checkCollision(bullets[i].rect, a.rect)) {
                    bool justDied = a.takeHit(10);
                    if (justDied) {
                        gameStats.setScore(gameStats.getScore() + 100);
                        effects.addText("+100", a.x + a.w / 2, a.y, 180);
                    }
                    bullets.erase(bullets.begin() + i);
                    bulletRemoved = true;
                    break;
                }
            }

            if (bulletRemoved) continue;

            if (bullets[i].isOffScreen()) {
                bullets.erase(bullets.begin() + i);
            } else {
                i++;
            }
        }

        // Update effects
        effects.update();
        effects.render(renderer, font);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);

    }

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
