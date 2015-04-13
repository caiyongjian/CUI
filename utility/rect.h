#ifndef _CUI_UTILITY_RECT_H__
#define _CUI_UTILITY_RECT_H__

#include <windows.h>
namespace cui {

  class Rect {
  public:
    Rect();
    Rect(int a, int b, int c, int d);
    Rect(const Rect& other);
    Rect(const RECT& other);
    Rect& operator=(const Rect& other);
    bool operator==(const Rect& other);
    bool operator!=(const Rect& other);

  public:
    int x;
    int y;
    int width;
    int height;
  };
}

#endif//_CUI_UTILITY_RECT_H__
