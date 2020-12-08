#include "../include/player.h"

Player::Player(int id, int x, int y){
    this->x = x;
    this->y = y;
    sprite = new Sprite(id, x, y);
}

Player::~Player(){
    delete sprite;
}

void Player::render(){
    sprite->render();
}

void Player::update(){
    sprite->update();
}

void Player::event(SDL_Event e){

}
