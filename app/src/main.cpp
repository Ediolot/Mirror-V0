#include <iostream>
#include <opencv2/core.hpp>
#include "modules/screen/Screen.h"
#include "modules/utils/Utils.h"
#include "modules/resources/Fonts.h"
#include "modules/resources/Colors.h"
#include "App.h"


int main(int argc, char** argv) {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Allegro Version: " << Utils::allegroVersion() << std::endl;

    App app;
    app.run();

    /*const int FPS = 80;
    const int WIDTH = 640;
    const int HEIGHT = 480;

    Screen screen(WIDTH, HEIGHT, FPS);

    if (!screen.startAllegro()) {
        return -1;
    }

    screen.run();*/

    return 0;
}