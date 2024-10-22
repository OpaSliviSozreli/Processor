#include "processor.h"

int main( int argc, char** argv )
{
    Spu_t spu = {};

    char* name = ( char* )calloc( strlen( argv[1] ) + 1, sizeof( char ) ); 

    if ( name == NULL )
    {
        fprintf( stderr, "file name is unidentified\n" );
        return 1;
    }

    strcpy( name, argv[1] );

    run();

    return 0;
}