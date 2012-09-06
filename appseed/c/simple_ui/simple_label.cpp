#include "framework.h"

#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_label::simple_label()
{
   
}

simple_label::~simple_label()
{
}



void simple_label::draw_this(HDC hdc)
{


   Gdiplus::Graphics graphics2(hdc);

   Gdiplus::Color c;

   if(get_plugin()->m_eschema == ::hotplugin::plugin::schema_darker)
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS
      c.SetValue(Gdiplus::Color::MakeARGB(255, 184 + 49, 149 + 49, 177 + 49));
#else
      c.SetValue(Gdiplus::Color::MakeARGB(255, 149 + 49, 184 + 49, 123 + 49));
#endif

   }
   else
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS
      c.SetValue(Gdiplus::Color::MakeARGB(255, 84, 49, 77));
#else
      c.SetValue(Gdiplus::Color::MakeARGB(255, 49, 84, 23));
#endif

   }

   Gdiplus::SolidBrush b(c);

   Gdiplus::Font f(L"Geneva", (float) (height(&m_rect) * 0.7f), 0.0f, Gdiplus::UnitPixel);

   wchar_t * pwsz = utf8_to_16(m_strText);

   float fMargin = (height(&m_rect) * ((1.0f - 0.7f) / 2.0f));

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF((float) (m_rect.left), (float) (m_rect.top + fMargin)), &b);

   ca2_free(pwsz);

}

