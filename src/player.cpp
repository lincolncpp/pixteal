#include "../include/player.h"

Player::Player(World *world, Text *text, int id, int x, int y) : Sprite(id, x, y){
    this->world = world;
    this->text = text;
    this->x = x;
    this->y = y;
}

Player::~Player(){

}

void Player::render(){
    // Renderizando nome
    text->setColor(251, 242, 54);
    text->setPos(x*32 - 16 + offsetx, WORLD_MARGIN_TOP + y*32 - 20 + offsety);
    text->setText("Thread 1");
    text->render();

    // Renderizando sprite
    Sprite::render();
}

void Player::update(){
    Sprite::update();

    // Checa se não está se movendo no momento e se existe algum movimento para fazer
    if (isMoving() == false && (moving_up|moving_right|moving_down|moving_left) == true){

        // Entrando na região critica
        pthread_mutex_lock(&world->mutex);

        if (moving_up) move(SP_UP);
        if (moving_right) move(SP_RIGHT);
        if (moving_down) move(SP_DOWN);
        if (moving_left) move(SP_LEFT);

        // Saindo da região crítica
        pthread_mutex_unlock(&world->mutex);
    }
}

void Player::setMovingUp(bool value){moving_up = value;}
void Player::setMovingRight(bool value){moving_right = value;}
void Player::setMovingDown(bool value){moving_down = value;}
void Player::setMovingLeft(bool value){moving_left = value;}
