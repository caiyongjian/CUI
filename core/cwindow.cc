#include "cwindow.h"
#include "../resource.h"

namespace cui {
static const uint32 kWindowDefaultChildStyle =
    WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

static const uint32 kWindowDefaultStyle =
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

static const uint32 kWindowDefaultExStyle = 0;

CWindowImpl::CWindowImpl()
  : hwnd_(NULL)
  , style_(0)
  , ex_style_(kWindowDefaultExStyle)
  , class_style_(CS_DBLCLKS)
{
}

CWindowImpl::~CWindowImpl() {

}

LRESULT CWindowImpl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
}

void CWindowImpl::OnPaint() {
  PAINTSTRUCT ps = {0};
  HDC display_dc = ::BeginPaint(hwnd_, &ps);
  CHECK(display_dc);

  Rect rect(ps.rcPaint);
  if (!rect.is_empty() && window_delegate_) {
    window_delegate_->HandlePaint(Rect(ps.rcPaint));
  }

  ::EndPaint(hwnd_, &ps);

  return 1;
}

LRESULT CWindowImpl::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  // Paint Backbround.
  HDC hDc = ::GetDC(hwnd_);
  RECT rc;
  ::GetClientRect(hwnd_, &rc);
  cui::Rect rect(rc);
  HDC hMemdc = ::CreateCompatibleDC(hDc);
  HBITMAP hBmp = ::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_PNG2));
  ::SelectObject(hMemdc, hBmp);
  BITMAPINFO bi = {0};
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  ::GetDIBits(hMemdc, hBmp, 0, 0, 0, &bi, DIB_RGB_COLORS);
  ::BitBlt(hDc, 0, 0, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight,
    hMemdc, 0, 0, SRCCOPY);
  return 0;
}

LRESULT CWindowImpl::OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;

  // Paint Backbround.
  return 0;
}

HWND CWindowImpl::GetCuiWnd()
{
  return hwnd_;
}

CWindowImpl* CWindowImpl::GetWindow(int uCode)
{
  CWindowImpl* pRet = NULL;
  switch(uCode)
  {
  case CW_FIRSTCHILD:
    break;
  }
  return pRet;
}

bool CWindowImpl::IsDisabled(BOOL bCheckParent/*=FALSE*/)
{
//   if (bCheckParent) return m_dwState & WndState_Disable;
//   else return m_bDisable;
  return true;
}

void CWindowImpl::EnableWindow(BOOL bEnable, BOOL bUpdate/* = FALSE */) {
}

ATOM CWindowImpl::RegisterWindowClass(WNDPROC wndProc, LPCTSTR pszClassName)
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

bool CWindowImpl::Init(HWND hParent, const Rect& rect) {
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

LRESULT CWindowImpl::StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (uMsg != WM_CREATE) {
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
  CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
  CWindowImpl* pThis = reinterpret_cast<CWindowImpl*>(pcs->lpCreateParams);
  pThis->hwnd_ = hWnd;
  ::SetWindowLong(hWnd, GWL_USERDATA, (DWORD_PTR)pThis);
  ::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD_PTR)NormalWindowProc);
  return NormalWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CWindowImpl::NormalWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  CWindowImpl* pThis = reinterpret_cast<CWindowImpl*>(::GetWindowLong(hWnd, GWL_USERDATA));
  if (!pThis) {
    return 0;
  }

  LRESULT result = 0;
  if (!pThis->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, result)) {
    result = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
  return result;
}

LPCWSTR CWindowImpl::GetWindowName()
{
  return L"";
}

cui::Rect CWindowImpl::GetWndRect()
{
  return rect_;
}

void CWindowImpl::Show()
{
  ::ShowWindow(hwnd_, SW_SHOW);
}

void CWindowImpl::SetBounds(const cui::Rect& bounds)
{
  rect_ = bounds;
}

LRESULT CWindowImpl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
  PostQuitMessage(0);
  return 0;
}

}