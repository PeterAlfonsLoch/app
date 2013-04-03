#pragma once


#include "ca/user/user_draw_context.h"
#include "ca_bitmap.h"
#include "ca_pen.h"
#include "ca_brush.h"
#include "ca_font.h"
#include "ca_region.h"
#include "ca_palette.h"
#include "ca_graphics_path.h"


/*#ifdef UNICODE
#define ___FUNCNAME(_Name) _Name##W
#else
#define ___FUNCNAME(_Name) _Name##A
#endif*/


namespace user
{


   class str_context;


}


namespace ca
{

   class dib;
   class job;

   enum e_text_rendering
   {
      text_rendering_anti_alias,
      text_rendering_anti_alias_grid_fit,
      text_rendering_single_bit_per_pixel,
      text_rendering_clear_type_grid_fit,
   };

   class CLASS_DECL_ca graphics :
      virtual public ::ca::simple_chain < ::user::draw_context >
   {
   public:



      ::user::str_context *      m_puistrcontext;

      ::user::draw_context *     m_pdrawcontext;

      ::ca::dib *                m_pdibAlphaBlend;
      point                      m_ptAlphaBlend;
      ::ca::job *                m_pjob;

      ::ca::bitmap_sp            m_bitmap;

      ::ca::pen_sp               m_sppen;
      ::ca::brush_sp             m_spbrush;
      ::ca::font_sp              m_spfont;
      ::ca::region_sp            m_spregion;

      ::ca::pen                  m_penxyz;
      ::ca::brush                m_brushxyz;
      ::ca::font                 m_fontxyz;
      ::ca::region               m_regionxyz;

      COLORREF                   m_crColor;
      double                     m_x;
      double                     m_y;

      e_alpha_mode               m_ealphamode;
      e_text_rendering           m_etextrendering;
      double                     m_dFontFactor;


      graphics();

      virtual bool is_set();

      virtual void * get_os_data() const;
      virtual bool attach(void * pdata);
      virtual bool attach(simple_graphics & g);
      virtual void * detach();


//      virtual bool attach(HDC hdc);
//      virtual HDC detach();


      virtual ::user::str_context * str_context();
      virtual ::user::draw_context * draw_context();


      virtual void set_alpha_mode(e_alpha_mode ealphamode);

      virtual void set_text_rendering(e_text_rendering etextrendering);

      virtual bool blur(bool bExpand, double dRadius, LPCRECT lprect);

      void set_solid_pen(double dWidth);

      virtual bool IsPrinting() const;            // TRUE if being used for printing

      virtual ::ca::pen & GetCurrentPen() const;
      virtual ::ca::brush & GetCurrentBrush() const;
      virtual ::ca::palette & GetCurrentPalette() const;
      virtual ::ca::font & GetCurrentFont() const;
      virtual ::ca::bitmap & GetCurrentBitmap() const;

      // for bidi and mirrored localization
      virtual uint32_t GetLayout() const;
      virtual uint32_t SetLayout(uint32_t dwLayout);

   // Constructors
      virtual bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName,
         const char * lpszOutput, const void * lpInitData);
      virtual bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName,
         const char * lpszOutput, const void * lpInitData);
      virtual bool CreateCompatibleDC(::ca::graphics * pgraphics);

      virtual bool DeleteDC();


   // Device-Context Functions
      virtual int32_t SaveDC();
      virtual bool RestoreDC(int32_t nSavedDC);
      virtual int32_t GetDeviceCaps(int32_t nIndex) const;
      virtual UINT SetBoundsRect(LPCRECT lpRectBounds, UINT flags);
      virtual UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags);
#ifdef WINDOWS
      virtual bool ResetDC(const DEVMODE* lpDevMode);
#endif

   // Drawing-Tool Functions
      virtual point GetBrushOrg() const;
      virtual point SetBrushOrg(int32_t x, int32_t y);
      virtual point SetBrushOrg(POINT point);
      virtual int32_t EnumObjects(int32_t nObjectType,
            int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

   // Type-safe selection helpers
   public:
      virtual ::ca::graphics_object* SelectStockObject(int32_t nIndex);
      virtual ::ca::pen* SelectObject(::ca::pen* pPen);
      virtual ::ca::brush* SelectObject(::ca::brush* pBrush);
      virtual ::ca::font* SelectObject(::ca::font* pFont);
      virtual ::ca::bitmap* SelectObject(::ca::bitmap* pBitmap);
      virtual int32_t SelectObject(::ca::region* pRgn);       // special return for regions
      virtual ::ca::graphics_object* SelectObject(::ca::graphics_object* pObject);
         // ::ca::graphics_object* provided so compiler doesn't use SelectObject(HGDIOBJ)

   // color and color Palette Functions
      virtual COLORREF GetNearestColor(COLORREF crColor) const;
      virtual ::ca::palette* SelectPalette(::ca::palette* pPalette, bool bForceBackground);
      virtual UINT RealizePalette();
      virtual void UpdateColors();

   // Drawing-Attribute Functions
      virtual COLORREF GetBkColor() const;
      virtual int32_t GetBkMode() const;
      virtual int32_t GetPolyFillMode() const;
      virtual int32_t GetROP2() const;
      virtual int32_t GetStretchBltMode() const;
      virtual COLORREF GetTextColor() const;


      virtual double get_dpix() const;

      virtual COLORREF SetBkColor(COLORREF crColor);
      virtual int32_t SetBkMode(int32_t nBkMode);
      virtual int32_t SetPolyFillMode(int32_t nPolyFillMode);
      virtual int32_t SetROP2(int32_t nDrawMode);
      virtual int32_t SetStretchBltMode(int32_t nStretchMode);
      virtual COLORREF SetTextColor(COLORREF crColor);

      virtual COLORREF SetColor(COLORREF crColor);
      virtual COLORREF setColor(COLORREF crColor);
      virtual COLORREF set_color(COLORREF crColor);

      virtual bool flush();



#ifdef WINDOWSEX
      virtual bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      virtual bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);
#endif

   #if (_WIN32_WINNT >= 0x0500)

      virtual COLORREF GetDCBrushColor() const;
      virtual COLORREF SetDCBrushColor(COLORREF crColor);

      virtual COLORREF GetDCPenColor() const;
      virtual COLORREF SetDCPenColor(COLORREF crColor);

   #endif

      // Graphics mode
      virtual int32_t SetGraphicsMode(int32_t iMode);
      virtual int32_t GetGraphicsMode() const;

      // World transform
#ifdef WINDOWS
      virtual bool SetWorldTransform(const XFORM* pXform);
      virtual bool ModifyWorldTransform(const XFORM* pXform,uint32_t iMode);
      virtual bool GetWorldTransform(XFORM* pXform) const;
#endif

      // Mapping Functions
      virtual int32_t GetMapMode() const;
      virtual point GetViewportOrg() const;
      virtual int32_t SetMapMode(int32_t nMapMode);
      // Viewport Origin
      virtual point SetViewportOrg(int32_t x, int32_t y);
      virtual point SetViewportOrg(POINT point);
      virtual point OffsetViewportOrg(int32_t nWidth, int32_t nHeight);

      // Viewport Extent
      virtual size GetViewportExt() const;
      virtual size SetViewportExt(int32_t cx, int32_t cy);
      virtual size SetViewportExt(SIZE size);
      virtual size ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom);

      // Window Origin
      virtual point GetWindowOrg() const;
      virtual point SetWindowOrg(int32_t x, int32_t y);
      virtual point SetWindowOrg(POINT point);
      virtual point OffsetWindowOrg(int32_t nWidth, int32_t nHeight);

      // Window extent
      virtual size GetWindowExt() const;
      virtual size SetWindowExt(int32_t cx, int32_t cy);
      virtual size SetWindowExt(SIZE size);
      virtual size ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom);

   // Coordinate Functions
      virtual void DPtoLP(LPPOINT lpPoints, int32_t nCount = 1) const;
      virtual void DPtoLP(LPRECT lpRect) const;
      virtual void DPtoLP(LPSIZE lpSize) const;
      virtual void LPtoDP(LPPOINT lpPoints, int32_t nCount = 1) const;
      virtual void LPtoDP(LPRECT lpRect) const;
      virtual void LPtoDP(LPSIZE lpSize) const;

   // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(LPSIZE lpSize) const;
      virtual void LPtoHIMETRIC(LPSIZE lpSize) const;
      virtual void HIMETRICtoDP(LPSIZE lpSize) const;
      virtual void HIMETRICtoLP(LPSIZE lpSize) const;

   // Region Functions
      virtual bool FillRgn(::ca::region* pRgn, ::ca::brush* pBrush);
      virtual bool FrameRgn(::ca::region* pRgn, ::ca::brush* pBrush, int32_t nWidth, int32_t nHeight);
      virtual bool InvertRgn(::ca::region* pRgn);
      virtual bool PaintRgn(::ca::region* pRgn);

   // Clipping Functions
      virtual int32_t GetClipBox(LPRECT lpRect) const;
      virtual int32_t GetClipBox(rect64 * lpRect) const;
      virtual bool PtVisible(int32_t x, int32_t y) const;
      virtual bool PtVisible(POINT point) const;
      virtual bool RectVisible(LPCRECT lpRect) const;
      virtual int32_t SelectClipRgn(::ca::region* pRgn);
      virtual int32_t ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual int32_t ExcludeClipRect(LPCRECT lpRect);
      virtual int32_t ExcludeUpdateRgn(::ca::window* pWnd);
      virtual int32_t IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual int32_t IntersectClipRect(LPCRECT lpRect);
      virtual int32_t OffsetClipRgn(int32_t x, int32_t y);
      virtual int32_t OffsetClipRgn(SIZE size);
      virtual int32_t SelectClipRgn(::ca::region* pRgn, int32_t nMode);

   // Line-Output Functions

      virtual point DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual point drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual point draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

      virtual point DrawLine(float x1, float y1, float x2, float y2);
      virtual point drawLine(float x1, float y1, float x2, float y2);
      virtual point draw_line(float x1, float y1, float x2, float y2);

      virtual bool DrawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool drawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool draw_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);


      virtual point GetCurrentPosition() const;
      virtual point MoveTo(int32_t x, int32_t y);
      virtual pointd MoveTo(double x, double y);
      virtual point MoveTo(POINT point);
      virtual bool LineTo(int32_t x, int32_t y);
      virtual bool LineTo(double x, double y);
      virtual bool LineTo(POINT point);
      virtual bool Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4);
      virtual bool Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual bool Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, double start, double extends);
      virtual bool Arc(LPCRECT lpRect, double start, double extends);
      virtual bool Polyline(const POINT* lpPoints, int32_t nCount);

      virtual bool AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle);
      virtual bool ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4);
      virtual bool ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual int32_t GetArcDirection() const;
      virtual int32_t SetArcDirection(int32_t nArcDirection);

      virtual bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount);
      virtual bool PolylineTo(const POINT* lpPoints, int32_t nCount);
      virtual bool PolyPolyline(const POINT* lpPoints, const uint32_t* lpPolyPoints, int32_t nCount);

      virtual bool PolyBezier(const POINT* lpPoints, int32_t nCount);
      virtual bool PolyBezierTo(const POINT* lpPoints, int32_t nCount);

   // Simple Drawing Functions
      virtual void FillRect(LPCRECT lpRect, ::ca::brush* pBrush);
      virtual void FrameRect(LPCRECT lpRect, ::ca::brush* pBrush);
      virtual void InvertRect(LPCRECT lpRect);
      virtual bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon);
      virtual bool DrawIcon(POINT point, ::visual::icon * picon);
      virtual bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
      virtual bool DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
         HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, ::ca::bitmap* pBitmap, UINT nFlags,
         ::ca::brush* pBrush = NULL);
#ifdef WINDOWS
      virtual bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         ::ca::brush* pBrush = NULL);
#endif
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         bool bPrefixText = TRUE, int32_t nTextLen = 0, HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         bool bPrefixText = TRUE, int32_t nTextLen = 0, ::ca::brush* pBrush = NULL);
#ifdef WINDOWSEX
      virtual bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, ::ca::brush* pBrush = NULL);
#endif
   // Ellipse and Polygon Functions
      virtual bool Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3,
         int32_t x4, int32_t y4);
      virtual bool Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual void DrawFocusRect(LPCRECT lpRect);
      virtual bool Ellipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool Ellipse(LPCRECT lpRect);
      virtual bool DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool DrawEllipse(LPCRECT lpRect);
      virtual bool FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool FillEllipse(LPCRECT lpRect);
      virtual bool Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4);
      virtual bool Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual bool fill_polygon(const POINTD * lpPoints, int32_t nCount);
      virtual bool fill_polygon(const POINT* lpPoints, int32_t nCount);
      virtual bool Polygon(point_array & pta);
      virtual bool Polygon(const POINT* lpPoints, int32_t nCount);
      virtual bool PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int32_t nCount);
      virtual bool Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool Rectangle(LPCRECT lpRect);
      virtual bool DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool DrawRectangle(LPCRECT lpRect);
      virtual bool FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool FillRectangle(LPCRECT lpRect);
      virtual bool RoundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3);
      virtual bool RoundRect(LPCRECT lpRect, POINT point);

   // Bitmap Functions
      virtual bool from(point ptDst, size size, ::ca::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop);
      virtual bool from(size size, ::ca::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop);
      virtual bool from(size size, ::ca::graphics * pgraphicsSrc, uint32_t dwRop);
      virtual bool PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop);
      virtual bool BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc,
         int32_t xSrc, int32_t ySrc, uint32_t dwRop);
      virtual bool StretchBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc,
         int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop);
      virtual COLORREF GetPixel(int32_t x, int32_t y) const;
      virtual COLORREF GetPixel(POINT point) const;
      virtual COLORREF SetPixel(int32_t x, int32_t y, COLORREF crColor);
      virtual COLORREF SetPixel(POINT point, COLORREF crColor);
      virtual bool FloodFill(int32_t x, int32_t y, COLORREF crColor);
      virtual bool ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType);
      virtual bool MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc,
         int32_t xSrc, int32_t ySrc, ::ca::bitmap& maskBitmap, int32_t xMask, int32_t yMask,
         uint32_t dwRop);
      virtual bool PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
         int32_t nWidth, int32_t nHeight, ::ca::bitmap& maskBitmap, int32_t xMask, int32_t yMask);
      virtual bool SetPixelV(int32_t x, int32_t y, COLORREF crColor);
      virtual bool SetPixelV(POINT point, COLORREF crColor);
      virtual bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
        void * pMesh, ULONG nMeshElements, uint32_t dwMode);
      virtual bool TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
        ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
        UINT clrTransparent);

      virtual bool alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dOpacity);
      virtual bool alpha_blend(point ptDst, size szDst,::ca::graphics * pgraphicsSrc, point ptSrc, size szSrc, double dOpacity);
      virtual bool alpha_blend(point ptDst, size sz,::ca::graphics * pgraphicsSrc, point ptSrc, double dOpacity);
      virtual bool alpha_blend(point ptDst, size sz,::ca::graphics * pgraphicsSrc, double dOpacity);
      virtual bool alpha_blend(size sz,::ca::graphics * pgraphicsSrc, point ptSrc, double dOpacity);
      virtual bool alpha_blend(size sz,::ca::graphics * pgraphicsSrc, double dOpacity);

/*      virtual bool alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
        ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
        BLENDFUNCTION blend);*/
/*      virtual bool alpha_blend(point ptDst, size szDst,::ca::graphics * pgraphicsSrc, point ptSrc, size szSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size sz,::ca::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size sz,::ca::graphics * pgraphicsSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(size sz,::ca::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(size sz,::ca::graphics * pgraphicsSrc, BLENDFUNCTION blend);*/

   // Text Functions
      virtual bool TextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount);
      virtual bool TextOut(int32_t x, int32_t y, const string & str);
      virtual bool TextOut(double x, double y, const char * lpszString, int32_t nCount);
      virtual bool TextOut(double x, double y, const string & str);
      virtual bool ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect,
               const char * lpszString, UINT nCount, LPINT lpDxWidths);
      virtual bool ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect,
               const string & str, LPINT lpDxWidths);
      virtual size TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount,
               int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin);
      virtual size TabbedTextOut(int32_t x, int32_t y, const string & str,
               int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin);


      virtual int32_t draw_text(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat);
      virtual int32_t draw_text(const string & str, LPRECT lpRect, UINT nFormat);

#ifndef METROWIN
      virtual int32_t draw_text_ex(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual int32_t draw_text_ex(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
#endif

      virtual size GetTextExtent(const char * lpszString, strsize nCount, int32_t iIndex) const;
      virtual size GetTextExtent(const char * lpszString, strsize nCount) const;
      virtual size GetTextExtent(const string & str) const;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex) const;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) const;
      virtual bool GetTextExtent(sized & size, const string & str) const;
      virtual size GetOutputTextExtent(const char * lpszString, strsize nCount) const;
      virtual size GetOutputTextExtent(const string & str) const;
      virtual size GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const;
      virtual bool GrayString(::ca::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight);
      virtual UINT GetTextAlign() const;
      virtual UINT SetTextAlign(UINT nFlags);
      virtual int32_t GetTextFace(int32_t nCount, LPTSTR lpszFacename) const;
      virtual int32_t GetTextFace(string & rString) const;


      virtual bool get_text_metrics(LPTEXTMETRIC lpMetrics) const;
      virtual bool get_output_text_metrics(LPTEXTMETRIC lpMetrics) const;


      virtual int32_t SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount);
      virtual int32_t GetTextCharacterExtra() const;
      virtual int32_t SetTextCharacterExtra(int32_t nCharExtra);

#ifdef WINDOWSEX

      virtual uint32_t GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const;
      virtual uint32_t GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const;

#endif

#if (_WIN32_WINNT >= 0x0500)

      virtual bool GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
      virtual bool GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, __out_opt LPSIZE lpSize) const;

#endif



   // Advanced Drawing
      virtual bool DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags);
      virtual bool DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState);

   // Scrolling Functions
      virtual bool ScrollDC(int32_t dx, int32_t dy, LPCRECT lpRectScroll, LPCRECT lpRectClip,
         ::ca::region* pRgnUpdate, LPRECT lpRectUpdate);

   // font Functions
      virtual bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      virtual bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      virtual uint32_t SetMapperFlags(uint32_t dwFlag);
      virtual size GetAspectRatioFilter() const;

#ifdef WINDOWSEX

      virtual bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;

#endif

      virtual uint32_t GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData, uint32_t cbData) const;

#ifdef WINDOWSEX

      virtual int32_t GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const;
      virtual UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
      virtual uint32_t GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, uint32_t cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      virtual bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const;

#endif

      virtual bool GetCharWidth(UINT nFirstChar, UINT nLastChar, float * lpFloatBuffer) const;

      virtual uint32_t GetFontLanguageInfo() const;

#if defined(WINDOWSEX) && (_WIN32_WINNT >= 0x0500)

      virtual bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      virtual bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

   // Printer/Device Escape Functions
      virtual int32_t Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData);
      virtual int32_t Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData, int32_t nOutputSize, char * lpszOutputData);
      virtual int32_t DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData);

      // Escape helpers
      virtual int32_t StartDoc(const char * lpszDocName);  // old Win3.0 version

#ifdef WINDOWSEX

      virtual int32_t StartDoc(LPDOCINFO lpDocInfo);

#endif

      virtual int32_t StartPage();
      virtual int32_t EndPage();
      virtual int32_t SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t));
      virtual int32_t AbortDoc();
      virtual int32_t EndDoc();

      // MetaFile Functions
#ifdef WINDOWS
      virtual bool PlayMetaFile(HMETAFILE hMF);
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds);
#endif
      virtual bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
         // can be used for enhanced metafiles only

   // Path Functions
      virtual bool AbortPath();
      virtual bool BeginPath();
      virtual bool CloseFigure();
      virtual bool EndPath();
      virtual bool FillPath();
      virtual bool FlattenPath();
      virtual bool StrokeAndFillPath();
      virtual bool StrokePath();
      virtual bool WidenPath();
      virtual float GetMiterLimit() const;
      virtual bool SetMiterLimit(float fMiterLimit);
      virtual int32_t GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount) const;
      virtual bool SelectClipPath(int32_t nMode);


      virtual bool draw_path(::ca::graphics_path * ppath);
      virtual bool fill_path(::ca::graphics_path * ppath);
      virtual bool path(::ca::graphics_path * ppath);

   // Misc Helper Functions
      virtual ::ca::brush * GetHalftoneBrush();
      virtual void DrawDragRect(LPCRECT lpRect, SIZE size,
         LPCRECT lpRectLast, SIZE sizeLast,
         ::ca::brush* pBrush = NULL, ::ca::brush* pBrushLast = NULL);
      virtual void FillSolidRect(const __rect64 * lpRect, COLORREF clr);
      virtual void FillSolidRect(LPCRECT lpRect, COLORREF clr);
      virtual void FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr);
      virtual void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
      virtual void Draw3dRect(int32_t x, int32_t y, int32_t cx, int32_t cy,
         COLORREF clrTopLeft, COLORREF clrBottomRight);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      // advanced use and implementation
      bool m_bPrinting;
      //virtual HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      virtual bool SelectFont(::ca::font * pfont);
      virtual bool selectFont(::ca::font * pfont);
      virtual bool select_font(::ca::font * pfont);
      virtual bool SetFont(::ca::font * pfont);
      virtual bool setFont(::ca::font * pfont);
      virtual bool set_font(::ca::font * pfont);

   };

   typedef smart_pointer < graphics > graphics_sp;

   class CLASS_DECL_ca memory_graphics :
      public graphics_sp
   {
   public:

      memory_graphics(::ca::application * papp);
      virtual ~memory_graphics();

   };

   class CLASS_DECL_ca client_graphics :
      virtual public graphics_sp
   {
   public:

      ::user::interaction * m_pui;

      client_graphics(::user::interaction * pui);
      virtual ~client_graphics();

   };

   class CLASS_DECL_ca window_graphics :
      virtual public graphics_sp
   {
   public:

      ::ca::window * m_pwindow;

      window_graphics(::ca::window * pwindow);
      virtual ~window_graphics();

   };

   class CLASS_DECL_ca paint_graphics :
      virtual public graphics_sp
   {
   public:

      ::ca::window *    m_pwindow;
#ifdef WINDOWSEX
      PAINTSTRUCT       m_ps;
#endif

      paint_graphics(::ca::window * pwindow);
      virtual ~paint_graphics();

   };

} // namespace ca


