//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_IMAGES_H
#define MIRROR_APP_IMAGES_H


#include <allegro5/bitmap.h>

class Images {
public:
    enum Rid {
        LENNA = 0,
        WEATHER_CLOUDS,
        WEATHER_FULL_NIGHT,
        WEATHER_FULL_SUNNY,
        WEATHER_NIGHT,
        WEATHER_RAINY,
        WEATHER_RAINY_THUNDER,
        WEATHER_SNOWY,
        WEATHER_SNOWY_RAINY,
        WEATHER_SUN,
        N_IMAGES
    };

private:
    ALLEGRO_BITMAP* bitmaps[N_IMAGES];

public:
    static Images& getInstance() {
        static Images x;
        return x;
    }

    static const ALLEGRO_BITMAP* get(Rid id) {
        return Images::getInstance().bitmaps[id];
    }

    Images(const Images&) = delete;
    Images(Images&&) = delete;
    void operator=(const Images&) = delete;
    void operator=(Images&&) = delete;

    bool load();
    void free();

private:
    Images();
    virtual ~Images();
};


#endif //MIRROR_APP_IMAGES_H
