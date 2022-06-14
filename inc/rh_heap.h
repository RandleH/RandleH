

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#ifndef RH_HEAP_H
#define RH_HEAP_H

#ifdef __cplusplus
extern "C"{
#endif

void   rh_heap__dynamic ( void* (*__malloc)(size_t), void (*__free)(void*), void* (*__realloc)(void*,size_t) );

void*  rh_heap__convert ( const void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) );
void   rh_heap__heapify (       void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) );
void*  rh_heap__create  (                               size_t width, int (*compar)(const void*, const void*) );
bool   rh_heap__is_heap ( const void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) );//

void   rh_heap__push    ( void* handler, const void *obj );
void   rh_heap__top     ( void* handler,       void *obj );
void   rh_heap__pop     ( void* handler );//
size_t rh_heap__size    ( void* handler );
void   rh_heap__reserve ( void* handler, size_t nel);
void   rh_heap__shrink  ( void* handler );
void   rh_heap__copy    ( void* handler, void* buf );
void   rh_heap__delete  ( void* handler, void* buf );
 
 

#ifdef __cplusplus
}
#endif






#endif



