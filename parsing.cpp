#include "parsing.h"
#include <iostream>
#include <utility>

Parsing::Parsing(int argc, char** argv) {
    if (argc < 3) {
        throw std::runtime_error("недостаточно аргументов для корретнго чтения картинки");
    }

    input_path = argv[1];
    if (input_path[0] == '-' || std::string(input_path).empty()) {
        throw std::runtime_error("неправильно введен путь ввода");
    }

    output_path = argv[2];
    if (std::string(output_path).empty() || output_path[0] == '-') {
        throw std::runtime_error("неправильно введен путь вывода");
    }

    std::string filter;
    int ind = -1;
    for (int i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            filter = std::string(argv[i]);
            args.push_back(std::make_pair(filter, std::vector<std::string>()));
            ++ind;
        } else {
            args[ind].second.emplace_back(argv[i]);
        }
    }
}
