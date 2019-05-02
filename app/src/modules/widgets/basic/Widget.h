//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_WIDGET_H
#define MIRROR_APP_WIDGET_H


#include "../../utils/Size.h"

class Widget {
protected:
    const Widget *parent;
    int x;
    int y;
    Size size;
    Size minSize;

public:
    explicit Widget(const Widget* parent = nullptr, int x = 0, int y = 0, Size size = Size(-1, -1), Size minSize = Size(-1, -1));

    virtual void draw(){}; // Should be const
    virtual void update(){};

    void setSize(Size size);
    void setW(double w, bool percentage = false);
    void setH(double h, bool percentage = false);
    void setMinSize(Size minSize);
    void setMinW(double w, bool percentage = false);
    void setMinH(double h, bool percentage = false);

    Size getSize() const;
    Size getMinSize() const;
};


#endif //MIRROR_APP_WIDGET_H
