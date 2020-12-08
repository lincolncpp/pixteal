#ifndef WORLD_H
#define WORLD_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "engine/texture.h"
#include "engine/engine.h"
#include <pthread.h>

#define WORLD_MARGIN_TOP 88

#define WORLD_WIDTH 25
#define WORLD_HEIGHT 15

class World{
private:
    Texture *texture_ground;
    Texture *texture_ores;
    Engine *engine;

    // Se a posição (x, y) está ocupada, occupied[x][y] = true
    // Só é permitido que uma thread acesse essa variável por vez.
    bool occupied[WORLD_WIDTH][WORLD_HEIGHT] = {};

    // Posição da recompensa
    int ore_x = 0;
    int ore_y = 0;
    int ore_id = 0;
    bool ore_valid = false;

public:
    // Mutex de acesso à variável occupied
    pthread_mutex_t mutex;

    World(Engine *engine, const char *path_ground, const char *path_ores);
    ~World();

    void render();
    void update();
    bool isOccupied(int x, int y);
    void setOccupied(int x, int y, bool value);

    int catchReward(int x, int y);

    SDL_Point randomPoint();
};

#endif
