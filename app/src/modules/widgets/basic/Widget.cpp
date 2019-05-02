//
// Created by jsier on 02/05/2019.
//

#include <cassert>
#include "Widget.h"

Widget::Widget(const Widget *parent, int x, int y, Size size, Size minSize)
    : parent(parent)
    , x(x)
    , y(y)
    , size(size)
    , minSize(minSize)
{
    assert(parent != nullptr || !(size.percentageW || size.percentageH)); // Cant use percentages without parent
}

void Widget::setSize(Size size) {
    this->size = size;
}

void Widget::setW(double w, bool percentage) {
    size.w = w;
    size.percentageW = percentage;
}

void Widget::setH(double h, bool percentage) {
    size.h = h;
    size.percentageH = percentage;
}

void Widget::setMinSize(Size minSize) {
    this->minSize = minSize;
}

void Widget::setMinW(double w, bool percentage) {
    minSize.w = w;
    minSize.percentageW = percentage;
}

void Widget::setMinH(double h, bool percentage) {
    minSize.h = h;
    minSize.percentageH = percentage;
}

Size Widget::getSize() const {
    return size;
}

Size Widget::getMinSize() const {
    return minSize;
}
