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

    static P_TYPE NoneSafeStrCpy(P_TYPE pdst, P_TYPE pSrc, int nLen)
    {
      ::memcpy(pdst, pSrc, nLen * sizeof(_TYPE));
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

    static P_TYPE NoneSafeStrCpy(P_TYPE pdst, P_TYPE pSrc, int nLen)
    {
      ::memcpy(pdst, pSrc, nLen * sizeof(_TYPE));
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

  static int _tstr_rgInitData[] = { -1, 0, 0, 0, 0, 0, 0, 0 };
  TStringData* _tstr_initDataNil = (TStringData*)&_tstr_rgInitData;
  const void* _tstr_initPszNil = (const void*)(((unsigned char*)&_tstr_rgInitData) + sizeof(TStringData));

  template<class tchar, class tchar_traits>
  class TStringT
  {
  public:
    typedef tchar _tchar;
    typedef const _tchar* pctchar;
    typedef tchar_traits _tchar_traits;

    _tchar* m_pszData;

    TStringT()
    {
      Init();
    }

    void Init()
    {
      m_pszData = (pctchar)_tstr_initPszNil;
    }

    TStringData* GetData()
    {
      return ((TStringData*)m_pszData) - 1;
    }

    TStringT(const TStringT& other)
    {
      CUIASSERT(other.GetData()->nRef != 0);
      if (other.GetData()->nRef >= 0)
      {
        other.GetData()->AddRef();
        m_pszData = other.m_pszData;
      }
      else
      {
        Init();
        *this = other.m_pszData;
      }
    }

    TStringT(tchar ch, int nLength = 1)
    {
      Init();
      if (nLength >= 1)
      {
        if (AllocBuffer(nLength))
        {
          for (int i = 0; i < nLength; i++)
          {
            m_pszData[i] = ch;
          }
        }
      }
    }

    int SafeLen(const tchar* psz)
    {
      return psz ? (int)tchar_traits::StrLen(psz) : 0;
    }

    TStringT(const tchar* psz, int nLength)
    {
      Init();
      if (nLength <0)
      {
        nLength = SafeLen(psz);
      }
      if (nLength > 0)
      {
        if (AllocBuffer(nLength))
        {
          tchar_traits::NoneSafeStrCpy(m_pszData, psz, nLength);
        }
      }
    }

    TStringT(const tchar* psz)
    {
      Init();
      int nLen = SafeLen(psz);
      if (nLen > 0)
      {
        if (AllocBuffer(nLen))
        {
          char_traits::NoneSafeStrCpy(m_pszData, psz, nLen);
        }
      }
    }

    ~TStringT()
    {
      TStringData* pdata = GetData();
      if (pdata != _tstr_initDataNil)
      {
        cui::CuiFree(pdata);
      }
    }

    int GetLength() const
    {
      return GetData()->nDataLen;
    }

    bool IsEmpty() const
    {
      return GetData()->nDataLen == 0;   
    }

    void Empty()
    {
      TStringData* pData = GetData();
      if (pData->nDataLen == 0)
      {
        return;
      }
      Relase();
    }

    void Relase()
    {
      TStringData* pData = GetData();
      if (pData != _tstr_initDataNil)
      {
        CUIASSERT(pData->nRef >= 1);
        pData->Release();
        Init();
      }
    }

    bool AllocBuffer(int nLen)
    {
      TStringData* pdata = AllocData(nLen);
      if (pdata)
      {
        m_pszData = pdata->data();
        return true;
      }
      
      return false;
    }

    TStringData* AllocData(int nLen, TStringData* pOld = NULL)
    {
      CUIASSERT(nLen >= 1);
      int malloc_len = sizeof(TStringData) + (nLen + 1) * sizeof(tchar);

      TStringData* pNew = NULL;
      if (pOld)
      {
        pNew = cui::CuiRealloc(pOld, malloc_len);
      }
      else
      {
        pNew = cui::CuiMalloc(malloc_len);
      }
      if (pNew == NULL)
      {
        NOREACHED();
        return pNew;
      }

      pNew->nRef = 1;
      pNew->nAllocLen = malloc_len;
      pNew->nDataLen = nLen;

      tchar* pch_data = pNew->data();
      pch_data[0] = '\0';
      return pNew;
    }


  };



}

#endif//_UTILITY_TSTRING_H__