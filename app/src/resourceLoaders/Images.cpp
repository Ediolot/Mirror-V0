//
// Created by jsier on 26/05/2019.
//

#include "Images.h"
#include "../utils/Utils.h"

Images::Images()
    : bitmaps()
{
    for (auto &bitmap : bitmaps) {
        bitmap = nullptr;
    }
}

Images::~Images() {
    free();
}

bool Images::load() {
    bool ok = true;

    Utils::initAllegroModule("Allegro loading images...", ok, [&](){
        bitmaps[LENNA] = al_load_bitmap("../resources/images/lenna.png");

        // Check if all fonts are ok
        for (auto &bitmap : bitmaps) {
            if (bitmap == nullptr) {
                return false;
            }
        }
        return true;
    });

    return ok;
}

void Images::free() {
    for (auto &bitmap : bitmaps) {
        al_destroy_bitmap(bitmap);
    }
}