#include "flters.h"
#include "image.h"

Pixel SelectPixelSharp(float &r, float &g, float &b) {
    r = Clamp(r, 0.0f, 1.0f);
    g = Clamp(g, 0.0f, 1.0f);
    b = Clamp(b, 0.0f, 1.0f);
    return Pixel(r, g, b);
}

void Sharpening::Apply(Image &image) {
    Image new_im(image.GetWidth(), image.GetHeight());

    const int matrix[MATRIX_SIZE] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    for (int y = 0; y != image.GetHeight(); ++y) {
        for (int x = 0; x != image.GetWidth(); ++x) {
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            int index = 0;

            for (int j = 1; j >= -1; --j) {
                for (int i = -1; i <= 1; ++i) {

                    int near_x = Clamp(x + i, 0, image.GetWidth() - 1);
                    int near_y = Clamp(y + j, 0, image.GetHeight() - 1);

                    Pixel neighbor_pixel = image[near_y][near_x];

                    r += neighbor_pixel.r * static_cast<float>(matrix[index]);
                    g += neighbor_pixel.g * static_cast<float>(matrix[index]);
                    b += neighbor_pixel.b * static_cast<float>(matrix[index]);

                    ++index;
                }
            }
            new_im[y][x] = SelectPixelSharp(r, g, b);
        }
    }
    image.SetPixel(new_im);
}