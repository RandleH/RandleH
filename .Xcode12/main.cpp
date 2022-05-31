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


#include "../app/poker/texas_holdem/rh_texash.hpp"




using namespace std;



int compar( const void* a, const void* b){
    printf("compar: %ld,%ld\n", (*(long*)a), (*(long*)b));
    return  ((*(long*)a) < (*(long*)b));
}



int main(){
    
    vector<long> a = {7,4,78,5,8,3,67,32,8,4};
    
    

    return 0;
}










//void  rh__heap_make_( int *base, size_t nel){
//    if( nel==0 || nel==1 ) return;
//    size_t idx = nel-1;
//
//    if( idx&0x01 ){
//        if( base[(idx-1)/2] > base[idx] ){
//            swap( base[idx], base[(idx-1)/2]);
//        }
//    }
//
//    for( size_t i=idx/2*2; i>0; --i ){
//
//#define a base[(i-1)/2]
//#define b base[i-1]
//#define c base[i]
//        if( a>b ){
//            if( b>c ){       // a>b>c
//                swap( b, c);
//                swap( a, b);
//            }else if( c>a ){ // c>a>b
//                swap( a, b);
//            }else{           // a>c>b
//                swap( a, c);
//            }
//        }else{
//            if( c>b ){       // c>b>a
//                //...//
//            }else if( a>c ){ // b>a>c
//                swap( b, c);
//                swap( a, b);
//            }else{           // b>c>a
//                swap( b, c);
//            }
//        }
//#undef a
//#undef b
//#undef c
//
//    }
//}















