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



extern"C"{
extern void hash_test(void);
}

int main(){
    
    hash_test();
    
    
    return 0;
}


























