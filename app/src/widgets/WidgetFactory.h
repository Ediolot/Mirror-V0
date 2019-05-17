//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_WIDGETFACTORY_H
#define MIRROR_APP_WIDGETFACTORY_H


#include <map>
#include "BaseWidget.h"

class WidgetFactory {
public:
    enum Type {
        DATETIME ,
    };

private:
    std::map<std::string, Type> mapping;

public:
    WidgetFactory();

    BaseWidget* createFromName(const std::string& name);
    BaseWidget* create(Type type);
};


#endif //MIRROR_APP_WIDGETFACTORY_H
