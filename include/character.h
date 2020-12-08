#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "engine/texture.h"

#define CHR_MARGIN_TOP 88
#define CHR_SPRITES 20
#define CHR_UP 0
#define CHR_RIGHT 1
#define CHR_DOWN 2
#define CHR_LEFT 3

class Character{
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
    Character(int id, int x, int y);

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
