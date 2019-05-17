//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "WidgetFactory.h"

WidgetFactory::WidgetFactory()
        : mapping()
{
    mapping.insert(std::make_pair("datetime", DATETIME));
}

BaseWidget *WidgetFactory::create(WidgetFactory::Type type) {
    return new BaseWidget("");
}

BaseWidget *WidgetFactory::createFromName(const std::string &name) {
    if (name.empty()) { // TODO exception
        std::cerr << "Error invalid name" << std::endl;
    }
    return create(mapping.at(name)); // TODO Check if it does not exist
}
