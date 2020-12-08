#include "../include/world.h"

World::World(Engine *engine, const char *path_ground, const char *path_ores){
    this->engine = engine;

    // Carregando textura do terreno e dos minérios
    texture_ground = new Texture(engine, path_ground);
    texture_ground->setPos(0, WORLD_MARGIN_TOP);
    texture_ores = new Texture(engine, path_ores);
    texture_ores->setWidth(32);
    texture_ores->setHeight(32);

    // Marcando as paredes como ocupado
    for(int x = 0;x < WORLD_WIDTH;x++){
        occupied[x][0] = true;
        occupied[x][1] = true;
        occupied[x][WORLD_HEIGHT-1] = true;
        occupied[x][WORLD_HEIGHT-2] = true;
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
    delete texture_ores;

    // Destruindo mutex
    pthread_mutex_destroy(&mutex);
}

void World::render(){
    texture_ground->render();

    if (ore_valid == true) texture_ores->render();
}

void World::update(){
    if (ore_valid == false){
        SDL_Point p = randomPoint();
        ore_x = p.x;
        ore_y = p.y;
        ore_id = rand()%3;
        ore_valid = true;

        texture_ores->setClip({ore_id*32, 0, 32, 32});
        texture_ores->setPos(ore_x*32, WORLD_MARGIN_TOP+ore_y*32);
    }
}

bool World::isOccupied(int x, int y){
    return occupied[x][y];
}

void World::setOccupied(int x, int y, bool value){
    occupied[x][y] = value;
}

int World::catchReward(int x, int y){
    if (ore_x == x && ore_y == y){
        ore_valid = false;

        // Bronze => 100 points
        // Silver => 200 points
        // Gold => 300 points
        return (ore_id+1)*100;
    }
    return 0;
}

// Retorna um ponto (x, y) aleatório que não está ocupado no mapa
SDL_Point World::randomPoint(){
    int x = 0;
    int y = 0;
    while(occupied[x][y] == true){
        x = rand()%WORLD_WIDTH;
        y = rand()%WORLD_HEIGHT;
    }
    return {x, y};
}
