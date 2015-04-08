// utf-8 encodings.
#ifndef _BASE_BASIC_DEFINES_H__
#define _BASE_BASIC_DEFINES_H__

#include <Windows.h>
#include <crtdbg.h>

#ifndef CUIASSERT
#define CUIASSERT(expr) _ASSERTE(expr)
#endif // CUIASSERT

#ifndef NOREACHED
#define NOREACHED() CUIASSERT(false)
#endif

#endif//_BASE_BASIC_DEFINES_H__