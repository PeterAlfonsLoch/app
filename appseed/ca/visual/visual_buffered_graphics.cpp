#include "StdAfx.h"

namespace visual
{

   buffered_graphics::buffered_graphics()
   {

   }

   buffered_graphics::~buffered_graphics()
   {

   }

   void buffered_graphics::Prepare(LPCRECT lpcrect)
   {
      rect rect(lpcrect);
      m_p->SetViewportOrg(rect.top_left());
      m_spbitmap->CreateCompatibleBitmap(m_p, rect.width(), rect.height());
      m_spbitmapBlend->CreateBitmap(
         rect.width(),
         rect.height(),
         1,
         32,
         NULL);
   /*#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|((DWORD)(BYTE)(a))<<24)))
      SelectObject(m_bitmapBlend);
      FillSolidRect(rect, ARGB(0, 0, 0, 0));*/
   }

} // namespace visual