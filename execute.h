#pragma once
#include "flters.h"

void Executor(Image &image, std::vector<std::pair<std::string, std::vector<std::string> > > &args) {

    for (const std::pair<const std::string, std::vector<std::string> > filter : args) {

        if (filter.first == "-neg") {
            Negative neg;
            neg.Apply(image);
        } else if (filter.first == "-gs") {
            Grayscale gs;
            gs.Apply(image);
        } else if (filter.first == "-sharp") {
            Sharpening sharp;
            sharp.Apply(image);
        } else if (filter.first == "-edge") {
            if (filter.second.empty()) {
                throw std::runtime_error("недостаточно аргументов для применения фильтра -edge");
            }
            float threshold = std::stof(filter.second[0]);
            EdgeDetection edge(threshold);
            edge.Apply(image);
        } else if (filter.first == "-blur") {
            if (filter.second.empty()) {
                throw std::runtime_error("недостаточно аргументов для применения фильтра -blur");
            }
            float sigma = std::stof(filter.second[0]);
            GaussianBlur blur(sigma);
            blur.Apply(image);
        } else if (filter.first == "-crystall") {
            if (filter.second.empty()) {
                throw std::runtime_error("недостаточно аргументов для применения фильтра -crystall");
            }
            int block = std::stoi(filter.second[0]);
            Crystallize crystall(block);
            crystall.Apply(image);
        } else if (filter.first == "-crop") {

            if (filter.second.size() < 2) {
                throw std::runtime_error("недостаточно аргументов для применения фильтра -crop");
            }
            int width = std::stoi(filter.second[0]);
            int height = std::stoi(filter.second[1]);

            Crop crop(width, height);
            crop.Apply(image);

        } else {
            throw std::runtime_error("недостаточно аргументов для применения фильтра");
        }
    }
}