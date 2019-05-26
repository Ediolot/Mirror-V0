//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_IMAGEWIDGET_H
#define MIRROR_APP_IMAGEWIDGET_H


#include <allegro5/bitmap.h>
#include "../BaseWidget.h"

class ImageWidget : public BaseWidget {

    inline static const std::string DEFAULT_VIEW = "../views/imageWidget.xml";
    ALLEGRO_BITMAP *image;
    std::string mode;

public:
    explicit ImageWidget(BaseWidget* parent = nullptr);
    virtual ~ImageWidget();
    const std::string& getDefaultViewPath() const override;
    void setImage(const std::string& path);

protected:
    void parseViewOptions(XMLElement *element) override;
    void updateViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_IMAGEWIDGET_H
