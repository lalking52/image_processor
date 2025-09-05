#pragma once

#include <fstream>
#include <iostream>
#include <vector>
const int BMP_HEADER_SIZE = 14;
const int DIP_HEADER_SIZE = 40;
const int MATRIX_SIZE = 9;

struct Pixel {
    float r, g, b;

    Pixel() : r(0), g(0), b(0) {
    }
    Pixel(float r, float g, float b) : r(r), g(g), b(b) {
    }
};

class Image {
public:
    Image(int width, int height)
        : image_(height, std::vector<Pixel>(width)),
          width_(width),
          height_(height),
          bmp_header_size_(BMP_HEADER_SIZE),
          dip_header_size_(DIP_HEADER_SIZE) {
    }

    void Read(const char *path);
    void Export(const char *path) const;

    std::vector<std::vector<Pixel> > image_;

    int GetWidth() const {
        return width_;
    }

    int GetHeight() const {
        return height_;
    }

    void SetWidth(int w) {
        width_ = w;
    }

    void SetHeight(int h) {
        height_ = h;
    }

    const int GetBMPHeaderSize() const {
        return bmp_header_size_;
    }

    const int GetDIBHeaderSize() const {
        return dip_header_size_;
    }

    std::vector<Pixel> &operator[](int y) {
        return image_[y];
    }

    const std::vector<Pixel> &operator[](int y) const {
        return image_[y];
    }

    void SetPixel(Image &another_image) {
        SetHeight(another_image.GetHeight());
        SetWidth(another_image.GetWidth());
        for (int y = 0; y != GetHeight(); ++y) {
            for (int x = 0; x != GetWidth(); ++x) {
                image_[y][x] = another_image[y][x];
            }
        }
    }

private:
    int width_;
    int height_;
    const int bmp_header_size_;
    const int dip_header_size_;
};