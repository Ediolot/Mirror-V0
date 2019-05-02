//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_WIDGET_H
#define MIRROR_APP_WIDGET_H


#include "../utils/Size.h"

class Widget {
    const Widget *parent;
    int x;
    int y;
    Size size;

public:
    Widget(const Widget* parent, int x, int y, Size size);

    virtual void draw() = 0; // Should be const
    virtual void update() = 0;

    void setSize(Size size);
    void setW(double w, bool percentage = false);
    void setH(double h, bool percentage = false);
};


#endif //MIRROR_APP_WIDGET_H
