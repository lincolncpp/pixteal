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
    Engine *engine;

    // Se a posição (x, y) está ocupada, occupied[x][y] = true
    // Só é permitido que uma thread acesse essa variável por vez.
    bool occupied[WORLD_WIDTH][WORLD_HEIGHT] = {};

public:
    // Mutex de acesso à variável occupied
    pthread_mutex_t mutex;

    World(Engine *engine, const char *path);
    ~World();

    void render();
    bool isOccupied(int x, int y);
    void setOccupied(int x, int y, bool value);
};

#endif
