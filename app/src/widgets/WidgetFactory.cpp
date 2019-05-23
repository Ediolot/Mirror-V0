//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "WidgetFactory.h"
#include "user/TextWidget.h"

WidgetFactory::WidgetFactory()
        : mapping()
{
    mapping.insert(std::make_pair("datetime", DATETIME));
    mapping.insert(std::make_pair("text", TEXT));
}

BaseWidget *WidgetFactory::create(WidgetFactory::Type type, BaseWidget* parent) {
    if (type == TEXT) return new TextWidget(, parent);
    return nullptr;
}

BaseWidget *WidgetFactory::createFromName(const std::string &name, BaseWidget* parent) {
    if (name.empty()) { // TODO exception
        std::cerr << "Error invalid name" << std::endl;
    }
    return create(mapping.at(name)); // TODO Check if it does not exist
}
