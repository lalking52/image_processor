#pragma once

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

struct Parsing {
    char *input_path;
    char *output_path;
    std::vector<std::pair<std::string, std::vector<std::string> > > args;

    Parsing(int argc, char **argv);
};