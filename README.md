# Description
 This repository aims to accelerate various algortihms using vectorization, parallelism and GPGPU programming. 
 Any sort of recommendations, improvements and even contributions are welcome.
 
All programs are compiled using the Intel-C++ compiler as I run an intel machine. Therefore all #pragma directives are for intel-specific architectures. (OS - Ubuntu 20.04 LTS)
Some programs will have a architecture specific compilation, namely AVX2. 
However, if it is required to compile for some other architecture say SSE, it can recompiled with the icpc compiler directives. 

All the present and upcoming SYCL/openCL codes are tested on an RTX 2070 and an Intel i7 9750H
