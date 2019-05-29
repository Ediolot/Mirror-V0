//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_COLORS_H
#define MIRROR_APP_COLORS_H

#include <allegro5/color.h>

class Colors {
public:
    enum Rid {
        WHITE = 0,
        BLACK,
        GREY,
        CYAN,
        GOLDEN_YELLOW,
        SUMMER_SKY,
        PELOROUS,
        CASPER,
        KOURNIKOVA,
        APACHE,
        GOLDEN_TAINOI,
        ROB_ROY,
        BERMUDA,
        TRADE_WIND,
        JELLY_BEAN,
        VICKING,
        SPUN_PEARL,
        RUBY,
        CARDINAL,
        FALLOW,
        MEDIUM_WOOD,
        PALE_TAUPE,
        EMPTY,
        N_COLORS
    };

private:
    ALLEGRO_COLOR colors[N_COLORS];

public:
    static Colors& getInstance() {
        static Colors x;
        return x;
    }

    static const ALLEGRO_COLOR& get(Rid id) {
        return Colors::getInstance().colors[id];
    }

    static const bool isEmpty(const ALLEGRO_COLOR& color) {
        return !memcmp(&color, &get(Colors::EMPTY), sizeof(ALLEGRO_COLOR));
    }

    Colors(const Colors&) = delete;
    Colors(Colors&&) = delete;
    void operator=(const Colors&) = delete;
    void operator=(Colors&&) = delete;

    bool load();

private:
    Colors();
    virtual ~Colors() = default;
};


#endif //MIRROR_APP_COLORS_H
