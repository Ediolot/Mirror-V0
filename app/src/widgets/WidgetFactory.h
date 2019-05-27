//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_WIDGETFACTORY_H
#define MIRROR_APP_WIDGETFACTORY_H


#include <map>
#include "BaseWidget.h"

class WidgetFactory {
public:
    BaseWidget* create(Properties::TYPE type, BaseWidget* parent = nullptr);
};


#endif //MIRROR_APP_WIDGETFACTORY_H
