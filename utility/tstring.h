// utf-8 encoding.

#ifndef _UTILITY_TSTRING_H__
#define _UTILITY_TSTRING_H__

namespace cui
{
  struct TStringData
  {
    long nRef;
    unsigned long nDataLen;
    unsigned long nAllocLen;

    _inline void* data() const
    {
      return (void*)(this + 1);
    }

    _inline void AddRef()
    {
      CUIASSERT(nRef >= 0);
      InterlockedIncrement(&nRef);
    }

    _inline void Release()
    {
      CUIASSERT(nRef != 0);
      if (InterlockedDecrement(&nRef) < 0)
      {
        cui::CuiFree(this);
      }
    }

    _inline bool IsShared() const
    {
      return nRef > 1;
    }

    _inline bool IsLocked() const
    {
      return nRef < 0;
    }

    _inline void Lock()
    {
      CUIASSERT(nRef > 1);
      nRef--;
      if (nRef == 0)
      {
        nRef = -1;
      }
    }

    _inline void UnLock()
    {
      CUIASSERT(IsLocked());
      if (IsLocked())
      {
        nRef++;
        if (nRef == 0)
        {
          nRef = 1;
        }
      }
    }
  };

  struct char_traits
  {
    typedef char _TYPE;
    typedef char* P_TYPE;
    typedef char** PP_TYPE;
    typedef const char* CP_TYPE;

    static size_t StrLen(CP_TYPE psz)
    {
      return psz ? ::strlen(psz) : 0;
    }

    static int StrCmp(CP_TYPE psz, CP_TYPE psz1 )
    {
      return ::strcmp(psz, psz1);
    }

    static int StrICmp(CP_TYPE psz, CP_TYPE psz1)
    {
      return ::stricmp(psz, psz1);
    }

    static int StrNCmp(CP_TYPE psz, CP_TYPE psz1, size_t len)
    {
      return ::strncmp(psz, psz1, len);
    }

    static P_TYPE StrChr(CP_TYPE psz, _TYPE ch)
    {
      return ::strchr(psz, ch);
    }

    static P_TYPE StrRChr(CP_TYPE psz, _TYPE ch)
    {
      return ::strrchr(psz, ch);
    }

    static P_TYPE StrStr(CP_TYPE psz, CP_TYPE psz1)
    {
      return ::strstr(psz, psz1);
    }

    static P_TYPE StrUpper(P_TYPE psz)
    {
      return ::strupr(psz);
    }

    static P_TYPE StrLower(P_TYPE psz)
    {
      return ::strlwr(psz);
    }

    static int IsSpace(_TYPE ch)
    {
      return ::isspace(ch);
    }

    static _TYPE CharLower(_TYPE ch)
    {
      return (_TYPE)::tolower(ch);
    }

    static _TYPE CharUpper(_TYPE ch)
    {
      return (_TYPE)toupper(ch);
    }

    static P_TYPE CharNext(P_TYPE psz)
    {
      return psz + 1;
    }

    static int Format(PP_TYPE ppszDst, CP_TYPE pszFormat, va_list args)
    {
      int len = ::_vscprintf( pszFormat, args ); // _vscprintf doesn't count terminating '\0'
      size_t malloc_size = (len + 1) * sizeof(_TYPE);
      *ppszDst = (P_TYPE)cui::CuiMalloc(malloc_size);
      ::vsprintf(*ppszDst, pszFormat, args);
      return len;
    }
  };


  //////////////////////////////////////////////////////////////////////////
  // wchar_traits.

  struct wchar_traits
  {
    typedef wchar_t _TYPE;
    typedef wchar_t* P_TYPE;
    typedef wchar_t** PP_TYPE;
    typedef const wchar_t* CP_TYPE;

    static size_t StrLen(CP_TYPE psz)
    {
      return psz ? ::wcslen(psz) : 0;
    }

    static int StrCmp(CP_TYPE psz, CP_TYPE psz1 )
    {
      return ::wcscmp(psz, psz1);
    }

    static int StrICmp(CP_TYPE psz, CP_TYPE psz1)
    {
      return ::wcsicmp(psz, psz1);
    }

    static int StrNCmp(CP_TYPE psz, CP_TYPE psz1, size_t len)
    {
      return ::wcsncmp(psz, psz1, len);
    }

    static P_TYPE StrChr(CP_TYPE psz, _TYPE ch)
    {
      return ::wcschr(psz, ch);
    }

    static P_TYPE StrRChr(CP_TYPE psz, _TYPE ch)
    {
      return ::wcsrchr(psz, ch);
    }

    static P_TYPE StrStr(CP_TYPE psz, CP_TYPE psz1)
    {
      return ::wcsstr(psz, psz1);
    }

    static P_TYPE StrUpper(P_TYPE psz)
    {
      return ::wcsupr(psz);
    }

    static P_TYPE StrLower(P_TYPE psz)
    {
      return ::wcslwr(psz);
    }

    static int IsSpace(_TYPE ch)
    {
      return ::iswspace(ch);
    }

    static _TYPE CharLower(_TYPE ch)
    {
      return (_TYPE)::towlower(ch);
    }

    static _TYPE CharUpper(_TYPE ch)
    {
      return (_TYPE)::towupper(ch);
    }

    static P_TYPE CharNext(P_TYPE psz)
    {
      return psz + 1;
    }

    static int Format(PP_TYPE ppszDst, CP_TYPE pszFormat, va_list args)
    {
      int len = ::_vscwprintf( pszFormat, args ); // _vscprintf doesn't count terminating '\0'
      size_t malloc_size = (len + 1) * sizeof(_TYPE);
      *ppszDst = (P_TYPE)cui::CuiMalloc(malloc_size);
      ::vswprintf(*ppszDst, pszFormat, args);
      return len;
    }
  };

  
  class SStringT



}

#endif//_UTILITY_TSTRING_H__