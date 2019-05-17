//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_TEXTWIDGET_H
#define MIRROR_APP_TEXTWIDGET_H


#include "../BaseWidget.h"

class TextWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/";
public:
    explicit TextWidget(const std::string& xmlView, const std::string& txt);
};


#endif //MIRROR_APP_TEXTWIDGET_H
