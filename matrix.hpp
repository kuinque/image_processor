#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include <tuple>
#include <valarray>

/**
 *  Represents a matrix with m rows and n columns.
 */

class Matrix {
public:
    struct RGB {
        static const uint8_t MAX_COLOR = 255;
        static const uint8_t MIN_COLOR = 0;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        RGB() : r(0), g(0), b(0) {
        }
        RGB(const uint8_t r, const uint8_t g, const uint8_t b) : r(r), g(g), b(b) {
        }
        RGB &operator=(const RGB &origin) {
            r = origin.r;
            g = origin.g;
            b = origin.b;
            return *this;
        }
        RGB &operator=(const std::tuple<int32_t, int32_t, int32_t> &origin) {
            r = static_cast<uint8_t>(
                std::max(static_cast<int32_t>(MIN_COLOR), std::min(static_cast<int32_t>(MAX_COLOR), get<0>(origin))));
            g = static_cast<uint8_t>(
                std::max(static_cast<int32_t>(MIN_COLOR), std::min(static_cast<int32_t>(MAX_COLOR), get<1>(origin))));
            b = static_cast<uint8_t>(
                std::max(static_cast<int32_t>(MIN_COLOR), std::min(static_cast<int32_t>(MAX_COLOR), get<2>(origin))));
            return *this;
        }
        bool operator=(const RGB origin) const {
            return std::tie(r, g, b) == std::tie(origin.r, origin.g, origin.b);
        }
        friend std::tuple<int32_t, int32_t, int32_t> operator*(const int32_t coefficient, const RGB &pixel) {
            std::tuple<int32_t, int32_t, int32_t> pixel_sum;
            get<0>(pixel_sum) = static_cast<int32_t>(pixel.r) * coefficient;
            get<1>(pixel_sum) = static_cast<int32_t>(pixel.g) * coefficient;
            get<2>(pixel_sum) = static_cast<int32_t>(pixel.b) * coefficient;
            return pixel_sum;
        }
    } __attribute__((packed));

    Matrix() : data_(new RGB[0]), rows_num_(0), cols_num_(0) {
    }

    Matrix(const int32_t rows_num, const int32_t cols_num)
        : data_(new RGB[rows_num * cols_num]), rows_num_(rows_num), cols_num_(cols_num) {
        if (rows_num == 0 || cols_num == 0) {
            throw std::logic_error("Invalid pixel matrix size.");
        }
    }

    Matrix(const Matrix &origin)
        : data_(origin.data_ ? new RGB[origin.cols_num_ * origin.rows_num_] : nullptr),
          rows_num_(origin.rows_num_),
          cols_num_(origin.cols_num_) {
        std::copy(origin.data_, origin.data_ + (origin.cols_num_ * origin.rows_num_), data_);
    }

    ~Matrix() {
        delete[] data_;
    }

    bool operator==(const Matrix &rhs) const {
        if (this == &rhs) {
            return true;
        }
        return (rows_num_ == rhs.rows_num_ && cols_num_ == rhs.cols_num_ &&
                std::memcpy(this->data_, rhs.data_, (rows_num_ * cols_num_)));
    }

    bool operator!=(const Matrix &rhs) const {
        return !(*this == rhs);
    }

    Matrix &operator=(const Matrix &rhs) {
        if (this == &rhs) {
            return *this;
        }
        Matrix tmp{rhs};
        Swap(tmp, *this);
        return *this;
    }

    const RGB &Get(const int32_t x, const int32_t y) const {
        if (!InBounds(x, y)) {
            throw std::out_of_range("Indexes are out of pixel matrix.");
        }
        return data_[Offset(x, y)];
    }

    void NearestCoordinates(int32_t &x, int32_t &y) const {
        x = std::max(0, std::min(rows_num_ - 1, x));
        y = std::max(0, std::min(cols_num_ - 1, y));
    }

    const RGB &GetNearest(const int32_t x, const int32_t y) const {
        int32_t nearest_x = x;
        int32_t nearest_y = y;
        NearestCoordinates(nearest_x, nearest_y);
        return data_[Offset(nearest_x, nearest_y)];
    }

    int32_t GetRowsNumber() const {
        return rows_num_;
    }

    int32_t GetColumnsNumber() const {
        return cols_num_;
    }

    void Set(const int32_t x, const int32_t y, RGB color) {
        if (!InBounds(x, y)) {
            throw std::out_of_range("Indexes are out of pixel matrix.");
        }
        data_[Offset(x, y)] = color;
    }

    bool InBounds(const int32_t x, const int32_t y) const {
        return (x >= 0) && (x < rows_num_) && (y >= 0) && (y < cols_num_);
    }

public:
    inline static const RGB WHITE_PIXEL{255, 255, 255};
    inline static const RGB BLACK_PIXEL{0, 0, 0};

protected:
    static void Swap(Matrix &copy, Matrix &origin) {
        std::swap(copy.data_, origin.data_);
        std::swap(copy.rows_num_, origin.rows_num_);
        std::swap(copy.cols_num_, origin.cols_num_);
    }

    int32_t Offset(const int32_t x, const int32_t y) const {
        return (x * cols_num_ + y);
    }

    RGB *data_;
    int32_t rows_num_;
    int32_t cols_num_;
};

#endif  // MATRIX_MATRIX_H
