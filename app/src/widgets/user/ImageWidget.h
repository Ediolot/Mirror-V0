//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_IMAGEWIDGET_H
#define MIRROR_APP_IMAGEWIDGET_H


#include <allegro5/bitmap.h>
#include "../BaseWidget.h"

class ImageWidget : public BaseWidget {
public:
    enum FillType {
        SCALE_FIT = 0,
        SCALE_ALL = 1,
        SCALE_EXPAND = 2,
    };

private:
    inline static const std::string DEFAULT_VIEW = "../views/imageWidget.xml";
    ALLEGRO_BITMAP *image;
    FillType mode;
    int backgroundR;
    int backgroundG;
    int backgroundB;

public:
    explicit ImageWidget(BaseWidget* parent = nullptr);
    virtual ~ImageWidget();
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void setImage(const std::string& path);
    void setModeFromStr(const std::string& modeStr);

protected:
    void parseViewOptions(XMLElement *element) override;
    void updateViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_IMAGEWIDGET_H
