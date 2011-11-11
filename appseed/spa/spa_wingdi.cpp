#include "spa.h"


void FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(hdc, clr);
   ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}


BOOL TextOutU(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
{
   vsstring str(pszUtf8, iSize);

   SIZE size;
   size.cx = 0;
   size.cy = 0;
   if(str.find(_unitext("✓")) != vsstring::npos)
   {
      str = str_replace(str, _unitext("✓"), "");
      ::GetTextExtentPointW(hdc, L"C", 1, &size);
      size.cx = size.cy;
      HBRUSH hbrush = ::CreateSolidBrush(RGB(0xaa, 0XCC, 0xaa));
      HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc, (HGDIOBJ) hbrush); 
      HPEN hpen = (HPEN) ::GetStockObject(NULL_PEN);
      HPEN hpenOld = (HPEN) ::SelectObject(hdc, (HGDIOBJ) hpen); 
      ::Ellipse(hdc, x + 1, y + 1, x + size.cx - 2, y + size.cy - 2);
      ::SelectObject(hdc, (HGDIOBJ)  hbrushOld);
      ::SelectObject(hdc, (HGDIOBJ)  hpenOld);
      ::DeleteObject((HGDIOBJ) hbrush);
      size.cx += 4;
   }
   BOOL b = TextOutU_dup(hdc, size.cx + x, y, str, str.length());
   return b;
}


