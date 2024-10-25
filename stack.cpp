#include "stack.h"

int stack_ctor( stack_t *stk ON_DEBUG( , const char* file, int line ) )
{
    ON_DEBUG( 
            stk->file_name = file;
            stk->line      = line;
            )

    stk->size = 0;
    stk->capacity = 28;
    
    stk->data = ( stack_element_t* )calloc( stk->capacity, sizeof( stack_element_t ) + sizeof( canary_t ) );
    stk->data = ( stack_element_t* )( ( char* )stk->data + sizeof( canary_t ) ); 

    stk->hash = MurmurHash2( ( char* )stk->data, stk->capacity * sizeof( stack_element_t ) );
 
    *( canary_t* )( ( char* )stk->data - sizeof( canary_t ) ) = _LEFT_CANARY_;
    *( canary_t* )( ( char* )stk->data + stk->capacity * sizeof( stack_element_t ) ) = _RIGHT_CANARY_;

    stk->left_struct_canary  = _STRUCT_LEFT_CANARY_;
    stk->right_struct_canary = _STRUCT_RIGHT_CANARY_;

    set_poison( stk );

    STACK_ASSERT( stk );

    return STACK_FUNC_OK;
}

int stack_dtor( stack_t* stk )
{
    STACK_ASSERT( stk );

    for ( size_t i = 0; i < ( size_t )stk->capacity - 1; i++ )
        stk->data[i] = 0;
        
    stk->capacity = 0;
    stk->size = 0;

    free( stk->data ); 

    STACK_ASSERT( stk );

    return STACK_FUNC_OK;
}

unsigned int MurmurHash2 ( char* key, unsigned int len )
{
  const unsigned int m = 0x5bd1e995;
  const unsigned int seed = 0;
  const int r = 24;

  unsigned int h = seed ^ len;

  const unsigned char* data = ( const unsigned char* )key;
  unsigned int k = 0;

  while ( len >= 4 )
  {
      k  = data[0];
      k |= data[1] << 8;
      k |= data[2] << 16;
      k |= data[3] << 24;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      data += 4;
      len -= 4;
  }

  switch ( len )
  {
    case 3:
      h ^= data[2] << 16;
    case 2:
      h ^= data[1] << 8;
    case 1:
      h ^= data[0];
      h *= m;
    default:
      assert ( 0 && "Hash function doesnt work right" );
  };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

int stack_error( const stack_t* stk )
{
    if ( stk == NULL )
        return PTR_IS_ZERO;
    if ( stk->data == NULL )
        return PTR_TO_DATA_IS_ZERO;
    if ( stk->size < 0 )
        return STACK_WRONG_SIZE;
    if ( stk->capacity < 0 )
        return CAPACITY_IS_NEGATIVE;
    if ( stk->size > stk->capacity ) 
        return STACK_OVERFLOW;
    if ( stk->left_struct_canary != _STRUCT_LEFT_CANARY_ )
        return STACK_LEFT_CANARY_PROBLEM;
    if ( stk->right_struct_canary != _STRUCT_RIGHT_CANARY_ )
        return STACK_RIGHT_CANARY_PROBLEM;
    if ( *( canary_t* )( ( char* )stk->data - sizeof( canary_t ) ) != _LEFT_CANARY_ )
        return LEFT_CANARY_PROBLEM;
    if ( *( canary_t* )( ( char* )stk->data + stk->capacity * sizeof( stack_element_t ) + sizeof( canary_t ) ) != 0 )
        return RIGHT_CANARY_PROBLEM;
    if ( stk->hash != MurmurHash2( ( char* )stk->data, stk->capacity * sizeof( stack_element_t ) ) )
        return HASH_PROBLEM;
        
    return STACK_OK;
}

int dump( stack_t* stk ON_DEBUG( , const char* file, int line ) )
{
    STACK_ASSERT( stk );
 
    fprintf( stderr, "the data is %p\n", stk->data );

    fprintf( stderr, " named stack born in line %d at file %s \n" ON_DEBUG( stk->line, stk->file_name ) ); // TODO: fix

    fprintf( stderr, "capacity is %d\n", stk->capacity );

    fprintf( stderr, "current size is %d\n", stk->size );

    fprintf( stderr, "error code is %d\n", stack_error( stk ) );

    fprintf( stderr, "hash is %d\n", stk->hash );

    fprintf( stderr, "left canary in struct is %0X\n", stk->left_struct_canary );
    fprintf( stderr, "right canary in struct is %0X\n", stk->right_struct_canary );

    fprintf( stderr, "left canary in data is %0X\n", *( canary_t* )( ( char* )stk->data - sizeof( canary_t ) ) );
    fprintf( stderr, "right canary in data is %0X\n", *( canary_t* )( ( char* )stk->data + stk->capacity * sizeof( stack_element_t ) ) );

    for ( int i = 0; i < stk->capacity - 1; i++ )
        fprintf( stderr, "[%d] elem: data value is <%d>\n", i, stk->data[i] );

    STACK_ASSERT( stk );

    return STACK_FUNC_OK; 
}

int stack_assert_func( stack_t* stk )
{
    int stk_error = stack_error( stk );

    if ( stk_error != STACK_OK )
        return stk_error;

    return STACK_OK;
}

int stack_push( stack_t* stk, stack_element_t value )
{
    STACK_ASSERT( stk );
    my_realloc( stk );

    stk->data[stk->size] = value;
    stk->size++;

    STACK_ASSERT( stk );

    return STACK_FUNC_OK;
}

stack_element_t stack_pop( stack_t* stk ) 
{
    STACK_ASSERT( stk );
    
    my_realloc( stk );

    if ( stk->size == 0 )
    {
        fprintf( stderr, "stack size is zero" );
        return SIZE_IS_ZERO;
    }

    stack_element_t value = stk->data[stk->size];
    stk->size--;
    
    STACK_ASSERT( stk );

    return value;
}

void my_realloc( stack_t *stk )
{                                  
    STACK_ASSERT( stk );
    if ( stk->size == stk->capacity )
    {
        stk->data = ( stack_element_t* )realloc( ( char* )stk->data - sizeof( canary_t ), stk->capacity * 2 * sizeof( stack_element_t ) + 2 * sizeof( canary_t ) );
        stk->data = ( stack_element_t* )( ( char* )stk->data + sizeof( canary_t ) );

        set_poison( stk );
    }
    if ( stk->size ==  stk->capacity / 4 )
    { 
        stk->data = ( stack_element_t* )realloc( ( char* )stk->data - sizeof( canary_t ), stk->capacity / 2 * sizeof( stack_element_t ) + 2 * sizeof( canary_t ) );
        stk->data = ( stack_element_t* )( ( char* )stk->data + sizeof( canary_t ) );      

        stk->capacity = stk->capacity / 4; 
    }
    STACK_ASSERT( stk );
}

void set_poison( stack_t *stk )
{
    for ( int i = stk->size; i < stk->capacity - 1; i++ ) 
        stk->data[i] = POISON; 
}