//
// Created by jsier on 16/05/2019.
//

#ifndef MIRROR_APP_APP_H
#define MIRROR_APP_APP_H

#include <vector>
#include <thread>
#include <iostream>
#include <atomic>
#include "modules/resources/Fonts.h"
#include "modules/utils/Utils.h"
#include "modules/resources/Colors.h"
#include "modules/utils/FPSMetric.h"
#include "widgets/base/Widget.h"

inline std::string const VIEWS_PATH = "../views/";

class App {

    // Other vars
    int width;
    int height;
    std::atomic_bool quit;

    // Screens
    std::vector<Widget*> screens;
    int mainScreenId;

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
    void loadScreens();
    bool startAllegroVars();
    void destroyAllegroVars();
};


#endif //MIRROR_APP_APP_H
