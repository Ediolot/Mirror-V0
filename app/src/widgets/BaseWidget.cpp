//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include <sstream>
#include "BaseWidget.h"
#include "WidgetFactory.h"


BaseWidget::BaseWidget(BaseWidget* parent)
    : parent(parent)
    , children()
    , x(0)
    , y(0)
    , width(0)
    , height(0)
    , padding(0)
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

    // ---- Parse (normally default) view options for this widget from the view file ----
    XMLElement *options = doc.FirstChildElement("root")->FirstChildElement("options"); // TODO exception if not found
    parseViewOptions(options);

    // ---- Load children and modify their viewing options as specified in this view file ----
    WidgetFactory factory;
    XMLElement *widgets = doc.FirstChildElement("root")->FirstChildElement("children"); // TODO exception if not found
    for (XMLElement* widget = widgets->FirstChildElement(); widget; widget = widget->NextSiblingElement()) {
        BaseWidget *child = factory.createFromName(widget->Attribute("type"), this);
        child->updateViewOptions(widget);
        children.push_back(child);
    }
}

void BaseWidget::clearView() {
    for (BaseWidget *widget : children) {
        delete widget;
    }
}

void BaseWidget::parseViewOptions(XMLElement *element) {
    x = toValue(element->FirstChildElement("pos"), "x");
    y = toValue(element->FirstChildElement("pos"), "y");
    width = toValue(element->FirstChildElement("size"), "width");
    height = toValue(element->FirstChildElement("size"), "height");
    padding = toValue(element->FirstChildElement("padding"), "value");
}

void BaseWidget::updateViewOptions(XMLElement *element) {
    x = toValue(element, "x", x);
    y = toValue(element, "y", y);
    width = toValue(element, "width", width);
    height = toValue(element, "height", height);
    padding = toValue(element, "padding", padding);
}

Value BaseWidget::toValue(XMLElement *element, const char *attribute,
                          double defaultValue, Value::Type defaultType) const {

    double value = defaultValue;
    Value::Type type = defaultType;

    if (!element) {
        return Value(value, type);
    }

    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return Value(value, type);
    }

    int len = strlen(attributeStr);
    value = strtod(attributeStr, nullptr);
    if (len > 3 && attributeStr[len - 1] == 'x' && attributeStr[len - 2] == 'p') {
        type = Value::Type::NUMERIC;
    } else {
        type = Value::Type::PERCENT;
        value /= 100.0;
    }

    return Value(value, type);
}

int BaseWidget::toInt(XMLElement *element, const char *attribute, int defaultValue) const {
    if (!element) {
        return defaultValue;
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return defaultValue;
    }
    return strtol(attributeStr, nullptr, 10);
}

std::string BaseWidget::toString(XMLElement *element, const char *attribute, const std::string &defaultValue) const {
    if (!element) {
        return defaultValue;
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return defaultValue;
    }
    return std::string(attributeStr);
}

Value BaseWidget::toValue(XMLElement *element, const char *attribute, const Value& value) const {
    return toValue(element, attribute, value.getDouble(), value.getType());
}

void BaseWidget::loadDefaultView() {
    loadView(getDefaultViewPath());
}

void BaseWidget::updateView() {
    if (parent) {
        rX = parent->rX + x.calculate(parent->rWidth) + padding.getDouble();
        rY = parent->rY + y.calculate(parent->rHeight) + padding.getDouble();
        rWidth = width.calculate(parent->rWidth) - padding.getDouble() * 2;
        rHeight = height.calculate(parent->rHeight) - padding.getDouble() * 2;
    } else {
        rX = x.getDouble() + padding.getDouble();
        rY = y.getDouble() + padding.getDouble();
        rWidth = width.getDouble() - padding.getDouble() * 2;
        rHeight = height.getDouble() - padding.getDouble() * 2;
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
