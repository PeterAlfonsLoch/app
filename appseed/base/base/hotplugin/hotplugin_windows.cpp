#include "framework.h"


namespace hotplugin
{


   void entry_hall_windows_on_paint(HDC hdc,const RECT & rect,const string & strEntryHallText)
   {


      // Create a hatched bit pattern.
      WORD HatchBits[8] ={0x55,0xAA,0x55,0xAA,0x55, 0xAA,0x55,0xAA};

      // Use the bit pattern to create a bitmap.
      HBITMAP hbm = ::CreateBitmap(8,8,1,1,HatchBits);


      HBRUSH hbrushBack = (HBRUSH) ::CreatePatternBrush(hbm);
      ::DeleteObject(hbm);
      HBRUSH hbrushDark = ::CreateSolidBrush(RGB(84,84,77));
      HBRUSH hbrushLate = ::CreateSolidBrush(RGB(84 + 49,84 + 49,77 + 42));
      HBRUSH hbrushLite = ::CreateSolidBrush(RGB(255,255,250));
      HBRUSH hbrushGren = ::CreateSolidBrush(RGB(77,184,123));

      HPEN hpen = (HPEN) ::GetStockObject(NULL_PEN);

      HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc,hbrushBack);

      HPEN hpenOld = (HPEN) ::SelectObject(hdc,hpen);

      //::Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);

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

         left = rect.left + MIN(m / 2,width(rect) / 2);
         right = rect.right - MIN(m / 2,width(rect) / 2);

      }

      ::rect rectBar(left,top,right,bottom);

      ::SelectObject(hdc,hbrushDark);

      //HPEN hpenLite = ::CreatePen(PS_SOLID,1,RGB(255,255,250));

      //::SelectObject(hdc,hpenLite);

      //::Rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

      //rectBar.deflate(2,2);

      int w = 284;

      ::SetTextColor(hdc,RGB(84,84,84));

      ::SetBkMode(hdc,TRANSPARENT);

      ::SelectObject(hdc,hbrushBack);

      ::SelectObject(hdc,hpen);

      //rectBar.right++;

      //rectBar.bottom++;

      int old = SetROP2(hdc,R2_MASKPEN);

      ::Rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

      SetROP2(hdc,old);

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

         //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

         str = "Opening ca2...";

      }

      ::SetBkMode(hdc,TRANSPARENT);

      ::SetTextColor(hdc,RGB(250,250,250));

      //HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);

      //HFONT hfontOld = (HFONT) ::SelectObject(hdc,hStockFont);

      //::TextOut(hdc,rectBar.left - 1,rectBar.bottom + 2,str,str.get_length());

      //rectBar.left++;
      //rectBar.top++;
      //rectBar.right--;
      //rectBar.bottom--;

      rectBar.left += 4;

      HFONT hFont = CreateFont(23,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
         CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,VARIABLE_PITCH,TEXT("Calibri"));
      HFONT hfontOld = (HFONT) ::SelectObject(hdc,hFont);

      ::DrawText(hdc,str,str.get_length(),&rectBar,DT_SINGLELINE| DT_VCENTER | DT_LEFT);

      ::DeleteObject(hFont);

      ::SelectObject(hdc,hfontOld);

      ::SelectObject(hdc,hpenOld);

      ::SelectObject(hdc,hbrushOld);

      ::DeleteObject(hbrushDark);
      ::DeleteObject(hbrushLite);
      ::DeleteObject(hbrushLate);
      ::DeleteObject(hbrushBack);
      ::DeleteObject(hbrushGren);
      //::DeleteObject(hpenLite);

   }


} // namespace hotplugin




