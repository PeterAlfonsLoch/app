#include "StdAfx.h"
#include "include/FreeImage.h"
#include "FreeImageFileProc.h"

#define AC_SRC_ALPHA                0x01

const imaging::CSysColorMap imaging::s_psyscolormap[] =
{
   // mapping from color in DIB to system color
   { RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
   { RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark gray
   { RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright gray
   { RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT },   // white
   { RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  0x80000000}
};

imaging::imaging(::ca::application * papp) :
   ca(papp)
{
}

imaging::~imaging()
{
   //    if(m_lpVoid != NULL)
   //        free(m_lpVoid);
}


::ca::bitmap_sp imaging::CreateDIBitmap(::ca::graphics * pdc, FIBITMAP * pFreeImage)
{
   ::ca::bitmap_sp bitmap(get_app());
   if(!bitmap->CreateDIBitmap(pdc,
      FreeImage_GetInfoHeader(pFreeImage),
      CBM_INIT,
      FreeImage_GetBits(pFreeImage),
      FreeImage_GetInfo(pFreeImage),
      DIB_RGB_COLORS))
   {
      TRACELASTERROR();
      return NULL;
   }
   return bitmap;
}

::ca::bitmap_sp imaging::CreateBitmap(::ca::graphics * pdc, FIBITMAP * pFreeImage)
{
   ::ca::bitmap_sp bitmap(get_app());
   void * pBits = FreeImage_GetBits(pFreeImage);
   if(!bitmap->CreateDIBitmap(pdc,
      FreeImage_GetInfoHeader(pFreeImage),
      CBM_INIT,
      pBits,
      FreeImage_GetInfo(pFreeImage),
      DIB_RGB_COLORS))
   {
      TRACELASTERROR();
      return (::ca::bitmap *) NULL;
   }

   //   LPVOID lpBits;
   //   BITMAPINFO *pbi = FreeImage_GetInfo(pFreeImage);
   //   HBITMAP hBitmap = ::CreateDIBSection(
   //      NULL,
   //      pbi,
   //      DIB_RGB_COLORS,
   //      &lpBits,
   //      NULL,
   //      0);
   //   memcpy(lpBits, FreeImage_GetBits(pFreeImage), pbi->bmiHeader.biSize);
   LPBITMAPINFO pbi = FreeImage_GetInfo(pFreeImage);
   int iSizeBitsZ = ((pbi->bmiHeader.biWidth * pbi->bmiHeader.biBitCount / 8 + 3) & ~3) * pbi->bmiHeader.biHeight;
   void * pDataZ = malloc(iSizeBitsZ);
   if(pbi->bmiHeader.biHeight != GetDIBits(
      (HDC)pdc->get_os_data(),           // handle to device context
      (HBITMAP)bitmap->get_os_data(),      // handle to bitmap
      0,   // first scan line to set in destination bitmap
      FreeImage_GetInfo(pFreeImage)->bmiHeader.biHeight,   // number of scan lines to copy
      pDataZ,    // address of base_array for bitmap bits
      FreeImage_GetInfo(pFreeImage), // address of structure with bitmap data
      DIB_RGB_COLORS        // RGB or palette index
      ))
   {
//      int i = 1 +1;
      TRACELASTERROR();
   }
   return bitmap;
}


FIBITMAP * imaging::LoadImageFile(var varFile, ::ca::application * papp)
{
   gen::memory_file memfile(get_app());
   System.file().as_memory(varFile, *memfile.get_memory(), papp);
   if(memfile.get_size() <= 0)
      return NULL;
   return LoadImageFile(&memfile);
}


/*FIBITMAP * imaging::LoadImageFile(CArchive & ar)
{
ASSERT(!ar.IsStoring());

return LoadImageFile(ar.GetFile());

}
*/

FIBITMAP * imaging::LoadImageFile(ex1::file * pfile)
{
   FreeImageIO io;
   io.read_proc = __ReadProc2;
   io.seek_proc = __SeekProc2;
   io.tell_proc = __TellProc2;
   io.write_proc = __WriteProc2;
   FIBITMAP *lpVoid = NULL;
   try
   {
      FREE_IMAGE_FORMAT format;
      format = FreeImage_GetFileTypeFromHandle(&io, pfile ,16);
      if(true)
      {
         lpVoid = FreeImage_LoadFromHandle(format, &io, pfile);
      }
   }
   catch(...)
   {
   }
   return lpVoid;
}

/*HBITMAP imaging::LoadBitmap(
                            const char * lpszType,
                            const char * lpszId)
{
   throw not_implemented_exception();
   /*
   gen::memory_file file(get_app());

   gen::Resource resource;

   if(!resource.ReadResource(*file.get_memory(), (UINT) MAKEINTRESOURCE(lpszId), lpszType))
   return false;

   file.seek_to_begin();

   ex1::file * pfile = &file;

   FreeImageIO io;
   io.read_proc   = ___Ex1File__ReadProc;
   io.seek_proc   = ___Ex1File__SeekProc;
   io.tell_proc   = ___Ex1File__TellProc;
   io.write_proc  = ___Ex1File__WriteProc;

   FREE_IMAGE_FORMAT format;
   format = FreeImage_GetFileTypeFromHandle(&io, pfile ,16);
   FIBITMAP *pfi = NULL;
   if(true)
   {
   pfi = FreeImage_LoadFromHandle(format, &io, pfile);
   }

   if(pfi == NULL)
   return NULL;

   BITMAPINFO * pbi = FreeImage_GetInfo(pfi);
   void * pData = FreeImage_GetBits(pfi);


   HDC hdcSource = CreateDC(
   "DISPLAY",
   NULL,
   NULL,
   NULL);

   HBITMAP hBitmapSource = ::CreateCompatibleBitmap(
   hdcSource,
   pbi->bmiHeader.biWidth,
   pbi->bmiHeader.biHeight);

   if(pbi->bmiHeader.biHeight != SetDIBits(
   hdcSource,
   hBitmapSource,
   0,
   pbi->bmiHeader.biHeight,
   pData,
   pbi,
   DIB_RGB_COLORS))
   {
   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);
   delete_object(hBitmapSource);
   return NULL;
   }

   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);

   return hBitmapSource;
   */
//}
//*/

/*****************************************************************************
*
* EmbossedTextOut
*
* draw embossed text in the given device context
*
* hDC                       - hDC to draw in
* x, y                      - Upper left corner of text
* lpsz                      - Pointer to the text
* cb                        - Length of text
* crText                    - color for text face
* crShadow                  - color for text shadow
* cx, cy                    - Offset for shadow
*
* The text will be drawn with the currently selected font.
*
* If cb == -1, the lstrlen(lpsz) will be used.
*
* If crText == -1, COLOR_BTNTEXT will be used.
*
* If crShadow == -1, COLOR_BTNSHADOW will be used.
*
*****************************************************************************/
VOID EmbossedTextOut(
                     HDC                     hDC,
                     int                     x,
                     int                     y,
                     //    char *                   lpsz,
                     LPTSTR                   lpsz,
                     UINT                    cb,
                     COLORREF                crText,
                     COLORREF                crShadow,
                     int                     cx,
                     int                     cy)
{
   COLORREF                crOld;
   UINT                    uMode;
   SIZE                    sizeText;
   RECT                    rcText;

   /* If text length is -1, use lstrlen to get the length
   ** of the text.
   */
   if (cb == -1)
      cb = lstrlen(lpsz);

   /* If the shadow or text color is -1, use the
   ** system color for that one.
   */
   if (crShadow == (COLORREF)-1)
      crShadow = GetSysColor (COLOR_BTNSHADOW);
   if (crText == (COLORREF)-1)
      crText = GetSysColor (COLOR_BTNTEXT);

   /* setup the DC, saving off the old values
   */
   uMode = SetBkMode(hDC, OPAQUE);
   crOld = SetTextColor(hDC, crShadow);

   /* draw the text at the desired offset using the
   ** shadow color, then again at the normal position
   ** using the text color.  This will the text an 'Embossed'
   ** or 'drop shadowed' look depending on what shadow color
   ** and offset are used.
   */
   GetTextExtentPoint32(hDC, lpsz, cb, &sizeText);
   rcText.left   = x;    rcText.right  = x+cx+sizeText.cx;
   rcText.top    = y;    rcText.bottom = y+cy+sizeText.cy;
   //ExtTextOut(hDC, x+cx, y+cy, ETO_OPAQUE, &rcText, lpsz, cb, NULL);
   SetBkMode(hDC, TRANSPARENT);
   //ExtTextOut(hDC, x-cx, y+cy, NULL, &rcText, lpsz, cb, NULL);
   //ExtTextOut(hDC, x-cx, y-cy, NULL, &rcText, lpsz, cb, NULL);
   //ExtTextOut(hDC, x+cx, y-cy, NULL, &rcText, lpsz, cb, NULL);
   //ExtTextOut(hDC, x+cx, y+cy, NULL, &rcText, lpsz, cb, NULL);
   ExtTextOut(hDC, x+cx, y+cy, NULL, NULL, lpsz, cb, NULL);
   SetBkMode(hDC, TRANSPARENT);
   SetTextColor(hDC, crText);
   if(!ExtTextOut(hDC, x, y, 0, NULL, lpsz, cb, NULL))
   {
//      TRACE("Failed to ExtTextOut, GetLastError() -->%d\n", GetLastError());
   }

   /* restore the DC
   */
   SetTextColor(hDC, crOld);
   SetBkMode(hDC, uMode);
}

/*****************************************************************************
*
* CreateScaledFont
*
* create a font scaled so that the given string will fit in the given
* rect, but be as large as possible while maintaining correct aspect ratio.
*
* hDC                       - DC to calculate font for
* lpRect                    - Rectangle to fit text into
* lpszFormat                - Format string to fit into rect
* anPosX[]                  - Will contain the X coordinates for each char
* anPosY                    - Will contain the Y coordinate for the string
*
* Returns HFONT or NULL if one could not be created
*
*****************************************************************************/
HFONT CreateScaledFont(
                       HDC                     hDC,
                       LPRECT                  lpRect,
                       LPRECT               lpWndRect,
                       LPTSTR                   lpszFormat,
                       int                     anPosX[],
                       int*                    nPosY)
{
   LOGFONT                 lf;
   HFONT                   hFont;
   HFONT                   h;
   LONG                    FormatWidth;
   LONG                    ScaledClientWidth;
   LONG                    ScaledClientHeight;
   LONG                    AspectN;
   LONG                    AspectD;
   int                     nPosX;
   UINT                    cb;
   UINT                    ii;
   UINT                    jj;
   SIZE                    size;

   ScaledClientHeight =  ((lpRect->bottom - lpRect->top)) * 3 / 4;
   ScaledClientWidth  =  ((lpRect->right  - lpRect->left)) * 3 / 4;

   memset(&lf, 0, sizeof(lf));
   lf.lfHeight         = -(int)ScaledClientHeight;
   lf.lfWeight         = FW_BOLD;
   lf.lfCharSet        = ANSI_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Arial");

   hFont = CreateFontIndirect(&lf);
   h = (struct HFONT__ *) SelectObject(hDC, hFont);

   cb = lstrlen(lpszFormat);
   GetTextExtentPoint(hDC, lpszFormat, cb, &size);

   AspectN = (LONG)size.cx;
   AspectD = (LONG)size.cy;

   FormatWidth = (ScaledClientHeight*AspectN)/AspectD;

   if (FormatWidth > ScaledClientWidth)
   {
      ScaledClientHeight =
         (ScaledClientWidth*AspectD)/AspectN;
      SelectObject(hDC, h);
      ::DeleteObject(hFont);

      lf.lfHeight = -(int)ScaledClientHeight;

      hFont = CreateFontIndirect(&lf);

      SelectObject(hDC, hFont);
      GetTextExtentPoint(hDC, lpszFormat, cb, &size);
   }

   *nPosY  = lpWndRect->top  + (lpWndRect->bottom- lpWndRect->top  - size.cy)/2;
   nPosX   = lpWndRect->left + (lpWndRect->right - lpWndRect->left - size.cx)/2;

   ii = 0;
   for (jj=0; jj < cb; jj++)
   {
      if (jj != 0)
         GetTextExtentPoint(hDC, lpszFormat, jj, &size);
      else
         size.cx = 0;

      anPosX[ii++] = nPosX + size.cx;
   }

   SelectObject(hDC, h);

   return hFont;
}


void GetMultiLineTextExtent(HDC hDC, stringa * pArray, LPSIZE lpSize)
{
   TEXTMETRIC tm;
   GetTextMetrics(
      hDC,
      &tm);
   int nIndex, nSize;
   nSize = pArray->get_size();
   lpSize->cx = 0;
   size size;
   for(nIndex = 0; nIndex < nSize; nIndex++)
   {
      const string &str = pArray->get_at(nIndex);
      GetTextExtentPoint32(
         hDC,
         str,
         str.get_length(),
         &size);
      if(size.cx > lpSize->cx)
         lpSize->cx = size.cx;
   }
   //   lpSize->cy =
   //      (tm.tmHeight +
   //      tm.tmExternalLeading +
   //      tm.tmInternalLeading) *
   nSize;
   lpSize->cy =
      (tm.tmHeight +
      tm.tmExternalLeading) *
      nSize;
}

void DrawMultiLineText(HDC hDC, stringa * pArray)
{
   TEXTMETRIC tm;
   GetTextMetrics(
      hDC,
      &tm);
   int nIndex, nSize;
   nSize = pArray->get_size();
   int yPos = 0;
   for(nIndex = 0; nIndex < nSize; nIndex++)
   {
      const string &str = pArray->get_at(nIndex);
      TextOut(
         hDC,
         0, yPos,
         str,
         str.get_length());

      yPos +=
         tm.tmHeight +
         tm.tmExternalLeading +
         tm.tmInternalLeading;

   }
}

bool imaging::GrayVRCP(
                       ::ca::graphics * pdc,
                       int x,
                       int y,
                       int cx,
                       int cy,
                       COLORREF crAlpha)
{
   UNREFERENCED_PARAMETER(pdc);
   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
   UNREFERENCED_PARAMETER(cx);
   UNREFERENCED_PARAMETER(cy);
   UNREFERENCED_PARAMETER(crAlpha);
   throw not_implemented_exception();
   ASSERT(FALSE);

   /*   ::ca::graphics * pdc = ::ca::graphics_sp::from_handle(hdc);

   ::ca::bitmap * pbitmap = pdc->GetCurrentBitmap();

   ::ca::bitmap bitmapLocal;

   bitmapLocal.CreateCompatibleBitmap(pdc, 1, 1);

   bool bScreenDC = false;

   {
   ::ca::bitmap * pbitmapOriginal = pdc->SelectObject(bitmapLocal);

   if(pbitmapOriginal == NULL ||
   pbitmapOriginal->get_os_data() ==
   pbitmap->get_os_data())
   {
   bScreenDC = true;
   bitmapLocal.delete_object();
   bitmapLocal.CreateCompatibleBitmap(pdc, cx, cy);
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(pdc);
   ::ca::bitmap * bitmapOld = spgraphics->SelectObject(bitmapLocal);
   spgraphics->BitBlt(0, 0, cx, cy, pdc, x, y, SRCCOPY);
   spgraphics->SelectObject(bitmapOld);
   pbitmap = & bitmapLocal;
   }

   BITMAP bitmap;
   if(!pbitmap->GetBitmap(&bitmap))
   {
   return false;
   }

   UINT uiScanLines = bitmap.bmHeight;
   UINT cbLine = ((bitmap.bmWidth * 3 + 1) & ~1);
   UINT cbImage =
   bitmap.bmHeight * cbLine;


   BITMAPINFO bmi;

   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bmi.bmiHeader.biWidth = bitmap.bmWidth;
   bmi.bmiHeader.biHeight = bitmap.bmHeight;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 24;
   bmi.bmiHeader.biCompression = BI_RGB;
   bmi.bmiHeader.biSizeImage = cbImage;
   bmi.bmiHeader.biXPelsPerMeter = 1;
   bmi.bmiHeader.biYPelsPerMeter = 1;
   bmi.bmiHeader.biClrUsed = 0;
   bmi.bmiHeader.biClrImportant = 0;

   LPBYTE lpbData = (LPBYTE) malloc(cbImage);

   GetDIBits(
   (HDC)pdc->get_os_data(),
   (HBITMAP) pbitmap->get_os_data(),
   0,
   uiScanLines,
   lpbData,
   &bmi,
   DIB_RGB_COLORS);

   LPBYTE lpbBase = lpbData + cbLine * x + y * 3;

   BYTE br, bg, bb;
   for(int i = 0; i < cy; i ++)
   {
   LPBYTE lpbLine = lpbBase + cbLine * i;
   for(int j = 0; j < cx; j++)
   {
   br = lpbLine[0];
   bg = lpbLine[1];
   bb = lpbLine[2];
   if(((br + bg + bb) / 3) < 127)
   {
   // dark;
   *lpbLine++ = 64;
   *lpbLine++ = 64;
   *lpbLine++ = 64;
   }
   else
   {
   *lpbLine++ = 192;
   *lpbLine++ = 192;
   *lpbLine++ = 192;
   }
   }
   }




   SetDIBits(
   (HDC)pdc->get_os_data(),
   (HBITMAP) pbitmap->get_os_data(),
   0,
   uiScanLines,
   lpbData,
   &bmi,
   DIB_RGB_COLORS);

   ::free(lpbData);

   if(bScreenDC)
   {
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(pdc);
   ::ca::bitmap * bitmapOld = spgraphics->SelectObject(bitmapLocal);
   pdc->BitBlt(x, y, cx, cy, &spgraphics, 0, 0, SRCCOPY);
   spgraphics->SelectObject(bitmapOld);
   bitmapLocal.delete_object();
   }
   }

   //GetDIBits(hdc, pbitmap
   //pbitmap->G
   return true;
   */
}

bool imaging::GrayVRCP(
                       ::ca::graphics * pdc,
                       ::ca::bitmap * pbitmap,
                       ::ca::bitmap * pbitmapMask,
                       LPCRECT lpcrect,
                       COLORREF crTransparent)
{

   return GrayVRCP(
      pdc,
      pbitmap,
      pbitmapMask,
      lpcrect->left,
      lpcrect->top,
      lpcrect->right - lpcrect->left,
      lpcrect->bottom - lpcrect->top,
      crTransparent);
}

/*::image_list * imaging::CreateGrayVRCPImageList(
::ca::graphics * pdc,
::image_list * pilGray,
::image_list * pilParam)
{
::image_list * pil = pilGray;

pil->create(pilParam);

::ca::graphics_sp spgraphics(get_app());

spgraphics->CreateCompatibleDC(pdc);

IMAGEINFO ii;

for(int i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
rect rect = ii.rcImage;
GrayVRCP(spgraphics->get_os_data(), ii.hbmImage, ii.hbmMask, rect.left, rect.top, rect.width(), rect.height(), RGB(192, 192, 192));
}
return pil;

}


bool imaging::CreateHueImageList(
::ca::graphics * pdc,
::image_list * pilGray,
::image_list * pilParam,
COLORREF crHue,
double dCompress)
{
::image_list * pil = pilGray;

if(!pil->create(pilParam))
return false;

::ca::graphics_sp spgraphics(get_app());

spgraphics->CreateCompatibleDC(pdc);

IMAGEINFO ii;

for(int i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
rect rect = ii.rcImage;
HueVRCP(
spgraphics->get_os_data(),
ii.hbmImage,
rect.left,
rect.top,
rect.width(),
rect.height(),
crHue,
dCompress);
}
return true;

}*/



bool imaging::CreateHueImageList(
                                 ::ca::graphics * pdc,
                                 image_list * pilGray,
                                 image_list * pilParam,
                                 COLORREF crHue,
                                 double dCompress)
{
   image_list * pil = pilGray;

   if(!pil->create(pilParam))
      return false;


   ::ca::graphics_sp spgraphics(get_app());

   spgraphics->CreateCompatibleDC(pdc);


   HueVRCP(
      spgraphics,
      pil->m_spdib->get_bitmap(),
      0, 0,
      pil->m_spdib->width(),
      pil->m_spdib->height(),
      crHue,
      dCompress);

   return true;

}

bool imaging::Createcolor_blend_ImageList(
                                        image_list * pilGray,
                                        image_list * pilParam,
                                        COLORREF cr,
                                        BYTE bAlpha)
{
   image_list * pil = pilGray;

   if(!pil->create(pilParam))
      return false;

   if(pil->m_spdib->get_graphics()->get_os_data() == NULL)
      return false;

   ::ca::graphics_sp spgraphics(get_app());

   spgraphics->CreateCompatibleDC(NULL);
   spgraphics->SetMapMode(MM_TEXT);
   //::ca::bitmap * pbitmapOld = spgraphics->GetCurrentBitmap();

   color_blend(pil->m_spdib->get_graphics(), null_point(), pil->m_spdib->size(), cr, bAlpha);

//   pil->m_spdib->channel_from(visual::rgba::channel_alpha, pilParam->m_spdib);

   //spgraphics->SelectObject(pbitmapOld);

   return true;

}



/*
::image_list * imaging::CreateGrayVRCPImageList(
::ca::graphics * pdc,
::image_list * pilParam)
{
::image_list * pil = new ::image_list();

pil->create(pilParam);

::ca::graphics_sp spgraphics(get_app());

spgraphics->CreateCompatibleDC(pdc);

IMAGEINFO ii;

for(int i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
rect rect = ii.rcImage;
GrayVRCP(spgraphics->get_os_data(), ii.hbmImage, ii.hbmMask, rect.left, rect.top, rect.width(), rect.height(), RGB(192, 192, 192));
}
return pil;

}

*/


bool imaging::GrayVRCP(
                       ::ca::graphics * pdc,
                       ::ca::bitmap * pbitmap,
                       ::ca::bitmap * pbitmapMask,
                       int x,
                       int y,
                       int cx,
                       int cy,
                       COLORREF crAlpha)
{
   UNREFERENCED_PARAMETER(crAlpha);
   //COLORREF cr3dface = GetSysColor(COLOR_3DFACE);
   COLORREF cr3dshadow = GetSysColor(COLOR_3DSHADOW);
   //BYTE uch3dfaceR = rgba_get_r(cr3dface);
   //BYTE uch3dfaceG = rgba_get_g(cr3dface);
   //BYTE uch3dfaceB = rgba_get_b(cr3dface);
   BYTE uch3dshadowR = rgba_get_r(cr3dshadow);
   BYTE uch3dshadowG = rgba_get_g(cr3dshadow);
   BYTE uch3dshadowB = rgba_get_b(cr3dshadow);

   COLORREF cr3dhighlight = GetSysColor(COLOR_3DHILIGHT);
   BYTE uch3dhighlightR = rgba_get_r(cr3dhighlight);
   BYTE uch3dhighlightG = rgba_get_g(cr3dhighlight);
   BYTE uch3dhighlightB = rgba_get_b(cr3dhighlight);

   class size size = pbitmap->get_size();

   UINT uiScanLines = size.cy;
   UINT cbLine = ((size.cx  * 3 + 3) & ~3);
   UINT cbImage = size.cy * cbLine;

   UINT cbMask = size.cy * ((size.cx + 3) & ~3);


   BITMAPINFO bmi;

   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bmi.bmiHeader.biWidth = size.cx;
   bmi.bmiHeader.biHeight = - size.cy;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 24;
   bmi.bmiHeader.biCompression = BI_RGB;
   bmi.bmiHeader.biSizeImage = 0;
   bmi.bmiHeader.biXPelsPerMeter = 1;
   bmi.bmiHeader.biYPelsPerMeter = 1;
   bmi.bmiHeader.biClrUsed = 0;
   bmi.bmiHeader.biClrImportant = 0;

   LPBYTE lpbData = (LPBYTE) malloc(cbImage);
   LPBYTE lpbShadow = (LPBYTE) malloc(cbMask);
   LPBYTE lpbMask = (LPBYTE) malloc(cbMask);
   //LPBYTE lpbShadow = lpbData;

   if(!GetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) pbitmap->get_os_data(),
      0,
      uiScanLines,
      lpbData,
      &bmi,
      DIB_RGB_COLORS))
   {
      return false;
   }

   class size sizeMask = pbitmapMask->get_size();

   BITMAPINFO * pbmiMask = (BITMAPINFO *) malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

   pbmiMask->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   pbmiMask->bmiHeader.biWidth = sizeMask.cx;
   pbmiMask->bmiHeader.biHeight = - sizeMask.cy;
   pbmiMask->bmiHeader.biPlanes = 1;
   pbmiMask->bmiHeader.biBitCount = 8;
   pbmiMask->bmiHeader.biCompression = BI_RGB;
   pbmiMask->bmiHeader.biSizeImage = 0;
   pbmiMask->bmiHeader.biXPelsPerMeter = 1;
   pbmiMask->bmiHeader.biYPelsPerMeter = 1;
   pbmiMask->bmiHeader.biClrUsed = 0;
   pbmiMask->bmiHeader.biClrImportant = 0;

   if(!GetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) pbitmapMask->get_os_data(),
      0, uiScanLines,
      lpbMask, pbmiMask, DIB_RGB_COLORS))
   {
      return false;
   }


   //   memcpy(lpbShadow, lpbData, cbImage);

   LPBYTE lpbBase = lpbData + cbLine * y + x * 3;
   LPBYTE lpbBaseShift = lpbData + cbLine * (y + 1) + (x + 1) * 3;
   LPBYTE lpbBaseShadow = lpbShadow + size.cx * y + x * 3;
   LPBYTE lpbBaseMask = lpbMask + size.cx * y + x;
   LPBYTE lpbBaseMaskShift = lpbMask + size.cx * (y + 1) + (x + 1);


   BYTE br, bg, bb;

//   COLORREF crBtnFace = GetSysColor(COLOR_BTNFACE);
//   COLORREF crBtnShad = GetSysColor(COLOR_BTNSHADOW);
//   COLORREF crWndBack = GetSysColor(COLOR_WINDOW);

//   BYTE bRBtnFace = rgba_get_r(crBtnFace);
//   BYTE bGBtnFace = rgba_get_g(crBtnFace);
//   BYTE bBBtnFace = rgba_get_b(crBtnFace);

//   BYTE bRBtnShad = rgba_get_r(crBtnShad);
//   BYTE bGBtnShad = rgba_get_g(crBtnShad);
//   BYTE bBBtnShad = rgba_get_b(crBtnShad);

//   BYTE bRWndBack = rgba_get_r(crWndBack);
//   BYTE bGWndBack = rgba_get_g(crWndBack);
//   BYTE bBWndBack = rgba_get_b(crWndBack);

   int i;
   for(i = 0; i < cy; i ++)
   {
      LPBYTE lpbLine = lpbBase + cbLine * i;
      LPBYTE lpbLineShadow = lpbBaseShadow + size.cx * i;
      LPBYTE lpbLineMask = lpbBaseMask + size.cy * i;
      for(int j = 0; j < cx; j++)
      {
         bb = *lpbLine++;
         bg = *lpbLine++;
         br = *lpbLine++;
         if((((br + bg + bb) / 3) < 192) &&
            (*lpbLineMask == 0))
         {
            *lpbLineShadow++ = 1;
         }
         else
         {
            *lpbLineShadow++ = 0;
         }
         lpbLineMask++;
      }
   }











   for(i = 0; i < cy; i ++)
   {
      LPBYTE lpbLine = lpbBase + cbLine * i;
      for(int j = 0; j < cx; j++)
      {
         *lpbLine++ = 0;
         *lpbLine++ = 0;
         *lpbLine++ = 0;
      }
   }










   for(i = 0; i < cy; i ++)
   {
      LPBYTE lpbLineMask = lpbBaseMask + size.cx * i;
      for(int j = 0; j < cx; j++)
      {
         *lpbLineMask++ = 1;
      }
   }




   int cyminus1 = cy - 1;
   int cxminus1 = cx - 1;
   BYTE b;

   for(i = 0; i < cyminus1; i ++)
   {
      LPBYTE lpbLine = lpbBaseShift + cbLine * i;
      LPBYTE lpbLineShadow = lpbBaseShadow + size.cx * i;
      LPBYTE lpbLineMask = lpbBaseMaskShift + size.cx * i;
      for(int j = 0; j < cxminus1; j++)
      {
         b = *lpbLineShadow;
         lpbLineShadow++;

         if(b == 1)
         {
            *lpbLine++ = uch3dhighlightB;
            *lpbLine++ = uch3dhighlightG;
            *lpbLine++ = uch3dhighlightR;
            *lpbLineMask++ = 0;
         }
         else
         {
            lpbLine += 3;
            lpbLineMask++;
         }
      }
   }







   for(i = 0; i < cy; i ++)
   {
      LPBYTE lpbLine = lpbBase + cbLine * i;
      LPBYTE lpbLineShadow = lpbBaseShadow + size.cx * i;
      LPBYTE lpbLineMask = lpbBaseMask + size.cx * i;
      for(int j = 0; j < cx; j++)
      {
         b = *lpbLineShadow;
         lpbLineShadow++;

         if(b == 1)
         {
            *lpbLine++ = uch3dshadowB;
            *lpbLine++ = uch3dshadowG;
            *lpbLine++ = uch3dshadowR;
            *lpbLineMask++ = 0;
         }
         else
         {
            lpbLine += 3;
            lpbLineMask++;
         }
      }
   }

   if(!SetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) pbitmap->get_os_data(),
      0,
      uiScanLines,
      lpbData,
      &bmi,
      DIB_RGB_COLORS))
   {
      return false;
   }

   if(!SetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) pbitmapMask->get_os_data(),
      0,
      uiScanLines,
      lpbMask,
      pbmiMask,
      DIB_RGB_COLORS))
   {
      return false;
   }

   ::free(lpbShadow);
   ::free(lpbData);
   ::free(lpbMask);
   ::free(pbmiMask);

   return true;

}

bool imaging::GetDeviceContext24BitsCC(
                                       ::ca::graphics *pdc,
                                       BITMAP & bm,
                                       BITMAPINFO & bmi,
                                       primitive::memory & memorystorage,
                                       ::ca::bitmap * pbitmap,
                                       LPCRECT lpcrect,
                                       int &iWidthParam,
                                       UINT & uiStartScanLineParam,
                                       UINT & uiScanLineCountParam,
                                       int & iLimitYParam)
{
   UNREFERENCED_PARAMETER(pbitmap);
   rect rect(lpcrect);

//   int x = rect.left;
   int y = rect.top;
//   int cx = rect.width();
   int cy = rect.height();

   ::ca::bitmap_sp spbmpTemp(get_app());
   if(!spbmpTemp->CreateCompatibleBitmap(pdc, 1, 1))
   {
      return false;
   }

   ::ca::bitmap * pbmpOld = pdc->SelectObject(spbmpTemp);

   if(pbmpOld != NULL)
   {
      try
      {
         ::ca::bitmap * pbmp = pbmpOld;

         throw not_implemented_exception();
/*         if(!pbmp->GetObject(sizeof(bm), &bm))
         {
            pdc->SelectObject(pbmpOld);
            return false;
         }*/

         bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
         bmi.bmiHeader.biWidth = bm.bmWidth ;
         bmi.bmiHeader.biHeight = bm.bmHeight;
         bmi.bmiHeader.biPlanes = 1;
         bmi.bmiHeader.biBitCount = 24;
         bmi.bmiHeader.biCompression = BI_RGB;
         bmi.bmiHeader.biSizeImage = 0;
         bmi.bmiHeader.biXPelsPerMeter = 0;
         bmi.bmiHeader.biYPelsPerMeter = 0;
         bmi.bmiHeader.biClrUsed = 0;
         bmi.bmiHeader.biClrImportant = 0;
         int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
         iWidthParam = iLineBytes;
         try
         {
            memorystorage.allocate(iLineBytes * cy);
         }
         catch(memory_exception * pe)
         {
            delete pe;
            throw 4000;
         }
         LPVOID lpv = memorystorage.get_data();
         point pointViewport = pdc->GetViewportOrg();

         UINT uiStartScanLine = max(0, bm.bmHeight - y - cy);
         UINT uiScanLines = cy + min(0, bm.bmHeight - y - cy);

         uiStartScanLineParam = uiStartScanLine;
         uiScanLineCountParam = uiScanLines;

         if(!(iLimitYParam = GetDIBits
            (
            (HDC)pdc->get_os_data(),
            (HBITMAP) pbmp->get_os_data(),
            uiStartScanLine,
            uiScanLines,
            lpv,
            &bmi,
            DIB_RGB_COLORS
            )
            ))
         {
            pdc->SelectObject(pbmpOld);
            return false;
         }
      }
      catch(int)
      {
//         UINT user = GetLastError();
         pdc->SelectObject(pbmpOld);
         return false;
      }
      pdc->SelectObject(pbmpOld);
      return true;
   }
   else
   {
      pdc->SelectObject(pbmpOld);
      return false;
   }
}

/*bool imaging::GetDeviceContext24BitsAllCC(
::ca::graphics *pdc,
BITMAP & bm,
BITMAPINFO & bmi,
primitive::memory & memorystorage,
::ca::bitmap   ** ppbitmap,
LPRECT lprect,
int &iWidthParam,
UINT & uiStartScanLineParam,
UINT & uiScanLineCountParam,
int & iLimitYParam)
{

int x = 0;
int y = 0;
int cx = -1;
int cy = -1;

::ca::bitmap * pbmpOld = pdc->GetCurrentBitmap();
if(pbmpOld == NULL)
{
return false;
}

::ca::bitmap spbmpTemp;
if(!spbmpTemp->CreateCompatibleBitmap(pdc, 1, 1))
{
return false;
}

if(pdc->SelectObject(spbmpTemp))
{
// pdc is a pointer to a primitive::memory device context
try
{
::ca::bitmap * pbmp = pbmpOld;

*ppbitmap = pbmp;

// This is a primitive::memory device context
if(!pbmp->GetObject(sizeof(bm), &bm))
throw 3500;

cx = bm.bmWidth;
cy = bm.bmHeight;

bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
bmi.bmiHeader.biWidth = bm.bmWidth ;
bmi.bmiHeader.biHeight = -bm.bmHeight;
bmi.bmiHeader.biPlanes = 1;
bmi.bmiHeader.biBitCount = 24;
bmi.bmiHeader.biCompression = BI_RGB;
bmi.bmiHeader.biSizeImage = 0;
bmi.bmiHeader.biXPelsPerMeter = 0;
bmi.bmiHeader.biYPelsPerMeter = 0;
bmi.bmiHeader.biClrUsed = 0;
bmi.bmiHeader.biClrImportant = 0;
int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
iWidthParam = iLineBytes;
try
{
memorystorage.allocate(iLineBytes * cy);
}
catch(memory_exception * pe)
{
delete pe;
throw 4000;
}
LPVOID lpv = memorystorage.get_data();
point pointViewport = pdc->GetViewportOrg();

UINT uiStartScanLine = 0;
UINT uiScanLines = cy;

uiStartScanLineParam = uiStartScanLine;
uiScanLineCountParam = uiScanLines;

if(!(iLimitYParam = GetDIBits
(
(HDC)pdc->get_os_data(),
(HBITMAP) pbmp->get_os_data(),
uiStartScanLine,
uiScanLines,
lpv,
&bmi,
DIB_RGB_COLORS
)
))
throw 5000;
}
catch(int)
{
UINT user = GetLastError();
pdc->SelectObject(pbmpOld);
return false;
}
}
else
{
try
{
::ca::bitmap * pbitmap = *ppbitmap;
// this is a display spgraphics

if(pbitmap->m_hObject == NULL)
{
pbitmap->CreateBitmap(cx + 100, cy + 100, 1, 24, NULL);
}
else
{
if(!pbitmap->GetObject(sizeof(bm), &bm))
throw 3500;
if(bm.bmWidth < cx ||
bm.bmHeight  < cy)
{
pbitmap->delete_object();
pbitmap->CreateBitmap(cx + 100, cy + 100, 1, 24, NULL);
}
}

::ca::graphics_sp graphicsMem(get_app());
graphicsMem->CreateCompatibleDC(pdc);
::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(pbitmap);
graphicsMem->BitBlt(
0, 0,
cx, cy,
pdc,
x, y,
SRCCOPY);
if(!pbitmap->GetObject(sizeof(bm), &bm))
throw 3500;
cx = bm.bmWidth;
cy = bm.bmHeight;


bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
bmi.bmiHeader.biWidth = bm.bmWidth ;
bmi.bmiHeader.biHeight = -bm.bmHeight;
bmi.bmiHeader.biPlanes = 1;
bmi.bmiHeader.biBitCount = 24;
bmi.bmiHeader.biCompression = BI_RGB;
bmi.bmiHeader.biSizeImage = 0;
bmi.bmiHeader.biXPelsPerMeter = 0;
bmi.bmiHeader.biYPelsPerMeter = 0;
bmi.bmiHeader.biClrUsed = 0;
bmi.bmiHeader.biClrImportant = 0;
int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
iWidthParam = iLineBytes;
try
{
memorystorage.allocate(iLineBytes * cy);
}
catch(memory_exception * pe)
{
delete pe;
throw 4000;
}

LPVOID lpv = memorystorage.get_data();

point pointViewport;
pointViewport = pdc->GetViewportOrg();
UINT uiStartScanLine = bm.bmHeight;

uiStartScanLineParam = uiStartScanLine;

//UINT uiStartScanLine = bm.bmHeight - y - cy;
UINT uiScanLines = cy;
uiScanLineCountParam = uiScanLines;
int xOffset = (x + pointViewport.x) * 3;
//if(!GetDIBits(dcAux.get_os_data(), bitmap, bm.bmHeight - cy, cy, lpv, &bmi, DIB_RGB_COLORS))
//  throw 5000;
int iLimitY = cy;
if(!(iLimitYParam =
GetDIBits(
graphicsMem->get_os_data(),
*pbitmap,
uiStartScanLine,
uiScanLines,
lpv,
&bmi,
DIB_RGB_COLORS)))
throw 5000;
int iLimitX = cx;

if(bm.bmWidth - x - pointViewport.x < iLimitX)
{
iLimitX = bm.bmWidth - x - pointViewport.x;
}

graphicsMem->SelectObject(pbmpMemOld);
graphicsMem->DeleteDC();
pdc->SelectObject(pbmpOld);
return true;
}
catch(int)
{
return false;
}
}

pdc->SelectObject(pbmpOld);
return true;
}*/

void imaging::BitmapBlend24CC(
                              LPBYTE lpbAParam,
                              int x1,
                              int y1,
                              int w1,
                              int cx,
                              int cy,
                              LPBYTE lpbBParam,
                              int x2,
                              int y2,
                              int w2,
                              LPBYTE lpbCParam,
                              int x3,
                              int y3,
                              int w3)
{
   int i, j;
   x1 *= 3;
   x2 *= 3;
   x3 *= 3;
   y1 *= w1;
   y2 *= w2;
   y3 *= w3;

   lpbAParam = (LPBYTE) lpbAParam + y1 + x1;
   lpbBParam = (LPBYTE) lpbBParam + y2 + x2;
   lpbCParam = (LPBYTE) lpbCParam + y3 + x3;

   //   BYTE dwA;
   for(i = 0; i < cy; i++)
   {
      LPBYTE lpbA = (LPBYTE) lpbAParam + (w1 * i);
      LPBYTE lpbB = (LPBYTE) lpbBParam + (w2 * i);
      LPBYTE lpbC = (LPBYTE) lpbCParam + (w3 * i);
      for(j = 0; j < cx; j++)
      {
         *lpbA++ = (BYTE) (((((DWORD) *lpbA) * ((DWORD) (255 - *lpbC)) + (((DWORD) *lpbB++) * ((DWORD) *lpbC++)))) / 255);
         *lpbA++ = (BYTE) (((((DWORD) *lpbA) * ((DWORD) (255 - *lpbC)) + (((DWORD) *lpbB++) * ((DWORD) *lpbC++)))) / 255);
         *lpbA++ = (BYTE) (((((DWORD) *lpbA) * ((DWORD) (255 - *lpbC)) + (((DWORD) *lpbB++) * ((DWORD) *lpbC++)))) / 255);
      }
   }

}


void imaging::BitmapBlend24CC(
                              LPBYTE lpbDestParam,
                              int xDest,
                              int yDest,
                              int wDest,
                              int cx,
                              int cy,
                              LPBYTE lpbSrcParam,
                              int xSrc,
                              int ySrc,
                              int wSrc,
                              BYTE bAlpha)
{
   int i, j;
   xDest *= 3;
   xSrc *= 3;
   yDest *= wDest;
   ySrc *= wSrc;

//   int maxw = cx * 3;
//   int cw = (maxw) & ~3;



   int iDestPadding = wDest - cx * 3;
   int iSrcPadding = wSrc - cx * 3;


   lpbDestParam = (LPBYTE) lpbDestParam + yDest + xDest;
   lpbSrcParam = (LPBYTE) lpbSrcParam + ySrc + xSrc;

//   BYTE bAlphaComplement = 255 - bAlpha;
   //   BYTE dwA;
   if(bAlpha == 0)
   {
   }
   if(bAlpha == 255)
   {
      for(i = 0; i < cy; i++)
      {
         LPBYTE lpbDst = (LPBYTE) lpbDestParam + (wDest * i);
         LPBYTE lpbSrc = (LPBYTE) lpbSrcParam + (wSrc * i);
         for(j = 0; j < cx; j++)
         {
            *lpbDst++ = *lpbSrc++;
            *lpbDst++ = *lpbSrc++;
            *lpbDst++ = *lpbSrc++;
         }
      }
   }
   else
   {
      LPBYTE lpbDst = (LPBYTE) lpbDestParam;
      LPBYTE lpbSrc = (LPBYTE) lpbSrcParam;
      for(i = 0; i < cy; i++)
      {

         for(j = 0; j < cx; j++)
         {
            *lpbDst++ = (BYTE) (((((int)*lpbSrc++ - *lpbDst) * ((int) (bAlpha))) / 256) + (int) *lpbDst);
            *lpbDst++ = (BYTE) (((((int)*lpbSrc++ - *lpbDst) * ((int) (bAlpha))) / 256) + (int) *lpbDst);
            *lpbDst++ = (BYTE) (((((int)*lpbSrc++ - *lpbDst) * ((int) (bAlpha))) / 256) + (int) *lpbDst);
         }
         lpbDst = (LPBYTE) lpbDst + iDestPadding;
         lpbSrc = (LPBYTE) lpbSrc + iSrcPadding;
      }
      /*      lpushDest = (unsigned short *) lpbDestParam;
      lpushSrc = (unsigned short *) lpbSrcParam;
      for(i = 0; i < cy; i++)
      {
      for(j = 0; j < cw; j+=2)
      {
      dwSrc = (*lpushSrc & 0xff) | ((*lpushSrc & 0xff00) << 16);
      dwDest = (*lpushDest & 0xff) | ((*lpushDest & 0xff00) << 16);
      dwDest = (((dwSrc - dwDest) * bAlpha) / 256) + dwDest;
      *lpushDest = (dwDest & 0xff) | ((dwDest & 0x00ff0000) >> 16);
      lpushSrc++;
      lpushDest++;
      }
      LPBYTE lpbDst = (LPBYTE) lpushDest;
      LPBYTE lpbSrc = (LPBYTE) lpushSrc;
      for(;j < maxw; j++)
      {
      *lpbDst++ = (BYTE) (((DWORD) (*lpbSrc++ - *lpbDst) * ((DWORD) (bAlpha))) / 256) + *lpbDst;
      }
      lpbDst = (LPBYTE) lpbDestParam + iDestPadding;
      lpbSrc = (LPBYTE) lpbSrcParam + iSrcPadding;
      }*/
   }

}


bool imaging::bitmap_blend(
                          ::ca::graphics * pdcDst, // destination device
                          point pt,
                          size size,
                          ::ca::graphics * pdcSrc, // source device
                          point ptSrc,
                          ::ca::graphics * pdcAlpha, // alpha information device (in alpha channel)
                          point ptAlpha,
                          ::ca::graphics * pdcAlphaComplement, // alpha information device (in alpha channel)
                          point ptAlphaComplement)
{

      UNREFERENCED_PARAMETER(ptAlphaComplement);
      ::ca::dib_sp dibA(get_app());

      if(!dibA->create(size))
         return false;

      ::ca::dib_sp dibB(get_app());

      if(!dibB->create(size))
         return false;

      //::ca::bitmap * pbmpOldA = (::ca::bitmap *) dibA->get_graphics()->SelectObject(dibA->get_graphics());
      //::ca::bitmap * pbmpOldB = (::ca::bitmap *) dibB->get_graphics()->SelectObject(dibB->get_graphics());

      dibB->get_graphics()->from(null_point(), size, pdcSrc, ptSrc, SRCCOPY);


      dibA->get_graphics()->from(null_point(), size, pdcAlphaComplement, ptAlpha, SRCCOPY);

      GdiFlush();


//      __int64 a = size.area();

      BLENDFUNCTION bf;
      bf.BlendOp     = AC_SRC_OVER;
      bf.BlendFlags  = 0;
      bf.SourceConstantAlpha = 0xFF;
      bf.AlphaFormat = AC_SRC_ALPHA;

      BOOL bOk;

      try
      {
         dibB->get_graphics()->alpha_blend(size, dibA->get_graphics(), bf);
      }
      catch(...)
      {
         bOk = false;
      }


      GdiFlush();

      dibA->get_graphics()->FillSolidRect(0, 0, size.cx, size.cy, RGB(255, 255, 255));
      dibB->get_graphics()->from(null_point(), size, dibA->get_graphics(), null_point(), SRCAND);

      //dibA->get_graphics()->BitBlt(0, 0, cx, cy, pdcAlpha, x3, y3, SRCCOPY);
      dibB->get_graphics()->from(null_point(), size, pdcAlpha, ptAlpha, SRCPAINT);

      try
      {
         pdcDst->alpha_blend(pt, size, dibB->get_graphics(), bf);
      }
      catch(...)
      {
         bOk = false;
      }

      GdiFlush();


      return true;
}

bool imaging::bitmap_blend(
                          ::ca::graphics * pdcA, // destination device
                          point pt,
                          size size,
                          ::ca::graphics * pdcB, // source device
                          point ptSrc,
                          ::ca::graphics * pdcC, // alpha information device
                          point ptAlpha,
                          byte uchAlphaConstant,
                          ::ca::dib * pdibA,
                          ::ca::dib * pdibB)
{
   ::ca::dib_sp dibA;
   ::ca::dib_sp dibB;

   if(pdibA == NULL)
   {
      dibA.create(get_app());
      pdibA = dibA;
   }
   if(pdibB == NULL)
   {
      dibB.create(get_app());
      pdibB = dibB;
   }


   if(!pdibA->create(size))
      return false;
   if(!pdibB->create(size))
      return false;


   pdibB->get_graphics()->from(null_point(), size, pdcB, ptSrc, SRCCOPY);


   pdibA->get_graphics()->from(null_point(), size, pdcC, ptAlpha, SRCCOPY);

   GdiFlush();


   UINT32 * lpuiA = (UINT32 *) pdibA->get_data();

   __int64 a = size.area();
   __int64 i;

   __int64 b = a - a % 4;
   for(i = 0; i < b; i +=4)
   {
      lpuiA[0] = 0xff000000 - ((lpuiA[0]) & 0xff000000);
      lpuiA[1] = 0xff000000 - ((lpuiA[1]) & 0xff000000);
      lpuiA[2] = 0xff000000 - ((lpuiA[2]) & 0xff000000);
      lpuiA[3] = 0xff000000 - ((lpuiA[3]) & 0xff000000);
      lpuiA += 4;
   }
   for (; i < a; i++)
   {
      *lpuiA++ = 0xff000000 - ((*lpuiA) & 0xff000000);
   }

   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = uchAlphaConstant;
   bf.AlphaFormat = AC_SRC_ALPHA;

   BOOL bOk;
   try
   {
      pdibB->get_graphics()->alpha_blend(size, pdibA->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }


   GdiFlush();

   lpuiA = (UINT32 *) pdibA->get_data();
   UINT32 * lpuiB = (UINT32 *) pdibB->get_data();

   for (i = 0; i < b; i +=4)
   {
      lpuiA[0] = (0xff000000 - (lpuiA[0] & 0xff000000)) | (lpuiB[0]  & 0x00ffffff);
      lpuiA[1] = (0xff000000 - (lpuiA[1] & 0xff000000)) | (lpuiB[1]  & 0x00ffffff);
      lpuiA[2] = (0xff000000 - (lpuiA[2] & 0xff000000)) | (lpuiB[2]  & 0x00ffffff);
      lpuiA[3] = (0xff000000 - (lpuiA[3] & 0xff000000)) | (lpuiB[3]  & 0x00ffffff);
      lpuiA += 4;
      lpuiB += 4;
   }
   for (; i < a; i++)
   {
      *lpuiA++ = (0xff000000 - (*lpuiA & 0xff000000)) | (*lpuiB++  & 0x00ffffff);
   }

   try
   {
      pdcA->alpha_blend(pt, size, pdibA->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }


   GdiFlush();


   return true;


}


bool imaging::bitmap_blend(
                          ::ca::graphics * pdcA, // destination device
                          point pt,
                          size size,
                          ::ca::dib * pdibB, // source device
                          point ptSrc,
                          ::ca::dib * pdibC, // alpha information device
                          point ptAlpha,
                          byte uchAlphaConstant)
{

   UNREFERENCED_PARAMETER(ptSrc);
   UNREFERENCED_PARAMETER(ptAlpha);

   GdiFlush();


   UINT32 * lpuiA = (UINT32 *) pdibC->get_data();

   __int64 a = size.area();
   __int64 i;

   __int64 b = a - a % 4;
   for(i = 0; i < b; i +=4)
   {
      lpuiA[0] = 0xff000000 - ((lpuiA[0]) & 0xff000000);
      lpuiA[1] = 0xff000000 - ((lpuiA[1]) & 0xff000000);
      lpuiA[2] = 0xff000000 - ((lpuiA[2]) & 0xff000000);
      lpuiA[3] = 0xff000000 - ((lpuiA[3]) & 0xff000000);
      lpuiA += 4;
   }
   for (; i < a; i++)
   {
      *lpuiA++ = 0xff000000 - ((*lpuiA) & 0xff000000);
   }

   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = uchAlphaConstant;
   bf.AlphaFormat = AC_SRC_ALPHA;

   BOOL bOk;
   try
   {
      pdibB->get_graphics()->alpha_blend(size, pdibC->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }


   GdiFlush();

   lpuiA = (UINT32 *) pdibC->get_data();
   UINT32 * lpuiB = (UINT32 *) pdibB->get_data();

   for (i = 0; i < b; i +=4)
   {
      lpuiA[0] = (0xff000000 - (lpuiA[0] & 0xff000000)) | (lpuiB[0]  & 0x00ffffff);
      lpuiA[1] = (0xff000000 - (lpuiA[1] & 0xff000000)) | (lpuiB[1]  & 0x00ffffff);
      lpuiA[2] = (0xff000000 - (lpuiA[2] & 0xff000000)) | (lpuiB[2]  & 0x00ffffff);
      lpuiA[3] = (0xff000000 - (lpuiA[3] & 0xff000000)) | (lpuiB[3]  & 0x00ffffff);
      lpuiA += 4;
      lpuiB += 4;
   }
   for (; i < a; i++)
   {
      *lpuiA++ = (0xff000000 - (*lpuiA & 0xff000000)) | (*lpuiB++  & 0x00ffffff);
   }

   try
   {
      pdcA->alpha_blend(pt, size, pdibC->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }
   GdiFlush();


   return true;


}

bool imaging::BitmapBlend2(
                           ::ca::graphics * pdcA, // destination device
                           point pt,
                           size size,
                           ::ca::graphics * pdcB, // source device
                           point ptSrc,
                           ::ca::graphics * pdcC, // alpha information device
                           point ptAlpha)
{
   BITMAPINFO bmi;

   // zero the primitive::memory for the bitmap info
   ZeroMemory(&bmi, sizeof(BITMAPINFO));

   ::ca::dib_sp dibA(get_app());

   if(!dibA->create(size))
      return false;

   ::ca::dib_sp dibB(get_app());

   if(!dibB->create(size))
      return false;

   dibB->get_graphics()->from(size, pdcB, ptSrc, SRCCOPY);

   dibA->get_graphics()->from(size, pdcC, ptAlpha, SRCCOPY);

   GdiFlush();


   UINT32 * lpuiA = (UINT32 *) dibA->get_data();

//   __int64 a = size.area();
   //      int i;

//   __int64 b = a - 4;
   /*      for (i = 0; i < b; i +=4)
   {
   lpuiA[0] = ((lpuiA[0] << 8) & 0xff000000);
   lpuiA[1] = ((lpuiA[1] << 8) & 0xff000000);
   lpuiA[2] = ((lpuiA[2] << 8) & 0xff000000);
   lpuiA[3] = ((lpuiA[3] << 8) & 0xff000000);
   lpuiA += 4;
   }
   for (; i < a; i++)
   {
   *lpuiA++ = ((*lpuiA << 8) & 0xff000000);
   }

   rect rect(0, 0, cx, cy);
   dibA->get_graphics()->InvertRect(rect);*/

   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = 0xFF;
   bf.AlphaFormat = AC_SRC_ALPHA;

   BOOL bOk;
   try
   {
      dibB->get_graphics()->alpha_blend(size, dibA->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }


   GdiFlush();

   lpuiA = (UINT32 *) dibA->get_data();
//   UINT32 * lpuiB = (UINT32 *) dibB->get_data();

   rect rect(null_point(), size);
   //      dibA->get_graphics()->InvertRect(rect);

   ::ca::dib_sp dibPat(get_app());
   dibPat->create(64, 64);
   dibPat->Fill(255, 0, 0, 0);

   ::ca::brush_sp brush(get_app());
   brush->CreatePatternBrush(dibPat->get_bitmap());

   ::ca::dib_sp spdib(get_app());
   spdib->create(size);

   spdib->get_graphics()->FillRect(rect, brush);

   try
   {
      pdcA->alpha_blend(pt, size, dibA->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }

   GdiFlush();

   return true;



}

bool imaging::bitmap_blend(
                          ::ca::graphics * pdcDst, // destination device
                          point pt,
                          size size,
                          ::ca::graphics * pdcSrcWithAlpha, // source device
                          point ptSrc)
{
   return color_blend(pdcDst, pt, size, pdcSrcWithAlpha, ptSrc);
}

bool imaging::BitmapDivBlend(
                          ::ca::graphics * pdcDst, // destination device
                          point ptDst,
                          size size,
                          ::ca::graphics * pdcSrc, // source device
                          point ptSrc,
                          BYTE bAlpha)
{
   visual::dib_sp spdib(get_app());
   spdib->create(size);
   spdib->to(pdcSrc, size);
   spdib->DivideRGB(bAlpha);
   BLENDFUNCTION bf;
   bf.BlendOp = AC_SRC_OVER;
   bf.BlendFlags = 0;
   bf.SourceConstantAlpha = bAlpha;  // half of 0xff = 50% transparency
   bf.AlphaFormat = 0;             // ignore source alpha channel

   //      try
   //    {
   return pdcDst->alpha_blend(ptDst, size, spdib->get_graphics(), ptSrc, bf) != 0;
}


bool imaging::bitmap_blend(
                          ::ca::graphics * pdcDst, // destination device
                          point ptDst,
                          size size,
                          ::ca::graphics * pdcSrc, // source device
                          point ptSrc,
                          BYTE bAlpha)
{
   BLENDFUNCTION bf;
   bf.BlendOp = AC_SRC_OVER;
   bf.BlendFlags = 0;
   bf.SourceConstantAlpha = bAlpha;  // half of 0xff = 50% transparency
   bf.AlphaFormat = 0;             // ignore source alpha channel

   //      try
   //    {
   return pdcDst->alpha_blend(ptDst, size, pdcSrc, ptSrc, bf) != 0;
}



bool imaging::ColorInvert(::ca::graphics * pdc, int x, int y, int cx, int cy)
{


   if(cx <= 0 || cy <= 0)
      return true;

   return false;

   //    single_lock sl(&m_csMem, TRUE);

   /*int iOriginalMapMode ;

   ::ca::bitmap_sp spbmpTemp(get_app());

   ::ca::bitmap_sp bitmapA(get_app());

   iOriginalMapMode = pdc->GetMapMode();
   pdc->SetMapMode(MM_TEXT);
   if(!spbmpTemp->CreateCompatibleBitmap(pdc, 1, 1))
   {
      pdc->SetMapMode(iOriginalMapMode);
      return false;
   }

   if(!pdc->SelectObject(spbmpTemp))
   {
      try
      {
         // this is a display spgraphics

         if(bitmapA->get_os_data() == NULL)
         {
            bitmapA->CreateBitmap(cx + 100, cy + 100, 1, 24, NULL);
         }
         else
         {
            BITMAP bm;
            if(!bitmapA->GetObject(sizeof(bm), &bm))
               throw 3500;
            if(bm.bmWidth < cx ||
               bm.bmHeight  < cy)
            {
               bitmapA->CreateBitmap(cx + 100, cy + 100, 1, 24, NULL);
            }
         }

         ::ca::graphics_sp graphicsMem(get_app());
         graphicsMem->CreateCompatibleDC(pdc);
         ::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(bitmapA);
         graphicsMem->BitBlt(
            0, 0,
            cx, cy,
            pdc,
            x, y,
            SRCCOPY);
         BITMAP bm;
         if(!bitmapA->GetObject(sizeof(bm), &bm))
            throw 3500;

         primitive::memory memstorageA;


         BITMAPINFO bmi;
         bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
         bmi.bmiHeader.biWidth = bm.bmWidth ;
         bmi.bmiHeader.biHeight = -bm.bmHeight;
         bmi.bmiHeader.biPlanes = 1;
         bmi.bmiHeader.biBitCount = 24;
         bmi.bmiHeader.biCompression = BI_RGB;
         bmi.bmiHeader.biSizeImage = 0;
         bmi.bmiHeader.biXPelsPerMeter = 0;
         bmi.bmiHeader.biYPelsPerMeter = 0;
         bmi.bmiHeader.biClrUsed = 0;
         bmi.bmiHeader.biClrImportant = 0;
         int iLineBytes =  (bm.bmWidthBytes + 3) & ~3;
         try
         {
            memstorageA.allocate(iLineBytes * cy);
         }
         catch(memory_exception * pe)
         {
            delete pe;
            throw 4000;
         }

         LPVOID lpv = memstorageA.get_data();

         point pointViewport;
         pointViewport = pdc->GetViewportOrg();
         UINT uiStartScanLine = bm.bmHeight - y - cy - pointViewport.y;
         //UINT uiStartScanLine = bm.bmHeight - y - cy;
         UINT uiScanLines = cy;
         int xOffset = (x + pointViewport.x) * 3;
         //if(!GetDIBits(dcAux.get_os_data(), bitmapA, bm.bmHeight - cy, cy, lpv, &bmi, DIB_RGB_COLORS))
         //  throw 5000;
         int iLimitY = cy;
         if(!(iLimitY =
            GetDIBits(
            (HDC)graphicsMem->get_os_data(),
            (HBITMAP)bitmapA->get_os_data(),
            uiStartScanLine,
            uiScanLines,
            lpv,
            &bmi,
            DIB_RGB_COLORS)))
            return false;
         int iLimitX = cx;

         if(bm.bmWidth - x - pointViewport.x < iLimitX)
         {
            iLimitX = bm.bmWidth - x - pointViewport.x;
         }

         LPBYTE lpb;
         int i, j;
         for(i = 0; i < iLimitY; i++)
         {
            lpb = (LPBYTE) lpv + (iLineBytes * i) + xOffset;
            for(j = 0; j < iLimitX; j++)
            {
               *lpb++ = (BYTE) 255 - *lpb;
               *lpb++ = (BYTE) 255 - *lpb;
               *lpb++ = (BYTE) 255 - *lpb;
            }
         }
         if(!SetDIBits(
            (HDC)graphicsMem->get_os_data(),
            (HBITMAP)bitmapA->get_os_data(),
            uiStartScanLine,
            uiScanLines,
            lpv,
            &bmi,
            DIB_RGB_COLORS))
            throw 6000;
         pdc->BitBlt(x, y, cx, cy, graphicsMem, 0, 0, SRCCOPY);
         graphicsMem->SelectObject(pbmpMemOld);
         graphicsMem->DeleteDC();
         pdc->SetMapMode(iOriginalMapMode);
         return true;
      }
      catch(int)
      {
         pdc->SetMapMode(iOriginalMapMode);
         return false;
      }
   }
   else
   {
      try
      {

         // This is a primitive::memory device context
         BITMAP bm;
         if(!pbmp->GetObject(sizeof(bm), &bm))
            throw 3500;

         BITMAPINFO bmi;
         bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
         bmi.bmiHeader.biWidth = bm.bmWidth ;
         bmi.bmiHeader.biHeight = -bm.bmHeight;
         bmi.bmiHeader.biPlanes = 1;
         bmi.bmiHeader.biBitCount = 24;
         bmi.bmiHeader.biCompression = BI_RGB;
         bmi.bmiHeader.biSizeImage = 0;
         bmi.bmiHeader.biXPelsPerMeter = 0;
         bmi.bmiHeader.biYPelsPerMeter = 0;
         bmi.bmiHeader.biClrUsed = 0;
         bmi.bmiHeader.biClrImportant = 0;
         int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;

         primitive::memory memstorageA;
         try
         {
            memstorageA.allocate(iLineBytes * cy);
         }
         catch(memory_exception * pe)
         {
            delete pe;
            throw 4000;
         }
         LPVOID lpv = memstorageA.get_data();
         point pointViewport = pdc->GetViewportOrg();
         UINT uiStartScanLine = bm.bmHeight - y - cy - pointViewport.y;
         //UINT uiStartScanLine = bm.bmHeight - y - cy;
         UINT uiScanLines = cy;
         int xOffset = (x + pointViewport.x) * 3;


         //int xOffset = (x) * 3;
         int iLimitY = cy;
         if(!(iLimitY =
            GetDIBits(
            (HDC)pdc->get_os_data(),
            (HBITMAP) pbmp->get_os_data(),
            uiStartScanLine,
            uiScanLines,
            lpv,
            &bmi,
            DIB_RGB_COLORS)))
            throw 5000;
         int iLimitX = cx;


         if(bm.bmWidth - x - pointViewport.x < iLimitX)
         {
            iLimitX = bm.bmWidth - x - pointViewport.x;
         }

         LPBYTE lpb;
         int i, j;
         for(i = 0; i < iLimitY; i++)
         {
            lpb = (LPBYTE) lpv + (iLineBytes * i) + xOffset;
            if(lpb < lpv)
               continue;
            for(j = 0; j < iLimitX; j++)
            {
               *lpb++ = (BYTE) 255 - *lpb ;
               *lpb++ = (BYTE) 255 - *lpb;
               *lpb++ = (BYTE) 255 - *lpb;
            }
         }

         if(!SetDIBits((HDC)pdc->get_os_data(),
            (HBITMAP) pbmp->get_os_data(),
            uiStartScanLine, uiScanLines,
            lpv, &bmi, DIB_RGB_COLORS))
            throw 6000;
      }
      catch(int)
      {
         pdc->SetMapMode(iOriginalMapMode);
         return false;
      }
   }
   pdc->SetMapMode(iOriginalMapMode);
   return true;*/
}

/*bool imaging::allocate(int iSize)
{
if(iSize > m_iSize)
{
m_lpVoid = malloc(iSize);
if(m_lpVoid == NULL)
{
return false;
}
else
{
m_iSize = iSize;
}
}
return true;

}*/

void imaging::SaveJpeg(const char * lpcszFile, ::ca::bitmap_sp pbitmap)
{
   FIBITMAP * fi= HBITMAPtoFI(pbitmap);
   fi = FreeImage_ConvertTo24Bits(fi);
   if (FreeImage_Save(FIF_JPEG, fi, lpcszFile, JPEG_QUALITYBAD))
   {
      //
   }
   FreeImage_Unload(fi);
}

void imaging::SavePng(const char * lpcszFile, ::ca::bitmap_sp pbitmap)
{
   FIBITMAP * fi= HBITMAPtoFI(pbitmap);
   if (FreeImage_Save(FIF_PNG, fi, lpcszFile, 0))
   {
      //
   }
   FreeImage_Unload(fi);
}

void imaging::SavePng(const char * lpcszFile, FIBITMAP *dib, bool bUnload)
{
   if (FreeImage_Save(FIF_PNG, dib, lpcszFile, 0)) {
      //
   }
   if(bUnload)
   {
      FreeImage_Unload(dib);
   }
}

FIBITMAP * imaging::HBITMAPtoFI(::ca::bitmap_sp pbitmap)
{
   if(pbitmap == NULL)
      return NULL;

   // ...
   // the following code assumes that you have a valid HBITMAP loaded into the primitive::memory
   BITMAP bm;
   throw not_implemented_exception();
//   pbitmap->GetObject(sizeof(BITMAP), (char *) &bm);
   if(bm.bmWidth <= 0 || bm.bmHeight <= 0)
      return NULL;
   FIBITMAP * fi = FreeImage_Allocate(bm.bmWidth, bm.bmHeight, bm.bmBitsPixel);
   // The GetDIBits function clears the biClrUsed and biClrImportant BITMAPINFO members (dont't know why)
   // So we save these infos below. This is needed for palettized images only.
   int nColors = FreeImage_GetColorsUsed(fi);
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);
   GetDIBits((HDC)spgraphics->get_os_data(), (HBITMAP) pbitmap->get_os_data(), 0, FreeImage_GetHeight(fi),
      FreeImage_GetBits(fi), FreeImage_GetInfo(fi), DIB_RGB_COLORS);



   // restore BITMAPINFO members
   FreeImage_GetInfoHeader(fi)->biClrUsed = nColors;
   FreeImage_GetInfoHeader(fi)->biClrImportant = nColors;

   return fi;
}



::ca::bitmap_sp imaging::FItoHBITMAP(FIBITMAP * pfibitmap, bool bUnloadFI)
{
   if(pfibitmap== NULL)
      return NULL;

   BITMAPINFO * pbi = FreeImage_GetInfo(pfibitmap);
   void * pData = FreeImage_GetBits(pfibitmap);


   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);

   ::ca::dib_sp dibSource(get_app());
   dibSource->create(pbi->bmiHeader.biWidth, pbi->bmiHeader.biHeight);

   dibSource->dc_select(false);

   if(pbi->bmiHeader.biHeight != SetDIBits(
      (HDC)spgraphics->get_os_data(),
      (HBITMAP) dibSource->get_bitmap()->get_os_data(),
      0,
      pbi->bmiHeader.biHeight,
      pData,
      pbi,
      DIB_RGB_COLORS))
   {
      if(bUnloadFI)
      {
         FreeImage_Unload(pfibitmap);
      }
      return NULL;
   }

   if(bUnloadFI)
   {
      FreeImage_Unload(pfibitmap);
   }


   return dibSource->detach_bitmap();
}

/*HBITMAP imaging::LoadImageSync(const char * lpcszImageFilePath)
{
string str;
gen::international::UTF8ToUnicode(str, lpcszImageFilePath);
return LoadImageSync(str);
}*/

::ca::bitmap_sp imaging::LoadImageSync(const char * lpcszImageFilePath, ::ca::application * papp)
{

   FIBITMAP * pfi = imaging::LoadImageFile(lpcszImageFilePath, papp);

   if(pfi == NULL)
      return NULL;

   return FItoHBITMAP(pfi, true);

}

bool imaging::color_blend_3dRect(::ca::graphics *pdc, LPCRECT lpcrect, COLORREF crTopLeft, BYTE bAlphaTopLeft, COLORREF crBottomRight, BYTE bAlphaBottomRight)
{
   rect rect(lpcrect);
   int x = rect.left;
   int y = rect.top;
   int cx = rect.width();
   int cy = rect.height();
   color_blend(pdc, point(x            , y         ), size(cx - 1 , 1      ), crTopLeft      , bAlphaTopLeft);
   color_blend(pdc, point(x            , y         ), size(1      , cy - 1 ), crTopLeft      , bAlphaTopLeft);
   color_blend(pdc, point(x + cx - 1   , y + 1     ), size(1      , cy - 1 ), crBottomRight  , bAlphaBottomRight);
   color_blend(pdc, point(x + 1        , y + cy - 1), size(cx - 1 , 1      ), crBottomRight  , bAlphaBottomRight);
   return true;
}

bool imaging::clip_color_blend(
                             ::ca::graphics * pdc,
                             LPCRECT lpcrect,
                             COLORREF cr,
                             BYTE alpha)
{
   class rect rect(lpcrect);
   return clip_color_blend(
      pdc,
      rect.top_left(),
      rect.size(),
      cr,
      alpha);
}


bool imaging::clip_color_blend(
                             ::ca::graphics * pdc,
                             point pt,
                             size size,
                             COLORREF cr,
                             BYTE bA)
{

   ::ca::bitmap_sp bitmapA(get_app());
   ::ca::graphics_sp graphicsMem(get_app());
   graphicsMem->CreateCompatibleDC(pdc);
   bitmapA->CreateCompatibleBitmap(pdc, size.cx, size.cy);
   ::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(bitmapA);
   graphicsMem->SetMapMode(MM_TEXT);
   graphicsMem->FillSolidRect(
      0, 0,
      size.cx, size.cy,
      cr);


   BLENDFUNCTION bf;
   bf.BlendOp = AC_SRC_OVER;
   bf.BlendFlags = 0;
   bf.SourceConstantAlpha = bA;  // half of 0xff = 50% transparency
   bf.AlphaFormat = 0;             // ignore source alpha channel

   BOOL bOk ;
   bOk = pdc->alpha_blend(pt, size, graphicsMem, bf);

   /*bOk = pdc->BitBlt(
   x, y, cx, cy,
   graphicsMem->
   0, 0,
   SRCCOPY);*/


   graphicsMem->SelectObject(pbmpMemOld);
   graphicsMem->DeleteDC();

   return bOk != 0;

   return true;
}
bool imaging::clip_color_blend(
                             ::ca::graphics * pdc,
                             LPCRECT lpcrect,
                             COLORREF cr,
                             BYTE alpha,
                             ::ca::region * prgnClip)
{
   class rect rect(lpcrect);
   return clip_color_blend(
      pdc,
      rect.top_left(),
      rect.size(),
      cr,
      alpha,
      prgnClip);
}


bool imaging::clip_color_blend(
                             ::ca::graphics * pdc,
                             point pt,
                             size size,
                             COLORREF cr,
                             BYTE bA,
                             ::ca::region * prgnClip)
{
   ::ca::bitmap_sp bitmapA(get_app());

   BITMAP   bm;

   rect rect(pt, size);

   point ptViewport = pdc->GetViewportOrg();

   rect.offset(ptViewport);

   ClipSave(
      pdc,
      bitmapA,
      NULL,
      &bm,
      rect,
      prgnClip);

   bool bOk = color_blend(pdc, pt, size, cr, bA);

   ClipRestore(
      pdc,
      bitmapA,
      NULL,
      &bm,
      rect,
      prgnClip);

   pdc->SetViewportOrg(ptViewport);

   return bOk;
}

bool imaging::color_blend(
                         ::ca::graphics * pdc,
                         const __rect64 * lpcrect,
                         COLORREF cr,
                         BYTE alpha)
{
   rect rect32;
   ::copy(rect32, lpcrect);
   return color_blend(pdc, rect32, cr, alpha);
}


bool imaging::color_blend(
                         ::ca::graphics * pdc,
                         LPCRECT lpcrect,
                         COLORREF cr,
                         BYTE alpha)
{
   class rect rect(lpcrect);
   return color_blend(
      pdc,
      rect.top_left(),
      rect.size(),
      cr,
      alpha);
}

bool imaging::color_blend(
                         ::ca::graphics * pdc,
                         LPCRECT lpcrect,
                         COLORREF cr,
                         BYTE alpha,
                         ::ca::dib * pdibWork)
{
   class rect rect(lpcrect);
   return color_blend(
      pdc,
      rect.top_left(),
      rect.size(),
      cr,
      alpha,
      pdibWork);
}

bool imaging::color_blend(
                         ::ca::graphics * pdc,
                         point pt,
                         size size,
                         COLORREF cr,
                         BYTE bA)
{
   ::ca::dib_sp spdib(get_app());
   return color_blend(pdc, pt, size, cr, bA, spdib);
}

bool imaging::color_blend(
                         ::ca::graphics * pdc,
                         int x, int y,
                         int cx, int cy,
                         COLORREF cr,
                         BYTE bA)
{

   return color_blend(pdc, point(x, y), size(cx, cy), cr, bA);
}

bool imaging::color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr, BYTE bA, ::ca::dib * pdibWork)
{


   pdc->FillSolidRect(pt.x, pt.y, size.cx, size.cy, (cr & 0x00ffffff) | (bA << 24));

   return true;

   if(pdibWork == NULL)
   {
      return false;
   }

   if(!pdibWork->create(size))
      return false;

   pdibWork->get_graphics()->SetMapMode(MM_TEXT);
   pdibWork->get_graphics()->FillSolidRect(0, 0, size.cx, size.cy, cr);

   HBITMAP hbitmapDest = (HBITMAP) ::GetCurrentObject((HDC)pdc->get_os_data(), OBJ_BITMAP);
   BITMAP bmDest;
   ::GetObject(hbitmapDest, sizeof(bmDest), &bmDest);
   POINT ptViewportDest;
   ::GetViewportOrgEx((HDC)pdc->get_os_data(), &ptViewportDest);
   ::GetMapMode((HDC)pdc->get_os_data());

   ::ca::bitmap * pbitmapSrc = pdibWork->get_bitmap();
   class size sizeSrc = pbitmapSrc->size();
   POINT ptViewportSrc;
   ptViewportSrc = pdibWork->get_graphics()->GetViewportOrg();

   BLENDFUNCTION bf;
   bf.BlendOp              = AC_SRC_OVER;
   bf.BlendFlags           = 0;
   bf.SourceConstantAlpha  = bA;
   bf.AlphaFormat          = 0; // ignore alpha channel

   BOOL bOk ;
   try
   {
      bOk = pdc->alpha_blend(pt, size, pdibWork->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }


   return bOk != 0;

}



bool imaging::prepare_blend(::ca::dib * pdib, LPCRECT lpcrect, COLORREF cr, BYTE bA, ::ca::dib * pdibWork)
{
   rect rect(lpcrect);
   return prepare_blend(pdib, rect.top_left(), rect.size(), cr, bA, pdibWork);
}

bool imaging::prepare_blend(::ca::dib * pdib, point pt, size size, COLORREF cr, BYTE bA, ::ca::dib * pdibWork)
{

   if(pdibWork == NULL)
   {
      return false;
   }

   if(!pdibWork->create(size))
      return false;

   pdibWork->get_graphics()->SetMapMode(MM_TEXT);
   pdibWork->get_graphics()->FillSolidRect(0, 0, size.cx, size.cy, cr);

   //::GdiFlush();


/*   HBITMAP hbitmapDest = (HBITMAP) ::GetCurrentObject((HDC)pdc->get_os_data(), OBJ_BITMAP);
   BITMAP bmDest;
   ::GetObject(hbitmapDest, sizeof(bmDest), &bmDest);
   POINT ptViewportDest;
   ::GetViewportOrgEx((HDC)pdc->get_os_data(), &ptViewportDest);
   ::GetMapMode((HDC)pdc->get_os_data());


   ::ca::bitmap * pbitmapSrc = pdibWork->get_bitmap();
   BITMAP bmSrc;
   pbitmapSrc->GetObject(sizeof(bmSrc), &bmSrc);
   POINT ptViewportSrc;
   ptViewportSrc = pdibWork->get_graphics()->GetViewportOrg();*/
   //int nMapModeSrc = pdibWork->get_graphics()->GetMapMode();

   // MM_TEXT 1


   //::ca::dib_sp dib(get_app());

   //dib->get_graphics()->BitBlt(0, 0, size.cx, size.cy, pdc, pt.x, pt.y, SRCCOPY);


   BLENDFUNCTION bf;
   bf.BlendOp              = AC_SRC_OVER;
   bf.BlendFlags           = 0;
   bf.SourceConstantAlpha  = bA;
   bf.AlphaFormat          = AC_SRC_ALPHA; // ignore alpha channel

   //pdibWork->fill_channel(bA, visual::rgba::channel_alpha);
   pdibWork->mult_alpha(NULL);

   BOOL bOk ;
   try
   {
      bOk = pdib->get_graphics()->alpha_blend(pt, size, pdibWork->get_graphics(), bf);
   }
   catch(...)
   {
      bOk = false;
   }

   pdib->channel_from(visual::rgba::channel_alpha, pdibWork);

   //dib->mult_alpha(NULL);




   return bOk != 0;

}

bool imaging::ClipSave(
                       ::ca::graphics * pdc,
                       ::ca::bitmap * pbitmap,
                       ::ca::bitmap * pbitmapOld,
                       BITMAP * pbmp,
                       LPCRECT lpcrect,
                       ::ca::region * prgnClip)
{

   if(pdc == NULL)
      return false;

   if(pbitmap == NULL)
      return false;

   if(prgnClip == NULL)
      return false;


   rect rectClipBox;

   prgnClip->GetRgnBox(rectClipBox);

   rect rectUpdate;

   rectUpdate.intersect(rectClipBox, lpcrect);

   //   if(!rectUpdate.is_empty())
   //   {
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(pdc);
   spgraphics->SetViewportOrg(pdc->GetViewportOrg());
   if(!CreateBitmap(
      spgraphics,
      pdc,
      pbitmap,
      pbitmapOld,
      pbmp,
      rectUpdate.right,
      rectUpdate.bottom))
   {
      return false;
   }
   ::ca::region rgnUpdate;
   rgnUpdate.CreateRectRgnIndirect(lpcrect);
   rgnUpdate.CombineRgn(&rgnUpdate, prgnClip, RGN_DIFF);
   rgnUpdate.GetRgnBox(rectUpdate);
   spgraphics->SelectObject(pbitmap);
   spgraphics->SelectClipRgn(&rgnUpdate);
   if(!spgraphics->BitBlt(
      rectUpdate.left,
      rectUpdate.top,
      rectUpdate.width(),
      rectUpdate.height(),
      pdc,
      rectUpdate.left,
      rectUpdate.top,
      SRCCOPY))
      return false;
   //   }
   return true;

   /*   if(pdc == NULL)
   return false;

   if(pbitmap == NULL)
   return false;

   if(prgnClip == NULL)
   return false;


   rect rectClipBox;

   prgnClip->GetRgnBox(rectClipBox);

   //   ::ca::region rgnUpdate;
   //   rgnUpdate.CreateRectRgnIndirect(lpcrect);
   //   rgnUpdate.CombineRgn(&rgnUpdate, prgnClip, RGN_DIFF);
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(pdc);
   spgraphics->SetViewportOrg(pdc->GetViewportOrg());

   if(!CreateBitmap(
   &spgraphics,
   pdc,
   pbitmapOld,
   pbitmap,
   pbmp,
   lpcrect->right,
   lpcrect->bottom))
   {
   return false;
   }
   //      spgraphics->SelectClipRgn(&rgnUpdate);
   if(!spgraphics->BitBlt(
   lpcrect->left,
   lpcrect->top,
   lpcrect->right - lpcrect->left,
   lpcrect->bottom - lpcrect->top,
   pdc,
   lpcrect->left,
   lpcrect->top,
   SRCCOPY))
   {
   return false;
   }
   else
   {
   return true;
   }*/
}

bool imaging::ClipRestore(
                          ::ca::graphics * pdc,
                          ::ca::bitmap * pbitmap,
                          ::ca::bitmap * pbitmapOld,
                          BITMAP * pbmp,
                          LPCRECT lpcrect,
                          ::ca::region * prgnClip)
{
   UNREFERENCED_PARAMETER(pbitmapOld);
   UNREFERENCED_PARAMETER(pbmp);
   if(pdc == NULL)
      return false;

   if(pbitmap == NULL)
      return false;

   rect rectClipBox;

   prgnClip->GetRgnBox(rectClipBox);

   rect rectUpdate;

   rectUpdate.intersect(rectClipBox, lpcrect);

   if(!rectUpdate.is_empty())
   {
      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(pdc);
      spgraphics->SetViewportOrg(pdc->GetViewportOrg());
      spgraphics->SelectObject(pbitmap);
      ::ca::region_sp rgnClip(get_app());
      rgnClip->CreateRectRgn(0, 0, 0, 0);
      int iClip = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnClip->get_os_data());
      ::ca::region_sp rgnUpdate(get_app());
      rgnUpdate->CreateRectRgnIndirect(lpcrect);
      rgnUpdate->CombineRgn(rgnUpdate, prgnClip, RGN_DIFF);
      pdc->SelectClipRgn(rgnUpdate);
      rgnUpdate->GetRgnBox(rectUpdate);
      bool bOk;
      bOk = pdc->BitBlt(
         rectUpdate.left,
         rectUpdate.top,
         rectUpdate.width(),
         rectUpdate.height(),
         spgraphics,
         rectUpdate.left,
         rectUpdate.top,
         SRCCOPY) != 0;



      if(iClip == 1)
      {
         pdc->SelectClipRgn(rgnClip);
      }
      else
         pdc->SelectClipRgn(NULL);
      return bOk;
   }
   return true;

   /*   if(pdc == NULL)
   return false;

   if(pbitmap == NULL)
   return false;

   rect rectClipBox;

   prgnClip->GetRgnBox(rectClipBox);

   rect rectUpdate(lpcrect);

   //rectUpdate.intersect(rectClipBox, lpcrect);

   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(pdc);
   spgraphics->SetViewportOrg(pdc->GetViewportOrg());
   spgraphics->SelectObject(pbitmap);
   ::ca::region rgnClip;
   rgnClip.CreateRectRgn(0, 0, 0, 0);
   int iClip = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnClip);
   rect rC;
   prgnClip->GetRgnBox(rC);
   ::ca::region rgnUpdate;
   rgnUpdate.CreateRectRgnIndirect(rectUpdate);
   rgnUpdate.CombineRgn(&rgnUpdate, prgnClip, RGN_DIFF);
   pdc->SelectClipRgn(&rgnUpdate);
   rect r1;
   rgnUpdate.GetRgnBox(r1);
   bool bOk;
   bOk = pdc->BitBlt(
   rectUpdate.left,
   rectUpdate.top,
   rectUpdate.width(),
   rectUpdate.height(),
   &spgraphics,
   rectUpdate.left,
   rectUpdate.top,
   SRCCOPY) != 0;



   if(iClip == 1)
   {
   pdc->SelectClipRgn(&rgnClip);
   }
   else
   pdc->SelectClipRgn(NULL);
   return bOk;*/
}


bool imaging::ClipSave(
                       ::ca::graphics * pdc,
                       ::ca::bitmap * pbitmap,
                       ::ca::bitmap * pbitmapOld,
                       BITMAP * pbmp,
                       LPCRECT lpcrect)
{

   if(pdc == NULL)
      return false;

   if(pbitmap == NULL)
      return false;

   ::ca::region_sp rgnClip(get_app());

   rgnClip->CreateRectRgn(0, 0, 0, 0);

   if(::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnClip->get_os_data()) == 1)
   {
      return ClipSave(
         pdc,
         pbitmap,
         pbitmapOld,
         pbmp,
         lpcrect,
         rgnClip);
   }
   return true;
}

bool imaging::ClipRestore(
                          ::ca::graphics * pdc,
                          ::ca::bitmap * pbitmap,
                          ::ca::bitmap * pbitmapOld,
                          BITMAP * pbmp,
                          LPCRECT lpcrect)
{
   if(pdc == NULL)
      return false;

   if(pbitmap == NULL)
      return false;

   ::ca::region_sp rgnClip(get_app());

   rgnClip->CreateRectRgn(0, 0, 0, 0);

   if(::GetClipRgn((HDC)pdc->get_os_data(), (HRGN) rgnClip->get_os_data()) == 1)
   {
      return ClipRestore(
         pdc,
         pbitmap,
         pbitmapOld,
         pbmp,
         lpcrect,
         rgnClip);
   }
   return true;
}

bool imaging::CreateBitmap(
                           ::ca::graphics * pdc,
                           ::ca::graphics * pdcScreen,
                           ::ca::bitmap * pbitmap,
                           ::ca::bitmap * pbitmapOld,
                           BITMAP * pbmp,
                           int cx,
                           int cy)
{
   int cxout = cx;
   int cyout = cy;

   pdc->SelectObject(pbitmapOld);
   bool bCreate = true;
   if(pbitmap->get_os_data() != NULL)
   {
      class size size = pbitmap->get_size();
      if(size.cx >= cx && size.cy >= cy)
      {
         bCreate = false;
      }

   }
   if(bCreate)
   {
      if(!pbitmap->CreateCompatibleBitmap(pdcScreen, cxout, cyout))
      {
         return false;
      }
   }
   if(!pdc->SelectObject(pbitmap))
   {
      if(!pbitmap->CreateCompatibleBitmap(pdcScreen, cxout, cyout))
      {
         return false;
      }
      if(!pdc->SelectObject(pbitmap))
      {
         return false;
      }
   }
   if(bCreate)
   {
      pdc->FillSolidRect(rect(0, 0, cxout, cyout), RGB (0, 0, 0));
   }
   return true;
}


bool imaging::CreateBitmap(::ca::graphics *pdc, ::ca::bitmap * pbitmapOld, ::ca::bitmap *pbitmap, BITMAP *pbmp, int cx, int cy)
{
   int cxout = cx;
   int cyout = cy;

   pdc->SelectObject(pbitmapOld);
   bool bCreate = true;
   if(pbitmap->get_os_data() != NULL)
   {
      class size size = pbitmap->get_size();
      if(size.cx >= cx && size.cy >= cy)
      {
         bCreate = false;
      }

   }
   if(bCreate)
   {
      if(!pbitmap->CreateCompatibleBitmap(pdc, cxout, cyout))
      {
         return false;
      }
   }
   if(!pdc->SelectObject(pbitmap))
   {
      if(!pbitmap->CreateCompatibleBitmap(pdc, cxout, cyout))
      {
         return false;
      }
      if(!pdc->SelectObject(pbitmap))
      {
         return false;
      }
   }
   if(bCreate)
   {
      pdc->FillSolidRect(rect(0, 0, cxout, cyout), RGB (255, 196, 255));
   }
   return true;
}

/*
HBITMAP
imaging::LoadSysColorBitmap(::ca::graphics * pdcCompatible, HINSTANCE hInst, HRSRC hRsrc, BOOL bMono)
{
   HGLOBAL hglb;
   if ((hglb = LoadResource(hInst, hRsrc)) == NULL)
      return NULL;

   LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
   if (lpBitmap == NULL)
      return NULL;

   // make copy of BITMAPINFOHEADER so we can modify the color table
   const int nColorTableSize = 1 << lpBitmap->biBitCount;
   UINT nSize = lpBitmap->biSize + nColorTableSize * sizeof(RGBQUAD);
   LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER)::malloc(nSize);
   if (lpBitmapInfo == NULL)
      return NULL;
   memcpy(lpBitmapInfo, lpBitmap, nSize);

   // color table is in RGBQUAD DIB format
   DWORD* pColorTable =
      (DWORD*)(((LPBYTE)lpBitmapInfo) + (UINT)lpBitmapInfo->biSize);

   for (int iColor = 0; iColor < nColorTableSize; iColor++)
   {
      // look for matching RGBQUAD color in original
      for (int i = 0; s_psyscolormap[i].iSysColorTo != 0x80000000; i++)
      {
         if (pColorTable[iColor] == s_psyscolormap[i].rgbqFrom)
         {
            if (bMono)
            {
               // all colors except text become white
               if (s_psyscolormap[i].iSysColorTo != COLOR_BTNTEXT)
                  pColorTable[iColor] = RGB_TO_RGBQUAD(255, 255, 255);
            }
            else
               pColorTable[iColor] =
               CLR_TO_RGBQUAD(::GetSysColor(s_psyscolormap[i].iSysColorTo));
            break;
         }
      }
   }

   int nWidth = (int)lpBitmapInfo->biWidth;
   int nHeight = (int)lpBitmapInfo->biHeight;
   HDC hDCScreen = pdcCompatible->get_os_data();
   HBITMAP hbm = ::CreateCompatibleBitmap(hDCScreen, nWidth, nHeight);

   if (hbm != NULL)
   {
      HDC hDCGlyphs = ::CreateCompatibleDC(hDCScreen);
      HBITMAP hbmOld = (HBITMAP)::SelectObject(hDCGlyphs, hbm);

      LPBYTE lpBits;
      lpBits = (LPBYTE)(lpBitmap + 1);
      lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);

      StretchDIBits(hDCGlyphs, 0, 0, nWidth, nHeight, 0, 0, nWidth, nHeight,
         lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
      SelectObject(hDCGlyphs, hbmOld);
      ::DeleteDC(hDCGlyphs);
   }
   //   ::ReleaseDC(NULL, hDCScreen);

   // free copy of bitmap info struct and resource itself
   ::free(lpBitmapInfo);
   ::FreeResource(hglb);

   return hbm;
}
*/
/*bool imaging::CreateBitmap(::ca::graphics *pdc, ::ca::bitmap *pbitmapOld, ::ca::bitmap *pbitmap, BITMAP * pbmp, int cx, int cy)
{
int cxout = cx + 30;
int cyout = cy + 30;

pdc->SelectObject(pbitmapOld);
bool bCreate = true;
if(pbitmap->m_hObject != NULL)
{
if(!pbitmap->GetBitmap(pbmp))
{
return false;
}
if(pbmp->bmWidth >= cx &&
pbmp->bmHeight >= cy)
{
bCreate = false;
}

}
if(bCreate)
{
pbitmap->delete_object();
if(!pbitmap->CreateCompatibleBitmap(&m_dcScreen, cxout, cyout))
{
return false;
}
}
if(!pdc->SelectObject(pbitmap))
{
return false;
}
if(bCreate)
{
pdc->FillSolidRect(rect(0, 0, cxout, cyout), RGB (0, 0, 0));
}
return true;

}

*/

// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
//BImage a;




void fastblur(::ca::dib * pimg, int radius)
{
   if(radius < 1)
   {
      return;
   }
  int w=pimg->width();
  int h=pimg->height();
  int wm=w-1;
  int hm=h-1;
  int wh=w*h;
  int div=radius+radius+1;
  int_array iaA;
  iaA.set_size(wh);
  int * a = iaA.get_data();
  int_array iaR;
  iaR.set_size(wh);
  int * r = iaR.get_data();
  int_array iaG;
  iaG.set_size(wh);
  int * g = iaG.get_data();
  int_array iaB;
  iaB.set_size(wh);
  int * b = iaB.get_data();
  int asum, rsum,gsum,bsum,x,y,i,yp,yi,yw;
  int p;
  int p1;
  int p2;
  int_array iaVmin;
  iaVmin.set_size(max(w,h));
  int * vmin = iaVmin.get_data();
  int_array iaVmax;
  iaVmax.set_size(max(w,h));
  int * vmax = iaVmax.get_data();
  int * pix=(int *) pimg->get_data();
  int_array iaDv;
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



bool imaging::blur(::ca::graphics *pdcDst, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iRadius)
{
   if(size.cx <= 0 || size.cy <= 0)
      return true;

   ::ca::dib_sp dibDst(get_app());

   if(!dibDst->create(size))
      return false;

   dibDst->get_graphics()->set_alpha_mode(::ca::alpha_mode_set);
   dibDst->get_graphics()->FillSolidRect(0, 0, size.cx, size.cy, ARGB(0, 0, 0, 0));
   dibDst->get_graphics()->set_alpha_mode(::ca::alpha_mode_blend);
/*   ::ca::dib_sp dibSrc(get_app());

   if(!dibSrc->create(size))
      return false;*/

   if(iRadius < 0)
   {
      if(!dibDst->from(null_point(), pdcSrc, ptSrc, size))
         return false;
      fastblur(dibDst, max(3, -iRadius));
   }
   else
   {
      if(!dibDst->from(null_point(), pdcSrc, ptSrc, size))
         return false;
      fastblur(dibDst, max(3, iRadius));
   }

   
   dibDst->to(pdcDst, ptDst, size);

   return true;

}

void imaging::blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iRadius)
{
   int iFilterWidth = iRadius * 2 + 1;
   int iFilterHeight = iRadius * 2 + 1;
   int divisor = iFilterWidth * iFilterHeight;
   BYTE *lpbSource;
   BYTE *lpwDestination;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpFilter;
   BYTE * pFilter = new BYTE[iFilterHeight *iFilterWidth];
   memset(pFilter, 1, iFilterHeight * iFilterWidth);

   LPBYTE lpbSrc = (LPBYTE) pdibSrc->get_data();
   LPBYTE lpbDst = (LPBYTE) pdibDst->get_data();
   int cx = pdibSrc->width();
   int cy = pdibSrc->height();
   int wSrc = cx * 4;
   int wDest = cx * 4;
   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterWidth;
//   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 4;
//   int max3x2 = (maxx1 - iFilterHeight) * 4;
//   int max3x3 = (maxx1 - iFilterHeight / 2) * 4;
   //int bm3Width = (cy * 3 + 3) & ~0x3L;
//   int w = cx * 3;
   //   memcpy(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   memcpy(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(int y = 0; y < cy; y++)
   {
   lpbSource = lpbSrc + wSrc * y;
   lpwDestination = lpbDst + wDest * y;
   for(int x = 0; x < w; x++)
   {
   *lpwDestination = *lpbSource;
   lpwDestination++;
   lpbSource++;
   }
   }*/
   DWORD dwR;
   DWORD dwG;
   DWORD dwB;
   DWORD dwA;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   yLBound[0] = 0;
   yUBound[0] = iFilterWidth / 2;
   xLBound[0] = 0;
   xUBound[0] = max3x1;

   // left
   yLBound[1] = iFilterWidth / 2;
   yUBound[1] = maxy1 - iFilterWidth / 2;
   xLBound[1] = 0;
   xUBound[1] = iFilterWidth / 2;

   // right
   yLBound[2] = iFilterWidth / 2;
   yUBound[2] = maxy1- iFilterWidth / 2;
   xLBound[2] = max3x1 - iFilterWidth / 2;
   xUBound[2] = max3x1;

   // bottom
   yLBound[3] = maxy1 - iFilterWidth / 2;
   yUBound[3] = maxy1;
   xLBound[3] = 0;
   xUBound[3] = max3x1;

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLBound[i];
   int yU = yUBound[i];
   int xL = xLBound[i];
   int xU = xUBound[i];
   for(int y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   lpbSource = lpbSrc + (wSrc * max((y1 - iFilterWidth / 2), 0));
   lpwDestination = lpbDst + (wDest  * y1);
   for(int x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   lpbSource_1 = lpbSource + ((max(x1 - iFilterWidth / 2 * 3, 0)));
   lpFilter = pFilter;
   //            lpConv = pConv;

   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   lpbSource_2 = lpbSource_1 + (wSrc * y2);
   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *lpbSource_2++ * *lpFilter;
   dwG += *lpbSource_2++ * *lpFilter;
   dwB += *lpbSource_2++ * *lpFilter++;

   }
   }
   lpwDestination_1 = lpwDestination + x1;
   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   lpwDestination_1[0] = max(0, min(dwR, 255));
   lpwDestination_1[1] = max(0, min(dwG, 255));
   lpwDestination_1[2] = min(0, min(dwB, 255));
   }
   else
   {
   lpwDestination_1[0] = dwR / divisor;
   lpwDestination_1[1] = dwG / divisor;
   lpwDestination_1[2] = dwB / divisor;
   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );

   for(; y1 < yU;)
   {
      lpbSource = lpbSrc + (wSrc * y2);

      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      lpwDestination = lpbDst + (wDest  * y1) + x1;
      for(; x1 < xU;)
      {
         lpbSource_1 = lpbSource + x2;
         lpFilter = pFilter;

         dwR = 0;
         dwG = 0;
         dwB = 0;
         dwA = 0;
         for(int yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwR += *lpbSource_2++ * *lpFilter;
               dwG += *lpbSource_2++ * *lpFilter;
               dwB += *lpbSource_2++ * *lpFilter;
               dwA += *lpbSource_2++ * *lpFilter;

            }
         }


         *lpwDestination++ = (unsigned char) (dwR / divisor);
         *lpwDestination++ = (unsigned char) (dwG / divisor);
         *lpwDestination++ = (unsigned char) (dwB / divisor);
         *lpwDestination++ = (unsigned char) (dwA / divisor);
         x1 += 3;
         x2 += 3;
      }
      y1++;
      y2++;
   }

   delete pFilter;
}


void imaging::blur_32CC_r2(::ca::dib * pdibDst, ::ca::dib * pdibSrc)
{
   LPBYTE lpbSrc = (LPBYTE) pdibSrc->get_data();
   LPBYTE lpbDst = (LPBYTE) pdibDst->get_data();
   int cx = pdibSrc->width();
   int cy = pdibSrc->height();
   int wSrc = cx * 4;
   int wDest = cx * 4;

   BYTE *lpbSource;
   BYTE *lpwDestination;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2[5];


   if(cx <= 0)
      return;
   if(cy <= 0)
      return;

   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - 5;
//   int maxy3 = cy - 2;
   int max3x1 = maxx1 * 4;
//   int max3x2 = (maxx1 - 5) * 4;
///   int max3x3 = (maxx1 - 2) * 4;
//   int w = cx * 3;
   DWORD dwR;
   DWORD dwG;
   DWORD dwB;
   DWORD dwA;

   int yL = 2;
   int yU = maxy1 - 2;
   int xL = 8;
   int xU = max3x1 - 8;


   int y1 = 2;
   int y2 = yL - 2;
   int x1;
   int x2;

   for(; y1 < yU;)
   {
      lpbSource = lpbSrc + (wSrc * y2);

      x1 = xL;
      x2 = xL - 8;
      lpwDestination = lpbDst + (wDest  * y1) + x1;
      for(; x1 < xU;)
      {
         lpbSource_1 = lpbSource + x2;
         dwR = 0;
         dwG = 0;
         dwB = 0;
         dwA = 0;
         lpbSource_2[0] = lpbSource_1;
         lpbSource_2[1] = lpbSource_1 + wSrc;
         lpbSource_2[2] = lpbSource_1 + wSrc * 2;
         lpbSource_2[3] = lpbSource_1 + wSrc * 3;
         lpbSource_2[4] = lpbSource_1 + wSrc * 4;

         // red
         lpwDestination[0] =
         (  lpbSource_2[0][0] + lpbSource_2[0][4] + lpbSource_2[0][8] + lpbSource_2[0][12] + lpbSource_2[0][16]
         +  lpbSource_2[1][0] + lpbSource_2[1][4] + lpbSource_2[1][8] + lpbSource_2[1][12] + lpbSource_2[1][16]
         +  lpbSource_2[2][0] + lpbSource_2[2][4] + lpbSource_2[2][8] + lpbSource_2[2][12] + lpbSource_2[2][16]
         +  lpbSource_2[3][0] + lpbSource_2[3][4] + lpbSource_2[3][8] + lpbSource_2[3][12] + lpbSource_2[3][16]
         +  lpbSource_2[4][0] + lpbSource_2[4][4] + lpbSource_2[4][8] + lpbSource_2[4][12] + lpbSource_2[4][16]
         ) / 25;

         // green
         lpwDestination[1] =
         (  lpbSource_2[0][1] + lpbSource_2[0][5] + lpbSource_2[0][9] + lpbSource_2[0][13] + lpbSource_2[0][17]
         +  lpbSource_2[1][1] + lpbSource_2[1][5] + lpbSource_2[1][9] + lpbSource_2[1][13] + lpbSource_2[1][17]
         +  lpbSource_2[2][1] + lpbSource_2[2][5] + lpbSource_2[2][9] + lpbSource_2[2][13] + lpbSource_2[2][17]
         +  lpbSource_2[3][1] + lpbSource_2[3][5] + lpbSource_2[3][9] + lpbSource_2[3][13] + lpbSource_2[3][17]
         +  lpbSource_2[4][1] + lpbSource_2[4][5] + lpbSource_2[4][9] + lpbSource_2[4][13] + lpbSource_2[4][17]
         ) / 25;

         // blue
         lpwDestination[2] =
         (  lpbSource_2[0][2] + lpbSource_2[0][6] + lpbSource_2[0][10] + lpbSource_2[0][14] + lpbSource_2[0][18]
         +  lpbSource_2[1][2] + lpbSource_2[1][6] + lpbSource_2[1][10] + lpbSource_2[1][14] + lpbSource_2[1][18]
         +  lpbSource_2[2][2] + lpbSource_2[2][6] + lpbSource_2[2][10] + lpbSource_2[2][14] + lpbSource_2[2][18]
         +  lpbSource_2[3][2] + lpbSource_2[3][6] + lpbSource_2[3][10] + lpbSource_2[3][14] + lpbSource_2[3][18]
         +  lpbSource_2[4][2] + lpbSource_2[4][6] + lpbSource_2[4][10] + lpbSource_2[4][14] + lpbSource_2[4][18]
         ) / 25;

         // alpha
         lpwDestination[3] =
         (  lpbSource_2[0][3] + lpbSource_2[0][7] + lpbSource_2[0][11] + lpbSource_2[0][15] + lpbSource_2[0][19]
         +  lpbSource_2[1][3] + lpbSource_2[1][7] + lpbSource_2[1][11] + lpbSource_2[1][15] + lpbSource_2[1][19]
         +  lpbSource_2[2][3] + lpbSource_2[2][7] + lpbSource_2[2][11] + lpbSource_2[2][15] + lpbSource_2[2][19]
         +  lpbSource_2[3][3] + lpbSource_2[3][7] + lpbSource_2[3][11] + lpbSource_2[3][15] + lpbSource_2[3][19]
         +  lpbSource_2[4][3] + lpbSource_2[4][7] + lpbSource_2[4][11] + lpbSource_2[4][15] + lpbSource_2[4][19]
         ) / 25;

         lpwDestination += 4;
         x1 += 4;
         x2 += 4;
      }
      y1++;
      y2++;
   }

}

bool imaging::channel_gray_blur(::ca::graphics *pdcDst, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iChannel, int iRadius)
{
   if(size.cx <= 0 || size.cy <= 0)
      return true;

   ::ca::dib_sp dibDst(get_app());

   if(!dibDst.is_set())
      return false;

   if(!dibDst->create(size))
      return false;

   ::ca::dib_sp dibSrc(get_app());

   if(!dibSrc.is_set())
      return false;

   if(!dibSrc->create(size))
      return false;

   if(!dibSrc->from(null_point(), pdcSrc, ptSrc, size))
      return false;

   if(!channel_gray_blur_32CC(
      dibDst,
      dibSrc,
      iChannel,
      iRadius))
      return false;

   if(!dibDst->to(pdcDst, ptDst, size))
      return false;

   return true;
}


bool imaging::channel_alpha_gray_blur(::ca::graphics *pdcDst, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iChannel, int iRadius)
{
   if(size.cx <= 0 || size.cy <= 0)
      return true;

   ::ca::dib_sp dibDst(get_app());

   if(!dibDst.is_set())
      return false;

   if(!dibDst->create(size))
      return false;

   ::ca::dib_sp dibSrc(get_app());

   if(!dibSrc.is_set())
      return false;

   if(!dibSrc->create(size))
      return false;

   if(!dibSrc->from(null_point(), pdcSrc, ptSrc, size))
      return false;

   if(!channel_alpha_gray_blur_32CC(
      dibDst,
      dibSrc,
      iChannel,
      iRadius))
      return false;

   if(!dibDst->to(pdcDst, ptDst, size))
      return false;

   return true;
}

bool imaging::channel_gray_blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc,
                                  int iChannel, int iRadius)
{

   if(iRadius <= 0)
      return true;

   int cx = pdibDst->width();
   int cy = pdibDst->height();
   if(cx != pdibSrc->width()
   || cy != pdibSrc->height())
      return false;
   LPBYTE lpbDst = (LPBYTE) pdibDst->get_data();
   LPBYTE lpbSrc = (LPBYTE) pdibSrc->get_data();
   int wSrc = cx * 4;
   int wDest = cx * 4;

   int iFilterW = iRadius * 2 + 1;
   int iFilterH = iRadius * 2 + 1;
   int iFilterHalfW = iRadius;
   int iFilterHalfH = iRadius;
//   int iFilterArea = iFilterW * iFilterH;
   int iDivisor;

   BYTE *lpwDestination;
   BYTE *lpwDestination_1;


   BYTE *lpbSource;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpbSource_3;

   DWORD dwI;

   int x, y;
   int x2;
   int x3;
   int iFilterXLBound;
   int iFilterXUBound;
   int iFilterYLBound;
   int iFilterYUBound;
   int xFilter;
   int yFilter;

   int xLBound[4];
   int xUBound[4];
   int yLBound[4];
   int yUBound[4];

   int xmax = cx - 1;
   int ymax = cy - 1;

   // top
   xLBound[0] = 0;
   xUBound[0] = cx - 1;
   yLBound[0] = 0;
   yUBound[0] = iFilterHalfH - 1;

   // left
   xLBound[1] = 0;
   xUBound[1] = iFilterHalfW - 1;
   yLBound[1] = iFilterHalfH;
   yUBound[1] = cy - iFilterHalfH - 1;

   // right
   xLBound[2] = cx - iFilterHalfW;
   xUBound[2] = cx - 1;
   yLBound[2] = iFilterHalfH;
   yUBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLBound[3] = 0;
   xUBound[3] = cx - 1;
   yLBound[3] = cy - iFilterHalfW;
   yUBound[3] = cy - 1;


   int iFilterLine;

   for(int i = 0; i < 4; i++)
   {
      int xL = xLBound[i];
      int xU = xUBound[i];
      int yL = yLBound[i];
      int yU = yUBound[i];
      for(y = yL; y <= yU; y++)
      {
         iFilterYLBound = y - iFilterHalfH;
         if(iFilterYLBound < 0)
            iFilterYLBound = 0;
         iFilterYUBound = y + iFilterHalfH;
         if(iFilterYUBound > ymax)
            iFilterYUBound = ymax;

         lpbSource = lpbSrc + (wSrc * max(iFilterYLBound, 0));
         lpwDestination = lpbDst + (wDest  * y);
         x = xL;
         x2 = x - iFilterHalfW;
         x3 = x * 4;
         for(; x <= xU; x++, x3+=4)
         {
            iFilterXLBound = x - iFilterHalfW;
            if(iFilterXLBound < 0)
               iFilterXLBound = 0;
            iFilterXUBound = x + iFilterHalfW;
            if(iFilterXUBound > xmax)
               iFilterXUBound = xmax;

            lpbSource_1 = lpbSource + max(iFilterXLBound, 0) * 4 + iChannel;

            dwI = 0;
            iFilterLine = 0;
            for(yFilter = iFilterYLBound; yFilter <= iFilterYUBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * iFilterLine);
               for(xFilter = iFilterXLBound; xFilter <= iFilterXUBound; xFilter++)
               {
                  dwI += *lpbSource_2;
                  lpbSource_2 += 4;
               }
               iFilterLine++;
            }
            lpwDestination_1 = lpwDestination + x3;
            iDivisor = (iFilterYUBound - iFilterYLBound + 1) * (iFilterXUBound - iFilterXLBound + 1);
            if(iDivisor == 0)
            {
               lpwDestination_1[0] = (BYTE) max(0, min(dwI, 255));
               lpwDestination_1[1] = (BYTE) max(0, min(dwI, 255));
               lpwDestination_1[2] = (BYTE) min(0, min(dwI, 255));
            }
            else
            {
               lpwDestination_1[0] = (BYTE) (dwI / iDivisor);
               lpwDestination_1[1] = lpwDestination_1[0];
               lpwDestination_1[2] = lpwDestination_1[0];
            }
         }
      }
   }

   iDivisor = iFilterW * iFilterH;

   iFilterYLBound     = 0;
   iFilterYUBound     = iFilterW - 1;
   iFilterXLBound     = 0;
   iFilterXUBound     = iFilterH - 1;

   int yL = iFilterHalfH;
   int yU = cy - iFilterHalfH;
   int xL = iFilterHalfW;
   int xU = cx - iFilterHalfW;

   int y1 = yL;
   int x1;

   iDivisor = (iFilterYUBound - iFilterYLBound + 1) * (iFilterXUBound - iFilterXLBound + 1);

   int wDiff = wDest - (xU - xL) * 4;
   lpbSource = lpbSrc + iChannel;
   lpwDestination = lpbDst + (wDest * yL) + xL * 4;
   for(; y1 < yU;)
   {
      x1 = xL;
      lpbSource_1 = lpbSource;
      for(; x1 < xU;)
      {
         dwI = 0;
         lpbSource_2 = lpbSource_1;
         for(int yFilter = iFilterYLBound; yFilter <= iFilterYUBound; yFilter++)
         {
            lpbSource_3 = lpbSource_2;
            for(int xFilter = iFilterXLBound; xFilter <= iFilterXUBound; xFilter++)
            {
               dwI += *lpbSource_3;
               lpbSource_3 += 4;
            }

            lpbSource_2 += wSrc;
         }

         dwI /= iDivisor;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) lpbSrc[(wDest * yL) + xL * 4];

         x1++;
         lpbSource_1 += 4;
      }
      lpwDestination += wDiff;
      y1++;
      lpbSource += wSrc;
   }

   return true;

}

bool imaging::channel_alpha_gray_blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc,
                                  int iChannel, int iRadius)
{

   if(iRadius <= 0)
      return true;

   int cx = pdibDst->width();
   int cy = pdibDst->height();
   if(cx != pdibSrc->width()
   || cy != pdibSrc->height())
      return false;
   LPBYTE lpbDst = (LPBYTE) pdibDst->get_data();
   LPBYTE lpbSrc = (LPBYTE) pdibSrc->get_data();
   int wSrc = cx * 4;
   int wDest = cx * 4;

   int iFilterW = iRadius * 2 + 1;
   int iFilterH = iRadius * 2 + 1;
   int iFilterHalfW = iRadius;
   int iFilterHalfH = iRadius;
//   int iFilterArea = iFilterW * iFilterH;
   int iDivisor;

   BYTE *lpwDestination;
   BYTE *lpwDestination_1;


   BYTE *lpbSource;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpbSource_3;

   DWORD dwI;

   int x, y;
   int x2;
   int x3;
   int iFilterXLBound;
   int iFilterXUBound;
   int iFilterYLBound;
   int iFilterYUBound;
   int xFilter;
   int yFilter;

   int xLBound[4];
   int xUBound[4];
   int yLBound[4];
   int yUBound[4];

   int xmax = cx - 1;
   int ymax = cy - 1;

   // top
   xLBound[0] = 0;
   xUBound[0] = cx - 1;
   yLBound[0] = 0;
   yUBound[0] = iFilterHalfH - 1;

   // left
   xLBound[1] = 0;
   xUBound[1] = iFilterHalfW - 1;
   yLBound[1] = iFilterHalfH;
   yUBound[1] = cy - iFilterHalfH - 1;

   // right
   xLBound[2] = cx - iFilterHalfW;
   xUBound[2] = cx - 1;
   yLBound[2] = iFilterHalfH;
   yUBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLBound[3] = 0;
   xUBound[3] = cx - 1;
   yLBound[3] = cy - iFilterHalfW;
   yUBound[3] = cy - 1;


   int iFilterLine;

   for(int i = 0; i < 4; i++)
   {
      int xL = xLBound[i];
      int xU = xUBound[i];
      int yL = yLBound[i];
      int yU = yUBound[i];
      for(y = yL; y <= yU; y++)
      {
         iFilterYLBound = y - iFilterHalfH;
         if(iFilterYLBound < 0)
            iFilterYLBound = 0;
         iFilterYUBound = y + iFilterHalfH;
         if(iFilterYUBound > ymax)
            iFilterYUBound = ymax;

         lpbSource = lpbSrc + (wSrc * max(iFilterYLBound, 0));
         lpwDestination = lpbDst + (wDest  * y);
         x = xL;
         x2 = x - iFilterHalfW;
         x3 = x * 4;
         for(; x <= xU; x++, x3+=4)
         {
            iFilterXLBound = x - iFilterHalfW;
            if(iFilterXLBound < 0)
               iFilterXLBound = 0;
            iFilterXUBound = x + iFilterHalfW;
            if(iFilterXUBound > xmax)
               iFilterXUBound = xmax;

            lpbSource_1 = lpbSource + max(iFilterXLBound, 0) * 4 + iChannel;

            dwI = 0;
            iFilterLine = 0;
            for(yFilter = iFilterYLBound; yFilter <= iFilterYUBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * iFilterLine);
               for(xFilter = iFilterXLBound; xFilter <= iFilterXUBound; xFilter++)
               {
                  dwI += *lpbSource_2;
                  lpbSource_2 += 4;
               }
               iFilterLine++;
            }
            lpwDestination_1 = lpwDestination + x3;
            iDivisor = (iFilterYUBound - iFilterYLBound + 1) * (iFilterXUBound - iFilterXLBound + 1);
            if(iDivisor == 0)
            {
               lpwDestination_1[0] = (BYTE) max(0, min(dwI, 255));
               lpwDestination_1[1] = (BYTE) max(0, min(dwI, 255));
               lpwDestination_1[2] = (BYTE) min(0, min(dwI, 255));
               lpwDestination_1[3] = (BYTE) min(0, min(dwI, 255));
            }
            else
            {
               lpwDestination_1[0] = (BYTE) (dwI / iDivisor);
               lpwDestination_1[1] = lpwDestination_1[0];
               lpwDestination_1[2] = lpwDestination_1[0];
               lpwDestination_1[3] = lpwDestination_1[0];
            }
         }
      }
   }

   iDivisor = iFilterW * iFilterH;

   iFilterYLBound     = 0;
   iFilterYUBound     = iFilterW - 1;
   iFilterXLBound     = 0;
   iFilterXUBound     = iFilterH - 1;

   int yL = iFilterHalfH;
   int yU = cy - iFilterHalfH;
   int xL = iFilterHalfW;
   int xU = cx - iFilterHalfW;

   int y1 = yL;
   int x1;

   iDivisor = (iFilterYUBound - iFilterYLBound + 1) * (iFilterXUBound - iFilterXLBound + 1);

   int wDiff = wDest - (xU - xL) * 4;
   lpbSource = lpbSrc + iChannel;
   lpwDestination = lpbDst + (wDest * yL) + xL * 4;
   for(; y1 < yU;)
   {
      x1 = xL;
      lpbSource_1 = lpbSource;
      for(; x1 < xU;)
      {
         dwI = 0;
         lpbSource_2 = lpbSource_1;
         for(int yFilter = iFilterYLBound; yFilter <= iFilterYUBound; yFilter++)
         {
            lpbSource_3 = lpbSource_2;
            for(int xFilter = iFilterXLBound; xFilter <= iFilterXUBound; xFilter++)
            {
               dwI += *lpbSource_3;
               lpbSource_3 += 4;
            }

            lpbSource_2 += wSrc;
         }

         dwI /= iDivisor;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;

         x1++;
         lpbSource_1 += 4;
      }
      lpwDestination += wDiff;
      y1++;
      lpbSource += wSrc;
   }

   return true;

}

bool imaging::channel_gray_blur(
                              ::ca::graphics * pdcDst,
                              point ptDst,
                              size size,
                              ::ca::graphics * pdcSrc,
                              point ptSrc,
                              int iChannel,
                              class size sizeFilter,
                              LPBYTE lpbFilter)
{
   if(size.cx <= 0 || size.cy <= 0)
      return true;

   ::ca::dib_sp dibDst(get_app());

   if(!dibDst.is_set())
      return false;

   if(!dibDst->create(size))
      return false;

   ::ca::dib_sp dibSrc(get_app());

   if(!dibSrc.is_set())
      return false;

   if(!dibSrc->create(size))
      return false;

   if(!dibSrc->from(null_point(), pdcSrc, ptSrc, size))
      return false;

   if(!channel_gray_blur_32CC(
      dibDst,
      dibSrc,
      iChannel,
      sizeFilter.cx,
      sizeFilter.cy,
      lpbFilter))
      return false;

   if(!dibDst->to(pdcDst, ptDst, size))
      return false;

   return true;

}


bool imaging::channel_gray_blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc,
                                  int iChannel,
                                  int iFilterWidth,
                                  int iFilterHeight,
                                  LPBYTE lpbFilter)
{

   int cx = pdibDst->width();
   int cy = pdibDst->height();
   if(cx != pdibSrc->width()
   || cy != pdibSrc->height())
      return false;
   LPBYTE lpbDst = (LPBYTE) pdibDst->get_data();
   LPBYTE lpbSrc = (LPBYTE) pdibSrc->get_data();
   int wSrc = cx * 4;
   int wDest = cx * 4;

   int iFilterArea = iFilterWidth * iFilterHeight;
   int divisor;

   BYTE *lpwDestination;


   BYTE *lpbSource;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpbSource_3;

   BYTE *lpFilter;
   BYTE * pFilter = new BYTE[iFilterHeight *iFilterWidth];
   memset(pFilter, 1, iFilterHeight * iFilterWidth);

   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterWidth;
//   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 4;
//   int max3x2 = (maxx1 - iFilterHeight) * 4;
//   int max3x3 = (maxx1 - iFilterHeight / 2) * 4;
   //int bm3Width = (cy * 3 + 3) & ~0x3L;
//   int w = cx * 4;
   //   memcpy(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   memcpy(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(int y = 0; y < cy; y++)
   {
   lpbSource = lpbSrc + wSrc * y;
   lpwDestination = lpbDst + wDest * y;
   for(int x = 0; x < w; x++)
   {
   *lpwDestination = *lpbSource;
   lpwDestination++;
   lpbSource++;
   }
   }*/
   DWORD dwI;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   yLBound[0] = 0;
   yUBound[0] = iFilterWidth / 2;
   xLBound[0] = 0;
   xUBound[0] = max3x1;

   // left
   yLBound[1] = iFilterWidth / 2;
   yUBound[1] = maxy1 - iFilterWidth / 2;
   xLBound[1] = 0;
   xUBound[1] = iFilterWidth / 2;

   // right
   yLBound[2] = iFilterWidth / 2;
   yUBound[2] = maxy1- iFilterWidth / 2;
   xLBound[2] = max3x1 - iFilterWidth / 2;
   xUBound[2] = max3x1;

   // bottom
   yLBound[3] = maxy1 - iFilterWidth / 2;
   yUBound[3] = maxy1;
   xLBound[3] = 0;
   xUBound[3] = max3x1;

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLBound[i];
   int yU = yUBound[i];
   int xL = xLBound[i];
   int xU = xUBound[i];
   for(int y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   lpbSource = lpbSrc + (wSrc * max((y1 - iFilterWidth / 2), 0));
   lpwDestination = lpbDst + (wDest  * y1);
   for(int x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   lpbSource_1 = lpbSource + ((max(x1 - iFilterWidth / 2 * 3, 0)));
   lpFilter = pFilter;
   //            lpConv = pConv;

   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   lpbSource_2 = lpbSource_1 + (wSrc * y2);
   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *lpbSource_2++ * *lpFilter;
   dwG += *lpbSource_2++ * *lpFilter;
   dwB += *lpbSource_2++ * *lpFilter++;

   }
   }
   lpwDestination_1 = lpwDestination + x1;
   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   lpwDestination_1[0] = max(0, min(dwR, 255));
   lpwDestination_1[1] = max(0, min(dwG, 255));
   lpwDestination_1[2] = min(0, min(dwB, 255));
   }
   else
   {
   lpwDestination_1[0] = dwR / divisor;
   lpwDestination_1[1] = dwG / divisor;
   lpwDestination_1[2] = dwB / divisor;
   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   divisor = 0;
   lpFilter = lpbFilter;
   for(int i = 0; i < iFilterArea; i++)
   {
      divisor += *lpFilter++;
   }

   int iFilterHalfWidth = iFilterWidth / 2;
//   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = cy - iFilterHalfWidth;
   int xL = iFilterHalfWidth;
   int xU = cx - iFilterHalfWidth;


   int y1 = yL;
   //int y2 = yL - iFilterHalfWidth;
   int x1;
   //int x2;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );

   int wDiff = wDest - (xU - xL) * 4;
   lpbSource = lpbSrc + iChannel;
   lpwDestination = lpbDst + (wDest  * yL) + xL * 4;
   for(; y1 < yU;)
   {


      x1 = xL;
      //x2 = xL - iFilterHalfWidth;

      lpbSource_1 = lpbSource;
      for(; x1 < xU;)
      {

         lpFilter = pFilter;

         dwI = 0;
         lpbSource_2 = lpbSource_1;
         for(int yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            lpbSource_3 = lpbSource_2;
            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwI += *lpbSource_3 * *lpFilter++;
               lpbSource_3 += 4;
            }

            lpbSource_2 += wSrc;
         }

         dwI /= divisor;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) dwI;
         *lpwDestination++ = (unsigned char) lpbSource_1[3];
         //      x1 += 3;
         x1++;
         lpbSource_1 += 4;
         //x2 += 3;
      }
      lpwDestination += wDiff;
      y1++;
      //y2++;
      lpbSource += wSrc;
   }

   delete pFilter;
   return true;
}



bool imaging::color_blend(::ca::graphics * pdc, LPCRECT lpcrect, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork)
{
   class rect rect(lpcrect);
   return color_blend(pdc, rect.top_left(), rect.size(), pdcColorAlpha, ptAlpha, pdibWork);
}

bool imaging::true_blend(::ca::graphics * pdc, LPCRECT lpcrect, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork, ::ca::dib * pdibWork2, ::ca::dib * pdibWork3)
{
   class rect rect(lpcrect);
   return true_blend(pdc, rect.top_left(), rect.size(), pdcColorAlpha, ptAlpha, pdibWork, pdibWork2, pdibWork3);
}

// COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

bool imaging::true_blend(::ca::graphics * pdc, point pt, size size, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork, ::ca::dib * pdibWork2, ::ca::dib * pdibWork3)
{
   return pdc->BitBlt(pt.x, pt.y, size.cx, size.cy, pdcColorAlpha, ptAlpha.x, ptAlpha.y, SRCCOPY);
   if(pdc == NULL)
      return false;
   if(pdcColorAlpha == NULL)
      return false;
   if(pdcColorAlpha->get_os_data() == NULL)
      return false;
   if(&pdcColorAlpha->GetCurrentBitmap() == NULL)
      return false;


   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = 0xFF;
   bf.AlphaFormat = AC_SRC_ALPHA;


   if(pdc->m_pdibAlphaBlend != NULL)
   {
      return pdc->alpha_blend(pt, size, pdcColorAlpha, ptAlpha, bf);
   }


   ::ca::dib_sp spdib;
   if(pdibWork == NULL)
   {
      spdib.create(get_app());
      pdibWork = spdib;
   }
   if(pdibWork == NULL)
      return false;
   if(!pdibWork->create(size))
      return false;
   if(!pdibWork->from(null_point(), pdcColorAlpha, ptAlpha, size))
      return false;




   ::ca::dib_sp spdib3;
   if(pdibWork3 == NULL)
   {
      spdib3.create(get_app());
      pdibWork3 = spdib3;
   }
   if(pdibWork3 == NULL)
      return false;
   if(!pdibWork3->create(size))
      return false;
   pdibWork3->from(null_point(), pdc, pt, size);



   ::ca::dib_sp spdib2;
   if(pdibWork2 == NULL)
   {
      spdib2.create(get_app());
      pdibWork2 = spdib2;
   }
   if(!pdibWork2->create(size))
      return false;

   // multiply by inverted alpha
   pdibWork2->FillByte(0);


   pdibWork2->channel_from(visual::rgba::channel_alpha, pdibWork);


   pdibWork2->channel_invert(visual::rgba::channel_alpha);

   pdibWork->get_graphics()->alpha_blend(null_point(), size, pdibWork2->get_graphics(), null_point(), bf);

   pdibWork2->channel_invert(visual::rgba::channel_alpha);

   pdibWork->channel_from(visual::rgba::channel_alpha, pdibWork2);

   //pdibWork3->get_graphics()->alpha_blend(null_point(), size, pdibWork->get_graphics(), null_point(), bf);

   //return pdc->BitBlt(pt.x, pt.y, size.cx, size.cy, pdibWork3->get_graphics(), 0, 0, SRCCOPY);

   return pdc->alpha_blend(pt, size, pdibWork->get_graphics(), null_point(), bf);


}


bool imaging::color_blend(::ca::graphics * pdc, point pt, size size, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork, ::ca::dib * pdibWork2)
{
   
   
   
   return pdc->BitBlt(pt.x, pt.y, size.cx, size.cy, pdcColorAlpha, ptAlpha.x, ptAlpha.y, SRCCOPY);



   UNREFERENCED_PARAMETER(pdibWork2);
   if(pdc == NULL)
      return false;
   if(pdcColorAlpha == NULL)
      return false;
   if(pdcColorAlpha->get_os_data() == NULL)
      return false;
   if(&pdcColorAlpha->GetCurrentBitmap() == NULL)
      return false;
   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = 0xFF;
   bf.AlphaFormat = AC_SRC_ALPHA;
   ::ca::dib_sp spdib;
   if(pdibWork == NULL)
   {
      spdib.create(get_app());
      pdibWork = spdib;
   }
   if(pdibWork == NULL)
      return false;
   if(!pdibWork->create(size))
      return false;
   if(!pdibWork->from(null_point(), pdcColorAlpha, ptAlpha, size))
      return false;
   //spdib->channel_invert(visual::rgba::channel_alpha);
   /*::ca::dib_sp spdib2;
   if(pdibWork2 == NULL)
   {
      spdib2.create(get_app());
      pdibWork2 = spdib2;
   }
   pdibWork->mult_alpha(pdibWork2);*/
   //pdibWork->get_graphics()->m_pdibAlphaBlend = spdib;
   return pdc->alpha_blend(pt, size, pdibWork->get_graphics(), ptAlpha, bf) != 0;
}

bool imaging::color_blend(::ca::graphics * pdc, point pt, size size, ::ca::graphics * pdcColorAlpha, point ptAlpha, double dBlend)
{

   if(pt.x < 0)
   {
      ptAlpha.x += -pt.x;
      pt.x = 0;
   }

   if(pt.y < 0)
   {
      ptAlpha.y += -pt.y;
      pt.y = 0;
   }


   if(dBlend >= 1.0)
   {

      pdc->BitBlt(pt.x, pt.y, size.cx, size.cy, pdcColorAlpha, 0, 0, SRCCOPY);

   }
   else
   {

      ::visual::dib_sp dib(get_app());
      if(!dib->create(size))
         return false;
      dib->get_graphics()->set_alpha_mode(::ca::alpha_mode_set);
      dib->from(point(0, 0), pdcColorAlpha, ptAlpha, size);
      dib->channel_multiply(visual::rgba::channel_alpha, dBlend);
      pdc->BitBlt(pt.x, pt.y, size.cx, size.cy, dib->get_graphics(), 0, 0, SRCCOPY);

   }

}


bool imaging::color_blend(::ca::graphics * pdc, LPCRECT lpcrect, ::ca::graphics * pdcColorAlpha, point ptAlpha, double dBlend)
{
   class rect rect(lpcrect);
   return color_blend(pdc, rect.top_left(), rect.size(), pdcColorAlpha, ptAlpha, dBlend);
}

bool imaging::pre_color_blend(
                            ::ca::graphics * pdcColorAlpha,
                            ::ca::graphics * pdcAlpha,
                            COLORREF cr)
{
   if(pdcAlpha->get_os_data() == NULL)
      return false;
   if(pdcColorAlpha->get_os_data() == NULL)
      return false;
   ::ca::bitmap * pbmp = &pdcAlpha->GetCurrentBitmap();
   BITMAP bm;
   class size size = pbmp->get_size();
 
   ::ca::dib_sp dibA(get_app());

   if(!dibA->create(size))
      return false;

   ::ca::dib_sp dibB(get_app());

   if(!dibB->create(size))
      return false;


   dibB->get_graphics()->FillSolidRect(0, 0, size.cx, size.cy, cr);


   dibA->get_graphics()->from(size, pdcAlpha, SRCCOPY);
   GdiFlush();


   UINT32 * lpuiA = (UINT32 *) dibA->get_data();

   __int64 a = size.area();
   int i;

   for (i = 0; i < a; i++)
   {
      *lpuiA++ = 0xff000000 - (*lpuiA & 0xff000000);
   }

   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = 0xFF;
   bf.AlphaFormat = AC_SRC_ALPHA;

   if(!dibB->get_graphics()->alpha_blend(size, dibA->get_graphics(), bf))
      return FALSE;

   GdiFlush();

   lpuiA = (UINT32 *) dibA->get_data();
   UINT32 * lpuiB = (UINT32 *) dibB->get_data();

   for (i = 0; i < a; i++)
   {
      *lpuiA++ = (0xff000000 - (*lpuiA & 0xff000000)) | (*lpuiB++  & 0x00ffffff);
   }

   return pdcColorAlpha->from(size, dibA->get_graphics(), SRCCOPY) != 0;

}





bool imaging::color_blend(
                         ::ca::graphics * pdcA, // destination device
                         point pt,
                         size size,
                         COLORREF cr,
                         ::ca::graphics * pdcC, // alpha information device
                         point ptSrc)
{
   ::ca::dib_sp dibA(get_app());

   if(!dibA->create(size))
      return false;

   ::ca::dib_sp dibB(get_app());

   if(!dibB->create(size))
      return false;


   dibB->get_graphics()->FillSolidRect(0, 0, size.cx, size.cy, cr);


   dibA->get_graphics()->from(size, pdcC, ptSrc, SRCCOPY);
   GdiFlush();


   UINT32 * lpuiA = (UINT32 *) dibA->get_data();

   __int64 a = size.area();
   __int64 i;

   for (i = 0; i < a; i++)
   {
      *lpuiA++ = 0xff000000 - ((*lpuiA << 8) & 0xff000000);
   }

   BLENDFUNCTION bf;
   bf.BlendOp     = AC_SRC_OVER;
   bf.BlendFlags  = 0;
   bf.SourceConstantAlpha = 0xFF;
   bf.AlphaFormat = AC_SRC_ALPHA;

   if(!dibB->get_graphics()->alpha_blend(size, dibA->get_graphics(), bf))
   {
      return FALSE;
   }


   GdiFlush();

   lpuiA = (UINT32 *) dibA->get_data();
   UINT32 * lpuiB = (UINT32 *) dibB->get_data();

   for (i = 0; i < a; i++)
   {
      *lpuiA++ = (0xff000000 - (*lpuiA & 0xff000000)) | (*lpuiB++  & 0x00ffffff);
   }

   if(!pdcA->alpha_blend(pt, size, dibA->get_graphics(), bf))
   {
      return false;
   }

   GdiFlush();

   return true;
}

void imaging::color_blend_24CC(
                             LPBYTE lpbAParam,
                             int x1,
                             int y1,
                             int w1,
                             int cx,
                             int cy,
                             COLORREF cr,
                             LPBYTE lpbCParam,
                             int x3,
                             int y3,
                             int w3)
{
   int i, j;
   x1 *= 3;
   x3 *= 3;
   y1 *= w1;
   y3 *= w3;

   BYTE bR = rgba_get_r(cr);
   BYTE bG = rgba_get_g(cr);
   BYTE bB = rgba_get_b(cr);

   lpbAParam = (LPBYTE) lpbAParam + y1 + x1;
   lpbCParam = (LPBYTE) lpbCParam + y3 + x3;

   //   BYTE dwA;
   for(i = 0; i < cy; i++)
   {
      LPBYTE lpbA = (LPBYTE) lpbAParam + (w1 * i);
      LPBYTE lpbC = (LPBYTE) lpbCParam + (w3 * i);
      for(j = 0; j < cx; j++)
      {
         *lpbA++ = (BYTE) (((((DWORD) *lpbA) * ((DWORD) (255 - *lpbC)) + (((DWORD) bB) * ((DWORD) *lpbC++)))) / 255);
         *lpbA++ = (BYTE) (((((DWORD) *lpbA) * ((DWORD) (255 - *lpbC)) + (((DWORD) bG) * ((DWORD) *lpbC++)))) / 255);
         *lpbA++ = (BYTE) (((((DWORD) *lpbA) * ((DWORD) (255 - *lpbC)) + (((DWORD) bR) * ((DWORD) *lpbC++)))) / 255);
      }
   }

}


bool imaging::clip_color_blend(
                             ::ca::graphics * pdc,
                             point pt,
                             size size,
                             COLORREF cr,
                             ::ca::graphics * pdcAlpha,
                             point ptAlpha)
{
   return color_blend(
      pdc,
      pt,
      size,
      cr, pdcAlpha,
      ptAlpha);
}



bool imaging::alpha_spread_R2(::ca::graphics *pdcDst, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, BYTE bMin)
{
   if(size.cx <= 0 || size.cy <= 0)
      return true;

   UINT user;
   UINT uiStartScanLine;
   UINT uiScanLineCount;


   rect rectDst(ptDst, size);
   rect rectSrc(ptSrc, size);

   int iwDest;

   BITMAPINFO bmiDst;
   BITMAP   bmDst;
   int iLimitYDst;

   ::ca::bitmap_sp bitmapDst(get_app());

   primitive::memory memstorageA;
   primitive::memory memstorageB;

   if(!GetDeviceContext24BitsCC(
      pdcDst,
      bmDst,
      bmiDst,
      memstorageA,
      bitmapDst,
      rectDst,
      iwDest,
      uiStartScanLine,
      uiScanLineCount,
      iLimitYDst))
   {
      return false;
   }

   LPBYTE lpbDst = memstorageA.get_data();


   int iwSrc;

   BITMAPINFO bmiSrc;
   BITMAP   bmSrc;
   int iLimitYSrc;

   ::ca::bitmap_sp bitmapSrc(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcSrc, bmSrc, bmiSrc,
      memstorageB,
      bitmapSrc,
      rectSrc,
      iwSrc,
      user,
      user,
      iLimitYSrc))
   {
      return false;
   }

   LPBYTE lpbSrc = memstorageB.get_data();


   point ptViewportDst = pdcDst->GetViewportOrg();
   point ptViewportSrc = pdcSrc->GetViewportOrg();

   int xvpDst = ptDst.x + ptViewportDst.x;
   int xvpSrc = ptSrc.x + ptViewportSrc.x;

   int iLimitX = size.cx;

   if(bmDst.bmWidth - xvpDst < iLimitX)
   {
      iLimitX = bmDst.bmWidth - xvpDst;
   }
   if(bmSrc.bmWidth - xvpSrc < iLimitX)
   {
      iLimitX = bmSrc.bmWidth - xvpSrc;
   }


   if(xvpDst < 0)
      return false;
   if(xvpSrc < 0)
      return false;

   int iLimitY = min(iLimitYDst, iLimitYSrc);

   alpha_spread_R2_24CC(
      lpbDst,
      xvpDst,
      0,
      iwDest,
      iLimitX,
      iLimitY,
      lpbSrc,
      xvpSrc,
      0,
      iwSrc,
      bMin);


   ::ca::bitmap * pbmpOld = &pdcDst->GetCurrentBitmap();
   if(pbmpOld == NULL)
   {
      ::ca::graphics_sp graphicsMem(get_app());
         graphicsMem->CreateCompatibleDC(pdcDst);
      if(!SetDIBits(
         (HDC)graphicsMem->get_os_data(),
         (HBITMAP) bitmapDst->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDst,
         DIB_RGB_COLORS))
         throw 6000;
      ::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(bitmapDst);
      if(!pdcDst->BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, graphicsMem, ptSrc.x, ptSrc.y, SRCCOPY))
      {
         ASSERT(FALSE);
      }
      graphicsMem->SelectObject(pbmpMemOld);
   }
   else
   {
      ::ca::bitmap_sp bitmap(get_app());
      bitmap->CreateCompatibleBitmap(pdcDst, 1, 1);
//      ::ca::bitmap * pbitmap = pdcDst->SelectObject(bitmap);
      if(!SetDIBits(
         (HDC) pdcDst->get_os_data(),
         (HBITMAP) bitmapDst->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDst,
         DIB_RGB_COLORS))
         throw 6000;
      pdcDst->SelectObject(bitmapDst);
   }

   return true;

}

bool imaging::alpha_spread(::ca::graphics *pdcDst, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, BYTE bMin, int iRadius)
{
   if(size.cx <= 0 || size.cy <= 0)
      return true;

   //   single_lock sl(&m_csMem, TRUE);


   UINT user;
   UINT uiStartScanLine;
   UINT uiScanLineCount;


   rect rectDest(ptDst, size);
   rect rectSrc(ptSrc, size);

   int iwDest;

   BITMAPINFO bmiDest;
   BITMAP   bmDest;
   int iLimitYDest;



   ::ca::bitmap_sp bitmapDest(get_app());
   primitive::memory memstorageA;
   primitive::memory memstorageB;

   if(!GetDeviceContext24BitsCC(
      pdcDst,
      bmDest,
      bmiDest,
      memstorageA,
      bitmapDest,
      rectDest,
      iwDest,
      uiStartScanLine,
      uiScanLineCount,
      iLimitYDest))
   {
      return false;
   }

   LPBYTE lpbDst = memstorageA.get_data();


   int iwSrc;

   BITMAPINFO bmiSrc;
   BITMAP   bmSrc;
   int iLimitYSrc;

   ::ca::bitmap_sp bitmapSrc(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcSrc, bmSrc, bmiSrc,
      memstorageB,
      bitmapSrc,
      rectSrc,
      iwSrc,
      user,
      user,
      iLimitYSrc))
   {
      return false;
   }

   LPBYTE lpbSrc = memstorageB.get_data();


   point ptViewportDest = pdcDst->GetViewportOrg();
   point ptViewportSrc = pdcSrc->GetViewportOrg();

   int xvpDest = ptDst.x + ptViewportDest.x;
   int xvpSrc = ptDst.y + ptViewportSrc.x;

   int iLimitX = size.cx;

   if(bmDest.bmWidth - xvpDest < iLimitX)
   {
      iLimitX = bmDest.bmWidth - xvpDest;
   }
   if(bmSrc.bmWidth - xvpSrc < iLimitX)
   {
      iLimitX = bmSrc.bmWidth - xvpSrc;
   }


   if(xvpDest < 0)
      return false;
   if(xvpSrc < 0)
      return false;

   int iLimitY = min(iLimitYDest, iLimitYSrc);

   alpha_spread__24CC(
      lpbDst,
      xvpDest,
      0,
      iwDest,
      iLimitX,
      iLimitY,
      lpbSrc,
      xvpSrc,
      0,
      iwSrc,
      bMin, iRadius);


   ::ca::bitmap * pbmpOld = &pdcDst->GetCurrentBitmap();
   if(pbmpOld == NULL)
   {
      ::ca::graphics_sp graphicsMem(get_app());
         graphicsMem->CreateCompatibleDC(pdcDst);
      if(!SetDIBits(
         (HDC)graphicsMem->get_os_data(),
         (HBITMAP) bitmapDest->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDest,
         DIB_RGB_COLORS))
         throw 6000;
      ::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(bitmapDest);
      if(!pdcDst->BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, graphicsMem, ptSrc.x, ptSrc.y, SRCCOPY))
      {
         ASSERT(FALSE);
      }
      graphicsMem->SelectObject(pbmpMemOld);
   }
   else
   {
      ::ca::bitmap_sp bitmap(get_app());
      bitmap->CreateCompatibleBitmap(pdcDst, 1, 1);
//      ::ca::bitmap * pbitmap = pdcDst->SelectObject(bitmap);
      if(!SetDIBits(
         (HDC) pdcDst->get_os_data(),
         (HBITMAP) bitmapDest->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDest,
         DIB_RGB_COLORS))
         throw 6000;
      pdcDst->SelectObject(bitmapDest);
   }

   return true;

}


void imaging::alpha_spread_R2_24CC(LPBYTE lpbDst, int xDest, int yDest, int wDest, int cx, int cy, LPBYTE lpbSrc, int xSrc, int ySrc, int wSrc, BYTE bMin)
{
   UNREFERENCED_PARAMETER(xDest);
   UNREFERENCED_PARAMETER(yDest);
   UNREFERENCED_PARAMETER(xSrc);
   UNREFERENCED_PARAMETER(ySrc);
   int iFilterWidth = 2 * 2 + 1;
   int iFilterHeight = 2 * 2 + 1;
   int divisor = iFilterWidth * iFilterHeight;
   BYTE *lpbSource;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpwDestination;
   BYTE *lpFilter;
   BYTE * pFilter = new BYTE[iFilterHeight *iFilterWidth];
   memset(pFilter, 1, iFilterHeight * iFilterWidth);

   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterWidth;
//   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 3;
//   int max3x2 = (maxx1 - iFilterHeight) * 3;
//   int max3x3 = (maxx1 - iFilterHeight / 2) * 3;
//   int w = cx * 3;
   DWORD dwR;
   DWORD dwG;
   DWORD dwB;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   yLBound[0] = 0;
   yUBound[0] = iFilterWidth / 2;
   xLBound[0] = 0;
   xUBound[0] = max3x1;

   // left
   yLBound[1] = iFilterWidth / 2;
   yUBound[1] = maxy1 - iFilterWidth / 2;
   xLBound[1] = 0;
   xUBound[1] = iFilterWidth / 2;

   // right
   yLBound[2] = iFilterWidth / 2;
   yUBound[2] = maxy1- iFilterWidth / 2;
   xLBound[2] = max3x1 - iFilterWidth / 2;
   xUBound[2] = max3x1;

   // bottom
   yLBound[3] = maxy1 - iFilterWidth / 2;
   yUBound[3] = maxy1;
   xLBound[3] = 0;
   xUBound[3] = max3x1;

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   DWORD bMin3 = bMin * 3;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );

   bool bSpread;

   for(; y1 < yU;)
   {
      lpbSource = lpbSrc + (wSrc * y2);

      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      lpwDestination = lpbDst + (wDest  * y1) + x1;
      for(; x1 < xU;)
      {
         lpbSource_1 = lpbSource + x2;
         lpFilter = pFilter;

         dwR = 0;
         dwG = 0;
         dwB = 0;
         bSpread = false;
         for(int yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwB = lpbSource_2[0];
               dwG = lpbSource_2[1];
               dwR = lpbSource_2[2];

               if(dwR + dwG + dwB > bMin3)
               {
                  bSpread = true;
                  break;
               }
               lpbSource_2 += 3;
            }
         }

         if(bSpread)
         {
            *((DWORD *) lpwDestination) |= 0x00ffffff;
            lpwDestination += 3;
         }
         else
         {
            lpwDestination += 3;
         }
         x1 += 3;
         x2 += 3;
      }
      y1++;
      y2++;
   }

   delete pFilter;
}


void imaging::alpha_spread__24CC(
                               LPBYTE lpbDst, int xDest, int yDest, int wDest, int cx, int cy,
                               LPBYTE lpbSrc, int xSrc, int ySrc, int wSrc,
                               BYTE bMin, int iRadius)
{
   UNREFERENCED_PARAMETER(xDest);
   UNREFERENCED_PARAMETER(yDest);
   UNREFERENCED_PARAMETER(xSrc);
   UNREFERENCED_PARAMETER(ySrc);
   int iFilterW      = iRadius * 2 + 1;
   int iFilterH      = iRadius * 2 + 1;
   int iFilterHalfW  = iFilterW / 2;
   int iFilterHalfH  = iFilterH / 2;
   int iFilterArea   = iFilterW * iFilterH;
   int divisor       = iFilterW * iFilterH;
   BYTE *lpbSource;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpwDestination;
   BYTE *lpFilter;
   BYTE * pFilter;

   int i;
   int x;
   int y;
   int x1;
   int y1;
   int x2;
   int y2;

   int iRadius2 = iRadius * iRadius;
   int r2;

   if(!m_alpha_spread__24CC_filterMap.Lookup(iRadius, pFilter))
   {
      pFilter = new BYTE[iFilterArea];
      m_alpha_spread__24CC_filterMap.set_at(iRadius, pFilter);
      for(y = 0; y <= iFilterHalfH; y++)
      {
         for(x = 0; x <= iFilterHalfW; x++)
         {
            x1 = iFilterHalfW - x;
            y1 = iFilterHalfH - y;
            r2 = x1 * x1 + y1 * y1;
            if(r2 <= iRadius2)
               i = 1;
            else
               i = 0;
            pFilter[x + y * iFilterW]                                   = (byte) i;
            pFilter[iFilterW - 1 - x + y * iFilterW]                    = (byte) i;
            pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW]   = (byte) i;
            pFilter[x + (iFilterH - 1 - y) * iFilterW]                  = (byte) i;
         }
      }
   }

   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterW;
//   int maxy3 = cy - iFilterW / 2;
   int max3x1 = maxx1 * 3;
//   int max3x2 = (maxx1 - iFilterH) * 3;
//   int max3x3 = (maxx1 - iFilterH / 2) * 3;
//   int w = cx * 3;
   DWORD dwR;
   DWORD dwG;
   DWORD dwB;


   int iFilterXLBound;
   int iFilterXUBound;
   int iFilterYLBound;
   int iFilterYUBound;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   xLBound[0] = 0;
   xUBound[0] = cx - 1;
   yLBound[0] = 0;
   yUBound[0] = iFilterHalfH - 1;

   // left
   xLBound[1] = 0;
   xUBound[1] = iFilterHalfW - 1;
   yLBound[1] = iFilterHalfH;
   yUBound[1] = cy - iFilterHalfH - 1;

   // right
   xLBound[2] = cx - iFilterHalfW;
   xUBound[2] = cx - 1;
   yLBound[2] = iFilterHalfH;
   yUBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLBound[3] = 0;
   xUBound[3] = cx - 1;
   yLBound[3] = cy - iFilterHalfW;
   yUBound[3] = cy - 1;

   int xL;
   int xU;
   int yL;
   int yU;

   bool bSpread;
   DWORD bMin3 = bMin * 3;


   for(i = 0; i < 4; i++)
   {
      xL = xLBound[i];
      xU = xUBound[i];
      yL = yLBound[i];
      yU = yUBound[i];

      y1 = yL;
      y2 = y1 - iFilterHalfH;
      for(; y1 <= yU;)
      {
         if(y1 < iFilterHalfH)
         {
            iFilterYLBound = iFilterHalfH - y1;
         }
         else
         {
            iFilterYLBound = 0;
         }
         if(y1 > (cy - iFilterHalfH))
         {
            iFilterYUBound = iFilterH - (y1 - (cy - iFilterHalfH)) - 1;
         }
         else
         {
            iFilterYUBound = iFilterH - 1;
         }

         lpbSource = lpbSrc + (wSrc * max(y2, 0));

         x1 = xL;
         x2 = (x1 - iFilterHalfW) * 3;
         lpwDestination = lpbDst + (wDest  * y1) + x1 * 3;
         for(; x1 <= xU;)
         {
            if(x1 < iFilterHalfH)
            {
               iFilterXLBound = iFilterHalfH - x1;
            }
            else
            {
               iFilterXLBound = 0;
            }
            if(x1 > (cx - iFilterHalfH + 1))
            {
               iFilterXUBound = iFilterH - (x1 - (cx - iFilterHalfH + 1));
            }
            else
            {
               iFilterXUBound = iFilterH - 1;
            }

            lpbSource_1 = lpbSource + max(x2, 0);


            dwR = 0;
            dwG = 0;
            dwB = 0;
            bSpread = false;
            for(int yFilter = iFilterYLBound; yFilter < iFilterYUBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
               lpFilter = pFilter + yFilter * iFilterW + iFilterXLBound;
               for(int xFilter = iFilterXLBound; xFilter < iFilterXUBound; xFilter++)
               {
                  if(*lpFilter >= 1)
                  {
                     dwB = lpbSource_2[0];
                     dwG = lpbSource_2[1];
                     dwR = lpbSource_2[2];

                     if(dwR + dwG + dwB > bMin3)
                     {
                        *((DWORD *) lpwDestination) |= 0x00ffffff;
                        goto breakFilter;
                     }
                  }
                  lpFilter++;
                  lpbSource_2 += 3;
               }
            }
breakFilter:
            lpwDestination += 3;
            x1++;
            x2 += 3;
         }
         y1++;
         y2++;
      }
   }

   iFilterYLBound = 0;
   iFilterYUBound = iFilterW - 1;
   iFilterXLBound = 0;
   iFilterXUBound = iFilterH - 1;

   int iFilterHalfWidth = iFilterW / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   yL = iFilterHalfWidth;
   yU = maxy1 - iFilterHalfWidth;
   xL = iFilterHalfWidthBytes;
   xU = max3x1 - iFilterHalfWidthBytes;

   y1 = yL;
   y2 = yL - iFilterHalfWidth;



   divisor = (iFilterYUBound - iFilterYLBound + 1) * (iFilterXUBound - iFilterXLBound + 1);


   for(; y1 < yU;)
   {
      lpbSource = lpbSrc + (wSrc * y2);

      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      lpwDestination = lpbDst + (wDest  * y1) + x1;
      for(; x1 < xU;)
      {
         lpbSource_1 = lpbSource + x2;
         lpFilter = pFilter;

         dwR = 0;
         dwG = 0;
         dwB = 0;
         bSpread = false;
         for(int yFilter = iFilterYLBound; yFilter <= iFilterYUBound; yFilter++)
         {
            lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
            lpFilter = pFilter + yFilter * iFilterW + iFilterXLBound;
            for(int xFilter = iFilterXLBound; xFilter <= iFilterXUBound; xFilter++)
            {
               if(*lpFilter >= 1)
               {
                  dwB = lpbSource_2[0];
                  dwG = lpbSource_2[1];
                  dwR = lpbSource_2[2];

                  if(dwR + dwG + dwB > bMin3)
                  {
                     bSpread = true;
                     break;
                  }
               }
               lpFilter++;
               lpbSource_2 += 3;
            }
         }

         if(bSpread)
         {
            *((DWORD *) lpwDestination) |= 0x00ffffff;
            lpwDestination += 3;
         }
         else
         {
            lpwDestination += 3;
         }
         x1 += 3;
         x2 += 3;
      }
      y1++;
      y2++;
   }

}



bool imaging::channel_spread(
                            ::ca::graphics *pdcDst,
                            point ptDst,
                            size size,
                            ::ca::graphics * pdcSrc,
                            point ptSrc,
                            int iChannel, int iRadius)
{
   if(size.is_empty())
      return true;

   ::ca::dib_sp dibDst(get_app());

   if(!dibDst.is_set())
      return false;

   if(!dibDst->create(size))
      return false;

   ::ca::dib_sp dibSrc(get_app());

   if(!dibSrc.is_set())
      return false;

   if(!dibSrc->create(size))
      return false;

   if(!dibSrc->from(null_point(), pdcSrc, ptSrc, size))
      return false;

   if(!channel_spread__32CC(
      dibDst,
      dibSrc,
      iChannel,
      iRadius))
      return false;

   
   if(!dibDst->to(pdcDst, ptDst, size))
      return false;

   return true;

}


bool imaging::channel_spread__32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iChannel, int iRadius)
{
   int iFilterW      = iRadius * 2 + 1;
   int iFilterH      = iRadius * 2 + 1;
   int iFilterHalfW  = iFilterW / 2;
   int iFilterHalfH  = iFilterH / 2;
   int iFilterArea   = iFilterW * iFilterH;
   int divisor       = iFilterW * iFilterH;
   BYTE *lpbSource;
   BYTE *lpbSource_1;
   BYTE *lpbSource_2;
   BYTE *lpwDestination;
   BYTE *lpFilter;
   BYTE * pFilter;

   int i;
   int x;
   int y;
   int x1;
   int y1;
   int x2;
   int y2;

   int iRadius2 = iRadius * iRadius;
   int r2;

   if(!m_alpha_spread__24CC_filterMap.Lookup(iRadius, pFilter))
   {
      pFilter = new BYTE[iFilterArea];
      m_alpha_spread__24CC_filterMap.set_at(iRadius, pFilter);
      for(y = 0; y <= iFilterHalfH; y++)
      {
         for(x = 0; x <= iFilterHalfW; x++)
         {
            x1 = iFilterHalfW - x;
            y1 = iFilterHalfH - y;
            r2 = x1 * x1 + y1 * y1;
            if(r2 <= iRadius2)
               i = 1;
            else
               i = 0;
            pFilter[x + y * iFilterW]                                   = (byte) i;
            pFilter[iFilterW - 1 - x + y * iFilterW]                    = (byte) i;
            pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW]   = (byte) i;
            pFilter[x + (iFilterH - 1 - y) * iFilterW]                  = (byte) i;
         }
      }
   }

   int cx = pdibDst->width();
   int cy = pdibDst->height();
   if(cx != pdibSrc->width()
   || cy != pdibSrc->height())
      return false;
   LPBYTE lpbDst = (LPBYTE) pdibDst->get_data();
   LPBYTE lpbSrc = (LPBYTE) pdibSrc->get_data();
   int wSrc = cx * 4;
   int wDest = cx * 4;
   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterW;
//   int maxy3 = cy - iFilterW / 2;
   int max3x1 = maxx1 * 4;
//   int max3x2 = (maxx1 - iFilterH) * 4;
//   int max3x3 = (maxx1 - iFilterH / 2) * 4;
   //int w = cx * 4;


   int iFilterXLBound;
   int iFilterXUBound;
   int iFilterYLBound;
   int iFilterYUBound;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   xLBound[0] = 0;
   xUBound[0] = cx - 1;
   yLBound[0] = 0;
   yUBound[0] = iFilterHalfH - 1;

   // left
   xLBound[1] = 0;
   xUBound[1] = iFilterHalfW - 1;
   yLBound[1] = iFilterHalfH;
   yUBound[1] = cy - iFilterHalfH - 1;

   // right
   xLBound[2] = cx - iFilterHalfW;
   xUBound[2] = cx - 1;
   yLBound[2] = iFilterHalfH;
   yUBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLBound[3] = 0;
   xUBound[3] = cx - 1;
   yLBound[3] = cy - iFilterHalfH;
   yUBound[3] = cy - 1;

   int xL;
   int xU;
   int yL;
   int yU;


   int xMax = cx - 1;
   int yMax = cy - 1;

   // limits due the filter
   int xMaxFilterBound = xMax - iFilterHalfW;
   int yMaxFilterBound = yMax - iFilterHalfH;

   int xFilterMax = iFilterW - 1;
   int yFilterMax = iFilterH - 1;

   for(i = 0; i < 4; i++)
   {
      xL = xLBound[i];
      xU = xUBound[i];
      yL = yLBound[i];
      yU = yUBound[i];

      y1 = yL;
      y2 = y1 - iFilterHalfH;
      for(; y1 <= yU;)
      {
         if(y1 < iFilterHalfH)
         {
            iFilterYLBound = iFilterHalfH - y1;
         }
         else
         {
            iFilterYLBound = 0;
         }
         if(y1 > yMaxFilterBound)
         {
            iFilterYUBound = yFilterMax - (y1 - yMaxFilterBound);
         }
         else
         {
            iFilterYUBound = yFilterMax;
         }

         lpbSource = lpbSrc + wSrc * y2;

         x1 = xL;
         x2 = (x1 - iFilterHalfW) * 4;
         lpwDestination = lpbDst + (wDest  * y1) + x1 * 4;
         for(; x1 <= xU; x1++)
         {
            if(x1 < iFilterHalfH)
            {
               iFilterXLBound = iFilterHalfH - x1;
            }
            else
            {
               iFilterXLBound = 0;
            }
            if(x1 > xMaxFilterBound)
            {
               iFilterXUBound = xFilterMax - (x1 - xMaxFilterBound);
            }
            else
            {
               iFilterXUBound = xFilterMax;
            }

            lpbSource_1 = lpbSource + max(x2, 0) + iChannel;


            for(int yFilter = iFilterYLBound; yFilter < iFilterYUBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
               lpFilter = pFilter + yFilter * iFilterW + iFilterXLBound;
               for(int xFilter = iFilterXLBound; xFilter < iFilterXUBound; xFilter++)
               {
                  if(*lpFilter >= 1)
                  {
                     if(lpbSource_2[0] > 0)
                     {
                        *((DWORD *) lpwDestination) |= 0xffffffff;
                        goto breakFilter;
                     }
                  }
                  lpFilter++;
                  lpbSource_2 += 4;
               }
            }
breakFilter:
            lpwDestination += 4;
            x2 += 4;
         }
         y1++;
         y2++;
      }
   }

   iFilterYLBound = 0;
   iFilterYUBound = iFilterW - 1;
   iFilterXLBound = 0;
   iFilterXUBound = iFilterH - 1;

   int iFilterHalfWidth = iFilterW / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 4;

   yL = iFilterHalfWidth;
   yU = maxy1 - iFilterHalfWidth;
   xL = iFilterHalfWidthBytes;
   xU = max3x1 - iFilterHalfWidthBytes;

   y1 = yL;
   y2 = yL - iFilterHalfWidth;



   divisor = (iFilterYUBound - iFilterYLBound + 1) * (iFilterXUBound - iFilterXLBound + 1);


   for(; y1 < yU;)
   {
      lpbSource = lpbSrc + (wSrc * y2) + iChannel;

      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      lpwDestination = lpbDst + (wDest  * y1) + x1;
      for(; x1 < xU;)
      {
         lpbSource_1 = lpbSource + x2;
         lpFilter = pFilter;

         for(int yFilter = iFilterYLBound; yFilter <= iFilterYUBound; yFilter++)
         {
            lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
            lpFilter = pFilter + yFilter * iFilterW + iFilterXLBound;
            for(int xFilter = iFilterXLBound; xFilter <= iFilterXUBound; xFilter++)
            {
               if(*lpFilter >= 1)
               {
                  if(lpbSource_2[0] > 0)
                  {
                     *((DWORD *) lpwDestination) |= 0xffffffff;
                     goto breakFilter2;
                  }
               }
               lpFilter++;
               lpbSource_2 += 4;
            }
         }
breakFilter2:
         lpwDestination += 4;
         x1 += 4;
         x2 += 4;
      }
      y1++;
      y2++;
   }

   return true;
}



bool imaging::pixelate(::ca::graphics *pdcDst, int xDest, int yDest, int cx, int cy, ::ca::graphics * pdcSrc, int xSrc, int ySrc, int iSize)
{

   /*::ca::graphics_sp & dibA->get_graphics()  = pthreadsafedata->m_dcA;
   ::ca::graphics_sp & dibB->get_graphics()  = pthreadsafedata->m_dcA;

   ::ca::bitmap & bitmapA  = pthreadsafedata->bitmapA;
   ::ca::bitmap & bitmapB  = pthreadsafedata->bitmapB;

   int cxDest = cx / iSize;
   int cyDest = cy / iSize;

   if(dibA->get_graphics()->get_os_data() == NULL)
   {
   ::ca::graphics_sp dcScreen;
   spgraphicsScreen->CreateDC("DISPLAY", NULL, NULL, NULL);
   dibA->get_graphics()->CreateCompatibleDC(&dcScreen);
   }
   if(dibB->get_graphics()->get_os_data() == NULL)
   {
   ::ca::graphics_sp dcScreen;
   spgraphicsScreen->CreateDC("DISPLAY", NULL, NULL, NULL);
   dibB->get_graphics()->CreateCompatibleDC(&dcScreen);
   }
   if(spbitmapB->m_hObject == NULL)
   {
   ::ca::graphics_sp dcScreen;
   spgraphicsScreen->CreateDC("DISPLAY", NULL, NULL, NULL);
   spbitmapB->CreateBitmap(cxDest + 100, cyDest + 100, 1, 32, NULL);

   }
   else
   {
   BITMAP bm;
   if(!spbitmapB->GetObject(sizeof(bm), &bm))
   throw 3500;
   if(bm.bmWidth < cx ||
   bm.bmHeight  < cy)
   {
   spbitmapB->delete_object();
   spbitmapB->CreateBitmap(cxDest + 100, cyDest + 100, 1, 32, NULL);
   }
   }
   dibB->get_graphics()->SelectObject(bitmapB);

   dibB->get_graphics()->SetStretchBltMode(HALFTONE);
   dibB->get_graphics()->StretchBlt(0, 0, cxDest, cyDest, pdcSrc, xSrc, ySrc, cx, cy, SRCCOPY);

   int x1 = xDest;
   int x2 = xDest + iSize;
   int y1;
   int y2;
   for(int x = 0; x < cxDest; x++)
   {
   y1 = yDest;
   y2 = yDest + iSize;
   for(int y = 0; y < cyDest; y++)
   {
   pdcDst->FillSolidRect(x1, y1, x2, y2, dibB->get_graphics()->GetPixel(x, y));
   y1 += iSize;
   y2 += iSize;
   }
   x1 += iSize;
   x2 += iSize;
   }

   return true;*/




   if(cx <= 0 || cy <= 0)
      return true;

   UINT user;
   UINT uiStartScanLine;
   UINT uiScanLineCount;


   primitive::memory memstorageA;
   primitive::memory memstorageB;
   primitive::memory memstorageC;

   rect rectDest;
   rectDest.left = xDest;
   rectDest.right = xDest + cx;
   rectDest.top = yDest;
   rectDest.bottom = yDest + cy;

   rect rectSrc;
   rectSrc.left = xSrc;
   rectSrc.right = xSrc + cx;
   rectSrc.top = ySrc;
   rectSrc.bottom = ySrc + cy;

   int iwDest;

   BITMAPINFO bmiDest;
   BITMAP   bmDest;
   int iLimitYDest;

   ::ca::bitmap_sp bitmapDest(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcDst,
      bmDest,
      bmiDest,
      memstorageA,
      bitmapDest,
      rectDest,
      iwDest,
      uiStartScanLine,
      uiScanLineCount,
      iLimitYDest))
   {
      return false;
   }

   LPBYTE lpbDst = memstorageA.get_data();


   int iwSrc;

   BITMAPINFO bmiSrc;
   BITMAP   bmSrc;
   int iLimitYSrc;

   ::ca::bitmap_sp bitmapSrc(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcSrc, bmSrc, bmiSrc,
      memstorageB,
      bitmapSrc,
      rectSrc,
      iwSrc,
      user,
      user,
      iLimitYSrc))
   {
      return false;
   }

   LPBYTE lpbSrc = memstorageB.get_data();

   memstorageC.allocate((cx + iSize) / iSize * (cy + iSize) / iSize);
//   LPBYTE lpc = memstorageC.get_data();


   point ptViewportDest = pdcDst->GetViewportOrg();
   point ptViewportSrc = pdcSrc->GetViewportOrg();

   int xvpDest = xDest + ptViewportDest.x;
   int xvpSrc = xSrc + ptViewportSrc.x;

   int iLimitX = cx;

   if(bmDest.bmWidth - xvpDest < iLimitX)
   {
      iLimitX = bmDest.bmWidth - xvpDest;
   }
   if(bmSrc.bmWidth - xvpSrc < iLimitX)
   {
      iLimitX = bmSrc.bmWidth - xvpSrc;
   }


   if(xvpDest < 0)
      return false;
   if(xvpSrc < 0)
      return false;

   int iLimitY = min(iLimitYDest, iLimitYSrc);

   pixelate_24CC(
      lpbDst + xvpDest * 3,
      0,
      0,
      iwDest,
      iLimitX,
      iLimitY,
      lpbSrc + xvpSrc * 3,
      0,
      0,
      iwSrc,
      iSize);


   ::ca::bitmap * pbmpOld = &pdcDst->GetCurrentBitmap();
   if(pbmpOld == NULL)
   {
      ::ca::graphics_sp graphicsMem(get_app());
         graphicsMem->CreateCompatibleDC(pdcDst);
      if(!SetDIBits(
         (HDC)graphicsMem->get_os_data(),
         (HBITMAP) bitmapDest->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDest,
         DIB_RGB_COLORS))
         throw 6000;
      ::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(bitmapDest);
      if(!pdcDst->BitBlt(xDest, yDest, cx, cy, graphicsMem, xSrc, ySrc, SRCCOPY))
      {
         ASSERT(FALSE);
      }
      graphicsMem->SelectObject(pbmpMemOld);
   }
   else
   {
      ::ca::bitmap_sp bitmap(get_app());
      bitmap->CreateCompatibleBitmap(pdcDst, 1, 1);
//      ::ca::bitmap * pbitmap = pdcDst->SelectObject(bitmap);
      if(!SetDIBits(
         (HDC) pdcDst->get_os_data(),
         (HBITMAP) bitmapDest->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDest,
         DIB_RGB_COLORS))
      {
         pdcDst->SelectObject(bitmapDest);
         return false;
      }
      pdcDst->SelectObject(bitmapDest);
   }

   return true;

}

void imaging::pixelate_24CC(
                           LPBYTE   lpbDst,
                           int      xDest,
                           int      yDest,
                           int      wDest,
                           int      cx,
                           int      cy,
                           LPBYTE   lpbSrc,
                           int      xSrc,
                           int      ySrc,
                           int      wSrc,
                           int      iSize)
{
   UNREFERENCED_PARAMETER(xDest);
   UNREFERENCED_PARAMETER(yDest);
   UNREFERENCED_PARAMETER(xSrc);
   UNREFERENCED_PARAMETER(ySrc);
   int      divisor;
   BYTE *   lpbSource;
   BYTE *   lpwDestination;
   BYTE *   lpwDestination_1;
   BYTE *   lpwDestination_2;
   BYTE *   lpbSource_1;
   BYTE *   lpbSource_2;

   int iFilterWidth = iSize;
   int iFilterHeight = iSize;
   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterWidth;
//   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 3;
//   int max3x2 = (maxx1 - iFilterHeight) * 3;
//   int max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //int w = cx * 3;

   DWORD dwR;
   DWORD dwG;
   DWORD dwB;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   yLBound[0] = 0;
   yUBound[0] = iFilterWidth / 2;
   xLBound[0] = 0;
   xUBound[0] = max3x1;

   // left
   yLBound[1] = iFilterWidth / 2;
   yUBound[1] = maxy1 - iFilterWidth / 2;
   xLBound[1] = 0;
   xUBound[1] = iFilterWidth / 2;

   // right
   yLBound[2] = iFilterWidth / 2;
   yUBound[2] = maxy1- iFilterWidth / 2;
   xLBound[2] = max3x1 - iFilterWidth / 2;
   xUBound[2] = max3x1;

   // bottom
   yLBound[3] = maxy1 - iFilterWidth / 2;
   yUBound[3] = maxy1;
   xLBound[3] = 0;
   xUBound[3] = max3x1;

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLBound[i];
   int yU = yUBound[i];
   int xL = xLBound[i];
   int xU = xUBound[i];
   for(int y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   lpbSource = lpbSrc + (wSrc * max((y1 - iFilterWidth / 2), 0));
   lpwDestination = lpbDst + (wDest  * y1);
   for(int x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   lpbSource_1 = lpbSource + ((max(x1 - iFilterWidth / 2 * 3, 0)));
   lpFilter = pFilter;
   //            lpConv = pConv;

   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   lpbSource_2 = lpbSource_1 + (wSrc * y2);
   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *lpbSource_2++ * *lpFilter;
   dwG += *lpbSource_2++ * *lpFilter;
   dwB += *lpbSource_2++ * *lpFilter++;

   }
   }
   lpwDestination_1 = lpwDestination + x1;
   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   lpwDestination_1[0] = max(0, min(dwR, 255));
   lpwDestination_1[1] = max(0, min(dwG, 255));
   lpwDestination_1[2] = min(0, min(dwB, 255));
   }
   else
   {
   lpwDestination_1[0] = dwR / divisor;
   lpwDestination_1[1] = dwG / divisor;
   lpwDestination_1[2] = dwB / divisor;
   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   divisor = (iFilterYEnd - iFilterYBegin)
      * (iFilterXEnd - iFilterXBegin);


   int cDest   = wDest - (iFilterWidth * 3);
   int cSrc    = wSrc  - (iFilterWidth * 3);
   int iSize3  = iSize * 3;

   int cyDest  = wDest * iSize;
   int cySrc   = wSrc  * iSize;



   lpbSource         = lpbSrc;
   lpwDestination    = lpbDst;
   for(; y1 < yU;)
   {
      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      for(; x1 < xU;)
      {
         lpbSource_1 = lpbSource + x2;

         dwR = 0;
         dwG = 0;
         dwB = 0;
         lpbSource_2 = lpbSource_1;
         int yFilter;
         for(yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwR += *lpbSource_2++;
               dwG += *lpbSource_2++;
               dwB += *lpbSource_2++;
            }
            lpbSource_2 += cSrc;
         }

         dwR /= divisor;
         dwG /= divisor;
         dwB /= divisor;

         lpwDestination_1 = lpwDestination + x2;
         lpwDestination_2 = lpwDestination_1;
         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(int xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               lpwDestination_2[0] = (BYTE) dwR;
               lpwDestination_2[1] = (BYTE) dwG;
               lpwDestination_2[2] = (BYTE) dwB;
               lpwDestination_2 += 3;
            }
            lpwDestination_2 += cDest;
         }


         x1 += iSize3;
         x2 += iSize3;
      }
      y1 += iSize;
      y2 += iSize;
      lpbSource         += cySrc;
      lpwDestination    += cyDest;
   }

}

bool imaging::alpha_pixelate(
                            ::ca::graphics *pdcDst,
                            int xDest,
                            int yDest,
                            int cx,
                            int cy,
                            ::ca::graphics * pdcSrc1,
                            int xSrc1,
                            int ySrc1,
                            ::ca::graphics * pdcSrc2,
                            int xSrc2,
                            int ySrc2,
                            int iSize,
                            int iAlpha)
{
   if(cx <= 0 || cy <= 0)
      return true;

   primitive::memory memstorageA;
   primitive::memory memstorageB;
   primitive::memory memstorageC;


   UINT user;
   UINT uiStartScanLine;
   UINT uiScanLineCount;


   rect rectDest;
   rectDest.left = xDest;
   rectDest.right = xDest + cx;
   rectDest.top = yDest;
   rectDest.bottom = yDest + cy;

   rect rectSrc1;
   rectSrc1.left = xSrc1;
   rectSrc1.right = xSrc1 + cx;
   rectSrc1.top = ySrc1;
   rectSrc1.bottom = ySrc1 + cy;

   rect rectSrc2;
   rectSrc2.left = xSrc2;
   rectSrc2.right = xSrc2 + cx;
   rectSrc2.top = ySrc2;
   rectSrc2.bottom = ySrc2 + cy;

   int iwDest;

   BITMAPINFO bmiDest;
   BITMAP   bmDest;
   int iLimitYDest;

   ::ca::bitmap_sp bitmapDest(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcDst,
      bmDest,
      bmiDest,
      memstorageA,
      bitmapDest,
      rectDest,
      iwDest,
      uiStartScanLine,
      uiScanLineCount,
      iLimitYDest))
   {
      return false;
   }

   LPBYTE lpbDst = memstorageA.get_data();


   int iwSrc1;
   int iwSrc2;

   BITMAPINFO bmiSrc1;
   BITMAP   bmSrc1;
   int iLimitYSrc1;

   ::ca::bitmap_sp bitmapSrc1(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcSrc1, bmSrc1, bmiSrc1,
      memstorageB,
      bitmapSrc1,
      rectSrc1,
      iwSrc1,
      user,
      user,
      iLimitYSrc1))
   {
      return false;
   }

   LPBYTE lpbSrc1 = memstorageB.get_data();

   BITMAPINFO bmiSrc2;
   BITMAP   bmSrc2;
   int iLimitYSrc2;

   ::ca::bitmap_sp bitmapSrc2(get_app());

   if(!GetDeviceContext24BitsCC(
      pdcSrc2, bmSrc2, bmiSrc2,
      memstorageC,
      bitmapSrc2,
      rectSrc2,
      iwSrc2,
      user,
      user,
      iLimitYSrc2))
   {
      return false;
   }

   LPBYTE lpbSrc2 = memstorageC.get_data();

   point ptViewportDest = pdcDst->GetViewportOrg();
   point ptViewportSrc1 = pdcSrc1->GetViewportOrg();
   point ptViewportSrc2 = pdcSrc2->GetViewportOrg();

   int xvpDest = xDest + ptViewportDest.x;
   int xvpSrc1 = xSrc1 + ptViewportSrc1.x;
   int xvpSrc2 = xSrc2 + ptViewportSrc2.x;

   int iLimitX = cx;

   if(bmDest.bmWidth - xvpDest < iLimitX)
   {
      iLimitX = bmDest.bmWidth - xvpDest;
   }
   if(bmSrc1.bmWidth - xvpSrc1 < iLimitX)
   {
      iLimitX = bmSrc1.bmWidth - xvpSrc1;
   }
   if(bmSrc2.bmWidth - xvpSrc2 < iLimitX)
   {
      iLimitX = bmSrc2.bmWidth - xvpSrc2;
   }


   if(xvpDest < 0)
      return false;
   if(xvpSrc1 < 0)
      return false;
   if(xvpSrc2 < 0)
      return false;

   int iLimitY = min(min(iLimitYDest, iLimitYSrc1), iLimitYSrc2);

   alpha_pixelate_24CC(
      lpbDst + xvpDest * 3,
      0,
      0,
      iwDest,
      iLimitX,
      iLimitY,
      lpbSrc1 + xvpSrc1 * 3,
      0,
      0,
      iwSrc1,
      lpbSrc2 + xvpSrc2 * 3,
      0,
      0,
      iwSrc2,
      iSize,
      iAlpha);


   ::ca::bitmap * pbmpOld = &pdcDst->GetCurrentBitmap();
   if(pbmpOld == NULL)
   {
      ::ca::graphics_sp graphicsMem(get_app());
         graphicsMem->CreateCompatibleDC(pdcDst);
      if(!SetDIBits(
         (HDC)graphicsMem->get_os_data(),
         (HBITMAP) bitmapDest->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDest,
         DIB_RGB_COLORS))
         throw 6000;
      ::ca::bitmap * pbmpMemOld = graphicsMem->SelectObject(bitmapDest);
      if(!pdcDst->BitBlt(xDest, yDest, cx, cy, graphicsMem, xDest, yDest, SRCCOPY))
      {
         ASSERT(FALSE);
      }
      graphicsMem->SelectObject(pbmpMemOld);
   }
   else
   {
      ::ca::bitmap_sp bitmap(get_app());
      bitmap->CreateCompatibleBitmap(pdcDst, 1, 1);
//      ::ca::bitmap * pbitmap = pdcDst->SelectObject(bitmap);
      if(!SetDIBits(
         (HDC) pdcDst->get_os_data(),
         (HBITMAP) bitmapDest->get_os_data(),
         uiStartScanLine,
         uiScanLineCount,
         lpbDst,
         &bmiDest,
         DIB_RGB_COLORS))
      {
         pdcDst->SelectObject(bitmapDest);
         return false;
      }
      pdcDst->SelectObject(bitmapDest);
   }

   return true;

}

void imaging::alpha_pixelate_24CC(
                                LPBYTE lpbDst,
                                int xDest,
                                int yDest,
                                int wDest,
                                int cx,
                                int cy,
                                LPBYTE lpbSrc1,
                                int xSrc1,
                                int ySrc1,
                                int wSrc1,
                                LPBYTE lpbSrc2,
                                int xSrc2,
                                int ySrc2,
                                int wSrc2,
                                int iSize,
                                int iAlpha)
{
   UNREFERENCED_PARAMETER(xDest);
   UNREFERENCED_PARAMETER(yDest);
   UNREFERENCED_PARAMETER(xSrc1);
   UNREFERENCED_PARAMETER(ySrc1);
   UNREFERENCED_PARAMETER(xSrc2);
   UNREFERENCED_PARAMETER(ySrc2);
//   const int constFilterWidth = 3;
   //   const int constFilterHeight = 3;
   int divisor = iSize * iSize;
   BYTE *lpbSource1;
   BYTE *lpbSource2;
   BYTE *lpwDestination;
   BYTE *lpwDestination_1;
   BYTE *lpwDestination_2;
   BYTE *lpbSource1_1;
   BYTE *lpbSource1_2;
   BYTE *lpbSource2_1;
   BYTE *lpbSource2_2;
   //   WORD *lpwDestination_2;
   //   BYTE *lpFilter;
   //DWORD *lpConv;
   //   BYTE pFilter[constFilterHeight *constFilterWidth];
   //DWORD pConv[constFilterHeight * constFilterWidth * 3];
   //   memset(pFilter, 1, constFilterHeight * constFilterWidth);

   int iFilterWidth = iSize;
   int iFilterHeight = iSize;
   int maxx1 = cx;
   int maxy1 = cy;
//   int maxy2 = cy - iFilterWidth;
//   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 3;
//   int max3x2 = (maxx1 - iFilterHeight) * 3;
//   int max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //int bm3Width = (cy * 3 + 3) & ~0x3L;
//   int w = cx * 3;
   //   memcpy(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   memcpy(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(int y = 0; y < cy; y++)
   {
   lpbSource = lpbSrc + wSrc * y;
   lpwDestination = lpbDst + wDest * y;
   for(int x = 0; x < w; x++)
   {
   *lpwDestination = *lpbSource;
   lpwDestination++;
   lpbSource++;
   }
   }*/
   DWORD dwR1;
   DWORD dwG1;
   DWORD dwB1;
   DWORD dwR2;
   DWORD dwG2;
   DWORD dwB2;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLBound[4];
   int yUBound[4];
   int xLBound[4];
   int xUBound[4];

   // top
   yLBound[0] = 0;
   yUBound[0] = iFilterWidth / 2;
   xLBound[0] = 0;
   xUBound[0] = max3x1;

   // left
   yLBound[1] = iFilterWidth / 2;
   yUBound[1] = maxy1 - iFilterWidth / 2;
   xLBound[1] = 0;
   xUBound[1] = iFilterWidth / 2;

   // right
   yLBound[2] = iFilterWidth / 2;
   yUBound[2] = maxy1- iFilterWidth / 2;
   xLBound[2] = max3x1 - iFilterWidth / 2;
   xUBound[2] = max3x1;

   // bottom
   yLBound[3] = maxy1 - iFilterWidth / 2;
   yUBound[3] = maxy1;
   xLBound[3] = 0;
   xUBound[3] = max3x1;

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLBound[i];
   int yU = yUBound[i];
   int xL = xLBound[i];
   int xU = xUBound[i];
   for(int y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   lpbSource = lpbSrc + (wSrc * max((y1 - iFilterWidth / 2), 0));
   lpwDestination = lpbDst + (wDest  * y1);
   for(int x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   lpbSource_1 = lpbSource + ((max(x1 - iFilterWidth / 2 * 3, 0)));
   lpFilter = pFilter;
   //            lpConv = pConv;

   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   lpbSource_2 = lpbSource_1 + (wSrc * y2);
   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *lpbSource_2++ * *lpFilter;
   dwG += *lpbSource_2++ * *lpFilter;
   dwB += *lpbSource_2++ * *lpFilter++;

   }
   }
   lpwDestination_1 = lpwDestination + x1;
   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   lpwDestination_1[0] = max(0, min(dwR, 255));
   lpwDestination_1[1] = max(0, min(dwG, 255));
   lpwDestination_1[2] = min(0, min(dwB, 255));
   }
   else
   {
   lpwDestination_1[0] = dwR / divisor;
   lpwDestination_1[1] = dwG / divisor;
   lpwDestination_1[2] = dwB / divisor;
   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   divisor = 255 * (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );

   int iRate1 = iAlpha;
   int iRate2 = 255 - iAlpha;

   DWORD dwR;
   DWORD dwG;
   DWORD dwB;

   int cFilter  = wDest - iFilterWidth * 3;
   int cFilter1 = wSrc1 - iFilterWidth * 3;
   int cFilter2 = wSrc2 - iFilterWidth * 3;

   int iSize3 = iSize * 3;

   for(; y1 < yU;)
   {
      lpbSource1     = lpbSrc1 + (wSrc1 * y2);
      lpbSource2     = lpbSrc2 + (wSrc2 * y2);
      lpwDestination = lpbDst + (wDest * y2);

      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;

      for(; x1 < xU;)
      {
         lpbSource1_1 = lpbSource1 + x2;
         lpbSource2_1 = lpbSource2 + x2;


         dwR1 = 0;
         dwG1 = 0;
         dwB1 = 0;
         dwR2 = 0;
         dwG2 = 0;
         dwB2 = 0;
         lpbSource1_2 = lpbSource1_1;
         lpbSource2_2 = lpbSource2_1;
         int yFilter;
         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(int xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               dwR1 += *lpbSource1_2++;
               dwG1 += *lpbSource1_2++;
               dwB1 += *lpbSource1_2++;
               dwR2 += *lpbSource2_2++;
               dwG2 += *lpbSource2_2++;
               dwB2 += *lpbSource2_2++;
            }
            lpbSource1_2 += cFilter1;
            lpbSource2_2 += cFilter2;
         }

         dwR = (dwR1 * iRate1 + dwR2 * iRate2) / divisor;
         dwG = (dwG1 * iRate1 + dwG2 * iRate2) / divisor;
         dwB = (dwB1 * iRate1 + dwB2 * iRate2) / divisor;

         lpwDestination_1 = lpwDestination + x2;
         lpwDestination_2 = lpwDestination_1;
         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(int xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               lpwDestination_2[0] = (BYTE) dwR;
               lpwDestination_2[1] = (BYTE) dwG;
               lpwDestination_2[2] = (BYTE) dwB;
               lpwDestination_2 += 3;
            }
            lpwDestination_2 += cFilter;
         }


         x1 += iSize3;
         x2 += iSize3;
      }
      y1 += iSize;
      y2 += iSize;
   }

}

void imaging::free(FIBITMAP * pfibitmap)
{
   FreeImage_Unload(pfibitmap);
}


bool imaging::HueVRCP(
                      ::ca::graphics * pdc,
                      ::ca::bitmap * pbitmap,
                      int x,
                      int y,
                      int cx,
                      int cy,
                      COLORREF crHue,
                      double dCompress // de 0 a 1
                      )
{
   //COLORREF cr3dface = GetSysColor(COLOR_3DFACE);
//   COLORREF cr3dshadow = GetSysColor(COLOR_3DSHADOW);
   //BYTE uch3dfaceR = rgba_get_r(cr3dface);
   //BYTE uch3dfaceG = rgba_get_g(cr3dface);
   //BYTE uch3dfaceB = rgba_get_b(cr3dface);
//   BYTE uch3dshadowR = rgba_get_r(cr3dshadow);
//   BYTE uch3dshadowG = rgba_get_g(cr3dshadow);
//   BYTE uch3dshadowB = rgba_get_b(cr3dshadow);

//   COLORREF cr3dhighlight = GetSysColor(COLOR_3DHILIGHT);
//   BYTE uch3dhighlightR = rgba_get_r(cr3dhighlight);
//   BYTE uch3dhighlightG = rgba_get_g(cr3dhighlight);
//   BYTE uch3dhighlightB = rgba_get_b(cr3dhighlight);



   class size size = pbitmap->get_size();

   UINT uiScanLines = size.cy;
   UINT cbLine = size.cx * 4;
   UINT cbImage = size.cy * cbLine;
//   UINT cbMask = bitmap.bmHeight * bitmap.bmWidth;


   BITMAPINFO bmi;

   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bmi.bmiHeader.biWidth = size.cx;
   bmi.bmiHeader.biHeight = - size.cy;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 32;
   bmi.bmiHeader.biCompression = BI_RGB;
   bmi.bmiHeader.biSizeImage = 0;
   bmi.bmiHeader.biXPelsPerMeter = 1;
   bmi.bmiHeader.biYPelsPerMeter = 1;
   bmi.bmiHeader.biClrUsed = 0;
   bmi.bmiHeader.biClrImportant = 0;

   LPBYTE lpbData = (LPBYTE) malloc(cbImage);
   //LPBYTE lpbShadow = lpbData;

   if(!GetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) pbitmap->get_os_data(),
      0,
      uiScanLines,
      lpbData,
      &bmi,
      DIB_RGB_COLORS))
   {
      return false;
   }


   COLORREF cra[256];

   color color;
   int i;
   for(i = 0; i < 256; i++)
   {
      color.set_rgb(crHue);
      color.hls_mult(1.0, (i / 255.0) * (1.0 - dCompress) + dCompress, 1.0);
      cra[i] = color.get_bgr();
   }


   LPBYTE lpbBase = lpbData + cbLine * y + x * 4;

//   COLORREF crBtnFace = GetSysColor(COLOR_BTNFACE);
//   COLORREF crBtnShad = GetSysColor(COLOR_BTNSHADOW);
//   COLORREF crWndBack = GetSysColor(COLOR_WINDOW);

//   BYTE bRBtnFace = rgba_get_r(crBtnFace);
//   BYTE bGBtnFace = rgba_get_g(crBtnFace);
///   BYTE bBBtnFace = rgba_get_b(crBtnFace);

//   BYTE bRBtnShad = rgba_get_r(crBtnShad);
//   BYTE bGBtnShad = rgba_get_g(crBtnShad);
//   BYTE bBBtnShad = rgba_get_b(crBtnShad);

//   BYTE bRWndBack = rgba_get_r(crWndBack);
//   BYTE bGWndBack = rgba_get_g(crWndBack);
//   BYTE bBWndBack = rgba_get_b(crWndBack);

   for(i = 0; i < cy; i ++)
   {
      LPBYTE lpb = lpbBase + cbLine * i;
      for(int j = 0; j < cx; j++)
      {
         COLORREF cr = (cra[(lpb[0] + lpb[1] + lpb[2]) / 3]) | lpb[3] << 24;
         *((DWORD *) lpb) = cr;
         lpb += 4;
      }
   }


   if(!SetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) pbitmap->get_os_data(),
      0,
      uiScanLines,
      lpbData,
      &bmi,
      DIB_RGB_COLORS))
   {
      return false;
   }


   ::free(lpbData);

   return true;

}


void imaging::AlphaTextOut(::ca::graphics *pdc, int left, int top, const char * lpcsz, int len, COLORREF cr, double dBlend)
{
   string str(lpcsz, len);
   if(dBlend <= 0.0)
      return;
   if(dBlend >= 1.0)
   {
      pdc->SetTextColor(cr);
      pdc->TextOut(left, top, str);
      return;
   }
   pdc->SetTextColor(ARGB((BYTE) (255 * dBlend), GetRValue(cr), GetGValue(cr), GetBValue(cr)));
   pdc->TextOut(left, top, str);
}


