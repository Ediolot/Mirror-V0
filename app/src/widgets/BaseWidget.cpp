//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "BaseWidget.h"
#include "WidgetFactory.h"


BaseWidget::BaseWidget(const std::string &xmlView)
    : widgets()
    , x(0)
    , y(0)
    , width(0)
    , height(0)
    , p_width(0)
    , p_height(0)
    , padding(0)
{
    loadView(xmlView);
}

BaseWidget::~BaseWidget() {
    clearView();
}

void BaseWidget::loadView(const std::string &xmlView) {
    if (xmlView.empty()) {
        return;
    }

    XMLDocument doc;
    doc.LoadFile(xmlView.c_str());

    WidgetFactory factory;
    XMLElement *children = doc.FirstChildElement("root")->FirstChildElement("children"); // TODO exception if not found
    for (XMLElement* child = children->FirstChildElement(); child; child = child->NextSiblingElement()) {
        factory.createFromName(child->Attribute("type"));
    }

    XMLElement *options = doc.FirstChildElement("root")->FirstChildElement("options"); // TODO exception if not found
    /*x = strtod(options->FirstChildElement("pos")->Attribute("x", "0"), nullptr);
    y = strtod(options->FirstChildElement("pos")->Attribute("y", "0"), nullptr);
    width = strtod(options->FirstChildElement("size")->Attribute("width", "0"), nullptr);
    height = strtod(options->FirstChildElement("size")->Attribute("height", "0"), nullptr);
    padding = strtod(options->FirstChildElement("size")->Attribute("padding", "0"), nullptr);*/

    parseOtherViewOptions(options);
}

void BaseWidget::clearView() {
    for (BaseWidget *widget : widgets) {
        delete widget;
    }
}

void BaseWidget::parseOtherViewOptions(XMLElement *options) {
    ;
}
