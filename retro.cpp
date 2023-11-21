#include "retro.h"

// retro filter
Retro::Retro(Matrix* origin) {
    pixel_array_ = origin;
}

// checks if parametrs are valid
void Retro::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Shouldn't be neg parametrs.");
    }
}

// apply filter
void Retro::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    int32_t width = pixel_array_->GetColumnsNumber();
    int32_t height = pixel_array_->GetRowsNumber();
    Matrix temp(height, width);
    for (int32_t x = 0; x < height; ++x) {
        for (int32_t y = 0; y < width; ++y) {
            Matrix::RGB rgb = pixel_array_->Get(x, y);
            std::tuple<int32_t, int32_t, int32_t> pixel = {static_cast<int32_t>(rgb.r), static_cast<int32_t>(rgb.g),
                                                           static_cast<int32_t>(rgb.b)};
            // reduces brightness
            get<0>(pixel) -= REDUCE_BRIGHTNESS;
            get<1>(pixel) -= REDUCE_BRIGHTNESS;
            get<2>(pixel) -= REDUCE_BRIGHTNESS;
            // contrasts picture
            get<0>(pixel) = static_cast<int32_t>(round(static_cast<double>(get<0>(pixel)) * CONTRAST_COEFFICIENT));
            get<1>(pixel) = static_cast<int32_t>(round(static_cast<double>(get<1>(pixel)) * CONTRAST_COEFFICIENT));
            get<2>(pixel) = static_cast<int32_t>(round(static_cast<double>(get<1>(pixel)) * CONTRAST_COEFFICIENT));
            // reconfiguration of colors
            get<0>(pixel) += COLOR_CORRECTION;
            get<1>(pixel) -= COLOR_CORRECTION;
            get<2>(pixel) += COLOR_CORRECTION;
            // random noise on picture
            int32_t noise_r = rand() % (RANDOM_NOISE * 2);
            int32_t noise_g = rand() % (RANDOM_NOISE * 2);
            int32_t noise_b = rand() % (RANDOM_NOISE * 2);
            get<0>(pixel) += noise_r - RANDOM_NOISE;
            get<1>(pixel) += noise_g - RANDOM_NOISE;
            get<2>(pixel) += noise_b - RANDOM_NOISE;

            rgb = pixel;
            temp.Set(x, y, rgb);
        }
    }
    (*pixel_array_) = temp;
}
