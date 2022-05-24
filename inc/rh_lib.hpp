#ifndef RH_LIB_H
#define RH_LIB_H

#include <cstdbool>
#include <cstddef>

namespace rh_lib{

template<class _RandomAccessIterator, class T>
std::pair<ptrdiff_t,bool> binary_search      ( _RandomAccessIterator first, _RandomAccessIterator last, const T& target){
    if( first==last ) return std::make_pair( 0, false);
    
    ptrdiff_t n=last-first;
    ptrdiff_t l=0, r=n-1;
    ptrdiff_t m=l+((r-l)>>1);
    
    while (l <= r) {
        m = l+((r-l)>>1);
        if( *(first+m) == target ){
            return std::make_pair( m, true);
        }else if( *(first+m) > target ){
            r = m-1;
        }else{
            l = m+1;
        }
    }
    return std::make_pair( l, false);
}

template<class _RandomAccessIterator, class T>
std::pair<ptrdiff_t,bool> binary_search_upper( _RandomAccessIterator first, _RandomAccessIterator last, const T& target){
    if( first==last ) return std::make_pair( 0, false);
    
    ptrdiff_t n=last-first;
    ptrdiff_t l=0, r=n-1;
    ptrdiff_t m=l+((r-l)>>1);
    
    while (l < r) {
        m = l+((r-l)>>1);
        if( *(first+m) <= target ){
            l = m+1;
        }else{
            r = m;
        }
    }
    bool res = ( (l!=n) && (*(first+l))==target );
    
    if( l==n )               return std::make_pair(   l,  res );
    if( *(first+l)<target )  return std::make_pair( l+1,  res );
    
    return std::make_pair( l,  res );
}


template<class _RandomAccessIterator>
ptrdiff_t                 partition_sort     ( _RandomAccessIterator first, _RandomAccessIterator middle, _RandomAccessIterator last){
    _RandomAccessIterator end = last-1;
    std::swap( *end, *middle );
    
    _RandomAccessIterator __idx = first;
    for( _RandomAccessIterator __iter=first; __iter<end; ++__iter ){
        if( (*__iter) <= (*end) ){
            std::swap( (*__iter), (*__idx) );
            ++__idx;
        }
    }
    std::swap( (*__idx), (*end));

    return (ptrdiff_t)(__idx-first);
}

template<class _RandomAccessIterator>
void                      qsort              ( _RandomAccessIterator first, _RandomAccessIterator last){
    ptrdiff_t __len = last - first -1;
    if( __len==0 ) return;
    
    static size_t seed = 0x3A97BFE0U;
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    
    ptrdiff_t __piv = rh_lib::partition_sort( first, first+(seed&(__len)), last);
    
    if( __piv != 0 )
        rh_lib::qsort(         first, first+__piv );
    if( __piv < __len )
        rh_lib::qsort( first+__piv+1,        last );
    
}

template<class _RandomAccessIterator>
void                      msort              ( _RandomAccessIterator first, _RandomAccessIterator last){
    ptrdiff_t __len = last-first;
    if( __len<=1 ) return;

    // Merge
    _RandomAccessIterator __mid = first+ (__len>>1);
    rh_lib::msort(  first, __mid );
    rh_lib::msort( __mid,   last );
    
    const size_t size = sizeof( *first );
    void*        ptmp = alloca( __len*size );
    
    char* ptr  = (char*)ptmp;
    _RandomAccessIterator ptr1 = first;
    _RandomAccessIterator ptr2 = __mid;
    while( ptr1!=__mid || ptr2!=last ){
        while( ptr1!=__mid  && (ptr2==last || *ptr1 < *ptr2) ){
            memcpy( ptr, &(*ptr1), size);
            ptr += size;
            ++ptr1;
        }
        while( ptr2!=last && (ptr1==__mid || *ptr1 >= *ptr2) ){
            memcpy( ptr, &(*ptr2), size);
            ptr += size;
            ++ptr2;
        }
    }
    memcpy( &(*first), ptmp, __len*size);
}

template<class _RandomAccessIterator>
void                      hsort              ( _RandomAccessIterator first, _RandomAccessIterator last){
    
}

long rand( void ){
    static uint32_t a = (uint32_t)0x3A97BFE0U;
    uint32_t x = a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    a = x;
    return (long)a;
}

long rand( long __s, long __e){
    if( __s >= __e ) return   0;

    long __p = __e - __s;
    return (long)__s+(rh_lib::rand()%__p);
}




}




#endif
