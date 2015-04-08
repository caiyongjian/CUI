#ifndef _UTILITY_HELPER_H__
#define _UTILITY_HELPER_H__
#include "../base/basic_defines.h"

#define CUI_CLASS_NAME(theClass, classname)               \
public:                                                   \
  static LPCTSTR GetClassName()                           \
  {                                                       \
    return classname;                                     \
  }                                                       \
                                                          \
  virtual bool IsClassName(LPCWSTR lpszName)              \
  {                                                       \
    if (wcscmp(GetClassName(), lpszName) == 0)            \
    {                                                     \
      return true;                                        \
    }                                                     \
    return false;                                         \
  }                                                       \

#define CUI_BEGIN_MESSAGE_MAP(theClass) \
public: \
  BOOL ProcessWindowMessage(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, \
      _In_ LPARAM lParam, _Inout_ LRESULT& lResult, _In_ DWORD dwMsgMapID = 0) \
    { \
      BOOL bHandled = TRUE; \
      (hWnd); \
      (uMsg); \
      (wParam); \
      (lParam); \
      (lResult); \
      (bHandled); \
      switch(dwMsgMapID) \
      { \
      case 0:

#define CUI_ALT_MSG_MAP(msgMapID) \
      break; \
      case msgMapID:

#define CUI_MESSAGE_HANDLER(msg, func) \
  if (uMsg == msg) \
  { \
    bHandled = TRUE; \
    lResult = func(uMsg, wParam, lParam, bHandled); \
    if (bHandled) \
      return TRUE; \
  }

#define CUI_MESSAGE_RANGE_HANDLER(msgFirst, msgLast, func) \
  if (uMsg >= msgFirst && uMsg <= msgLast) \
  { \
    bHandled = TRUE; \
    lResult = func(uMsg, wParam, lParam, bHandled); \
    if (bHandled) \
      return TRUE; \
  }

#define CUI_COMMAND_HANDLER(id, code, func) \
  if (uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
  { \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if (bHandled) \
      return TRUE; \
  }

#define CUI_END_MSG_MAP() \
    break; \
  default: \
    CUIASSERT(FALSE); \
    break; \
  }\
  return FALSE; \
}

HMODULE GetModuleFromAddress(void* address);

#endif//_UTILITY_HELPER_H__