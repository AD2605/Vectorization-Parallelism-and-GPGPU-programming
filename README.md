# Description
 This repository aims to accelerate various algortihms using vectorization, parallelism and GPGPU programming. 
 Any sort of recommendations, improvements and even contributions are welcome.
 
All programs are compiled using the Intel-C++ compiler as I run an intel machine. Therefore all #pragma directives are for intel-specific architectures. (OS - Ubuntu 20.04 LTS)
Some programs will have a architecture specific compilation, namely AVX2. 
However, if it is required to compile for some other architecture say SSE, it can recompiled with the icpc compiler directives. 

All the present and upcoming SYCL/openCL codes are tested on an RTX 2070 and an Intel i7 9750H and the Intel Neo GPU (iGPU, Intel UHD Graphics 630)

Currently the It contains the Following Operations - 
* BLAS I and some BLAS II routines.
* Filter Convolutions and Morphological operations like Erode and Dilate.
* A Convolutional Layer(Without the Backprop, hopefully I will commit that soon)
* Linear layer (wx^T + b) both forward as well as backprop(dL/dW and dL/dX). Currently the matmul is implemented in openMP.
  I will include forward and backward definitions which pass it off to the local BLAS. (sgemm_ for CPU and cuBLAS for CUDA. for SYCL, Matmul to be coded). 
* Machine Learning Models like Linear and Logistic regression, Bayes and Markov chains(Soon)
* Activations like Relu, Leaky Relu(Both are non divergent operations) and Tanh
* Parallel sorting and graph traversals

In terms of usability, each file contains just the function and class definitions. Also, I am still pondering a way to make a device selector interface for
SYCL. 
