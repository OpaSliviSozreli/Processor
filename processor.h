#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <stdio.h>
#include <math.h> 
#include <assert.h>

#include "../const_lib/const.h"
#include "../onegin_lib/input_and_output.h"
#include "../stack_lib/stack.h"


const int NUMBER_OF_REGS = 10;

struct Spu_t
{
    int* code;
    int ip;
    stack_t stk;
    int* regs;
};

Errors run( FILE* fp );
int    spu_dump( Spu_t* spu, stack_t* stk );
Errors spu_ctor( FILE* fp, Spu_t* spu );
int    spu_dtor( Spu_t* spu );

#endif