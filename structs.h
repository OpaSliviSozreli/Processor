#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <stdio.h>

struct PtrToLines
{
    int        number_of_lines;
    char**     ptrs_to_strings;       
};

struct  OriginalText
{
    char*  text;
    size_t number_of_successfully_read_elements;
};

#endif