#include <iostream>
#include <opencv2/core.hpp>
#include "modules/screen/Screen.h"
#include "modules/utils/Utils.h"
#include "modules/resources/Fonts.h"
#include "modules/resources/Colors.h"

int main(int argc, char** argv) {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Allegro Version: " << Utils::allegroVersion() << std::endl;

    const int FPS = 80;
    const int WIDTH = 640;
    const int HEIGHT = 480;

    Utils::startAllegro();
    Fonts::getInstance().load();
    Colors::getInstance().load();

    Screen screen(WIDTH, HEIGHT, FPS);

    if (!screen.startAllegro()) {
        return -1;
    }

    screen.run();

    return 0;
}