

#include "../inc/rh_heap.h"


static void* (*MALLOC)(size_t)        = malloc;
static void* (*REALLOC)(void*,size_t) = realloc;
static void  (*FREE)(void*)           = free;


typedef struct{
    void*  base;
    size_t size;
    size_t cnt;
}HeapHandler_t;


void push( uint8_t *base, size_t idx, size_t width, int (*compar)(const void*, const void*) ){
    if( idx==0 ){
        return;
    }
    
    // Item: base[width*idx]
    for( size_t i=0; i<idx; ++i ){
        
        if( compar( &base[width*idx], &base[width*(idx*2+1)] )==1 ){
            
        }else if( compar( &base[width*idx], &base[width*(idx*2+2)] )==1 ){
            
        }
    }
    
}

void  rh__heap_make( void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) ){
    
    for( size_t i=0; i<nel; ++i ){
        push(base, i, width, compar);
    }
}















void* rh__heap_create( void ){
    return memset( MALLOC( sizeof(HeapHandler_t) ), '\0', sizeof(HeapHandler_t));
}

void  rh__heap_insert( void* handler, void *obj, size_t obj_size, int (*compar)(const void*, const void*) ){
    
}



