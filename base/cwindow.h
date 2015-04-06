#ifndef CUI_BASE_CWINDOW_H__
#define CUI_BASE_CWINDOW_H__
#include "../utility/helper.h"

namespace cui {

  typedef enum tagCW_CODE
  {
    CW_FIRSTCHILD=0,
    CW_LASTCHILD,
    CW_PREVSIBLING,
    CW_NEXTSIBLING,
    CW_PARENT,
    CW_OWNER,
  } CW_CODE;

class CuiWindow {
public:
  CUI_CLASS_NAME(CuiWindow, L"cui_window")

  CuiWindow();
  virtual ~CuiWindow();

public:
  HWND GetCuiWnd();
  CuiWindow* GetWindow(int uCode);

  BOOL IsDisabled(BOOL bCheckParent=FALSE);
  void EnableWindow(BOOL bEnable, BOOL bUpdate= FALSE);

  BOOL IsVisible(BOOL bCheckParent = FALSE);
  void SetVisible(BOOL bVisible, BOOL bUpdate= FALSE);

  void set_style(DWORD style) {
    style_ = style;
  }

  void set_ex_style(DWORD ex_style) {
    ex_style_ = ex_style;
  }


  CUI_BEGIN_MESSAGE_MAP(CuiWindow)
    CUI_MESSAGE_HANDLER(WM_PAINT, OnPaint)
    CUI_MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    CUI_MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
  END_MSG_MAP();

  LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
  HWND  hwnd_;
  DWORD style_;
  DWORD ex_style_;
};

}

#endif//CUI_BASE_CWINDOW_H__