#ifndef CUI_BASE_CWINDOW_DELEGATE_H__
#define CUI_BASE_CWINDOW_DELEGATE_H__

namespace cui {

  class WindowDelegate {
  public:
    void HandlePaint(const Rect& rect);
    void Init(HWND hWnd, const Rect& rect);
    void Show();
  private:
    CWindowImpl* window_impl_;
  };
}

#endif//CUI_BASE_CWINDOW_DELEGATE_H__