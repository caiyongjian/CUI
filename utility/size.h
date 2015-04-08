// utf-8 encodings.
#ifndef _UTILITY_SIZE_H__
#define _UTILITY_SIZE_H__

namespace cui {
class Size {

public:
  Size();
  Size(int wid, int hei);
  Size(const Size& other);
  Size& operator=(const Size& other);
  bool operator==(const Size& other);
  bool operator!=(const Size& other);

public:
  int width;
  int height;
};

Size::Size()
: width(0)
, height(0)
{

}

Size::Size(const Size& other)
: width(other.width)
, height(other.height)
{

}

Size::Size(int wid, int hei)
: width(wid)
, height(hei)
{

}

Size& Size::operator=(const Size& other)
{
  width = other.width;
  height = other.height;
  return *this;
}

bool Size::operator==(const Size& other)
{
  return width == other.width &&
         height == other.height;
}

bool Size::operator!=(const Size& other)
{
  return !(*this == other);
}

} //namespce cui


#endif//_UTILITY_SIZE_H__