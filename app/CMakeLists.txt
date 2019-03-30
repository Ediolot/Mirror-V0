cmake_minimum_required(VERSION 3.13)
project(mirror_app)

set(CMAKE_CXX_STANDARD 17)

# ALLEGRO 5
set(ALLEGRO5_INCLUDE D:/Programming/Libs/allegro-5.2.5.1/include)
set(ALLEGRO5_LIB_DIR D:/Programming/Libs/allegro-5.2.5.1/lib)
set(ALLEGRO5_LIBS allegro_monolith-debug)

# OPENCV 4
find_package(OpenCV REQUIRED HINTS "D:/Programming/Libs/opencv-4.0.1")

add_executable(mirror_app src/main.cpp src/modules/screen/Screen.cpp src/modules/screen/Screen.h src/modules/opencv/videoCam.cpp src/modules/opencv/videoCam.h src/utils/Utils.cpp src/utils/Utils.h)
target_include_directories(mirror_app PRIVATE ${ALLEGRO5_INCLUDE})
target_link_directories(mirror_app PRIVATE ${ALLEGRO5_LIB_DIR})
target_link_libraries(mirror_app ${ALLEGRO5_LIBS} ${OpenCV_LIBS})