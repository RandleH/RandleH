

#include "../inc/rh_heap.h"

#ifdef __cplusplus
extern "C"{
#endif




static void* (*MALLOC)(size_t)        = malloc;
static void* (*REALLOC)(void*,size_t) = realloc;
static void  (*FREE)(void*)           = free;


typedef struct{
    void*  base;
    size_t size;
    size_t cnt;
    size_t width;
    int    (*compar)(const void*, const void*);
}HeapHandler_t;

#define HEAP_MALLOC_STEP   16U



//void  rh__heap_make_( int *base, size_t nel, int (*compar)( const void*, const void*)){
//    if( nel==0 || nel==1 ) return;
//
//    // base[nel-1/2] is the first element who has a child.
//    for( long i=(nel-1)/2; i>=0; --i ){
//        // shift down
//
//        size_t root = i;
//        while( (2*root+1)<nel ){
//            size_t child = 2*root+1;
//            if( child+1<nel && 1==compar( &base[child], &base[child+1]) ){
//                child++;
//            }
//
//            if( 1==compar( &base[root], &base[child]) ){
//                swap( base[child], base[root]);
//                root = child;
//            }else{
//                break;
//            }
//
//        }
//
//    }
//}


#define RH_SWAP( a, b, width)       do{\
                                        size_t cnt = width;\
                                        char  *ptr1= (char*)(&a);\
                                        char  *ptr2= (char*)(&b);\
                                        while(cnt--){\
                                            *(char*)(ptr1) ^= *(char*)ptr2;\
                                            *(char*)(ptr2) ^= *(char*)ptr1;\
                                            *(char*)(ptr1) ^= *(char*)ptr2;\
                                            ++ptr1;++ptr2;\
                                        }\
                                    }while(0)

#define LEFT_CHILD_OF(x)            (((x)<<1)+1)
#define RIGHT_CHILD_OF(x)           (LEFT_CHILD_OF(x)+1)
#define PARENT_OF(x)                (((x)-1)>>1)
#define FIRST_PARENT(n)             (((n)-2)>>1)

void  rh_heap__heapify( void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) ){
    if( nel==0 || nel==1 ) return;

    for( ptrdiff_t i=FIRST_PARENT(nel); i>=0; --i ){
        
        size_t __root  = i;
        while( LEFT_CHILD_OF(__root) < nel ){
            size_t __child = LEFT_CHILD_OF(__root);
            
            char *__ptr1 = (char*)(base)+__child*width;
            char *__ptr2 = __ptr1+width;
            if( __child+1<nel && 1==compar( __ptr1, __ptr2 ) ){
                __child ++;
            }
            
            __ptr1 = (char*)(base)+__root*width;
            __ptr2 = (char*)(base)+__child*width;
            if( 1==compar( __ptr1, __ptr2 ) ){
                {// swap
                    size_t cnt = width;
                    while(cnt--){
                        *__ptr1 ^= *__ptr2;
                        *__ptr2 ^= *__ptr1;
                        *__ptr1 ^= *__ptr2;
                        ++__ptr1;++__ptr2;
                    }
                }
                __root = __child;
            }else{
                break;
            }
            
        }
    }
}

void* rh_heap__convert( void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) ){
    HeapHandler_t *res = rh_heap__create( width, compar);
    if( nel==0 ) return res;
    res->size  = nel/HEAP_MALLOC_STEP*HEAP_MALLOC_STEP+HEAP_MALLOC_STEP;
    res->cnt   = nel;
    res->width = width;
    res->base  = memcpy(  MALLOC( res->size*sizeof(width) ), base, nel*sizeof(width));
    rh_heap__heapify( res->base, nel, width, compar);
    return res;
}

void* rh_heap__create(  size_t width, int (*compar)(const void*, const void*) ){
    HeapHandler_t* res = memset( MALLOC( sizeof(HeapHandler_t) ), '\0', sizeof(HeapHandler_t));
    res->compar = compar;
    return res;
}


//void rh__heap_push_( int* base, size_t nel,  int (*compar)( const void* a, const void* b)){
//    if( nel==0 ) return;
//    size_t idx = nel-1;
//    while( idx ){
//        size_t l = idx-(idx%2==0);
//        size_t r = idx+(idx%2==1);
//        if( compar( &base[(idx-1)/2], &base[idx]) ){        // base[(idx-1)/2]>base[idx]
//            swap(base[(idx-1)/2], base[idx]);
//            if( r<=idx && compar( &base[l], &base[r]) ){
//                swap( base[l], base[r]);
//            }
//        }else{
//            if( r<=idx && compar( &base[l], &base[r]) ){
//                swap( base[l], base[r]);
//            }
//            break;
//        }
//
//        idx = (idx-1)/2;
//    }
//}


void  rh_heap__push   ( void* handler, const void *obj ){
    if( ((HeapHandler_t*)handler)->cnt==((HeapHandler_t*)handler)->size ){
        ((HeapHandler_t*)handler)->size += HEAP_MALLOC_STEP;
        ((HeapHandler_t*)handler)->base  = REALLOC( ((HeapHandler_t*)handler)->base, ((HeapHandler_t*)handler)->size*((HeapHandler_t*)handler)->width );
    }
    
//    HeapHandler_t* view = handler;
    
    memcpy( ((HeapHandler_t*)handler)->base+((HeapHandler_t*)handler)->width*((HeapHandler_t*)handler)->cnt, obj, ((HeapHandler_t*)handler)->width);
    ((HeapHandler_t*)handler)->cnt++;
    
    assert( ((HeapHandler_t*)handler)->cnt!=0 );
    
    size_t idx = ((HeapHandler_t*)handler)->cnt-1;
    char *base = (char*)((HeapHandler_t*)handler)->base;
    while( idx ){
        
        char *__ptr1 = base+PARENT_OF(idx)*((HeapHandler_t*)handler)->width;
        char *__ptr2 = base+idx*((HeapHandler_t*)handler)->width;
        
        if( ((HeapHandler_t*)handler)->compar( __ptr1, __ptr2) ){
            {// swap
                size_t cnt = ((HeapHandler_t*)handler)->width;
                while(cnt--){
                    *__ptr1 ^= *__ptr2;
                    *__ptr2 ^= *__ptr1;
                    *__ptr1 ^= *__ptr2;
                    ++__ptr1;++__ptr2;
                }
            }
        }else{
            break;
        }
        idx = (idx-1)/2;
    }
    
//    for( size_t i=0; i<view->cnt; ++i ){
//        printf( "%ld ", ((long*)(view->base))[i] );
//    }
//    printf("\n");
    
}

void  rh_heap__delete ( void* handler ){
    FREE( ((HeapHandler_t*)handler)->base );
    FREE( handler );
}


#ifdef __cplusplus
}
#endif



