//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_BASECOMPONENT_H
#define MIRROR_APP_BASECOMPONENT_H

#include <string>
#include <vector>
#include "../external/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class BaseWidget {
protected:
    std::vector<BaseWidget*> widgets;

    double x;
    double y;
    double width; // Target width
    double height; // Target height
    double p_width;
    double p_height;
    double padding;

public:
    explicit BaseWidget(const std::string& xmlView);
    virtual ~BaseWidget();

    void loadView(const std::string& xmlView);
    void clearView();

protected:
    virtual void parseOtherViewOptions(XMLElement *options);
};


#endif //MIRROR_APP_BASECOMPONENT_H
