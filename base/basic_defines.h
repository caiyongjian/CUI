// utf-8 encodings.
#ifndef _BASE_BASIC_DEFINES_H__
#define _BASE_BASIC_DEFINES_H__

#include <Windows.h>
#include <crtdbg.h>

#ifndef CUIASSERT
#define CUIASSERT(expr) _ASSERTE(expr)
#endif // CUIASSERT

#ifndef CHECK
#define CHECK(expr) !(expr) ? (void*)0 = 0x123 : (void*)0;
#endif

#ifndef NOREACHED
#define NOREACHED() CUIASSERT(false)
#endif

#define String8 std::string;
#define String16 std::wstring;

#define uint32 unsigned int;
#define uint16 unsigned short;


#endif//_BASE_BASIC_DEFINES_H__