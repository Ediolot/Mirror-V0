//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_IMAGES_H
#define MIRROR_APP_IMAGES_H


#include <allegro5/bitmap.h>

class Images {
    static const int ELEMENTS = 1;
    ALLEGRO_BITMAP* bitmaps[ELEMENTS];

public:
    enum Rid {
        LENNA = 0,
    };

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
