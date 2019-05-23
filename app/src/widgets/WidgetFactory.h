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
        DATETIME,
        TEXT,
    };

private:
    std::map<std::string, Type> mapping;

public:
    WidgetFactory();

    BaseWidget* createFromName(const std::string& name, BaseWidget* parent = nullptr);
    BaseWidget* create(Type type, BaseWidget* parent = nullptr);
};


#endif //MIRROR_APP_WIDGETFACTORY_H
