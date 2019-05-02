#ifndef MM_TEST_SCREEN_H
#define MM_TEST_SCREEN_H

#include <iostream>
#include <chrono>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Screen {
    ALLEGRO_TIMER* loopTimer;
    ALLEGRO_EVENT_QUEUE* eventQ;
    ALLEGRO_DISPLAY* display;

    bool debug;
    bool fullScreen;
    int width;
    int height;
    int targetFPS;
    int fps;

    const double FPS_UPDATE_S = 1.0;

public:
    Screen(int width, int height, int targetFPS = 30, bool debug = false, bool fullScreen = false);
    virtual ~Screen();

    bool startAllegro();
    void run();
    void draw(double elapsed);

private:
    void drawFPS();
    void destroy_allegro_vars();
};


#endif //MM_TEST_SCREEN_H
