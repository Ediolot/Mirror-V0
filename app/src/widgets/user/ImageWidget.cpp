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
    , imagePath("")
    , image(nullptr)
    , scale(Properties::SCALE_TYPE::SCALE_ALL)
{}

ImageWidget::~ImageWidget() {
    al_destroy_bitmap(image);
}

const std::string &ImageWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void ImageWidget::parseViewOptions(XMLElement *element) {
    BaseWidget::parseViewOptions(element);

    imagePath = Properties::Parser::string(element, "path", imagePath);
    scale = Properties::Parser::scaleType(element, "scale", scale);
    setImage(imagePath);
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

    switch (scale) {
        default: break;
        case Properties::SCALE_TYPE::SCALE_ALL: break;
        case Properties::SCALE_TYPE::SCALE_FIT:
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
        case Properties::SCALE_TYPE::SCALE_EXPAND:
            // TODO
            break;
    }
    al_draw_scaled_bitmap(image, 0, 0, bw, bh, dx, dy, dw, dh, 0);
}
