
#include "../inc/rh_lib.h"

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




/*-----------------------------------------------------------------------------------------------------------------------------------------------------
 * Memory Node Should be odered by the member of index
 *
 *
 *    Memory1   ->>   Memory2     ->>     Memory3           ->>      Memory4                 Reserved Info ( size=rh_static__memory_infocnt )
 *       |               |                   |                          |                          |
 *       |               |                   |                          |                          |
 * [ xxxxxxxxx________xxxxxxx_______xxxxxxxxxxxxxxxxxxx____________xxxxxxxxxxx______________##############] Virtual Malloc Memory
 *                                                                                          |
 *                                                                                          |
 *                                                                                       rh_static_memory_infoptr
 *
 *
 * index=0                                                                                      index=rh_static__memory_size-1
 *
 -----------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct MallocInfo_t{
    size_t                   byte;
    size_t                   idx;
}MallocInfo_t;
static uint8_t        *rh_static__memory_ptr        = NULL;
static size_t          rh_static__memory_size       = 0;
static size_t          rh_static__memory_free       = 0;
static size_t          rh_static__memory_allocated  = 0;
static MallocInfo_t   *rh_static__memory_infoptr    = NULL;
static size_t          rh_static__memory_infocnt    = 0;
    
void*    rh_libc__malloc_init(void* __global_allocated_ptr, size_t byte){
    rh_static__memory_ptr      = __global_allocated_ptr;
    rh_static__memory_size = rh_static__memory_free = byte;
    rh_static__memory_allocated     = 0;
    return __global_allocated_ptr;
}
    
static size_t rh_libc__sbrk( size_t size ){
    if( !rh_static__memory_infoptr ) return 0;
    
    MallocInfo_t *ptr    = rh_static__memory_infoptr;
    size_t free_byte_optim = rh_static__memory_free;
    size_t free_idx_optim  = LONG_MAX;
    for( size_t i=0; i<=rh_static__memory_infocnt; ++i ){
        if( i==0 ){
            size_t free_byte = ptr[0].idx;
            if( free_byte >= size && free_byte_optim > free_byte ){
                free_byte_optim = free_byte;
                free_idx_optim  = 0;
            }
        }else if( i<rh_static__memory_infocnt ){
            size_t free_byte = ptr[i].idx - ptr[i-1].idx - ptr[i-1].byte;
            if( free_byte >= size && free_byte_optim > free_byte ){
                free_byte_optim = free_byte;
                free_idx_optim  = ptr[i-1].idx+ptr[i-1].byte;
            }
        }else{
            size_t free_byte = rh_static__memory_size - rh_static__memory_infocnt*sizeof(MallocInfo_t) - ptr[i-1].idx - ptr[i-1].byte;
            if( free_byte >= size && free_byte_optim > free_byte ){
                free_byte_optim = free_byte;
                free_idx_optim  = ptr[i-1].idx+ptr[i-1].byte;
            }
        }
        
    }
    
    return free_idx_optim;
}

static size_t rh_libc__locate(void* ptr){
    ptrdiff_t idx = (char*)ptr > (char*)rh_static__memory_ptr? ((char*)ptr-(char*)rh_static__memory_ptr) : ((char*)rh_static__memory_ptr-(char*)ptr);
    assert( idx<rh_static__memory_size ); // This pointer exceeds the reasonable range
    {
        ptrdiff_t l=0, r=rh_static__memory_infocnt-1;
        ptrdiff_t m=l+((r-l)>>1);
        
        while (l <= r) {
            m = l+((r-l)>>1);
            if( rh_static__memory_infoptr[m].idx == idx ){
                return m;
            }else if( rh_static__memory_infoptr[m].idx > idx ){
                r = m-1;
            }else{
                l = m+1;
            }
        }
    }
    assert(0); // This pointer hasn't been allocated
    return -1;
}

void*    rh_libc__malloc(size_t size){
    if( rh_static__memory_allocated + size > rh_static__memory_size )
        return NULL;
    
    if( rh_static__memory_infocnt==0 ){
        ++rh_static__memory_infocnt;
        rh_static__memory_infoptr = (MallocInfo_t*)(rh_static__memory_ptr+rh_static__memory_size-sizeof(MallocInfo_t));
        rh_static__memory_infoptr->byte = size;
        rh_static__memory_infoptr->idx  = 0;
        rh_static__memory_allocated += size;
        rh_static__memory_free      -= size;
        return rh_static__memory_ptr;
    }
    
    MallocInfo_t res = {
        .idx   = rh_libc__sbrk( size ) ,\
        .byte  = size
    };
    
    if( res.idx==LONG_MAX ) return NULL;
    
    size_t a = rh_static__memory_infocnt;
    {   // Insert the new malloc information
        MallocInfo_t *ptr    = rh_static__memory_infoptr;
        ptrdiff_t l=0, r=rh_static__memory_infocnt-1;
        ptrdiff_t m=l+((r-l)>>1);
        while (l <= r) {
            m = l+((r-l)>>1);
            if( res.idx <= ptr[m].idx ){
                a = m;
                r = m-1;
            }else{
                l = m+1;
            }
        }
    }
    rh_static__memory_infoptr    = memmove( (void*)(rh_static__memory_infoptr-1), (void*)(rh_static__memory_infoptr), a*sizeof(MallocInfo_t));
    rh_static__memory_infoptr[a] = res;
    ++rh_static__memory_infocnt;
    rh_static__memory_allocated += size;
    rh_static__memory_free      -= size;
    
    return &rh_static__memory_ptr[ rh_static__memory_infoptr[a].idx ];
}
void*    rh_libc__calloc(size_t count, size_t size){
    size_t  byt = count*size;
    void*   ptr = rh_libc__malloc(byt);
    if(ptr==NULL) return ptr;
    return memset( ptr, 0, byt );
}
void     rh_libc__free( void* ptr){
    assert( rh_static__memory_infocnt!=0 );
    size_t a = rh_libc__locate(ptr);

    rh_static__memory_allocated -= rh_static__memory_infoptr[a].byte;
    rh_static__memory_free      += rh_static__memory_infoptr[a].byte;
    if( rh_static__memory_infocnt==1 )
        rh_static__memory_infoptr = NULL;
    else{
        rh_static__memory_infoptr = memmove( (void*)(rh_static__memory_infoptr+1), (void*)(rh_static__memory_infoptr), a*sizeof(MallocInfo_t));
    }
    --rh_static__memory_infocnt;
}
void*    rh_libc__realloc(void *ptr, size_t size){
    if( !ptr ) return rh_libc__malloc(size);
    
    size_t a = rh_libc__locate(ptr);
    if( rh_static__memory_infoptr[a].byte >= size )
        return ptr;
    
    size_t byte_reallocate = rh_static__memory_infoptr[a].byte; // 如果不改变首地址, 直接扩容可达到的最大容量.
    if( a==rh_static__memory_infocnt-1 ){
        byte_reallocate = rh_static__memory_size - rh_static__memory_infocnt*sizeof(MallocInfo_t) - rh_static__memory_infoptr[a].idx;
    }else{
        byte_reallocate = rh_static__memory_infoptr[a+1].idx - rh_static__memory_infoptr[a].idx;
    }
    
    if( byte_reallocate >= size ){
        rh_static__memory_infoptr[a].byte = size;
        return ptr;
    }
    
    rh_libc__free(ptr);
    ptr = memmove( rh_libc__malloc(size), ptr, size);
    return ptr;
}
void*    rh_libc__malloc_deinit(void){
    uint8_t *ptr = rh_static__memory_ptr;
    rh_static__memory_size          = 0;
    rh_static__memory_free          = 0;
    rh_static__memory_allocated     = 0;
    rh_static__memory_ptr           = NULL;
    rh_static__memory_infoptr       = NULL;
    rh_static__memory_infocnt       = 0;
    return memset( ptr, 0x00, rh_static__memory_size);
}


const volatile char* rh_libc__bin_itoa  (uint8_t  x){
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
const volatile char* rh_libc__bin_ltoa  (uint32_t x){
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
const volatile char* rh_libc__bin_ftoa  (float    x){
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


void     rh_libc__debug_malloc_print( int (*print_func)( const char*, ...) ){
    MallocInfo_t *ptr = rh_static__memory_infoptr;
    print_func( "|\t Idx\t|\tByte\t|\n" );
    for( size_t i=0; i<rh_static__memory_infocnt; ++i ){
        print_func( "|\t%4ld\t|\t%4ld\t|\n", ptr[i].idx, ptr[i].byte );
    }
}

#include <time.h>
static void rh_libc__test_malloc_0( int (*print)(const char *format, ...) ){
    uint8_t heap[1024] = {0};
    rh_libc__malloc_init( heap, 1024);
    for( size_t i=0, j=0; i<rh_static__memory_size-j; ++i, j+=sizeof(MallocInfo_t) ){
        uint8_t *ptr1 = rh_libc__malloc(1);
        assert( ptr1==&heap[i] );  // 内存申请返回指针不符合逻辑, 无释放则最优解应逐字节递增
    }
    rh_libc__malloc_deinit();
    print( "Test Malloc Case 0: Passed.\n" );
}
static void rh_libc__test_malloc_1( int (*print)(const char *format, ...) ){
    uint8_t heap[1024] = {0};
    rh_libc__malloc_init( heap, 1024);
    
    uint8_t *ptr1 = rh_libc__malloc(10);
    uint8_t *ptr2 = rh_libc__malloc(10);
    rh_libc__free(ptr1);
    rh_libc__free(ptr2);
    
    
    time_t foo;
    srand((unsigned)time(&foo));
    
    // malloc memory for 10 times
    void *ptrs[10] = {0};
    for( size_t i=0; i<10; ++i ){
        ptrs[i] = rh_libc__malloc( random()%8 );
    }
    
    // shuffle the address
    for( size_t i=0; i<0xff; ++i ){
        size_t a = rand()%10;
        size_t b = rand()%10;
        void* ptr = ptrs[a];
        ptrs[a]   = ptrs[b];
        ptrs[b]   = ptr;
    }
    
    for( size_t i=0; i<10; ++i ){
        rh_libc__free( ptrs[i] );
    }
    
    assert( !rh_static__memory_infoptr );
    rh_libc__malloc_deinit();
    print( "Test Malloc Case 1: Passed.\n" );
}
static void rh_libc__test_malloc_2( int (*print)(const char *format, ...) ){
    uint8_t heap[1024] = {0};
    rh_libc__malloc_init( heap, 1024);
    time_t foo;
    srand((unsigned)time(&foo));
    // malloc memory for 10 times
    void *ptrs[10] = {0};
    for( size_t i=0; i<10; ++i ){
        size_t size = random()%8;
        ptrs[i] = rh_libc__malloc( size );
        assert( ptrs[i]==rh_libc__realloc( ptrs[i], size) );
    }
    
    // shuffle the address
    for( size_t i=0; i<0xff; ++i ){
        size_t a = rand()%10;
        size_t b = rand()%10;
        void* ptr = ptrs[a];
        ptrs[a]   = ptrs[b];
        ptrs[b]   = ptr;
    }
    for( size_t i=0; i<10; ++i ){
        rh_libc__free( ptrs[i] );
    }
    assert( !rh_static__memory_infoptr );
    
    rh_libc__malloc_deinit();
    print( "Test Malloc Case 2: Passed.\n" );
}
static void(*test_malloc[])( int (*print)(const char *format, ...) ) = {
    rh_libc__test_malloc_0 , // 逐字节动态申请, 不释放
    rh_libc__test_malloc_1 , // 随机大小动态申请, 随机顺序释放
    rh_libc__test_malloc_2 , // 随机大小动态申请, 动态重配
};

void     rh_libc__test_malloc( int (*print)(const char *format, ...) ){
    for( size_t i=0; i<sizeof(test_malloc)/sizeof(void*); ++i ){
        (*test_malloc[i])(print);
    }
}



//#ifdef __cplusplus
//}
//#endif
