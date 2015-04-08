#ifndef CUI_BASE_CWINDOW_H__
#define CUI_BASE_CWINDOW_H__
#include "../utility/helper.h"
#include "../utility/rect.h"

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

  bool Init(HWND hParent);

  HWND GetParent();

  virtual LPCWSTR GetWindowName();

protected:
  static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg,
                                          WPARAM wParam, LPARAM lParam);
  static LRESULT CALLBACK NormalWindowProc(HWND hWnd, UINT uMsg,
                                           WPARAM wParam, LPARAM lParam);
public:
  HWND GetCuiWnd();
  CuiWindow* GetWindow(int uCode);

  bool IsDisabled(BOOL bCheckParent=FALSE);
  void EnableWindow(BOOL bEnable, BOOL bUpdate= FALSE);

  bool IsVisible(BOOL bCheckParent = FALSE);
  void SetVisible(BOOL bVisible, BOOL bUpdate= FALSE);

  void set_style(DWORD style) {
    style_ = style;
  }
  void set_ex_style(DWORD ex_style) {
    ex_style_ = ex_style;
  }
  void SetBounds(const cui::Rect& bounds);

  void Show();

  CUI_BEGIN_MESSAGE_MAP(CuiWindow)
    CUI_MESSAGE_HANDLER(WM_PAINT, OnPaint)
    CUI_MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    CUI_MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
    CUI_MESSAGE_HANDLER(WM_CREATE, OnCreate)
    CUI_MESSAGE_HANDLER(WM_CLOSE, OnClose)
  CUI_END_MSG_MAP();

  LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  cui::Rect GetWndRect();
  ATOM RegisterWindowClass(WNDPROC wndProc, LPCTSTR pszClassName);

protected:
  DWORD style_;
  DWORD ex_style_;
  cui::Rect rect_;
  HWND hwnd_;
};

}

#endif//CUI_BASE_CWINDOW_H__