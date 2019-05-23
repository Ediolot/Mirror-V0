//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_TEXTWIDGET_H
#define MIRROR_APP_TEXTWIDGET_H


#include "../BaseWidget.h"

class TextWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/textWidget.xml";

private:
    std::string txt;

public:
    explicit TextWidget(const std::string& xmlView = DEFAULT_VIEW, BaseWidget* parent = nullptr);

protected:
    void parseOtherViewOptions(XMLElement *options) override;
};


#endif //MIRROR_APP_TEXTWIDGET_H
