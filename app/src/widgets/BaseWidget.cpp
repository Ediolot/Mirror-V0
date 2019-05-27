//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include <sstream>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "BaseWidget.h"
#include "WidgetFactory.h"


BaseWidget::BaseWidget(BaseWidget* parent)
    : id("")
    , parent(parent)
    , children()
    , x(0)
    , y(0)
    , width(0)
    , height(0)
    , padding(2)
    , background(Colors::get(Colors::EMPTY))
    , vAlign(Properties::ALIGN::TOP)
    , hAlign(Properties::ALIGN::LEFT)
{}

BaseWidget::~BaseWidget() {
    clearView();
}

void BaseWidget::loadView(const std::string &xmlView) {
    if (xmlView.empty()) {
        return;
    }
    XMLDocument doc;
    doc.LoadFile(xmlView.c_str());

    // ---- Load children and modify their viewing options as specified in this view file ----
    WidgetFactory factory;
    XMLElement *widgets = doc.FirstChildElement("root")->FirstChildElement("children"); // TODO exception if not found
    for (XMLElement* widget = widgets->FirstChildElement(); widget; widget = widget->NextSiblingElement()) {
        Properties::TYPE childType = Properties::Parser::type(widget, "type", Properties::TYPE::NONE);
        BaseWidget *child = factory.create(childType, this);
        child->parseViewOptions(widget);
        children.push_back(child);
    }
}

void BaseWidget::clearView() {
    for (BaseWidget *widget : children) {
        delete widget;
    }
}

void BaseWidget::parseViewOptions(XMLElement *element) {
    id         = Properties::Parser::string(element, "id", id);
    x          = Properties::Parser::value(element, "x", x);
    y          = Properties::Parser::value(element, "y", y);
    width      = Properties::Parser::value(element, "width", width);
    height     = Properties::Parser::value(element, "height", height);
    padding    = Properties::Parser::value(element, "padding", padding);
    background = Properties::Parser::color(element, "background", background);
    vAlign     = Properties::Parser::align(element, "valign", vAlign);
    hAlign     = Properties::Parser::align(element, "halign", hAlign);
}

void BaseWidget::loadDefaultView() {
    loadView(getDefaultViewPath());
}

void BaseWidget::updateView() {
    if (parent) {
        // If it has a parent, calculate reference variables using it
        rX      = parent->rX + x.calculate(parent->rWidth) + padding.getDouble();
        rY      = parent->rY + y.calculate(parent->rHeight) + padding.getDouble();
        rWidth  = width.calculate(parent->rWidth) - padding.getDouble() * 2;
        rHeight = height.calculate(parent->rHeight) - padding.getDouble() * 2;
    } else {
        rX      = x.getDouble() + padding.getDouble();
        rY      = y.getDouble() + padding.getDouble();
        rWidth  = width.getDouble() - padding.getDouble() * 2;
        rHeight = height.getDouble() - padding.getDouble() * 2;
    }
    if (hAlign == Properties::ALIGN::CENTER) {
        rX -= rWidth / 2;
    }
    else if (hAlign == Properties::ALIGN::RIGHT) {
        rX -= rWidth;
    }
    if (vAlign == Properties::ALIGN::CENTER) {
        rY -= rHeight / 2;
    }
    else if (vAlign == Properties::ALIGN::BOTTOM) {
        rY -= rHeight;
    }

    if (!Colors::isEmpty(background)) {
        al_draw_filled_rectangle(rX, rY, rX + rWidth, rY + rHeight, background);
    }
    for (BaseWidget* child : children) {
        child->updateView();
    }
}

void BaseWidget::setWidth(double value, Value::Type type) {
    width = Value(value, type);
}

void BaseWidget::setHeight(double value, Value::Type type) {
    height = Value(value, type);
}

const std::string& BaseWidget::getId() const {
    return id;
}

BaseWidget *BaseWidget::getChild(const std::string& childId) {
    for (BaseWidget *child : children) {
        if (child->getId() == childId) {
            return child;
        }
    }
    std::cerr << "CHILD " << childId << " not found!" << std::endl;
    return nullptr;
}

void BaseWidget::updateControllerRT(double elapsed) {
    for (BaseWidget *child : children) {
        child->updateControllerRT(elapsed);
    }
}

void BaseWidget::updateControllerInter(UpdateRate rate) {
    for (BaseWidget *child : children) {
        child->updateControllerInter(rate);
    }
}

bool BaseWidget::rateIs(BaseWidget::UpdateRate rate, BaseWidget::UpdateRate reference) const {
    return rate >= reference;
}
