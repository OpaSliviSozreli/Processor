#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <stdio.h>
#include <string.h>

#include "array_of_pointers.h" 
#include "input_and_output.h"
#include "../const_lib/const.h"

const int DEFAULT_SIZE_OF_WORD = 10;
const int NUMBER_OF_LABLES = 10;

struct LabelParameters
{
    char* name;
    size_t pointer;
};

struct LabelsTable
{
    LabelParameters label[NUMBER_OF_LABLES];
    bool is_lable;
};

Errors assembler( PtrToLines* lines_parameters, OriginalText* original_text );
bool   find_label( const char* str );
void   lable_table_ctor( LabelsTable* labels );
int check_if_lable( LabelsTable* labels, char* first_word_in_line, int cur_arg_in_code );

#endif