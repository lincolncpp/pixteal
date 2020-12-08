#include "../include/character.h"

Texture *Character::texture = nullptr;

Character::Character(int id, int x, int y){
    this->id = id % CHR_SPRITES;
    this->x = x;
    this->y = y;
}

void Character::render(){
    Character::texture->setPos(x*32 + offsetx, CHR_MARGIN_TOP + y*32 + offsety);
    Character::texture->setClip({id*32, 0, 32, 32});
    Character::texture->render();
}

void Character::update(){

}

void Character::setX(int x){this->x = x;}
void Character::setY(int y){this->y = y;}
void Character::setPos(int x, int y){this->x = x;this->y = y;}
void Character::move(int dir){
    if (is_moving == false){
        is_moving = true;
        this->dir = dir;
    }
}

void Character::loadTexture(Texture *texture){
    Character::texture = texture;
    Character::texture->setWidth(32);
    Character::texture->setHeight(32);
}

void Character::unloadTexture(){
    delete Character::texture;
}
