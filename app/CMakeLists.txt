cmake_minimum_required(VERSION 3.13)
project(mirror_app)

set(CMAKE_CXX_STANDARD 17)

# ALLEGRO 5
set(ALLEGRO5_INCLUDE D:/Programming/Libs/allegro-5.2.5.1/include)
set(ALLEGRO5_LIB_DIR D:/Programming/Libs/allegro-5.2.5.1/lib)
set(ALLEGRO5_LIBS allegro_monolith-debug)

# OPENCV 4
find_package(OpenCV REQUIRED HINTS "D:/Programming/Libs/opencv-4.0.1")

# TINYDIR
set(TINYDIR_INCLUDE D:/Programming/Libs/tinydir)

# JSON
set(JSON_INCLUDE D:/Programming/Libs/nlohmann)

# CURL
set(CURL_INCLUDE D:/Programming/Libs/curl-7.65.0/include)
set(CURL_LIB_DIR D:/Programming/Libs/curl-7.65.0/lib)
set(CURL_LIBS libcurl)

add_executable(mirror_app src/main.cpp src/utils/Utils.cpp src/utils/Utils.h src/resourceLoaders/Fonts.cpp src/resourceLoaders/Fonts.h src/resourceLoaders/Colors.cpp src/resourceLoaders/Colors.h src/App.cpp src/App.h src/utils/FPSMetric.cpp src/utils/FPSMetric.h src/widgets/activity/BaseActivity.cpp src/widgets/activity/BaseActivity.h src/widgets/activity/ActivityFactory.cpp src/widgets/activity/ActivityFactory.h src/widgets/activity/user/MainActivity.cpp src/widgets/activity/user/MainActivity.h src/external/tinyxml2/tinyxml2.cpp src/external/tinyxml2/tinyxml2.h src/widgets/WidgetFactory.cpp src/widgets/WidgetFactory.h src/widgets/BaseWidget.cpp src/widgets/BaseWidget.h src/widgets/user/TextWidget.cpp src/widgets/user/TextWidget.h src/utils/Value.cpp src/utils/Value.h src/widgets/user/ImageWidget.cpp src/widgets/user/ImageWidget.h src/resourceLoaders/Images.cpp src/resourceLoaders/Images.h src/widgets/user/DatetimeWidget.cpp src/widgets/user/DatetimeWidget.h src/widgets/Properties.cpp src/widgets/Properties.h src/widgets/user/WeatherWidget.cpp src/widgets/user/WeatherWidget.h src/widgets/user/NewsWidget.cpp src/widgets/user/NewsWidget.h src/utils/RunOnceAsync.cpp src/utils/RunOnceAsync.h src/utils/Requester.cpp src/utils/Requester.h src/widgets/user/SolarSystemWidget.cpp src/widgets/user/SolarSystemWidget.h)
target_include_directories(mirror_app PRIVATE ${ALLEGRO5_INCLUDE} ${TINYDIR_INCLUDE} ${JSON_INCLUDE} ${CURL_INCLUDE})
target_link_directories(mirror_app PRIVATE ${ALLEGRO5_LIB_DIR} ${CURL_LIB_DIR})
target_link_libraries(mirror_app ${ALLEGRO5_LIBS} ${OpenCV_LIBS} ${CURL_LIBS})