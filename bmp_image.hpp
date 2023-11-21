#ifndef PRECPPPROJECT_BMP_IMAGE_H
#define PRECPPPROJECT_BMP_IMAGE_H

#include <cstdint>
#include <exception>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

#include "matrix.hpp"

class BMPImage {
public:
    static const uint16_t BMP_SIGNATURE = 0x4D42;  // BM
    static const uint16_t BMP_BITS_PER_PIXEL = 24;

    // assume that we are working with GCC
    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    } __attribute__((packed));

    // assume that we are working with GCC
    struct DIBHeader {
        uint32_t dib_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes_num;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t x_per_metre;
        int32_t y_per_meter;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

public:
    BMPImage() {
    }

    ~BMPImage() {
        if (IsOpen()) {
            Close();
        }
    }

    // opens file with specified file name
    void Open(const std::string &filename) {
        if (file_.is_open()) {
            throw std::logic_error("File is already open.");
        }

        if (filename.empty()) {
            throw std::logic_error("File is empty.");
        }
        filename_ = filename;
        file_.open(filename_);
        if (!file_.is_open()) {
            throw std::runtime_error("Cannot open file.");
        }
    }

    // closes file
    void Close() {
        if (!IsOpen()) {
            throw std::logic_error("Cannot close already opened file.");
        }
        file_.close();
        filename_.clear();
    }

    // reads open BMP file
    void ReadBmp() {
        if (!IsOpen()) {
            throw std::logic_error("File is not open.");
        }

        // always reads from the begin of the file
        file_.seekg(0);
        ReadBmpHeader();
        ReadDibHeader();
        ReadPixelArray();
    }

    // saves current BMP file
    void SaveBmp(const std::string filename) {
        std::ofstream ofs{filename, std::ios::binary};
        // checks if can't be saved
        if (!ofs.is_open()) {
            throw std::runtime_error("Cannot save file.");
        }
        // takes into padding
        int32_t row_size = pixel_array_.GetColumnsNumber() * 3 + (4 - ((pixel_array_.GetColumnsNumber() * 3) % 4)) % 4;
        // writes bmp_header
        bmp_header_.file_size = sizeof(bmp_header_) + sizeof(dib_header_) + row_size * pixel_array_.GetRowsNumber();
        bmp_header_.offset = sizeof(bmp_header_) + sizeof(dib_header_);
        ofs.write(reinterpret_cast<const char *>(&bmp_header_), sizeof(bmp_header_));
        // writes dib_header
        dib_header_.height = pixel_array_.GetRowsNumber();
        dib_header_.width = pixel_array_.GetColumnsNumber();
        ofs.write(reinterpret_cast<const char *>(&dib_header_), sizeof(dib_header_));
        uint8_t row[row_size];
        // writes pixel matrix
        for (int32_t x = pixel_array_.GetRowsNumber() - 1; x >= 0; --x) {
            int32_t row_pointer = 0;
            for (int32_t y = 0; y < pixel_array_.GetColumnsNumber(); ++y) {
                Matrix::RGB rgb = pixel_array_.Get(x, y);
                row[row_pointer++] = rgb.r;
                row[row_pointer++] = rgb.g;
                row[row_pointer++] = rgb.b;
            }
            ofs.write(reinterpret_cast<const char *>(&row), row_size);
        }
        ofs.close();
    }

    bool IsOpen() const {

        return file_.is_open();
    }

    const std::string &GetFileName() const {
        return filename_;
    }

    Matrix *GetMatrixReference() {
        return &pixel_array_;
    }

protected:
    // reads BMP header without specifying current read position
    // doesn't check if file is open
    void ReadBmpHeader() {
        if (!file_.is_open()) {
            throw std::runtime_error("BMPHeader is not open.");
        }
        file_.read(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));
        if (!file_.is_open()) {
            throw std::runtime_error("BMPHeader is not open.");
        }
        // checking correctness bmp_header_ right here
        if (bmp_header_.signature != BMP_SIGNATURE) {
            throw std::runtime_error("BMP File is not correct.");
        }
    }

    // reads BMP header without specifying current read position.
    void ReadDibHeader() {
        if (!file_.is_open()) {
            throw std::runtime_error("DIBHeader is not open.");
        }
        file_.read(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
        if (!file_.is_open()) {
            throw std::runtime_error("DIBHeader is not open.");
        }

        // checking correctness of fields here ... (bits_per_pixel)
        if (dib_header_.bits_per_pixel != BMP_BITS_PER_PIXEL) {
            throw std::runtime_error("BMP File is not correct.");
        }
    }

    // reads RGB Matrix specifying current read position
    void ReadPixelArray() {
        if (!file_.is_open()) {
            throw std::runtime_error("DIBHeader is not open.");
        }
        // specify offset from bmp_header offset of file
        file_.seekg(bmp_header_.offset);
        pixel_array_ = Matrix{dib_header_.height, dib_header_.width};
        int32_t row_size = pixel_array_.GetColumnsNumber() * 3 + (4 - ((pixel_array_.GetColumnsNumber() * 3) % 4)) % 4;
        uint8_t row[row_size];
        for (int32_t x = pixel_array_.GetRowsNumber() - 1; x >= 0; --x) {
            file_.read(reinterpret_cast<char *>(&row), row_size);
            int32_t row_pointer = 0;
            for (int32_t y = 0; y < pixel_array_.GetColumnsNumber(); ++y) {
                pixel_array_.Set(x, y, {row[row_pointer++], row[row_pointer++], row[row_pointer++]});
            }
        }
        if (!file_.is_open()) {
            throw std::runtime_error("DIBHeader is not open.");
        }
    }

protected:
    std::string filename_;
    std::fstream file_;

    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    Matrix pixel_array_;
};

#endif  // PRECPPPROJECT_BMP_IMAGE_H
