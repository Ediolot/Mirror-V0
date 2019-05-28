//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_IMAGEWIDGET_H
#define MIRROR_APP_IMAGEWIDGET_H


#include <allegro5/bitmap.h>
#include <mutex>
#include "../BaseWidget.h"

class ImageWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/imageWidget.xml";
    std::string imagePath;
    ALLEGRO_BITMAP *image;
    Properties::SCALE_TYPE scale;
    std::mutex mtx;

public:
    explicit ImageWidget(BaseWidget* parent = nullptr);
    virtual ~ImageWidget();
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void setImage(const std::string& path);
    void setModeFromStr(const std::string& modeStr);

protected:
    void parseViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_IMAGEWIDGET_H
