#ifndef PRECPPPROJECT_BLUR_H
#define PRECPPPROJECT_BLUR_H

#include "filter.h"

class Blur : public Filter {
public:
    explicit Blur(Matrix* origin);

    // calculates pixel contribution
    void PixelContribution(std::tuple<double, double, double>& origin, const int32_t xy_offset,
                           double* offset_coefficient);

    // calculates vertically
    void HeightCalculate(std::tuple<double, double, double>** temp, const int32_t height, const int32_t width,
                         const double common_multiplier, const double sigma_mult, const int32_t sigma,
                         double* offset_coefficient);

    // finds neares coordinates for x and y
    void NearestCoordinates(int32_t& x, int32_t& y, const int32_t height, const int32_t width) const;

    // calculates horizontally
    void WidthCalculate(std::tuple<double, double, double>** temp, const int32_t height, const int32_t width,
                        const double common_multiplier, const double sigma_mult, const int32_t sigma,
                        double* offset_coefficient);

    // checks if parametrs are valid
    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;

    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 1;
    static const int32_t MATRIX_CONSIDER_SIZE = 3;
    inline static const double SIGMA_COEFFICIENT = 2.0;
    inline static const double PI = std::atan(1.0) * 4.0;
    inline static const double E = std::exp(1.0);
};

#endif  // PRECPPPROJECT_BLUR_H
