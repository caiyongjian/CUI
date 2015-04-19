#ifndef CUI_BASE_VIEW_H__
#define CUI_BASE_VIEW_H__
#include "../base/macros.h"

#include "../utility/helper.h"
#include "../utility/rect.h"

namespace cui {

  class View {
  public:
    View();
    View* parent()
    {
      return parent_;
    }

    View* parent() const
    {
      return parent_;
    }
    
    void SetBounds(Rect& bounds);
    void SetText(String16& text);
    void SetToolTip(String16& tooltip);
    void SetWindowName(String16& name);

    void Init();
    void Show();

    void SetStyle(uint32 style);
    void SetExStyle(uint32 ex_style);

    void OnPaint();

  private:
    View* parent_;
    Rect bounds_;

    uint32 style_;
    uint32 ex_style_;

    String16 window_text_;
    String16 tooltip_text_;
    String16 window_name_;

    DISALLOW_COPY_AND_ASSIGN(View);
  };

}

#endif//CUI_BASE_VIEW_H__