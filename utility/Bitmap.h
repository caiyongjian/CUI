#ifndef _CUI_UTILITY_RECT_H__
#define _CUI_UTILITY_RECT_H__

#include <windows.h>
namespace cui {
  class BitmapOwner;

  class CuiBitmap {
  public:
    CuiBitmap();
    CuiBitmap(HBITMAP hBitmap);
    CuiBitmap(const CuiBitmap& other);
    CuiBitmap& operator=(const CuiBitmap& other);

    ~CuiBitmap();

    bool IsNull();

    bool Load();
    void Reset();
    Size GetSize();
    
  private:
    BitmapOwner* owner;
  };

  class BitmapHelper {
  public:
    static HBITMAP LoadBitmap(int res_id);
  };
}

#endif//_CUI_UTILITY_RECT_H__
