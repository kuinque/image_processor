#include "blur.h"

Blur::Blur(Matrix* origin) {
    pixel_array_ = origin;
}

// calculates pixel contribution
void Blur::PixelContribution(std::tuple<double, double, double>& origin, const int32_t xy_offset,
                             double* offset_coefficient) {
    double coefficient = offset_coefficient[xy_offset];
    get<0>(origin) *= coefficient;
    get<1>(origin) *= coefficient;
    get<2>(origin) *= coefficient;
}

// calculates vertically
void Blur::HeightCalculate(std::tuple<double, double, double>** temp, const int32_t height, const int32_t width,
                           const double common_multiplier, const double sigma_mult, const int32_t sigma,
                           double* offset_coefficient) {
    for (int32_t x0 = 0; x0 < height; ++x0) {
        for (int32_t y0 = 0; y0 < width; ++y0) {
            // no sense to cosider bigger matrix
            temp[x0][y0] = std::make_tuple(0.0, 0.0, 0.0);
            for (int32_t x_offset = -MATRIX_CONSIDER_SIZE * sigma; x_offset <= MATRIX_CONSIDER_SIZE * sigma;
                 ++x_offset) {
                int32_t x = x0 + x_offset;
                int32_t y = y0;
                Matrix::RGB rgb = pixel_array_->GetNearest(x, y);
                std::tuple<double, double, double> next_pixel =
                    std::make_tuple(static_cast<double>(rgb.r), static_cast<double>(rgb.g), static_cast<double>(rgb.b));
                PixelContribution(next_pixel, MATRIX_CONSIDER_SIZE * sigma + x_offset, offset_coefficient);
                get<0>(temp[x0][y0]) += get<0>(next_pixel);
                get<1>(temp[x0][y0]) += get<1>(next_pixel);
                get<2>(temp[x0][y0]) += get<2>(next_pixel);
            }
        }
    }
}

// finds neares coordinates for x and y
void Blur::NearestCoordinates(int32_t& x, int32_t& y, const int32_t height, const int32_t width) const {
    x = std::max(0, std::min(height - 1, x));
    y = std::max(0, std::min(width - 1, y));
}

// calculates horizontally
void Blur::WidthCalculate(std::tuple<double, double, double>** temp, const int32_t height, const int32_t width,
                          const double common_multiplier, const double sigma_mult, const int32_t sigma,
                          double* offset_coefficient) {
    for (int32_t x0 = 0; x0 < height; ++x0) {
        for (int32_t y0 = 0; y0 < width; ++y0) {
            std::tuple<double, double, double> pixels_sum{0, 0, 0};
            // no sense to cosider bigger matrix
            for (int32_t y_offset = -MATRIX_CONSIDER_SIZE * sigma; y_offset <= MATRIX_CONSIDER_SIZE * sigma;
                 ++y_offset) {
                int32_t x = x0;
                int32_t y = y0 + y_offset;
                NearestCoordinates(x, y, height, width);
                std::tuple<double, double, double> near_pixel = temp[x][y];
                PixelContribution(near_pixel, MATRIX_CONSIDER_SIZE * sigma + y_offset, offset_coefficient);
                get<0>(pixels_sum) += get<0>(near_pixel);
                get<1>(pixels_sum) += get<1>(near_pixel);
                get<2>(pixels_sum) += get<2>(near_pixel);
            }
            get<0>(pixels_sum) *= common_multiplier;
            get<1>(pixels_sum) *= common_multiplier;
            get<2>(pixels_sum) *= common_multiplier;
            Matrix::RGB rgb{static_cast<uint8_t>(round(get<0>(pixels_sum))),
                            static_cast<uint8_t>(round(get<1>(pixels_sum))),
                            static_cast<uint8_t>(round(get<2>(pixels_sum)))};
            pixel_array_->Set(x0, y0, rgb);
        }
    }
}

// checks if parametrs are valid
void Blur::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
    if (parametrs_size != PARAMETRS_SIZE) {
        throw std::runtime_error("Should be 1 blur parametrs.");
    }
    try {
        std::stod(parametrs[0]);
    } catch (...) {
        throw std::runtime_error("Parametr for blur not valid.");
    }
}

// apply filter
void Blur::ApplyFilter(int parametrs_size, char* parametrs[]) {
    CheckParametrsValidity(parametrs_size, parametrs);
    double sigma = std::stod(parametrs[0]);
    if (sigma < 0) {
        throw std::logic_error("Sigma should be at least zero.");
    }
    int32_t width = pixel_array_->GetColumnsNumber();
    int32_t height = pixel_array_->GetRowsNumber();
    std::tuple<double, double, double>** double_pixels = new std::tuple<double, double, double>*[height];
    for (int x = 0; x < height; ++x) {
        double_pixels[x] = new std::tuple<double, double, double>[width];
    }
    // calculates necessary multipliers
    double sigma_mult = (SIGMA_COEFFICIENT * sigma * sigma);
    double common_multiplier = 1.0 / (sigma_mult * PI);
    int32_t sigma_rounded = static_cast<int32_t>(round(sigma));
    // pre-calc of horizontal/vertical offset coefficients
    double* offset_coefficient = new double[MATRIX_CONSIDER_SIZE * sigma_rounded * 2 + 2];
    for (int32_t xy_offset = -MATRIX_CONSIDER_SIZE * sigma_rounded; xy_offset <= MATRIX_CONSIDER_SIZE * sigma_rounded;
         ++xy_offset) {
        double coefficient = static_cast<double>(xy_offset * xy_offset) / sigma_mult;
        coefficient = 1.0 / pow(E, coefficient);
        offset_coefficient[MATRIX_CONSIDER_SIZE * sigma_rounded + xy_offset] = coefficient;
    }

    HeightCalculate(double_pixels, height, width, common_multiplier, sigma_mult, sigma_rounded, offset_coefficient);
    WidthCalculate(double_pixels, height, width, common_multiplier, sigma_mult, sigma_rounded, offset_coefficient);

    delete[] offset_coefficient;
    for (int x = 0; x < height; ++x) {
        delete[] double_pixels[x];
    }
    delete[] double_pixels;
}
