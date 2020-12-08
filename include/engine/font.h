#ifndef FONT_H
#define FONT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>

class Font {
    friend class Texture;

private:
   TTF_Font *font = nullptr;
   std::string path;
   int size;

   void loadFont(const char *path, int size);

public:
   Font(const char *path, int size);
   ~Font();
   void free();

   void setSize(int size);
};

#endif
