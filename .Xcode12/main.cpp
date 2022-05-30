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

#include <iostream>


#include "../app/poker/texas_holdem/rh_texash.hpp"




using namespace std;



extern "C"{
void hash_test(void);
}


int compar( const void* a, const void* b){
    return  ((*(int*)a) < (*(int*)b));
}

void push_( int *base, size_t idx, int (*compar)( const void* a, const void* b)){
    while( idx ){
        size_t l = idx-(idx%2==0);
        size_t r = idx+(idx%2==1);
        if( compar( &base[(idx-1)/2], &base[idx]) ){        // base[(idx-1)/2]>base[idx]
            swap(base[(idx-1)/2], base[idx]);
            if( r<=idx && compar( &base[l], &base[r]) ){
                swap( base[l], base[r]);
            }
        }else{
            if( r<=idx && compar( &base[l], &base[r]) ){
                swap( base[l], base[r]);
            }
            break;
        }
    
        idx = (idx-1)/2;
    }
}

void  rh__heap_make_( int *base, size_t nel, int (*compar)( const void* a, const void* b) ){
    for( size_t idx=0; idx<nel; ++idx ){
        while( idx ){
            size_t l = idx-(idx%2==0);
            size_t r = idx+(idx%2==1);
            if( compar( &base[(idx-1)/2], &base[idx]) ){        // base[(idx-1)/2]>base[idx]
                swap(base[(idx-1)/2], base[idx]);
                if( r<=idx && compar( &base[l], &base[r]) ){
                    swap( base[l], base[r]);
                }
            }else{
                if( r<=idx && compar( &base[l], &base[r]) ){
                    swap( base[l], base[r]);
                }
                break;
            }
        
            idx = (idx-1)/2;
        }
    }
}

int main(){
    
    size_t cnt=1000;
    
    while(cnt--){
        vector<int> a(rand()%0xffff);
        for( auto &i:a ){
            i = rand();
        }
        
//        rh__heap_make_( &(*a.begin()), a.size(), compar);
        std::make_heap( a.begin(), a.end(), std::less<int>() );
        assert( std::is_heap( a.begin(), a.end(), std::less<int>()) );
//        cout<<std::is_heap( a.begin(), a.end(), std::less<int>())<<endl;
    }
    
    return 0;
}


























