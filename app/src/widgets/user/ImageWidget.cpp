//
// Created by jsier on 26/05/2019.
//

#include <allegro5/allegro.h>
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

    std::string imagePath = toString(element->FirstChildElement("path"), "value");
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
    image = al_load_bitmap(path.c_str());
}
