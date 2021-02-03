#ifndef SYCL_DNN_CONVOLUTION_H
#define SYCL_DNN_CONVOLUTION_H

#include <CL/sycl.hpp>
#include <vector>
#include <iostream>

using namespace cl::sycl;

class Convolution2D{
public:

    Convolution2D(size_t in_channels, size_t out_channels, size_t kernel_size[], size_t padding, size_t stride,
                  size_t height, size_t width, size_t batch);
    float* forward(float* input, queue Queue);

private:

    size_t in_channels;
    size_t out_channels;
    size_t kernel[2];
    size_t width;
    size_t height;
    size_t batch;
    size_t stride;
    size_t padding;

    std::vector<std::vector<float*>> Kernels;
    float* Bias;
};


#endif //SYCL_DNN_CONVOLUTION_H
