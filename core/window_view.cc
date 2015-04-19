#include "window_view.h"

namespace cui {

  void WindowView::SetWindowName(String16& name)
  {
    window_name_ = name;
  }

   void WindowView::Show()
   {
     //Layout();
     //Paint();
   }
 
   void WindowView::SetStyle(uint32 style) {
     style_ = style;
   }
 
   void WindowView::SetExStyle(uint32 ex_style) {
     ex_style_ = ex_style;
   }
 
   void WindowView::Init()
   {
      
   }

}