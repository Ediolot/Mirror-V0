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
        bitmaps[LENNA]                 = al_load_bitmap("../resources/images/lenna.png");
        bitmaps[WEATHER_CLOUDS]        = al_load_bitmap("../resources/images/weather/clouds.png");
        bitmaps[WEATHER_NIGHT_AND_CLOUDS]    = al_load_bitmap("../resources/images/weather/full-night.png");
        bitmaps[WEATHER_SUN_AND_CLOUDS]    = al_load_bitmap("../resources/images/weather/full-sunny.png");
        bitmaps[WEATHER_NIGHT]         = al_load_bitmap("../resources/images/weather/night.png");
        bitmaps[WEATHER_RAINY]         = al_load_bitmap("../resources/images/weather/rainy.png");
        bitmaps[WEATHER_RAINY_THUNDER] = al_load_bitmap("../resources/images/weather/rainy-thunder.png");
        bitmaps[WEATHER_SNOWY]         = al_load_bitmap("../resources/images/weather/snowy.png");
        bitmaps[WEATHER_SNOWY_RAINY]   = al_load_bitmap("../resources/images/weather/snowy-rainy.png");
        bitmaps[WEATHER_SUN]           = al_load_bitmap("../resources/images/weather/sun-alt.png");

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