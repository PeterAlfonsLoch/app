#include "framework.h"


namespace hotplugin
{


   void entry_hall_windows_on_paint(HDC hdc,const RECT & rect,const string & strEntryHallText)
   {

      HBRUSH hbrushBack = ::CreateSolidBrush(RGB(184,184,177));
      HBRUSH hbrushDark = ::CreateSolidBrush(RGB(84,84,77));
      HBRUSH hbrushLate = ::CreateSolidBrush(RGB(84 + 49,84 + 49,77 + 42));
      HBRUSH hbrushLite = ::CreateSolidBrush(RGB(255,255,250));
      HBRUSH hbrushGren = ::CreateSolidBrush(RGB(184,254,177));

      HPEN hpen = (HPEN) ::GetStockObject(NULL_PEN);

      HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc,hbrushBack);

      HPEN hpenOld = (HPEN) ::SelectObject(hdc,hpen);

      ::Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);

      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if(height(rect) < h)
      {
         top = rect.top;
         bottom = rect.bottom;
      }
      else
      {
         top = rect.top + height(rect) / 2 - h / 2;
         bottom = rect.top + height(rect) / 2 + h / 2;
      }

      if(width(rect) < m)
      {
         left = rect.left;
         right = rect.right;
      }
      else
      {

         left = rect.left + min(m / 2,width(rect) / 2);
         right = rect.right - min(m / 2,width(rect) / 2);

      }

      ::rect rectBar(left,top,right,bottom);

      ::SelectObject(hdc,hbrushDark);

      HPEN hpenLite = ::CreatePen(PS_SOLID,1,RGB(255,255,250));

      ::SelectObject(hdc,hpenLite);

      ::Rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

      rectBar.deflate(2,2);

      int w = 284;

      ::SelectObject(hdc,hbrushLate);

      ::SelectObject(hdc,hpen);

      rectBar.right++;

      rectBar.bottom++;

      ::Rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

      int v = ::GetTickCount() * 484 / 1000;

      ::SelectObject(hdc,hbrushGren);

      int x = v % rectBar.width();

      ::rect rectBrick(left + x,rectBar.top,left + x + w,rectBar.bottom);
      ::rect rectDraw;

      if(rectDraw.intersect(rectBar,rectBrick))
      {

         ::Rectangle(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

      }

      rectBrick.offset(-rectBar.width(),0);

      if(rectDraw.intersect(rectBar,rectBrick))
      {

         ::Rectangle(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

      }

      rectBrick.offset(rectBar.width() * 2,0);

      if(rectDraw.intersect(rectBar,rectBrick))
      {

         ::Rectangle(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

      }

      string str(strEntryHallText);
      

      if(str.is_empty())
      {

         str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

      }

      ::SetBkMode(hdc,TRANSPARENT);

      ::SetTextColor(hdc,RGB(84,84,77));

      HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);

      HFONT hfontOld = (HFONT) ::SelectObject(hdc,hStockFont);

      ::TextOut(hdc,rectBar.left - 1,rectBar.bottom + 2,str,str.get_length());


      ::SelectObject(hdc,hfontOld);

      ::SelectObject(hdc,hpenOld);

      ::SelectObject(hdc,hbrushOld);

      ::DeleteObject(hbrushDark);
      ::DeleteObject(hbrushLite);
      ::DeleteObject(hbrushLate);
      ::DeleteObject(hbrushBack);
      ::DeleteObject(hbrushGren);
      ::DeleteObject(hpenLite);

   }


} // namespace hotplugin




