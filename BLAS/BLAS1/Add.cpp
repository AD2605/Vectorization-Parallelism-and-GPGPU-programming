void constAdd(float* input, int width, int height){
    queue Queue;
    buffer<float, 1> Buffer{input, width*height};
    buffer<float, 1> result{width * height};
    Queue.submit([&Buffer, &result, width, height](handler& Handler){
       auto data = Buffer.get_access<access::mode::read>(Handler);
       auto result_Accessor = result.get_access<access::mode::write>(Handler);

       Handler.parallel_for<exampleClass>(range<1> (width), [data, result_Accessor, width, height](id<1> idx){
           for (int k = 0; k < height; ++k) {
               auto position = idx[0]*width + k;
               result_Accessor[position] = data[position] + 1e2;
           }
       });
    });

    auto accessor = result.get_access<access::mode::read>();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            std::cout<<accessor[i*width + j]<<"  ";
        }
    }
}

void Add(float * A, float* B, size_t width, size_t height){
    queue Queue;
    buffer<float, 1> buffer_A{A, {width *height}};
    buffer<float, 1> buffer_B{B, {width *height}};
    buffer<float, 1> buffer_C{{width *height}};

    Queue.submit([&buffer_A, &buffer_B, &buffer_C, width, height](handler& Handler){
       auto A_Accessor = buffer_A.get_access<access::mode::read>(Handler);
       auto B_Accesor = buffer_B.get_access<access::mode::read>(Handler);
       auto C_Accessor = buffer_C.get_access<access::mode::write>(Handler);

       Handler.parallel_for<exampleAdd>(range<2> {width, height},[A_Accessor, B_Accesor, C_Accessor, width]
       (id<2> item){

           C_Accessor[item[0]*width + item[1]] = A_Accessor[item[0]*width + item[1]] + B_Accesor[item[0]*width + item[1]];

       });
    });

    auto accessor = buffer_C.get_access<access::mode::read>();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            //std::cout<<accessor[i*width + j]<<"  ";
            ;
        }
    }

}
