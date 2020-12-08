#include <iostream>
#include <string>
#include "../include/engine/engine.h"
#include "../include/engine/texture.h"
#include "../include/engine/font.h"
#include "../include/engine/text.h"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 600

Engine *engine;

// Thread 0 (renderização)
void render(){

}

// Thread 1 (entradas)
void event(SDL_Event e){

}

int main(){

    // Criando engine
    engine = new Engine(WINDOW_WIDTH, WINDOW_HEIGHT, "Pixteal");

    // Iniciando engine
    engine->start(render, event);

    // Aguardando a finalização das threads da engine
    engine->join();

    // Destruindo componentes
    delete engine;

    return 0;
}
