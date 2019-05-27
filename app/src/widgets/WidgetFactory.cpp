//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "WidgetFactory.h"
#include "user/TextWidget.h"
#include "user/ImageWidget.h"
#include "user/DatetimeWidget.h"

BaseWidget *WidgetFactory::create(Properties::TYPE type, BaseWidget* parent) {
    BaseWidget *widget = nullptr;
    switch(type) {
        case Properties::TYPE::TEXT: widget = new TextWidget(parent); break;
        case Properties::TYPE::IMAGE: widget = new ImageWidget(parent); break;
        case Properties::TYPE::DATETIME: widget = new DatetimeWidget(parent); break;
        default: return nullptr;
    }
    widget->loadDefaultView();
    return widget;
}
