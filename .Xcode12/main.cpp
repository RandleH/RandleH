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
#include "rh_stack.h"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#include <unistd.h>
#include <stdio.h>

int rh_sdcard__echo ( const char *__f, const char *__mode, const char *__data, size_t __len){
    FILE *file = fopen( __f, __mode);
    if( file==NULL ) return -1;
    fwrite( __data, 1, __len, file);
    fclose(file);
    return 0;
}


static int compar_int_less(const void *a, const void *b){
    return (*(int*)a) < (*(int*)b);
}

static int compar_int_greater(const void *a, const void *b){
    return (*(int*)a) > (*(int*)b);
}


int main(){
    // { 0, 3, 4, 5, 7, 8, 10, 12, 238}
    std::vector<int> v = {10, 12, 14};
    
    
    auto res = rh_lib::binary_search( v.begin(), v.end(), 9);
    
    if( res.second){
        cout<< "Found it @"<< res.first << endl;
    }else{
        cout<< "Not found"<< endl;
    }
    
    return 0;
}








