#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "array_of_pointers.h"

void count_number_of_lines( PtrToLines *lines_parameters,  OriginalText *original_text )
{   
    assert( original_text->text != NULL );

    for ( size_t i = 0; i < original_text->number_of_successfully_read_elements; i++ )
    {
        if ( original_text->text[i] == '\n' ) 
            lines_parameters->number_of_lines++;
    }

    original_text->text[original_text->number_of_successfully_read_elements - 1] = '\n';
}

void fill_array_of_pointers( PtrToLines *lines_parameters,  OriginalText *original_text )
{   
    assert( original_text->text != NULL );

    lines_parameters->ptrs_to_strings = ( char** ) calloc( lines_parameters->number_of_lines + 1, sizeof( char * ) );

    lines_parameters->ptrs_to_strings[0] = &original_text->text[0];

    int cur_str = 1;
//----------------------------------------------------------------------------------------------
    //fprintf(stderr, "size = %d\n", original_text->number_of_successfully_read_elements);
//------------------------------------------------------------------------------------------------
    for ( size_t i = 0; i < original_text->number_of_successfully_read_elements; i++ ) 
    {   
//---------------------------------------------------------------------------------------------------------
        //fprintf( stderr, "%p\n", &original_text->text[i] );
//---------------------------------------------------------------------------------------------------------
        if ( original_text->text[i] == '\r' ) 
        {
//---------------------------------------------------------------------------------------------------------
            //fprintf(stderr, "before change: <%c><%d>\n", original_text->text[i], original_text->text[i]);
//----------------------------------------------------------------------------------------------------------
            original_text->text[i] = '\0';
//------------------------------------------------------------------------------------------------
            //fprintf(stderr, "after change:  <%c><%d>\n", original_text->text[i], original_text->text[i]);
            //fprintf( stderr, " <%d>, %p\n", i, &original_text->text[i] );
//-----------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
            //fprintf( stderr, "<%p><%s>\n", lines_parameters->lines_stat.string_end, lines_parameters->lines_stat.string_end );
//------------------------------------------------------------------------------------------------
        }
         
        if ( original_text->text[i] == '\n' ) 
        {
            original_text->text[i] = '\0';
//------------------------------------------------------------------------------------------------
            //fprintf( stderr, "<%c><%d>\n", original_text->text[i], original_text->text[i] );
//------------------------------------------------------------------------------------------------
            lines_parameters->ptrs_to_strings[cur_str++] = &original_text->text[i + 1];
//------------------------------------------------------------------------------------------------
            //fprintf( stderr, "%d, <%p><%s>\n", cur_str - 1, lines_parameters->ptrs_to_strings[cur_str -1], lines_parameters->ptrs_to_strings[cur_str - 1] );
//------------------------------------------------------------------------------------------------       
        }

//--------------------------------------------------------
            //fprintf( stderr, " the start %s\n", lines_parameters->lines_stat.string_start );
            //fprintf( stderr, " the end %s\n", lines_parameters->lines_stat.string_end );
//--------------------------------------------------------
    }
//------------------------------------------------------------------------------------------------
    //lines_parameters->end_of_str[lines_parameters->number_of_lines] = &original_text->text[original_text->number_of_successfully_read_elements];
//------------------------------------------------------------------------------------------------
}

void split_text_into_lines( PtrToLines *lines_parameters,  OriginalText *original_text )
{
    count_number_of_lines(  lines_parameters, original_text ); 
    fill_array_of_pointers( lines_parameters, original_text ); 
}