
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//#ifdef __cplusplus
//extern "C"{
//#endif

void*    rh_libc__bit_stream_SHL( void *base, size_t len, size_t bit ){
    size_t H = bit>>3;
    size_t L = bit&0x07;

    if( H >= len ){
        return memset( base, 0x00, len);
    }
    
    memmove( (uint8_t*)(base)+H, base, len-H);
    memset (            base   , 0x00,     H);
    
    uint8_t *ptr = ((uint8_t*)base)+len-1;
    while( len-- ){
        *ptr <<= L;
        if( len!=0 ){
            *ptr  |= (((  (uint16_t)(*(ptr-1))  )<<L) >> 8);
        }
        --ptr;
    }
    assert( ptr+1==base );
    return base;
}
    
    
#define M_SWAP_4BIT(x)    ((0x0f)&((((x)&0x55)<<1|((x)>>1)&0x55)&0x33)<<2|((((x)&0x55)<<1|((x)>>1)&0x55)>>2)&0x33)
#define M_SWAP_8BIT(x)    ((M_SWAP_4BIT((x)&0x0f)<<4)|(M_SWAP_4BIT(((x)&0xf0)>>4)))
#define M_SWAP_16BIT(x)   ((M_SWAP_8BIT((x)&0x00ff)<<8)|(M_SWAP_8BIT(((x)&0xff00)>>8)))
#define M_SWAP_32BIT(x)   ((M_SWAP_16BIT((x)&0x0000ffff)<<16)|(M_SWAP_16BIT(((x)&0xffff0000)>>16)))
uint8_t  rh_libc__bit_swap8  ( uint8_t  __a ){
    return (uint8_t)M_SWAP_8BIT((__a&0xff));
}
    
uint16_t rh_libc__bit_swap16 ( uint16_t __a ){
    return (uint16_t)M_SWAP_16BIT((__a&0xffff));
}
    
uint32_t rh_libc__bit_swap32 ( uint32_t __a ){
    return (uint32_t)M_SWAP_32BIT((__a&0xffffffff));
}
    
uint32_t rh_libc__bit_b2g    ( uint32_t __a ){
    return (uint32_t)(((__a)>>1)^(__a));
}




/*--------------------------------------------------------------------------------------------------------
 * Memory Node Should be odered by the member of index
 *
 *
 *    Node1     ->>   Node2       ->>     Node3             ->>      Node4       Nodes
 *    Memory1   ->>   Memory2     ->>     Memory3           ->>      Memory4     Used Memory
 *       |               |                   |                          |
 *       |               |                   |                          |
 * [ xxxxxxxxx________xxxxxxx_______xxxxxxxxxxxxxxxxxxx____________xxxxxxxxxxx________ ] Virtual Heap
 * index=0                                                                   index=32768
 *
 --------------------------------------------------------------------------------------------------------*/
static uint8_t *rh_static__memory_ptr        = NULL;
static size_t   rh_static__memory_size       = 0;
static size_t   rh_static__memory_free       = 0;
static size_t   rh_static__memory_allocated  = 0;

    
static struct __MallocNode_t{
    unsigned long            index;
    size_t                   byte;
    void*                    ptr;
    struct __MallocNode_t*   pNextNode;
}*pHeapMemoryHeadNode = NULL;
    
    
void*    rh_libc__malloc_init(void* __global_allocated_ptr, size_t byte){
    rh_static__memory_ptr      = __global_allocated_ptr;
    rh_static__memory_size = rh_static__memory_free = byte;
    rh_static__memory_allocated     = 0;
    return __global_allocated_ptr;
}
    
void*    rh_libc__malloc(size_t size){
    size_t size_need       = size;
    if( rh_static__memory_allocated + size_need > rh_static__memory_size )
        return NULL;
    else{
        rh_static__memory_allocated += size_need;
        // It doesn't mean there is enough space to allocate.
    }
    
    void* ptr = NULL;
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pNewNode  = (struct __MallocNode_t*)malloc(sizeof(struct __MallocNode_t));
    struct __MallocNode_t* pForeward = NULL,*pBackward = NULL;
    size_t minDist                   = rh_static__memory_size;
    
    pNewNode->byte      = size_need;
    pNewNode->pNextNode = NULL;
    
    // Special Condition. There isn't any allocated memory.
    if(pNode == NULL){
        pHeapMemoryHeadNode = pNewNode;
        pNewNode->index     = 0;
        pNewNode->ptr       = ptr = &rh_static__memory_ptr[pNewNode->index];
        rh_static__memory_free -= size_need;
        return ptr;
    }
    
    // Search the optimal memory block for users.
    while(pNode != NULL){
        size_t size_free = 0;
        // All nodes should be ordered by the member of "index". Which means...
        // "pNode->index" is always ahead of "pNextNode->index" or there will be a problem.
        if(pNode->pNextNode != NULL){
            size_free = (pNode->pNextNode->index) - (pNode->index + pNode->byte);
        }else{
            size_free = (rh_static__memory_size-1) - ((pNode->index) + (pNode->byte));
        }
        if( size_free - size_need < minDist && size_free >= size_need ){
            minDist             = size_free - size_need;
            ptr                 = &rh_static__memory_ptr[ (pNode->index + pNode->byte) ];

            pForeward           = pNode;
            pBackward           = pNode->pNextNode;
            pNewNode->index     = (pForeward->index + pForeward->byte);
            pNewNode->pNextNode = pBackward;
            pNewNode->ptr       = ptr;
        }
        // Continue to search...
        pNode = pNode->pNextNode;
    }
    
    if(ptr != NULL && pForeward != NULL && pNewNode != NULL){
        // Found enough space to allocate
        pForeward->pNextNode = pNewNode;
        pNewNode->pNextNode  = pBackward;
    }else{
        // Fail to find enough space to allocate
        free(pNewNode);
        rh_static__memory_allocated -= size_need;
    }
    rh_static__memory_free = rh_static__memory_size - rh_static__memory_allocated ;
    return ptr;
}
void*    rh_libc__calloc(size_t count, size_t size){
    size_t  byt = count*size;
    void*   ptr = rh_libc__malloc(byt);
    if(ptr==NULL) return ptr;
    return memset( ptr, 0, byt );
}
void     rh_libc__free(void *ptr){
    unsigned long index = (unsigned long)((unsigned char*)ptr - rh_static__memory_ptr);
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pForeward = NULL;
    while(pNode != NULL){
        if(pNode->index == index && pNode->ptr == ptr){
            if(pForeward != NULL){
                pForeward->pNextNode = pNode->pNextNode;
                rh_static__memory_allocated -= pNode->byte;
                free(pNode);
            }else{
                // 前节点为空只可能pNode为pHeapMemoryHeadNode
            
                // RH_ASSERT( pNode == pHeapMemoryHeadNode );
                // RH_ASSERT( pNode->ptr == rh_static__memory_ptr );
            
                rh_static__memory_allocated -= pNode->byte;
                pHeapMemoryHeadNode = NULL;
                free(pNode);
            }
            break;
        }
        pForeward = pNode;
        pNode     = pNode->pNextNode;
    }
    rh_static__memory_free = rh_static__memory_size - rh_static__memory_allocated;
}

void*    rh_libc__malloc_deinit(void){
    uint8_t *ptr = rh_static__memory_ptr;
    
    struct __MallocNode_t *pList = pHeapMemoryHeadNode;
    while( !pList ){
        struct __MallocNode_t *pTmp = pList->pNextNode;
        free(pList);
        pList = pTmp;
    }
    
    rh_static__memory_size          = 0;
    rh_static__memory_free          = 0;
    rh_static__memory_allocated     = 0;
    rh_static__memory_ptr           = NULL;
    return ptr;
}


const char* rh_libc__bin_itoa  (uint8_t  x){
    static char pTmp[(sizeof(uint8_t)<<3)+1] = {0};
    
    memset( pTmp , '\0' ,  (sizeof(uint8_t)<<3)+1 );
    
    union{
        struct{
            uint8_t bit0 : 1;
            uint8_t bit1 : 1;
            uint8_t bit2 : 1;
            uint8_t bit3 : 1;
            uint8_t bit4 : 1;
            uint8_t bit5 : 1;
            uint8_t bit6 : 1;
            uint8_t bit7 : 1;
        };
        uint8_t x;
    }value;
    value.x = x;
    
    pTmp[0] = value.bit7 + '0';
    pTmp[1] = value.bit6 + '0';
    pTmp[2] = value.bit5 + '0';
    pTmp[3] = value.bit4 + '0';
    pTmp[4] = value.bit3 + '0';
    pTmp[5] = value.bit2 + '0';
    pTmp[6] = value.bit1 + '0';
    pTmp[7] = value.bit0 + '0';

    return pTmp;
}
const char* rh_libc__bin_ltoa  (uint32_t x){
    static char pTmp[(sizeof(uint32_t)<<3)+1] = {0};
    char* pTmp_iter = pTmp;
    
    uint8_t* pNum = ((uint8_t*)(&x))+sizeof(uint32_t) - 1;
    
    memset( pTmp , '\0' ,  (sizeof(uint32_t)<<3)+1 );
    size_t size = sizeof(uint32_t);
    
    while(size--){
        size_t byte = 8;
        while(byte--){
            (*pTmp_iter) = '0'+(((*(uint8_t*)(pNum))>>byte)&0x01);
            pTmp_iter++;
        }
        pNum--;
    }
    return pTmp;
}
const char* rh_libc__bin_ftoa  (float    x){
    static char pTmp[(sizeof(float)<<3)+1] = {0};
    char* pTmp_iter = pTmp;
    
    uint8_t* pNum = ((uint8_t*)(&x))+sizeof(float) - 1;
    
    memset( pTmp , '\0' ,  (sizeof(float)<<3)+1 );
    size_t size = sizeof(float);
    
    while(size--){
        size_t byte = 8;
        while(byte--){
            (*pTmp_iter) = '0'+(((*(uint8_t*)(pNum))>>byte)&0x01);
            pTmp_iter++;
        }
        pNum--;
    }
    return pTmp;
}


void     rh_libc__insert_sort ( void *base, size_t nel, size_t width, int (*compar)(const void *, const void *) ){
    if(nel==0||nel==1) return;
        
    uint8_t* ptr_iter = ((uint8_t*)base);
    for( long i=1; i<nel; i++, ptr_iter+=width ){
        uint8_t* ptr_tar = alloca(width);
        uint8_t* ptr_tmp = ptr_iter;
        
        memmove(ptr_tar, (ptr_iter+width), width);
        for (long j=i-1; j>=0; --j, ptr_tmp-=width){
            if( (*compar)( ptr_tmp, ptr_tar )>=0 ){        // compare base[j] & base[i]
                memmove( ptr_tmp+width, ptr_tmp, width );
                continue;
            }
            break;
        }
        memmove( ptr_tmp+width, ptr_tar, width );
    }
}

void     rh_libc__shell_sort  ( void *base, size_t nel, size_t width, int (*compar)(const void *, const void *) ){
    size_t inc = nel-1; // 希尔增量
        
    inc |= inc>>1;
    inc |= inc>>2;
    inc |= inc>>4;
    inc |= inc>>8;
    inc |= inc>>16;
    
    while( inc>1 ){
        inc = ((inc+1)>>1)-1;                             // 希尔增量递推关系式子(自行设定) 此处为 a[n] = 2^n - 1
        // 以下为对步长为 inc 所得到的子数组进行插入排序
        size_t   step     = inc*width;                    // 字节步长 = 单个元素字节数 x 数组步长
        uint8_t* ptr_iter = ((uint8_t*)base);             // 子数组首地址
        for( long i=inc; i<nel; i++, ptr_iter+=width ){
            uint8_t* ptr_tar = alloca(width);
            uint8_t* ptr_tmp = ptr_iter;
            memmove(ptr_tar, ptr_iter+step, width);       // 临时存放选中的元素值
            
            for (long j=i-inc; j>=0; j-=inc, ptr_tmp-=step){
                if( (*compar)( ptr_tmp, ptr_tar )>=0 ){        // compare base[j] & base[i]
                    memmove( ptr_tmp+step, ptr_tmp, width );
                    continue;
                }
                break;
            }
            memmove( ptr_tmp+step, ptr_tar, width );
        }
    }
}
    

int      rh_libc__memswap     ( void* __a, void* __b, size_t size ){
    ptrdiff_t offset = __a - __b;
    if( offset<0 ) offset = -offset;
    
    if( offset < size ) return 1;  // Memory overlapped
    
    uint8_t* a = __a;
    uint8_t* b = __b;
    while(size--){
        (*a) ^= (*b);
        (*b) ^= (*a);
        (*a) ^= (*b);
        ++a; ++b;
    }
    
    return 0;
}

void*    rh_libc__memset_area ( void* __a, int value,           size_t size, size_t strides, size_t xs, size_t ys, size_t xe, size_t ye){
    if( !__a ) return __a;
    const size_t nItems = (xe-xs+1)*size;
    const size_t step   = size*strides;
    for( size_t y=ys, offset = size*(strides*ys + xs); y<=ye; ++y, offset+=step){
        memset( ((char*)__a + offset) , value, nItems );
    }

    return __a;
}

void*    rh_libc__memcpy_area ( void* __dst,const void* __src,  size_t size, size_t strides, size_t xs, size_t ys, size_t xe, size_t ye){
    if( (!__dst) || (xe<xs) ) return NULL;
    const size_t nItems = (xe-xs+1)*size;
    const size_t step   = size*strides;
    for( size_t y=ys, offset = size*(strides*ys + xs); y<=ye; ++y, offset+=step){
        memcpy( ((char*)__dst + offset) , ((char*)__src + offset), nItems );
    }

    return __dst;
}

void*    rh_libc__memgrb_area ( void* __dst,const void* __src,  size_t size, size_t strides, size_t xs, size_t ys, size_t xe, size_t ye){
    if( (!__dst) || (!__src) || (xe<xs) )  return NULL;

    const size_t nItems = (xe-xs+1)*size;
    const size_t step   = size*strides;
    char* p = __dst;
    for( size_t y=ys, offset = size*(strides*ys + xs); y<=ye; ++y, offset+=step){
        memmove( p , ((char*)__src+offset), nItems );
        p += nItems;
    }
    
    return __dst;
}



//#ifdef __cplusplus
//}
//#endif
