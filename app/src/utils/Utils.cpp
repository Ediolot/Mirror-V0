//
// Created by jsier on 30/03/2019.
//

#include "Utils.h"

std::string Utils::allegroVersion() {
    uint32_t version = al_get_allegro_version();
    int major    = version >> 24;
    int minor    = (version >> 16) & 255;
    int revision = (version >> 8) & 255;
    int release  = version & 255;

    return std::to_string(major)    + "." +
           std::to_string(minor)    + "." +
           std::to_string(revision) + "." +
           std::to_string(release);
}


void matToBitmapRGB888(const cv::Mat& mat, ALLEGRO_BITMAP* bitmap) {
    assert(mat.channels() == 3);
    assert(al_get_bitmap_format(bitmap) == ALLEGRO_PIXEL_FORMAT_RGB_888);
    int width = al_get_bitmap_width(bitmap);
    int height = al_get_bitmap_height(bitmap);
    ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_WRITEONLY);
    memcpy(region->data, mat.data, width * height * 3);
    al_unlock_bitmap(bitmap);
}