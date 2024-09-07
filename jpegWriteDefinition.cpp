#include <cstdint>
#include <fstream>
#include <vector>
#include "jpegWriteDeclaration.hpp"

void writeJPEG(const std::vector<std::vector<bool>>& data, const std::string& filename, int pixelSize) {
    int width = data[0].size() * pixelSize;
    int height = data.size() * pixelSize;
    int paddingAmount = ((4 - (width * 3) % 4) % 4);

    JPEGheader header;
    header.file_size = sizeof(JPEGheader) + (width * 3 + paddingAmount) * height;
    header.offset_data = sizeof(JPEGheader);
    header.width = width;
    header.height = height;
    header.size_image = (width * 3 + paddingAmount) * height;

    std::ofstream outfile(filename, std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(&header), sizeof(header));

    std::vector<unsigned char> padding(paddingAmount, 0);
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            int dataY = y / pixelSize;
            int dataX = x / pixelSize;
            unsigned char color = data[dataY][dataX] ? 0 : 255;
            outfile.write(reinterpret_cast<const char*>(&color), 1);
            outfile.write(reinterpret_cast<const char*>(&color), 1);
            outfile.write(reinterpret_cast<const char*>(&color), 1);
        }
        if (paddingAmount > 0) {
            outfile.write(reinterpret_cast<const char*>(padding.data()), paddingAmount);
        }
    }
}