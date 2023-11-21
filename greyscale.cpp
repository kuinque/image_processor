#include "greyscale.h"

// grey scale filter
GS::GS(Matrix* origin) {
    pixel_array_ = origin;
}

// check if parametrs are valid
void GS::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Shouldn't be gs parametrs.");
    }
}

// apply filter
void GS::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    int32_t width = pixel_array_->GetColumnsNumber();
    int32_t height = pixel_array_->GetRowsNumber();
    Matrix temp(height, width);
    for (int32_t x = 0; x < height; ++x) {
        for (int32_t y = 0; y < width; ++y) {
            // calculating new value for pixel
            Matrix::RGB rgb = pixel_array_->Get(x, y);
            uint8_t new_color = static_cast<uint8_t>(round(get<0>(PIXEL_COEFFICIENT) * static_cast<double>(rgb.r) +
                                                           get<1>(PIXEL_COEFFICIENT) * static_cast<double>(rgb.g) +
                                                           get<2>(PIXEL_COEFFICIENT) * static_cast<double>(rgb.b)));
            rgb.r = new_color;
            rgb.g = new_color;
            rgb.b = new_color;
            temp.Set(x, y, rgb);
        }
    }
    (*pixel_array_) = temp;
}
