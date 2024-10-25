#include "assembler.h"

Errors assembler( PtrToLines* lines_parameters, OriginalText* original_text, LabelsTable* labels )
{
    assert( lines_parameters != nullptr );
    assert( original_text    != nullptr );
    assert( labels           != nullptr );
    
    FILE* input_file = fopen( "original.txt", "rb" );

    if ( !input_file )
        return CANT_OPEN_INPUT_FILE;
    
    input_text( original_text );
    split_text_into_lines( lines_parameters, original_text );

    size_t file_size = count_file_size( input_file );

    fclose( input_file );

    lable_table_ctor( labels );

    int* code = ( int* ) calloc( file_size, sizeof( char ) ); 

    while ( 1 )
    {             
        int arg = 0;
        char first_word_in_line[DEFAULT_SIZE_OF_WORD] = "";
        int cur_str = 0;
        int cur_arg_in_code = 0;

        sscanf( lines_parameters->ptrs_to_strings[cur_str], "%s", first_word_in_line ); 

        if ( strcmp( first_word_in_line, "push" ) == 0 )
        {
            code[cur_arg_in_code++] == PUSH;               
            sscanf( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "pop" ) == 0 )
        {
            code[cur_arg_in_code++] == POP;
            sscanf( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "add" ) == 0 )
        {
            code[cur_arg_in_code++] == ADD;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "sub" ) == 0 )
        {
            code[cur_arg_in_code++] == SUB;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "mul" ) == 0 )
        {
            code[cur_arg_in_code++] == MUL;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "div" ) == 0 )
        {
            code[cur_arg_in_code++] == DIV;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "out" ) == 0 )
        {
            code[cur_arg_in_code++] == OUT;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++; 
        }

        else if ( strcmp( first_word_in_line, "in" ) == 0 )
        {
            code[cur_arg_in_code++] == IN;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "sqrt" ) == 0 )
        {
            code[cur_arg_in_code++] == SQRT;                    
            sscanf ( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++; 
        }

        else if ( strcmp( first_word_in_line, "sin" ) == 0 )
        {
            code[cur_arg_in_code++] == SIN;                    
            sscanf ( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "cos" ) == 0 )
        {
            code[cur_arg_in_code++] == COS;                    
            sscanf ( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "dump" ) == 0 )
        {
            code[cur_arg_in_code++] == DUMP;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            cur_str++; 
        }

        else if( strcmp( first_word_in_line, "hlt" ) == 0 )
        {
            code[cur_arg_in_code++] == HLT;
            check_if_lable( labels, first_word_in_line, cur_arg_in_code );
            break;
        }
    }

    FILE* output_file = fopen( "assembler.txt", "wb" );

    if ( !output_file )
        return CANT_OPEN_OUTPUT_FILE;

    fwrite( code, sizeof( int ), sizeof( code ) / sizeof( code[0] ), output_file );

    fclose( output_file );
}

void lable_table_ctor( LabelsTable* labels )
{
    assert( labels != nullptr );

    for ( size_t i = 0; i < NUMBER_OF_LABLES; i++ )
        labels[i].label->pointer = -1;
}

int check_if_lable( LabelsTable* labels, char* first_word_in_line, int cur_arg_in_code )
{
    if ( strchr( ( const char* )first_word_in_line, ':' ) != nullptr )
    {
        for ( size_t i = 0; i < NUMBER_OF_LABLES; i++ )
        {
            if ( labels[i].label->pointer == -1 &&
                    labels[i].label->name == nullptr )
            {
                labels[i].label->pointer = cur_arg_in_code;
                labels[i].label->name = first_word_in_line;

                break;
            }

            else if ( labels[i].label->pointer == -1 &&
                        strcmp( labels[i].label->name, first_word_in_line ) == 0 )
            {
                labels[i].label->pointer = cur_arg_in_code;
                break;
            }

        }
    }
}
