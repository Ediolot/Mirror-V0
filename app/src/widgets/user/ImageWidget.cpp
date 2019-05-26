//
// Created by jsier on 26/05/2019.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include "ImageWidget.h"

ImageWidget::ImageWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , image(nullptr)
    , mode("")
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
    mode = toString(element->FirstChildElement("mode"), "value");
    setImage(imagePath);
}

void ImageWidget::updateViewOptions(XMLElement *element) {
    BaseWidget::updateViewOptions(element);

    std::string imagePath = toString(element, "path");
    mode = toString(element, "mode", mode);
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

    const char* t =  "lenna.png";
    image = al_load_bitmap(t);
    std::cout << t << " " << image << std::endl;
}

void ImageWidget::updateView() {
    BaseWidget::updateView();
    al_draw_bitmap(image, rX, rY, 0);
}
