#include "../../include/engine/engine.h"

Engine::Engine(int width, int height, const char *title) {

    // Inicializando SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    // Criando janela
    window_width = width;
    window_height = height;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    // Inicializando SDL_png
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags)  & imgFlags)){
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(-1);
    }

    // Criando Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    // Inicializando SDL_ttf
    if(TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(-1);
    }
}

Engine::~Engine() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Engine::start(void render(), void update()){
    unsigned int fps_tick = 0;
    int frame = 0;

    while(run == true){
        unsigned int t0 = SDL_GetTicks();

        // Chamando função de atualização
        update();

        // Chamando função de renderização
        SDL_RenderClear(renderer);
        render();
        SDL_RenderPresent(renderer);

        // Calculando FPS
        unsigned int t1 = SDL_GetTicks();
        frame++;
        if (t1 >= fps_tick+1000){
            fps_tick = t1;
            fps = frame;
            frame = 0;
        }

        // Ajustando FPS conforme o limite especificado
        Engine::sleep(t0);
    }
}

void Engine::stop(){
    run = false;
}

bool Engine::isRunning(){
    return run;
}

int Engine::getFps(){
    return fps;
}

void Engine::sleep(unsigned int t0){
    if (FPS_LIMIT != 0){

        // Tempo em nanossegundos
        unsigned int delta = (SDL_GetTicks()-t0)*1e6;
        unsigned int ideal = 1e9/FPS_LIMIT;

        if (delta < ideal){
            timespec t;
            t.tv_sec = 0;
            t.tv_nsec = ideal-delta;
            nanosleep(&t, NULL);
        }
    }
}
