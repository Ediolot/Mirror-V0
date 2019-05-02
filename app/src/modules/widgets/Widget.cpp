//
// Created by jsier on 02/05/2019.
//

#include "Widget.h"

Widget::Widget(const Widget *parent, int x, int y, Size size)
    : parent(parent)
    , x(x)
    , y(y)
    , size(size)
{}

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
