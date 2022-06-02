



#include "../inc/rh_heap.h"
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;


bool   rh_heap__test    ( int (*print)( const char*, ...));

static int compar_int_less(const void *a, const void *b){
    return (*(int*)a) < (*(int*)b);
}

static int compar_int_greater(const void *a, const void *b){
    return (*(int*)a) > (*(int*)b);
}

bool   rh_heap__test    ( int (*print)( const char*, ...)){
    time_t t;
    srand((unsigned int)time(&t));
    vector<int> v(rand()%4096, rand());
    
    rh_heap__heapify( &(*v.begin()), v.size(), sizeof(int), compar_int_less);
    print("Case 1: EXPECTED=1 ANS=%d\n", std::is_heap(v.begin(), v.end(), std::less<int>()) );
    
    v = vector<int>(rand()%4096, rand());
    rh_heap__heapify( &(*v.begin()), v.size(), sizeof(int), compar_int_greater);
    print("Case 2: EXPECTED=1 ANS=%d\n", std::is_heap(v.begin(), v.end(), std::greater<int>()) );
    
    return true;
}

