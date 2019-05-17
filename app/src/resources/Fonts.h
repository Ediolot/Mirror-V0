//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_FONTS_H
#define MIRROR_APP_FONTS_H

#include <allegro5/allegro_font.h>

class Fonts {
    static const int ELEMENTS = 1;
    static const int SIZES = 5;
    ALLEGRO_FONT* fonts[ELEMENTS * SIZES];
    
public:
    enum Rid {
        DEFAULT_FONT = 0,
    };

    enum Size {
        PX8 = 0, PX16 = 1, PX32 = 2, PX64 = 3, PX128 = 4
    };

    static Fonts& getInstance() {
        static Fonts x;
        return x;
    }

    static const ALLEGRO_FONT* get(Rid id, Size size = PX16) {
        return Fonts::getInstance().fonts[id + size];
    }

    Fonts(const Fonts&) = delete;
    Fonts(Fonts&&) = delete;
    void operator=(const Fonts&) = delete;
    void operator=(Fonts&&) = delete;

    bool load();
    void free();

private:
    Fonts();
    virtual ~Fonts();
};


#endif //MIRROR_APP_FONTS_H
