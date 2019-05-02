//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_FONTS_H
#define MIRROR_APP_FONTS_H

#include <allegro5/allegro_font.h>

class Fonts {
    static const int ELEMENTS = 1;
    ALLEGRO_FONT* fonts[ELEMENTS];
    
public:
    enum Rid {
        DEFAULT_FONT = 0,
    };

    static Fonts& getInstance() {
        static Fonts x;
        return x;
    }

    static const ALLEGRO_FONT* get(Rid id) {
        return Fonts::getInstance().fonts[id];
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
