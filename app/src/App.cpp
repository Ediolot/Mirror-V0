//
// Created by jsier on 16/05/2019.
//

#include <tinydir.h>
#include "App.h"
#include "widgets/activity/ActivityFactory.h"
#include "resourceLoaders/Images.h"

App::App()
    : width(1280)
    , height(1024)
    , activities()
    , mainActivityId(-1)
    , quit(false)
    , drawingEventQ(nullptr)
    , drawingTimer(nullptr)
    , display(nullptr)
    , targetViewFPS(60)
    , fps()
    , eventQ(nullptr)
{
    Utils::startAllegro();
    startAllegroVars();
    Fonts::getInstance().load();
    Colors::getInstance().load();
    Images::getInstance().load();
}

App::~App() {
    destroyAllegroVars();
    for (BaseActivity* activity : activities) {
        delete activity;
    }
}

void App::run() {
    loadActivities();
    std::thread updaterController(&App::updateControllers, this);
    std::thread updaterEvents(&App::updateEvents, this);
    updateViews();
    updaterController.join();
    updaterEvents.join();
}

void App::updateEvents() {
    while (!quit.load()) {
        ALLEGRO_EVENT ev{};
        al_wait_for_event(eventQ, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: quit.store(true); break;
            default: break;
        }
    }
}

void App::updateViews() {
    fps.init();

    al_start_timer(drawingTimer);
    while (!quit.load()) {
        ALLEGRO_EVENT ev{};
        al_wait_for_event(drawingEventQ, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            fps.measure();
            al_clear_to_color(Colors::get(Colors::BLACK));
            if (mainActivityId > -1) {
                activities[mainActivityId]->updateView();
            }
            fps.draw();
            al_flip_display();
        }
    }
}

void App::updateControllers() {
    double lastUpdate = -1; // In seconds
    double elapsedRealTime = 0;
    double elapsedT = 0;
    double elapsedS = 0;
    double elapsedM = 0;
    double elapsedH = 0;
    double elapsedD = 0;

    // The biggest update rate should trigger all other updates
    activities[mainActivityId]->updateControllerInter(BaseWidget::UpdateRate::EACH_12HOUR);

    while (!quit.load()) {
        double update = al_get_time();
        elapsedRealTime = update - lastUpdate;

        if (mainActivityId > -1 && lastUpdate > 0) {
            BaseWidget::UpdateRate rate = BaseWidget::UpdateRate::NONE;
            elapsedT += elapsedRealTime;
            elapsedS += elapsedRealTime;
            elapsedM += elapsedRealTime;
            elapsedH += elapsedRealTime;
            elapsedD += elapsedRealTime;

            if (elapsedT > TICK_TIME) {
                elapsedT -= TICK_TIME;
                rate = BaseWidget::UpdateRate::EACH_TICK;
            }
            if (elapsedS > 1.0) {
                elapsedS -= 1.0;
                rate = BaseWidget::UpdateRate::EACH_SECOND;
            }
            if (elapsedM > 60.0) {
                elapsedM -= 60.0;
                rate = BaseWidget::UpdateRate::EACH_MINUTE;
            }
            if (elapsedH > 3600.0) {
                elapsedH -= 3600.0;
                rate = BaseWidget::UpdateRate::EACH_HOUR;
            }
            if (elapsedD > 3600.0 * 12.0) {
                elapsedH -= 3600.0 * 12.0;
                rate = BaseWidget::UpdateRate::EACH_12HOUR;
            }

            if (rate != BaseWidget::UpdateRate::NONE) {
                // TODO should be async
                activities[mainActivityId]->updateControllerInter(rate);
            }
            activities[mainActivityId]->updateControllerRT(elapsedRealTime);
        }
        lastUpdate = update;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void App::destroyAllegroVars() {
    if (display)       al_destroy_display(display);
    if (eventQ)        al_destroy_event_queue(eventQ);
    if (drawingEventQ) al_destroy_event_queue(drawingEventQ);
    if (drawingTimer)  al_destroy_timer(drawingTimer);
}

bool App::startAllegroVars() {
    bool ok = true;

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
    Utils::initAllegroModule("Allegro creating displays...", ok, [&](){
        display = al_create_display(width, height);
        return display;
    });
    Utils::initAllegroModule("Allegro creating timers...", ok, [&](){
        drawingTimer = al_create_timer(1.0 / targetViewFPS);
        return drawingTimer;
    });
    Utils::initAllegroModule("Allegro creating event queues...", ok, [&](){
        eventQ = al_create_event_queue();
        drawingEventQ = al_create_event_queue();
        return eventQ && drawingEventQ;
    });

    if (!ok) {
        destroyAllegroVars();
    } else {
        al_register_event_source(eventQ, al_get_display_event_source(display));
        al_register_event_source(drawingEventQ, al_get_timer_event_source(drawingTimer));
    }
    return ok;
}

void App::loadActivities() {
    assert(activities.empty());

    ActivityFactory factory;
    BaseActivity *activity = factory.createNext();

    while (activity) {
        activity->setWidth(width);
        activity->setHeight(height);
        activities.push_back(activity);
        activity = factory.createNext();
    }

    if (!activities.empty()) {
        mainActivityId = 0;
    }
}
