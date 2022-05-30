

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


static void* (*MALLOC)(size_t)         = malloc;
static void* (*REALLOC)(void*,size_t)  = realloc;
static void  (*FREE)(void*)            = free;

#define M_HASH_TABLE_BIT    (8)
#define M_HASH_TABLE_SIZE   (1<<(M_HASH_TABLE_BIT))
#define M_HASH_MALLOC_STEP  (16)

typedef struct{
    void   *key;
    size_t s_key;
    void   *obj;
}HashBucket_t;

typedef struct{
    size_t        cnt;
    size_t        size;
    HashBucket_t *buf;
}HashTable_t;


#define M_JSHASH( hash, key, size )          do{\
                                                 hash =1315423911;\
                                                 size_t i = size;\
                                                 while(i--) hash^=((hash<<5)+(*key++)+(hash>>2));\
                                                 hash %= 249997;\
                                             }while(0)



void* rh_hash__create_(void){
    HashTable_t *table = MALLOC( sizeof(HashTable_t)*M_HASH_TABLE_SIZE );
    
    return memset( table, '\0', sizeof(HashTable_t)*M_HASH_TABLE_SIZE);
}

bool  rh_hash__table_contain_( HashTable_t *table, void* key, size_t key_size){
    for( size_t i=0; i<table->cnt; ++i ){
        if( table->buf[i].s_key == key_size ){
            if( memcmp( table->buf[i].key, key, key_size)==0 )  // Key exists.
                return true;
        }
    }
    return false;
}

bool  rh_hash__table_insert_( HashTable_t *table, void* key, size_t key_size, void* obj, size_t obj_size){
    if( rh_hash__table_contain_(table, key, key_size) )
        return false;
    
    if( table->cnt == table->size ){
        table->size += M_HASH_MALLOC_STEP;
        table->buf = (HashBucket_t*)REALLOC( table->buf, table->size*sizeof(HashBucket_t) );
    }
    
    assert( table->buf );
    table->cnt++;
    table->buf[ table->cnt-1 ].key   = memcpy( MALLOC(key_size), key, key_size);
    table->buf[ table->cnt-1 ].s_key = key_size;
    table->buf[ table->cnt-1 ].obj   = memcpy( MALLOC(obj_size), obj, obj_size);
    assert( table->cnt<=table->size );
    return true;
}

bool  rh_hash__insert_( void* handler, void* key, size_t key_size, void* obj, size_t obj_size ){
    unsigned int hash = 0;
    M_JSHASH( hash, (const char*)key, key_size);
    hash %= 0xff;
    
    return rh_hash__table_insert_( &((HashTable_t*)handler)[hash], key, key_size, obj, obj_size );
}

void* rh_hash__get_( void* handler, void* key, size_t key_size){
    unsigned int hash = 0;
    M_JSHASH( hash, (const char*)key, key_size);
    hash %= 0xff;
    
    HashTable_t* table = &((HashTable_t*)handler)[hash];
    for( size_t i=0; i<table->cnt; ++i ){
        if( table->buf[i].s_key == key_size ){
            if( memcmp( table->buf[i].key, key, key_size)==0 )  // Key exists.
                return table->buf[i].obj;
        }
    }
    
    return NULL;
}

bool  rh_hash__contain_( void* handler, void* key, size_t key_size ){
    unsigned int hash = 0;
    M_JSHASH( hash, (const char*)key, key_size);
    hash %= 0xff;
    return rh_hash__table_contain_( &((HashTable_t*)handler)[hash], key, key_size);
}

void* rh_hash__remove_( void* handler, void* key ){
    return NULL;
}











void hash_test(void){

}




