#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

void renderText(SDL_Renderer* renderer,
                const std::string& text,
                int x, int y,
                TTF_Font* font,
                SDL_Color color = {255, 255,255,255});

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

#endif