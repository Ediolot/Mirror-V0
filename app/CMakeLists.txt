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

# add_executable(mirror_app src/main.cpp src/modules/screen/Screen.cpp src/modules/screen/Screen.h src/modules/opencv/VideoCam.cpp src/modules/opencv/VideoCam.h src/modules/utils/Utils.cpp src/modules/utils/Utils.h src/modules/widgets_old/basic/Widget.cpp src/modules/widgets_old/basic/Widget.h src/modules/widgets_old/DateTime.cpp src/modules/widgets_old/DateTime.h src/modules/widgets_old/basic/Text.cpp src/modules/widgets_old/basic/Text.h src/modules/resources/Fonts.cpp src/modules/resources/Fonts.h src/modules/resources/Colors.cpp src/modules/resources/Colors.h src/modules/utils/Size.h src/modules/widgets_old/basic/Layout.cpp src/modules/widgets_old/basic/Layout.h src/App.cpp src/App.h src/modules/utils/FPSMetric.cpp src/modules/utils/FPSMetric.h)
add_executable(mirror_app src/main.cpp src/utils/Utils.cpp src/utils/Utils.h src/resources/Fonts.cpp src/resources/Fonts.h src/resources/Colors.cpp src/resources/Colors.h src/App.cpp src/App.h src/utils/FPSMetric.cpp src/utils/FPSMetric.h src/widgets/activity/BaseActivity.cpp src/widgets/activity/BaseActivity.h src/widgets/activity/ActivityFactory.cpp src/widgets/activity/ActivityFactory.h src/widgets/activity/user/MainActivity.cpp src/widgets/activity/user/MainActivity.h src/external/tinyxml2/tinyxml2.cpp src/external/tinyxml2/tinyxml2.h src/widgets/WidgetFactory.cpp src/widgets/WidgetFactory.h src/widgets/BaseWidget.cpp src/widgets/BaseWidget.h src/widgets/user/TextWidget.cpp src/widgets/user/TextWidget.h src/utils/Value.cpp src/utils/Value.h)
target_include_directories(mirror_app PRIVATE ${ALLEGRO5_INCLUDE} ${TINYDIR_INCLUDE})
target_link_directories(mirror_app PRIVATE ${ALLEGRO5_LIB_DIR})
target_link_libraries(mirror_app ${ALLEGRO5_LIBS} ${OpenCV_LIBS})