#include <cassert>
#include <cctype>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "input_controller.h"

int main(int argc, char* argv[]) {
    InputController input_controller;
    input_controller.InputFlow(argc, argv);
    return 0;
}
