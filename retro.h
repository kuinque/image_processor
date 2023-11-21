#ifndef PRECPPPROJECT_RETRO_H
#define PRECPPPROJECT_RETRO_H

#include "filter.h"

// retro filter
class Retro : public Filter {
public:
    explicit Retro(Matrix* origin);

    // checks if parametrs are valid
    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;

    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 0;
    static const int32_t REDUCE_BRIGHTNESS = -30;
    inline static const double CONTRAST_COEFFICIENT = 1.2;
    static const int32_t COLOR_CORRECTION = 10;
    static const int32_t RANDOM_NOISE = 10;
};

#endif  // PRECPPPROJECT_RETRO_H
