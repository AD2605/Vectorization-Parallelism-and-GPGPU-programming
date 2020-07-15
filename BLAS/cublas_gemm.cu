#include <cstdlib>
#include <cublas_v2.h>
#include <curand.h>
#include <ctime>
#include <iostream>

void gpu_cublas(const float* A, const float* B, float* C, int m, int n, int k)
{
    int lda=m,ldb=k,ldc=m;
    const float alf = 1;
    const float bet = 0;
    const float *alpha = &alf;
    const float *beta = &bet;

    cublasHandle_t handle;
    cublasCreate(&handle);
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m,n,k, alpha, A, lda, B, ldb, beta, C, ldc);
    cublasDestroy(handle);
}

int main()
{
    int nr_rows_A =3,
        nr_cols_A=3,
        nr_rows_B=3,
        nr_cols_B=3,
        nr_rows_C=3,
        nr_cols_C=3;

    float *d_A, *d_B, *d_C;
    auto *h_A = (float *)malloc(nr_rows_A * nr_cols_A * sizeof(float));
    auto *h_B = (float *)malloc(nr_rows_B * nr_cols_B * sizeof(float));
    auto *h_C = (float *)malloc(nr_rows_C * nr_cols_C * sizeof(float));

    cudaMalloc(&d_A,nr_rows_A * nr_cols_A * sizeof(float));
    cudaMalloc(&d_B,nr_rows_B * nr_cols_B * sizeof(float));
    cudaMalloc(&d_C,nr_rows_C * nr_cols_C * sizeof(float));

    curandGenerator_t generator;
    curandCreateGenerator(&generator, CURAND_RNG_PSEUDO_DEFAULT);
    curandSetPseudoRandomGeneratorSeed(generator, (unsigned long long ) clock());
    curandGenerateUniform(generator, h_A, nr_rows_A * nr_cols_A);
    curandGenerateUniform(generator, h_B, nr_rows_B*nr_cols_B);
    std::cout<<"GENERATED MATRICES";
    //cudaMemcpy(d_A,h_A,nr_rows_A * nr_cols_A * sizeof(float),cudaMemcpyHostToDevice);
    //cudaMemcpy(d_B,h_B,nr_rows_B * nr_cols_B * sizeof(float),cudaMemcpyHostToDevice);
    gpu_cublas(d_A, d_B, d_C, nr_rows_A, nr_cols_A, nr_rows_B);
    cudaMemcpy(h_C,d_C, nr_rows_C*nr_cols_C*sizeof(float), cudaMemcpyDeviceToHost);
    std::cout<<"C = "<<std::endl;
    for (int i = 0; i <nr_rows_A ; ++i) {
        for (int j = 0;j<nr_rows_A; ++j){
            std::cout << h_C[j * nr_rows_A + i] << " ";
        }
        std::cout<<std::endl;
    }
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);

}