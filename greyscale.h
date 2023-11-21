#ifndef PRECPPPROJECT_GREYSCALE_H
#define PRECPPPROJECT_GREYSCALE_H

#include "filter.h"

// grey scale filter
class GS : public Filter {
public:
    explicit GS(Matrix* origin);

    // check if parametrs are valid
    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;

    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 0;
    inline static const std::tuple<const double, const double, const double> PIXEL_COEFFICIENT{0.299, 0.587, 0.114};
};

#endif  // PRECPPPROJECT_GREYSCALE_H
