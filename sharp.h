#ifndef PRECPPPROJECT_SHARP_H
#define PRECPPPROJECT_SHARP_H

#include "filter.h"

// sharping filter
class Sharp : public Filter {
public:
    explicit Sharp(Matrix* origin);
    // culculates new pixel culors
    void ChangeCurrentPixel(Matrix& temp, const int32_t x, const int32_t y);
    // checks if parametrs are valid
    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;
    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 0;
    static const int32_t NEAR_PIXELS = 9;
    inline static const int32_t PIXEL_COEFFICIENT[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    inline static const int32_t WIDTH_OFFSET[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    inline static const int32_t HEIGHT_OFFSET[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
};

#endif  // PRECPPPROJECT_SHARP_H
