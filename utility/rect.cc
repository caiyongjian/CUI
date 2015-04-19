#include "rect.h"

#include <windows.h>

namespace cui {

  Rect::Rect()
    : x(0)
    , y(0)
    , width(0)
    , height(0)
  {

  }

  Rect::Rect(int a, int b, int c, int d)
    : x(a)
    , y(b)
    , width(c)
    , height(d)
  {

  }

  Rect::Rect(const Rect& other)
    : x(other.x)
    , y(other.y)
    , width(other.width)
    , height(other.height)
  {

  }

  Rect::Rect( const RECT& other )
    : x(other.left)
    , y(other.top)
    , width(other.right - other.left)
    , height(other.bottom - other.top)
  {
  }

  Rect& Rect::operator=(const Rect& other)
  {
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
    return *this;
  }

  bool Rect::operator==(const Rect& other)
  {
    return x == other.x &&
           y == other.y &&
           width == other.width &&
           height == other.height ? true : false;
  }

  bool Rect::operator!=(const Rect& other)
  {
    return !(*this==other);
  }

  bool Rect::is_empty()
  {
    return width == 0 && height == 0;
  }

}

