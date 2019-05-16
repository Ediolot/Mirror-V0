//
// Created by jsier on 16/05/2019.
//

#include "App.h"

App::App()
    : loopTimer(nullptr)
    , eventQ(nullptr)
    , display(nullptr)
    , width(640)
    , height(480)
    , targetViewFPS(60)
    , fps()
    , screens()
    , mainScreenId(0)
    , quit(false)
{
    // screens.emplace_back(640, 480, 80); // Example main screen

    Utils::startAllegro();
    Fonts::getInstance().load();
    Colors::getInstance().load();
}

App::~App() {
    destroyAllegroVars();
}

void App::run() {
    startAllegroVars();
    std::thread updaterView(&App::updateViews, this);
    std::thread updaterController(&App::updateControllers, this);
    // std::thread updaterEvents(&App::updateEvents, this);
    updaterView.join();
    updaterController.join();
}

void App::updateEvents() {
    // In case there is a need to separate drawing from the events
}

void App::updateViews() {
    bool redraw = true;

    bool ok = true;
    Utils::initAllegroModule("Allegro creating displays...", ok, [&](){
        display = al_create_display(width, height);
        return display;
    });
    al_register_event_source(eventQ, al_get_display_event_source(display));

    fps.init();

    al_start_timer(loopTimer);
    while (!quit.load()) {
        ALLEGRO_EVENT ev{};
        al_wait_for_event(eventQ, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_TIMER: redraw = true; break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE: quit.store(true); break;
            default: break;
        }

        if (redraw && al_event_queue_is_empty(eventQ)) {
            fps.measure();
            al_clear_to_color(Colors::get(Colors::BLACK));
            // screens[mainScreenId].updateViews();
            fps.draw();
            al_flip_display();
            redraw = false;
        }
    }
}

void App::updateControllers() {
    double lastUpdate = -1; // In seconds

    while (!quit.load()) {
        double update = al_get_time();
        double elapsed = update - lastUpdate;
        if (lastUpdate > 0) {
            //std::cout << "controllers " << elapsed << std::endl;
        }
        lastUpdate = update;
    }
}

void App::destroyAllegroVars() {
    if (display)     al_destroy_display(display);
    if (eventQ)      al_destroy_event_queue(eventQ);
    if (loopTimer)   al_destroy_timer(loopTimer);
}

bool App::startAllegroVars() {
    bool ok = true;

    Utils::initAllegroModule("Allegro creating timers...", ok, [&](){
        loopTimer = al_create_timer(1.0 / targetViewFPS);
        return loopTimer;
    });
    Utils::initAllegroModule("Allegro creating event queues...", ok, [&](){
        eventQ = al_create_event_queue();
        return eventQ;
    });

    if (!ok) {
        destroyAllegroVars();
    } else {
        al_register_event_source(eventQ, al_get_timer_event_source(loopTimer));
    }
    return ok;
}
