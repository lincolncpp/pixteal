#include "../include/enemy.h"

Enemy::Enemy(World *world, Text *text, std::string name, int id, int x, int y) : Sprite(id, x, y){
    this->world = world;
    this->text = text;
    this->name = name;
}

void Enemy::render(){
    // Renderizando nome
    text->setColor(223, 113, 38);
    text->setPos(x*32 - 16 + offsetx, WORLD_MARGIN_TOP + y*32 - 20 + offsety);
    text->setText(name);
    text->render();

    // Renderizando sprite
    Sprite::render();
}
void Enemy::update(){
    // Atualizando sprite
    Sprite::update();
}
