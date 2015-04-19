#include "window_delegate.h"
#include "../resource.h"

namespace cui {

  void WindowDelegate::HandlePaint(const Rect& rect)
  {
    HWND hwnd = window_impl_->hwnd_;


    HDC hDc = ::GetDC(hwnd);

    RECT rc;
    ::GetClientRect(hwnd, &rc);
    cui::Rect rect(rc);
    HDC hMemdc = ::CreateCompatibleDC(hDc);
    HBITMAP hBmp = ::LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
    ::SelectObject(hMemdc, hBmp);
    BITMAPINFO bi = {0};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ::GetDIBits(hMemdc, hBmp, 0, 0, 0, &bi, DIB_RGB_COLORS);

    Graphics *g = new Gdiplus::Graphics();
    g->Clear(Color(0));
    g->DrawImage()

    ::BitBlt(hDc, 0, 0, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight,
      hMemdc, 0, 0, SRCCOPY);
  }

  void WindowDelegate::Init(HWND hWnd, const Rect& rect)
  {
    window_impl_ = new CWindowImpl();
    window_impl_->Init(hWnd, rect);
  }

  void WindowDelegate::Show() {
    window_impl_->Show();
  }

}