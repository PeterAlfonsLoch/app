
using namespace Gdiplus;


namespace hotplugin
{

   CLASS_DECL_AXIS void entry_hall_windows_on_paint(HDC hdc, const RECT & rect, const string & strEntryHallText)
   {

#if 0

      throw "TODO trying to get rid of GDI PLUS dependency on Windows, is it possible to use GDI with coached alpha extensions?";

#else

#ifndef METROWIN

      Graphics g(hdc);

      Graphics * pgraphics = &g;


      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if (height(rect) < h)
      {
         top = rect.top;
         bottom = rect.bottom;
      }
      else
      {
         top = rect.top + height(rect) / 2 - h / 2;
         bottom = rect.top + height(rect) / 2 + h / 2;
      }

      if (width(rect) < m)
      {
         left = rect.left;
         right = rect.right;
      }
      else
      {

         left = rect.left + MIN(m / 2, width(rect) / 2);
         right = rect.right - MIN(m / 2, width(rect) / 2);

      }

      ::rect rectBar(left, top, right, bottom);

      int w = 284;

      int v = ::GetTickCount() * 484 / 1000;

      int x = v % rectBar.width();

      ::rect rectBrick(left + x, rectBar.top, left + x + w, rectBar.bottom);
      ::rect rectDraw;

      int32_t cx = width(rect);
      int32_t cy = height(rect);
      pgraphics->SetCompositingMode(CompositingModeSourceOver);

      string str(strEntryHallText);

      if (str.is_empty())
      {

         //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

         str = "Opening...";

      }

      bool bStatic = false;

      if (::str::begins_eat(str, "***"))
      {

         bStatic = true;

      }

      SolidBrush brush(Color(184, 49, 49, 49));

      pgraphics->FillRectangle(&brush, rectBar.left, rectBar.top, width(rectBar), height(rectBar));

      if (!bStatic)
      {

         SolidBrush brushGren(Color(184, 77, 184, 123));

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->FillRectangle(&brushGren, rectDraw.left, rectDraw.top, width(rectDraw), height(rectDraw));

         }

         rectBrick.offset(-rectBar.width(), 0);

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->FillRectangle(&brushGren, rectDraw.left, rectDraw.top, width(rectDraw), height(rectDraw));

         }

         rectBrick.offset(rectBar.width() * 2, 0);

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->FillRectangle(&brushGren, rectDraw.left, rectDraw.top, width(rectDraw), height(rectDraw));

         }

      }

      Pen pen(Color(149, 149, 149, 142), 1.0f);

      pgraphics->DrawRectangle(&pen, rectBar.left, rectBar.top, width(rectBar), height(rectBar));

      Font f(L"Calibri", 18, 0, UnitPixel);

      //f->create_pixel_font("Calibri",18);

      rectBar.left += 4;

      rectBar.top += 5;

      pgraphics->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

      wstring wstr;

      wstr = str;

      SolidBrush b(Color(184, 255, 255, 255));

      pgraphics->DrawString(wstr, (INT)wstr.get_length(), &f, PointF((REAL)rectBar.left, (REAL)rectBar.top), &b);

#endif

#endif

   }





} // namespace hotplugin