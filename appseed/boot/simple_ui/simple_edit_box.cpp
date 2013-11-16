#include "framework.h"


simple_edit_box::simple_edit_box()
{

   m_iPos = 0;

}

simple_edit_box::~simple_edit_box()
{
}







bool simple_edit_box::on_lbutton_down(int32_t x, int32_t y)
{

   set_focus(this);

   return true;

}

bool simple_edit_box::on_lbutton_up(int32_t x, int32_t y)
{

   return true;

}



bool simple_edit_box::is_focusable()
{

   return true;

}


/*

CLASS_DECL_BOOT char to_upper(int32_t ch)
{
   
   if(ch >= 'a' && ch <= 'z')
   {
      ch = ch - 'a' + 'A';
   }

   return ch;

}


CLASS_DECL_BOOT char * to_upper(char * pchParam)
{
char * pch = pchParam;
while(*pch == '\0')
{
   *pch = to_upper(*pch);
   pch++;
}
return pchParam;
}


*/


void simple_edit_box::draw_this(simple_graphics & g)
{

   rect rectClient;

   get_client_rect(rectClient);

   g.set_alpha_mode(::draw2d::alpha_mode_blend);

   simple_brush br;

   br.create_solid(g, ARGB(84 + 49, 255, 255, 233));

   g.fill_rect(rectClient, br);

   draw_focus_rect(g);

   simple_solid_brush b(g, ARGB(223, 49, 49, 23));

   simple_pixel_font f(g, (int32_t)height(&rectClient) * 10, "Geneva");

   g.select(b);

   g.select(f);

   float fMargin = (height(&rectClient) * ((1.0f - 0.7f) / 2.0f));

   g.text_out((int32_t)(rectClient.left + fMargin), (int32_t)(rectClient.top + fMargin), m_strText);

}

bool simple_edit_box::on_char(int32_t iKey, const string & strChar)
{

   if (iKey == VK_CONTROL)
   {

   }
   else    if (iKey == VK_MENU)
   {

   }
   else    if (iKey == VK_SHIFT)
   {

   }
   else if (iKey == VK_TAB)
   {
      focus_next();
      return true;
   }
   else if(iKey == VK_RETURN)
   {
      on_action("submit");
      return true;
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
      return true;
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
      return true;
   }
   else
   {

      m_strText = m_strText.substr(0, m_iPos) + strChar + m_strText.substr(m_iPos + 1);

      m_iPos++;
      return true;

   }

   return false;

}
