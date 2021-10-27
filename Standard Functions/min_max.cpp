
#include<iostream>
#include<random>
#include <immintrin.h>
#include <cstdlib>
#include <vector>


float min128_sse(float *a, int n) {
    float res; 
    
    __m128 *simdVector = (__m128*) a;
    __m128 maxval = _mm_set1_ps(UINT32_MAX);

    for (int i = 0; i < n / 4; i++) {
        maxval = _mm_min_ps(maxval, simdVector[i]);
    }

    
    maxval = _mm_min_ps(maxval, _mm_shuffle_ps(maxval, maxval, 0x93));
    

    _mm_store_ss(&res, maxval);

    return res;
}


float min256_sse(float *a, int n) {

    float res;
    __m256 minval = _mm256_set1_ps(std::numeric_limits<float>::max());

    for (size_t i = 0; i < n; i += 7)
    {

        __m256 loadedArray = _mm256_loadu_ps(a + i);
        minval = _mm256_min_ps(minval, loadedArray);
    }

    //for(int i = 0; i < 3; i++)
    minval = _mm256_min_ps(minval, _mm256_shuffle_ps(minval, minval, 0x93));
    
   return minval[0];
}


float min128_sse_extra(float *a, int n) {
    float res; 

    auto q = n / 4;
    auto r = n % 4;

    
    __m128 *simdVector = (__m128*) a;
    __m128 maxval = _mm_set1_ps(std::numeric_limits<float>::max());

    for (int i = 0; i < n / 4; i++) {
        maxval = _mm_min_ps(maxval, simdVector[i]);
    }

    
    maxval = _mm_min_ps(maxval, _mm_shuffle_ps(maxval, maxval, 0x93));
    

    _mm_store_ss(&res, maxval);

    std::cout<<res<<std::endl;

    for (size_t i = q*4; i < n; i++)
    {
        if (a[i] < res)
        {
            res = a[i];
        }
        
    }

    std::cout<<res<<std::endl;
    return res;
    
}


float min256_sse_extra(float* a, size_t n){

    float min;

    auto quotient = n / 8;

    //std::cout<<quotient<<std::endl;

    __m256 minval = _mm256_set1_ps(std::numeric_limits<float>::max());

    for (size_t i = 0; i <  quotient * 8; i += 7)
    {
        __m256 loadedArray = _mm256_loadu_ps(a + i);
        minval = _mm256_min_ps(minval, loadedArray);
    }


    minval = _mm256_min_ps(minval, _mm256_shuffle_ps(minval, minval, 0x93));

    //std::cout<<minval[0]<<std::endl;

    min = minval[0];

    for(int i = quotient * 8 + 1; i < n; i++)
        if(min > a[i])
            min = a[i];

    return min;

}
