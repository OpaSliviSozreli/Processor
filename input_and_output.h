#ifndef _PRINT_H_
#define _PRINT_H_

#include "../const_lib/const.h"
#include "structs.h"

void           print_sorted_text( PtrToLines *lines_parameters  );
ReadingErrors  input_text(  OriginalText *original_text );
int            count_file_size( FILE *fp );

#endif
