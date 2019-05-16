//
// Created by jsier on 16/05/2019.
//

#ifndef MIRROR_APP_APP_H
#define MIRROR_APP_APP_H

#include<vector>
#include<thread>
#include <iostream>
#include <atomic>
#include "modules/resources/Fonts.h"
#include "modules/utils/Utils.h"
#include "modules/resources/Colors.h"
#include "modules/screen/Screen.h"
#include "modules/utils/FPSMetric.h"

class App {
    ALLEGRO_TIMER* loopTimer;
    ALLEGRO_EVENT_QUEUE* eventQ;
    ALLEGRO_DISPLAY* display;

    int width;
    int height;
    int targetViewFPS;
    FPSMetric fps;

    std::vector<Screen> screens;
    int mainScreenId;

    std::atomic_bool quit;

public:
    App();
    virtual ~App();

    void run();
    void updateViews();
    void updateControllers();
    void updateEvents();

private:
    bool startAllegroVars();
    void destroyAllegroVars();
};


#endif //MIRROR_APP_APP_H
