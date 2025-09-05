#include "flters.h"

void Grayscale::Apply(Image &image) {
    const float n299 = 0.299f;
    const float n587 = 0.587f;
    const float n114 = 0.114f;

    for (int y = 0; y != image.GetHeight(); ++y) {
        for (int x = 0; x != image.GetWidth(); ++x) {
            float red = image.image_[y][x].r;
            float green = image.image_[y][x].g;
            float blue = image.image_[y][x].b;

            image.image_[y][x].r = n299 * red + n587 * green + n114 * blue;
            image.image_[y][x].g = n299 * red + n587 * green + n114 * blue;
            image.image_[y][x].b = n299 * red + n587 * green + n114 * blue;
        }
    }
}