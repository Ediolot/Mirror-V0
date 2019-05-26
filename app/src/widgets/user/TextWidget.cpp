//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "TextWidget.h"

TextWidget::TextWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , txt("")
{}

void TextWidget::parseViewOptions(XMLElement *element) {
    BaseWidget::parseViewOptions(element);

    txt = toString(element->FirstChildElement("text"), "value");
    // TODO parse font
}

void TextWidget::updateViewOptions(XMLElement *element) {
    BaseWidget::updateViewOptions(element);

    txt = toString(element, "value", txt);
    // TODO font
}

const std::string& TextWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}
