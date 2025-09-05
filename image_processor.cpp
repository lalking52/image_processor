#include "execute.h"
#include "image.h"
#include "parsing.h"

int main(int argc, char **argv) {
    Parsing parse(argc, argv);
    Image image(0, 0);
    image.Read(parse.input_path);

    Executor(image, parse.args);

    image.Export(parse.output_path);
    return 0;
}