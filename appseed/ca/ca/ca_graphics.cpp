#include "framework.h"
#include <math.h>

namespace ca
{

   graphics::graphics()
   {
      m_puistrcontext         = NULL;
      m_pdrawcontext          = NULL;
      m_pdibAlphaBlend        = NULL;
      m_pjob                  = NULL;
      m_crColor               = RGB(0, 0, 0);
      m_dFontFactor           = 1.0;
   }

   ::user::str_context * graphics::str_context()
   {
      return m_puistrcontext;
   }

   ::user::draw_context * graphics::draw_context()
   {
      return m_pdrawcontext;
   }

   bool graphics::is_set()
   {
      return get_os_data() != 0;
   }

   void *  graphics::get_os_data() const
   {
      throw interface_only_exception(get_app());
      return 0;
   }
   /*

   /*
#ifdef WINDOWS

   bool graphics::attach(HDC hdc)
   {
      throw interface_only_exception(get_app());
   }

   HDC graphics::detach()
   {
      throw interface_only_exception(get_app());
   }

#endif

   */

   bool graphics::attach(simple_graphics & g)
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::attach(void * pdata)
   {
      throw interface_only_exception(get_app());
   }

   void * graphics::detach()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::IsPrinting() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::CreateDC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      throw interface_only_exception(get_app());
   }

   bool graphics::CreateIC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      throw interface_only_exception(get_app());
   }

   bool graphics::CreateCompatibleDC(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::ExcludeUpdateRgn(::ca::window* pWnd)
   {
      UNREFERENCED_PARAMETER(pWnd);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetDeviceCaps(int32_t nIndex) const
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());
   }

   point graphics::GetBrushOrg() const
   {
      throw interface_only_exception(get_app());
   }

   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   point graphics::SetBrushOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      UNREFERENCED_PARAMETER(nObjectType);
      UNREFERENCED_PARAMETER(lpfn);
      UNREFERENCED_PARAMETER(lpData);
      throw interface_only_exception(get_app());
   }

   ::ca::bitmap* graphics::SelectObject(::ca::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception(get_app());
   }

   ::ca::graphics_object* graphics::SelectObject(::ca::graphics_object* pObject)
   {
      UNREFERENCED_PARAMETER(pObject);
      throw interface_only_exception(get_app());
   }

/*   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
   {
      UNREFERENCED_PARAMETER(hObject);
      throw interface_only_exception(get_app());
   }*/


   bool graphics::SelectFont(::ca::font * pfont)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_fontxyz = *pfont;

      m_fontxyz.m_dFontSize *= m_dFontFactor;

      return true;
   }

   bool graphics::selectFont(::ca::font * pfont)
   {
      return SelectFont(pfont);
   }

   bool graphics::select_font(::ca::font * pfont)
   {
      return selectFont(pfont);
   }

   bool graphics::SetFont(::ca::font * pfont)
   {
      return select_font(pfont);
   }

   bool graphics::setFont(::ca::font * pfont)
   {
      return SetFont(pfont);
   }

   bool graphics::set_font(::ca::font * pfont)
   {
      return setFont(pfont);
   }

   COLORREF graphics::GetNearestColor(COLORREF crColor) const
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   UINT graphics::RealizePalette()
   {
      throw interface_only_exception(get_app());
   }

   void graphics::UpdateColors()
   {
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::GetBkColor() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetBkMode() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetPolyFillMode() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetROP2() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetStretchBltMode() const
   {
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::GetTextColor() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetMapMode() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetGraphicsMode() const
   {
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {
      UNREFERENCED_PARAMETER(pXform);
      throw interface_only_exception(get_app());
   }

#endif

   point graphics::GetViewportOrg() const
   {
      throw interface_only_exception(get_app());
   }

   size graphics::GetViewportExt() const
   {
      throw interface_only_exception(get_app());
   }

   point graphics::GetWindowOrg() const
   {
      throw interface_only_exception(get_app());
   }

   size graphics::GetWindowExt() const
   {
      throw interface_only_exception(get_app());
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   size graphics::SetViewportExt(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
   }

   point graphics::SetWindowOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   size graphics::SetWindowExt(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
   }

   void graphics::DPtoLP(LPPOINT lpPoints, int32_t nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   void graphics::DPtoLP(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   void graphics::LPtoDP(LPPOINT lpPoints, int32_t nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   void graphics::LPtoDP(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::FillRgn(::ca::region* pRgn, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

   bool graphics::FrameRgn(::ca::region* pRgn, ::ca::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   bool graphics::InvertRgn(::ca::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   bool graphics::PaintRgn(::ca::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   bool graphics::PtVisible(int32_t x, int32_t y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   bool graphics::PtVisible(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   bool graphics::RectVisible(LPCRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   point graphics::GetCurrentPosition() const
   {
      throw interface_only_exception(get_app());
   }

   point graphics::MoveTo(POINT point)
   {

      pointd pointd = MoveTo((double)point.x, (double)point.y);

      return ::point((int64_t) pointd.x, (int64_t) pointd.y);

   }

   bool graphics::LineTo(POINT point)
   {
      return LineTo(double(point.x), double(point.y));
   }

   bool graphics::Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception(get_app());
   }

   bool graphics::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
   }


   bool graphics::Arc(int32_t x1, int32_t y1, int32_t w, int32_t h, double start, double extends)
   {

      point ptCenter;

      ptCenter.x = (x1 + w) / 2;
      ptCenter.y = (y1 + h) / 2;

      double dx = max(2.0, (w) / 2.0);
      double dy = max(2.0, (h) / 2.0);

      double startx = (cos(start) * dx) + ptCenter.x;
      double starty = (cos(start) * dy) + ptCenter.x;

      double endx = (cos(start + extends) * dx) + ptCenter.x;
      double endy = (cos(start + extends) * dy) + ptCenter.x;

      return Arc(x1, y1, x1 + w, y1 + h, (int32_t) startx, (int32_t) starty, (int32_t) endx, (int32_t) endy);

   }

   bool graphics::Arc(LPCRECT lpRect, double start, double extends)
   {
      return Arc(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, start, extends);
   }

   bool graphics::Polyline(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   void graphics::FillRect(LPCRECT lpRect, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

   void graphics::FrameRect(LPCRECT lpRect, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

   void graphics::InvertRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(picon);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(picon);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(picon);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(istepIfAniCur);
      UNREFERENCED_PARAMETER(hbrFlickerFreeDraw);
      UNREFERENCED_PARAMETER(diFlags);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawState(point pt, size size, ::ca::bitmap* pBitmap, UINT nFlags, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(pBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

#endif

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

#endif

   bool graphics::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nEdge);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nType);
      UNREFERENCED_PARAMETER(nState);
      throw interface_only_exception(get_app());
   }

   bool graphics::Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception(get_app());
   }

   bool graphics::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
   }

   void graphics::DrawFocusRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::Ellipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      bool bFill = FillEllipse(x1, y1, x2, y2);

      bool bDraw = DrawEllipse(x1, y1, x2, y2);

      return bFill && bDraw;

   }

   bool graphics::Ellipse(LPCRECT lpRect)
   {

      bool bFill = FillEllipse(lpRect);

      bool bDraw = DrawEllipse(lpRect);

      return bFill && bDraw;

   }


   bool graphics::DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawEllipse(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   bool graphics::FillEllipse(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception(get_app());
   }

   bool graphics::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
   }

   bool graphics::fill_polygon(const POINTD * lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::fill_polygon(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::Polygon(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyCounts);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::Polygon(point_array & pta)
   {
      return Polygon(pta.get_data(), (int32_t) pta.get_count());
   }

   bool graphics::Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   bool graphics::Rectangle(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   bool graphics::DrawRectangle(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   bool graphics::FillRectangle(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   bool graphics::RoundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      throw interface_only_exception(get_app());
   }

   bool graphics::RoundRect(LPCRECT lpRect, POINT point)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception(get_app());
   }

   bool graphics::BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception(get_app());
   }

   bool graphics::StretchBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nSrcWidth);
      UNREFERENCED_PARAMETER(nSrcHeight);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::GetPixel(int32_t x, int32_t y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::GetPixel(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      UNREFERENCED_PARAMETER(nFillType);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(int32_t x, int32_t y, const string & str)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(double x, double y, const char * lpszString, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(double x, double y, const string & str)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }


   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception(get_app());
   }

   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect, const string & str, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception(get_app());
   }

   size graphics::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);
      throw interface_only_exception(get_app());
   }

   size graphics::TabbedTextOut(int32_t x, int32_t y, const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   size graphics::GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   bool graphics::GrayString(::ca::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(lpfnOutput);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   UINT graphics::GetTextAlign() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetTextFace(int32_t nCount, LPTSTR lpszFacename) const
   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszFacename);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetTextFace(string & rString) const
   {
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception(get_app());
   }

   bool graphics::get_text_metrics(LPTEXTMETRIC lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception(get_app());
   }

   bool graphics::get_output_text_metrics(LPTEXTMETRIC lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetTextCharacterExtra() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception(get_app());
   }

   uint32_t graphics::GetFontLanguageInfo() const
   {
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   uint32_t graphics::GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   uint32_t graphics::GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

#endif

   size graphics::GetAspectRatioFilter() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::ScrollDC(int32_t dx, int32_t dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::ca::region * pRgnUpdate, LPRECT lpRectUpdate)
   {
      UNREFERENCED_PARAMETER(dx);
      UNREFERENCED_PARAMETER(dy);
      UNREFERENCED_PARAMETER(lpRectScroll);
      UNREFERENCED_PARAMETER(lpRectClip);
      UNREFERENCED_PARAMETER(pRgnUpdate);
      UNREFERENCED_PARAMETER(lpRectUpdate);
      throw interface_only_exception(get_app());
   }

   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszInData);
      UNREFERENCED_PARAMETER(lpOutData);
      throw interface_only_exception(get_app());
   }

   // ::ca::graphics_sp 3.1 Specific functions
   UINT graphics::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception(get_app());
   }

   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception(get_app());
   }

#if !defined(LINUX) && !defined(MACOS)

   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      UNREFERENCED_PARAMETER(lpDevMode);
      throw interface_only_exception(get_app());
   }

#endif


#ifdef WINDOWSEX

   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
   {
      UNREFERENCED_PARAMETER(cbData);
      UNREFERENCED_PARAMETER(lpotm);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpabc);
      throw interface_only_exception(get_app());
   }

#endif

   uint32_t graphics::GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData,  uint32_t cbData) const
   {
      UNREFERENCED_PARAMETER(dwTable);
      UNREFERENCED_PARAMETER(dwOffset);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(cbData);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   int32_t graphics::GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const
   {
      UNREFERENCED_PARAMETER(nPairs);
      UNREFERENCED_PARAMETER(lpkrnpair);
      throw interface_only_exception(get_app());
   }

   uint32_t graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,  uint32_t cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   {
      UNREFERENCED_PARAMETER(nChar);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpgm);
      UNREFERENCED_PARAMETER(cbBuffer);
      UNREFERENCED_PARAMETER(lpBuffer);
      UNREFERENCED_PARAMETER(lpmat2);
      throw interface_only_exception(get_app());
   }

   // ::userbase::document handling functions
   int32_t graphics::StartDoc(LPDOCINFO lpDocInfo)
   {
      UNREFERENCED_PARAMETER(lpDocInfo);
      throw interface_only_exception(get_app());
   }

#endif

   int32_t graphics::StartPage()
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::EndPage()
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {
      UNREFERENCED_PARAMETER(lpfn);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::AbortDoc()
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::EndDoc()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc,
      int32_t xSrc, int32_t ySrc, ::ca::bitmap& maskBitmap, int32_t xMask, int32_t yMask, uint32_t dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(maskBitmap);
      UNREFERENCED_PARAMETER(xMask);
      UNREFERENCED_PARAMETER(yMask);
      UNREFERENCED_PARAMETER(dwRop);

      throw interface_only_exception(get_app());
   }
   bool graphics::PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
      int32_t nWidth, int32_t nHeight, ::ca::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
   {
      UNREFERENCED_PARAMETER(lpPoint);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(maskBitmap);
      UNREFERENCED_PARAMETER(xMask);
      UNREFERENCED_PARAMETER(yMask);
      UNREFERENCED_PARAMETER(ySrc);
      throw interface_only_exception(get_app());
   }

   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nRadius);
      UNREFERENCED_PARAMETER(fStartAngle);
      UNREFERENCED_PARAMETER(fSweepAngle);
      throw interface_only_exception(get_app());
   }

   bool graphics::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetArcDirection() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyPolyline(const POINT* lpPoints, const uint32_t* lpPolyPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {
      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception(get_app());
   }

#endif

   ::ca::pen & graphics::GetCurrentPen() const
   {
      throw interface_only_exception(get_app());
   }

   ::ca::brush & graphics::GetCurrentBrush() const
   {
      throw interface_only_exception(get_app());
   }

   ::ca::palette & graphics::GetCurrentPalette() const
   {
      throw interface_only_exception(get_app());
   }

   ::ca::font & graphics::GetCurrentFont() const
   {
      throw interface_only_exception(get_app());
   }

   ::ca::bitmap & graphics::GetCurrentBitmap() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyBezier(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData, int32_t nOutputSize, char * lpszOutputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      UNREFERENCED_PARAMETER(nOutputSize);
      UNREFERENCED_PARAMETER(lpszOutputData);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpABCF);
      throw interface_only_exception(get_app());
   }

#endif

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float * lpFloatBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpFloatBuffer);
      throw interface_only_exception(get_app());
   }

   bool graphics::AbortPath()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::BeginPath()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::CloseFigure()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::EndPath()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::FillPath()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::FlattenPath()
   {
      throw interface_only_exception(get_app());
   }

   float graphics::GetMiterLimit() const
   {
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {
      UNREFERENCED_PARAMETER(fMiterLimit);
      throw interface_only_exception(get_app());
   }

   bool graphics::StrokeAndFillPath()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::StrokePath()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::WidenPath()
   {
      throw interface_only_exception(get_app());
   }


   bool graphics::draw_path(::ca::graphics_path * ppath)
   {

      throw interface_only_exception(get_app());

   }


   bool graphics::fill_path(::ca::graphics_path * ppath)
   {

      throw interface_only_exception(get_app());

   }

   bool graphics::path(::ca::graphics_path * ppath)
   {

      bool bOk1 = fill_path(ppath);

      bool bOk2 = draw_path(ppath);

      return bOk1 && bOk2;

   }


   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {
      UNREFERENCED_PARAMETER(nDataSize);
      UNREFERENCED_PARAMETER(pCommentData);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, LPCRECT lpBounds)
   {
      UNREFERENCED_PARAMETER(hEnhMF);
      UNREFERENCED_PARAMETER(lpBounds);
      throw interface_only_exception(get_app());
   }

#endif

   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
      ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
   {
      UNREFERENCED_PARAMETER(xDest);
      UNREFERENCED_PARAMETER(yDest);
      UNREFERENCED_PARAMETER(nDestWidth);
      UNREFERENCED_PARAMETER(nDestHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nSrcWidth);
      UNREFERENCED_PARAMETER(nSrcHeight);
      UNREFERENCED_PARAMETER(crTransparent);
      throw interface_only_exception(get_app());
   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, uint32_t dwMode)
   {
      UNREFERENCED_PARAMETER(pVertices);
      UNREFERENCED_PARAMETER(nVertices);
      UNREFERENCED_PARAMETER(pMesh);
      UNREFERENCED_PARAMETER(nMeshElements);
      UNREFERENCED_PARAMETER(dwMode);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   COLORREF graphics::GetDCBrushColor() const
   {
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::GetDCPenColor() const
   {
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

#ifndef METROWIN

   bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpabc);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception(get_app());
   }

#endif

   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpnFit);
      UNREFERENCED_PARAMETER(alpDx);
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

#endif

   void graphics::DPtoHIMETRIC(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   void graphics::HIMETRICtoLP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   ::ca::brush * graphics::GetHalftoneBrush()
   {
      throw interface_only_exception(get_app());
   }

   // top of windows implementation

   void graphics::DrawDragRect(LPCRECT lpRect, SIZE size, LPCRECT lpRectLast, SIZE sizeLast, ::ca::brush* pBrush, ::ca::brush* pBrushLast)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpRectLast);
      UNREFERENCED_PARAMETER(sizeLast);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(pBrushLast);
      throw interface_only_exception(get_app());
   }

   void graphics::FillSolidRect(LPCRECT lpRect, COLORREF clr)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(clr);
      throw interface_only_exception(get_app());
   }

   void graphics::FillSolidRect(const __rect64 * lpRect, COLORREF clr)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(clr);
      throw interface_only_exception(get_app());
   }

   void graphics::FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(clr);
      throw interface_only_exception(get_app());
   }

   void graphics::Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(clrTopLeft);
      UNREFERENCED_PARAMETER(clrBottomRight);
      throw interface_only_exception(get_app());
   }

   void graphics::Draw3dRect(int32_t x, int32_t y, int32_t cx, int32_t cy,  COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(clrTopLeft);
      UNREFERENCED_PARAMETER(clrBottomRight);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::ca::graphics_sp

   void graphics::assert_valid() const
   {
      throw interface_only_exception(get_app());
   }

   void graphics::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception(get_app());
   }




   bool graphics::DeleteDC()
   {
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int32_t graphics::StartDoc(const char * lpszDocName)
   {
      UNREFERENCED_PARAMETER(lpszDocName);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SaveDC()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::RestoreDC(int32_t nSavedDC)
   {
      UNREFERENCED_PARAMETER(nSavedDC);
      throw interface_only_exception(get_app());
   }

   ::ca::graphics_object* graphics::SelectStockObject(int32_t nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());
   }

   ::ca::pen* graphics::SelectObject(::ca::pen * pPen)
   {
      UNREFERENCED_PARAMETER(pPen);
      throw interface_only_exception(get_app());
   }

   ::ca::brush* graphics::SelectObject(::ca::brush * pBrush)
   {
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

   ::ca::font* graphics::SelectObject(::ca::font * pFont)
   {
      UNREFERENCED_PARAMETER(pFont);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SelectObject(::ca::region * pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   ::ca::palette* graphics::SelectPalette(::ca::palette * pPalette, bool bForceBackground)
   {
      UNREFERENCED_PARAMETER(pPalette);
      UNREFERENCED_PARAMETER(bForceBackground);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetBkColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetBkMode(int32_t nBkMode)
   {
      UNREFERENCED_PARAMETER(nBkMode);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {
      UNREFERENCED_PARAMETER(nPolyFillMode);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetROP2(int32_t nDrawMode)
   {
      UNREFERENCED_PARAMETER(nDrawMode);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {
      UNREFERENCED_PARAMETER(nStretchMode);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetTextColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {
      UNREFERENCED_PARAMETER(pXform);
      throw interface_only_exception(get_app());
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform, uint32_t iMode)
   {
      UNREFERENCED_PARAMETER(pXform);
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception(get_app());
   }

#endif

   int32_t graphics::SetMapMode(int32_t nMapMode)
   {
      UNREFERENCED_PARAMETER(nMapMode);
      throw interface_only_exception(get_app());
   }

   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   size graphics::SetViewportExt(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   size graphics::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception(get_app());
   }

   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   size graphics::SetWindowExt(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetClipBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::GetClipBox(rect64 * lpRect) const
   {
      rect rect;
      int32_t iClip = GetClipBox(rect);
      rect64 rect64(rect);
      *lpRect = rect64;
      return iClip;
   }

   int32_t graphics::SelectClipRgn(::ca::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::ExcludeClipRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::IntersectClipRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::OffsetClipRgn(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
   }

   point graphics::MoveTo(int32_t x, int32_t y)
   {
      pointd pointd = MoveTo((double) x, (double) y);
      return point((LONG) pointd.x, (LONG) pointd.y);
   }

   bool graphics::LineTo(int32_t x, int32_t y)
   {
      return LineTo((double) x, (double) y);
   }

   bool graphics::LineTo(double x, double y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {
      UNREFERENCED_PARAMETER(nBreakExtra);
      UNREFERENCED_PARAMETER(nBreakCount);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {
      UNREFERENCED_PARAMETER(nCharExtra);
      throw interface_only_exception(get_app());
   }

   uint32_t graphics::SetMapperFlags(uint32_t dwFlag)
   {
      UNREFERENCED_PARAMETER(dwFlag);
      throw interface_only_exception(get_app());
   }

   uint32_t graphics::GetLayout() const
   {
      throw interface_only_exception(get_app());
   }

   uint32_t graphics::SetLayout(uint32_t dwSetLayout)
   {
      UNREFERENCED_PARAMETER(dwSetLayout);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {
      UNREFERENCED_PARAMETER(nArcDirection);
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::PolylineTo(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }


#ifdef WINDOWSEX


   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {

      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception(get_app());

   }


#endif


   bool graphics::PolyBezierTo(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::SelectClipPath(int32_t nMode)
   {
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::SelectClipRgn(::ca::region* pRgn, int32_t nMode)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      UNREFERENCED_PARAMETER(hMF);
      throw interface_only_exception(get_app());
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   void graphics::DPtoLP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTextExtent(const char * lpszString, strsize nCount, int32_t iIndex) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(iIndex);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTextExtent(const char * lpszString, strsize nCount) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTextExtent(const string & str) const
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex) const
   {
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(iIndex);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount) const
   {
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetTextExtent(sized & size, const string & str) const
   {
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   size graphics::GetOutputTextExtent(const string & str) const
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::draw_text(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::draw_text(const string & str, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception(get_app());
   }

#ifndef METROWIN

   int32_t graphics::draw_text_ex(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
   }

   int32_t graphics::draw_text_ex(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
   }


#endif


   bool graphics::from(point ptDst, size size, ::ca::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop)
   {
      return BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, dwRop) != FALSE;
   }

   bool graphics::from(size size, ::ca::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop)
   {
      return from(null_point(), size, pgraphicsSrc, ptSrc, dwRop);
   }

   bool graphics::from(size size, ::ca::graphics * pgraphicsSrc, uint32_t dwRop)
   {
      return from(size, pgraphicsSrc, null_point(), dwRop);
   }

   bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dOpacity)
   {
      UNREFERENCED_PARAMETER(xDest);
      UNREFERENCED_PARAMETER(yDest);
      UNREFERENCED_PARAMETER(nDestWidth);
      UNREFERENCED_PARAMETER(nDestHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nSrcWidth);
      UNREFERENCED_PARAMETER(nSrcHeight);
      UNREFERENCED_PARAMETER(dOpacity);
      throw interface_only_exception(get_app());
   }

   bool graphics::alpha_blend(point ptDst, size szDst,::ca::graphics * pgraphicsSrc, point ptSrc, size szSrc, double dOpacity)
   {
      return alpha_blend(ptDst.x, ptDst.y, szDst.cx, szDst.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, szSrc.cx, szSrc.cy, dOpacity);
   }

   bool graphics::alpha_blend(point ptDst, size size,::ca::graphics * pgraphicsSrc, point ptSrc, double dOpacity)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, ptSrc, size, dOpacity);
   }

   bool graphics::alpha_blend(point ptDst, size size,::ca::graphics * pgraphicsSrc, double dOpacity)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, null_point(), dOpacity);
   }

   bool graphics::alpha_blend(size size,::ca::graphics * pgraphicsSrc, point ptSrc, double dOpacity)
   {
      return alpha_blend(null_point(), size, pgraphicsSrc, ptSrc, dOpacity);
   }

   bool graphics::alpha_blend(size size,::ca::graphics * pgraphicsSrc, double dOpacity)
   {
      return alpha_blend(size, pgraphicsSrc, null_point(), dOpacity);
   }


/*
   bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
      ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, BLENDFUNCTION blend)
   {
      UNREFERENCED_PARAMETER(xDest);
      UNREFERENCED_PARAMETER(yDest);
      UNREFERENCED_PARAMETER(nDestWidth);
      UNREFERENCED_PARAMETER(nDestHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nSrcWidth);
      UNREFERENCED_PARAMETER(nSrcHeight);
      UNREFERENCED_PARAMETER(blend);
      throw interface_only_exception(get_app());
   }*/

/*   bool graphics::alpha_blend(point ptDst, size szDst,::ca::graphics * pgraphicsSrc, point ptSrc, size szSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(ptDst.x, ptDst.y, szDst.cx, szDst.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, szSrc.cx, szSrc.cy, blend);
   }

   bool graphics::alpha_blend(point ptDst, size size,::ca::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, ptSrc, size, blend);
   }

   bool graphics::alpha_blend(point ptDst, size size,::ca::graphics * pgraphicsSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, null_point(),blend);
   }

   bool graphics::alpha_blend(size size,::ca::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(null_point(), size, pgraphicsSrc, ptSrc, blend);
   }

   bool graphics::alpha_blend(size size,::ca::graphics * pgraphicsSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(size, pgraphicsSrc, null_point(), blend);
   }*/

   void graphics::set_alpha_mode(e_alpha_mode ealphamode)
   {
      m_ealphamode = ealphamode;
   }

   void graphics::set_text_rendering(e_text_rendering etextrendering)
   {
      throw not_implemented(get_app());
   }

   bool graphics::blur(bool bExpand, double dRadius, LPCRECT lpcrect)
   {
      throw interface_only_exception(get_app());
   }


   COLORREF graphics::SetColor(COLORREF crColor)
   {

      m_crColor               = crColor;

      m_penxyz.m_cr           = crColor;
      m_penxyz.m_bUpdated     = false;

      m_brushxyz.m_cr         = crColor;
      m_brushxyz.m_etype      = ::ca::brush::type_solid;
      m_brushxyz.m_bUpdated   = false;


      return TRUE;

   }

   COLORREF graphics::setColor(COLORREF crColor)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return SetColor(crColor);
   }

   COLORREF graphics::set_color(COLORREF crColor)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return setColor(crColor);
   }

   point graphics::DrawLine(float x1, float y1, float x2, float y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      MoveTo(x1, y1);
      return LineTo(x2, y2);

   }

   point graphics::drawLine(float x1, float y1, float x2, float y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2);

   }

   point graphics::draw_line(float x1, float y1, float x2, float y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2);

   }



   point graphics::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      MoveTo(x1, y1);
      return LineTo(x2, y2);

   }

   point graphics::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2);

   }

   point graphics::draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2);

   }

   bool graphics::DrawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      Draw3dRect(x1, y1, x2, y2, m_crColor, m_crColor);

      return TRUE;

   }

   bool graphics::drawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawRect(x1, y1, x2, y2);

   }

   bool graphics::draw_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawRect(x1, y1, x2, y2);

   }

   pointd graphics::MoveTo(double x, double y)
   {
      double px = m_x;
      double py = m_y;
      m_x = x;
      m_y = y;
      return pointd(px, py);
   }


   void graphics::set_solid_pen(double dWidth)
   {

      m_penxyz.create_solid(this, dWidth, m_crColor);

   }

   memory_graphics::memory_graphics(::ca::application * papp) :
      ::ca::graphics_sp(papp)
   {
      ::ca::graphics_sp::m_p->CreateCompatibleDC(NULL);
   }

   memory_graphics::~memory_graphics()
   {

   }

   client_graphics::client_graphics(::user::interaction * pui)
   {
      m_pui = pui;
      ::ca::graphics_sp::operator = (pui->GetDC());
   }

   client_graphics::~client_graphics()
   {
      m_pui->ReleaseDC(m_p);
   }

   window_graphics::window_graphics(::ca::window * pwindow)
   {
      m_pwindow = pwindow;
      create(pwindow->get_app());
      m_p->attach(pwindow->GetWindowDC());
   }

   window_graphics::~window_graphics()
   {
      m_pwindow->ReleaseDC(m_p);
   }

   paint_graphics::paint_graphics(::ca::window * pwindow)
   {
      m_pwindow = pwindow;
      create(pwindow->get_app());
#ifdef WINDOWSEX
      m_p->attach(::BeginPaint(pwindow->get_safe_handle(), &m_ps));
#else
      throw todo(get_app());
#endif
   }

   paint_graphics::~paint_graphics()
   {
#ifdef WINDOWSEX
      ::EndPaint(m_pwindow->get_safe_handle(), &m_ps);
#else
      throw todo(get_app());
#endif
   }


   double graphics::get_dpix() const
   {
      return 96.0;
   }

   bool graphics::flush()
   {
      throw interface_only_exception(get_app());
      return false;
   }



} // namespace ca


dump_context & operator<<(dump_context & dumpcontext, SIZE size)
{
   return dumpcontext << "(" << size.cx << " x " << size.cy << ")";
}

dump_context & operator<<(dump_context & dumpcontext, POINT point)
{
   return dumpcontext << "(" << point.x << ", " << point.y << ")";
}

dump_context & operator<<(dump_context & dumpcontext, const RECT& rect)
{
   return dumpcontext << "(L " << rect.left << ", T " << rect.top << ", R " <<
      rect.right << ", B " << rect.bottom << ")";
}
