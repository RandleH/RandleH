
#include "../inc/rh_stack.h"


#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    void*  base;
    size_t size;
    size_t cnt;
    size_t width;
}StackHandler_t;

static void* (*MALLOC)(size_t)        = malloc;
static void* (*REALLOC)(void*,size_t) = realloc;
static void  (*FREE)(void*)           = free;

#define __HANDLER   ((StackHandler_t*)handler)
    
#define STACK_MALLOC_STEP         4U

#define RH_ASSIGN(x,y)            do{\
                                      assert(sizeof(x)==sizeof(y));\
                                      RH_ASSIGN_PTR_S( &x, &y, sizeof(x));\
                                  }while(0)

#define RH_ASSIGN_PTR_S(p1,p2,s)  do{\
                                      switch(s){\
                                          case 1:{\
                                            (*(uint8_t*)(p1))  = (*(uint8_t*)(p2));\
                                            break;\
                                          }\
                                          case 2:{\
                                            (*(uint16_t*)(p1)) = (*(uint16_t*)(p2));\
                                            break;\
                                          }\
                                          case 4:{\
                                            (*(uint32_t*)(p1)) = (*(uint32_t*)(p2));\
                                            break;\
                                          }\
                                          case 8:{\
                                            (*(uint64_t*)(p1)) = (*(uint64_t*)(p2));\
                                            break;\
                                          }\
                                          default:{\
                                            memcpy( p1, p2, s);\
                                            break;\
                                          }\
                                      }\
                                  }while(0)
    
void   rh_stack__dynamic  ( void* (*__malloc)(size_t), void (*__free)(void*), void* (*__realloc)(void*,size_t) ){
    assert(__malloc);
    assert(__free);
    assert(__realloc);
    MALLOC  = __malloc;
    FREE    = __free;
    REALLOC = __realloc;
}
    
void*  rh_stack__create   ( size_t width ){
    StackHandler_t* res = memset( MALLOC( sizeof(StackHandler_t) ), '\0', sizeof(StackHandler_t));
    res->width = width;
    return res;
}
    
void   rh_stack__push     ( void* handler, const void* obj){
    if( !handler || !obj ) return;
    
    if( __HANDLER->cnt == __HANDLER->size ){
        __HANDLER->size += STACK_MALLOC_STEP;
        __HANDLER->base = REALLOC( __HANDLER->base, __HANDLER->size*__HANDLER->width );
    }
    __HANDLER->cnt++;
    
    RH_ASSIGN_PTR_S( __HANDLER->base+__HANDLER->width*(__HANDLER->cnt-1), obj, __HANDLER->width);
}
    
const void* rh_stack__top      ( void* handler ){
    if( !handler || __HANDLER->cnt==0 ) return NULL;
    
    return __HANDLER->base+__HANDLER->width*(__HANDLER->cnt-1);
}
    
void   rh_stack__pop      ( void* handler ){
    if( !handler || __HANDLER->cnt==0 ) return;
    __HANDLER->cnt--;
    rh_stack__shrink( handler );
}
    
size_t rh_stack__size     ( void* handler ){
    if( !handler ) return 0;
    return __HANDLER->cnt;
}
    
bool   rh_stack__empty    ( void* handler ){
    if( !handler ) return false;
    return __HANDLER->cnt==0;
}
    
void   rh_stack__shrink   ( void* handler ){
    if( !handler || __HANDLER->size-__HANDLER->cnt < STACK_MALLOC_STEP ) return;
    
    if( __HANDLER->cnt==0 ){
        FREE(__HANDLER->base);
        __HANDLER->base = NULL;
        __HANDLER->size = 0;
        return;
    }
    
    while( __HANDLER->size - STACK_MALLOC_STEP > __HANDLER->cnt ){
        __HANDLER->size -= STACK_MALLOC_STEP;
    }
    
    REALLOC( __HANDLER->base, __HANDLER->size*__HANDLER->width );
}
    
void   rh_stack__reserve  ( void* handler,      size_t size ){
    if( !handler || __HANDLER->size>=size ) return;
    __HANDLER->size = size;
    __HANDLER->base = REALLOC( __HANDLER->base, __HANDLER->size*__HANDLER->width);
}

void        rh_stack__copy     ( void* handler,       void* buf  ){
    if( !handler || !buf ) return;
    memcpy( buf, __HANDLER->base, __HANDLER->cnt*__HANDLER->width);
}
    
void   rh_stack__delete   ( void* handler,       void* buf ){
    if( !handler ) return;
    
    if( buf ){
        memcpy( buf, __HANDLER->base, __HANDLER->cnt*__HANDLER->width);
    }
    
    FREE(__HANDLER->base);
    FREE(__HANDLER);
}
    
    
#ifdef __cplusplus
}
#endif

