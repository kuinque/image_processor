#include "edge.h"

Edge::Edge(Matrix* origin) {
    pixel_array_ = origin;
}

// applying pixel with threshold
void Edge::ThresholdPixel(Matrix::RGB& origin, const uint8_t threshold) {
    if (origin.r > threshold) {
        origin = Matrix::WHITE_PIXEL;
        return;
    }
    origin = Matrix::BLACK_PIXEL;
}

// transforms pixel
void Edge::TransformPixel(Matrix& temp, const int32_t x, const int32_t y, const int32_t threshold) {
    Matrix::RGB rgb = pixel_array_->Get(x, y);
    std::tuple<int32_t, int32_t, int32_t> current_pixel{0, 0, 0};
    for (int32_t pixel_num = 0; pixel_num < NEAR_PIXELS; ++pixel_num) {
        // constants sue to pixel matrix
        std::tuple<int32_t, int32_t, int32_t> near_pixel =
            PIXEL_COEFFICIENT[pixel_num] *
            pixel_array_->GetNearest(x + HEIGHT_OFFSET[pixel_num], y + WIDTH_OFFSET[pixel_num]);
        get<0>(current_pixel) += get<0>(near_pixel);
        get<1>(current_pixel) += get<1>(near_pixel);
        get<2>(current_pixel) += get<2>(near_pixel);
    }
    rgb = current_pixel;
    ThresholdPixel(rgb, threshold);
    temp.Set(x, y, rgb);
}

// checks if parametrs are valid
void Edge::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Should be 1 edge parametr.");
    }
    try {
        std::stod(parametrs[0]);
    } catch (...) {
        throw std::runtime_error("Parametr for edge not valid.");
    }
}

// apply filter
void Edge::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    uint8_t threshold =
        static_cast<uint8_t>(round(std::stod(parametrs[0]) * static_cast<double>(Matrix::RGB::MAX_COLOR)));
    if (threshold < 0 || threshold > Matrix::RGB::MAX_COLOR) {
        throw std::logic_error("Threshold should be in range [0, 1].");
    }
    // applying grey scales
    GS gs{pixel_array_};
    gs.ApplyFilter(0, {});
    int32_t width = pixel_array_->GetColumnsNumber();
    int32_t height = pixel_array_->GetRowsNumber();
    Matrix temp(height, width);
    for (int32_t x = 0; x < height; ++x) {
        for (int32_t y = 0; y < width; ++y) {
            TransformPixel(temp, x, y, threshold);
        }
    }
    (*pixel_array_) = temp;
}
