//
// Created by jsier on 02/05/2019.
//

#include "Colors.h"

Colors::Colors()
    : colors()
{}

Colors::~Colors() {}

bool Colors::load() {

    colors[WHITE] = al_map_rgb(255, 255, 255);
    colors[BLACK] = al_map_rgb(0, 0, 0);
    colors[CYAN] = al_map_rgb(0, 176, 246);

    return true;
}
