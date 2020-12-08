#include "../../include/engine/font.h"

Font::Font(const char *path, int size) {
    this->path = path;
    this->size = size;
    loadFont(path, size);
}

Font::~Font() {
    free();
}

void Font::free() {
    if (font != nullptr){
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void Font::loadFont(const char *path, int size) {
    free();

    // Carregando fonte .ttfs
    font = TTF_OpenFont(path, size);
    if (font == nullptr){
        std::cerr << "Error on loading font! TTF_Error: " << TTF_GetError() << std::endl;
        exit(-1);
    }
}

void Font::setSize(int size) {
    loadFont(path.c_str(), size);
}
