#include "screeneffects.h"
#include "utils.h"

void ScreenEffects::addText(const std::string& t, int x, int y, int lifetime) {
    texts.push_back({t, x, y, lifetime, lifetime});
}

void ScreenEffects::update() {
    for (int i = 0; i < texts.size();) {
        texts[i].y -= 1;
        texts[i].lifetime--;

        if (texts[i].lifetime <= 0) {
            texts.erase(texts.begin() + i);
        } else {
            i++;
        }
    }
}

void ScreenEffects::render(SDL_Renderer* renderer, TTF_Font* font) {
    for (auto& t : texts) {
        // Fade out: Alpha depends on lifetime

        float lifeRatio = (float)t.lifetime / (float)t.maxLifeTime;
        if (lifeRatio < 0) lifeRatio = 0.0f;
        
        Uint8 alpha = (Uint8)(lifeRatio * 255);

        SDL_Color color = {255, 255, 0, alpha}; // Yellow with fade
        renderText(renderer, t.text, t.x, t.y, font, color);
    }
}