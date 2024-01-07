#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Tensor {
public:
    Tensor() : Tensor(0, 0, 0, 0) {}
    Tensor(size_t n) : Tensor(n, 1, 1, 1) {}
    Tensor(size_t n, size_t c) : Tensor(n, c, 1, 1) {}
    Tensor(size_t n, size_t c, size_t h) : Tensor(n, c, h, 1) {}
    Tensor(size_t n, size_t c, size_t h, size_t w) :
        N(n), C(c), H(h), W(w), offset_(0), data_(std::make_shared<std::vector<float>>(n * c * h * w)) {}
    Tensor(size_t n, size_t c, size_t h, size_t w, size_t offset, std::shared_ptr<std::vector<float>> data) :
        N(n), C(c), H(h), W(w), offset_(offset), data_(data) {}

    bool empty() const {
        return data_->empty();
    }

    float* data() {
        return data_->data();
    }

    void fill(float c) {
        std::fill(data_->begin(), data_->end(), c);
    }

    void print() const {
        for (size_t n = 0; n < N; ++n) {
            for (size_t c = 0; c < C; ++c) {
                for (size_t h = 0; h < H; ++h) {
                    for (size_t w = 0; w < W; ++w) {
                        std::cout << operator()(n, c, h, w) << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
    }

    float& operator()(size_t n, size_t c = 0, size_t h = 0, size_t w = 0) {
        size_t index = offset_ + n * (C * H * W) + c * (H * W) + h * W + w;
        return data()[index];
    }

    Tensor slice(size_t idx, size_t num) const {
        size_t offset = offset_ + idx * C * H * W;
        return Tensor(num, C, H, W, offset, data_);
    }

    std::ostream& write(std::ostream& os) const {
        return os << N << "x" << C << "x" << H << "x" << W;
    }

    size_t N, C, H, W;

private:
    size_t offset_;
    std::shared_ptr<std::vector<float>> data_;
};

std::ostream& operator<<(std::ostream& os, const Tensor& t) {
    return t.write(os);
}

#endif // TENSOR_HPP
