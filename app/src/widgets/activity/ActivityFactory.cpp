//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "ActivityFactory.h"
#include "user/MainActivity.h"

ActivityFactory::ActivityFactory()
        : nextActivityIdx(0)
{}

BaseActivity *ActivityFactory::create(ActivityFactory::Type type) {
    BaseActivity *activity = nullptr;
    switch(type) {
        case Type::MAIN_ACTIVITY: activity = new MainActivity(); break;
        default: return nullptr;
    }
    activity->loadDefaultView();
    return activity;
}

BaseActivity *ActivityFactory::createNext() {
    int max = std::extent<decltype(ACTIVITIES)>::value;

    if (nextActivityIdx < max) {
        return create(ACTIVITIES[nextActivityIdx++]);
    }
    return nullptr;
}
