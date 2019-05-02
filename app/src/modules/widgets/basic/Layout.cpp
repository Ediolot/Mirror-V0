//
// Created by jsier on 02/05/2019.
//

#include "Layout.h"

Layout::Layout(const Widget *parent, int x, int y, Size size, Size minSize)
    : Widget(parent, x, y, size, minSize)
    , widgets()
    , weights()
    , totalWeight(0)
{}

void Layout::addWidget(Widget *widget, double weight) {
    widgets.push_back(widget);
    weights.push_back(weight);
    totalWeight += weight;
    updateContents();
}

void Layout::draw() {
    for (Widget* widget : widgets) {
        widget->draw();
    }
}

HLayout::HLayout(const Widget *parent, int x, int y, Size size, Size minSize)
    : Layout(parent, x, y, size, minSize)
{}

void HLayout::updateContents() {
    for (Widget* widget : widgets) {
        widget->setH(1.0, true); // 100% Height
    }
}
