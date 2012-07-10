#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_edit_box::simple_edit_box(simple_ui * puiParent) :
   simple_ui(puiParent)
{
   
}

simple_edit_box::~simple_edit_box()
{
}


void simple_edit_box::draw_this(HDC hdc)
{

   Gdiplus::Graphics graphics2(hdc);

   graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

   Gdiplus::SolidBrush br(Gdiplus::Color(184, 255, 255, 240));

   graphics2.FillRectangle(&br, m_rect.left, m_rect.top, width(&m_rect), height(&m_rect));

   Gdiplus::SolidBrush b(Gdiplus::Color(223, 84, 84, 77));

   Gdiplus::Font f(L"Geneva", height(&m_rect), 0, Gdiplus::UnitPixel);

   wchar_t * pwsz = utf8_to_16(m_strText);

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF(m_rect.left + 2, m_rect.top), &b);

   ca2_free(pwsz);

}









void simple_edit_box::on_char(int ch)
{
   if(ch == VK_TAB)
   {
      focus_next();
   }
   else if(ch == VK_RETURN)
   {
      on_action("submit");
   }
   else if(ch == VK_BACK)
   {
      if(m_iPos > m_strText.get_length())
      {
         m_iPos = m_strText.get_length();
      }
      if(m_iPos > 0)
      {
         m_strText = m_strText.substr(0, m_iPos - 1) + m_strText.substr(m_iPos);
         m_iPos--;
      }
      else
      {
         m_iPos = 0;
      }
   }
   else if(ch == VK_DELETE)
   {
      if(m_iPos < 0)
      {
         m_iPos = 0;
      }
      if(m_iPos < m_strText.get_length())
      {
         m_strText = m_strText.substr(0, m_iPos) + m_strText.substr(m_iPos + 1);
      }
   }
   else 
   {
      m_strText += ch;
   }
}

void simple_edit_box::on_lbutton_down(int x, int y)
{
}
   
void simple_edit_box::on_lbutton_up(int x, int y)
{
}



bool simple_edit_box::is_focusable()
{

   return true;

}
