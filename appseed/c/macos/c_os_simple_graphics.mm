//
//  c_os_os_simple_graphics.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#import "macos/c_os_graphics_mm.h"


/*
void set(XColor & color, COLORREF cr)
{
   color.pixel    = cr;
   color.red      = GetRValue(cr);
   color.green    = GetGValue(cr);
   color.blue     = GetBValue(cr);
}
*/










os_simple_graphics::os_simple_graphics()
{
   
   m_nsgc     = NULL;
   
   m_iScreen      = 0;
   
   m_bForeColor   = false;
   
   m_bBackColor   = false;
   
}


os_simple_graphics::~os_simple_graphics()
{
   
}


bool os_simple_graphics::set_alpha_mode(::ca::e_alpha_mode emode)
{
   
   if(emode == ::ca::alpha_mode_blend)
   {
      [m_nsgc setCompositingOperation: NSCompositeSourceOver];
   }
   else if(emode == ::ca::alpha_mode_set)
   {
      [m_nsgc setCompositingOperation: NSCompositeCopy];
   }
   
   return true;
   
}

bool os_simple_graphics::is_null()
{
   return m_nsgc != NULL;
}

bool os_simple_graphics::create(HDC hdc)
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

bool os_simple_graphics::create_from_bitmap(simple_bitmap & b)
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

/*

bool os_simple_graphics::detach_bitmap()
{
   
   if(m_iType != 0)
      destroy();
   
    if(m_hdc == NULL)
    return false;
    
    if(m_hbitmapOld == NULL)
    return false;
    
    if(m_iType != 3)
    return false;
    
    HBITMAP hbitmap = (HBITMAP) ::SelectObject(m_hdc, m_hbitmapOld);
    
    m_iType = 1;
   
   //   return hbitmap != NULL;
   return false;
   
}

*/

bool os_simple_graphics::from_entire_window(HWND hwnd)
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


bool os_simple_graphics::from_window(HWND hwnd)
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

bool os_simple_graphics::from_window_paint(HWND hwnd, LPRECT lprectPaint)
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

bool os_simple_graphics::reference_os_data(HDC hdc)
{
   
   m_iType = 5;
   
   //   m_hdc = hdc;
   
   return true;
   
}


bool os_simple_graphics::create()
{
   
   simple_graphics g;
   
   g.from_window(NULL);
   
   return create(g);
   
}



bool os_simple_graphics::create(simple_graphics & g)
{
   
   //   return create(g.m_hdc);
   return false;
   
}
 


bool os_simple_graphics::create_from_screen()
{
   
   return from_window(NULL);
   
}

bool os_simple_graphics::select(simple_font & font)
{
   
   m_font = font;
   
   return true;
   
}

bool os_simple_graphics::select(simple_brush & brush)
{
   
   m_brush = brush;
   
   return true;
   
}

bool os_simple_graphics::select(simple_pen & pen)
{
   
   m_pen = pen;
   
   return true;
   
}

bool os_simple_graphics::destroy()
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
      
      free_color(m_nscolorFore);
      
   }
   
   if(m_bBackColor)
   {
      
      free_color(m_nscolorBack);
      
   }
   
   //   m_hwnd   = NULL;
   
   // m_hdc    = NULL;
   
   m_iType  = 0;
   
   return bOk && bOkOldBitmap && bOkOldBrush && bOkOldFont && bOkOldPen;
   
}

bool os_simple_graphics::set_offset(int x, int y)
{
   
   [NSGraphicsContext setCurrentContext:m_nsgc];
   
   NSAffineTransform * xform = [NSAffineTransform transform];
   
   [xform translateXBy:x yBy:y];
   
   [xform set];
   
    [xform release];
   
   //POINT ptViewport;
   
   //   if(!SetViewportOrgEx(m_hdc, x, y, &ptViewport))
   //    return false;
   
   return true;
   
}

bool os_simple_graphics::offset(int x, int y)
{
   
   [NSGraphicsContext setCurrentContext:m_nsgc];
   
   NSAffineTransform * xform = [NSAffineTransform transform];
   
   [xform translateXBy:x yBy:y];
   
   [xform concat];
   
   [xform release];
   
   return true;
   
}


bool os_simple_graphics::bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop)
{
   
   //   return ::BitBlt(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, rop) != FALSE;
   return false;
   
   
}

bool os_simple_graphics::blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata)
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

SIZE os_simple_graphics::get_text_extent(const char * psz, int iLen)
{
   
   SIZE size;
   
   NSString * labelString = [[NSString alloc] initWithCString:psz encoding: NSUTF8StringEncoding];
   
   NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys: m_font.m_nsfont, NSFontAttributeName, nil];
   NSSize labelSize = [labelString sizeWithAttributes:attributes];
   
   size.cx = labelSize.width;
   size.cy = labelSize.height;
   
   return size;
   
}

void os_simple_graphics::set(simple_brush & brush)
{
   
   set_foreground(brush.m_cr);
   
}


void os_simple_graphics::set(simple_pen & pen)
{
   
   set_foreground(pen.m_cr);
   
}


NSColor  * os_simple_graphics::alloc_color(COLORREF cr)
{
   
   NSColor * color = [NSColor colorWithSRGBRed:GetRValue(cr) / 255.0f green:GetGValue(cr) / 255.0f blue:GetBValue(cr) / 255.0f alpha:GetAValue(cr)  / 255.0f ];
   
   return color;
   
}

bool os_simple_graphics::rectangle(LPCRECT lpcrect)
{
   
   NSRect rect;
   
   rect.origin.x = lpcrect->left;
   rect.origin.y = lpcrect->top;
   rect.size.width = lpcrect->right - lpcrect->left;
   rect.size.height = lpcrect->bottom - lpcrect->top;
   
   
   
   if(m_brush.m_iStock != NULL_BRUSH)
   {
      
      set(m_brush);
      
      NSRectFill(rect);
      
   }
   
   if(m_pen.m_iStock != NULL_PEN)
   {
      
      set(m_pen);
      
      NSFrameRect(rect);
      
   }
   
   return true;
   
}


bool os_simple_graphics::free_color(NSColor * nscolor)
{

   [nscolor release];
   
   return true;
   
   
}

void os_simple_graphics::set_foreground(COLORREF cr)
{
   
   if(m_bForeColor)
   {
      
      free_color(m_nscolorFore);
      
      m_bForeColor = false;
      
   }
   
   m_nscolorFore = alloc_color(cr);
   
   m_bForeColor = true;
   
   [NSGraphicsContext setCurrentContext:m_nsgc];
   
   [m_nscolorFore set];
   
}

void os_simple_graphics::set_background(COLORREF cr)
{
   
   if(m_bBackColor)
   {
      
      free_color(m_nscolorBack);
      
      m_bBackColor = false;
      
   }
   
   m_nscolorBack = alloc_color(cr);
   
   m_bBackColor = true;
   
   [NSGraphicsContext setCurrentContext:m_nsgc];
   
   [m_nscolorBack setFill];
   
}

bool os_simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{
   
   set(brush);
   
   NSRect rect;
   
   rect.origin.x = lpcrect->left;
   rect.origin.y = lpcrect->top;
   rect.size.width = lpcrect->right - lpcrect->left;
   rect.size.height = lpcrect->bottom - lpcrect->top;
   
   NSBezierPath * path = [NSBezierPath bezierPath];
   
   [path appendBezierPathWithRect:rect];
   
   [NSGraphicsContext setCurrentContext:m_nsgc];
   
   [path fill];
   
   [path release];
   
   return true;
   
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

/*

bool os_simple_graphics::set_text_color(COLORREF cr)
{
   
   m_crTextColor = cr;
   
   return true;
   
   
}
 */

/*

bool os_simple_graphics::alpha_blend(int x, int y, int cx, int cy, os_simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf)
{
   
   NSRect rect;
   
   rect.origin.x = x;
   rect.origin.y = y;
   rect.size.width = cx;
   rect.size.height = cy;
   
   NSRect rect1;
                  
   rect.origin.x = x1;
   rect.origin.y = y1;
   rect.size.width = cx1;
   rect.size.height = cy1;
   
   [NSGraphicsContext setCurrentContext: m_nsgc];
   
   
   
   [gSrc.m_bitmap.m_nsimage drawInRect:rect fromRect: rect1 operation:NSCompositeSourceOver fraction:1.0];
   
   //return ::AlphaBlend(m_hdc, x, y, cx, cy, gSrc.m_hdc, x1, y1, cx1, cy1, bf) != FALSE;
   
   return false;
   
}
 
 */

void os_simple_graphics::fill_solid_rect(LPCRECT lpRect, COLORREF cr)
{
   
   simple_brush brush;
   
   brush.create_solid((simple_graphics &)*this, cr);
   
   fill_rect(lpRect, brush);
   
}


bool os_simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{
   
   if(!m_font.m_bUpdated)
   {
      
      if(m_font.update())
         return false;
      
   }
   
   NSColor * colorFore = alloc_color(m_crTextColor);
   
   NSColor * colorBack = alloc_color(0);
   
   NSDictionary *textAttributes = [NSDictionary dictionaryWithObjectsAndKeys:
                                   m_font.m_nsfont, NSFontAttributeName,
                                   colorFore, NSForegroundColorAttributeName,
                                   colorBack, NSBackgroundColorAttributeName, nil];

   NSString * labelString = [[NSString alloc] initWithCString:pszUtf8 encoding: NSUTF8StringEncoding];

   [labelString drawAtPoint:NSMakePoint(x, y) withAttributes:textAttributes];
   
   [labelString release];
      
   free_color(colorBack);
      
   free_color(colorFore);
   
   return true;
   
}



bool os_simple_graphics::fill_polygon(POINT * p, int iCount, ::ca::e_fill_mode)
{
   
   if(m_brush.m_estyle == simple_brush::style_stock && m_brush.m_iStock == NULL_BRUSH)
      return true;
   
   
   NSBezierPath * path = [NSBezierPath bezierPath];
   
   NSPointArray pa = new NSPoint[iCount];
   
   for(int i = 0; i < iCount; i++)
   {
      pa[i] = NSMakePoint(p[i].x, p[i].y);
   }
                                            
   [path appendBezierPathWithPoints:pa count: iCount];
   
   [NSGraphicsContext setCurrentContext:m_nsgc];
   
   [path fill];
   
   [path release];
   
   delete pa;
   
   return true;
   
   
}