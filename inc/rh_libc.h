#ifndef RH_LIBC_H
#define RH_LIBC_H

#ifdef __cplusplus
extern "C"{
#endif

extern void*    rh_libc__bit_stream_SHL( void *base, size_t len, size_t bit );

extern uint8_t  rh_libc__bit_swap8  ( uint8_t  __a );
extern uint16_t rh_libc__bit_swap16 ( uint16_t __a );
extern uint32_t rh_libc__bit_swap32 ( uint32_t __a );
extern uint32_t rh_libc__bit_b2g    ( uint32_t __a );

extern void*    rh_libc__malloc_init(void* __global_allocated_ptr, size_t __nbyte);
extern void*    rh_libc__malloc(size_t __nbyte);
extern void*    rh_libc__calloc(size_t count, size_t __nbyte);
extern void     rh_libc__free(void *ptr);
extern void*    rh_libc__malloc_deinit(void);


extern const volatile char*     rh_libc__bin_itoa  (uint8_t  x);
extern const volatile char*     rh_libc__bin_ltoa  (uint32_t x);
extern const volatile char*     rh_libc__bin_ftoa  (float    x);


extern void     rh_libc__insert_sort ( void *base, size_t nel, size_t width, int (*compar)(const void *, const void *) );
extern void     rh_libc__shell_sort  ( void *base, size_t nel, size_t width, int (*compar)(const void *, const void *) );


extern int      rh_libc__memswap     ( void* __a, void* __b, size_t size );
extern void*    rh_libc__memset_area ( void* __a, int value,           size_t size, size_t strides, size_t xs, size_t ys, size_t xe, size_t ye);
extern void*    rh_libc__memcpy_area ( void* __dst,const void* __src,  size_t size, size_t strides, size_t xs, size_t ys, size_t xe, size_t ye);
extern void*    rh_libc__memgrb_area ( void* __dst,const void* __src,  size_t size, size_t strides, size_t xs, size_t ys, size_t xe, size_t ye);//




#ifdef __cplusplus
}
#endif


#endif



