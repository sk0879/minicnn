#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "tensor.hpp"

bool is_little_endian() {
    int n = 1;
    return *(char*)&n == 1;
}

void readWeightsAndBiases(const std::string& filename) {
    size_t output_channel, input_channel, kernel_height, kernel_width;

    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&output_channel), sizeof(size_t));
    file.read(reinterpret_cast<char*>(&input_channel), sizeof(size_t));
    file.read(reinterpret_cast<char*>(&kernel_height), sizeof(size_t));
    file.read(reinterpret_cast<char*>(&kernel_width), sizeof(size_t));

    if (is_little_endian()) {
        std::reverse(reinterpret_cast<char*>(&output_channel), reinterpret_cast<char*>(&output_channel) + sizeof(size_t));
        std::reverse(reinterpret_cast<char*>(&input_channel), reinterpret_cast<char*>(&input_channel) + sizeof(size_t));
        std::reverse(reinterpret_cast<char*>(&kernel_height), reinterpret_cast<char*>(&kernel_height) + sizeof(size_t));
        std::reverse(reinterpret_cast<char*>(&kernel_width), reinterpret_cast<char*>(&kernel_width) + sizeof(size_t));
    }

    Tensor weights_(output_channel, input_channel, kernel_height, kernel_width);

    for (size_t n = 0; n < output_channel; ++n) {
        for (size_t c = 0; c < input_channel; ++c) {
            for (size_t h = 0; h < kernel_height; ++h) {
                for (size_t w = 0; w < kernel_width; ++w) {
                    float val;
                    if (file.read(reinterpret_cast<char*>(&val), sizeof(float))) {
                        weights_(n, c, h, w) = val;
                        std::cout << weights_(n, c, h, w) << "\n";
                    } else {
                        std::cerr << "Error reading float value at position (" << n << ", " << c << ", " << h << ", " << w << ")\n";
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    // Replace "your_binary_file.dat" with the actual filename
    readWeightsAndBiases("/mnt/d/Etudes/Computer-Vision/assignment/lenet.raw");

    return 0;
}
