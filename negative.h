#ifndef PRECPPPROJECT_NEGATIVE_H
#define PRECPPPROJECT_NEGATIVE_H

#include "filter.h"

// negative filter
class Neg : public Filter {
public:
    explicit Neg(Matrix* origin);
    // check if parametrs are valid
    void CheckParametrsValidity(int parametrs_size, char* parametrs[]) override;
    // apply filter
    void ApplyFilter(int parametrs_size, char* parametrs[]) override;

private:
    static const int PARAMETRS_SIZE = 0;
};

#endif  // PRECPPPROJECT_NEGATIVE_H
