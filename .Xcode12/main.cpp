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

#include <iostream>


using namespace std;
int main(){
    char buf[33] = {0};
    
    strncpy( buf, (const char*)rh_libc__bin_ltoa( RH_RGB565( RH_MAKE_COLOR(255, 0, 255) )), 32);
    buf[32] = '\0';
    cout<< buf <<endl;
    
    return 0;
}



