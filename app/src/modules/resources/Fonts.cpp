//
// Created by jsier on 02/05/2019.
//

#include "Fonts.h"
#include "../utils/Utils.h"

Fonts::Fonts()
    : fonts()
{
    for (auto &font : fonts) {
        font = nullptr;
    }
}

Fonts::~Fonts() {
    free();
}

bool Fonts::load() {
    bool ok = true;

    Utils::initAllegroModule("Allegro loading fonts...", ok, [&](){
        fonts[DEFAULT_FONT] = al_load_font("../files/Ubuntu-Regular.ttf", 16, 0);
        return fonts[DEFAULT_FONT];
    });

    return ok;
}

void Fonts::free() {
    for (auto &font : fonts) {
        al_destroy_font(font);
    }
}
