#include "tstring.h"

#pragma warning(disable:4996)

namespace cui
{
    // Globals

    // For an empty string, m_pszData will point here
    // (note: avoids special case of checking for NULL m_pszData)
    // empty string data (and locked)
    static int _tstr_rgInitData[] = { -1, 0, 0, 0, 0, 0, 0, 0 };
    TStringData* _tstr_initDataNil = (TStringData*)&_tstr_rgInitData;
    const void* _tstr_initPszNil = (const void*)(((unsigned char*)&_tstr_rgInitData) + sizeof(TStringData));

    char* char_traits::StrUpper( char* psz )
    {
#ifdef _MBCS
      return (char*)_mbsupr((unsigned char*)psz);
#else
      return strupr(psz);
#endif
    }

    char* char_traits::StrLower( char* psz )
    {
#ifdef _MBCS
      return (char*)_mbslwr((unsigned char*)psz);
#else
      return strlwr(psz);
#endif
    }

    int char_traits::Format( char** ppszDst, const char* pszFormat, va_list args )
    {
      int len = _vscprintf( pszFormat, args ); // _vscprintf doesn't count terminating '\0'
      *ppszDst = (char*)cui::CuiMalloc(len+1);
      vsprintf(*ppszDst, pszFormat, args);
      return len;
    }


    wchar_t* wchar_traits::StrUpper( wchar_t* psz )
    {
      return _wcsupr(psz);
    }

    wchar_t* wchar_traits::StrLower( wchar_t* psz )
    {
      return _wcslwr(psz);
    }

    int wchar_traits::Format( wchar_t** ppszDst, const wchar_t* pszFormat, va_list args )
    {
      int len = _vscwprintf( pszFormat, args ); // _vscprintf doesn't count terminating '\0'
      *ppszDst = (wchar_t*)cui::CuiMalloc((len+1)*sizeof(wchar_t));
      vswprintf(*ppszDst, pszFormat, args);
      return len;
    }

}
