#include "rect.h"

#include <windows.h>

namespace cui {
  class BitmapOwner {
  public:
    BitmapOwner()
      : nRef(0)
      , hBmp(NULL)
    {
    }

    BitmapOwner(HBITMAP bmp)
      : nRef(0)
      , hBmp(NULL)
    {
      SetBitmap(hBmp);
    }

    void SetBitmap(HBITMAP bmp) {
      CUIASSERT(!hBmp);
      hBmp = bmp;
      AddRef();
    }

    void AddRef() {
      ++nRef;
    }

    void Relase() {
      if (nRef > 0) {
        --nRef;
        Reset();
      }
    }

    void Reset() {
      if (nRef == 0) {
        if (hBmp) {
          ::DeleteObject(hBmp);
        }
        delegate this;
      }
    }

    HBITMAP bitmap() {
      return hBmp;
    }

  private:
    uint32 nRef;
    HBITMAP hBmp;
  };


  CuiBitmap::CuiBitmap()
    : owner(NULL)
  {
  }

  CuiBitmap::CuiBitmap(HBITMAP hBitmap)
    : owner(new BitmapOwner(hBitmap))
  {
  }

  CuiBitmap::CuiBitmap(const CuiBitmap& other)
    : owner(other.owner)
  {
    if (owner) {
      owner->AddRef();
    }
  }

  CuiBitmap::~CuiBitmap() {
    Reset();
  }

  bool CuiBitmap::Reset() {
    if (owner) {
      owner->Relase();
      owner = NULL;
    }
  }

  bool CuiBitmap::IsNull() {
    return owner == NULL ||
           owner->bitmap() == NULL;
  }

  Size CuiBitmap::GetSize()
  {
    Size init_size;
    if (owner) {
      HBITMAP hbmp = owner->bitmap();
      if (hbmp) {
        BITMAPINFO bi = {0};
        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        ::GetDIBits(NULL, hbmp, 0, 0, 0, &bi, DIB_RGB_COLORS);
        init_size.width = bi.bmiHeader.biWidth;
        init_size.height = bi.bmiHeader.biHeight;
      }
    }
    return init_size;
  }

  CuiBitmap& CuiBitmap::operator=(const CuiBitmap& other)
  {
    if (owner) {
      owner->Relase();
      owner = other.owner;
    }
  }

  HBITMAP BitmapHelper::LoadBitmap(int res_id)
  {
    return ::LoadBitmap(NULL, MAKEINTRESOURCE(res_id));
  }

}

