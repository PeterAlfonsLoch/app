#pragma once


struct FIBITMAP;

#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13

#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(rgba_get_b(clr), rgba_get_g(clr), rgba_get_r(clr)))

class image_list;

class CLASS_DECL_ca2 imaging :
   virtual public ::ca2::object
{
public:
   class CSysColorMap
   {
      public:
         // use uint32_t instead of RGBQUAD so we can compare two RGBQUADs easily
         uint32_t rgbqFrom;
         uint32_t iSysColorTo;
   };

protected:
   map < int32_t, int32_t, LPBYTE, LPBYTE > m_alpha_spread__24CC_filterMap;
   map < int32_t, int32_t, LPBYTE, LPBYTE > m_alpha_spread__32CC_filterMap;


public:
   imaging(sp(::ca2::application) papp);
    ~imaging();


   static const CSysColorMap s_psyscolormap[];


   virtual void pixelate_24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t xSrc, int32_t ySrc, int32_t wSrc, int32_t iSize);
   virtual bool pixelate(::ca2::graphics *pdcDest, int32_t xDest, int32_t yDest, int32_t cx, int32_t cy, ::ca2::graphics * pdcSrc, int32_t xSrc, int32_t ySrc, int32_t iSize);

   virtual void alpha_pixelate_24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc1, int32_t xSrc1, int32_t ySrc1, int32_t wSrc1, LPBYTE lpbSrc2, int32_t xSrc2, int32_t ySrc2, int32_t wSrc2, int32_t iSize, int32_t iAlpha);
   virtual bool alpha_pixelate(::ca2::graphics *pdcDest, int32_t xDest, int32_t yDest, int32_t cx, int32_t cy, ::ca2::graphics * pdcSrc1, int32_t xSrc1, int32_t ySrc1, ::ca2::graphics * pdcSrc2, int32_t xSrc2, int32_t ySrc2, int32_t iSize, int32_t iAlpha);


   virtual void blur_32CC(::ca2::dib * pdibDst, ::ca2::dib * pdibSrc, int32_t iRadius);
   virtual void blur_32CC_r2(::ca2::dib * pdibDst, ::ca2::dib * pdibSrc);

   virtual bool channel_gray_blur_32CC(::ca2::dib * pdibDst, ::ca2::dib * pdibSrc, int32_t iChannel, int32_t iRadius);
   virtual bool channel_gray_blur(::ca2::graphics * pdcDest, point ptDst, size size, ::ca2::graphics * pdcSrc, point ptSrc, int32_t iChannel, int32_t iRadius);
   virtual bool channel_gray_blur_32CC(::ca2::dib * pdibDst, ::ca2::dib * pdibSrc, int32_t iChannel, int32_t iFilterWidth, int32_t iFilterHeight,  LPBYTE lpbFilter);
   virtual bool channel_gray_blur(::ca2::graphics * pdcDest, point ptDst, size size, ::ca2::graphics * pdcSrc, point ptSrc, int32_t iChannel, class size sizeFilter,  LPBYTE lpbFilter);
   virtual bool channel_alpha_gray_blur_32CC(::ca2::dib * pdibDst, ::ca2::dib * pdibSrc, int32_t iChannel, int32_t iRadius);
   virtual bool channel_alpha_gray_blur(::ca2::graphics * pdcDest, point ptDst, size size, ::ca2::graphics * pdcSrc, point ptSrc, int32_t iChannel, int32_t iRadius);

   void alpha_spread_R2_24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t ySrc, int32_t xSrc, int32_t wSrc, BYTE bMin);
   void alpha_spread__24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t ySrc, int32_t xSrc, int32_t wSrc, BYTE bMin, int32_t iRadius);

   bool channel_spread__32CC(::ca2::dib * pdibDst, ::ca2::dib * pdibSrc, int32_t iChannel, int32_t iRadius, COLORREF cr);

   bool alpha_spread_R2(
      ::ca2::graphics * pdcDest,
      point ptDst,
      size size,
      ::ca2::graphics * pdcSrc,
      point ptSrc,
      BYTE bMin);

   bool alpha_spread(
      ::ca2::graphics * pdcDest,
      point ptDst,
      size size,
      ::ca2::graphics * pdcSrc,
      point ptSrc,
      BYTE bMin,
      int32_t iRadius);

   bool channel_spread(
      ::ca2::graphics * pdcDest,
      point ptDst,
      size size,
      ::ca2::graphics * pdcSrc,
      point ptSrc,
      int32_t iChannel,
      int32_t iRadius);

   bool channel_spread_set_color(
      ::ca2::graphics * pdcDest,
      point ptDst,
      size size,
      ::ca2::graphics * pdcSrc,
      point ptSrc,
      int32_t iChannel,
      int32_t iRadius,
      COLORREF cr);


   bool true_blend(::ca2::graphics * pdc, LPCRECT lpcrect, ::ca2::graphics * pdcColorAlpha, point ptAlpha, ::ca2::dib * pdibWork = NULL, ::ca2::dib * pdibWork2 = NULL, ::ca2::dib * pdibWork3 = NULL);

   bool true_blend(::ca2::graphics * pdc, point pt, size size, ::ca2::graphics * pdcColorAlpha, point ptAlpha, ::ca2::dib * pdibWork = NULL, ::ca2::dib * pdibWork2 = NULL, ::ca2::dib * pdibWork3 = NULL);

   bool blur(::ca2::graphics * pdcDst, point ptDst, size size, ::ca2::graphics * pdcSrc, point ptSrc, int32_t iRadius);

   void color_blend_24CC(
      LPBYTE lpbA,
      int32_t x1,
      int32_t y1,
      int32_t w1,
      int32_t cx,
      int32_t cy,
      COLORREF cr,
      LPBYTE lpbC,
      int32_t x3,
      int32_t y3,
      int32_t w3);


   bool color_blend(::ca2::graphics * pdc, point pt, size size, ::ca2::graphics * pdcColorAlpha, point ptAlpha, ::ca2::dib * pdibWork = NULL, ::ca2::dib * pdibWork2 = NULL);
   bool color_blend(::ca2::graphics * pdc, LPCRECT lpcrect, ::ca2::graphics * pdcColorAlpha, point ptAlpha, ::ca2::dib * pdibWork = NULL);

   bool color_blend(::ca2::graphics * pdc, LPCRECT lpcrect, ::ca2::graphics * pdcColorAlpha, point ptAlpha, double dBlend);
   bool color_blend(::ca2::graphics * pdc, point pt, size size, ::ca2::graphics * pdcColorAlpha, point ptAlpha, double dBlend);

   bool color_blend(::ca2::graphics * pdc, int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF cr, BYTE bAlpha);
   bool color_blend(::ca2::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha);
   bool color_blend(::ca2::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha);
   bool color_blend(::ca2::graphics * pdc,   const __rect64 * lpcrect, COLORREF cr,   BYTE alpha);

   bool color_blend(::ca2::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha, ::ca2::dib * pdibWork);
   bool color_blend(::ca2::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha, ::ca2::dib * pdibWork);

   bool prepare_blend(::ca2::dib * pdib, point pt, size size, COLORREF cr, BYTE alpha, ::ca2::dib * pdibWork);
   bool prepare_blend(::ca2::dib * pdib, LPCRECT lpcrect, COLORREF cr, BYTE alpha, ::ca2::dib * pdibWork);


   bool clip_color_blend(::ca2::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha);
   bool clip_color_blend(::ca2::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha);

/*
   bool clip_color_blend(::ca2::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha, ::ca2::region * prgnClip);
   bool clip_color_blend(::ca2::graphics * pdc, LPCRECT lpcrect, COLORREF cr, BYTE alpha, ::ca2::region * prgnClip);
*/


   static bool CreateBitmap(
      ::ca2::graphics * pdc,
      ::ca2::bitmap * pbitmapOld,
      ::ca2::bitmap * pbitmap,
      BITMAP * pbmp,
      int32_t cx,
      int32_t cy);

   static bool CreateBitmap(
      ::ca2::graphics * pdc,
      ::ca2::graphics * pdcScreen,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapOld,
      BITMAP * pbmp,
      int32_t cx,
      int32_t cy);

   void AlphaTextOut(::ca2::graphics * pdc, int32_t left, int32_t top, const char * lpcsz, int32_t len, COLORREF cr, double dBlend);

/*

   bool ClipSave(
      ::ca2::graphics * pdc,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect);

   bool ClipRestore(
      ::ca2::graphics * pdc,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect);

   bool ClipSave(
      ::ca2::graphics * pdc,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect,
      ::ca2::region * prgnClip);

   bool ClipRestore(
      ::ca2::graphics * pdc,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapOld,
      BITMAP * pbmp,
      LPCRECT lpcrect,
      ::ca2::region * prgnClip);

*/

   bool GetDeviceContext24BitsCC(
      ::ca2::graphics *pdc,
      BITMAP & bm,
      BITMAPINFO & bmi,
      primitive::memory & memomrystorage,
      ::ca2::bitmap * pbitmap,
      LPCRECT lpcrect,
      int32_t & iWidth,
      UINT & uiStartScanLine,
      UINT & uiScanLineCount,
      int32_t & iLimitYParam);






   bool GrayVRCP(
      ::ca2::graphics * pgraphics,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapMask,
      int32_t x,
      int32_t y,
      int32_t cx,
      int32_t cy,
      COLORREF crTransparent);

   bool HueVRCP(::ca2::dib * pdib, COLORREF crHue, double dCompress);

   bool GrayVRCP(
      ::ca2::graphics * pgraphics,
      ::ca2::bitmap * pbitmap,
      ::ca2::bitmap * pbitmapMask,
      LPCRECT lpcrect,
      COLORREF crTransparent);

   bool GrayVRCP(
      ::ca2::graphics * pgraphics,
      int32_t x,
      int32_t y,
      int32_t cx,
      int32_t cy,
      COLORREF crAlpha);

   bool CreateHueImageList(
      ::ca2::graphics * pdc,
      sp(image_list) pilGray,
      sp(image_list) pilParam,
      COLORREF crHue,
      double dCompress);


   bool Createcolor_blend_ImageList(
      sp(image_list) pilGray,
      sp(image_list) pilParam,
      COLORREF cr,
      BYTE bAlpha);



   bool BitmapBlend2(::ca2::graphics * pdcDst, point pt, size size, ::ca2::graphics * pdcSrc, point ptSrc,
      ::ca2::graphics * pdcAlpha, // alpha information device (in alpha channel)
      point ptAlpha);

   /*bool bitmap_blend(::ca2::graphics * pdcDst, point pt, size size, ::ca2::graphics * pdcSrc, point ptSrc,
      ::ca2::graphics * pdcAlpha, // alpha information device (in red channel)
      point ptAlpha,
      BYTE alphaConstant = 255,
      ::ca2::dib * pdibWorkA = NULL,
      ::ca2::dib * pdibWorkB = NULL);*/


/*   bool bitmap_blend(::ca2::graphics * pdcDst, point pt, size size, ::ca2::dib * pdibSrc, point ptSrc,
      ::ca2::dib * pdibAlpha, // alpha information device (in red channel)
      point ptAlpha,
      BYTE alphaConstant = 255);*/

   /*bool bitmap_blend(::ca2::graphics * pdcDst, point pt, size size, ::ca2::graphics * pdcSrc, point ptSrc,
      ::ca2::graphics * pdcAlpha, // alpha information device (in alpha channel)
      point ptAlpha,
      ::ca2::graphics * pdcAlphaComplement, // alpha information device (in alpha channel)
      point ptAlphaComplement);*/

   bool bitmap_blend(::ca2::graphics * pdcDst, point pt, size size,
      ::ca2::graphics * pdcSrcWithAlpha, // source device
      point ptSrc);

   bool BitmapDivBlend(::ca2::graphics * pdcDst, point pt, size size, ::ca2::graphics * pdcSrc, point ptSrc, BYTE bAlpha);

   bool bitmap_blend(::ca2::graphics * pdcDst, point pt, size size, ::ca2::graphics * pdcSrc, point ptSrc, BYTE bAlpha);

   void BitmapBlend24CC(
      LPBYTE lpbA,
      int32_t x1,
      int32_t y1,
      int32_t w1,
      int32_t cx,
      int32_t cy,
      LPBYTE lpbB,
      int32_t x2,
      int32_t y2,
      int32_t w2,
      LPBYTE lpbC,
      int32_t x3,
      int32_t y3,
      int32_t w3);
   void BitmapBlend24CC(
      LPBYTE lpbDest,
      int32_t xDest,
      int32_t yDest,
      int32_t wDest,
      int32_t cx,
      int32_t cy,
      LPBYTE lpbSrc,
      int32_t xSrc,
      int32_t ySrc,
      int32_t wSrc,
      BYTE bAlpha);

   virtual bool color_blend_3dRect(::ca2::graphics * pdc, LPCRECT lpcrect, COLORREF crTopLeft, BYTE bAlphaTopLeft, COLORREF crBottomRight, BYTE bAlphaBottomRight);

   virtual bool ColorInvert(::ca2::graphics * pdc, int32_t x, int32_t y, int32_t cx, int32_t cy);

   virtual ::ca2::bitmap_sp CreateDIBitmap(::ca2::graphics * pdc, FIBITMAP * pFreeImage);
   virtual ::ca2::bitmap_sp CreateBitmap(::ca2::graphics * pdc,FIBITMAP * pFreeImage);

/*   virtual ::ca2::bitmap * LoadSysColorBitmap(
      ::ca2::graphics * pdcCompatible,
      HINSTANCE hInst,
      HRSRC hRsrc,
      bool bMono = false);*/

   virtual bool LoadImageFile(::ca2::dib * pdib, var varFile, sp(::ca2::application) papp);
   virtual bool LoadImageSync(::ca2::dib * pdib, const char * lpcszImageFilePath, sp(::ca2::application) papp);

   virtual FIBITMAP * LoadImageFile(var varFile, sp(::ca2::application) papp);
   virtual FIBITMAP * LoadImageFile(sp(::ca2::file) pfile);
   virtual ::ca2::bitmap_sp FItoHBITMAP(FIBITMAP * pfibitmap, bool bDestroyFI);
   virtual FIBITMAP * HBITMAPtoFI(::ca2::bitmap_sp hbitmap);
   virtual ::ca2::bitmap_sp LoadImageSync(const char * lpcszImageFilePath, sp(::ca2::application) papp);
   virtual void SaveJpeg(const char * lpcszFile, ::ca2::bitmap_sp pbitmap);
   virtual void SavePng(const char * lpcszFile, ::ca2::bitmap_sp pbitmap);
   virtual void SavePng(const char * lpcszFile, FIBITMAP * pfi, bool bUnload);

   virtual void free(FIBITMAP * pfibitmap);
};

void EmbossedTextOut(
   ::ca2::graphics *        pdc,
   int32_t                 x,
   int32_t                 y,
   const char *            lpcsz,
   size_t                  cb,
   COLORREF                crText,
   COLORREF                crShadow,
   int32_t                 cx,
   int32_t                 cy);

void GetMultiLineTextExtent(HDC hDC, stringa *pArray, LPSIZE lpSize);
void DrawMultiLineText(HDC hDC, stringa *pArray);


