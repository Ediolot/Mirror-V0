//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_LAYOUT_H
#define MIRROR_APP_LAYOUT_H


#include <vector>
#include "Widget.h"

class Layout : public Widget {
protected:
    std::vector<Widget*> widgets;
    std::vector<double> weights;
    double totalWeight;

public:
    explicit Layout(const Widget* parent = nullptr, int x = 0, int y = 0, Size size = Size(-1, -1), Size minSize = Size(-1, -1));
    void addWidget(Widget* widget, double weight = 1);
    void draw() override;

private:
    virtual void updateContents() = 0;
};

class HLayout : public Layout {
public:
    explicit HLayout(const Widget* parent = nullptr, int x = 0, int y = 0, Size size = Size(-1, -1), Size minSize = Size(-1, -1));

private:
    void updateContents() override;
};


#endif //MIRROR_APP_LAYOUT_H
