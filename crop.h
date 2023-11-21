#ifndef PRECPPPROJECT_CROP_H
#define PRECPPPROJECT_CROP_H

#include "filter.h"

// crop filter
class Crop : public Filter {
public:
    explicit Crop(Matrix* origin);  // check if all parametrs are valid

    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;

    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 2;
};

#endif  // PRECPPPROJECT_CROP_H
