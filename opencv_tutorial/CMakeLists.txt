cmake_minimum_required (VERSION 3.0)
project (DisplayImage)

find_package( OpenCV 4.0.0 REQUIRED)
message("OpenCV version: ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(DisplayImage displayImage.cpp)
TARGET_LINK_LIBRARIES(DisplayImage ${OpenCV_LIBS})
