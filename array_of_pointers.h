#ifndef _ARRAY_OF_POINTERS_H
#define _ARRAY_OF_POINTERS_H

#include "structs.h"

void count_number_of_lines( PtrToLines *lines_parameters,  OriginalText *original_text );
void fill_array_of_pointers( PtrToLines *lines_parameters,  OriginalText *original_text );
void split_text_into_lines( PtrToLines *lines_parameters,  OriginalText *original_text );

#endif