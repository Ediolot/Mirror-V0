//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_TEXT_H
#define MIRROR_APP_TEXT_H


#include <string>
#include <allegro5/allegro_font.h>

class Text {
    ALLEGRO_FONT* font;
    std::string txt;
    int x;
    int y;
    int align;
};


#endif //MIRROR_APP_TEXT_H
