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

    int* code = ( int* ) calloc( file_size, sizeof( int ) );
    fread( code, sizeof( char ), file_size, fp );

    fclose( fp );

    while( 1 )
    {
        int ip = 0;

        if ( code[ip] == PUSH )
        {
            stack_element_t arg = 0;
            scanf( "%d", &arg );
            stack_push( &stk, arg );
            ip+=2;
        }

        else if ( code[ip] == SUB )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 - stack_value_1 );
            ip++;
        }

        else if ( code[ip] == ADD )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 + stack_value_1 );
            ip++;
        }

        else if ( code[ip] == MUL )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 * stack_value_1 );
            ip++;
        }

        else if ( code[ip] == DIV )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 / stack_value_1 );
            ip++;
        }

        else if ( code[ip] == SQRT )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, sqrt( stack_value ) );
            ip++;
        }

        else if ( code[ip] == SIN )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, sin( stack_value ) );
            ip++;
        }

        else if ( code[ip] == COS )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, cos( stack_value ) );
            ip++;
        }

        else if ( code[ip] == OUT )
        {
            fprintf( stderr, "%d", stack_pop( &stk ) );
            ip++;
        }

        else if ( code[ip] == IN )
        {
            stack_element_t arg = 0;
            scanf( "%d", &arg );
            stack_push( &stk, arg );
            ip += 2;
        }

        else if ( code[ip] == DUMP )
        {    
            STACK_DUMP( &stk );
            ip++;
        }

        else if ( code[ip] == HLT )
        {    break;
            ip++;
        }
        else
            fprintf( stderr, "STNTERR: '%s'", code[ip] );
    }
}

int count_file_size( FILE* fp ) 
{
    fseek( fp, 0, SEEK_END );
    size_t file_size = ftell( fp );                         
    rewind ( fp );

    return file_size;
}