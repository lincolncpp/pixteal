#include "../include/world.h"

World::World(Engine *engine, const char *path){
    this->engine = engine;

    // Carregando textura do terreno
    texture_ground = new Texture(engine, path);
    texture_ground->setPos(0, WORLD_MARGIN_TOP);

    // Marcando as paredes como ocupado
    for(int x = 0;x < WORLD_WIDTH;x++){
        occupied[x][0] = true;
        occupied[x][WORLD_HEIGHT-1] = true;
    }
    for(int y = 0;y < WORLD_HEIGHT;y++){
        occupied[0][y] = true;
        occupied[WORLD_WIDTH-1][y] = true;
    }

    // Inicializando mutex
    pthread_mutex_init(&mutex, NULL);
}

World::~World(){
    delete texture_ground;

    // Destruindo mutex
    pthread_mutex_destroy(&mutex);
}

void World::render(){
    texture_ground->render();
}

bool World::isOccupied(int x, int y){
    return occupied[x][y];
}

void World::setOccupied(int x, int y, bool value){
    occupied[x][y] = value;
}
