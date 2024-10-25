#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "input_and_output.h"

ReadingErrors input_text(  OriginalText* original_text ) 
{
    const char* filename = "original.txt"; 

    FILE* fp = fopen( filename, "rb" ); 

    if ( !fp )
        return SYS_ERROR;

    size_t file_size = count_file_size( fp );

    original_text->text = ( char * ) calloc( file_size + 1, sizeof( char ) );
    original_text->number_of_successfully_read_elements = fread( original_text->text, sizeof( char ), file_size, fp );

    fclose( fp );

    if ( original_text->number_of_successfully_read_elements != file_size )
        return ERROR_OF_READING;
    return READING_WENT_OK;
}

int count_file_size( FILE* fp ) 
{
    fseek( fp, 0, SEEK_END );
    size_t file_size = ftell( fp );                         
    rewind ( fp );

    return file_size;
}
