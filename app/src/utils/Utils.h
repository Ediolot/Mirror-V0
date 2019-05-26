//
// Created by jsier on 30/03/2019.
//

#ifndef MM_TEST_UTILS_H
#define MM_TEST_UTILS_H

#include <cstdint>
#include <string>
#include <cassert>
#include <allegro5/allegro.h>
#include <opencv2/core.hpp>
#include <json.h>

namespace Utils {
    std::string allegroVersion();
    void matToBitmapRGB888(const cv::Mat& mat, ALLEGRO_BITMAP* bitmap);
    void initAllegroModule(const std::string msg, bool &ok, std::function<bool()> lambda);
    bool startAllegro();
    std::string execCmd(const std::string &cmd);
    nlohmann::json requestJSON(const std::string& url);
}


#endif //MM_TEST_UTILS_H
