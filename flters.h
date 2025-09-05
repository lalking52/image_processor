#pragma once
#include "image.h"

Pixel ApplyMatrix(Image &image, int x, int y, const int matrix[MATRIX_SIZE], std::string type, float param);
template <typename T>

T Clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}

class BaseFilter {
public:
    virtual void Apply(Image &image) = 0;
};

class Crop : public BaseFilter {

public:
    Crop(int width, int height) : width_(width), height_(height) {
    }
    void Apply(Image &image) override;
    int width_;
    int height_;
};

class Grayscale : public BaseFilter {
public:
    void Apply(Image &image) override;
};

class Negative : public BaseFilter {
public:
    void Apply(Image &image) override;
};

class Sharpening : public BaseFilter {
public:
    void Apply(Image &image) override;
};

class EdgeDetection : public BaseFilter {
public:
    float threshold;
    explicit EdgeDetection(float t) : threshold(t) {
    }
    void Apply(Image &image) override;
};

class GaussianBlur : public BaseFilter {
public:
    float sigma;

    explicit GaussianBlur(float sigma) : sigma(sigma) {
    }
    void Apply(Image &image) override;
};

// дополнительный
class Crystallize : public BaseFilter {
public:
    int BlockSize;

    explicit Crystallize(int size) : BlockSize(size) {
    }

    void Apply(Image &image) override;
};
