#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
#include "engine.h"
#include "texture.h"

class Text {
private:
    Engine *engine;
    Texture *texture;
    Font *font;

    std::string text;
    SDL_Color color;
    int x;
    int y;

public:
    Text(Engine *engine, Font *font, std::string text);
    ~Text();

    void reloadTexture();

    void setColor(int r, int g, int b);
    void setColor(int r, int g, int b, int alpha);
    void setAlpha(int alpha);
    void setText(std::string text);
    void setFont(Font *font);
    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);

    void render();
};

#endif
