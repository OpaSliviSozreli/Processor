#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef int stack_element_t;
typedef unsigned long long canary_t;

#ifdef DEBUG
    #define ON_DEBUG( ... ) __VA_ARGS__
#else
    #define ON_DEBUG( ... )
#endif

#define CHECK_( stk ) if ( stack_error( stk ) != STACK_OK ) stk_error =
#define STACK_CTOR( stk ) stack_ctor( ( stk ) ON_DEBUG( , __FILE__, __LINE__ ) )
#define STACK_DUMP( stk )  dump( ( stk ) ON_DEBUG( , __FILE__, __LINE__ ) )
#define STACK_ASSERT( stk )  if ( stack_assert_func( ( stk ) ) != STACK_OK )\
                                 STACK_DUMP ( stk );

const  stack_element_t POISON = 0XFFF; 

const  canary_t _LEFT_CANARY_  = 0XEB01DA;
const  canary_t _RIGHT_CANARY_ = 0XE1DAC;

const  canary_t _STRUCT_LEFT_CANARY_  = 0XEDA;
const  canary_t _STRUCT_RIGHT_CANARY_ = 0XDEAD;

struct stack_t
{
    canary_t left_struct_canary;
    ON_DEBUG( const char* stack_name )
    ON_DEBUG( const char* file_name )
    ON_DEBUG( int line )
    stack_element_t* data;
    int size; 
    int capacity;
    unsigned int hash;
    canary_t right_struct_canary;
};

enum StackStatus 
{
    STACK_FUNC_OK,
    STACK_FUNC_FAIL    
};

enum ErrorCode
{
    STACK_OK,        
    SIZE_IS_ZERO,         
    PTR_IS_ZERO,  
    PTR_TO_DATA_IS_ZERO,      
    STACK_WRONG_SIZE,     
    CAPACITY_IS_NEGATIVE, 
    STACK_OVERFLOW,    
    CANT_OPEN_LOG_FILE,
    LEFT_CANARY_PROBLEM,
    RIGHT_CANARY_PROBLEM,
    STACK_LEFT_CANARY_PROBLEM,
    STACK_RIGHT_CANARY_PROBLEM,
    HASH_PROBLEM
};
                            
int             stack_ctor( stack_t *stk ON_DEBUG( , const char* file, int line ) );
int             stack_dtor( stack_t* stk );
int             dump( stack_t* stk ON_DEBUG( , const char* file, int line ) );
int             stack_assert_func( stack_t *stk );
int             stack_error( const stack_t* stk );
int             stack_push( stack_t* stk, stack_element_t value );
void            my_realloc( stack_t *stk );
void            set_poison( stack_t *stk );
stack_element_t stack_pop( stack_t* stk );
unsigned int    MurmurHash2 ( char * key, unsigned int len );

#endif
