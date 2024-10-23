#include "assembler.h"

Errors assembler( PtrToLines* lines_parameters, OriginalText* original_text, LabelsTable* labels )
{
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

        // TODO: CheckIfLabel

        if ( strcmp( first_word_in_line, "push" ) == 0 )
        {
            code[cur_arg_in_code++] == PUSH;               
            sscanf( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            cur_str++;

           /// TOOO: move from here  if ( find_label( first_word_in_line ) == 1 )
            {
                if ( labels->type = NEXT )
                {
                    for ( size_t i = 0; i < NUMBER_OF_LABLES; i++ )
                    {
                        if ( labels[i].label->pointer == -1 &&
                             labels[i].label->name == nullptr )
                        {
                            labels[i].label->pointer = PUSH;
                            labels[i].label->name = first_word_in_line;

                            break;
                        }

                        else if ( labels[i].label->pointer == -1 &&
                                  strcmp( labels[i].label->name, first_word_in_line ) == 0 )
                        {
                            labels[i].label->pointer = PUSH;
                            break;
                        }

                    }
                }
            }
        }

        else if ( strcmp( first_word_in_line, "add" ) == 0 )
        {
            code[cur_arg_in_code++] == ADD;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "sub" ) == 0 )
        {
            code[cur_arg_in_code++] == SUB;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "mul" ) == 0 )
        {
            code[cur_arg_in_code++] == MUL;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "div" ) == 0 )
        {
            code[cur_arg_in_code++] == DIV;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "out" ) == 0 )
        {
            code[cur_arg_in_code++] == OUT;
            cur_str++; 
        }

        else if ( strcmp( first_word_in_line, "in" ) == 0 )
        {
            code[cur_arg_in_code++] == IN;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "sqrt" ) == 0 )
        {
            code[cur_arg_in_code++] == SQRT;                    
            sscanf ( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            cur_str++; 
        }

        else if ( strcmp( first_word_in_line, "sin" ) == 0 )
        {
            code[cur_arg_in_code++] == SIN;                    
            sscanf ( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "cos" ) == 0 )
        {
            code[cur_arg_in_code++] == COS;                    
            sscanf ( lines_parameters->ptrs_to_strings[cur_str], "%s %d", first_word_in_line, arg );        
            code[cur_arg_in_code++] == arg;
            cur_str++;
        }

        else if ( strcmp( first_word_in_line, "dump" ) == 0 )
        {
            code[cur_arg_in_code++] == DUMP;
            cur_str++; 
        }

        else if( strcmp( first_word_in_line, "hlt" ) == 0 )
        {
            code[cur_arg_in_code++] == HLT;
            break;
        }
    }

    FILE* output_file = fopen( "assembler.txt", "wb" );

    if ( !output_file )
        return CANT_OPEN_OUTPUT_FILE;

    fwrite( code, sizeof( int ), sizeof( code ) / sizeof( code[0] ), output_file );

    fclose( output_file );
}

bool find_label( const char* str ) // TODO: replae find_label with strchr 
{
    bool islabel = 0;
    char ch = 0;

    for (int i = 0; ch != '\0'; i++)
    {
        ch = str[i];

        if ( ch == ':' )
        {
            islabel = 1;
            break;
        } 
    }

    return islabel;
}

void lable_table_ctor( LabelsTable* labels )
{
    assert( labels != nullptr );

    for ( size_t i = 0; i < NUMBER_OF_LABLES; i++ )
        labels[i].label->pointer = -1;
}
