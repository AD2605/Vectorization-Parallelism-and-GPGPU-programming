### Convolutional Neural Network implementation in SYCL

This part of the repo aims to implement the convolutional neural and parallelize it using SYCL. This is a batched implementation with input as
`[batch, in_channels, width, height]` as in pytorch. I will soon replace the input from `float*` to a `tensor_accessor` from libtorch so that the user 
does not need to input width and height in each layer(Though this might take time, Dismantling pytorch is really hard). 
