#include "view.h"

namespace cui {


  void View::SetParent(View* other)
  {
    parent_ = other;
  }

  void View::SetBounds(Rect& bounds)
  {
    bounds_ = bounds;
  }

  void View::SetText(String16& text)
  {
    window_text_ = text;
  }

  void View::SetToolTip(String16& tooltip)
  {
    tooltip_text_ = tooltip;
  }

  void View::SetWindowName(String16& name)
  {
    window_name_ = name;
  }

  void View::OnPaint()
  {

  }

//   void View::Show()
//   {
//     //Layout();
//     //Paint();
//   }
// 
//   void View::SetStyle(uint32 style) {
//     style_ = style;
//   }
// 
//   void View::SetExStyle(uint32 ex_style) {
//     ex_style_ = ex_style;
//   }
// 
//   void View::Init()
//   {
// 
//   }

}