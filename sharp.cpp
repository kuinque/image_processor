#include "sharp.h"

// sharping filter
Sharp::Sharp(Matrix* origin) {
    pixel_array_ = origin;
}

// culculates new pixel culors
void Sharp::ChangeCurrentPixel(Matrix& temp, const int32_t x, const int32_t y) {
    Matrix::RGB rgb = pixel_array_->Get(x, y);
    std::tuple<int32_t, int32_t, int32_t> current_pixel{0, 0, 0};
    for (int32_t pixel_num = 0; pixel_num < NEAR_PIXELS; ++pixel_num) {
        // constants due to pixel matrix
        std::tuple<int32_t, int32_t, int32_t> near_pixel =
            PIXEL_COEFFICIENT[pixel_num] *
            pixel_array_->GetNearest(x + HEIGHT_OFFSET[pixel_num], y + WIDTH_OFFSET[pixel_num]);
        get<0>(current_pixel) += get<0>(near_pixel);
        get<1>(current_pixel) += get<1>(near_pixel);
        get<2>(current_pixel) += get<2>(near_pixel);
    }
    rgb = current_pixel;
    temp.Set(x, y, rgb);
}

// checks if parametrs are valid
void Sharp::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Shouldn't be sharp parametrs.");
    }
}

// apply filter
void Sharp::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    int32_t width = pixel_array_->GetColumnsNumber();
    int32_t height = pixel_array_->GetRowsNumber();
    Matrix temp(height, width);
    for (int32_t x = 0; x < height; ++x) {
        for (int32_t y = 0; y < width; ++y) {
            ChangeCurrentPixel(temp, x, y);
        }
    }
    (*pixel_array_) = temp;
}
