//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_WIDGET_H
#define MIRROR_APP_WIDGET_H


class Widget {
    int x;
    int y;
    int w;
    int h;

public:
    virtual void draw() = 0; // Should be const
    virtual void update() = 0;
};


#endif //MIRROR_APP_WIDGET_H
