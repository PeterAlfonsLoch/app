#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_password::simple_password(simple_ui * puiParent) :
   simple_edit_box(puiParent)
{
   
}

simple_password::~simple_password()
{
}


void simple_password::draw_this(HDC hdc)
{

   Gdiplus::Graphics graphics2(hdc);

   graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

   Gdiplus::SolidBrush br(Gdiplus::Color(184, 255, 255, 240));

   graphics2.FillRectangle(&br, m_rect.left, m_rect.top, width(&m_rect), height(&m_rect));

   Gdiplus::SolidBrush b(Gdiplus::Color(223, 84, 84, 77));

   Gdiplus::Font f(L"Geneva", height(&m_rect), 0, Gdiplus::UnitPixel);

   int iLen = m_strText.get_length();

   wchar_t * pwsz = (wchar_t *) ca2_alloc((iLen + 1) * 2);

   pwsz[iLen] = L'\0';
   while(iLen > 0)
   {
      iLen--;
      pwsz[iLen] = L'*';
   }

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF(m_rect.left + 2, m_rect.top), &b);

   ca2_free(pwsz);

}









