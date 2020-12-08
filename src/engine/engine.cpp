#include "../../include/engine/engine.h"

bool Engine::run = true;

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

    // Inicializando SDL_mixer
    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
    //     std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    //     exit(-1);
    // }
}

Engine::~Engine() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    // Mix_Quit();
    SDL_Quit();
}

void Engine::start(void render_function(), void event_function(SDL_Event e)){
    this->render_function = render_function;
    this->event_function = event_function;
    int rc = 0;

    // Criando e definindo atributo das threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Iniciando thread de renderização e de eventos de entrada
    rc = pthread_create(&thread_render, &attr, render, (void*)this);
    if (rc){
        std::cerr << "ERROR; return code from pthread_create() is " << rc << std::endl;
        exit(-1);
    }
    rc = pthread_create(&thread_event, &attr, event, (void*)this);
    if (rc){
        std::cerr << "ERROR; return code from pthread_create() is " << rc << std::endl;
        exit(-1);
    }

    // Destruindo objeto de atributo
    pthread_attr_destroy(&attr);
}

void Engine::join(){
    int rc = 0;

    // Aguardando a finalização das threads
    rc = pthread_join(thread_render, NULL);
    if (rc){
        std::cerr << "ERROR; return code from pthread_join() is " << rc << std::endl;
        exit(-1);
    }
    rc = pthread_join(thread_event, NULL);
    if (rc){
        std::cerr << "ERROR; return code from pthread_join() is " << rc << std::endl;
        exit(-1);
    }
}

void *Engine::render(void *instance){
    Engine *engine = (Engine*)instance;
    unsigned int fps_tick = 0;
    int frame = 0;

    while(run == true){
        unsigned int t0 = SDL_GetTicks();

        // Renderização
        SDL_RenderClear(engine->renderer);
        engine->render_function();
        SDL_RenderPresent(engine->renderer);

        unsigned int t1 = SDL_GetTicks();

        // Calculando FPS
        frame++;
        if (t1 >= fps_tick+1000){
            fps_tick = t1;
            engine->fps = frame;
            frame = 0;
        }

        // Ajustando FPS conforme o limite especificado
        Engine::sleep(t0);
    }

    pthread_exit(NULL);
}

void *Engine::event(void *instance){
    Engine *engine = (Engine*)instance;
    SDL_Event e;

    while(run == true){
        unsigned int t0 = SDL_GetTicks();

        // Tratando entradas
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                run = false;
            }

            engine->event_function(e);
        }

        // Ajustando FPS conforme o limite especificado
        Engine::sleep(t0);
    }

    pthread_exit(NULL);
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
