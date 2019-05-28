//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_TEXTWIDGET_H
#define MIRROR_APP_TEXTWIDGET_H


#include <allegro5/allegro_font.h>
#include <mutex>
#include "../BaseWidget.h"
#include "../../resourceLoaders/Fonts.h"

class TextWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/textWidget.xml";
    std::string txt;
    Fonts::Rid fontFamily;
    Fonts::Size fontSize;
    Properties::ALIGN alignment;
    std::mutex mtx;

public:
    explicit TextWidget(BaseWidget* parent = nullptr);
    virtual ~TextWidget() = default;
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void setText(const std::string& newTxt);

private:
    std::string drawTextLine(double x, double y, std::string txt, const std::string& end = "") const;

protected:
    void parseViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_TEXTWIDGET_H
