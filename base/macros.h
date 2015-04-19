// utf-8 encodings.
#ifndef _BASE_MACROS_H__
#define _BASE_MACROS_H__

#define DISALLOW_COPY(theClass) \
  theClass(const theClass&)

#define DISALLOW_ASSIGN(theClass) \
  theClass& operator=(const theClass&)

#define DISALLOW_COPY_AND_ASSIGN(theClass) \
  DISALLOW_COPY(theClass); \
  DISALLOW_ASSIGN(theClass)

#endif//_BASE_MACROS_H__