#include "../include/enemy.h"

Enemy::Enemy(World *world, Text *text, std::string name, int id, int x, int y) : Sprite(id, x, y){
    this->world = world;
    this->text = text;
    this->name = name;
}

void Enemy::render(){
    // Renderizando sprite
    Sprite::render();
}

void Enemy::renderName(){
    // Renderizando nome
    text->setColor(255, 255, 255);
    text->setPos(x*32 - 16 + offsetx, WORLD_MARGIN_TOP + y*32 - 20 + offsety);
    text->setText(name);
    text->render();
}

void Enemy::update(){
    // Atualizando sprite
    Sprite::update();

    // Movimenta o personagem
    if (isMoving() == false){

        // Entrando na região critica
        pthread_mutex_lock(&world->mutex);

        // Obtendo posição do tesouro
        SDL_Point point = world->getOrePosition();
        int p = (rand()%100)+1;

        // Se o tesouro não está no mapa ou p > ENEMY_PROBABILITY, então
        // anda aleatoriamente para algum lado
        if (point.x == -1 || p > ENEMY_PROBABILITY*100){

            // Tentativas finitas
            for(int i = 0;i < ENEMY_RANDOM_ATTEMPTS;i++){
                int dir = (rand()%4)+1;

                if (dir == SP_UP && world->isOccupied(x, y-1) == false){
                    world->setOccupied(x, y, false);
                    world->setOccupied(x, y-1, true);
                    move(SP_UP);
                    break;
                }
                if (dir == SP_RIGHT && world->isOccupied(x+1, y) == false){
                    world->setOccupied(x, y, false);
                    world->setOccupied(x+1, y, true);
                    move(SP_RIGHT);
                    break;
                }
                if (dir == SP_DOWN && world->isOccupied(x, y+1) == false){
                    world->setOccupied(x, y, false);
                    world->setOccupied(x, y+1, true);
                    move(SP_DOWN);
                    break;
                }
                if (dir == SP_LEFT && world->isOccupied(x-1, y) == false){
                    world->setOccupied(x, y, false);
                    world->setOccupied(x-1, y, true);
                    move(SP_LEFT);
                    break;
                }
            }
        }
        else{ // Anda em direação do tesouro

            if (point.x > x && world->isOccupied(x+1, y) == false){ // Tesouro está à direita
                world->setOccupied(x, y, false);
                world->setOccupied(x+1, y, true);
                move(SP_RIGHT);
            }
            else if (point.x < x && world->isOccupied(x-1, y) == false){ // Tesouro está à esquerda
                world->setOccupied(x, y, false);
                world->setOccupied(x-1, y, true);
                move(SP_LEFT);
            }
            else if (point.y > y && world->isOccupied(x, y+1) == false){ // Tesouro está abaixo
                world->setOccupied(x, y, false);
                world->setOccupied(x, y+1, true);
                move(SP_DOWN);
            }
            else if (point.y < y && world->isOccupied(x, y-1) == false){ // Tesouro está acima
                world->setOccupied(x, y, false);
                world->setOccupied(x, y-1, true);
                move(SP_UP);
            }
        }

        // Saindo da região crítica
        pthread_mutex_unlock(&world->mutex);
    }

    // Pegando recompensa do chão (caso esteja em cima)
    points += world->catchReward(x, y);
}

int Enemy::getPoints(){
    return points;
}
