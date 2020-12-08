#ifndef ENGINE_H
#define ENGINE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "pthread.h"
#include <iostream>
#include "texture.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


#define FPS_LIMIT 120

class Texture;

class Engine{
    friend class Texture;

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int window_width = -1;
    int window_height = -1;
    void (*render_function)();
    void (*event_function)(SDL_Event);
    int fps = 0;

    pthread_t thread_render;
    pthread_t thread_event;

    static bool run;
    static void *render(void *instance);
    static void *event(void *instance);

public:
    Engine(int width, int height, const char *title);
    ~Engine();

    void start(void render_function(), void event_function(SDL_Event e));
    void join();
    bool isRunning();
    int getFps();

    static void sleep(unsigned int t0);
};


#endif
