#pragma once


namespace draw2d
{


   class CLASS_DECL_BASE graphics :
      virtual public ::object,
      public ::core::simple_chain < ::user::draw_context >
   {
   public:


      ::user::str_context *         m_puistrcontext;
      ::user::draw_context *        m_pdrawcontext;
      ::draw2d::dib *               m_pdibAlphaBlend;
      point                         m_ptAlphaBlend;
      ::job *                       m_pjob;


      ::draw2d::dib *               m_pdib;
      ::draw2d::bitmap_sp           m_spbitmap;
      ::draw2d::pen_sp              m_sppen;
      ::draw2d::brush_sp            m_spbrush;
      ::draw2d::font_sp             m_spfont;
      ::draw2d::region_sp           m_spregion;


      //::draw2d::pen                 m_penxyz;
      //::draw2d::brush               m_brushxyz;
      //::draw2d::font                m_fontxyz;
      //::draw2d::region              m_regionxyz;

      COLORREF                      m_crColor;
      double                        m_x;
      double                        m_y;

      e_alpha_mode                  m_ealphamode;
      e_text_rendering              m_etextrendering;
      double                        m_dFontFactor;

      // advanced use and implementation
      bool                          m_bPrinting;




      graphics();

      virtual bool is_set();

      virtual void * get_os_data() const;
      virtual void * get_os_data_ex(int i) const;

      template < typename T >
      T * get_typed_os_data(int i) const
      {
         return (T *) get_os_data_ex(i);
      }

      virtual bool attach(void * pdata);
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

      virtual ::draw2d::pen_sp      get_current_pen() const;
      virtual ::draw2d::brush_sp    get_current_brush() const;
      virtual ::draw2d::palette_sp  get_current_palette() const;
      virtual ::draw2d::font_sp     get_current_font() const;
      virtual ::draw2d::bitmap_sp   get_current_bitmap() const;

      // for bidi and mirrored localization
      virtual uint32_t GetLayout() const;
      virtual uint32_t SetLayout(uint32_t dwLayout);

   // Constructors
      virtual bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData);
      virtual bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData);
      virtual bool CreateCompatibleDC(::draw2d::graphics * pgraphics);

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


      virtual bool set_text_color(COLORREF clr);

   // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(int32_t nIndex);
      virtual ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      virtual ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont);
      virtual ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      virtual int32_t SelectObject(::draw2d::region* pRgn);       // special return for regions


   // color and color Palette Functions
      virtual COLORREF GetNearestColor(COLORREF crColor) const;
      virtual ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      virtual UINT RealizePalette();
      virtual void UpdateColors();

   // Drawing-Attribute Functions
      virtual int32_t GetPolyFillMode() const;
      virtual int32_t GetROP2() const;
      virtual int32_t GetStretchBltMode() const;


      virtual double get_dpix() const;

      virtual int32_t SetPolyFillMode(int32_t nPolyFillMode);
      virtual int32_t SetROP2(int32_t nDrawMode);
      virtual int32_t SetStretchBltMode(int32_t nStretchMode);


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
      virtual bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      virtual bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight);
      virtual bool InvertRgn(::draw2d::region* pRgn);
      virtual bool PaintRgn(::draw2d::region* pRgn);

   // Clipping Functions
      virtual int32_t GetClipBox(LPRECT lpRect) const;
      virtual int32_t GetClipBox(rect64 * lpRect) const;
      virtual bool PtVisible(int32_t x, int32_t y) const;
      virtual bool PtVisible(POINT point) const;
      virtual bool RectVisible(LPCRECT lpRect) const;
      virtual int32_t SelectClipRgn(::draw2d::region* pRgn);
      virtual int32_t ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual int32_t ExcludeClipRect(LPCRECT lpRect);
//      virtual int32_t ExcludeUpdateRgn(::window_sp pwindow);
      virtual int32_t IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual int32_t IntersectClipRect(LPCRECT lpRect);
      virtual int32_t OffsetClipRgn(int32_t x, int32_t y);
      virtual int32_t OffsetClipRgn(SIZE size);
      virtual int32_t SelectClipRgn(::draw2d::region* pRgn, int32_t nMode);

   // Line-Output Functions

      virtual bool DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

      virtual bool DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen);
      virtual bool drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen);
      virtual bool draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen);

      virtual bool DrawLine(float x1, float y1, float x2, float y2);
      virtual bool drawLine(float x1, float y1, float x2, float y2);
      virtual bool draw_line(float x1, float y1, float x2, float y2);

      virtual bool DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);
      virtual bool drawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);
      virtual bool draw_line(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);

      virtual bool DrawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool drawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool draw_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

      virtual bool DrawRect(LPCRECT lpcrect, ::draw2d::pen * ppen);
      virtual bool drawRect(LPCRECT lpcrect, ::draw2d::pen * ppen);
      virtual bool draw_rect(LPCRECT lpcrect, ::draw2d::pen * ppen);


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
      virtual void FillRect(LPCRECT lpRect, ::draw2d::brush* pBrush);
      virtual void FrameRect(LPCRECT lpRect, ::draw2d::brush* pBrush);
      virtual void InvertRect(LPCRECT lpRect);
      virtual bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon);
      virtual bool DrawIcon(POINT point, ::visual::icon * picon);
      virtual bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
      virtual bool DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
         HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags,
         ::draw2d::brush* pBrush = NULL);
#ifdef WINDOWS
      virtual bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         ::draw2d::brush* pBrush = NULL);
#endif
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         bool bPrefixText = TRUE, int32_t nTextLen = 0, HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         bool bPrefixText = TRUE, int32_t nTextLen = 0, ::draw2d::brush* pBrush = NULL);
#ifdef WINDOWSEX
      virtual bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = NULL);
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
      virtual bool fill_polygon(point_array & pta);
      virtual bool fill_polygon(pointd_array & pta);
      virtual bool draw_polygon(const POINT* lpPoints, int32_t nCount);
      virtual bool draw_polygon(const POINTD* lpPoints,int32_t nCount);
      virtual bool draw_polygon(point_array & pta);
      virtual bool draw_polygon(pointd_array & pta);
      virtual bool Polygon(point_array & pta);
      virtual bool Polygon(pointd_array & pta);
      virtual bool Polygon(const POINT* lpPoints, int32_t nCount);
      virtual bool Polygon(const POINTD* lpPoints,int32_t nCount);
      virtual bool PolyPolygon(const POINT* lpPoints,const INT* lpPolyCounts,int32_t nCount);
      virtual bool Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool Rectangle(LPCRECT lpRect);
      virtual bool DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool DrawRectangle(LPCRECT lpRect);
      virtual bool FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool FillRectangle(LPCRECT lpRect);
      virtual bool RoundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3);
      virtual bool RoundRect(LPCRECT lpRect, POINT point);

   // Bitmap Functions
      virtual bool from(point ptDst, size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop);
      virtual bool from(size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop);
      virtual bool from(size size, ::draw2d::graphics * pgraphicsSrc, uint32_t dwRop);
      virtual bool PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop);

      virtual bool BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc = 0, int32_t ySrc = 0, uint32_t dwRop = SRCCOPY);
      virtual bool BitBlt(LPCRECT lpcrect, ::draw2d::graphics * pgraphicsSrc, POINT ptSrc = ::null_point(), uint32_t dwRop = SRCCOPY);
      virtual bool BitBlt(POINT ptDst, SIZE size, ::draw2d::graphics * pgraphicsSrc, POINT ptSrc = ::null_point(), uint32_t dwRop = SRCCOPY);

      virtual bool StretchBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
         int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop);
      virtual COLORREF GetPixel(int32_t x, int32_t y) const;
      virtual COLORREF GetPixel(POINT point) const;
      virtual COLORREF SetPixel(int32_t x, int32_t y, COLORREF crColor);
      virtual COLORREF SetPixel(POINT point, COLORREF crColor);
      virtual bool FloodFill(int32_t x, int32_t y, COLORREF crColor);
      virtual bool ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType);
      virtual bool MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
         int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask,
         uint32_t dwRop);
      virtual bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
         int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask);
      virtual bool SetPixelV(int32_t x, int32_t y, COLORREF crColor);
      virtual bool SetPixelV(POINT point, COLORREF crColor);
      virtual bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
        void * pMesh, ULONG nMeshElements, uint32_t dwMode);
      virtual bool TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
        UINT clrTransparent);

      virtual bool alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dOpacity);
      virtual bool alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, double dOpacity);
      virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, double dOpacity);
      virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, double dOpacity);
      virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, double dOpacity);
      virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, double dOpacity);

/*      virtual bool alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
        BLENDFUNCTION blend);*/
/*      virtual bool alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
      virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend);*/

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
      virtual int32_t draw_text(const char * lpszString,strsize nCount,LPRECTD lpRect,UINT nFormat);
      virtual int32_t draw_text(const string & str,LPRECTD lpRect,UINT nFormat);

#ifndef METROWIN
      virtual int32_t draw_text_ex(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual int32_t draw_text_ex(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual int32_t draw_text_ex(const char * lpszString,strsize nCount,LPRECTD lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
      virtual int32_t draw_text_ex(const string & str,LPRECTD lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
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
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight);
      virtual UINT GetTextAlign() const;
      virtual UINT SetTextAlign(UINT nFlags);
      virtual int32_t GetTextFace(int32_t nCount, LPTSTR lpszFacename) const;
      virtual int32_t GetTextFace(string & rString) const;


      virtual bool get_text_metrics(text_metric * lpMetrics) const;
      virtual bool get_output_text_metrics(text_metric * lpMetrics) const;


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
         ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate);

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
      virtual UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) const;
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

      virtual bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      virtual bool draw_path(::draw2d::path * ppath);
      virtual bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      virtual bool fill_path(::draw2d::path * ppath);
      virtual bool path(::draw2d::path * ppath);

   // Misc Helper Functions
      virtual ::draw2d::brush * GetHalftoneBrush();
      virtual void DrawDragRect(LPCRECT lpRect, SIZE size,
         LPCRECT lpRectLast, SIZE sizeLast,
         ::draw2d::brush* pBrush = NULL, ::draw2d::brush* pBrushLast = NULL);
      virtual void FillSolidRect(const __rect64 * lpRect, COLORREF clr);
      virtual void FillSolidRect(LPCRECT lpRect, COLORREF clr);
      virtual void FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr);
      virtual void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
      virtual void Draw3dRect(int32_t x, int32_t y, int32_t cx, int32_t cy,
         COLORREF clrTopLeft, COLORREF clrBottomRight);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool SelectFont(::draw2d::font * pfont);
      virtual bool selectFont(::draw2d::font * pfont);
      virtual bool select_font(::draw2d::font * pfont);
      virtual bool SetFont(::draw2d::font * pfont);
      virtual bool setFont(::draw2d::font * pfont);
      virtual bool set_font(::draw2d::font * pfont);



      //=============================================================================
      //
      // draw_round_rect()
      //
      // Purpose:     Draws a rounded rectangle with a solid pen
      //
      // Parameters:  pGraphics	- [in]	pointer to the Graphics device
      //				r			- [in]	Rect that defines the round rectangle boundaries
      //				color		- [in]	Color value for the brush
      //				radius		- [in]  radius of the rounded corner
      //				width		- [in]  width of the border
      //
      // Returns:     None
      //
      bool draw_round_rect(const RECT & r, ::draw2d::pen * ppen, int32_t radius);
      bool draw_round_top_left(const RECT & r, ::draw2d::pen * ppen, int32_t radius);
      bool draw_round_bottom_right(const RECT & r, ::draw2d::pen * ppen, int32_t radius);

      bool draw_round_rect(const RECT & r, COLORREF color, int32_t radius, int32_t width);
      bool draw_round_top_left(const RECT & r, COLORREF color, int32_t radius, int32_t width);
      bool draw_round_bottom_right(const RECT & r, COLORREF color, int32_t radius, int32_t width);

      //=============================================================================
      //
      // fill_round_rect()
      //
      // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
      //				first then fills in the rectangle.
      //
      // Parameters:  pGraphics	- [in]	pointer to the Graphics device
      //				r			- [in]	Rect that defines the round rectangle boundaries
      //				color		- [in]	Color value for the brush
      //				radius		- [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      bool fill_round_rect(const RECT & r, COLORREF color, int32_t radius);

      //=============================================================================
      //
      // fill_round_rect()
      //
      // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
      //				first then fills in the rectangle.
      //
      // Parameters:  pGraphics	- [in]	pointer to the Graphics device
      //				pBrush		- [in]  pointer to a Brush
      //				r			- [in]	Rect that defines the round rectangle boundaries
      //				color		- [in]	Color value for the border (needed in case the
      //									brush is a type other than solid)
      //				radius		- [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      bool fill_round_rect(const RECT & r, ::draw2d::brush * pbrush, int32_t radius);


      bool round_rect(const RECT & r, int32_t radius);

      virtual int32_t _DrawText(const char * lpcsz, strsize iCount, LPCRECT lpcrect, UINT uiFormat, ::draw2d::font * pfontUnderline = NULL);
      virtual int32_t _DrawText(const string & str, LPCRECT lpcrect, UINT uiFormat, ::draw2d::font * pfontUnderline = NULL);

#ifdef WINDOWSEX

      virtual bool Attach(HDC hdc);
      virtual HDC Detach();
      virtual bool AttachPrinter(HDC hdc);
      virtual HDC DetachPrinter();

#endif


   };

   class CLASS_DECL_BASE graphics_sp :
      public smart_pointer < graphics >
   {
   public:

      graphics_sp()
      {
      }

      graphics_sp(graphics * p) :
         smart_pointer < graphics > (p)
      {
      }


      graphics_sp(const smart_pointer < graphics > & p) :
         smart_pointer < graphics > (p)
      {
      }

      graphics_sp(allocatorsp allocer) :
         smart_pointer < graphics > (allocer)
      {
      }

   };

   class CLASS_DECL_BASE memory_graphics :
      public graphics_sp
   {
   public:

      memory_graphics(allocatorsp allocer);
      virtual ~memory_graphics();

   };


/*   class CLASS_DECL_BASE window_graphics :
      virtual public graphics_sp
   {
   public:

      ::window_sp m_pwindow;

      window_graphics(::window_sp pwindow);
      virtual ~window_graphics();

   };

   class CLASS_DECL_BASE paint_graphics :
      virtual public graphics_sp
   {
   public:

      ::window_sp    m_pwindow;
#ifdef WINDOWSEX
      PAINTSTRUCT       m_ps;
#endif

      paint_graphics(::window_sp pwindow);
      virtual ~paint_graphics();

   };*/



} // namespace base



CLASS_DECL_BASE dump_context & operator<<(dump_context & dumpcontext, SIZE size);
CLASS_DECL_BASE dump_context & operator<<(dump_context & dumpcontext, POINT point);
CLASS_DECL_BASE dump_context & operator<<(dump_context & dumpcontext, const RECT& rect);
