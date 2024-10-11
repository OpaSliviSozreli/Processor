#include "processor.h"

Errors run()
{
    stack_t stk = {};

    STACK_CTOR( &stk );

    const char* filename = "machine_code.txt"; 

    FILE* fp = fopen( filename, "rb" ); 

    if ( !fp )
        return READING_ERROR;

    size_t file_size = count_file_size( fp );

    char* buff = ( char * ) calloc( file_size, sizeof( char ) );
    fread( buff, sizeof( char ), file_size, fp );

    fclose( fp );

    while( 1 )
    {
        int cmd = 0;
        scanf( "%d", cmd );

        if ( cmd == PUSH )
        {
            stack_element_t arg = 0;
            scanf( "%d", &arg );
            stack_push( &stk, arg );
        }

        else if ( cmd == SUB )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 - stack_value_1 );
        }

        else if ( cmd == ADD )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 + stack_value_1 );
        }

        else if ( cmd == MUL )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 * stack_value_1 );
        }

        else if ( cmd == DIV )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 / stack_value_1 );
        }

        else if ( cmd == SQRT )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, sqrt( stack_value ) );
        }

        else if ( cmd == SIN )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, sin( stack_value ) );
        }

        else if ( cmd == COS )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, cos( stack_value ) );
        }

        else if ( cmd == OUT )
            fprintf( stderr, "%d", stack_pop( &stk ) );

        else if ( cmd == IN )
        {
            stack_element_t arg = 0;
            scanf( "%d", &arg );
            stack_push( &stk, arg );
        }

        else if ( cmd == DUMP )
            STACK_DUMP( &stk );

        else if ( cmd == HLT )
            break;
        else
            fprintf( stderr, "STNTERR: '%s'", cmd );
    }
}

int count_file_size( FILE* fp ) 
{
    fseek( fp, 0, SEEK_END );
    size_t file_size = ftell( fp );                         
    rewind ( fp );

    return file_size;
}