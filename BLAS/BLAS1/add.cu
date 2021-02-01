#include <cstdio>
#include <cstdlib>
#include <cmath>

// CUDA kernel. Each thread takes care of one element of c

__global__ void vecAdd(double *a, double *b, double *c, int n)
{
    // Get our global thread ID
    uint id = blockIdx.x*blockDim.x+threadIdx.x;

    // Make sure we do not go out of bounds
    if (id < n)
        c[id] = a[id] + b[id];
}

__global__ void matrixAdd(double * a, double * b, double * c,int width, int height ){
    uint i = blockIdx.x * blockDim.x + threadIdx.x;
    uint j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i< width and j < height){
        *(c + i*width + j) = *(a + i*width + j) + *(b + i*width + j);
    }

}

int main( int argc, char* argv[] )
{
    int width = 4096;
    int height = 8192;
    double count = 1.0;

    dim3 threads(512, 512);
    dim3 groups(int(ceil(width*height*sizeof(double )/threads.x)), int(ceil(width*height* sizeof(double )/threads.y)));

    dim3 threads_1D(1024);
    dim3 groups_1D(int(ceil(width*height*sizeof(double )/threads.x)));

    double * host_A, *host_B,*host_C, *host_C1D;
    double* device_A, *device_B, *device_C, *device_C1D;

    host_A = (double *)malloc(width * height * sizeof(double ));
    host_B = (double *)malloc(width * height * sizeof(double ));
    host_C = (double *)malloc(width * height * sizeof(double ));
    host_C1D = (double *)malloc(width * height * sizeof(double ));

    for(int i = 0; i<width; i++){
        for (int j = 0;j<height;j++){
            *(host_A + i*width + j) = *(host_B + i*width + j) = ++count;
        }
    }

    cudaMalloc((&device_A), width*height* sizeof(double ));
    cudaMalloc((&device_B), width*height* sizeof(double ));
    cudaMalloc((&device_C), width*height* sizeof(double ));
    cudaMalloc((&device_C1D), width*height* sizeof(double ));

    cudaMemcpy(device_A, host_A, width*height* sizeof(double ), cudaMemcpyHostToDevice);
    cudaMemcpy(device_B, host_B, width*height* sizeof(double ), cudaMemcpyHostToDevice);

    matrixAdd<<<groups, threads>>>(device_A, device_B, device_C, width);
    vecAdd<<<groups_1D, threads_1D>>>(device_A, device_B, device_C1D);

    cudaMemcpy(host_C, device_C, width*height* sizeof(double ), cudaMemcpyDeviceToHost);

    for(int i = 0; i<width; i++){
        for (int j = 0;j<height;j++){
            printf("%f ", *(host_A + i*width + j));
            printf("%s", "  ");
        }
    }

}