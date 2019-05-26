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

    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
    ALLEGRO_PATH *p = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_set_path_filename(p, "lenna.png");
    image = al_load_bitmap(al_path_cstr(p, '/'));
    std::cout << al_path_cstr(p, '/') << " " << image << std::endl;
    al_destroy_path(p);
}

void ImageWidget::updateView() {
    BaseWidget::updateView();
    al_draw_bitmap(image, rX, rY, 0);
}
