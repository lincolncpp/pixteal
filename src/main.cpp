#include <iostream>
#include <string>
#include "../include/engine/engine.h"
#include "../include/engine/texture.h"
#include "../include/engine/font.h"
#include "../include/engine/text.h"
#include "../include/character.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 568

// Engine
Engine *engine;

// Texturas
Texture *texture_ground;
Texture *texture_1px;

// Fonte e texto
Font *font;
Text *text_name;

// Personagens
Character *character_player;

// Thread 0 (renderização)
void render(){
    // Renderizando terreno
    texture_ground->render();

    // Renderizando interface
    texture_1px->setColor(50, 60, 57);
    texture_1px->setWidth(WINDOW_WIDTH);
    texture_1px->setHeight(88);
    texture_1px->render();

    character_player->render();

    text_name->render();
}

// Thread 1 (entradas)
void event(SDL_Event e){

}

int main(){

    // Criando engine
    engine = new Engine(WINDOW_WIDTH, WINDOW_HEIGHT, "Pixteal");

    // Carregando fonte e texto
    font = new Font("gfx/font.ttf", 16);
    text_name = new Text(engine, font, "Thread 0");
    text_name->setColor(20, 19, 30);
    text_name->setPos(5*32-16, 88+5*32-20);

    // Carregando texturas
    texture_ground = new Texture(engine, "gfx/ground.png");
    texture_ground->setY(88);
    texture_1px = new Texture(engine, "gfx/1px.png");
    Character::loadTexture(new Texture(engine, "gfx/sprites.png"));

    character_player = new Character(rand(), 5, 5);

    // Iniciando engine
    engine->start(render, event);

    // Aguardando a finalização das threads da engine
    engine->join();

    // Destruindo componentes
    Character::unloadTexture();
    delete font;
    delete text_name;
    delete texture_ground;
    delete texture_1px;
    delete engine;

    return 0;
}
