#include "assembler.h"

int main( int argc, char** argv )
{
    PtrToLines   lines_parameters = {};
    OriginalText original_text    = {};

    assembler( &lines_parameters, &original_text );
    
    return 0;
}

