#include "Regression.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){
    size_t size = 32768;
    std::vector<float> input_vector(size, 1.0f);

    LinearRegression linearRegression(size); //Initialize the Class.
    linearRegression.sycl(" "); //call the .sycl() method to run the forward and Backward on SPIR supported Devices.
    float output = linearRegression.forward(input_vector);

    // One can choose Devices by Vendor Names, AMD, Intel, Arm or
    // by Device type, GPU, CPU and the HOST.
    // One can change the target Device after Initialization as well.

    float loss = -2.0124;
    float learning_rate = 1e-3;
    linearRegression.setDevice(std::string("Intel"));

    linearRegression.backward(loss, learning_rate);
}
