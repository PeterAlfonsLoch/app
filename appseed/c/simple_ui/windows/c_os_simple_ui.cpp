#include "framework.h"
#include <GdiPlus.h>


void simple_ui::draw_this(HDC hdc)
{

   Gdiplus::Graphics graphics2(hdc);

   graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

   //Gdiplus::Color crOut(0, 255, 255, 233);

   //Gdiplus::Color crIn(84 + 49, 255, 255, 233);

   Gdiplus::Color crOut;

   Gdiplus::Color crIn;

   if(get_plugin()->m_eschema == ::hotplugin::plugin::schema_darker)
   {

      crOut.SetValue(Gdiplus::Color::MakeARGB(0, 84, 84, 77));

      crIn.SetValue(Gdiplus::Color::MakeARGB(84 + 49, 84, 84, 77));

   }
   else
   {

      crOut.SetValue(Gdiplus::Color::MakeARGB(0, 255, 255, 233));

      crIn.SetValue(Gdiplus::Color::MakeARGB(84 + 49, 255, 255, 233));

   }

   int iBorderH = min(height(&m_rect) / 2, 49);

   Gdiplus::LinearGradientBrush br1(Gdiplus::Point(0, 0), Gdiplus::Point(0, iBorderH), crOut, crIn);

   graphics2.FillRectangle(&br1, m_rect.left, m_rect.top, width(&m_rect), iBorderH);

   Gdiplus::SolidBrush br(crIn);

   graphics2.FillRectangle(&br, m_rect.left, m_rect.top + iBorderH, width(&m_rect), height(&m_rect) - (iBorderH * 2));

   Gdiplus::LinearGradientBrush br2(Gdiplus::Point(0, m_rect.bottom - iBorderH), Gdiplus::Point(0, m_rect.bottom), crIn, crOut);

   graphics2.FillRectangle(&br2, m_rect.left, m_rect.bottom - iBorderH, width(&m_rect), iBorderH);


}
