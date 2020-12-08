#include "../../include/engine/text.h"

Text::Text(Engine *engine, Font *font, std::string text) {
    this->engine = engine;
    this->font = font;
    this->text = text;
    color = {255, 255, 255, 255};
    reloadTexture();
}

Text::~Text() {
    delete texture;
}

void Text::reloadTexture() {
    if (texture != nullptr) delete texture;
    texture = new Texture(engine, font, text.c_str(), color);
    texture->setX(x);
    texture->setY(y);
}

void Text::setColor(int r, int g, int b) {
    color.r = r;
    color.g = g;
    color.b = b;
    texture->setColor(r, g, b);
}

void Text::setColor(int r, int g, int b, int alpha) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = alpha;
    texture->setColor(r, g, b, alpha);
}

void Text::setAlpha(int alpha) {
    color.a = alpha;
    texture->setAlpha(color.a);
}

void Text::setText(std::string text) {
    if (this->text != text){
        this->text = text;
        reloadTexture();
    }
}

void Text::setFont(Font *font) {
    this->font = font;
    reloadTexture();
}

void Text::setX(int x){
    this->x = x;
    this->texture->setX(x);
}

void Text::setY(int y){
    this->y = y;
    this->texture->setY(y);
}

void Text::setPos(int x, int y){
    setX(x);
    setY(y);
}

void Text::render(){texture->render();}
