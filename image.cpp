#include "image.h"
#include <stdexcept>

void Image::Read(const char *path) {
    std::ifstream bmp;
    bmp.open(path, std::ios::in | std::ios::binary);

    if (!bmp.is_open()) {
        std::cout << "Невозможно открыть файл" << std::endl;
        return;
    }

    unsigned char *file_header = new unsigned char[GetBMPHeaderSize()];
    bmp.read(reinterpret_cast<char *>(file_header), GetBMPHeaderSize());

    unsigned char *information_header = new unsigned char[GetDIBHeaderSize()];
    bmp.read(reinterpret_cast<char *>(information_header), GetDIBHeaderSize());

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "Путь ведет не к bitmap image" << std::endl;
        bmp.close();
        return;
    }

    const size_t n4 = 4;
    const size_t n8 = 8;
    const size_t n16 = 16;
    const size_t n24 = 24;

    SetWidth(information_header[n4] + (information_header[n4 + 1] << n8) + (information_header[n4 + 2] << n16) +
             (information_header[n4 + 3] << n24));
    SetHeight(information_header[n8] + (information_header[n8 + 1] << n8) + (information_header[n8 + 2] << n16) +
              (information_header[n8 + 3] << n24));

    image_.resize(GetHeight());
    for (size_t y = 0; y < GetHeight(); ++y) {
        image_[y].resize(GetWidth());
    }

    const size_t n255 = 255.0f;

    const int padding_amount = ((4 - (GetWidth() * 3) % 4) % 4);

    for (int y = 0; y < GetHeight(); ++y) {
        for (int x = 0; x < GetWidth(); ++x) {
            unsigned char color[3];
            bmp.read(reinterpret_cast<char *>(color), 3);

            image_[y][x].r = static_cast<float>(color[2]) / n255;
            image_[y][x].g = static_cast<float>(color[1]) / n255;
            image_[y][x].b = static_cast<float>(color[0]) / n255;
        }
        bmp.ignore(padding_amount);
    }
    bmp.close();

    std::cout << "Файл успешно прочитан" << std::endl;
    delete[] file_header;
    delete[] information_header;
}

void Image::Export(const char *path) const {
    std::ofstream bmp;
    bmp.open(path, std::ios::out | std::ios::binary);

    if (!bmp.is_open()) {
        std::cout << "Невозможно открыть файл" << std::endl;
        return;
    }
    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding_amount = ((4 - (GetWidth() * 3) % 4) % 4);

    const int file_size =
        GetBMPHeaderSize() + GetDIBHeaderSize() + GetWidth() * GetHeight() * 3 + padding_amount * GetWidth();

    unsigned char *file_header = new unsigned char[GetBMPHeaderSize()];

    file_header[0] = 'B';
    file_header[1] = 'M';

    const size_t n5 = 5;
    const size_t n6 = 6;
    const size_t n7 = 7;
    const size_t n8 = 8;
    const size_t n9 = 9;
    const size_t n10 = 10;
    const size_t n11 = 11;
    const size_t n12 = 12;
    const size_t n13 = 13;
    const size_t n14 = 14;
    const size_t n15 = 15;
    const size_t n16 = 16;
    const size_t n17 = 17;
    const size_t n18 = 18;
    const size_t n19 = 19;
    const size_t n20 = 20;
    const size_t n21 = 21;
    const size_t n22 = 22;
    const size_t n23 = 23;
    const size_t n24 = 24;
    const size_t n25 = 25;
    const size_t n26 = 26;
    const size_t n27 = 27;
    const size_t n28 = 28;
    const size_t n29 = 29;
    const size_t n30 = 30;

    file_header[2] = file_size;
    file_header[3] = file_size >> n8;
    file_header[4] = file_size >> n16;
    file_header[n5] = file_size >> n24;

    file_header[n6] = 0;
    file_header[n7] = 0;

    file_header[n8] = 0;
    file_header[n9] = 0;

    file_header[n10] = GetBMPHeaderSize() + GetDIBHeaderSize();
    file_header[n11] = 0;
    file_header[n12] = 0;
    file_header[n13] = 0;

    unsigned char *information_header = new unsigned char[GetDIBHeaderSize()];

    information_header[0] = GetDIBHeaderSize();
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;

    information_header[4] = GetWidth();

    const size_t n31 = 31;
    const size_t n32 = 32;
    const size_t n33 = 33;
    const size_t n34 = 34;
    const size_t n35 = 35;
    const size_t n36 = 36;
    const size_t n37 = 37;
    const size_t n38 = 38;
    const size_t n39 = 39;

    information_header[n5] = GetWidth() >> n8;
    information_header[n6] = GetWidth() >> n16;
    information_header[n7] = GetWidth() >> n24;

    information_header[n8] = GetHeight();
    information_header[n9] = GetHeight() >> n8;
    information_header[n10] = GetHeight() >> n16;
    information_header[n11] = GetHeight() >> n24;

    information_header[n12] = 1;
    information_header[n13] = 0;

    information_header[n14] = n24;
    information_header[n15] = 0;

    information_header[n16] = 0;
    information_header[n17] = 0;
    information_header[n18] = 0;
    information_header[n19] = 0;

    information_header[n20] = 0;
    information_header[n21] = 0;
    information_header[n22] = 0;
    information_header[n23] = 0;

    information_header[n24] = 0;
    information_header[n25] = 0;
    information_header[n26] = 0;
    information_header[n27] = 0;

    information_header[n28] = 0;
    information_header[n29] = 0;
    information_header[n30] = 0;
    information_header[n31] = 0;

    information_header[n32] = 0;
    information_header[n33] = 0;
    information_header[n34] = 0;
    information_header[n35] = 0;

    information_header[n36] = 0;
    information_header[n37] = 0;
    information_header[n38] = 0;
    information_header[n39] = 0;

    const size_t n255 = 255.0f;

    bmp.write(reinterpret_cast<char *>(file_header), GetBMPHeaderSize());
    bmp.write(reinterpret_cast<char *>(information_header), GetDIBHeaderSize());
    for (int y = 0; y < GetHeight(); ++y) {
        for (int x = 0; x < GetWidth(); ++x) {
            unsigned char r = static_cast<unsigned char>(image_[y][x].r * n255);
            unsigned char g = static_cast<unsigned char>(image_[y][x].g * n255);
            unsigned char b = static_cast<unsigned char>(image_[y][x].b * n255);

            unsigned char pixel[] = {b, g, r};

            bmp.write(reinterpret_cast<char *>(pixel), 3);
        }
        bmp.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }
    bmp.close();

    std::cout << "Файл успешно создан" << std::endl;
    delete[] file_header;
    delete[] information_header;
}