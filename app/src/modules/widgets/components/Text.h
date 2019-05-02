//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_TEXT_H
#define MIRROR_APP_TEXT_H


#include <string>
#include <allegro5/allegro_font.h>

enum Align {
    LEFT = ALLEGRO_ALIGN_LEFT,
    RIGHT = ALLEGRO_ALIGN_RIGHT,
    CENTER = ALLEGRO_ALIGN_CENTER,
    TOP,
    DOWN,
};

class Text {
    const ALLEGRO_FONT* font;
    std::string txt;
    ALLEGRO_COLOR color;
    int x;
    int y;
    int hAlign;
    int vAlign;

public:
    Text(std::string txt, const ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x = 0, int y = 0, Align hAlign = LEFT, Align vAlign = TOP);
    void draw();
    void setText(std::string txt);
    int getHeight() const;
};


#endif //MIRROR_APP_TEXT_H
