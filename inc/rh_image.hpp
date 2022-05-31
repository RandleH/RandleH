#ifndef RH_IMAGE_H
#define RH_IMAGE_H


#include <iostream>
#include <cstdint>
#include <cstddef>

namespace rh_image{

template<typename T>
class Img{
public:
    Img();
    void *load( const char *path );
    size_t n_rows;
    size_t n_cols;
    size_t n_byte;
    
    int    img_type;
    
    arma::Cube<uint8_t> pix;
    
private:
    T*     memptr;
};


template<typename T>
Img<T>::Img():pix(),n_rows(0),n_cols(0){
    
}



template<typename T>
void* Img<T>::load(const char* path){
    std::cout<<path<<std::endl;
    int r,c,ch;
    
    auto ptr = stbi_load(path, (int*)(&r), (int*)(&c), &ch, 0);
    auto ptr1 = ptr;
    n_rows = (size_t)r;
    n_cols = (size_t)c;
    
    switch(ch){
        case 3:{
            pix = arma::Cube<uint8_t>( n_rows, n_cols, 3 );
            uint8_t *pR = pix.memptr();
            uint8_t *pG = pR+n_rows*n_cols;
            uint8_t *pB = pG+n_rows*n_cols;
            
            for(size_t y=0; y<n_rows; ++y){
                for(size_t x=0; x<n_cols; ++x, ++pR, ++pG, ++pB){
                    *pR = *ptr++;
                    *pG = *ptr++;
                    *pB = *ptr++;
                }
            }
            break;
        }
        default:
            break;
    }
    
    std::cout<<n_rows<<'x'<<n_cols<<std::endl<<"Channel:"<<ch<<std::endl;
    
  

    
    return ptr1;
}


typedef Img <uint8_t>   imgbin;
typedef Img <uint8_t>   img256;
typedef Img <uint16_t>  img565;
typedef Img <uint32_t>  img888a;

}

#endif
