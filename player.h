#ifndef PLAYER_H
#define PLAYER_H
#include "constant.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Plane {
    public:
        int x, y, w, h; 
        int speed;
        float renderScale;
        SDL_Rect rect;
        SDL_Texture* texture;
        SDL_Renderer* renderer;

    Plane(int startX, int startY, int width, int height, int s, SDL_Renderer* r);
    ~Plane();

    void update(const Uint8* keystates);
    void render(SDL_Renderer* renderer);
};


#endif