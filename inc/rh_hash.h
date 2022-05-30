#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#ifndef RH_HASH_H
#define RH_HASH_H

#ifdef __cplusplus
extern "C"{
#endif

void* rh_hash__create_ ( void );
bool  rh_hash__insert_ ( void* handler, void* key, size_t key_size, void* obj, size_t obj_size );
bool  rh_hash__contain_( void* handler, void* key, size_t key_size );
void* rh_hash__get_    ( void* handler, void* key, size_t key_size );

//void* rh_hash__get_     ( void* handler, void* key );//

//void* rh_hash__remove_  ( void* handler, void* key );//
//void  rh_hash__delete_  ( void* handler);//






#ifdef __cplusplus
}
#endif

#endif



