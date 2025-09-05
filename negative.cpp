#include "flters.h"

void Negative::Apply(Image &image) {
    for (int y = 0; y != image.GetHeight(); ++y) {
        for (int x = 0; x != image.GetWidth(); ++x) {
            image.image_[y][x].r = 1 - image.image_[y][x].r;
            image.image_[y][x].g = 1 - image.image_[y][x].g;
            image.image_[y][x].b = 1 - image.image_[y][x].b;
        }
    }
}