#include "flters.h"
#include "image.h"

void Crop::Apply(Image& image) {
    if (width_ > image.GetWidth()) {
        width_ = image.GetWidth();
    }
    if (height_ > image.GetHeight()) {
        height_ = image.GetHeight();
    }

    Image new_im(width_, height_);
    int row = 0;

    for (int y = image.GetHeight() - height_; y < image.GetHeight(); ++y) {
        for (int x = 0; x < width_; ++x) {

            new_im[row][x] = image[y][x];
        }
        ++row;
    }
    image.SetPixel(new_im);
}