//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_TEXTWIDGET_H
#define MIRROR_APP_TEXTWIDGET_H


#include "../BaseWidget.h"

class TextWidget : public BaseWidget {

    inline static const std::string DEFAULT_VIEW = "../views/textWidget.xml";
    std::string txt;

public:
    explicit TextWidget(BaseWidget* parent = nullptr);
    const std::string& getDefaultViewPath() const override;

protected:
    void parseViewOptions(XMLElement *element) override;
    void updateViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_TEXTWIDGET_H
