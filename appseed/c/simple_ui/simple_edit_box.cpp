#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_edit_box::simple_edit_box()
{
   
   m_iPos = 0;

}

simple_edit_box::~simple_edit_box()
{
}


void simple_edit_box::draw_this(HDC hdc)
{

   Gdiplus::Graphics graphics2(hdc);

   graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

   Gdiplus::SolidBrush br(Gdiplus::Color(84 + 49, 255, 255, 233));

   graphics2.FillRectangle(&br, m_rect.left, m_rect.top, width(&m_rect), height(&m_rect));

   Gdiplus::SolidBrush b(Gdiplus::Color(223, 84, 84, 77));

   Gdiplus::Font f(L"Geneva", height(&m_rect) * 0.7f, 0, Gdiplus::UnitPixel);

   wchar_t * pwsz = utf8_to_16(m_strText);

   float fMargin = (height(&m_rect) * ((1.0f - 0.7f) / 2.0f));

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF(m_rect.left + fMargin, m_rect.top + fMargin), &b);

   ca2_free(pwsz);

}


char to_upper(int ch)
{
   if(ch >= 'a' && ch <= 'z')
   {
      ch = ch - 'a' + 'A';
   }
   return ch;
}


char * to_upper(char * pchParam)
{
   char * pch = pchParam;
   while(*pch == '\0')
   {
      *pch = to_upper(*pch);
      pch++;
   }
   return pchParam;
}








void simple_edit_box::on_char(int ch, UINT uScan)
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

      /*int chInsert;

      if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            if(ch == 2)
               chInsert = '@';
            else
               chInsert = tolower(ch);
         }
         else
         {
            chInsert = toupper(ch);
         }
      }
      else
      {
         if((GetKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            if(ch == 2)
               chInsert = '@';
            else
               chInsert = toupper(ch);
         }
         else
         {
            chInsert = tolower(ch);
         }
      }
      
      vsstring str(chInsert);
      
      */

      wchar_t wsz[32];

      BYTE baState[256];

      GetKeyboardState(baState);

      if((GetKeyState(VK_SHIFT) & 0x80000000) != 0)
      {
         baState[VK_SHIFT] |= 0x80;
      }


      int iRet = ToUnicodeEx(ch, uScan, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));

      if(iRet > 0)
      {

         wsz[iRet] = L'\0';

         vsstring str;

         str.attach(utf16_to_8(wsz));

         if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
         {
            if((GetKeyState(VK_SHIFT) & 0x80000000) != 0)
            {
               to_lower(str.m_psz);
            }
            else
            {
               to_upper(str.m_psz);
            }
         }
         else
         {
            if((GetKeyState(VK_SHIFT) & 0x80000000) != 0)
            {
               to_upper(str.m_psz);
            }
            else
            {
               to_lower(str.m_psz);
            }
         }

         m_strText = m_strText.substr(0, m_iPos) + str + m_strText.substr(m_iPos + 1);

      }

      m_iPos++;

   }

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
