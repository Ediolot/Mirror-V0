//
// Created by jsier on 26/05/2019.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include "ImageWidget.h"
#include "../../resourceLoaders/Colors.h"

ImageWidget::ImageWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , image(nullptr)
    , mode(SCALE_ALL)
    , backgroundR(-1)
    , backgroundG(-1)
    , backgroundB(-1)
{}

ImageWidget::~ImageWidget() {
    al_destroy_bitmap(image);
}

const std::string &ImageWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void ImageWidget::parseViewOptions(XMLElement *element) {
    BaseWidget::parseViewOptions(element);

    std::string imagePath = toString(element->FirstChildElement("path"), "value");
    std::string modeStr = toString(element->FirstChildElement("mode"), "value", "scale_all");
    backgroundR = toInt(element->FirstChildElement("background"), "r", -1);
    backgroundG = toInt(element->FirstChildElement("background"), "g", -1);
    backgroundB = toInt(element->FirstChildElement("background"), "b", -1);
    setImage(imagePath);
    setModeFromStr(modeStr);
}

void ImageWidget::updateViewOptions(XMLElement *element) {
    BaseWidget::updateViewOptions(element);

    std::string imagePath = toString(element, "path");
    std::string modeStr = toString(element, "mode");
    backgroundR = toInt(element, "r", backgroundR);
    backgroundG = toInt(element, "g", backgroundG);
    backgroundB = toInt(element, "b", backgroundB);
    setImage(imagePath);
    setModeFromStr(modeStr);
}

void ImageWidget::setImage(const std::string &path) {
    if (path.empty()) {
        return;
    }
    // TODO lock
    if (image) {
        al_destroy_bitmap(image);
    }
    image = al_load_bitmap(path.c_str());
}

void ImageWidget::updateView() {
    BaseWidget::updateView();

    double bw = al_get_bitmap_width(image);
    double bh = al_get_bitmap_height(image);
    double dx = rX;
    double dy = rY;
    double dw = rWidth;
    double dh = rHeight;

    double ratioW = dw / bw;
    double ratioH = dh / bh;
    bool shortOnWidth = ratioW > ratioH;

    switch (mode) {
        case SCALE_ALL: break;
        case SCALE_FIT:
            if (shortOnWidth) {
                dx += dw / 2.0;
                dw = bw * ratioH;
                dx -= dw / 2.0;
            } else {
                dy += dh / 2.0;
                dh = bh * ratioW;
                dy -= dh / 2.0;
            }
            break;
        case SCALE_EXPAND:
            // TODO
            break;
    }
    if (backgroundR >= 0 && backgroundG >= 0 && backgroundB >= 0) {
        ALLEGRO_COLOR color = al_map_rgb(backgroundR, backgroundG, backgroundB);
        al_draw_filled_rectangle(rX, rY, rX + rWidth, rY + rHeight, color);
    }
    al_draw_scaled_bitmap(image, 0, 0, bw, bh, dx, dy, dw, dh, 0);
}

void ImageWidget::setModeFromStr(const std::string &modeStr) {
    if (modeStr == "scale_all" || modeStr == "SCALE_ALL") {
        mode = SCALE_ALL;
    } else if (modeStr == "scale_fit" || modeStr == "SCALE_FIT") {
        mode = SCALE_FIT;
    } else if (modeStr == "scale_expand" || modeStr == "SCALE_EXPAND") {
        mode = SCALE_EXPAND;
    }
}
