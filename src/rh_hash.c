

#include "../inc/rh_hash.h"

#define M  249997
#define M1 1000001
#define M2 0xF0000000

// RS Hash Function
unsigned int RSHash    ( const char *str){
    unsigned int b=378551;
    unsigned int a=63689;
    unsigned int hash=0;
    
    while(*str)
    {
        hash=hash*a+(*str++);
        a*=b ;
    }
    
    return(hash % 249997);
}
unsigned int JSHash    ( const char *str){
    unsigned int hash=1315423911 ;  // 这个不是质数，能被3整除，为什么要用这个数?
    
    while(*str)
    {
        hash^=((hash<<5)+(*str++)+(hash>>2));
    }
    
    return(hash % M);
}
unsigned int PJWHash   ( const char *str){
    unsigned int BitsInUnignedInt=(unsigned int)(sizeof(unsigned int)*8);
    unsigned int ThreeQuarters=(unsigned int)((BitsInUnignedInt*3)/4);
    unsigned int OneEighth=(unsigned int)(BitsInUnignedInt/8);
    unsigned int HighBits=(unsigned int)(0xFFFFFFFF)<<(BitsInUnignedInt-OneEighth);
    unsigned int hash=0 ;
    unsigned int test=0 ;
    
    while(*str){
        hash=(hash<<OneEighth)+(*str++);
        if((test=hash&HighBits)!=0)
        {
            hash=((hash^(test>>ThreeQuarters))&(~HighBits));
        }
    }
    
    return(hash % M);
}
unsigned int ELFHash   ( const char *str){
    unsigned int hash=0 ;
    unsigned int x=0 ;
    
    while(*str){
        hash=(hash<<4)+(*str++);
        if((x=hash&0xF0000000L)!=0){
            hash^=(x>>24);
            hash&=~x ;
        }
    }
    
    return(hash % M);
}
unsigned int BKDRHash  ( const char *str){
    unsigned int seed=131 ;// 31 131 1313 13131 131313 etc..
    unsigned int hash=0 ;
    
    while(*str){
        hash=hash*seed+(*str++);
    }
    
    return(hash % M);
}
unsigned int SDBMHash  ( const char *str){
    unsigned int hash=0 ;
    
    while(*str){
        hash=(*str++)+(hash<<6)+(hash<<16)-hash ;
    }
    
    return(hash % M);
}
unsigned int DJBHash   ( const char *str){
    unsigned int hash=5381 ;
    
    while(*str){
        hash+=(hash<<5)+(*str++);
    }
    
    return(hash % M);
}
unsigned int APHash    ( const char *str){
    unsigned int hash=0 ;
    int i ;
    
    for(i=0;*str;i++){
        if((i&1)==0){
            hash^=((hash<<7)^(*str++)^(hash>>3));
        }
        else{
            hash^=(~((hash<<11)^(*str++)^(hash>>5)));
        }
    }
    
    return(hash % M);
}


static void* (*MALLOC)(size_t) = malloc;
static void  (*FREE)(void*)    = free;


typedef struct{
    void * table_[256];
    size_t s_key;
    size_t s_obj;
}HashTable_t;

void* rh_hash__create( size_t size_key, size_t size_obj){
    HashTable_t *ptr = (HashTable_t *)MALLOC(sizeof(HashTable_t));
    ptr->s_key = size_key;
    ptr->s_obj = size_obj;
    memset( ptr->table_, '\0', 256);
    return ptr;
}

bool  rh_hash__insert_( void* handler, void* key, void* object ){
    char *str = alloca(((HashTable_t*)handler)->s_key+1);
    str[((HashTable_t*)handler)->s_key] = '\0';
    memcpy(str, key, ((HashTable_t*)handler)->s_key);
    unsigned int hash = JSHash(str);
    printf("hash=%d\n", hash);
    return true;
}

void* rh_hash__get_( void* handler, void* key){
    return NULL;
}

bool  rh_hash__contain_( void* handler, void* key ){
    return true;
}

void* rh_hash__remove_( void* handler, void* key ){
    return NULL;
}







