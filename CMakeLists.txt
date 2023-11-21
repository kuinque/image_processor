cmake_minimum_required(VERSION 3.8)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor image_processor.cpp matrix.hpp bmp_image.hpp input_controller.h input_controller.cpp blur.h blur.cpp crop.h crop.cpp edge.h edge.cpp filter.h filter.cpp greyscale.h greyscale.cpp negative.h negative.cpp retro.h retro.cpp sharp.h sharp.cpp)
# add_executable(image_processor bmp_image.hpp) 
