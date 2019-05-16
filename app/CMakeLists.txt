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

# add_executable(mirror_app src/main.cpp src/modules/screen/Screen.cpp src/modules/screen/Screen.h src/modules/opencv/VideoCam.cpp src/modules/opencv/VideoCam.h src/modules/utils/Utils.cpp src/modules/utils/Utils.h src/modules/widgets/basic/Widget.cpp src/modules/widgets/basic/Widget.h src/modules/widgets/DateTime.cpp src/modules/widgets/DateTime.h src/modules/widgets/basic/Text.cpp src/modules/widgets/basic/Text.h src/modules/resources/Fonts.cpp src/modules/resources/Fonts.h src/modules/resources/Colors.cpp src/modules/resources/Colors.h src/modules/utils/Size.h src/modules/widgets/basic/Layout.cpp src/modules/widgets/basic/Layout.h src/App.cpp src/App.h src/modules/utils/FPSMetric.cpp src/modules/utils/FPSMetric.h)
add_executable(mirror_app src/main.cpp src/modules/utils/Utils.cpp src/modules/utils/Utils.h src/modules/resources/Fonts.cpp src/modules/resources/Fonts.h src/modules/resources/Colors.cpp src/modules/resources/Colors.h src/App.cpp src/App.h src/modules/utils/FPSMetric.cpp src/modules/utils/FPSMetric.h src/widgets/base/Widget.cpp src/widgets/base/Widget.h src/widgets/base/WidgetView.cpp src/widgets/base/WidgetView.h src/widgets/base/WidgetModel.cpp src/widgets/base/WidgetModel.h src/widgets/base/WidgetController.cpp src/widgets/base/WidgetController.h src/widgets/screen/WidgetScreenController.cpp src/widgets/screen/WidgetScreenController.h src/widgets/screen/WidgetScreenModel.cpp src/widgets/screen/WidgetScreenModel.h src/Acitivity/BaseActivity.cpp src/Acitivity/BaseActivity.h)
target_include_directories(mirror_app PRIVATE ${ALLEGRO5_INCLUDE} ${TINYDIR_INCLUDE})
target_link_directories(mirror_app PRIVATE ${ALLEGRO5_LIB_DIR})
target_link_libraries(mirror_app ${ALLEGRO5_LIBS} ${OpenCV_LIBS})