#ifndef SCREENEFFECTS_H
#define SCREENEFFECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

struct floatingText {
    std::string text;
    int x, y;
    int lifetime;
    int maxLifeTime;
};

class ScreenEffects {
    public:
        std::vector<floatingText> texts;

        void addText(const std::string& t, int x, int y, int lifetime);
        void update();
        void render(SDL_Renderer* renderer, TTF_Font* font);

};

#endif