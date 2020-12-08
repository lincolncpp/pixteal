#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "engine/texture.h"
#include "engine/text.h"
#include "sprite.h"
#include "world.h"

class Player: private Sprite{
private:
    bool moving_up = false;
    bool moving_right = false;
    bool moving_down = false;
    bool moving_left = false;
    int priority = 0;

    int points = 0;

    World *world;
    Text *text;

public:
    Player(World *world, Text *text, int id, int x, int y);

    void render();
    void renderName();
    void update();

    int getPoints();

    void setMovingUp(bool value);
    void setMovingRight(bool value);
    void setMovingDown(bool value);
    void setMovingLeft(bool value);
};

#endif
