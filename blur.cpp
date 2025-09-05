#include "flters.h"
#include <cmath>

void GaussianBlur::Apply(Image &image) {
    int radius = static_cast<int>(sigma * 3);
    float norm_sum = 0.0f;
    const float coef = 1 / (2.0f * static_cast<float>(M_PI) * sigma * sigma);
    for (ssize_t x = -radius; x <= radius; ++x) {
        for (ssize_t y = -radius; y <= radius; ++y) {
            norm_sum += static_cast<float>(coef) * std::exp(-static_cast<float>(x * x + y * y) / (2 * sigma * sigma));
        }
    }

    Image new_image(image.GetWidth(), image.GetHeight());

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            for (int x = -radius; x <= radius; ++x) {
                int new_i = std::min(image.GetHeight() - 1, std::max(0, i + x));
                new_image[i][j].r += image[new_i][j].r * std::exp(-static_cast<float>(x * x) / (2 * sigma * sigma));
                new_image[i][j].g += image[new_i][j].g * std::exp(-static_cast<float>(x * x) / (2 * sigma * sigma));
                new_image[i][j].b += image[new_i][j].b * std::exp(-static_cast<float>(x * x) / (2 * sigma * sigma));
            }
        }
    }

    Image new_image_y = new_image;
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            for (int y = -radius; y <= radius; ++y) {
                if (y == 0) {
                    continue;
                }
                int new_j = std::min(image.GetWidth() - 1, std::max(0, j + y));
                new_image_y[i][j].r +=
                    new_image[i][new_j].r * std::exp(-static_cast<float>(y * y) / (2 * sigma * sigma));
                new_image_y[i][j].g +=
                    new_image[i][new_j].g * std::exp(-static_cast<float>(y * y) / (2 * sigma * sigma));
                new_image_y[i][j].b +=
                    new_image[i][new_j].b * std::exp(-static_cast<float>(y * y) / (2 * sigma * sigma));
            }
        }
    }

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            new_image_y[i][j].r = new_image_y[i][j].r * (coef / norm_sum);
            new_image_y[i][j].g = new_image_y[i][j].g * (coef / norm_sum);
            new_image_y[i][j].b = new_image_y[i][j].b * (coef / norm_sum);
        }
    }
    image.SetPixel(new_image_y);
}
