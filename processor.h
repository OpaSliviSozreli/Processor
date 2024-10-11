#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <stdio.h>
#include <math.h> 

#include "stack.h"

enum Errors
{
    READING_ERROR
};

enum CmdValue
{
    PUSH,
    ADD,
    SUB,
    MUL,
    DIV,
    OUT,
    IN,
    SQRT,
    SIN,
    COS,
    DUMP,
    HLT
};

Errors run();
int  count_file_size( FILE* fp ) ;

#endif