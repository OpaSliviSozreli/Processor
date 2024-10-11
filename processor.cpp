#include "processor.h"

void Run()
{
    stack_t stk = {};

    STACK_CTOR( &stk );

    while( 1 )
    {
        char cmd[50] = "";
        scanf( "%s", cmd );

        if ( strcmp( cmd, "push" ) == 0 )
        {
            stack_element_t arg = 0;
            scanf( "%d", &arg );
            stack_push( &stk, arg );
        }

        else if ( strcmp( cmd, "sub" ) == 0 )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 - stack_value_1 );
        }

        else if ( strcmp( cmd, "add" ) == 0 )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 + stack_value_1 );
        }

        else if ( strcmp( cmd, "mul" ) == 0 )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 * stack_value_1 );
        }

        else if ( strcmp( cmd, "div" ) == 0 )
        {
            stack_element_t stack_value_1 = stack_pop( &stk );
            stack_element_t stack_value_2 = stack_pop( &stk );

            stack_push( &stk, stack_value_2 / stack_value_1 );
        }

        else if ( strcmp( cmd, "sqrt" ) == 0 )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, sqrt( stack_value ) );
        }

        else if ( strcmp( cmd, "sin" ) == 0 )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, sin( stack_value ) );
        }

        else if ( strcmp( cmd, "cos" ) == 0 )
        {
            stack_element_t stack_value = stack_pop( &stk );

            stack_push( &stk, cos( stack_value ) );
        }

        else if ( strcmp( cmd, "out" ) == 0 )
            fprintf( stderr, "%d", stack_pop( &stk ) );

        else if ( strcmp( cmd, "in" ) == 0 )
        {
            stack_element_t arg = 0;
            scanf( "%d", &arg );
            stack_push( &stk, arg );
        }

        else if ( strcmp( cmd, "dump" ) == 0 )
            STACK_DUMP( &stk );

        else if ( strcmp( cmd, "hlt" ) == 0 )
            break;
        else
            fprintf( stderr, "STNTERR: '%s'", cmd );
    }
}