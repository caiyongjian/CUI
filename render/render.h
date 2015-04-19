#ifndef _CUI_UTILITY_RECT_H__
#define _CUI_UTILITY_RECT_H__

#include <windows.h>
namespace cui {

  class Render {
  public:
    bool DrawImage(const CuiBitmap& bitmap, const Rect& rect) = 0;
  };

  class RenderGDI {
  public:
    void SetWndHandle(HWND hwnd) {
      hwnd_ = hwnd;
    }
    bool DrawImage(const CuiBitmap& bitmap, const Rect& rect) override;
  private:
    HWND hwnd_;
  };
}

#endif//_CUI_UTILITY_RECT_H__
