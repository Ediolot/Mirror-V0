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
        fonts[DEFAULT_FONT + PX8]   = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 8, 0);
        fonts[DEFAULT_FONT + PX16]  = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 16, 0);
        fonts[DEFAULT_FONT + PX24]  = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 24, 0);
        fonts[DEFAULT_FONT + PX32]  = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 32, 0);
        fonts[DEFAULT_FONT + PX40]  = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 40, 0);
        fonts[DEFAULT_FONT + PX64]  = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 64, 0);
        fonts[DEFAULT_FONT + PX128] = al_load_font("../resources/fonts/Ubuntu-Regular.ttf", 128, 0);

        // Check if all fonts are ok
        for (auto &font : fonts) {
            if (font == nullptr) {
                return false;
            }
        }
        return true;
    });

    return ok;
}

void Fonts::free() {
    for (auto &font : fonts) {
        al_destroy_font(font);
    }
}
