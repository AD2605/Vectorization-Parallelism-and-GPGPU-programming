//
// Created by atharva on 07/06/20.
//
#include "image.h"
#ifndef MATRIX_MULTIPLICATION_ERODE_DILATE_H
#define MATRIX_MULTIPLICATION_ERODE_DILATE_H
template<typename type>
void Erode(ImageClass<type> & img_in, ImageClass<type> & img_out, int kernel_size);

template<typename type>
void Dilate(ImageClass<type> & img_in, ImageClass<type> & img_out, int kernel_size);

#endif
