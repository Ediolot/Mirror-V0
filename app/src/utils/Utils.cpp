//
// Created by jsier on 30/03/2019.
//

#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "Utils.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <json.h>

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

void Utils::matToBitmapRGB888(const cv::Mat& mat, ALLEGRO_BITMAP* bitmap) {
    assert(mat.channels() == 3);
    assert(al_get_bitmap_format(bitmap) == ALLEGRO_PIXEL_FORMAT_RGB_888);
    int width = al_get_bitmap_width(bitmap);
    int height = al_get_bitmap_height(bitmap);
    ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_WRITEONLY);
    memcpy(region->data, mat.data, width * height * 3);
    al_unlock_bitmap(bitmap);
}

void Utils::initAllegroModule(const std::string msg, bool &ok, std::function<bool()> lambda) {
    if (ok) {
        std::cout << msg;
        ok = bool((lambda)());
        std::cout << (ok ? "[OK]" : "[FALSE]") << std::endl;
    }
}

bool Utils::startAllegro() {
    bool ok = true;

    initAllegroModule("Allegro init...", ok, [](){
        return bool(al_init());
    });
    initAllegroModule("Allegro primitives...", ok, [](){
        return al_init_primitives_addon();
    });
    initAllegroModule("Allegro audio...", ok, [](){
        return al_install_audio();
    });
    initAllegroModule("Allegro audio codec...", ok, [](){
        return al_init_acodec_addon();
    });
    initAllegroModule("Allegro image...", ok, [](){
        return al_init_image_addon();
    });
    initAllegroModule("Allegro reserve samples...", ok, [](){
        return al_reserve_samples(1);
    });
    initAllegroModule("Allegro font & ttf...", ok, [](){
        al_init_font_addon();
        al_init_ttf_addon();
        return true;
    });

    return ok;
}

std::string Utils::execCmd(const std::string &cmd) {
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

nlohmann::json Utils::requestJSON(const std::string& url) {
    const std::string CURL_CMD = "D:\\Programming\\Libs\\curl-7.65.0\\bin\\curl.exe -s"; // TODO
    std::string cmd = CURL_CMD + " " + "\"" + url + "\"";
    std::string output = execCmd(cmd);
    std::cout << cmd << "\n" << output << std::endl;
    return nlohmann::json::parse(output);
}