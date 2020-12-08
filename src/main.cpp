#include <iostream>
#include <string>
#include "../include/engine/engine.h"
#include "../include/engine/texture.h"
#include "../include/engine/font.h"
#include "../include/engine/text.h"
#include "../include/sprite.h"
#include "../include/player.h"
#include "../include/world.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 568

// Engine
Engine *engine;

// Variáveis do jogo
World *world;

// Texturas
Texture *texture_1px;

// Fonte e texto
Font *font;
Text *text;

// Jogador
Player *player;

// Thread principal
void render(){
    // Renderizando terreno
    world->render();

    // Renderizando interface
    texture_1px->setColor(50, 60, 57);
    texture_1px->setWidth(WINDOW_WIDTH);
    texture_1px->setHeight(88);
    texture_1px->render();

    player->render();
}

// Thread principal
void update(){

    // Tratando eventos
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0){
        // Comando para fechar o programa
        if (e.type == SDL_QUIT) {
            engine->stop();
            return;
        }

        // Tecla para baixo ou para baixo
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
            SDL_Keycode code = e.key.keysym.sym;

            if (code == SDLK_UP || code == SDLK_w) player->setMovingUp(e.type == SDL_KEYDOWN);
            if (code == SDLK_RIGHT || code == SDLK_d) player->setMovingRight(e.type == SDL_KEYDOWN);
            if (code == SDLK_DOWN || code == SDLK_s) player->setMovingDown(e.type == SDL_KEYDOWN);
            if (code == SDLK_LEFT || code == SDLK_a) player->setMovingLeft(e.type == SDL_KEYDOWN);
        }
    }

    // Atualizando Jogador
    player->update();
}

int main(){

    // Criando engine
    engine = new Engine(WINDOW_WIDTH, WINDOW_HEIGHT, "Pixteal");

    // Carregando textura dos personagens
    Sprite::loadTexture(new Texture(engine, "gfx/sprites.png"));

    // Carregando fonte e objeto para renderização de texto
    font = new Font("gfx/font.ttf", 16);
    text = new Text(engine, font, " ");

    // Carregando objetos do jogo
    world = new World(engine, "gfx/ground.png");
    player = new Player(world, text, rand(), 5, 5);

    // Carregando texturas
    texture_1px = new Texture(engine, "gfx/1px.png");

    // Iniciando motor de renderização
    engine->start(render, update);

    // Destruindo componentes
    delete world;
    delete player;
    delete font;
    delete text;
    delete texture_1px;
    Sprite::unloadTexture();
    delete engine;

    return 0;
}
