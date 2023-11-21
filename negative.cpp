#include "negative.h"

// negative filter
Neg::Neg(Matrix* origin) {
    pixel_array_ = origin;
}

// check if parametrs are valid
void Neg::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Shouldn't be neg parametrs.");
    }
}

// apply filter
void Neg::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    int32_t width = pixel_array_->GetColumnsNumber();
    int32_t height = pixel_array_->GetRowsNumber();
    Matrix temp(height, width);
    for (int32_t x = 0; x < height; ++x) {
        for (int32_t y = 0; y < width; ++y) {
            // calculating new values
            Matrix::RGB rgb = pixel_array_->Get(x, y);
            rgb.r = Matrix::RGB::MAX_COLOR - rgb.r;
            rgb.g = Matrix::RGB::MAX_COLOR - rgb.g;
            rgb.b = Matrix::RGB::MAX_COLOR - rgb.b;
            temp.Set(x, y, rgb);
        }
    }
    (*pixel_array_) = temp;
}
