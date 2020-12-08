#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "engine/texture.h"
#include "engine/text.h"
#include "sprite.h"
#include "world.h"

class Player{
private:
    int x;
    int y;

    Sprite *sprite;
    Text *text;

public:
    Player(Text *text, int id, int x, int y);
    ~Player();

    void render();
    void update();
    void event(SDL_Event e);
};

#endif
