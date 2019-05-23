//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include "BaseWidget.h"
#include "WidgetFactory.h"


BaseWidget::BaseWidget(const std::string &xmlView, BaseWidget* parent)
    : parent(parent)
    , children()
    , x(0)
    , y(0)
    , width(0)
    , height(0)
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
    XMLElement *widgets = doc.FirstChildElement("root")->FirstChildElement("children"); // TODO exception if not found
    for (XMLElement* widget = widgets->FirstChildElement(); widget; widget = widget->NextSiblingElement()) {
        factory.createFromName(widget->Attribute("type"), this);
    }

    XMLElement *options = doc.FirstChildElement("root")->FirstChildElement("options"); // TODO exception if not found
    x = toValue(options, "pos", "x");
    y = toValue(options, "pos", "y");
    width = toValue(options, "size", "width");
    height = toValue(options, "size", "height");
    padding = toValue(options, "padding", "value");

    parseOtherViewOptions(options);
}

void BaseWidget::clearView() {
    for (BaseWidget *widget : children) {
        delete widget;
    }
}

void BaseWidget::parseOtherViewOptions(XMLElement *options) {
    ;
}

Value BaseWidget::toValue(XMLElement *options, const char *node, const char *attribute,
                          double defaultValue, Value::Type defaultType) const {

    double value = defaultValue;
    Value::Type type = defaultType;

    XMLElement* element = options->FirstChildElement(node);
    if (!element) {
        return Value(value, type);
    }

    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return Value(value, type);
    }

    int len = strlen(attributeStr);
    if (len > 3 && attributeStr[len - 1] == 'x' && attributeStr[len - 2] == 'p') {
        type = Value::Type::PERCENT;
    } else {
        type = Value::Type::NUMERIC;
    }

    value = strtod(attributeStr, nullptr);
    return Value(value, type);
}

std::string BaseWidget::toString(XMLElement *options, const char *node, const std::string &defaultValue) const {
    XMLElement* element = options->FirstChildElement(node);
    if (!element) {
        return defaultValue;
    }
    return element->GetText();
}
