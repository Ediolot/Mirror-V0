//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_ACTIVITYFACTORY_H
#define MIRROR_APP_ACTIVITYFACTORY_H


#include <string>
#include "BaseActivity.h"

class ActivityFactory {
    int nextActivityIdx;

public:
    enum Type {
        MAIN_ACTIVITY,
    };

    ActivityFactory();

    BaseActivity* create(Type type);
    BaseActivity* createNext();
};

inline const ActivityFactory::Type ACTIVITIES[] = {
        ActivityFactory::Type::MAIN_ACTIVITY,
};

#endif //MIRROR_APP_ACTIVITYFACTORY_H


