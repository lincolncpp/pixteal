#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "engine/texture.h"

#define SP_MARGIN_TOP 88
#define SP_SPRITES 20
#define SP_SPEED 200

#define SP_UP 0
#define SP_RIGHT 1
#define SP_DOWN 2
#define SP_LEFT 3

class Sprite{
private:
    int id;
    int x;
    int y;
    int offsetx = 0;
    int offsety = 0;
    int dir = 0;
    bool is_moving = false;
    unsigned int move_time = 0;

    static Texture *texture;

public:
    Sprite(int id, int x, int y);

    void render();
    void update();

    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
    void move(int dir);

    static void loadTexture(Texture *texture);
    static void unloadTexture();
};

#endif
