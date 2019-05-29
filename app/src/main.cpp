#include <iostream>
#include <opencv2/core.hpp>
#include "utils/Utils.h"
#include "App.h"
#include "utils/Requester.h"
#include <typeinfo>

int main(int argc, char** argv) {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    std::cout << "Allegro Version: " << Utils::allegroVersion() << std::endl;

    Requester::start();
    App app;
    app.run();
    Requester::end();

    return 0;
}