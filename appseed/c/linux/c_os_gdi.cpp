#include "framework.h"



#include "linux/c_os_cross_win_gdi_internal.h"



inline void set(XColor & color, COLORREF cr)
{
   color.pixel    = cr;
   color.red      = GetRValue(cr);
   color.green    = GetGValue(cr);
   color.blue     = GetBValue(cr);
}











simple_graphics::simple_graphics()
{

   m_pdisplay     = NULL;

   m_iScreen      = 0;

   m_bForeColor   = false;

   m_bBackColor   = false;

}


simple_graphics::~simple_graphics()
{

}

bool simple_graphics::create(HDC hdc)
{

   if(m_iType != 0)
      destroy();

//   m_hdc = ::CreateCompatibleDC(hdc);

   //if(m_hdc == NULL)
     // return false;

  // ::ReleaseDC(NULL, hdc);

   m_iType = 1;

   return true;

}

bool simple_graphics::create_from_bitmap(simple_bitmap & b)
{

   if(m_iType != 0)
      destroy();

/*   m_hdc = ::CreateCompatibleDC(NULL);

   if(m_hdc == NULL)
      return false;

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, b.m_hbitmap);

   if(m_hbitmapOld == NULL)
   {

      ::DeleteDC(m_hdc);

      m_hdc = NULL;

      return false;

   }*/

   m_iType = 3;

   return true;

}

bool simple_graphics::detach_bitmap()
{

   if(m_iType != 0)
      destroy();

/*   if(m_hdc == NULL)
      return false;

   if(m_hbitmapOld == NULL)
      return false;

   if(m_iType != 3)
      return false;

   HBITMAP hbitmap = (HBITMAP) ::SelectObject(m_hdc, m_hbitmapOld);

   m_iType = 1;*/

//   return hbitmap != NULL;
   return false;

}

bool simple_graphics::from_entire_window(HWND hwnd)
{

   if(m_iType != 0)
      destroy();

/*   m_hdc = ::GetWindowDC(hwnd);

   if(m_hdc == NULL)
      return false;

   m_hwnd = hwnd;*/

   m_iType = 2;

   return true;

}


bool simple_graphics::from_window(HWND hwnd)
{

   if(m_iType != 0)
      destroy();

/*   m_hdc = ::GetDC(hwnd);

   if(m_hdc == NULL)
      return false;

   m_hwnd = hwnd;*/

   m_iType = 2;

   return true;

}

bool simple_graphics::from_window_paint(HWND hwnd, LPRECT lprectPaint)
{

   if(m_iType != 0)
      destroy();

/*    m_hdc = BeginPaint(hwnd, &m_ps);

    if(m_hdc == NULL)
       return false;

    m_hwnd = hwnd;

    if(lprectPaint != NULL)
    {

       *lprectPaint = m_ps.rcPaint;

    }*/

    m_iType = 4;

    return true;

}

bool simple_graphics::reference_os_data(HDC hdc)
{

   m_iType = 5;

//   m_hdc = hdc;

   return true;

}

XFontStruct * simple_graphics::get_font(simple_font & font)
{

   vsstring strName;

   int i = 0;

   XFontStruct * pfont = NULL;

   while(true)
   {

      strName = font.get_name(i);

      if(i >= 32 || strName.is_empty())
         break;

      pfont = XLoadQueryFont(m_pdisplay, strName);

      if(pfont != NULL)
         break;

   }

   return pfont;

}


bool simple_graphics::create()
{

   simple_graphics g;

   g.from_window(NULL);

   return create(g);

}

bool simple_graphics::create(simple_graphics & g)
{

//   return create(g.m_hdc);
return false;

}

bool simple_graphics::create_from_screen()
{

   return from_window(NULL);

}

bool simple_graphics::select(simple_font & font)
{

   m_font = font;

   return true;

}

bool simple_graphics::select(simple_brush & brush)
{

   m_brush = brush;

   return true;

}

bool simple_graphics::select(simple_pen & pen)
{

   m_pen = pen;

   return true;

}

bool simple_graphics::destroy()
{

   bool bOk = true;

   bool bOkOldBitmap = true;

   bool bOkOldPen = true;

   bool bOkOldBrush = true;

   bool bOkOldFont = true;



/*   if(m_hbitmapOld != NULL)
   {

      bOkOldBitmap   = ::SelectObject(m_hdc, m_hbitmapOld) != NULL;

      m_hbitmapOld   = NULL;

   }

   if(m_hbrushOld != NULL)
   {

      bOkOldBrush    = ::SelectObject(m_hdc, m_hbrushOld) != NULL;

      m_hbrushOld    = NULL;

   }

   if(m_hpenOld != NULL)
   {

      bOkOldPen      = ::SelectObject(m_hdc, m_hpenOld) != NULL;

      m_hpenOld      = NULL;
   }

   if(m_hfontOld != NULL)
   {

      bOkOldFont     = ::SelectObject(m_hdc, m_hfontOld) != NULL;

      m_hfontOld     = NULL;

   }*/


   if(m_iType == 1)
   {

//      bOk = ::DeleteDC(m_hdc) != FALSE;

   }
   else if(m_iType == 2)
   {

  //    bOk = ::ReleaseDC(m_hwnd, m_hdc) != FALSE;

   }
   else if(m_iType == 3)
   {

    //  bOk = ::DeleteDC(m_hdc) != FALSE;

   }
   else if(m_iType == 4)
   {

      //bOk = EndPaint(m_hwnd, &m_ps) != FALSE;

   }

   if(m_bForeColor)
   {

      free_color(m_uiForeColor);

   }

   if(m_bBackColor)
   {

      free_color(m_uiBackColor);

   }

//   m_hwnd   = NULL;

  // m_hdc    = NULL;

   m_iType  = 0;

   return bOk && bOkOldBitmap && bOkOldBrush && bOkOldFont && bOkOldPen;

}

bool simple_graphics::set_offset(int x, int y)
{

   POINT ptViewport;

//   if(!SetViewportOrgEx(m_hdc, x, y, &ptViewport))
  //    return false;

   return true;

}

bool simple_graphics::offset(int x, int y)
{

   POINT ptViewport;

//   if(!OffsetViewportOrgEx(m_hdc, x, y, &ptViewport))
  //    return false;

   return true;

}


bool simple_graphics::bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop)
{

//   return ::BitBlt(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, rop) != FALSE;
return false;


}

bool simple_graphics::blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata)
{

   /*try
   {

      Gdiplus::Bitmap b(cx, cy, cx *4 , PixelFormat32bppARGB, (BYTE *) pdata);

      Gdiplus::Graphics * pg = new Gdiplus::Graphics(m_hdc);

      pg->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      pg->SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

      pg->DrawImage(&b, x, y, 0, 0, cx, cy, Gdiplus::UnitPixel);

      pg->Flush(Gdiplus::FlushIntentionSync);

      delete pg;

      ::GdiFlush();

      return true;

   }
   catch(...)
   {

   }
*/
   return false;

}

SIZE simple_graphics::get_text_extent(const char * psz, int iLen)
{

   SIZE size;

   size.cx = Xutf8TextEscapement(m_font.m_fontset, psz, iLen);

	size.cy = m_font.m_iAscent + m_font.m_iDescent;

   return size;

}

void simple_graphics::select_brush(simple_brush & brush)
{

   set_foreground(brush.m_cr);

}


void simple_graphics::select_brush()
{

   select_brush(m_brush);

}

void simple_graphics::select_pen(simple_pen & pen)
{

   set_foreground(pen.m_cr);

}


void simple_graphics::select_pen()
{

   select_pen(m_pen);

}

long unsigned int simple_graphics::alloc_color(COLORREF cr)
{

   XColor color;

   set(color, cr);

   XAllocColor(m_pdisplay, m_colormap, &color);

   return color.pixel;

}

bool simple_graphics::rectangle(LPCRECT lpcrect)
{

   bool bOk1 = true;

   if(m_brush.m_iStock != NULL_BRUSH)
   {

      select_brush();

      bOk1 = XFillRectangle(m_pdisplay, m_d, m_gc, lpcrect->left, lpcrect->top, lpcrect->right - lpcrect->left, lpcrect->bottom - lpcrect->top) != 0;

   }

   bool bOk2 = true;

   if(m_pen.m_iStock != NULL_PEN)
   {

      select_pen();

      bOk2 = XDrawRectangle(m_pdisplay, m_d, m_gc, lpcrect->left, lpcrect->top, lpcrect->right - lpcrect->left, lpcrect->bottom - lpcrect->top) != 0;

   }

   return bOk1 && bOk2;

}


bool simple_graphics::free_color(long unsigned int pixel)
{

   if(!XFreeColors(m_pdisplay, m_colormap, &pixel, 1, 0))
      return false;

   return true;


}

void simple_graphics::set_foreground(COLORREF cr)
{

   if(m_bForeColor)
   {

      free_color(m_uiForeColor);

      m_bForeColor = false;

   }

   m_uiForeColor = alloc_color(cr);

   m_bForeColor = true;

   XSetForeground(m_pdisplay, m_gc, m_uiForeColor);

}

void simple_graphics::set_background(COLORREF cr)
{

   if(m_bBackColor)
   {

      free_color(m_uiBackColor);

      m_bBackColor = false;

   }

   m_uiBackColor = alloc_color(cr);

   m_bBackColor = true;

   XSetBackground(m_pdisplay, m_gc, m_uiBackColor);

}

bool simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{

   select_brush(brush);

   return XFillRectangle(m_pdisplay, m_d, m_gc, lpcrect->left, lpcrect->top, lpcrect->right - lpcrect->left, lpcrect->bottom - lpcrect->top) != 0;

}


/*XColor green_col;
Colormap colormap;
char green[] = "#00FF00";

Assign a colormap to the colormap variable with the DefaultColormap function. The DefaultColormap function takes two arguments. The first argument is the display connection. The second argument is the screen number.


colormap = DefaultColormap(dis, 0);

Create the graphics context using XCreateGC and put the GC information in green_gc


green_gc = XCreateGC(dis, win, 0, 0);

Parse the color 00FF00 and allocate the color for later use.*/

/*

XParseColor(dis, colormap, green, &green_col);
XAllocColor(dis, colormap, &green_col);

Now that the color has been allocated set the foreground of the graphics context with XSetForeground. The last argument to XSetForeground is the pixel value of the color allocated.


XSetForeground(dis, green_gc, green_col.pixel);

Now the program can draw using the foreground color set for green_gc.


case Expose:
XDrawRectangle(dis, win, green_gc, 1, 1, 497, 497);
XDrawRectangle(dis, win, green_gc, 50, 50, 398, 398);
break;



   return ::FillRect(m_hdc, lpcrect, brush.m_hbrush) != FALSE;

}
*/

bool simple_graphics::set_text_color(COLORREF cr)
{

   m_crTextColor = cr;

   return true;


}

bool simple_graphics::alpha_blend(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf)
{

   //return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;

   return false;

}

void simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF cr)
{

   simple_brush brush;

   brush.create_solid(cr);

   fill_rect(lpRect, brush);

}



simple_brush::simple_brush()
{

   m_iStock = -1;

   m_iStyle = FillSolid;

   m_cr = 0;

}

simple_brush::~simple_brush()
{


}

bool simple_brush::create_solid(COLORREF cr)
{

   m_iStock = -1;

   m_iStyle = FillSolid;

   m_cr = cr;

   return true;

}


bool simple_brush::from_stock(int iId)
{

   if(iId != NULL_BRUSH)
      return false;

   m_iStock = iId;

   return true;

}



bool simple_brush::destroy()
{

   m_iStock = -1;

   m_iStyle = FillSolid;

   m_cr = 0;

}




simple_bitmap::simple_bitmap()
{

   m_pixmap = 0;

}

simple_bitmap::~simple_bitmap()
{

   if(m_pixmap != 0)
   {

      destroy();

   }

}

bool simple_bitmap::create(int cx, int cy, simple_graphics & g,  COLORREF ** ppdata)
{

   /*BITMAPINFO m_Info;

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=cx;
	m_Info.bmiHeader.biHeight=cy;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32;
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=cx*cy*4;*/

	m_mem.allocate(cx * cy * 4);

	memset(m_mem.get_data(), 0, m_mem.get_size());

	if(!create_from_data(cx, cy, (COLORREF *) m_mem.get_data(), g))
	{

      m_mem.allocate(0);

      return false;

	}

	if(ppdata != NULL)
	{

      *ppdata = (COLORREF *) m_mem.get_data();

	}

   return true;

}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g)
{

   m_pdisplay = g.m_pdisplay;

   m_pixmap = XCreatePixmapFromBitmapData(g.m_pdisplay, g.m_d, (char *) pdata, cx, cy, BlackPixel(g.m_pdisplay, g.m_iScreen), WhitePixel(g.m_pdisplay, g.m_iScreen), 32);

   if(m_pixmap == 0)
   {

      m_pdisplay = NULL;

      return false;

   }


   return true;

}



bool simple_bitmap::destroy()
{

   if(m_pixmap == NULL)
      return true;


   bool bOk = ::XFreePixmap(m_pdisplay, m_pixmap) != FALSE;

   m_pixmap = 0;

   if(!bOk)
      return false;

   return true;

}






simple_pen::simple_pen()
{

   m_iStock = -1;
   m_iStyle = LineSolid;
   m_iWidth = 0;
   m_cr = 0;

}

simple_pen::~simple_pen()
{

}

bool simple_pen::create_solid(int iWidth, COLORREF cr)
{

   m_iStock = -1;

   m_iStyle    = LineSolid;

   m_iWidth    = iWidth;

   m_cr = cr;


   return TRUE;

}

bool simple_pen::from_stock(int iId)
{

   if(iId != NULL_PEN)
      return false;

   m_iStock = iId;

   return true;


}

bool simple_pen::destroy()
{

   m_iStock = -1;
   m_iStyle = LineSolid;
   m_iWidth = 0;
   m_cr = 0;


   return true;

}



simple_pen & simple_pen::operator = (const simple_pen & pen)
{

   m_iStock = pen.m_iStock;

   m_iStyle    = pen.m_iStyle;

   m_iWidth    = pen.m_iWidth;

   m_cr  = pen.m_cr;

   return *this;

}


bool simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{

   if(!m_font.m_bUpdated)
   {

      if(m_font.update(m_pdisplay))
         return false;

   }

   Xutf8DrawString(m_pdisplay, m_d, m_font.m_fontset, m_gc, x, y, pszUtf8, iSize);

   return true;

}



simple_font::simple_font()
{

   m_strFamily    = "helvetica";
   m_iWeight      = 400;
   m_iSize        = 10;
   m_bUpdated     = false;
   m_fontset      = 0;

}

simple_font::~simple_font()
{

   /*if(m_hfont != NULL)
   {

      destroy();

   }*/

}

/*bool simple_font::create_indirect(LPLOGFONT  lplf)
{

   m_hfont = ::CreateFontIndirect(lplf);

   if(m_hfont == NULL)
      return false;


   return true;

}
*/

vsstring simple_font::get_weight(int iWeight)
{

   if(iWeight <= 400)
   {
      return "medium";
   }
   else
   {
      return "bold";
   }

}

vsstring simple_font::get_name(int i)
{

   if(i == 0)
   {

      vsstring strWeight = get_weight(m_iWeight);

      vsstring strSize = itoa_dup(m_iSize);

      return "-*-" + m_strFamily +"-" + strWeight + "-r-*-*-" + strSize + "-*-72-72-*-*";
   }
   if(m_iWeight > 400)
   {

      if(i == 1)
      {

         vsstring strSize = itoa_dup(m_iSize);

         return "-*-" + m_strFamily +"-medium-r-*-*-" + strSize + "-*-72-72-*-*";

      }
      else if(i == 2)
      {

         vsstring strWeight = get_weight(m_iWeight);

         return "-*-" + m_strFamily +"-" + strWeight + "-r-*-*-*-*-72-72-*-*";
      }
      else if(i == 3)
      {

         return "-*-" + m_strFamily +"-*-r-*-*-*-*-72-72-*-*";

      }
      else
      {

         i -= 3;

      }

   }
   if(m_strFamily != "helvetica")
   {

      if(i == 1)
      {

         vsstring strSize = itoa_dup(m_iSize);

         return "-*-helvetica-medium-r-*-*-" + strSize + "-*-72-72-*-*";

      }
      else if(i == 2)
      {

         vsstring strWeight = get_weight(m_iWeight);

         return "-*-helvetica-" + strWeight + "-r-*-*-*-*-72-72-*-*";
      }
      else if(i == 3)
      {

         return "-*-helvetica-*-r-*-*-*-*-72-72-*-*";

      }
      else
      {

         i -= 3;

      }
   }

   return "fixed";

}

bool simple_font::update(Display * pdisplay)
{

   if(m_bUpdated)
   {

      m_bUpdated = false;

   }

	int nmissing;
	char **missing;
	char *def_string;


   vsstring strName;

   int j = 0;

   while(true)
   {

      strName = get_name(j);

      if(j >= 32 || strName.is_empty())
         return false;

      m_fontset = XCreateFontSet(pdisplay, m_strFamily, &missing, &nmissing, &def_string);

      if(m_fontset != 0)
         break;


   }

   m_bUpdated = true;

   m_pdisplay = pdisplay;

	XFreeStringList(missing);

	XFontStruct ** fonts;

	char ** font_names;

	int nfonts = XFontsOfFontSet(m_fontset, &fonts, &font_names);

	m_iAscent = 0;

	m_iDescent = 0;

	for(int j = 0; j < nfonts; j++)
	{

		if(fonts[j]->ascent > m_iAscent)
         m_iAscent = fonts[j]->ascent;

		if(fonts[j]->descent > m_iDescent)
         m_iDescent = fonts[j]->descent;

	}

   return true;
}

bool simple_font::destroy()
{

   if(m_bUpdated)
   {

      XFreeFontSet(m_pdisplay, m_fontset);

      m_fontset = 0;

      m_pdisplay = NULL;

   }

   m_strFamily    = "";

   m_iWeight      = 400;

   m_iSize        = 0;

   return true;

}


bool simple_font::create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g)
{

   return create_point_bold(nPointSize, lpszFaceName, FALSE, g);

}

bool simple_font::create_point_bold(int nPointSize, const char * lpszFaceName, int iBold, simple_graphics & g)
{

   LOGFONT logFont;

   memset_dup(&logFont, 0, sizeof(LOGFONT));

   logFont.lfCharSet = DEFAULT_CHARSET;

   if(g.m_pdisplay == NULL)
   {

      g.create();

   }


   m_strFamily = lpszFaceName;

   m_iSize = nPointSize;

   m_iWeight = iBold != FALSE ? 800 : 400;

   return update(g.m_pdisplay);

}
