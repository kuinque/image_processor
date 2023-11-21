#include "crop.h"

// crop filter
Crop::Crop(Matrix* origin) {
    pixel_array_ = origin;
}

// check if all parametrs are valid
void Crop::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Should be 2 crop parametrs.");
    }
    try {
        std::stoi(parametrs[0]);
    } catch (...) {
        throw std::runtime_error("Parametrs for crop not valid.");
    }
    try {
        std::stoi(parametrs[1]);
    } catch (...) {
        throw std::runtime_error("Parametrs for crop not valid.");
    }
}

// apply filter
void Crop::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    int32_t new_height = std::stoi(parametrs[1]);
    int32_t new_width = std::stoi(parametrs[0]);
    // check if new values are lower than 0
    if (new_width <= 0 || new_height <= 0) {
        throw std::logic_error("Canoot be cropped to that size.");
    }
    new_height = std::min(pixel_array_->GetRowsNumber(), new_height);
    new_width = std::min(pixel_array_->GetColumnsNumber(), new_width);
    Matrix temp(new_height, new_width);
    for (int32_t x = 0; x < new_height; ++x) {
        for (int32_t y = 0; y < new_width; ++y) {
            temp.Set(x, y, pixel_array_->Get(x, y));
        }
    }
    (*pixel_array_) = temp;
}
