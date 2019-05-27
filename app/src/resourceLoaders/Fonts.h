//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_FONTS_H
#define MIRROR_APP_FONTS_H

#include <allegro5/allegro_font.h>

class Fonts {
public:
    enum Rid {
        DEFAULT_FONT = 0,
        N_FONTS,
    };

    enum Size {
        PX8 = 0, PX16, PX24, PX32, PX40, PX64, PX128,
        N_FONTS_SIZES,
    };

private:
    ALLEGRO_FONT* fonts[N_FONTS * N_FONTS_SIZES];

public:
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
