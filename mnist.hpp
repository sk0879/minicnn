#ifndef MNIST_HPP
#define MNIST_HPP

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include "tensor.hpp"

#ifdef MNIST_PRE_PAD
#define PRE_PAD 2
#else
#define PRE_PAD 0
#endif

class MNIST {
public:
    // Constructor to initialize the MNIST class with the path to the dataset file
    MNIST(std::string path) : pad_(PRE_PAD), path_(path) {
        load();
    }

    // Function to load MNIST data from a file
    void load() {
        // ... (Your existing load() function implementation)
    }

    // Function to get a single image at a specified index
    Tensor at(size_t idx) {
        assert(idx < imgs_.N && "Index out of bounds");
        return imgs_.slice(idx, 1);
    }

    // Function to get a slice of images starting from a specified index
    Tensor slice(size_t idx, size_t num) {
        assert(idx + num <= imgs_.N && "Index out of bounds");
        return imgs_.slice(idx, num);
    }

    // Function to print a single image at a specified index
    void print(size_t idx) {
        assert(idx < imgs_.N && "Index out of bounds");
        auto img = at(idx);
        printImage(img);
    }

    // Function to print all images in the MNIST dataset
    void printAllImages() {
        for (size_t n = 0; n < imgs_.N; ++n) {
            printImage(at(n));
        }
    }

    // Function to get the total number of images in the dataset
    size_t totalImages() {
        return imgs_.N;
    }

private:
    // Function to check the endianness of the system
    bool isLittleEndian() {
        int n = 1;
        return *(char *)&n == 1;
    }

    // Function to print an individual image
    void printImage(const Tensor& img) {
        for (size_t h = pad_; h < 28 + pad_; ++h) {
            for (size_t w = pad_; w < 28 + pad_; ++w) {
                int val = static_cast<int>(img(0, 0, h, w) * 255.f);
                std::cout << (val > 0 ? "x" : " ");
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------------\n";
    }

    Tensor imgs_;
    size_t pad_;
    std::string path_;
};

#endif // MNIST_HPP
