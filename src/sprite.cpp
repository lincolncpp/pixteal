#include "../include/sprite.h"

Texture *Sprite::texture = nullptr;

Sprite::Sprite(int id, int x, int y){
    this->id = id % SP_SPRITES;
    this->x = x;
    this->y = y;
}

void Sprite::render(){
    Sprite::texture->setPos(x*32 + offsetx, SP_MARGIN_TOP + y*32 + offsety);
    Sprite::texture->setClip({id*32, 0, 32, 32});
    Sprite::texture->render();
}

void Sprite::update(){
    unsigned int t = SDL_GetTicks();

    if (is_moving){
        if (move_time == 0) move_time = t;
        unsigned int delta = t-move_time;
        int pos = 32*delta/SP_SPEED;
        if (pos > 32) pos = 32;

        if (dir == SP_UP) offsety = -pos;
        else if (dir == SP_RIGHT) offsetx = pos;
        else if (dir == SP_DOWN) offsety = pos;
        else offsetx = -pos;

        if (pos == 32){
            if (dir == SP_UP) y--;
            else if (dir == SP_RIGHT) x++;
            else if (dir == SP_DOWN) y++;
            else x--;

            is_moving = false;
            move_time = 0;
            offsetx = 0;
            offsety = 0;
        }
    }
}

void Sprite::setX(int x){this->x = x;}
void Sprite::setY(int y){this->y = y;}
void Sprite::setPos(int x, int y){this->x = x;this->y = y;}
void Sprite::move(int dir){
    if (is_moving == false){
        is_moving = true;
        this->dir = dir;
    }
}

void Sprite::loadTexture(Texture *texture){
    Sprite::texture = texture;
    Sprite::texture->setWidth(32);
    Sprite::texture->setHeight(32);
}

void Sprite::unloadTexture(){
    delete Sprite::texture;
}
