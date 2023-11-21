#ifndef PRECPPPROJECT_INPUT_CONTROLLER_H
#define PRECPPPROJECT_INPUT_CONTROLLER_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "bmp_image.hpp"
#include "crop.h"
#include "greyscale.h"
#include "negative.h"
#include "sharp.h"
#include "edge.h"
#include "blur.h"
#include "retro.h"

class InputController {
public:
    // reads file input
    void InputFlow(const int argc, char* argv[]);

private:
    // outputs info about filters
    void InputInfo();
    // analyze parametrs and filters
    void InputAnalyze(const int argc, char* argv[]);

private:
    Matrix* pixel_array_;
    std::map<std::string, int> filter_map_ = {{"-crop", 2}, {"-gs", 0},   {"-neg", 0},  {"-sharp", 0},
                                              {"-edge", 1}, {"-blur", 1}, {"-retro", 0}};
};

#endif  // PRECPPPROJECT_IMAGE_CONTROLLER_H
