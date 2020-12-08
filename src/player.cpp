#include "../include/player.h"

Player::Player(Text *text, int id, int x, int y){
    this->text = text;
    this->x = x;
    this->y = y;
    sprite = new Sprite(id, x, y);
}

Player::~Player(){
    delete sprite;
}

void Player::render(){
    // Renderizando nome
    text->setColor(251, 242, 54);
    text->setPos(x*32 - 16, WORLD_MARGIN_TOP + y*32 - 20);
    text->setText("Thread 1");
    text->render();

    // Renderizando sprite
    sprite->render();
}

void Player::update(){
    sprite->update();
}

// Thread 1
void Player::event(SDL_Event e){

}
