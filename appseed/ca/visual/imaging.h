#pragma once


struct FIBITMAP;

#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13

#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(rgba_get_b(clr), rgba_get_g(clr), rgba_get_r(clr)))

class image_list;

class CLASS_DECL_ca imaging : 
   virtual public ::radix::object
{
public:
   class CSysColorMap
   {
      public:
         // use DWORD instead of RGBQUAD so we can compare two RGBQUADs easily
         DWORD rgbqFrom;
         int iSysColorTo;
   };

protected:
   ::collection::map < int, int, LPBYTE, LPBYTE > m_alpha_spread__24CC_filterMap;


public:
   imaging(::ca::application * papp);
    ~imaging();


   static const CSysColorMap s_psyscolormap[];


   virtual void pixelate_24CC(LPBYTE lpbDest, int xDest, int yDest, int wDest, int cx, int cy, LPBYTE lpbSrc, int xSrc, int ySrc, int wSrc, int iSize);
   virtual bool pixelate(::ca::graphics *pdcDest, int xDest, int yDest, int cx, int cy, ::ca::graphics * pdcSrc, int xSrc, int ySrc, int iSize);

   virtual void alpha_pixelate_24CC(LPBYTE lpbDest, int xDest, int yDest, int wDest, int cx, int cy, LPBYTE lpbSrc1, int xSrc1, int ySrc1, int wSrc1, LPBYTE lpbSrc2, int xSrc2, int ySrc2, int wSrc2, int iSize, int iAlpha);
   virtual bool alpha_pixelate(::ca::graphics *pdcDest, int xDest, int yDest, int cx, int cy, ::ca::graphics * pdcSrc1, int xSrc1, int ySrc1, ::ca::graphics * pdcSrc2, int xSrc2, int ySrc2, int iSize, int iAlpha);


   virtual void blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iRadius);
   virtual void blur_32CC_r2(::ca::dib * pdibDst, ::ca::dib * pdibSrc);
   
   virtual bool channel_gray_blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iChannel, int iRadius);
   virtual bool channel_gray_blur(::ca::graphics * pdcDest, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iChannel, int iRadius);
   virtual bool channel_gray_blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iChannel, int iFilterWidth, int iFilterHeight,  LPBYTE lpbFilter);
   virtual bool channel_gray_blur(::ca::graphics * pdcDest, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iChannel, class size sizeFilter,  LPBYTE lpbFilter);
   virtual bool channel_alpha_gray_blur_32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iChannel, int iRadius);
   virtual bool channel_alpha_gray_blur(::ca::graphics * pdcDest, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iChannel, int iRadius);

   void alpha_spread_R2_24CC(LPBYTE lpbDest, int xDest, int yDest, int wDest, int cx, int cy, LPBYTE lpbSrc, int ySrc, int xSrc, int wSrc, BYTE bMin);
   void alpha_spread__24CC(LPBYTE lpbDest, int xDest, int yDest, int wDest, int cx, int cy, LPBYTE lpbSrc, int ySrc, int xSrc, int wSrc, BYTE bMin, int iRadius);

   bool channel_spread__32CC(::ca::dib * pdibDst, ::ca::dib * pdibSrc, int iChannel, int iRadius);

   bool alpha_spread_R2(
      ::ca::graphics * pdcDest, 
      point ptDst,
      size size, 
      ::ca::graphics * pdcSrc, 
      point ptSrc,
      BYTE bMin);

   bool alpha_spread(
      ::ca::graphics * pdcDest, 
      point ptDst,
      size size,
      ::ca::graphics * pdcSrc, 
      point ptSrc,
      BYTE bMin,
      int iRadius);

   bool channel_spread(
      ::ca::graphics * pdcDest, 
      point ptDst,
      size size,
      ::ca::graphics * pdcSrc, 
      point ptSrc,
      int iChannel,
      int iRadius);

   bool true_blend(::ca::graphics * pdc, LPCRECT lpcrect, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork = NULL, ::ca::dib * pdibWork2 = NULL, ::ca::dib * pdibWork3 = NULL);

   bool true_blend(::ca::graphics * pdc, point pt, size size, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork = NULL, ::ca::dib * pdibWork2 = NULL, ::ca::dib * pdibWork3 = NULL);
   
   bool blur(::ca::graphics * pdcDst, point ptDst, size size, ::ca::graphics * pdcSrc, point ptSrc, int iRadius);

   void color_blend_24CC(
      LPBYTE lpbA,
      int x1,
      int y1,
      int w1,
      int cx,
      int cy,
      COLORREF cr,
      LPBYTE lpbC,
      int x3,
      int y3,
      int w3);


   bool color_blend(::ca::graphics * pdc, point pt, size size, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork = NULL, ::ca::dib * pdibWork2 = NULL);
   bool color_blend(::ca::graphics * pdc, LPCRECT lpcrect, ::ca::graphics * pdcColorAlpha, point ptAlpha, ::ca::dib * pdibWork = NULL);

   bool color_blend(::ca::graphics * pdc, LPCRECT lpcrect, ::ca::graphics * pdcColorAlpha, point ptAlpha, double dBlend);
   bool color_blend(::ca::graphics * pdc, point pt, size size, ::ca::graphics * pdcColorAlpha, point ptAlpha, double dBlend);
   bool color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr, ::ca::graphics * pdcAlpha, point ptAlpha);
   bool pre_color_blend(::ca::graphics * pdcColorAlpha, ::ca::graphics * pdcAlpha, COLORREF cr);
   bool clip_color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr,   ::ca::graphics * pdcAlpha, point ptAlpha);

   bool color_blend(::ca::graphics * pdc, int x, int y, int cx, int cy, COLORREF cr, BYTE bAlpha);
   bool color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha);
   bool color_blend(::ca::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha);
   bool color_blend(::ca::graphics * pdc,   const __rect64 * lpcrect, COLORREF cr,   BYTE alpha);
   
   bool color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha, ::ca::dib * pdibWork);
   bool color_blend(::ca::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha, ::ca::dib * pdibWork);

   bool prepare_blend(::ca::dib * pdib, point pt, size size, COLORREF cr, BYTE alpha, ::ca::dib * pdibWork);
   bool prepare_blend(::ca::dib * pdib, LPCRECT lpcrect, COLORREF cr, BYTE alpha, ::ca::dib * pdibWork);

   bool clip_color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha);
   bool clip_color_blend(::ca::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha);
   
   bool clip_color_blend(::ca::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha, ::ca::region * prgnClip);
   bool clip_color_blend(::ca::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha, ::ca::region * prgnClip);

   static bool CreateBitmap(
      ::ca::graphics * pdc, 
      ::ca::bitmap * pbitmapOld,
      ::ca::bitmap * pbitmap, 
      BITMAP * pbmp, 
      int cx, 
      int cy);

   static bool CreateBitmap(
      ::ca::graphics * pdc, 
      ::ca::graphics * pdcScreen, 
      ::ca::bitmap * pbitmap, 
      ::ca::bitmap * pbitmapOld,
      BITMAP * pbmp, 
      int cx, 
      int cy);
   
   void AlphaTextOut(::ca::graphics * pdc, int left, int top, const char * lpcsz, int len, COLORREF cr, double dBlend);
   
   bool ClipSave(
      ::ca::graphics * pdc,
      ::ca::bitmap * pbitmap,
      ::ca::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect);

   bool ClipRestore(
      ::ca::graphics * pdc,
      ::ca::bitmap * pbitmap,
      ::ca::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect);

   bool ClipSave(
      ::ca::graphics * pdc,
      ::ca::bitmap * pbitmap,
      ::ca::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect,
      ::ca::region * prgnClip);

   bool ClipRestore(
      ::ca::graphics * pdc,
      ::ca::bitmap * pbitmap,
      ::ca::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect,
      ::ca::region * prgnClip);

   bool GetDeviceContext24BitsCC(
      ::ca::graphics *pdc,
      BITMAP & bm,
      BITMAPINFO & bmi,
      primitive::memory & memomrystorage,
      ::ca::bitmap * pbitmap,
      LPCRECT lpcrect,
      int & iWidth,
      UINT & uiStartScanLine,
      UINT & uiScanLineCount,
      int & iLimitYParam);






   bool GrayVRCP(
      ::ca::graphics * pgraphics,
      ::ca::bitmap * pbitmap,
      ::ca::bitmap * pbitmapMask,
      int x,
      int y,
      int cx,
      int cy,
      COLORREF crTransparent);

   bool HueVRCP(
      ::ca::graphics * pgraphics,
      ::ca::bitmap * pbitmap,
      int x,
      int y,
      int cx,
      int cy,
      COLORREF crHue,
      double dCompress);

   bool GrayVRCP(
      ::ca::graphics * pgraphics,
      ::ca::bitmap * pbitmap,
      ::ca::bitmap * pbitmapMask,
      LPCRECT lpcrect,
      COLORREF crTransparent);

   bool GrayVRCP(
      ::ca::graphics * pgraphics,
      int x,
      int y,
      int cx,
      int cy,
      COLORREF crAlpha);

   bool CreateHueImageList(
      ::ca::graphics * pdc,
      image_list * pilGray,
      image_list * pilParam,
      COLORREF crHue,
      double dCompress);


   bool Createcolor_blend_ImageList(
      image_list * pilGray,
      image_list * pilParam,
      COLORREF cr,
      BYTE bAlpha);



   bool BitmapBlend2(::ca::graphics * pdcDst, point pt, size size, ::ca::graphics * pdcSrc, point ptSrc,
      ::ca::graphics * pdcAlpha, // alpha information device (in alpha channel) 
      point ptAlpha);
   
   bool bitmap_blend(::ca::graphics * pdcDst, point pt, size size, ::ca::graphics * pdcSrc, point ptSrc,
      ::ca::graphics * pdcAlpha, // alpha information device (in red channel)
      point ptAlpha,
      BYTE alphaConstant = 255,
      ::ca::dib * pdibWorkA = NULL,
      ::ca::dib * pdibWorkB = NULL);


   bool bitmap_blend(::ca::graphics * pdcDst, point pt, size size, ::ca::dib * pdibSrc, point ptSrc,
      ::ca::dib * pdibAlpha, // alpha information device (in red channel)
      point ptAlpha,
      BYTE alphaConstant = 255);

   bool bitmap_blend(::ca::graphics * pdcDst, point pt, size size, ::ca::graphics * pdcSrc, point ptSrc,
      ::ca::graphics * pdcAlpha, // alpha information device (in alpha channel)
      point ptAlpha,
      ::ca::graphics * pdcAlphaComplement, // alpha information device (in alpha channel)
      point ptAlphaComplement);

   bool bitmap_blend(::ca::graphics * pdcDst, point pt, size size, 
      ::ca::graphics * pdcSrcWithAlpha, // source device
      point ptSrc);

   bool BitmapDivBlend(::ca::graphics * pdcDst, point pt, size size, ::ca::graphics * pdcSrc, point ptSrc, BYTE bAlpha);

   bool bitmap_blend(::ca::graphics * pdcDst, point pt, size size, ::ca::graphics * pdcSrc, point ptSrc, BYTE bAlpha);

   void BitmapBlend24CC(
      LPBYTE lpbA,
      int x1,
      int y1,
      int w1,
      int cx,
      int cy,
      LPBYTE lpbB,
      int x2,
      int y2,
      int w2,
      LPBYTE lpbC,
      int x3,
      int y3,
      int w3);
   void BitmapBlend24CC(
      LPBYTE lpbDest,
      int xDest,
      int yDest,
      int wDest,
      int cx,
      int cy,
      LPBYTE lpbSrc,
      int xSrc,
      int ySrc,
      int wSrc,
      BYTE bAlpha);

   virtual bool color_blend_3dRect(::ca::graphics * pdc, LPCRECT lpcrect, COLORREF crTopLeft, BYTE bAlphaTopLeft, COLORREF crBottomRight, BYTE bAlphaBottomRight);

   virtual bool ColorInvert(::ca::graphics * pdc, int x, int y, int cx, int cy);

   virtual ::ca::bitmap_sp CreateDIBitmap(::ca::graphics * pdc, FIBITMAP * pFreeImage);
   virtual ::ca::bitmap_sp CreateBitmap(::ca::graphics * pdc,FIBITMAP * pFreeImage);

/*   virtual ::ca::bitmap * LoadSysColorBitmap(
      ::ca::graphics * pdcCompatible, 
      HINSTANCE hInst, 
      HRSRC hRsrc,
      BOOL bMono = false);*/

   virtual FIBITMAP * LoadImageFile(var varFile, ::ca::application * papp);
   virtual FIBITMAP * LoadImageFile(ex1::file * pfile);
   virtual ::ca::bitmap_sp FItoHBITMAP(FIBITMAP * pfibitmap, bool bDestroyFI);
   virtual FIBITMAP * HBITMAPtoFI(::ca::bitmap_sp hbitmap);
   virtual ::ca::bitmap_sp LoadImageSync(const char * lpcszImageFilePath, ::ca::application * papp);
   virtual void SaveJpeg(const char * lpcszFile, ::ca::bitmap_sp pbitmap);
   virtual void SavePng(const char * lpcszFile, ::ca::bitmap_sp pbitmap);
   virtual void SavePng(const char * lpcszFile, FIBITMAP * pfi, bool bUnload);

   virtual void free(FIBITMAP * pfibitmap);
};

VOID EmbossedTextOut(
     HDC                    hDC,
     int                    x,
     int                    y,
//     char *                  lpsz,
     LPTSTR                  lpsz,
     UINT                   cb,
     COLORREF               crText,
     COLORREF               crShadow,
     int                    cx,
     int                    cy);   

HFONT CreateScaledFont(
     HDC                    hDC,
     LPRECT                 lpRect,
    LPRECT               lpWndRect,
     LPTSTR                  lpszFormat,
     int                    anPosX[],
     int* nPosY);

void GetMultiLineTextExtent(HDC hDC, stringa *pArray, LPSIZE lpSize);
void DrawMultiLineText(HDC hDC, stringa *pArray);


