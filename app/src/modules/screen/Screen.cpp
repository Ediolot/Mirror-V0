#include "Screen.h"

Screen::Screen(int width, int height, int targetFPS, bool debug, bool fullScreen)
    : loopTimer(nullptr)
    , eventQ(nullptr)
    , display(nullptr)
    , defaultFont(nullptr)
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
    if (display)   al_destroy_display(display);
    if (eventQ)    al_destroy_event_queue(eventQ);
    if (loopTimer) al_destroy_timer(loopTimer);
}

bool Screen::startAllegro() {
    bool ok = true;

    INIT("Allegro init...", ok, [](){
        return al_init();
    });
    INIT("Allegro primitives...", ok, [](){
        return al_init_primitives_addon();
    });
    INIT("Allegro audio...", ok, [](){
        return al_install_audio();
    });
    INIT("Allegro audio codec...", ok, [](){
        return al_init_acodec_addon();
    });
    INIT("Allegro reserve samples...", ok, [](){
        return al_reserve_samples(1);
    });
    INIT("Allegro font & ttf...", ok, [](){
        al_init_font_addon();
        al_init_ttf_addon();
        return true;
    });
    INIT("Allegro loading fonts...", ok, [&](){
        defaultFont = al_load_font("../files/Ubuntu-Regular.ttf", 16, 0);
        return defaultFont;
    });
    INIT("Allegro creating timers...", ok, [&](){
        loopTimer = al_create_timer(1.0 / targetFPS);
        return loopTimer;
    });
    INIT("Allegro creating event queues...", ok, [&](){
        eventQ = al_create_event_queue();
        return eventQ;
    });
    INIT("Allegro creating displays...", ok, [&](){
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
            al_clear_to_color(al_map_rgb(0,0,0));
            draw(elapsed);
            // Draw fps over (if debug)
            drawFPS();
            // Change buffer
            al_flip_display();
        }
    }
}

void Screen::draw(double elapsed) {
    // Elapsed counts the elapsed time from the last frame. So, even when the framerate changes
    // the square will move at the same speed (sx, sy)
    // Only for example purposes, do not use static variables here !
    static double sx = 100;
    static double sy = 100;
    static double x = 0;
    static double y = 0;
    const double w = 100;
    const double h = 100;
    al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(200,200,255));

    x += sx * elapsed;
    y += sy * elapsed;
    if ((x+w) > width) {
        x = (width - w);
        sx *= -1;
    }
    if ((y+h) > height) {
        y = (height - h);
        sy *= -1;
    }
    if (x < 0) {
        x = 0;
        sx *= -1;
    }
    if (y < 0) {
        y = 0;
        sy *= -1;
    }
}

void Screen::drawFPS() {
    std::string txt = "FPS: " + std::to_string(fps);
    al_draw_text(defaultFont, al_map_rgb(255,255,255), 10, 10, ALLEGRO_ALIGN_LEFT, txt.c_str());
}
