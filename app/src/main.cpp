#include <iostream>
#include <opencv2/core.hpp>
#include "utils/Utils.h"
#include "App.h"

int main(int argc, char** argv) {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Allegro Version: " << Utils::allegroVersion() << std::endl;

    App app;
    app.run();

    return 0;
}