

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

#define HEAP_MALLOC_STEP        16U

#define RH_SWAP(x,y)            do{\
                                    assert(sizeof(x)==sizeof(y));\
                                    RH_SWAP_PTR_S( &x, &y, sizeof(x));\
                                }while(0)

#define RH_SWAP_PTR_S(p1,p2,s)  do{\
                                    switch(s){\
                                        case 1:{\
                                          (*(uint8_t*)(p1))  ^= (*(uint8_t*)(p2));\
                                          (*(uint8_t*)(p2))  ^= (*(uint8_t*)(p1));\
                                          (*(uint8_t*)(p1))  ^= (*(uint8_t*)(p2));\
                                          break;\
                                        }\
                                        case 2:{\
                                          (*(uint16_t*)(p1)) ^= (*(uint16_t*)(p2));\
                                          (*(uint16_t*)(p2)) ^= (*(uint16_t*)(p1));\
                                          (*(uint16_t*)(p1)) ^= (*(uint16_t*)(p2));\
                                          break;\
                                        }\
                                        case 4:{\
                                          (*(uint32_t*)(p1)) ^= (*(uint32_t*)(p2));\
                                          (*(uint32_t*)(p2)) ^= (*(uint32_t*)(p1));\
                                          (*(uint32_t*)(p1)) ^= (*(uint32_t*)(p2));\
                                          break;\
                                        }\
                                        case 8:{\
                                          (*(uint64_t*)(p1)) ^= (*(uint64_t*)(p2));\
                                          (*(uint64_t*)(p2)) ^= (*(uint64_t*)(p1));\
                                          (*(uint64_t*)(p1)) ^= (*(uint64_t*)(p2));\
                                          break;\
                                        }\
                                        default:{\
                                          for( size_t i=0; i<s; ++i ){\
                                              ((uint8_t*)(p1))[i] ^= ((uint8_t*)(p2))[i];\
                                              ((uint8_t*)(p2))[i] ^= ((uint8_t*)(p1))[i];\
                                              ((uint8_t*)(p1))[i] ^= ((uint8_t*)(p2))[i];\
                                          }\
                                          break;\
                                        }\
                                    }\
                                }while(0)


#define LEFT_CHILD_OF(x)            (((x)<<1)+1)
#define RIGHT_CHILD_OF(x)           (LEFT_CHILD_OF(x)+1)
#define PARENT_OF(x)                (((x)-1)>>1)
#define FIRST_PARENT(n)             (((n)-2)>>1)
    
#define __HANDLER   ((HeapHandler_t*)handler)
    
void  rh_heap__dynamic ( void* (*__malloc)(size_t), void (*__free)(void*), void* (*__realloc)(void*,size_t) ){
    assert(__malloc);
    assert(__free);
    assert(__realloc);
    MALLOC  = __malloc;
    FREE    = __free;
    REALLOC = __realloc;
}

void  rh_heap__heapify (       void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) ){
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
                RH_SWAP_PTR_S( __ptr1, __ptr2, width);
                __root = __child;
            }else{
                break;
            }
            
        }
    }
}

void* rh_heap__convert ( const void *base, size_t nel, size_t width, int (*compar)(const void*, const void*) ){
    HeapHandler_t *res = rh_heap__create( width, compar);
    if( nel==0 ) return res;
    res->size  = nel/HEAP_MALLOC_STEP*HEAP_MALLOC_STEP+HEAP_MALLOC_STEP;
    res->cnt   = nel;
    res->width = width;
    res->base  = memcpy(  MALLOC( res->size*sizeof(width) ), base, nel*sizeof(width));
    rh_heap__heapify( res->base, nel, width, compar);
    return res;
}

void* rh_heap__create  (                               size_t width, int (*compar)(const void*, const void*) ){
    HeapHandler_t* res = memset( MALLOC( sizeof(HeapHandler_t) ), '\0', sizeof(HeapHandler_t));
    res->compar = compar;
    return res;
}

void  rh_heap__push    ( void* handler, const void *obj ){
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
    
void  rh_heap__top     ( void* handler,       void *obj ){
    if( !obj || !handler || ((HeapHandler_t*)handler)->cnt==0 ) return;
    memcpy( obj, ((HeapHandler_t*)handler)->base, ((HeapHandler_t*)handler)->width);
}

void  rh_heap__pop     ( void* handler ){
    if( !handler || __HANDLER->cnt==0 ) return;
    
    if( __HANDLER->cnt==1 ){
        __HANDLER->cnt = 0;
        return;
    }
    
    RH_SWAP_PTR_S( __HANDLER->base, __HANDLER->base+(__HANDLER->cnt-1)*__HANDLER->width, __HANDLER->width );
    
    __HANDLER->cnt--;
    
    size_t __idx = 0;
    while( __idx< __HANDLER->cnt ){
        size_t __child = LEFT_CHILD_OF(__idx);
        
        char *__ptr1 = (char*)(__HANDLER->base)+__child*__HANDLER->width;
        char *__ptr2 = __ptr1+__HANDLER->width;
        if( __child+1<__HANDLER->cnt && 1==__HANDLER->compar( __ptr1, __ptr2 ) ){
            __child ++;
        }
        
        __ptr1 = (char*)(__HANDLER->base)+__idx*__HANDLER->width;
        __ptr2 = (char*)(__HANDLER->base)+__child*__HANDLER->width;
        
        
        if( __HANDLER->compar( __ptr1, __ptr2 ) ){
            RH_SWAP_PTR_S( __ptr1, __ptr2, __HANDLER->width);
        }else{
            break;
        }
        
        __idx = __child;
    }
    
    
}
    
size_t rh_heap__size( void* handler ){
    if( !handler ) return 0;
    return __HANDLER->cnt;
}
    
void  rh_heap__reserve ( void* handler, size_t nel){
    if( !handler ) return;
    if( ((HeapHandler_t*)handler)->size >= nel) return;
    ((HeapHandler_t*)handler)->size = nel;
    ((HeapHandler_t*)handler)->base = REALLOC( ((HeapHandler_t*)handler)->base, ((HeapHandler_t*)handler)->width*nel );
}

void  rh_heap__shrink  ( void* handler ){
    if( !handler ) return;
    
    if( ((HeapHandler_t*)handler)->cnt==0 ){
        FREE( ((HeapHandler_t*)handler)->base );
        ((HeapHandler_t*)handler)->base = NULL;
        ((HeapHandler_t*)handler)->size = 0;
    }else if( ((HeapHandler_t*)handler)->cnt < ((HeapHandler_t*)handler)->size ){
        ((HeapHandler_t*)handler)->size = ((HeapHandler_t*)handler)->cnt;
        ((HeapHandler_t*)handler)->base = REALLOC( ((HeapHandler_t*)handler)->base, ((HeapHandler_t*)handler)->width*((HeapHandler_t*)handler)->size );
    }
    
}
    
void  rh_heap__copy    ( void* handler, void* buf ){
    if( !handler ) return;
    memcpy( buf, __HANDLER->base, __HANDLER->cnt*__HANDLER->width);
}
    
void  rh_heap__delete  ( void* handler, void* buf ){
    if( !handler ) return;
    if( !buf ){
        rh_heap__copy( handler, buf );
    }
    
    FREE( ((HeapHandler_t*)handler)->base );
    FREE( handler );
}


#ifdef __cplusplus
}
#endif


#ifdef RH_HEAP_TEST
static void rh_heap__push_    ( int* base, size_t nel, int (*compar)( const void*, const void*)){
    if( nel==0 ) return;
    size_t idx = nel-1;
    while( idx ){
        size_t l = idx-(idx%2==0);
        size_t r = idx+(idx%2==1);
        if( compar( &base[(idx-1)/2], &base[idx]) ){        // base[(idx-1)/2]>base[idx]
            std::swap(base[(idx-1)/2], base[idx]);
            if( r<=idx && compar( &base[l], &base[r]) ){
                std::swap( base[l], base[r]);
            }
        }else{
            if( r<=idx && compar( &base[l], &base[r]) ){
                std::swap( base[l], base[r]);
            }
            break;
        }

        idx = (idx-1)/2;
    }
}
    
static void rh_heap__heapify_ ( int *base, size_t nel, int (*compar)( const void*, const void*)){
    if( nel==0 || nel==1 ) return;

    // base[nel-1/2] is the first element who has a child.
    for( long i=(nel-1)/2; i>=0; --i ){
        // shift down

        size_t root = i;
        while( (2*root+1)<nel ){
            size_t child = 2*root+1;
            if( child+1<nel && 1==compar( &base[child], &base[child+1]) ){
                child++;
            }

            if( 1==compar( &base[root], &base[child]) ){
                std::swap( base[child], base[root]);
                root = child;
            }else{
                break;
            }

        }

    }
}
#endif


