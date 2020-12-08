#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "engine/texture.h"
#include "world.h"

#define SP_SPRITES 20
#define SP_SPEED 200

#define SP_UP 1
#define SP_RIGHT 2
#define SP_DOWN 3
#define SP_LEFT 4

class Player;
class Enemy;

class Sprite{
    friend class Player;
    friend class Enemy;

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
    bool update();

    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
    void move(int dir);
    bool isMoving();

    static void loadTexture(Texture *texture);
    static void unloadTexture();
};

#endif
