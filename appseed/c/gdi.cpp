#include "StdAfx.h"



#ifdef LINUX
#include "linux/c_os_cross_win_gdi_internal.h"
#elif defined(MACOS)
#include "macos/c_os_cross_win_gdi_internal.h"
#endif




#if defined(LINUX) || defined(MACOS)

BOOL TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
{    
    CGContextRef m_cgContext = hdc->m_gcontext;
    int angle = 0;
    
    if (pszUtf8 == NULL || strlen(pszUtf8) <= 0)
        return TRUE;
    
    //wxMacFastPortSetter helper(this) ;
   // MacInstallFont() ;
    
    OSStatus status = noErr ;
    ATSUTextLayout atsuLayout ;
    
    //wxMacUniCharBuffer unibuf( str ) ;
    UniChar * unibuf = (UniChar *) utf8_to_16(pszUtf8);
    UniCharCount chars = wcslen_dup((wchar_t *)unibuf);
    
    status = ::ATSUCreateTextLayoutWithTextPtr( unibuf , 0 , chars , chars , 1 ,
                                               &chars , (ATSUStyle*) &hdc->m_macATSUIStyle , &atsuLayout ) ;
    
//    wxASSERT_MSG( status == noErr , wxT("couldn't create the layout of the rotated text") );
    
    status = ::ATSUSetTransientFontMatching( atsuLayout , true ) ;
 //   wxASSERT_MSG( status == noErr , wxT("couldn't setup transient font matching") );
    
    int iAngle = int( angle );
    int drawX = hdc->XLOG2DEVMAC(x) ;
    int drawY = hdc->YLOG2DEVMAC(y) ;
    
    ATSUTextMeasurement textBefore, textAfter ;
    ATSUTextMeasurement ascent, descent ;
    
    ATSLineLayoutOptions layoutOptions = kATSLineNoLayoutOptions ;
    
    if (m_font.GetNoAntiAliasing())
    {
        layoutOptions |= kATSLineNoAntiAliasing ;
    }
    
    Fixed atsuAngle = IntToFixed( iAngle ) ;
    
    ATSUAttributeTag atsuTags[] =
    {
        kATSULineLayoutOptionsTag ,
        kATSULineRotationTag ,
    } ;
    
    ByteCount atsuSizes[sizeof(atsuTags)/sizeof(ATSUAttributeTag)] =
    {
        sizeof( ATSLineLayoutOptions ) ,
        sizeof( Fixed ) ,
    } ;
    
    ATSUAttributeValuePtr    atsuValues[sizeof(atsuTags)/sizeof(ATSUAttributeTag)] =
    {
        &layoutOptions ,
        &atsuAngle ,
    } ;
    
    status = ::ATSUSetLayoutControls(atsuLayout , sizeof(atsuTags)/sizeof(ATSUAttributeTag) - ( abs(iAngle) > 0.001 ? 0 : 1),
                                     atsuTags, atsuSizes, atsuValues ) ;
    
    status = ::ATSUMeasureText( atsuLayout, kATSUFromTextBeginning, kATSUToTextEnd,
                               &textBefore , &textAfter, &ascent , &descent );
    wxASSERT_MSG( status == noErr , wxT("couldn't measure the rotated text") );
    
    if ( m_backgroundMode == wxSOLID )
    {
        // background painting must be done by hand, cannot be done by ATSUI
        wxCoord x2 , y2 ;
        PolyHandle polygon = OpenPoly();
        
        ::MoveTo(drawX, drawY);
        
        x2 = (int) (drawX + sin(angle / RAD2DEG) * FixedToInt(ascent + descent)) ;
        y2 = (int) (drawY + cos(angle / RAD2DEG) * FixedToInt(ascent + descent)) ;
        ::LineTo(x2, y2);
        
        x2 = (int) (drawX + sin(angle / RAD2DEG) * FixedToInt(ascent + descent ) + cos(angle / RAD2DEG) * FixedToInt(textAfter)) ;
        y2 = (int) (drawY + cos(angle / RAD2DEG) * FixedToInt(ascent + descent) - sin(angle / RAD2DEG) * FixedToInt(textAfter)) ;
        ::LineTo(x2, y2);
        
        x2 = (int) (drawX + cos(angle / RAD2DEG) * FixedToInt(textAfter)) ;
        y2 = (int) (drawY - sin(angle / RAD2DEG) * FixedToInt(textAfter)) ;
        ::LineTo(x2, y2);
        
        ::LineTo( drawX, drawY) ;
        ClosePoly();
        
        ::ErasePoly( polygon );
        KillPoly( polygon );
    }
    
    drawX += (int)(sin(angle / RAD2DEG) * FixedToInt(ascent));
    drawY += (int)(cos(angle / RAD2DEG) * FixedToInt(ascent));
    status = ::ATSUDrawText( atsuLayout, kATSUFromTextBeginning, kATSUToTextEnd,
                            IntToFixed(drawX) , IntToFixed(drawY) );
    
    wxASSERT_MSG( status == noErr , wxT("couldn't draw the rotated text") );
    
    Rect rect ;
    status = ::ATSUMeasureTextImage( atsuLayout, kATSUFromTextBeginning, kATSUToTextEnd,
                                    IntToFixed(drawX) , IntToFixed(drawY) , &rect );
    wxASSERT_MSG( status == noErr , wxT("couldn't measure the rotated text") );
    
    OffsetRect( &rect , -m_macLocalOrigin.x , -m_macLocalOrigin.y ) ;
    CalcBoundingBox(XDEV2LOG(rect.left), YDEV2LOG(rect.top) );
    CalcBoundingBox(XDEV2LOG(rect.right), YDEV2LOG(rect.bottom) );
    ::ATSUDisposeTextLayout(atsuLayout);
}

void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   XSetBackground(hdc->m_display, hdc->m_gc, clr);
   XFillRectangle(hdc->m_display, hdc->m_d, hdc->m_gc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
{
   LOGFONT logFont;
   memset_dup(&logFont, 0, sizeof(LOGFONT));
   logFont.lfCharSet = DEFAULT_CHARSET;
   logFont.lfHeight = nPointSize;
   logFont.lfWeight = BOLD ? FW_BOLD : FW_NORMAL;
   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return CreatePointFontIndirect_dup(&logFont, hdc);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{

#ifdef WINDOWS

   HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);

   // convert nPointSize to logical units based on pgraphics
   LOGFONT logFont = *lpLogFont;
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hDC, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hDC, &ptOrg, 1);
   logFont.lfHeight = -abs_dup(pt.y - ptOrg.y);

   if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);

   return ::CreateFontIndirect(&logFont);

#else

   /*HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);*/

   return ::CreateFontIndirect(lpLogFont);

   /*if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);*/

#endif

}




void fastblur(DWORD * pdata, int w, int h, int radius)
{
   if(radius < 1)
   {
      return;
   }
  int wm=w-1;
  int hm=h-1;
  int wh=w*h;
  int div=radius+radius+1;
  simple_int_array iaA;
  iaA.set_size(wh);
  int * a = iaA.get_data();
  simple_int_array iaR;
  iaR.set_size(wh);
  int * r = iaR.get_data();
  simple_int_array iaG;
  iaG.set_size(wh);
  int * g = iaG.get_data();
  simple_int_array iaB;
  iaB.set_size(wh);
  int * b = iaB.get_data();
  int asum, rsum,gsum,bsum,x,y,i,yp,yi,yw;
  int p;
  int p1;
  int p2;
  simple_int_array iaVmin;
  iaVmin.set_size(max(w,h));
  int * vmin = iaVmin.get_data();
  simple_int_array iaVmax;
  iaVmax.set_size(max(w,h));
  int * vmax = iaVmax.get_data();
  int * pix=(int *) pdata;
  simple_int_array iaDv;
  iaDv.set_size(256*div);
  int * dv = iaDv.get_data();
  for (i=0;i<iaDv.get_count();i++)
  {
      dv[i]= min(255, i/div);
  }

  yw=yi=0;

   for(x=0;x<w;x++)
   {
      vmin[x]=min(x+radius+1,wm);
      vmax[x]=max(x-radius,0);
   }

   for (y=0;y<h;y++)
   {
      asum=rsum=gsum=bsum=0;
      for(i=-radius;i<=radius;i++)
      {
         p=pix[yi+min(wm,max(i,0))];
         asum+=((p & 0xff000000)>>24);
         rsum+=((p & 0xff0000)>>16);
         gsum+=((p & 0x00ff00)>>8);
         bsum+=(p & 0x0000ff);
      }
      for(x=0;x<w;x++)
      {
         a[yi]=dv[asum];
         r[yi]=dv[rsum];
         g[yi]=dv[gsum];
         b[yi]=dv[bsum];

         p1=pix[yw+vmin[x]];
         p2=pix[yw+vmax[x]];

         asum+= ((p1 >> 24) & 0xff )-((p2 >> 24) & 0xff);
         rsum+= ((p1 & 0x00ff0000)-(p2 & 0x00ff0000))>>16;
         gsum+= ((p1 & 0x0000ff00)-(p2 & 0x0000ff00))>>8;
         bsum+= ((p1 & 0x000000ff)-(p2 & 0x000000ff));
         yi++;
      }
      yw+=w;
  }
   for (y=0;y<h;y++)
   {
      vmin[y] = min(y+radius+1,hm) * w;
      vmax[y] = max(y-radius,0) * w;
   }

   for (x=0;x<w;x++)
   {
      asum=rsum=gsum=bsum=0;
      yp=-radius*w;
      for(i=-radius;i<=radius;i++)
      {
         yi=max(0,yp)+x;
         rsum+=r[yi];
         gsum+=g[yi];
         bsum+=b[yi];
         asum+=a[yi];
         yp+=w;
      }
      yi=x;
      for (y=0;y<h;y++)
      {
         pix[yi]=(dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];

         p1=x+vmin[y];
         p2=x+vmax[y];

         rsum+=r[p1]-r[p2];
         gsum+=g[p1]-g[p2];
         bsum+=b[p1]-b[p2];
         asum+=a[p1]-a[p2];

      yi+=w;
      }
   }

}

#elif defined(WINDOWS)

BOOL TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   BOOL b = TextOutW(hdc, x, y, pwsz, wcslen_dup(pwsz));
   delete  [] pwsz;
   return b;
}

void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(hdc, clr);
   ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
{
   LOGFONT logFont;
   memset_dup(&logFont, 0, sizeof(LOGFONT));
   logFont.lfCharSet = DEFAULT_CHARSET;
   logFont.lfHeight = nPointSize;
   logFont.lfWeight = BOLD ? FW_BOLD : FW_NORMAL;
   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return CreatePointFontIndirect_dup(&logFont, hdc);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{
   HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);

   // convert nPointSize to logical units based on pgraphics
   LOGFONT logFont = *lpLogFont;
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hDC, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hDC, &ptOrg, 1);
   logFont.lfHeight = -abs_dup(pt.y - ptOrg.y);

   if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);

   return ::CreateFontIndirect(&logFont);
}




void fastblur(DWORD * pdata, int w, int h, int radius)
{
   if(radius < 1)
   {
      return;
   }
  int wm=w-1;
  int hm=h-1;
  int wh=w*h;
  int div=radius+radius+1;
  simple_int_array iaA;
  iaA.set_size(wh);
  int * a = iaA.get_data();
  simple_int_array iaR;
  iaR.set_size(wh);
  int * r = iaR.get_data();
  simple_int_array iaG;
  iaG.set_size(wh);
  int * g = iaG.get_data();
  simple_int_array iaB;
  iaB.set_size(wh);
  int * b = iaB.get_data();
  int asum, rsum,gsum,bsum,x,y,i,yp,yi,yw;
  int p;
  int p1;
  int p2;
  simple_int_array iaVmin;
  iaVmin.set_size(max(w,h));
  int * vmin = iaVmin.get_data();
  simple_int_array iaVmax;
  iaVmax.set_size(max(w,h));
  int * vmax = iaVmax.get_data();
  int * pix=(int *) pdata;
  simple_int_array iaDv;
  iaDv.set_size(256*div);
  int * dv = iaDv.get_data();
  for (i=0;i<iaDv.get_count();i++)
  {
      dv[i]= min(255, i/div);
  }

  yw=yi=0;

   for(x=0;x<w;x++)
   {
      vmin[x]=min(x+radius+1,wm);
      vmax[x]=max(x-radius,0);
   }

   for (y=0;y<h;y++)
   {
      asum=rsum=gsum=bsum=0;
      for(i=-radius;i<=radius;i++)
      {
         p=pix[yi+min(wm,max(i,0))];
         asum+=((p & 0xff000000)>>24);
         rsum+=((p & 0xff0000)>>16);
         gsum+=((p & 0x00ff00)>>8);
         bsum+=(p & 0x0000ff);
      }
      for(x=0;x<w;x++)
      {
         a[yi]=dv[asum];
         r[yi]=dv[rsum];
         g[yi]=dv[gsum];
         b[yi]=dv[bsum];

         p1=pix[yw+vmin[x]];
         p2=pix[yw+vmax[x]];

         asum+= ((p1 >> 24) & 0xff )-((p2 >> 24) & 0xff);
         rsum+= ((p1 & 0x00ff0000)-(p2 & 0x00ff0000))>>16;
         gsum+= ((p1 & 0x0000ff00)-(p2 & 0x0000ff00))>>8;
         bsum+= ((p1 & 0x000000ff)-(p2 & 0x000000ff));
         yi++;
      }
      yw+=w;
  }
   for (y=0;y<h;y++)
   {
      vmin[y] = min(y+radius+1,hm) * w;
      vmax[y] = max(y-radius,0) * w;
   }

   for (x=0;x<w;x++)
   {
      asum=rsum=gsum=bsum=0;
      yp=-radius*w;
      for(i=-radius;i<=radius;i++)
      {
         yi=max(0,yp)+x;
         rsum+=r[yi];
         gsum+=g[yi];
         bsum+=b[yi];
         asum+=a[yi];
         yp+=w;
      }
      yi=x;
      for (y=0;y<h;y++)
      {
         pix[yi]=(dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];

         p1=x+vmin[y];
         p2=x+vmax[y];

         rsum+=r[p1]-r[p2];
         gsum+=g[p1]-g[p2];
         bsum+=b[p1]-b[p2];
         asum+=a[p1]-a[p2];

      yi+=w;
      }
   }

}

#endif
