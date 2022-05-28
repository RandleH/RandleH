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


void foooo(void){
    printf( "foo:%p\n", "Hello, world" );
}






int main(){
    void *Hash1 = rh_hash__create( sizeof(char*), sizeof(int));
    
    int obj = 1;
    rh_hash__insert( Hash1, "1", &obj);
    
    
    
    return 0;
}


























