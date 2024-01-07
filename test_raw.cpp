#include <iostream>
#include <fstream>

void readWeightsAndBiases(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    // Read the header (assuming it contains necessary information)
    size_t outputChannel, inputChannel, kernelHeight, kernelWidth;
    file.read(reinterpret_cast<char*>(&outputChannel), sizeof(outputChannel));
    file.read(reinterpret_cast<char*>(&inputChannel), sizeof(inputChannel));
    file.read(reinterpret_cast<char*>(&kernelHeight), sizeof(kernelHeight));
    file.read(reinterpret_cast<char*>(&kernelWidth), sizeof(kernelWidth));

    std::cout << "Output Channels: " << outputChannel << std::endl;
    std::cout << "Input Channels: " << inputChannel << std::endl;
    std::cout << "Kernel Height: " << kernelHeight << std::endl;
    std::cout << "Kernel Width: " << kernelWidth << std::endl;

    // Read weights and biases
    for (size_t outputIdx = 0; outputIdx < outputChannel; ++outputIdx) {
        for (size_t inputIdx = 0; inputIdx < inputChannel; ++inputIdx) {
            for (size_t heightIdx = 0; heightIdx < kernelHeight; ++heightIdx) {
                for (size_t widthIdx = 0; widthIdx < kernelWidth; ++widthIdx) {
                    float weight;
                    file.read(reinterpret_cast<char*>(&weight), sizeof(weight));
                    std::cout << "Weight[" << outputIdx << "][" << inputIdx << "][" << heightIdx << "][" << widthIdx << "]: " << weight << std::endl;
                }
            }
        }
    }

    file.close();
}

int main() {
    readWeightsAndBiases("lenet.raw");
    return 0;
}

