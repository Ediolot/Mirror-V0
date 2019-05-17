//
// Created by jsier on 16/05/2019.
//

#include <allegro5/altime.h>
#include <string>
#include <allegro5/allegro_font.h>
#include "FPSMetric.h"
#include "../resources/Fonts.h"
#include "../resources/Colors.h"

void FPSMetric::init() {
    start = al_get_time();
    frames = 0;
    elapsed = 0;
    fps = 0;
}

void FPSMetric::measure() {
    frames++;
    end = al_get_time();
    elapsed = (end - start) / frames; // Elapsed time since last frame
    if ((elapsed * frames) > FPS_UPDATE_S) {
        fps = int(1 / elapsed);
        start = end;
        frames = 0;
    }
}

int FPSMetric::value() {
    return fps;
}

void FPSMetric::draw() const {
    std::string txt = "FPS: " + std::to_string(fps);
    al_draw_text(Fonts::get(Fonts::DEFAULT_FONT), Colors::get(Colors::WHITE), 10, 10, ALLEGRO_ALIGN_LEFT, txt.c_str());
}
