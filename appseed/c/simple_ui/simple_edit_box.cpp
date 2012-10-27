#include "framework.h"


simple_edit_box::simple_edit_box()
{

   m_iPos = 0;

}

simple_edit_box::~simple_edit_box()
{
}







void simple_edit_box::on_lbutton_down(int x, int y)
{

   set_focus(this);

}

void simple_edit_box::on_lbutton_up(int x, int y)
{
}



bool simple_edit_box::is_focusable()
{

   return true;

}




CLASS_DECL_c char to_upper(int ch)
{
if(ch >= 'a' && ch <= 'z')
{
   ch = ch - 'a' + 'A';
}
return ch;
}


CLASS_DECL_c char * to_upper(char * pchParam)
{
char * pch = pchParam;
while(*pch == '\0')
{
   *pch = to_upper(*pch);
   pch++;
}
return pchParam;
}





void simple_edit_box::draw_this(simple_graphics & g)
{

   g.set_alpha_mode(::ca::alpha_mode_blend);

   simple_brush br;

   br.create_solid(g, ARGB(84 + 49, 255, 255, 233));

   g.fill_rect(m_rect, br);

   draw_focus_rect(g);

   simple_solid_brush b(g, ARGB(223, 49, 49, 23));

   simple_pixel_font f(g, height(&m_rect) * 10, "Geneva");

   g.select(b);

   g.select(f);

   float fMargin = (height(&m_rect) * ((1.0f - 0.7f) / 2.0f));

   g.text_out((int) (m_rect.left + fMargin), (int) (m_rect.top + fMargin), m_strText);

}

void simple_edit_box::on_char(int iKey, const vsstring & strChar)
{

   if(iKey == VK_TAB)
   {
      focus_next();
   }
   else if(iKey == VK_RETURN)
   {
      on_action("submit");
   }
   else if(iKey == VK_BACK)
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
   else if(iKey == VK_DELETE)
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

      m_strText = m_strText.substr(0, m_iPos) + strChar + m_strText.substr(m_iPos + 1);

      m_iPos++;

   }

}
