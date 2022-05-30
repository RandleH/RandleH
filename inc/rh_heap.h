

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#ifndef RH_HEAP_H
#define RH_HEAP_H



void  rh_heap__make   ( void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) );//
bool  rh_heap__isheap ( void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) );//

void* rh_heap__create( void );//
void  rh_heap__insert( void* handler, void *obj, size_t obj_size, int (*compar)(const void*, const void*) );//


#endif



