#include "../../include/engine/texture.h"

Texture::Texture(Engine *engine, Font *font, const char *text, SDL_Color color) {
    this->engine = engine;
    free();

    // Criando textura a partir da fonte e do texto dado
    SDL_Surface *text_surface = TTF_RenderText_Blended(font->font, text, color);
    if (text_surface == nullptr){
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(-1);
    }
    texture = SDL_CreateTextureFromSurface(engine->renderer, text_surface);
    if (texture == nullptr){
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    src_width = text_surface->w;
    src_height = text_surface->h;
    rect = clip = {0, 0, src_width, src_height};

    SDL_FreeSurface(text_surface);
    text_surface = nullptr;
}

Texture::Texture(Engine *engine, const char *path) {
    this->engine = engine;
    free();

    // Carregando textura
    texture = IMG_LoadTexture(engine->renderer, path);
    if (texture == nullptr){
        std::cerr << "Error on loading texture! IMG_Error: " << IMG_GetError() << std::endl;
        exit(-1);
    }

    // Obtendo dimensões da textura carregada
    int real_width, real_height;
    SDL_QueryTexture(texture, nullptr, nullptr, &real_width, &real_height);
    src_width = real_width;
    src_height = real_height;
    rect = clip = {0, 0, src_width, src_height};
}

Texture::~Texture() {
    free();
}

void Texture::free() {
    if (texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Texture::render(){
    if (ex) SDL_RenderCopyEx(engine->renderer, texture, &clip, &rect, angle, &center, flip);
    else SDL_RenderCopy(engine->renderer, texture, &clip, &rect);
}

void Texture::setX(int x){rect.x = x;}
void Texture::setY(int y){rect.y = y;}
void Texture::setPos(int x, int y){rect.x = x, rect.y = y;}
void Texture::setWidth(int width){rect.w = width;}
void Texture::setHeight(int height){rect.h = height;}
void Texture::setRect(SDL_Rect rect){this->rect = rect;}
void Texture::setClip(SDL_Rect clip){this->clip = clip, ex = true;}
void Texture::setAngle(double angle){this->angle = angle, ex = true;}
void Texture::setCenter(SDL_Point center){this->center = center, ex = true;}
void Texture::setFlip(SDL_RendererFlip flip){this->flip = flip, ex = true;}

void Texture::setColor(int r, int g, int b) {
    SDL_SetTextureColorMod(texture, r, g, b);
}
void Texture::setColor(int r, int g, int b, int alpha){
    setColor(r, g, b);
    setAlpha(alpha);
}
void Texture::setAlpha(int alpha){
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setBlendMode(SDL_BlendMode blend) {
    SDL_SetTextureBlendMode(texture, blend);
}

int Texture::getSrcWidth() {return src_width;}
int Texture::getSrcHeight() {return src_height;}
