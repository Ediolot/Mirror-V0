//
// Created by jsier on 02/05/2019.
//

#include "Text.h"

Text::Text(std::string txt, const ALLEGRO_FONT *font, ALLEGRO_COLOR color, int x, int y, Align hAlign, Align vAlign)
    : color(color)
    , font(font)
    , txt(std::move(txt))
    , x(x), y(y)
    , hAlign(hAlign)
    , vAlign(vAlign)
{}

void Text::draw() {
    int alignedY = y;
    int fontHeight = getHeight();
    if (vAlign == DOWN) {
        alignedY -= fontHeight;
    }
    if (vAlign == CENTER) {
        alignedY -= fontHeight / 2;
    }

    al_draw_text(font, color, x, alignedY, hAlign, txt.c_str());
}

void Text::setText(std::string txt) {
    this->txt = std::move(txt);
}

int Text::getHeight() const {
    return al_get_font_line_height(font);
}
