#include "../include/player.h"

Player::Player(World *world, Text *text, int id, int x, int y) : Sprite(id, x, y){
    this->world = world;
    this->text = text;
}

void Player::render(){
    // Renderizando sprite
    Sprite::render();
}

void Player::renderName(){
    // Renderizando nome
    text->setColor(251, 242, 54);
    text->setPos(x*32 - 16 + offsetx, WORLD_MARGIN_TOP + y*32 - 20 + offsety);
    text->setText("Thread 1");
    text->render();
}

void Player::update(){
    // Atualizando sprite
    Sprite::update();

    // Checa se não está se movendo no momento e se existe algum movimento para fazer
    if (isMoving() == false && (moving_up|moving_right|moving_down|moving_left) == true){

        // Entrando na região critica
        pthread_mutex_lock(&world->mutex);

        // Move para a posição solicitada e disponível
        if (moving_up && (priority == 0 || priority == SP_UP)) {
            if (world->isOccupied(x, y-1) == false){
                world->setOccupied(x, y, false);
                world->setOccupied(x, y-1, true);
                move(SP_UP);
            }
        }
        else if (moving_right && (priority == 0 || priority == SP_RIGHT)) {
            if (world->isOccupied(x+1, y) == false){
                world->setOccupied(x, y, false);
                world->setOccupied(x+1, y, true);
                move(SP_RIGHT);
            }
        }
        else if (moving_down && (priority == 0 || priority == SP_DOWN)){
            if (world->isOccupied(x, y+1) == false){
                world->setOccupied(x, y, false);
                world->setOccupied(x, y+1, true);
                move(SP_DOWN);
            }
        }
        else if (moving_left && (priority == 0 || priority == SP_LEFT)) {
            if (world->isOccupied(x-1, y) == false){
                world->setOccupied(x, y, false);
                world->setOccupied(x-1, y, true);
                move(SP_LEFT);
            }
        }

        // Saindo da região crítica
        pthread_mutex_unlock(&world->mutex);
    }

    // Pegando recompensa do chão (caso esteja em cima)
    points += world->catchReward(x, y);
}

int Player::getPoints(){
    return points;
}

void Player::setMovingUp(bool value){
    if (value == true && moving_up == false) priority = SP_UP;
    if (value == false) priority = 0;
    moving_up = value;
}
void Player::setMovingRight(bool value){
    if (value == true && moving_right == false) priority = SP_RIGHT;
    if (value == false) priority = 0;
    moving_right = value;
}
void Player::setMovingDown(bool value){
    if (value == true && moving_down == false) priority = SP_DOWN;
    if (value == false) priority = 0;
    moving_down = value;
}
void Player::setMovingLeft(bool value){
    if (value == true && moving_left == false) priority = SP_LEFT;
    if (value == false) priority = 0;
    moving_left = value;
}
