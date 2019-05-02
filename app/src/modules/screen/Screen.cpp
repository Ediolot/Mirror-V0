#include "Screen.h"
#include "../utils/Utils.h"
#include "../resources/Fonts.h"
#include "../resources/Colors.h"
#include "../widgets/DateTime.h"
#include "../widgets/basic/Layout.h"

Screen::Screen(int width, int height, int targetFPS, bool debug, bool fullScreen)
    : loopTimer(nullptr)
    , eventQ(nullptr)
    , display(nullptr)
    , debug(debug)
    , fullScreen(fullScreen)
    , width(width)
    , height(height)
    , targetFPS(targetFPS)
    , fps(0)
{}

Screen::~Screen() {
    destroy_allegro_vars();
}

void Screen::destroy_allegro_vars() {
    if (display)     al_destroy_display(display);
    if (eventQ)      al_destroy_event_queue(eventQ);
    if (loopTimer)   al_destroy_timer(loopTimer);
}

bool Screen::startAllegro() {
    bool ok = true;

    Utils::initAllegroModule("Allegro creating timers...", ok, [&](){
        loopTimer = al_create_timer(1.0 / targetFPS);
        return loopTimer;
    });
    Utils::initAllegroModule("Allegro creating event queues...", ok, [&](){
        eventQ = al_create_event_queue();
        return eventQ;
    });
    Utils::initAllegroModule("Allegro creating displays...", ok, [&](){
        display = al_create_display(width, height);
        return display;
    });

    if (!ok) {
        destroy_allegro_vars();
    } else {
        al_register_event_source(eventQ, al_get_display_event_source(display));
        al_register_event_source(eventQ, al_get_timer_event_source(loopTimer));
    }
    return ok;
}

void Screen::run() {
    bool redraw = true;
    bool quit = false;

    double start = al_get_time();
    double end;
    int frames = 0;
    double elapsed = 0;

    al_start_timer(loopTimer);
    while (!quit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQ, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_TIMER: redraw = true; break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE: quit = true; break;
        }

        if (redraw && al_event_queue_is_empty(eventQ)) {
            // FPS measurement
            frames++;
            end = al_get_time();
            elapsed = (end - start) / frames; // Elapsed time since last frame
            if ((elapsed * frames) > FPS_UPDATE_S) {
                fps = int(1 / elapsed);
                start = end;
                frames = 0;
            }
            // Draw screen
            redraw = false;
            al_clear_to_color(Colors::get(Colors::BLACK));
            draw(elapsed);
            // Draw fps over (if debug)
            drawFPS();
            // Change buffer
            al_flip_display();
        }
    }
}

void Screen::draw(double elapsed) {
    static HLayout dt(nullptr, 0, 0, Size(100, 10));
    static bool first = true;

    if (first) {
        dt.addWidget(new Text("asd", Fonts::get(Fonts::DEFAULT_FONT), Colors::get(Colors::WHITE)));
        dt.addWidget(new Text("xyz", Fonts::get(Fonts::DEFAULT_FONT), Colors::get(Colors::WHITE)));
        first = false;
    }
    dt.draw();
}

void Screen::drawFPS() {
    std::string txt = "FPS: " + std::to_string(fps);
    //al_draw_text(Fonts::get(Fonts::DEFAULT_FONT), Colors::get(Colors::WHITE), 10, 10, ALLEGRO_ALIGN_LEFT, txt.c_str());
}
