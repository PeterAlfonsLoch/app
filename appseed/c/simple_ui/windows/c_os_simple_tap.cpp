#include "framework.h"
#include <Gdiplus.h>


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


      Gdiplus::Color crOut;

      Gdiplus::Color crIn;

      Gdiplus::Color crBorderOut;

      Gdiplus::Color crBorderIn;


      if(is_hover() || m_bDown || m_bMouseMove)
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         crOut.SetValue(Gdiplus::Color::MakeARGB(184 + 49, 255, 230, 255));

         crIn.SetValue(Gdiplus::Color::MakeARGB(255, 255, 84 + 49, 255));

         crBorderOut.SetValue(Gdiplus::Color::MakeARGB(184, 150, 100, 150));

         crBorderIn.SetValue(Gdiplus::Color::MakeARGB(184, 255, 240, 255));

#else

         crOut.SetValue(Gdiplus::Color::MakeARGB(184 + 49, 230, 255, 225));

         crIn.SetValue(Gdiplus::Color::MakeARGB(255, 84 + 49, 255, 77 + 49));

         crBorderOut.SetValue(Gdiplus::Color::MakeARGB(184, 100, 150, 100));

         crBorderIn.SetValue(Gdiplus::Color::MakeARGB(184, 240, 255, 235));

#endif

      }
      else
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         crOut.SetValue(Gdiplus::Color::MakeARGB(184, 255, 210, 255));

         crIn.SetValue(Gdiplus::Color::MakeARGB(255, 255, 84 + 49, 255));

         crBorderOut.SetValue(Gdiplus::Color::MakeARGB(184, 90, 20, 90));

         crBorderIn.SetValue(Gdiplus::Color::MakeARGB(184, 255, 240, 255));

#else

         crOut.SetValue(Gdiplus::Color::MakeARGB(184, 210, 255, 205));

         crIn.SetValue(Gdiplus::Color::MakeARGB(255, 84 + 49, 255, 77 + 49));

         crBorderOut.SetValue(Gdiplus::Color::MakeARGB(184, 20, 90, 20));

         crBorderIn.SetValue(Gdiplus::Color::MakeARGB(184, 240, 255, 235));

#endif

      }

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
