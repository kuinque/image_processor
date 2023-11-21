#ifndef PRECPPPROJECT_FILTER_H
#define PRECPPPROJECT_FILTER_H

#include "matrix.hpp"

class Filter {
public:
    Filter();
    explicit Filter(Matrix* origin);
    ~Filter();
    virtual void CheckParametrsValidity(int parametrs_size, char* parametrs[]);
    virtual void ApplyFilter(int parametrs_size, char* parametrs[]);

protected:
    Matrix* pixel_array_;
};

#endif  // PRECPPPROJECT_FILTER_H
