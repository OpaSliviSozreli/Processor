#ifndef _CONST_H_
#define _CONST_H_

#include "../stack_lib/stack.h"

enum ReadingErrors
{
    SYS_ERROR = 0,
    END_OF_STRING = 0,
    ERROR_OF_READING = 0,
    READING_WENT_OK = 1,
};

enum Errors
{
    SUCCESS,
    CANT_OPEN_INPUT_FILE,
    CANT_OPEN_OUTPUT_FILE,
    CANT_OPEN_BYTE_FILE,
    WRONG_FILE_TO_SPU_CTOR,
    READING_ERROR
};

enum CmdValue
{
    PUSH,
    POP,
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
    JA,
    JB,
    JE,
    JNE,
    HLT
};

#endif