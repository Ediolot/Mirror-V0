//
// Created by jsier on 16/05/2019.
//

#ifndef MIRROR_APP_APP_H
#define MIRROR_APP_APP_H

#include <vector>
#include <thread>
#include <iostream>
#include <atomic>
#include "resourceLoaders/Fonts.h"
#include "resourceLoaders/Colors.h"
#include "utils/Utils.h"
#include "utils/FPSMetric.h"
#include "widgets/activity/BaseActivity.h"
#include "widgets/activity/ActivityFactory.h"

class App {
    static inline const int TICKS_PER_SECOND = 4;
    static inline const double TICK_TIME = 1.0 / TICKS_PER_SECOND;

    // Other vars
    int width;
    int height;
    std::atomic_bool quit;

    // Screens
    std::vector<BaseActivity*> activities;
    int mainActivityId;

    // For the controller loop
    // ALLEGRO_EVENT_QUEUE* drawingEventQ;
    // ALLEGRO_TIMER* drawingTimer;

    // For the drawing loop
    ALLEGRO_EVENT_QUEUE* drawingEventQ;
    ALLEGRO_TIMER* drawingTimer;
    ALLEGRO_DISPLAY* display;
    int targetViewFPS;
    FPSMetric fps;

    // General ALLEGRO vars
    ALLEGRO_EVENT_QUEUE* eventQ;

public:
    App();
    virtual ~App();

    void run();
    void updateViews();
    void updateControllers();
    void updateEvents();

private:
    // For each screen view, create a screen model + controller
    void loadActivities();
    bool startAllegroVars();
    void destroyAllegroVars();
};


#endif //MIRROR_APP_APP_H
