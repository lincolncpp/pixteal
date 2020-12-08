#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "pthread.h"
#include <iostream>
#include "engine.h"
#include "font.h"

class Engine;
class Font;

class Texture{
    friend class Text;

private:
    SDL_Texture *texture = nullptr;
    Engine *engine = nullptr;

    int src_width;
    int src_height;

    SDL_Rect rect;
    SDL_Rect clip;
    double angle = 0;
    SDL_Point center = {0, 0};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool ex = false;

    Texture();

public:
    Texture(Engine *engine, Font *font, const char *text, SDL_Color color);
    Texture(Engine *engine, const char *path);
    ~Texture();
    void free();

    void render();
    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
    void setWidth(int width);
    void setHeight(int height);
    void setRect(SDL_Rect rect);
    void setClip(SDL_Rect clip);
    void setAngle(double angle);
    void setCenter(SDL_Point center);
    void setFlip(SDL_RendererFlip flip);
    void setColor(int r, int g, int b);
    void setColor(int r, int g, int b, int alpha);
    void setAlpha(int alpha);
    void setBlendMode(SDL_BlendMode blend);
    int getSrcWidth();
    int getSrcHeight();
};

#endif
