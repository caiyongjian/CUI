#include "rect.h"

#include <windows.h>

namespace cui {



  bool RenderGDI::DrawImage(const CuiBitmap& bitmap, const Rect& rect)
  {
    HDC hDc = ::GetDC(hwnd_);

    RECT rc;
    ::GetClientRect(hwnd_, &rc);
    cui::Rect rect(rc);
    HDC hMemdc = ::CreateCompatibleDC(hDc);
    HBITMAP hBmp = ::LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
    ::SelectObject(hMemdc, hBmp);
    BITMAPINFO bi = {0};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ::GetDIBits(hMemdc, hBmp, 0, 0, 0, &bi, DIB_RGB_COLORS);

   ::BitBlt(hDc, 0, 0, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight,
      hMemdc, 0, 0, SRCCOPY);

    return true;
  }

}

