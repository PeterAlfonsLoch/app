#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_tap::simple_tap()
{
   
   m_strId = "submit";

}


simple_tap::~simple_tap()
{
}


void simple_tap::draw_this(HDC hdc)
{

   //draw_simple(hdc);

   draw_volume(hdc);

}


void simple_tap::draw_simple(HDC hdc)
{

   {
      
      Gdiplus::Graphics graphics2(hdc);

      graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

#if CA2_PLATFORM_VERSION == CA2_BASIS

      Gdiplus::SolidBrush br(Gdiplus::Color(184, 255, 184, 240));

#else

      Gdiplus::SolidBrush br(Gdiplus::Color(184, 184, 255, 177));

#endif

      graphics2.FillRectangle(&br, m_rect.left, m_rect.top, width(&m_rect), height(&m_rect));

   }

   draw_text(hdc);

}


void simple_tap::draw_volume(HDC hdc)
{

   {

      Gdiplus::Graphics graphics2(hdc);

      graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

#if CA2_PLATFORM_VERSION == CA2_BASIS

      Gdiplus::Color crOut(184, 255, 240, 255);

      Gdiplus::Color crIn(255, 255, 184, 255);

      Gdiplus::Color crBorderOut(184, 90, 20, 90);

      Gdiplus::Color crBorderIn(184, 255, 240, 255);

#else
   
      Gdiplus::Color crOut(184, 240, 255, 235);

      Gdiplus::Color crIn(255, 184, 255, 177);

      Gdiplus::Color crBorderOut(184, 20, 90, 20);

      Gdiplus::Color crBorderIn(184, 240, 255, 235);

#endif

      int iBorderH = height(&m_rect) / 2;

      Gdiplus::LinearGradientBrush br1(Gdiplus::Point(0, m_rect.top - 1), Gdiplus::Point(0, m_rect.top + iBorderH + 2), crOut, crIn);

      graphics2.FillRectangle(&br1, m_rect.left, m_rect.top, width(&m_rect), iBorderH);

      Gdiplus::LinearGradientBrush br2(Gdiplus::Point(0, m_rect.top + iBorderH - 1), Gdiplus::Point(0, m_rect.top + iBorderH * 2 + 2), crIn, crOut);

      graphics2.FillRectangle(&br2, m_rect.left, m_rect.top + iBorderH, width(&m_rect), iBorderH);

      Gdiplus::Pen pen1(crBorderOut);

      graphics2.DrawRectangle(&pen1, m_rect.left, m_rect.top, width(&m_rect), iBorderH * 2);

      Gdiplus::Pen pen2(crBorderIn);

      graphics2.DrawRectangle(&pen2, m_rect.left + 1, m_rect.top + 1, width(&m_rect) - 2, iBorderH * 2 - 2);

   }

   draw_text(hdc);

}


void simple_tap::draw_text(HDC hdc)
{

   Gdiplus::Graphics graphics2(hdc);

#if CA2_PLATFORM_VERSION == CA2_BASIS
   Gdiplus::SolidBrush b(Gdiplus::Color(223, 84, 49, 77));
#else
   Gdiplus::SolidBrush b(Gdiplus::Color(223, 49, 84, 23));
#endif

   Gdiplus::Font f(L"Geneva", (float) (height(&m_rect) * 0.7), 0.0f, Gdiplus::UnitPixel);

   wchar_t * pwsz = utf8_to_16(m_strText);

   float fMargin = (height(&m_rect) * ((1.0f - 0.7f) / 2.0f));

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF((float) (m_rect.left + fMargin), (float) (m_rect.top + fMargin)), &b);

   ca2_free(pwsz);

}


void simple_tap::on_char(int ch, UINT uScan)
{
   
   if(ch == VK_RETURN || ch == VK_SPACE)
   {

      on_action(m_strId);

   }
   else if(ch == VK_TAB)
   {

      focus_next();

   }


}

void simple_tap::on_lbutton_down(int x, int y)
{
   
   set_focus(this);

   m_bDown = true;

}
   
void simple_tap::on_lbutton_up(int x, int y)
{

   if(m_bDown)
   {
      
      m_bDown = false;

      on_action(m_strId);

   }

}




bool simple_tap::is_focusable()
{
   return true;
}

