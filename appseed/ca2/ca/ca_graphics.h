#pragma once


#include "user/user_draw_context.h"


namespace user
{
   class str_context;
}

/////////////////////////////////////////////////////////////////////////////
// The device context

namespace ca
{

   class dib;
   class job;

   enum e_alpha_mode
   {
      alpha_mode_set,
      alpha_mode_blend,
   };

   class CLASS_DECL_ca graphics :
      virtual public _template::simple_chain < ::user::draw_context >
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

      graphics();

      virtual bool is_set();

      virtual void * get_os_data() const;
      virtual void attach(void * pdata);

      virtual ::user::str_context * str_context();
      virtual ::user::draw_context * draw_context();


      virtual void set_alpha_mode(e_alpha_mode ealphamode);

      void set_solid_pen(double dWidth);

      virtual BOOL IsPrinting() const;            // TRUE if being used for printing

      virtual ::ca::pen & GetCurrentPen() const;
      virtual ::ca::brush & GetCurrentBrush() const;
      virtual ::ca::palette & GetCurrentPalette() const;
      virtual ::ca::font & GetCurrentFont() const;
      virtual ::ca::bitmap & GetCurrentBitmap() const;

      // for bidi and mirrored localization
      virtual DWORD GetLayout() const;
      virtual DWORD SetLayout(DWORD dwLayout);

   // Constructors
      virtual BOOL CreateDC(const char * lpszDriverName, const char * lpszDeviceName,
         const char * lpszOutput, const void * lpInitData);
      virtual BOOL CreateIC(const char * lpszDriverName, const char * lpszDeviceName,
         const char * lpszOutput, const void * lpInitData);
      virtual BOOL CreateCompatibleDC(::ca::graphics * pgraphics);

      virtual BOOL DeleteDC();

   // Device-Context Functions
      virtual int SaveDC();
      virtual BOOL RestoreDC(int nSavedDC);
      virtual int GetDeviceCaps(int nIndex) const;
      virtual UINT SetBoundsRect(LPCRECT lpRectBounds, UINT flags);
      virtual UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags);
#ifdef WINDOWS
      virtual BOOL ResetDC(const DEVMODE* lpDevMode);
#endif

   // Drawing-Tool Functions
      virtual point GetBrushOrg() const;
      virtual point SetBrushOrg(int x, int y);
      virtual point SetBrushOrg(POINT point);
      virtual int EnumObjects(int nObjectType,
            int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

   // Type-safe selection helpers
   public:
      virtual ::ca::graphics_object* SelectStockObject(int nIndex);
      virtual ::ca::pen* SelectObject(::ca::pen* pPen);
      virtual ::ca::brush* SelectObject(::ca::brush* pBrush);
      virtual ::ca::font* SelectObject(::ca::font* pFont);
      virtual ::ca::bitmap* SelectObject(::ca::bitmap* pBitmap);
      virtual int SelectObject(::ca::region* pRgn);       // special return for regions
      virtual ::ca::graphics_object* SelectObject(::ca::graphics_object* pObject);
         // ::ca::graphics_object* provided so compiler doesn't use SelectObject(HGDIOBJ)

   // color and color Palette Functions
      virtual COLORREF GetNearestColor(COLORREF crColor) const;
      virtual ::ca::palette* SelectPalette(::ca::palette* pPalette, BOOL bForceBackground);
      virtual UINT RealizePalette();
      virtual void UpdateColors();

   // Drawing-Attribute Functions
      virtual COLORREF GetBkColor() const;
      virtual int GetBkMode() const;
      virtual int GetPolyFillMode() const;
      virtual int GetROP2() const;
      virtual int GetStretchBltMode() const;
      virtual COLORREF GetTextColor() const;

      virtual COLORREF SetBkColor(COLORREF crColor);
      virtual int SetBkMode(int nBkMode);
      virtual int SetPolyFillMode(int nPolyFillMode);
      virtual int SetROP2(int nDrawMode);
      virtual int SetStretchBltMode(int nStretchMode);
      virtual COLORREF SetTextColor(COLORREF crColor);

      virtual COLORREF SetColor(COLORREF crColor);
      virtual COLORREF setColor(COLORREF crColor);
      virtual COLORREF set_color(COLORREF crColor);



#ifdef WINDOWS
      virtual BOOL GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      virtual BOOL SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);
#endif

   #if (_WIN32_WINNT >= 0x0500)

      virtual COLORREF GetDCBrushColor() const;
      virtual COLORREF SetDCBrushColor(COLORREF crColor);

      virtual COLORREF GetDCPenColor() const;
      virtual COLORREF SetDCPenColor(COLORREF crColor);

   #endif

      // Graphics mode
      virtual int SetGraphicsMode(int iMode);
      virtual int GetGraphicsMode() const;

      // World transform
#ifdef WINDOWS
      virtual BOOL SetWorldTransform(const XFORM* pXform);
      virtual BOOL ModifyWorldTransform(const XFORM* pXform,DWORD iMode);
      virtual BOOL GetWorldTransform(XFORM* pXform) const;
#endif

      // Mapping Functions
      virtual int GetMapMode() const;
      virtual point GetViewportOrg() const;
      virtual int SetMapMode(int nMapMode);
      // Viewport Origin
      virtual point SetViewportOrg(int x, int y);
      virtual point SetViewportOrg(POINT point);
      virtual point OffsetViewportOrg(int nWidth, int nHeight);

      // Viewport Extent
      virtual size GetViewportExt() const;
      virtual size SetViewportExt(int cx, int cy);
      virtual size SetViewportExt(SIZE size);
      virtual size ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom);

      // Window Origin
      virtual point GetWindowOrg() const;
      virtual point SetWindowOrg(int x, int y);
      virtual point SetWindowOrg(POINT point);
      virtual point OffsetWindowOrg(int nWidth, int nHeight);

      // Window extent
      virtual size GetWindowExt() const;
      virtual size SetWindowExt(int cx, int cy);
      virtual size SetWindowExt(SIZE size);
      virtual size ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom);

   // Coordinate Functions
      virtual void DPtoLP(LPPOINT lpPoints, int nCount = 1) const;
      virtual void DPtoLP(LPRECT lpRect) const;
      virtual void DPtoLP(LPSIZE lpSize) const;
      virtual void LPtoDP(LPPOINT lpPoints, int nCount = 1) const;
      virtual void LPtoDP(LPRECT lpRect) const;
      virtual void LPtoDP(LPSIZE lpSize) const;

   // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(LPSIZE lpSize) const;
      virtual void LPtoHIMETRIC(LPSIZE lpSize) const;
      virtual void HIMETRICtoDP(LPSIZE lpSize) const;
      virtual void HIMETRICtoLP(LPSIZE lpSize) const;

   // Region Functions
      virtual BOOL FillRgn(::ca::region* pRgn, ::ca::brush* pBrush);
      virtual BOOL FrameRgn(::ca::region* pRgn, ::ca::brush* pBrush, int nWidth, int nHeight);
      virtual BOOL InvertRgn(::ca::region* pRgn);
      virtual BOOL PaintRgn(::ca::region* pRgn);

   // Clipping Functions
      virtual int GetClipBox(LPRECT lpRect) const;
      virtual int GetClipBox(rect64 * lpRect) const;
      virtual BOOL PtVisible(int x, int y) const;
      virtual BOOL PtVisible(POINT point) const;
      virtual BOOL RectVisible(LPCRECT lpRect) const;
      virtual int SelectClipRgn(::ca::region* pRgn);
      virtual int ExcludeClipRect(int x1, int y1, int x2, int y2);
      virtual int ExcludeClipRect(LPCRECT lpRect);
      virtual int ExcludeUpdateRgn(::ca::window* pWnd);
      virtual int IntersectClipRect(int x1, int y1, int x2, int y2);
      virtual int IntersectClipRect(LPCRECT lpRect);
      virtual int OffsetClipRgn(int x, int y);
      virtual int OffsetClipRgn(SIZE size);
      virtual int SelectClipRgn(::ca::region* pRgn, int nMode);

   // Line-Output Functions

      virtual point DrawLine(int x1, int y1, int x2, int y2);
      virtual point drawLine(int x1, int y1, int x2, int y2);
      virtual point draw_line(int x1, int y1, int x2, int y2);

      virtual BOOL DrawRect(int x1, int y1, int x2, int y2);
      virtual BOOL drawRect(int x1, int y1, int x2, int y2);
      virtual BOOL draw_rect(int x1, int y1, int x2, int y2);


      virtual point GetCurrentPosition() const;
      virtual point MoveTo(int x, int y);
      virtual point MoveTo(double x, double y);
      virtual point MoveTo(POINT point);
      virtual BOOL LineTo(int x, int y);
      virtual BOOL LineTo(double x, double y);
      virtual BOOL LineTo(POINT point);
      virtual BOOL Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      virtual BOOL Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual BOOL Arc(int x1, int y1, int x2, int y2, double start, double extends);
      virtual BOOL Arc(LPCRECT lpRect, double start, double extends);
      virtual BOOL Polyline(const POINT* lpPoints, int nCount);

      virtual BOOL AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle);
      virtual BOOL ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      virtual BOOL ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual int GetArcDirection() const;
      virtual int SetArcDirection(int nArcDirection);

      virtual BOOL PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount);
      virtual BOOL PolylineTo(const POINT* lpPoints, int nCount);
      virtual BOOL PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount);

      virtual BOOL PolyBezier(const POINT* lpPoints, int nCount);
      virtual BOOL PolyBezierTo(const POINT* lpPoints, int nCount);

   // Simple Drawing Functions
      virtual void FillRect(LPCRECT lpRect, ::ca::brush* pBrush);
      virtual void FrameRect(LPCRECT lpRect, ::ca::brush* pBrush);
      virtual void InvertRect(LPCRECT lpRect);
      virtual BOOL DrawIcon(int x, int y, ::visual::icon * picon);
      virtual BOOL DrawIcon(POINT point, ::visual::icon * picon);
      virtual BOOL DrawIcon(int x, int y, ::visual::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
      virtual BOOL DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
         HBRUSH hBrush = NULL);
      virtual BOOL DrawState(point pt, size size, ::ca::bitmap* pBitmap, UINT nFlags,
         ::ca::brush* pBrush = NULL);
#ifdef WINDOWS
      virtual BOOL DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         HBRUSH hBrush = NULL);
      virtual BOOL DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         ::ca::brush* pBrush = NULL);
#endif
      virtual BOOL DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         BOOL bPrefixText = TRUE, int nTextLen = 0, HBRUSH hBrush = NULL);
      virtual BOOL DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         BOOL bPrefixText = TRUE, int nTextLen = 0, ::ca::brush* pBrush = NULL);
#ifdef WINDOWS
      virtual BOOL DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
      virtual BOOL DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, ::ca::brush* pBrush = NULL);
#endif
   // Ellipse and Polygon Functions
      virtual BOOL Chord(int x1, int y1, int x2, int y2, int x3, int y3,
         int x4, int y4);
      virtual BOOL Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual void DrawFocusRect(LPCRECT lpRect);
      virtual BOOL Ellipse(int x1, int y1, int x2, int y2);
      virtual BOOL Ellipse(LPCRECT lpRect);
      virtual BOOL DrawEllipse(int x1, int y1, int x2, int y2);
      virtual BOOL DrawEllipse(LPCRECT lpRect);
      virtual BOOL FillEllipse(int x1, int y1, int x2, int y2);
      virtual BOOL FillEllipse(LPCRECT lpRect);
      virtual BOOL Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      virtual BOOL Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      virtual BOOL Polygon(point_array & pta);
      virtual BOOL Polygon(const POINT* lpPoints, int nCount);
      virtual BOOL PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int nCount);
      virtual BOOL Rectangle(int x1, int y1, int x2, int y2);
      virtual BOOL Rectangle(LPCRECT lpRect);
      virtual BOOL RoundRect(int x1, int y1, int x2, int y2, int x3, int y3);
      virtual BOOL RoundRect(LPCRECT lpRect, POINT point);

   // Bitmap Functions
      virtual bool from(point ptDst, size size, ::ca::graphics * pgraphicsSrc, point ptSrc, DWORD dwRop);
      virtual bool from(size size, ::ca::graphics * pgraphicsSrc, point ptSrc, DWORD dwRop);
      virtual bool from(size size, ::ca::graphics * pgraphicsSrc, DWORD dwRop);
      virtual BOOL PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop);
      virtual BOOL BitBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
         int xSrc, int ySrc, DWORD dwRop);
      virtual BOOL StretchBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
         int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop);
      virtual COLORREF GetPixel(int x, int y) const;
      virtual COLORREF GetPixel(POINT point) const;
      virtual COLORREF SetPixel(int x, int y, COLORREF crColor);
      virtual COLORREF SetPixel(POINT point, COLORREF crColor);
      virtual BOOL FloodFill(int x, int y, COLORREF crColor);
      virtual BOOL ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType);
      virtual BOOL MaskBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
         int xSrc, int ySrc, ::ca::bitmap& maskBitmap, int xMask, int yMask,
         DWORD dwRop);
      virtual BOOL PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc,
         int nWidth, int nHeight, ::ca::bitmap& maskBitmap, int xMask, int yMask);
      virtual BOOL SetPixelV(int x, int y, COLORREF crColor);
      virtual BOOL SetPixelV(POINT point, COLORREF crColor);
      virtual BOOL GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
        void * pMesh, ULONG nMeshElements, DWORD dwMode);
      virtual BOOL TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        UINT clrTransparent);
      virtual bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size szDst,::ca::graphics * pgraphicsSrc, point ptSrc, size szSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size sz,::ca::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size sz,::ca::graphics * pgraphicsSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(size sz,::ca::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(size sz,::ca::graphics * pgraphicsSrc, BLENDFUNCTION blend);

   // Text Functions
      virtual BOOL TextOut(int x, int y, const char * lpszString, int nCount);
      virtual BOOL TextOut(int x, int y, const string & str);
      virtual BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
               const char * lpszString, UINT nCount, LPINT lpDxWidths);
      virtual BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
               const string & str, LPINT lpDxWidths);
      virtual size TabbedTextOut(int x, int y, const char * lpszString, int nCount,
               int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
      virtual size TabbedTextOut(int x, int y, const string & str,
               int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

   #pragma push_macro("DrawText")
   #pragma push_macro("DrawTextEx")
   #undef DrawText
   #undef DrawTextEx
      virtual int _AFX_FUNCNAME(DrawText)(const char * lpszString, int nCount, LPRECT lpRect,
               UINT nFormat);
      virtual int _AFX_FUNCNAME(DrawText)(const string & str, LPRECT lpRect, UINT nFormat);
#ifdef WINDOWS
      virtual int _AFX_FUNCNAME(DrawTextEx)(LPTSTR lpszString, int nCount, LPRECT lpRect,
               UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual int _AFX_FUNCNAME(DrawTextEx)(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
#endif

      virtual int DrawText(const char * lpszString, int nCount, LPRECT lpRect,
               UINT nFormat);
      virtual int DrawText(const string & str, LPRECT lpRect, UINT nFormat);
#ifdef WINDOWS
      virtual int DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect,
               UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual int DrawTextEx(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
#endif
   #pragma pop_macro("DrawText")
   #pragma pop_macro("DrawTextEx")

      virtual size GetTextExtent(const char * lpszString, int nCount) const;
      virtual size GetTextExtent(const string & str) const;
      virtual size GetOutputTextExtent(const char * lpszString, int nCount) const;
      virtual size GetOutputTextExtent(const string & str) const;
      virtual size GetTabbedTextExtent(const char * lpszString, int nCount,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetTabbedTextExtent(const string & str,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetOutputTabbedTextExtent(const char * lpszString, int nCount,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetOutputTabbedTextExtent(const string & str,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      virtual BOOL GrayString(::ca::brush* pBrush,
         BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData,
            int nCount, int x, int y, int nWidth, int nHeight);
      virtual UINT GetTextAlign() const;
      virtual UINT SetTextAlign(UINT nFlags);
      virtual int GetTextFace(int nCount, LPTSTR lpszFacename) const;
      virtual int GetTextFace(string & rString) const;
   #pragma push_macro("GetTextMetrics")
   #undef GetTextMetrics
#ifdef WINDOWS
      virtual BOOL _AFX_FUNCNAME(GetTextMetrics)(LPTEXTMETRIC lpMetrics) const;
      virtual BOOL GetTextMetrics(LPTEXTMETRIC lpMetrics) const;
#endif
   #pragma pop_macro("GetTextMetrics")
#ifdef WINDOWS
      virtual BOOL GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const;
#endif
      virtual int SetTextJustification(int nBreakExtra, int nBreakCount);
      virtual int GetTextCharacterExtra() const;
      virtual int SetTextCharacterExtra(int nCharExtra);
#ifdef WINDOWS
      virtual DWORD GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;
      virtual DWORD GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;
#endif
   #if (_WIN32_WINNT >= 0x0500)

      virtual BOOL GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
      virtual BOOL GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE lpSize) const;

   #endif



   // Advanced Drawing
      virtual BOOL DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags);
      virtual BOOL DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState);

   // Scrolling Functions
      virtual BOOL ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip,
         ::ca::region* pRgnUpdate, LPRECT lpRectUpdate);

   // font Functions
      virtual BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      virtual BOOL GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      virtual DWORD SetMapperFlags(DWORD dwFlag);
      virtual size GetAspectRatioFilter() const;
#ifdef WINDOWS
      virtual BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
#endif
      virtual DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const;
#ifdef WINDOWS

      virtual int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const;
      virtual UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
      virtual DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
         DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      virtual BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
         LPABCFLOAT lpABCF) const;
#endif
      virtual BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar,
         float* lpFloatBuffer) const;

      virtual DWORD GetFontLanguageInfo() const;

   #if (_WIN32_WINNT >= 0x0500)

      virtual BOOL GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      virtual BOOL GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;

   #endif

   // Printer/Device Escape Functions
      virtual int Escape(int nEscape, int nCount,
         const char * lpszInData, LPVOID lpOutData);
      virtual int Escape(int nEscape, int nInputSize, const char * lpszInputData,
         int nOutputSize, char * lpszOutputData);
      virtual int DrawEscape(int nEscape, int nInputSize, const char * lpszInputData);

      // Escape helpers
      virtual int StartDoc(const char * lpszDocName);  // old Win3.0 version
   #ifdef WINDOWS
      virtual int StartDoc(LPDOCINFO lpDocInfo);
   #endif
      virtual int StartPage();
      virtual int EndPage();
      virtual int SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, int));
      virtual int AbortDoc();
      virtual int EndDoc();

   // MetaFile Functions
#ifdef WINDOWS
      virtual BOOL PlayMetaFile(HMETAFILE hMF);
      virtual BOOL PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds);
#endif
      virtual BOOL AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
         // can be used for enhanced metafiles only

   // Path Functions
      virtual BOOL AbortPath();
      virtual BOOL BeginPath();
      virtual BOOL CloseFigure();
      virtual BOOL EndPath();
      virtual BOOL FillPath();
      virtual BOOL FlattenPath();
      virtual BOOL StrokeAndFillPath();
      virtual BOOL StrokePath();
      virtual BOOL WidenPath();
      virtual float GetMiterLimit() const;
      virtual BOOL SetMiterLimit(float fMiterLimit);
      virtual int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const;
      virtual BOOL SelectClipPath(int nMode);

   // Misc Helper Functions
      static ::ca::brush* PASCAL GetHalftoneBrush();
      virtual void DrawDragRect(LPCRECT lpRect, SIZE size,
         LPCRECT lpRectLast, SIZE sizeLast,
         ::ca::brush* pBrush = NULL, ::ca::brush* pBrushLast = NULL);
      virtual void FillSolidRect(const __rect64 * lpRect, COLORREF clr);
      virtual void FillSolidRect(LPCRECT lpRect, COLORREF clr);
      virtual void FillSolidRect(int x, int y, int cx, int cy, COLORREF clr);
      virtual void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
      virtual void Draw3dRect(int x, int y, int cx, int cy,
         COLORREF clrTopLeft, COLORREF clrBottomRight);

   // Implementation
   public:
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      // advanced use and implementation
      BOOL m_bPrinting;
      virtual HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      virtual bool SelectFont(::ca::font * pfont);
      virtual bool selectFont(::ca::font * pfont);
      virtual bool select_font(::ca::font * pfont);
      virtual bool SetFont(::ca::font * pfont);
      virtual bool setFont(::ca::font * pfont);
      virtual bool set_font(::ca::font * pfont);

   protected:
      // used for implementation of non-virtual SelectObject calls
      static ::ca::graphics_object* PASCAL SelectGdiObject(HDC hDC, HGDIOBJ h);
   };

   typedef smart_pointer < graphics > graphics_sp;

   class CLASS_DECL_ca client_graphics :
      virtual public graphics_sp
   {
   public:

      ::ca::window * m_pwindow;

      client_graphics(::ca::window * pwindow);
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
#ifdef WINDOWS
      PAINTSTRUCT       m_ps;
#endif

      paint_graphics(::ca::window * pwindow);
      virtual ~paint_graphics();

   };

} // namespace ca


