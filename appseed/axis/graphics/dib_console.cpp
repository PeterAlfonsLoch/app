#include "framework.h"


COLORREF dib_console::console_COLORREF(int iColor)
{
   switch(iColor)
   {
   case ::console::WHITE:
      return ARGB(255,255,255,255);
   case ::console::BLUE:
      return ARGB(255,127,127,255);
   case ::console::DARKBLUE:
      return ARGB(255,0,0,255);
   case ::console::RED:
      return ARGB(255,255,0,0);
   case ::console::CYAN:
      return ARGB(255,0,255,255);
   case ::console::MAGENTA:
      return ARGB(255,255,0,255);
   case ::console::YELLOW:
      return ARGB(255,255,255,0);
   }
   return ARGB(255,0,0,0);
}

dib_console::dib_console(::aura::application * papp,size sizeTile):
object(papp),
m_dib(allocer()),
m_sizeTile(sizeTile)
{
   cout.m_spbuffer = this;
   m_x = 0;
   m_y = 0;
}

void dib_console::SetWindowSize(int iHeight,int iWidth)
{

   m_sizeWindow.cx = iWidth;
   m_sizeWindow.cy = iHeight;

   m_dib->create(m_sizeTile.cx * m_sizeWindow.cx,m_sizeTile.cy * m_sizeWindow.cy);
   m_dib->get_graphics()->m_spfont.alloc(allocer());
   //m_dib->get_graphics()->m_spfont->create_pixel_font("Lucida Sans Unicode", m_sizeTile.cy * 0.92);
   m_dib->get_graphics()->m_spfont->create_pixel_font("Lucida Console",m_sizeTile.cy * 0.92);

   SetScreenColor(::console::BLACK);

}


void dib_console::SetCursorVisibility(bool show)
{
}

void dib_console::SetCursorPosition(int y,int x)
{

   m_x = x;
   m_y = y;

}

void dib_console::SetTextColor(int color)
{

   m_iColor = color;

}


void dib_console::SetScreenColor(int color)
{

   m_dib->Fill(console_COLORREF(color));

}

void dib_console::write(const char * psz)
{
   ::draw2d::pen_sp p2(allocer());
   p2->create_solid(4.0,console_COLORREF(m_iColor));
   ::draw2d::pen_sp p(allocer());
   p->create_solid(2.0,console_COLORREF(m_iColor));
   string str;
   int i2 = 2;
   while(*psz)
   {
      ::str::international::multibyte_to_utf8(437,str,string(*psz));
      wstring wstr = str;
      wchar_t w = ((const wchar_t *)wstr)[0];
      //    m_dib->get_graphics()->
      m_dib->get_graphics()->set_smooth_mode(::draw2d::smooth_mode_none);
      m_dib->get_graphics()->FillSolidRect(m_x * m_sizeTile.cx,m_y * m_sizeTile.cy,m_sizeTile.cx,m_sizeTile.cy,ARGB(255,0,0,0));
      if(!defer_write(*psz,m_x * m_sizeTile.cx,m_y * m_sizeTile.cy,m_sizeTile.cx,m_sizeTile.cy))
      {
         //         m_dib->get_graphics()->FillSolidRect(m_x * m_sizeTile.cx + 1,m_y * m_sizeTile.cy + 1,m_sizeTile.cx - 1,m_sizeTile.cy - 1,ARGB(255,0,0,0));

         if(*psz == (char)209)// horizontal double / down simple
         {


            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );

            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );

         }
         else if(*psz == (char)205)// horizontal double
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
         }
         else if(*psz == (char)196) // horizontal simple
         {
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
         }
         else if(*psz == (char)186) // vertical double
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
         }
         else if(*psz == (char)199) // vertical double / right simple
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
         }
         else if(*psz == (char)182) // vertical double / left simple
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
         }
         else if(*psz == (char)179) // vertical simple
         {
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
         }
         else if(*psz == (char)218) // top-left simple
         {
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy
               );
         }
         else if(*psz == (char)201) // top-left double
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2 - i2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
         }
         else if(*psz == (char)200) // bottom-left double
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2 - i2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy
               );
         }
         else if(*psz == (char)192) // bottom-left simple
         {
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx + 1,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy
               );
         }
         else if(*psz == (char)188) // bottom-right double
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2 + i2,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy
               );
         }
         else if(*psz == (char)217) // bottom-right simple
         {
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy
               );
         }
         else if(*psz == (char)187) // top-right double
         {
            m_dib->get_graphics()->SelectObject(p2);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2 + i2,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
         }
         else if(*psz == (char)191) // top-right simple
         {
            m_dib->get_graphics()->SelectObject(p);

            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy / 2
               );
            m_dib->get_graphics()->DrawLine(
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_x * m_sizeTile.cx + m_sizeTile.cx / 2,m_y * m_sizeTile.cy + m_sizeTile.cy + 1
               );
         }
         else
         {
            m_dib->get_graphics()->set_text_color(console_COLORREF(m_iColor));
            m_dib->get_graphics()->draw_text(str,rect(m_x * m_sizeTile.cx,m_y * m_sizeTile.cy,
               m_x * m_sizeTile.cx + m_sizeTile.cx,m_y * m_sizeTile.cy + m_sizeTile.cy),DT_CENTER | DT_VCENTER);
         }

      }

      m_x++;

      if(m_x >= (m_dib->m_size.cx / m_sizeTile.cx))
      {
         m_x = 0;
         m_y++;
      }

      psz++;
   }

}


void dib_console::write(const void * lpBuf,::primitive::memory_size nCount)
{
   string str((const char *)lpBuf,MIN(strnlen_s((const char *)lpBuf,nCount),nCount));
   write(str);
}


bool dib_console::defer_write(char ch,int x,int y,int cx,int cy)
{
   return false;
}



