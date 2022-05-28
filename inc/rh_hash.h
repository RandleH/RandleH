#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#ifndef RH_HASH_H
#define RH_HASH_H

#ifdef __cplusplus
extern "C"{
#endif

void* rh_hash__create   ( size_t size_key, size_t size_obj);//
bool  rh_hash__insert_  ( void* handler, void* key, void* object );//


void* rh_hash__get_     ( void* handler, void* key );//
bool  rh_hash__contain_ ( void* handler, void* key );//
void* rh_hash__remove_  ( void* handler, void* key );//
void  rh_hash__delete_  ( void* handler);//



#define rh_hash__insert(h,k,o)     rh_hash__insert_( h, (void*)(k), (void*)(o))
#define rh_hash__get_(h,k)         rh_hash__get( h, (void*)(k))
#define rh_hash__contain_(h,k)     rh_hash__contain( h, (void*)(k))
#define rh_hash__remove_(h,k)      rh_hash__remove( h, (void*)(k))


#ifdef __cplusplus
}
#endif

#endif



