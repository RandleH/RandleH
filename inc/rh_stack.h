

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#ifndef RH_STACK_H
#define RH_STACK_H

#ifdef __cplusplus
extern "C"{
#endif


void        rh_stack__dynamic  ( void* (*__malloc)(size_t), void (*__free)(void*), void* (*__realloc)(void*,size_t) );
     
void*       rh_stack__create   ( size_t width );
void        rh_stack__push     ( void* handler, const void* obj);
const void* rh_stack__top      ( void* handler );
void        rh_stack__pop      ( void* handler );
size_t      rh_stack__size     ( void* handler );
bool        rh_stack__empty    ( void* handler );
void        rh_stack__shrink   ( void* handler );
void        rh_stack__reserve  ( void* handler,      size_t size );
void        rh_stack__copy     ( void* handler,       void* buf  );
void        rh_stack__delete   ( void* handler,       void* buf  );



#ifdef __cplusplus
}
#endif






#endif



