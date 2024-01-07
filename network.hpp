#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "tensor.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath> // Added for the exp() function
#include <vector>

enum class LayerType : uint8_t {
    Conv2d = 0,
    Linear,
    MaxPool2d,
    ReLu,
    SoftMax,
    Flatten
};

std::ostream& operator<<(std::ostream& os, LayerType layer_type) {
    switch (layer_type) {
        case LayerType::Conv2d: return os << "Conv2d";
        case LayerType::Linear: return os << "Linear";
        case LayerType::MaxPool2d: return os << "MaxPool2d";
        case LayerType::ReLu: return os << "ReLu";
        case LayerType::SoftMax: return os << "SoftMax";
        case LayerType::Flatten: return os << "Flatten";
    };
    return os << static_cast<std::uint8_t>(layer_type);
}

class Layer {
public:
    Layer(LayerType layer_type) : layer_type_(layer_type), input_(), weights_(), bias_(), output_() {}

    virtual void fwd() = 0;
    virtual void read_weights_bias(std::ifstream& is) = 0;

    void print() {
        std::cout << layer_type_ << std::endl;
        if (!input_.empty()) std::cout << "  input: " << input_ << std::endl;
        if (!weights_.empty()) std::cout << "  weights: " << weights_ << std::endl;
        if (!bias_.empty()) std::cout << "  bias: " << bias_ << std::endl;
        if (!output_.empty()) std::cout << "  output: " << output_ << std::endl;
    }

    virtual Tensor get_input() = 0; // Make it virtual

    // TODO: additional required methods

protected:
    const LayerType layer_type_;
    Tensor input_;
    Tensor weights_;
    Tensor bias_;
    Tensor output_;
};

class Conv2d : public Layer {
public:
    // ... (Existing code)

    Tensor get_input() override; // Implement the virtual function

    void fwd() override;

    // ... (Existing code)
};

class NeuralNetwork {
public:
    NeuralNetwork(bool debug = false) : debug_(debug) {}

    void add(Layer* layer);

    void load(std::string file);

    Tensor predict(Tensor input);

private:
    bool debug_;
    std::vector<Layer*> lenet; // Use pointers for polymorphism

    // ... (Existing code)
};

#endif // NETWORK_HPP
