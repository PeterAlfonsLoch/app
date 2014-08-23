#include "framework.h"

namespace visual
{

   buffered_graphics::buffered_graphics()
   {

   }

   buffered_graphics::~buffered_graphics()
   {

   }

   void buffered_graphics::Prepare(const RECT & rectParam)
   {
      ::rect rect(rectParam);
      m_p->SetViewportOrg(rect.top_left());
      m_spbitmap->CreateCompatibleBitmap(m_p, rect.width(), rect.height());
      m_spbitmapBlend->CreateBitmap(
         m_p,
         rect.width(),
         rect.height(),
         1,
         32,
         NULL,
         rect.width() * sizeof(COLORREF));
   /*#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((uint32_t)(BYTE)(b))<<16)|((uint32_t)(BYTE)(a))<<24)))
      SelectObject(m_bitmapBlend);
      FillSolidRect(rect, ARGB(0, 0, 0, 0));*/
   }

} // namespace visual
