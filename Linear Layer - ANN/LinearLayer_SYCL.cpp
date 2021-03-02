#include <CL/sycl.hpp>
#include <SYCL/memory_scope.h>
#include <SYCL/common.h>
#include <random>


class linearForward;
using namespace cl::sycl;

class Linear{
public:
    Linear(size_t in_features, size_t out_features){
        std::random_device device{};
        std::normal_distribution<float> distribution{0, 2};

        std::mt19937 generator{device()};
        this->in_features = in_features;
        this->out_features = out_features;

        this->weights = (float*)malloc(in_features*out_features*sizeof(float));
        this->bias = (float*)malloc(out_features*sizeof(float));
        this->in_features = in_features;
        this->out_features = out_features;

        for(int i=0; i<this->in_features; i++){
            for (int j=0; j<out_features; j++){
                *(weights + i*in_features + j) = distribution(generator);
            }
        }

        for(int i=0; i<this->out_features; i++){
            *(this->bias+i) = distribution(generator);
        }
    }

    float* forward(float* input, queue Queue, size_t batch_size){
      // This should ideally be dispatched to the BLAS Handle. Have to Install SYCL-BLAS
        this->current_input = input;
        float* output = (float*)malloc(batch_size * this->out_features * sizeof(float ));

        buffer<float, 1 >weight_buffer{this->weights, {this->in_features * this->out_features}};
        buffer<float, 1>bias_buffer{this->bias, {this->out_features}};
        buffer<float, 1>input_buffer{input, {batch_size * this->in_features}};
        buffer<float, 1>output_buffer{output, {batch_size * this->out_features}};
        auto in = this->in_features; auto out = this->out_features;

        Queue.submit([&weight_buffer, &bias_buffer, &input_buffer, &output_buffer, in, out, batch_size](handler& cgh){
            auto weight_ptr = weight_buffer.get_access<access::mode::read>(cgh);
            auto bias_ptr = bias_buffer.get_access<access::mode::read>(cgh);
            auto input_ptr = input_buffer.get_access<access::mode::read>(cgh);
            auto output_ptr = output_buffer.get_access<access::mode::write>(cgh);

            cgh.parallel_for<linearForward>(range<2>(batch_size, out), [weight_ptr, bias_ptr, input_ptr, output_ptr, in, batch_size, out](id<2> idx){
                float sum = 0.0f;
                for(int i=0; i<in; i++){
                    auto input_matrix_id = batch_size*idx.get(0) + i;
                    auto weight_matrix_id = out*i + idx.get(1);

                    sum += input_ptr[input_matrix_id] * weight_ptr[weight_matrix_id];
                }
                auto output_matrix_id = batch_size*idx.get(0) + idx.get(1);
                output_ptr[output_matrix_id] = sum + bias_ptr[idx.get(1)];
            });
        });

        return output;
    }

private:
    size_t in_features;
    size_t out_features;

    float* weights;
    float* bias;
    float* current_input;
};
