//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "WidgetFactory.h"
#include "user/TextWidget.h"
#include "user/ImageWidget.h"

WidgetFactory::WidgetFactory()
        : mapping()
{
    mapping.insert(std::make_pair("datetime", DATETIME));
    mapping.insert(std::make_pair("text", TEXT));
    mapping.insert(std::make_pair("image", IMAGE));
}

BaseWidget *WidgetFactory::create(WidgetFactory::Type type, BaseWidget* parent) {
    BaseWidget *widget = nullptr;
    switch(type) {
        case Type::TEXT: widget = new TextWidget(parent); break;
        case Type::IMAGE: widget = new ImageWidget(parent); break;
        default: return nullptr;
    }
    widget->loadDefaultView();
    return widget;
}

BaseWidget *WidgetFactory::createFromName(const std::string &name, BaseWidget* parent) {
    if (name.empty()) { // TODO exception
        std::cerr << "Error invalid name" << std::endl;
    }
    return create(mapping.at(name)); // TODO Check if it does not exist
}
