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
    const void draw_multiline(double x, double y, ALLEGRO_USTR *ustr, int flags);

    const ALLEGRO_USTR *ustr_split_next(const ALLEGRO_USTR *ustr,
                                        ALLEGRO_USTR_INFO *info, int *pos, const char *delimiter);

    const ALLEGRO_USTR *get_next_soft_line(const ALLEGRO_USTR *ustr,
                                           ALLEGRO_USTR_INFO *info, int *pos,
                                           const ALLEGRO_FONT *font, float max_width);

protected:
    void parseViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_TEXTWIDGET_H
