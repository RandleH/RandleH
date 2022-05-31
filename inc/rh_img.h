

#include <stdio.h>
#include <stdlib.h>


#ifndef RH_IMG_H
#define RH_IMG_H


#ifdef __cplusplus
extern "C"{
#endif


int rh_img__write_bmp( const char *filename, int x, int y, int comp, const void *data, int strides);//
int rh_img__write_jpg( const char *filename, int x, int y, int comp, const void *data, int strides);//
int rh_img__write_png( const char *filename, int x, int y, int comp, const void *data, int strides);//



#ifdef __cplusplus
}
#endif

#endif
