//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "WidgetFactory.h"
#include "user/TextWidget.h"
#include "user/ImageWidget.h"
#include "user/DatetimeWidget.h"
#include "user/WeatherWidget.h"
#include "user/NewsWidget.h"
#include "user/SolarSystemWidget.h"

BaseWidget *WidgetFactory::create(Properties::TYPE type, BaseWidget* parent) {
    BaseWidget *widget = nullptr;
    switch(type) {
        case Properties::TYPE::TEXT: widget = new TextWidget(parent); break;
        case Properties::TYPE::IMAGE: widget = new ImageWidget(parent); break;
        case Properties::TYPE::DATETIME: widget = new DatetimeWidget(parent); break;
        case Properties::TYPE::WEATHER: widget = new WeatherWidget(parent); break;
        case Properties::TYPE::NEWS: widget = new NewsWidget(parent); break;
        case Properties::TYPE::SOLAR_SYSTEM: widget = new SolarSystemWidget(parent); break;
        default: return nullptr;
    }
    widget->loadDefaultView();
    return widget;
}
