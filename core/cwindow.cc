#include "cwindow.h"
namespace cui {

CuiWindow* pLockedThis = NULL;

CuiWindow::CuiWindow()
  : hwnd_(NULL)
  , style_(0)
  , ex_style_(0)
{

}

CuiWindow::~CuiWindow() {

}

LRESULT CuiWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
}

LRESULT CuiWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  //Paint Controls.
  return 0;
}

LRESULT CuiWindow::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  // Paint Backbround.
  return 0;
}

LRESULT CuiWindow::OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;

  // Paint Backbround.
  return 0;
}

HWND CuiWindow::GetCuiWnd()
{
  return hwnd_;
}

CuiWindow* CuiWindow::GetWindow(int uCode)
{
  CuiWindow* pRet = NULL;
  switch(uCode)
  {
  case CW_FIRSTCHILD:
    break;
  }
  return pRet;
}

bool CuiWindow::IsDisabled(BOOL bCheckParent/*=FALSE*/)
{
//   if (bCheckParent) return m_dwState & WndState_Disable;
//   else return m_bDisable;
  return true;
}

void CuiWindow::EnableWindow(BOOL bEnable, BOOL bUpdate/* = FALSE */) {
}

ATOM CuiWindow::RegisterWindowClass(WNDPROC wndProc, LPCTSTR pszClassName)
{
  WNDCLASSEX wnd_class = {0};
  wnd_class.cbSize = sizeof(wnd_class);
  wnd_class.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  wnd_class.lpfnWndProc = wndProc;
  wnd_class.hInstance = GetModuleFromAddress(wndProc);
  wnd_class.hCursor = ::LoadCursor(NULL, IDC_ARROW);
  wnd_class.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wnd_class.lpszClassName = pszClassName;
  return ::RegisterClassEx(&wnd_class);
}

bool CuiWindow::Init(HWND hParent) {
  ATOM atom = RegisterWindowClass(StartWindowProc, GetClassName());
  if (!atom) {
    return false;
  }

  cui::Rect rect = GetWndRect();
  HWND hWnd = ::CreateWindowEx(
      ex_style_, reinterpret_cast<wchar_t*>(atom), NULL, style_, rect.x,
      rect.y, rect.width, rect.height, hParent, NULL, NULL, this);
  //TODO:other operation.
  return true;
}

LRESULT CuiWindow::StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
  CuiWindow* pThis = reinterpret_cast<CuiWindow*>(pcs->lpCreateParams);
  pThis->hwnd_ = hWnd;
  ::SetWindowLong(hWnd, GWL_USERDATA, (DWORD_PTR)pThis);
  ::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD_PTR)NormalWindowProc);
  return NormalWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CuiWindow::NormalWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  CuiWindow* pThis = reinterpret_cast<CuiWindow*>(::GetWindowLong(hWnd, GWL_USERDATA));
  if (!pThis) {
    return 0;
  }

  LRESULT result = 0;
  if (!pThis->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, result)) {
    result = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
  return result;
}

LPCWSTR CuiWindow::GetWindowName()
{
  return L"";
}

cui::Rect CuiWindow::GetWndRect()
{
  return rect_;
}

void CuiWindow::Show()
{
  ::ShowWindow(hwnd_, SW_SHOW);
}

void CuiWindow::SetBounds(const cui::Rect& bounds)
{
  rect_ = bounds;
}

LRESULT CuiWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
  PostQuitMessage(0);
  return 0;
}

}