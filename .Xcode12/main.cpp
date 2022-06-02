//
//  main.cpp
//  Xcode12
//
//  Created by Randle Helmslay on 2022/5/24.
//

#include <stdio.h>
#include "rh_math.hpp"
#include "rh_lib.hpp"
#include "rh_lib.h"
#include "rh_color.h"
#include "rh_hash.h"
#include "rh_heap.h"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


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
                                              ((char*)(p1))[i] ^= ((char*)(p2))[i];\
                                              ((char*)(p2))[i] ^= ((char*)(p1))[i];\
                                              ((char*)(p1))[i] ^= ((char*)(p2))[i];\
                                          }\
                                          break;\
                                        }\
                                    }\
                                }while(0)


typedef int var;

int compar( const void *a, const void *b ){
    printf("CMP: %d, %d = %d\n", *(var*)a, *(var*)b, ((*(var*)a) < (*(var*)b)));
    return (*(var*)a) < (*(var*)b);
}


#include "../test/rh_test_heap.hpp"

int main(){
    
    rh_heap__test(printf);
    
    return 0;
}








