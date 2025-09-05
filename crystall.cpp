#include "flters.h"

void Crystallize::Apply(Image &image) {
    for (int y = 0; y < image.GetHeight(); y += BlockSize) {
        for (int x = 0; x < image.GetWidth(); x += BlockSize) {
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            int count = 0;

            for (int by = 0; by < BlockSize; ++by) {
                for (int bx = 0; bx < BlockSize; ++bx) {
                    int near_x = x + bx;
                    int near_y = y + by;

                    if (near_x < image.GetWidth() && near_y < image.GetHeight()) {
                        Pixel pixel = image[near_y][near_x];
                        r += pixel.r;
                        g += pixel.g;
                        b += pixel.b;
                        count++;
                    }
                }
            }
            if (count > 0) {
                r /= static_cast<float>(count);
                g /= static_cast<float>(count);
                b /= static_cast<float>(count);
            }
            for (int by = 0; by < BlockSize; ++by) {
                for (int bx = 0; bx < BlockSize; ++bx) {
                    int near_x = x + bx;
                    int near_y = y + by;

                    if (near_x < image.GetWidth() && near_y < image.GetHeight()) {
                        image[near_y][near_x] = Pixel(Clamp(r, 0.0f, 1.0f), Clamp(g, 0.0f, 1.0f), Clamp(b, 0.0f, 1.0f));
                    }
                }
            }
        }
    }
}
