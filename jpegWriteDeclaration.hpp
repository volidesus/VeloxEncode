#include <vector>
#include <string>

#ifndef JPEGWRITEDECLARATION_HPP
#define JPEGWRITEDECLARATION_HPP

#pragma pack(push, 1)
struct JPEGheader {
    uint16_t file_type{ 0x4D42 };
    uint32_t file_size{ 0 };
    uint16_t reserved1{ 0 };
    uint16_t reserved2{ 0 };
    uint32_t offset_data{ 0 };
    uint32_t header_size{ 40 };
    int32_t width{ 0 };
    int32_t height{ 0 };
    uint16_t planes{ 1 };
    uint16_t bits_per_pixel{ 24 };
    uint32_t compression{ 0 };
    uint32_t size_image{ 0 };
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };
    uint32_t colors_important{ 0 };
};
#pragma pack(pop)

void writeJPEG(const std::vector<std::vector<bool>>& data, const std::string& filename, int pixelSize);

#endif
