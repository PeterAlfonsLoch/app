//
//  c_os_os_simple_graphics.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#import "macos/ca_os_graphics_mm.h"


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
   
   m_pdc     = NULL;
   
   m_iScreen      = 0;
   
   m_bForeColor   = false;
   
   m_bBackColor   = false;
   
   m_bGotOriginalClipPath = false;
   
}


os_simple_graphics::~os_simple_graphics()
{
   
}


bool os_simple_graphics::set_alpha_mode(::draw2d::e_alpha_mode emode)
{
   
   try
   {
      
      if(m_pdc == NULL)
         return false;
      
      m_ealphamode = emode;
      
      if(m_ealphamode == ::draw2d::alpha_mode_blend)
      {
         
         CGContextSetBlendMode(m_pdc, kCGBlendModeNormal);
         
      }
      else if(m_ealphamode == ::draw2d::alpha_mode_set)
      {
         
         CGContextSetBlendMode(m_pdc, kCGBlendModeCopy);
         
      }
      
   }
   catch(...)
   {
      
   }
   
   
   return true;
   
}

bool os_simple_graphics::is_null()
{
   return m_pdc != NULL;
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

bool os_simple_graphics::from_entire_window(oswindow hwnd)
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


bool os_simple_graphics::from_window(oswindow hwnd)
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

bool os_simple_graphics::from_window_paint(oswindow hwnd, LPRECT lprectPaint)
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
   
   //   m_hwnd   = NULL;
   
   // m_hdc    = NULL;
   
   m_iType  = 0;
   
   return bOk && bOkOldBitmap && bOkOldBrush && bOkOldFont && bOkOldPen;
   
}

bool os_simple_graphics::set_offset(int x, int y)
{
   
   CGAffineTransform affine = m_affine;
   
   //      CGAffineTransform affineInvert = CGAffineTransformInvert(affine);
   
   CGAffineTransform affineABCD = CGContextGetCTM(m_pdc);
   
   //      CGAffineTransform affineBCD = CGAffineTransformConcat(affineInvert, affineABCD);
   
   CGAffineTransform affineABCDInvert = CGAffineTransformInvert(affineABCD);
   
   CGContextConcatCTM(m_pdc, affineABCDInvert);
   
   //      CGAffineTransform affineQ1 = CGContextGetCTM(m_pdc);
   
   CGContextConcatCTM(m_pdc, affine);
   
   //      CGAffineTransform affineQ2 = CGContextGetCTM(m_pdc);
   
   CGContextTranslateCTM(m_pdc, x, y);
   
   //      CGAffineTransform affineQ3 = CGContextGetCTM(m_pdc);
   
   //      CGContextConcatCTM(m_pdc, affineBCD);
   
   //      CGPoint pt;
   
   //      pt.x = 0.f;
   
   //      pt.y = 0.f;
   
   //      CGPointApplyAffineTransform(pt, affineBCD);
   
   //      CGContextTranslateCTM(m_pdc, -pt.x, -pt.y);
   
   return true;
   
   
}

bool os_simple_graphics::offset(int x, int y)
{
   
   CGContextTranslateCTM(m_pdc, x, y);
   
   return true;
   
}

bool os_simple_graphics::bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop)
{
   
   try
   {
      
      CGImageRef image = CGBitmapContextCreateImage((CGContextRef) gSrc.m_pdc);
      
      if(image == NULL)
      {
         
         return false;
         
      }
      
      CGRect rect;
      
      rect.origin.x = x;
      rect.origin.y = y;
      rect.size.width = min(cx, CGImageGetWidth(image) - x1);
      rect.size.height = min(cy, CGImageGetHeight(image) - y1);
      
      CGRect rectSub;
      
      rectSub.origin.x = x1;
      rectSub.origin.y = y1;
      rectSub.size.width = rect.size.width;
      rectSub.size.height = rect.size.height;
      
      CGImageRef imageSub = CGImageCreateWithImageInRect(image, rectSub);
      
      if(imageSub != NULL)
      {
         
         CGContextDrawImage(m_pdc, rect, imageSub);
         
         CGImageRelease(imageSub);
         
      }
      
      CGImageRelease(image);
      
      
      
      //
      //         cairo_pattern_t * ppattern = cairo_get_source((cairo_t *) pgraphicsSrc->get_os_data());
      //
      //         if(ppattern == NULL)
      //            return false;
      //
      //         cairo_set_source(m_pdc, ppattern);
      //
      //         cairo_paint(m_pdc);
      
      return true;
      
   }
   catch(...)
   {
      
      return false;
      
   }
   
   
   
   
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
   
   CGFloat ascent, descent, leading, width;
   
   SIZE size;
   
   const_cast < os_simple_graphics * > (this)->internal_show_text(0, 0, psz, (int32_t) iLen, kCGTextInvisible, false, &ascent, &descent, &leading, &width);
   
   //      CGPoint pt = CGContextGetTextPosition(m_pdc);
   
   //      size.cx = pt.x;
   
   //      size.cy = pt.y;
   
   size.cy = ascent + descent + leading;
   
   //      double dRate = m_spfont->m_dFontSize / size.cy;
   
   size.cx = width;
   
   //    size.cy *= dRate;
   
   //if(size.cy < m_spfont->m_dFontSize)
   //   size.cy = m_spfont->m_dFontSize;
   
   return size;
   
   
}


void os_simple_graphics::internal_set_fill_color(COLORREF cr)
{
   
   CGContextSetRGBFillColor(m_pdc, GetRValue(cr) / 255.0f, GetGValue(cr) / 255.0f, GetBValue(cr) / 255.0f, GetAValue(cr) / 255.0f);
   
}


void os_simple_graphics::internal_set_stroke_color(COLORREF cr)
{
   
   CGContextSetRGBStrokeColor(m_pdc, GetRValue(cr) / 255.0f, GetGValue(cr) / 255.0f, GetBValue(cr) / 255.0f, GetAValue(cr) / 255.0f);
   
}



bool os_simple_graphics::rectangle(LPCRECT lpcrect)
{
   
   if(m_brush.m_etype != ::simple_brush::type_null)
   {

      fill_rect(lpcrect, m_brush);
      
   }
   
   if(m_pen.m_etype != ::simple_pen::type_null)
   {

      draw_rect(lpcrect, m_pen);
      
   }
   
   return true;
   
}







bool os_simple_graphics::fill_rect(LPCRECT lpcrect, simple_brush & brush)
{
  
   CGRect rect;
   
   rect.origin.x = lpcrect->left;
   rect.origin.y = lpcrect->top;
   rect.size.width = lpcrect->right - lpcrect->left;
   rect.size.height = lpcrect->bottom - lpcrect->top;
   
   internal_set_fill_color(brush.m_cr);
   
   ::CGContextFillRect(m_pdc, rect);
   
   return true;
   
}



void os_simple_graphics::fill_solid_rect(LPCRECT lpcrect, COLORREF cr)
{
   
   CGRect rect;
   
   rect.origin.x = lpcrect->left;
   rect.origin.y = lpcrect->top;
   rect.size.width = lpcrect->right - lpcrect->left;
   rect.size.height = lpcrect->bottom - lpcrect->top;
   
   internal_set_fill_color(cr);
   
   ::CGContextFillRect(m_pdc, rect);
   
}


bool os_simple_graphics::text_out(int x, int y, const char * pszUtf8, int iSize)
{
   
   return internal_show_text(x, y, pszUtf8, iSize, kCGTextFill);
   
}



bool os_simple_graphics::fill_polygon(POINT * pa, int nCount, ::draw2d::e_fill_mode)
{
   
   if(m_brush.m_etype == simple_brush::type_null)
      return true;
   
   
   if(nCount <= 0)
      return TRUE;
   
   CGContextBeginPath(m_pdc);
   
   CGContextMoveToPoint(m_pdc, pa[0].x, pa[0].y);
   
   for(int32_t i = 1; i < nCount; i++)
   {
      
      CGContextAddLineToPoint(m_pdc, pa[i].x, pa[i].y);
      
   }
   
   CGContextClosePath(m_pdc);
   
   fill();
   
   return true;
   
   
}


bool os_simple_graphics::draw_polygon(POINT * pa, int nCount, ::draw2d::e_fill_mode)
{
   
   if(m_brush.m_etype == simple_brush::type_null)
      return true;
   
   
   if(nCount <= 0)
      return TRUE;
   
   CGContextBeginPath(m_pdc);
   
   CGContextMoveToPoint(m_pdc, pa[0].x, pa[0].y);
   
   for(int32_t i = 1; i < nCount; i++)
   {
      
      CGContextAddLineToPoint(m_pdc, pa[i].x, pa[i].y);
      
   }
   
   CGContextClosePath(m_pdc);
   
   draw();
   
   return true;
   
   
}


void os_simple_graphics::defer_get_original_clip_path()
{
   
   if(!m_bGotOriginalClipPath)
   {
      
      m_rectOriginalClip = CGContextGetClipBoundingBox(m_pdc);
      
      m_bGotOriginalClipPath = true;
      
   }
   
}

// On 30 Oct, 2012, at 6:47 AM, Graham Cox <graham....@bigpond.com> wrote:
// http://www.mail-archive.com/cocoa-dev@lists.apple.com/msg83889.html
bool os_simple_graphics::exclude_clip(simple_path & path)
{

/*   [NSGraphicsContext setCurrentContext:m_pdc];
   
   NSBezierPath * cp = [NSBezierPath bezierPathWithRect: m_rectOriginalClip];
   
   [cp appendBezierPath: path.m_nspath];
   
   [cp setWindingRule:NSEvenOddWindingRule];
   
   [cp addClip];
  */
   return true;

}



bool os_simple_graphics::replace_clip(simple_path &path)
{
   
/*
 [NSGraphicsContext setCurrentContext:m_pdc];
   
   [path.m_nspath setClip];
 */
   return true;
   
}


bool os_simple_graphics::replace_clip(const RECT & r)
{
   
   
   return true;
   
}


bool os_simple_graphics::draw_line(int x1, int y1, int x2, int y2, simple_pen &pen)
{
   
   CGContextBeginPath(m_pdc);
   
   CGContextMoveToPoint(m_pdc, x1, y1);
   
   CGContextAddLineToPoint(m_pdc, x2, y2);
   
   draw();
   
   return true;
   
}


bool os_simple_graphics::draw_path(simple_path & path, simple_pen &pen)
{
   
   CGContextBeginPath(m_pdc);
   
   CGContextAddPath(m_pdc, path.m_path);
   
   draw(&pen);
   
   return true;
   
}


bool os_simple_graphics::draw_rect(LPCRECT lpcrect, simple_pen &pen)
{
   
   simple_path path;
   
   path.add_rect(*lpcrect);
   
   draw(&pen);
   
   return true;
   
}

bool os_simple_graphics::fill_path(simple_path & path, simple_brush & brush)
{
   
   CGContextBeginPath(m_pdc);
   
   CGContextAddPath(m_pdc, path.m_path);
   
   fill(&brush);
   
   return true;
   
}



bool os_simple_graphics::internal_show_text(double x, double y, const char * lpszString, int32_t nCount, CGTextDrawingMode emode, bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth)
{
   
   string str(lpszString, nCount);
   
   CFStringRef string = CFStringCreateWithCString(NULL, str, kCFStringEncodingUTF8);
   
   if(string == NULL)
      return false;
   
   CGContextBeginPath(m_pdc);
   
   ::string strFontName;
   
   if(m_font.m_strFontFamilyName == "Lucida Sans Unicode")
   {
      
      strFontName = "Helvetica";
      
   }
   else
   {
      
      strFontName = "Helvetica";
      
   }
   
   CFStringRef fontName = CFStringCreateWithCString(NULL, strFontName, kCFStringEncodingUTF8);
   
   double dFontSize;
   
   dFontSize = m_font.m_dFontSize;
   
   CTFontDescriptorRef fontD = CTFontDescriptorCreateWithNameAndSize(fontName, 0.f);
   
   CTFontRef font =  CTFontCreateWithFontDescriptor(fontD, dFontSize, NULL);
   
   CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
   
   CGColorRef cr = NULL;
   
   if(emode != kCGTextInvisible && bDraw)
   {
      
      CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
      
      CGFloat components[4];
      
      COLORREF crText = m_brush.m_cr;
      
      components[0] = GetRValue(crText) / 255.f;
      
      components[1] = GetGValue(crText) / 255.f;
      
      components[2] = GetBValue(crText) / 255.f;
      
      components[3] = GetAValue(crText) / 255.f;
      
      cr = CGColorCreate(rgbColorSpace, components);
      
      CGColorSpaceRelease(rgbColorSpace);
      
   }
   
   CFTypeRef values[] = { font, cr };
   
   CFDictionaryRef attributes =
   CFDictionaryCreate(
                      kCFAllocatorDefault,
                      (const void**) &keys,
                      (const void**)&values,
                      (emode != kCGTextInvisible && bDraw) ? 2 : 1,
                      &kCFTypeDictionaryKeyCallBacks,
                      &kCFTypeDictionaryValueCallBacks);
   
   
   CFAttributedStringRef attrString =
   
   CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
   
   CFRelease(string);
   
   CFRelease(attributes);
   
   CTLineRef line = CTLineCreateWithAttributedString(attrString);
   
   CGFloat ascent, descent, leading, width;
   
   width = CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
   
   //      double dRate = dFontSize / (ascent + descent + leading);
   
   if(bDraw)
   {
      
      CGContextSetTextDrawingMode(m_pdc, emode);
      
      CGContextSetTextMatrix(m_pdc, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y + dFontSize), 1.f, -1.f));
      
      CTLineDraw(line, m_pdc);
      
   }
   
   CFRelease(line);
   
   if(emode != kCGTextInvisible && bDraw)
   {
      
      CGColorRelease(cr);
      
   }
   
   CFRelease(fontName);
   
   CFRelease(fontD);
   
   CFRelease(font);
   
   if(pascent != NULL)
   {
      
      *pascent = ascent;
      
   }
   
   if(pdescent != NULL)
   {
      
      *pdescent = descent;
      
   }
   
   if(pleading != NULL)
   {
      
      *pleading = leading;
      
   }
   
   if(pwidth != NULL)
   {
      
      *pwidth = width;
      
   }
   
   return true;
   
}

bool os_simple_graphics::fill()
{

   return fill(&m_brush);
   
}


bool os_simple_graphics::fill(simple_brush * pbrush)
{

   if(pbrush->m_etype == ::simple_brush::type_linear_gradient_point_color)
   {
   
      CGContextSaveGState(m_pdc);
   
      CGContextClip(m_pdc);
   
      CGPoint myStartPoint, myEndPoint;
   
      myStartPoint.x = pbrush->m_pt1.x;
   
      myStartPoint.y = pbrush->m_pt1.y;
   
      myEndPoint.x = pbrush->m_pt2.x;
   
      myEndPoint.y = pbrush->m_pt2.y;
   
      CGContextDrawLinearGradient(m_pdc, (CGGradientRef) pbrush->get_os_data(), myStartPoint, myEndPoint, 0);
   
      CGContextRestoreGState(m_pdc);
   
   }
   else
   {
   
      CGContextSetFillColorWithColor(m_pdc, (CGColorRef) pbrush->get_os_data());
   
      CGContextFillPath(m_pdc);
   
   }

   return true;

}

bool os_simple_graphics::draw()
{
   
   return draw(&m_pen);
   
}


bool os_simple_graphics::draw(simple_pen * ppen)
{
   
   if(ppen == NULL || ppen->m_etype == ::simple_pen::type_null)
      return true;
   
   if(ppen->m_etype == ::simple_pen::type_solid)
   {
      
      CGContextSaveGState(m_pdc);
      
      CGContextSetRGBStrokeColor(m_pdc, GetRValue(ppen->m_cr) / 255.f, GetGValue(ppen->m_cr) / 255.f, GetBValue(ppen->m_cr) / 255.f, GetAValue(ppen->m_cr) / 255.f);
      
      CGContextSetLineWidth(m_pdc, ppen->m_dWidth);
      
      if(fmod(ppen->m_dWidth, 2.0) <= 1.0)
      {
         
         CGContextTranslateCTM(m_pdc, 0.5f, 0.5f);
         
      }
      
      CGContextStrokePath(m_pdc);
      
      CGContextRestoreGState(m_pdc);
      
   }
   
   return true;
   
}
