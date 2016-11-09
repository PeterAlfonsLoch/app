//#include "framework.h"
//#include "aura/graphics/graphics.h"




// CreateHITMAP (adapted)
// Adapted from 
// Marius Bancila's Blog
// C++,.NET,Windows programming & others
// (CAmiloST's opinion [Sato's opinion] why 's and .NET?, isn't ++ enough or needed more .Net or exquisite type of coffe?!?!?! or snake or something else?!?!
// Marius Bancila
// Software Developer
// Microsoft MVP VisualC++
// Cofounder of Codexpert
// www.mariusbancila.ro
// http://mariusbancila.ro/blog/tag/wic/
// Display images as you type in C++
// Marius Bancila C++ 2011 - 08 - 04 1 comment

HBITMAP CreateHBITMAP(COLORREF * pdata,int stride,int cx,int cy)
{

   HBITMAP hbmp = NULL;

   BITMAPINFO bminfo;

   ZeroMemory(&bminfo,sizeof(bminfo));
   bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bminfo.bmiHeader.biWidth = cx;
   bminfo.bmiHeader.biHeight = -((LONG)cy);
   bminfo.bmiHeader.biPlanes = 1;
   bminfo.bmiHeader.biBitCount = 32;
   bminfo.bmiHeader.biCompression = BI_RGB;

   COLORREF * pvImageBits = NULL;

   HDC hdcScreen = GetDC(NULL);

   hbmp = CreateDIBSection(hdcScreen,&bminfo,DIB_RGB_COLORS,(void **)&pvImageBits,NULL,0);

   ReleaseDC(NULL,hdcScreen);

   if(hbmp == NULL)
      goto Return;

   int bmStride = cx * sizeof(COLORREF);

   if(stride == bmStride)
   {

      memcpy(pvImageBits,pdata,cy * stride);

   }
   else
   {

      byte * psrc = (byte *)pdata;

      byte * pdst = (byte *)pvImageBits;

      for(index i = 0; i < cy; i++)
      {

         memcpy(pvImageBits,pdata,bmStride);

      }

   }

Return:

   return hbmp;

}




// default implementation for these methods (present only in Windows for Desktop Applications)


namespace draw2d
{

   HBITMAP bitmap::GetHBITMAP()
   {

      if(m_hbitmapGet != NULL)
         return m_hbitmapGet;

      m_hbitmapGet = _GetHBITMAP();

      return m_hbitmapGet;

   }

   void bitmap::ReleaseHBITMAP(HBITMAP hbitmap)
   {

      if(hbitmap == NULL)
         return;

      if(m_hbitmapGet == NULL)
         return;

      _ReleaseHBITMAP(hbitmap);

      m_hbitmapGet = NULL;

   }

   HBITMAP bitmap::_GetHBITMAP()
   {

      if(get_os_data() == NULL)
         return NULL;

      ::draw2d::dib_sp dib(allocer());

      dib->create(GetBitmapDimension());

      if(dib->area() <= 0)
         return NULL;

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      g->SelectObject(this);

      dib->get_graphics()->BitBlt(null_point(),dib->m_size,g,null_point(),SRCCOPY);

      return CreateHBITMAP(dib->m_pcolorref,dib->m_iScan,dib->m_size.cx,dib->m_size.cy);

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      ::DeleteObject(hbitmap);

   }

} // namespace draw2d







HFONT wingdi_CreatePointFont(int nPointSize, const char * lpszFaceName, HDC hdc, LOGFONTW *plf)
{

   LOGFONTW lF;

   if (plf == NULL)
      plf = &lF;

   ZEROP(plf);

   plf->lfCharSet = DEFAULT_CHARSET;

   plf->lfHeight = nPointSize;

   wstring wstr(lpszFaceName);

   wstr = wstr.substr(0, sizeof(plf->lfFaceName));

   wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

   return wingdi_CreatePointFontIndirect(plf, hdc);

}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT wingdi_CreatePointFontIndirect(LOGFONTW* lpLogFont, HDC hdc)
{

   LOGFONTW & logFont = *lpLogFont;

   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hdc, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hdc, &ptOrg, 1);
   logFont.lfHeight = -abs(pt.y - ptOrg.y);

   logFont.lfQuality = ANTIALIASED_QUALITY;

   HFONT hfont = ::CreateFontIndirectW(&logFont);

   if (::GetObjectW(hfont, sizeof(logFont), lpLogFont))
   {

      output_debug_string("got log font");
   }



   return hfont;

}


namespace draw2d
{


   font::e_cs wingdi_get_cs(int iCs)
   {

      if (iCs == CHINESEBIG5_CHARSET)
      {

         return font::cs_CHINESEBIG5;

      }
      else if (iCs == GB2312_CHARSET)
      {

         return font::cs_GB2312;

      }
      else if (iCs == SHIFTJIS_CHARSET)
      {

         return font::cs_SHIFTJIS;

      }
      else if (iCs == ANSI_CHARSET)
      {

         return font::cs_ANSI;

      }
      else if (iCs == SYMBOL_CHARSET)
      {

         return font::cs_SYMBOL;

      }
      else if (iCs == OEM_CHARSET)
      {

         return font::cs_DEFAULT;

      }
      else if (iCs == DEFAULT_CHARSET)
      {

         return font::cs_DEFAULT;

      }
      else if (iCs == HEBREW_CHARSET)
      {

         return font::cs_HEBREW;

      }
      else if (iCs == ARABIC_CHARSET)
      {

         return font::cs_ARABIC;

      }
      else if (iCs == GREEK_CHARSET)
      {

         return font::cs_GREEK;

      }
      else if (iCs == TURKISH_CHARSET)
      {

         return font::cs_TURKISH;

      }
      else if (iCs == VIETNAMESE_CHARSET)
      {

         return font::cs_VIETNAMESE;

      }
      else if (iCs == THAI_CHARSET)
      {

         return font::cs_THAI;

      }
      else if (iCs == EASTEUROPE_CHARSET)
      {

         return font::cs_EASTEUROPE;

      }
      else if (iCs == RUSSIAN_CHARSET)
      {

         return font::cs_RUSSIAN;

      }
      else if (iCs == JOHAB_CHARSET)
      {

         return font::cs_JOHAB;

      }
      else if (iCs == HANGUL_CHARSET)
      {

         return font::cs_HANGUL;

      }
      else if (iCs == BALTIC_CHARSET)
      {

         return font::cs_BALTIC;

      }
      else if (iCs == MAC_CHARSET)
      {

         return font::cs_MAC;

      }
      else
      {

         output_debug_string("OTHER CHAR SET");

      }

      return font::cs_DEFAULT;

   }


} // namespace draw2d




