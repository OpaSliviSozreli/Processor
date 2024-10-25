#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <stdio.h>
#include <math.h> 
#include <assert.h>

#include "../const_lib/const.h"
#include "../onegin_lib/input_and_output.h"
#include "../stack_lib/stack.h"


const int NUMBER_OF_REGS = 5;
const int NUMBER_OF_RAM_CELLS = 20;

struct Registers
{
    char* name;
    bool is_reg;
    int value;
};

struct Ram
{
    bool is_ram;
    int value;
};

struct Spu_t
{
    int* code;
    int ip;
    stack_t stk;
    Registers regs[NUMBER_OF_REGS];
    Ram ram[NUMBER_OF_RAM_CELLS];
};

Errors       run( const char* name_of_input_bytecode_file );
int          spu_dump( Spu_t* spu, stack_t* stk );
Errors       spu_ctor( FILE* fp, Spu_t* spu );
int          spu_dtor( Spu_t* spu );
const  char* get_input_file_name( int argc, char** argv );

#endif