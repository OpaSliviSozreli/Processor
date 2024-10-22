#include "processor.h"

Errors run( FILE* fp )
{
    if ( !fp )
        return CANT_OPEN_BYTE_FILE;
    
    Spu_t* spu = {};
    spu_ctor( fp, spu );

    size_t file_size = count_file_size( fp );
    fread( spu->code, sizeof( int ), file_size / sizeof( int ), fp );

    while( 1 )
    {
        switch( spu->code[spu->ip] )
        {
            case( PUSH ):
            {
                stack_push( &spu->stk, spu->code[spu->ip + 1] );
                spu->ip+=2;
            }

            case( SUB ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk );
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                stack_push( &spu->stk, stack_value_2 - stack_value_1 );
                spu->ip++;
            }

            case( ADD ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk );
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                stack_push( &spu->stk, stack_value_2 + stack_value_1 );
                spu->ip++;
            }

            case( MUL ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk );
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                stack_push( &spu->stk, stack_value_2 * stack_value_1 );
                spu->ip++;
            }

            case( DIV ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk );
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                stack_push( &spu->stk, stack_value_2 / stack_value_1 );
                spu->ip++;
            }

            case( SQRT ):
            {
                stack_element_t stack_value = stack_pop( &spu->stk );

                stack_push( &spu->stk, sqrt( stack_value ) );
                spu->ip++;
            }

            case( SIN ):
            {
                stack_element_t stack_value = stack_pop( &spu->stk );

                stack_push( &spu->stk, sin( stack_value ) );
                spu->ip++;
            }

            case( COS ):
            {
                stack_element_t stack_value = stack_pop( &spu->stk );

                stack_push( &spu->stk, cos( stack_value ) );
                spu->ip++;
            }

            case( OUT ):
            {
                printf( "%d", stack_pop( &spu->stk ) );
                spu->ip++;
            }

            case( IN ):
            {
                stack_element_t arg = 0;
                scanf( "%d", &arg );
                stack_push( &spu->stk, arg );
                spu->ip++;
            }

            case( DUMP ):
            {    
                spu_dump( spu, &spu->stk ); 
                spu->ip++;
            }

            case ( JA ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk );
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                if ( stack_value_1 > stack_value_2 )
                    spu->ip = spu->code[spu->ip + 1];
                else break;
            }
            
            case ( JB ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk );
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                if ( stack_value_1 < stack_value_2 )
                    spu->ip = spu->code[spu->ip + 1];
                else break;
            }
            
            case ( JE ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk ); 
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                if ( stack_value_1 == stack_value_2 )
                    spu->ip = spu->code[spu->ip + 1];
                else break;
            }
            
            case ( JNE ):
            {
                stack_element_t stack_value_1 = stack_pop( &spu->stk ); 
                stack_element_t stack_value_2 = stack_pop( &spu->stk );

                if ( stack_value_1 != stack_value_2 )
                    spu->ip = spu->code[spu->ip + 1];
                else break;
            }

            case( HLT ):
            {   
                free ( spu->code ); 
                spu->ip++;
                break;
            }
            default:
                fprintf( stderr, "Syntax Error: '%d'", spu->code[spu->ip] );
        }
    }

    return SUCCESS;
}

int spu_dump( Spu_t* spu )
{
    assert( spu != nullptr );

    fprintf( stderr, "----------------------------------------------------------------------\n" );
    fprintf( stderr, "code adr is %0xp\n", spu->code );

    fprintf( stderr, "ip is %d\n", spu->ip );

    for ( size_t i = 0; i < ( size_t )NUMBER_OF_REGS; i++ )
        fprintf( stderr, "current [%d] registers content is %d", i, spu->regs[i] );
    
    fprintf( stderr, "----------------------------------------------------------------------\n" );

    STACK_DUMP( &spu->stk );
}

Errors spu_ctor( FILE* fp, Spu_t* spu )
{
    if ( !fp )
        return WRONG_FILE_TO_SPU_CTOR;
    spu->ip = 0;

    assert( spu != nullptr );

    size_t file_size = count_file_size( fp );
    spu->code = ( int* )calloc( file_size, sizeof( char ) );

    STACK_CTOR( &spu->stk );

    spu->regs = ( int* )calloc( NUMBER_OF_REGS, sizeof( int ) );

    return SUCCESS;

}

int spu_dtor( Spu_t* spu )
{
    assert( spu != nullptr );

    spu->ip = 0;

    for( size_t i = 0; i < sizeof( spu->code ) / sizeof( spu->code[0] ); i++ )
        spu->code[i] = 0;

    stack_dtor( &spu->stk );

    for ( size_t i = 0; i < ( size_t )NUMBER_OF_REGS; i++ )
        spu->regs[i] = 0;
}