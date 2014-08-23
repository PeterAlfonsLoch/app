#pragma once


struct FIBITMAP;

#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13

#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(rgba_get_b(clr), rgba_get_g(clr), rgba_get_r(clr)))

class image_list;

class CLASS_DECL_BASE imaging :
   virtual public ::object
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
   imaging(sp(::aura::application) papp);
    ~imaging();


   static const CSysColorMap s_psyscolormap[];


   virtual void pixelate_24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t xSrc, int32_t ySrc, int32_t wSrc, int32_t iSize);
   virtual bool pixelate(::draw2d::graphics *pdcDest, int32_t xDest, int32_t yDest, int32_t cx, int32_t cy, ::draw2d::graphics * pdcSrc, int32_t xSrc, int32_t ySrc, int32_t iSize);

   virtual void alpha_pixelate_24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc1, int32_t xSrc1, int32_t ySrc1, int32_t wSrc1, LPBYTE lpbSrc2, int32_t xSrc2, int32_t ySrc2, int32_t wSrc2, int32_t iSize, int32_t iAlpha);
   virtual bool alpha_pixelate(::draw2d::graphics *pdcDest, int32_t xDest, int32_t yDest, int32_t cx, int32_t cy, ::draw2d::graphics * pdcSrc1, int32_t xSrc1, int32_t ySrc1, ::draw2d::graphics * pdcSrc2, int32_t xSrc2, int32_t ySrc2, int32_t iSize, int32_t iAlpha);


   virtual void blur_32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iRadius);
   virtual void blur_32CC_r2(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc);

   virtual bool channel_gray_blur_32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iChannel, int32_t iRadius);
   virtual bool channel_gray_blur(::draw2d::graphics * pdcDest, point ptDst, size size, ::draw2d::graphics * pdcSrc, point ptSrc, int32_t iChannel, int32_t iRadius);
   virtual bool channel_gray_blur_32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iChannel, int32_t iFilterWidth, int32_t iFilterHeight,  LPBYTE lpbFilter);
   virtual bool channel_gray_blur(::draw2d::graphics * pdcDest, point ptDst, size size, ::draw2d::graphics * pdcSrc, point ptSrc, int32_t iChannel, class size sizeFilter,  LPBYTE lpbFilter);
   virtual bool channel_alpha_gray_blur_32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iChannel, int32_t iRadius);
   virtual bool channel_alpha_gray_blur(::draw2d::graphics * pdcDest, point ptDst, size size, ::draw2d::graphics * pdcSrc, point ptSrc, int32_t iChannel, int32_t iRadius);

   void alpha_spread_R2_24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t ySrc, int32_t xSrc, int32_t wSrc, BYTE bMin);
   void alpha_spread__24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t ySrc, int32_t xSrc, int32_t wSrc, BYTE bMin, int32_t iRadius);

   bool channel_spread__32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iChannel, int32_t iRadius, COLORREF cr);

   bool alpha_spread_R2(
      ::draw2d::graphics * pdcDest,
      point ptDst,
      size size,
      ::draw2d::graphics * pdcSrc,
      point ptSrc,
      BYTE bMin);

   bool alpha_spread(
      ::draw2d::graphics * pdcDest,
      point ptDst,
      size size,
      ::draw2d::graphics * pdcSrc,
      point ptSrc,
      BYTE bMin,
      int32_t iRadius);

   bool channel_spread(
      ::draw2d::graphics * pdcDest,
      point ptDst,
      size size,
      ::draw2d::graphics * pdcSrc,
      point ptSrc,
      int32_t iChannel,
      int32_t iRadius);

   bool channel_spread_set_color(
      ::draw2d::graphics * pdcDest,
      point ptDst,
      size size,
      ::draw2d::graphics * pdcSrc,
      point ptSrc,
      int32_t iChannel,
      int32_t iRadius,
      COLORREF cr);


   bool true_blend(::draw2d::graphics * pdc, const RECT & rect, ::draw2d::graphics * pdcColorAlpha, point ptAlpha, ::draw2d::dib * pdibWork = NULL, ::draw2d::dib * pdibWork2 = NULL, ::draw2d::dib * pdibWork3 = NULL);

   bool blur(::draw2d::graphics * pdcDst, point ptDst, size size, ::draw2d::graphics * pdcSrc, point ptSrc, int32_t iRadius);

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


   bool color_blend(::draw2d::graphics * pdc, const RECT & rect, ::draw2d::graphics * pdcColorAlpha, point ptAlpha, ::draw2d::dib * pdibWork = NULL);

   bool color_blend(::draw2d::graphics * pdc, const RECT & rect, ::draw2d::graphics * pdcColorAlpha, point ptAlpha, double dBlend);
   bool color_blend(::draw2d::graphics * pdc, point pt, size size, ::draw2d::graphics * pdcColorAlpha, point ptAlpha, double dBlend);

   bool color_blend(::draw2d::graphics * pdc, int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF cr, BYTE bAlpha);
   bool color_blend(::draw2d::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha);
   bool color_blend(::draw2d::graphics * pdc, const RECT & rect, COLORREF cr, BYTE alpha);
   bool color_blend(::draw2d::graphics * pdc,   const __rect64 * lpcrect, COLORREF cr,   BYTE alpha);

   bool clip_color_blend(::draw2d::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha);
   bool clip_color_blend(::draw2d::graphics * pdc, const RECT & rect, COLORREF cr, BYTE alpha);

/*
   bool clip_color_blend(::draw2d::graphics * pdc, point pt, size size, COLORREF cr, BYTE alpha, ::draw2d::region * prgnClip);
   bool clip_color_blend(::draw2d::graphics * pdc, const RECT & rect, COLORREF cr, BYTE alpha, ::draw2d::region * prgnClip);
*/


   static bool CreateBitmap(
      ::draw2d::graphics * pdc,
      ::draw2d::bitmap * pbitmapOld,
      ::draw2d::bitmap * pbitmap,
      BITMAP * pbmp,
      int32_t cx,
      int32_t cy);

   static bool CreateBitmap(
      ::draw2d::graphics * pdc,
      ::draw2d::graphics * pdcScreen,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapOld,
      BITMAP * pbmp,
      int32_t cx,
      int32_t cy);

   void AlphaTextOut(::draw2d::graphics * pdc, int32_t left, int32_t top, const char * lpcsz, int32_t len, COLORREF cr, double dBlend);

/*

   bool ClipSave(
      ::draw2d::graphics * pdc,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapOld,
      BITMAP * pbmp,
      const RECT & rect);

   bool ClipRestore(
      ::draw2d::graphics * pdc,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapOld,
      BITMAP * pbmp,
      const RECT & rect);

   bool ClipSave(
      ::draw2d::graphics * pdc,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapOld,
      BITMAP * pbmp,
      const RECT & rect,
      ::draw2d::region * prgnClip);

   bool ClipRestore(
      ::draw2d::graphics * pdc,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapOld,
      BITMAP * pbmp,
      const RECT & rect,
      ::draw2d::region * prgnClip);

*/

   bool GetDeviceContext24BitsCC(
      ::draw2d::graphics *pdc,
      BITMAP & bm,
      BITMAPINFO & bmi,
      primitive::memory & memomrystorage,
      ::draw2d::bitmap * pbitmap,
      const RECT & rect,
      int32_t & iWidth,
      UINT & uiStartScanLine,
      UINT & uiScanLineCount,
      int32_t & iLimitYParam);






   bool GrayVRCP(
      ::draw2d::graphics * pgraphics,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapMask,
      int32_t x,
      int32_t y,
      int32_t cx,
      int32_t cy,
      COLORREF crTransparent);

   bool HueVRCP(::draw2d::dib * pdib, COLORREF crHue, double dCompress);

   bool GrayVRCP(
      ::draw2d::graphics * pgraphics,
      ::draw2d::bitmap * pbitmap,
      ::draw2d::bitmap * pbitmapMask,
      const RECT & rect,
      COLORREF crTransparent);

   bool GrayVRCP(
      ::draw2d::graphics * pgraphics,
      int32_t x,
      int32_t y,
      int32_t cx,
      int32_t cy,
      COLORREF crAlpha);

   bool CreateHueImageList(
      ::draw2d::graphics * pdc,
      sp(image_list) pilGray,
      sp(image_list) pilParam,
      COLORREF crHue,
      double dCompress);


   bool Createcolor_blend_ImageList(
      sp(image_list) pilGray,
      sp(image_list) pilParam,
      COLORREF cr,
      BYTE bAlpha);



   bool BitmapBlend2(::draw2d::graphics * pdcDst, point pt, size size, ::draw2d::graphics * pdcSrc, point ptSrc,
      ::draw2d::graphics * pdcAlpha, // alpha information device (in alpha channel)
      point ptAlpha);

   bool BitmapDivBlend(::draw2d::graphics * pdcDst, point pt, size size, ::draw2d::graphics * pdcSrc, point ptSrc, BYTE bAlpha);

   bool bitmap_blend(::draw2d::graphics * pdcDst, point pt, size size, ::draw2d::graphics * pdcSrc, point ptSrc, BYTE bAlpha);

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

   virtual bool color_blend_3dRect(::draw2d::graphics * pdc, const RECT & rect, COLORREF crTopLeft, BYTE bAlphaTopLeft, COLORREF crBottomRight, BYTE bAlphaBottomRight);

   virtual bool ColorInvert(::draw2d::graphics * pdc, int32_t x, int32_t y, int32_t cx, int32_t cy);

   virtual ::draw2d::bitmap_sp CreateDIBitmap(::draw2d::graphics * pdc, FIBITMAP * pFreeImage);
   virtual ::draw2d::bitmap_sp CreateBitmap(::draw2d::graphics * pdc,FIBITMAP * pFreeImage);

/*   virtual ::draw2d::bitmap * LoadSysColorBitmap(
      ::draw2d::graphics * pdcCompatible,
      HINSTANCE hInst,
      HRSRC hRsrc,
      bool bMono = false);*/

   virtual bool LoadImageFile(::draw2d::dib * pdib, var varFile, sp(::aura::application) papp);
   virtual bool LoadImageSync(::draw2d::dib * pdib, const char * lpcszImageFilePath, sp(::aura::application) papp);

   virtual FIBITMAP * LoadImageFile(var varFile, sp(::aura::application) papp);
   virtual FIBITMAP * LoadImageFile(::file::buffer_sp  pfile);
   virtual ::draw2d::bitmap_sp FItoHBITMAP(FIBITMAP * pfibitmap, bool bDestroyFI);
   virtual FIBITMAP * HBITMAPtoFI(::draw2d::bitmap_sp hbitmap);
   virtual ::draw2d::bitmap_sp LoadImageSync(const char * lpcszImageFilePath, sp(::aura::application) papp);
   virtual void SaveJpeg(const char * lpcszFile, ::draw2d::bitmap_sp pbitmap);
   virtual void SavePng(const char * lpcszFile, ::draw2d::bitmap_sp pbitmap);
   virtual void SavePng(const char * lpcszFile, FIBITMAP * pfi, bool bUnload);

   virtual void free(FIBITMAP * pfibitmap);


   bool load_from_file(::draw2d::dib * pdib, var varFile, bool bCache = true, sp(::aura::application) papp = NULL);
   bool load_from_matter(::draw2d::dib * pdib, var varFile, sp(::aura::application) papp = NULL);
   bool read_from_file(::draw2d::dib * pdib, ::file::buffer_sp buffer, sp(::aura::application) papp = NULL);

   bool load_from_file(::visual::cursor * pcursor, var varFile, sp(::aura::application) papp = NULL);
   bool load_from_matter(::visual::cursor * pcursor, var varFile, sp(::aura::application) papp = NULL);

   ::visual::cursor_sp load_cursor_from_file(var varFile, sp(::aura::application) papp = NULL);
   ::visual::cursor_sp load_cursor_from_matter(var varFile, sp(::aura::application) papp = NULL);

   virtual bool from(::draw2d::dib * pdib, ::draw2d::graphics * pgraphics, FIBITMAP *pfibitmap, bool bUnloadFI, sp(::aura::application) papp = NULL);

};

void EmbossedTextOut(
   ::draw2d::graphics *        pdc,
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


