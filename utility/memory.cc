// utf-8 encoding.

#include "memory.h"

#include <stdlib.h>
#include <malloc.h>

void* cui::CuiMalloc( size_t len )
{
  return ::malloc(len);
}

void* cui::CuiRealloc( void* p, size_t len )
{
  return ::realloc(p, len);
}

void* cui::CuiCalloc( size_t count, size_t nElemtLen )
{
  return ::calloc(count, nElemtLen);
}

void cui::CuiFree( void* p )
{
  ::free(p);
}
