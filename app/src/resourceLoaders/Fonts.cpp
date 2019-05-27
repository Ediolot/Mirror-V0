//
// Created by jsier on 02/05/2019.
//

#include <iostream>
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
        loadSingle(DEFAULT_FONT, "../resources/fonts/Ubuntu-Regular.ttf");
        //loadSingle(ICO_FONT, "../resources/fonts/icofont.ttf");

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

void Fonts::loadSingle(Fonts::Rid rid, const char *path) {
    fonts[rid * N_FONTS_SIZES + PX8]   = al_load_font(path, 8, 0);
    fonts[rid * N_FONTS_SIZES + PX16]  = al_load_font(path, 16, 0);
    fonts[rid * N_FONTS_SIZES + PX24]  = al_load_font(path, 24, 0);
    fonts[rid * N_FONTS_SIZES + PX32]  = al_load_font(path, 32, 0);
    fonts[rid * N_FONTS_SIZES + PX40]  = al_load_font(path, 40, 0);
    fonts[rid * N_FONTS_SIZES + PX64]  = al_load_font(path, 64, 0);
    fonts[rid * N_FONTS_SIZES + PX128] = al_load_font(path, 128, 0);
}
