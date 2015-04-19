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

class CWindowImpl {
public:
  CUI_CLASS_NAME(CWindowImpl, L"cui_window")

  CWindowImpl();
  virtual ~CWindowImpl();

  bool Init(HWND hParent, const Rect& rect);

  HWND GetParent();

  virtual LPCWSTR GetWindowName();

protected:
  static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg,
                                          WPARAM wParam, LPARAM lParam);
  static LRESULT CALLBACK NormalWindowProc(HWND hWnd, UINT uMsg,
                                           WPARAM wParam, LPARAM lParam);
public:
  HWND GetCuiWnd();
  CWindowImpl* GetWindow(int uCode);

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

  CUI_BEGIN_MSG_MAP(CWindowImpl)
    CUI_MSG_WM_PAINT(OnPaint)
    CUI_MSG(WM_ERASEBKGND, OnEraseBkgnd)
    CUI_MSG_RANGE(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
    CUI_MSG(WM_CREATE, OnCreate)
    CUI_MSG(WM_CLOSE, OnClose)
  CUI_END_MSG_MAP();

  LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  void OnPaint();
  LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  cui::Rect GetWndRect();
  ATOM RegisterWindowClass(WNDPROC wndProc, LPCTSTR pszClassName);

protected:
  uint32 style_;
  uint32 ex_style_;
  uint32 class_style_;

  WindowDelegate* window_delegate_;
  cui::Rect rect_;
  HWND hwnd_;
};

}

#endif//CUI_BASE_CWINDOW_H__