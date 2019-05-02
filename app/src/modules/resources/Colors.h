//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_COLORS_H
#define MIRROR_APP_COLORS_H


#include <allegro5/color.h>

class Colors {
    static const int ELEMENTS = 3;
    ALLEGRO_COLOR colors[ELEMENTS];

public:
    enum Rid {
        WHITE = 0,
        BLACK = 1,
        CYAN  = 2,
    };

    static Colors& getInstance() {
        static Colors x;
        return x;
    }

    static const ALLEGRO_COLOR get(Rid id) {
        return Colors::getInstance().colors[id];
    }

    Colors(const Colors&) = delete;
    Colors(Colors&&) = delete;
    void operator=(const Colors&) = delete;
    void operator=(Colors&&) = delete;

    bool load();

private:
    Colors();
    virtual ~Colors();
};


#endif //MIRROR_APP_COLORS_H
