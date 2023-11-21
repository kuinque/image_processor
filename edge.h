#ifndef PRECPPPROJECT_EDGE_H
#define PRECPPPROJECT_EDGE_H

#include "filter.h"
#include "greyscale.h"

// edge filter
class Edge : public Filter {
public:
    explicit Edge(Matrix* origin);

    // applying pixel with threshold
    void ThresholdPixel(Matrix::RGB& origin, const uint8_t threshold);

    // transforms pixel
    void TransformPixel(Matrix& temp, const int32_t x, const int32_t y, const int32_t threshold);

    // checks if parametrs are valid
    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;

    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 1;
    static const int32_t NEAR_PIXELS = 9;
    inline static const int32_t PIXEL_COEFFICIENT[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    inline static const int32_t WIDTH_OFFSET[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    inline static const int32_t HEIGHT_OFFSET[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
};

#endif  // PRECPPPROJECT_EDGE_H
