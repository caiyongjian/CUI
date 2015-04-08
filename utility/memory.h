// utf-8 encoding.

#ifndef _UTILITY_MEMORY_H__
#define _UTILITY_MEMORY_H__

namespace cui {
  void* CuiMalloc(size_t len);
  void* CuiRealloc(void* p, size_t len);
  void* CuiCalloc(size_t count, size_t nElemtLen);
  void  CuiFree(void* p);
}

#endif//_UTILITY_MEMORY_H__