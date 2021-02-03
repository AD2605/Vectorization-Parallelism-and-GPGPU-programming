#include "Convolution.h"
#include <random>

#include <CL/sycl.hpp>
using namespace cl::sycl;
class convForward;
Convolution2D::Convolution2D(size_t in_channels, size_t out_channels, size_t kernel_size[], size_t padding,
                             size_t stride, size_t height, size_t width, size_t batch) {
    this->in_channels = in_channels;
    this->out_channels = out_channels;
    this->kernel[0] = kernel[0];
    this->kernel[1] = kernel[1];
    this->padding = padding;
    this->stride = stride;
    this->height = height;
    this->batch = batch;
    this->width = width;

    srand((float)time(NULL));

#pragma omp parallel for
    for (int i = 0; i < this->in_channels; i++) {
#pragma omp simd
        for (int j = 0; j < this->out_channels; j++) {
            this->Kernels[i][j] = (float *)malloc(kernel_size[0]*kernel_size[1]*sizeof(float ));

            for (int k = 0; k < kernel_size[0]; k++) {
                for (int l = 0; l < kernel_size[1]; l++) {
                    *(this->Kernels[i][j] + (k*kernel_size[0] + l)*sizeof(float )) = float(rand()/RAND_MAX);
                }
            }
        }
    }

    this->Bias = (float *)malloc(this->out_channels*sizeof(float ));
#pragma omp parallel for
    for (int i = 0; i < this->out_channels; ++i) {
        *(this->Bias + i) = rand()/RAND_MAX;
    }
}

float *Convolution2D::forward(float *input, queue Queue){
    /*
     * The input is a multidimensional array of shape Batch * num_channels * width * height
     * I do have to verify once whether am I convolving correctly.
     * */

    size_t output_height = (this->height - this->kernel[1] + 2* this->padding)/ this->stride + 1;
    size_t output_width = (this->width - this->kernel[0] + 2* this->padding)/ this->stride + 1;
    size_t size = 1;
    buffer<float, 1>buffer_input{input, {this->batch * this->in_channels * this->width * this->height}};
    buffer<float, 1>buffer_output{{this->batch * this->out_channels * output_width * output_height}};

    auto kernels = this->Kernels;
    auto channels = this->in_channels;
    auto batch = this->batch;
    auto height = this->height;
    auto width = this->width;
    auto out_channels = this->out_channels;
    Queue.submit([&buffer_input, &buffer_output, kernels, batch, height, width, out_channels, channels](handler& Handler){
        auto input_accessor = buffer_input.get_access<access::mode::read>(Handler);
        auto output_accessor = buffer_output.get_access<access::mode::write>(Handler);
        Handler.parallel_for_work_group<convForward>(range<3>{channels, width, height}, [input_accessor, output_accessor, kernels, batch, height, width, out_channels, channels]
                (id<3> item){
            for(int j=0; j<batch; j++){
                float image = input_accessor[batch*width*channels*j];

            }
        });
    });
    return nullptr;
}

