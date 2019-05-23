//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "TextWidget.h"

TextWidget::TextWidget(const std::string &xmlView, BaseWidget *parent)
    : BaseWidget(xmlView, parent)
    , txt("")
{}

void TextWidget::parseOtherViewOptions(XMLElement *options) {
    txt = toString(options, "text");
    std::cout << "txt: " << txt << std::endl;
}
