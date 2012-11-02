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

#ifdef WINDOWS

   bool graphics::Attach(HDC hdc)
   {
      throw interface_only_exception(get_app());
   }

   HDC graphics::Detach()
   {
      throw interface_only_exception(get_app());
   }

#endif

   void graphics::attach(void * pdata)
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

   int graphics::ExcludeUpdateRgn(::ca::window* pWnd)
   {
      UNREFERENCED_PARAMETER(pWnd);
      throw interface_only_exception(get_app());
   }

   int graphics::GetDeviceCaps(int nIndex) const
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());
   }

   point graphics::GetBrushOrg() const
   {
      throw interface_only_exception(get_app());
   }

   point graphics::SetBrushOrg(int x, int y)
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

   int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
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

   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
   {
      UNREFERENCED_PARAMETER(hObject);
      throw interface_only_exception(get_app());
   }


   bool graphics::SelectFont(::ca::font * pfont)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_fontxyz = *pfont;

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

   int graphics::GetBkMode() const
   {
      throw interface_only_exception(get_app());
   }

   int graphics::GetPolyFillMode() const
   {
      throw interface_only_exception(get_app());
   }

   int graphics::GetROP2() const
   {
      throw interface_only_exception(get_app());
   }

   int graphics::GetStretchBltMode() const
   {
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::GetTextColor() const
   {
      throw interface_only_exception(get_app());
   }

   int graphics::GetMapMode() const
   {
      throw interface_only_exception(get_app());
   }

   int graphics::GetGraphicsMode() const
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

   void graphics::DPtoLP(LPPOINT lpPoints, int nCount) const
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

   void graphics::LPtoDP(LPPOINT lpPoints, int nCount) const
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

   bool graphics::FrameRgn(::ca::region* pRgn, ::ca::brush* pBrush, int nWidth, int nHeight)
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

   bool graphics::PtVisible(int x, int y) const
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

      return ::point(pointd.x, pointd.y);

   }

   bool graphics::LineTo(POINT point)
   {
      return LineTo(double(point.x), double(point.y));
   }

   bool graphics::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
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


   bool graphics::Arc(int x1, int y1, int x2, int y2, double start, double extends)
   {

      point ptCenter;

      ptCenter.x = (x2 + x1) / 2;
      ptCenter.y = (y2 + y1) / 2;

      double dx = max(2.0, (x2 - x1) / 2.0);
      double dy = max(2.0, (y2 - y1) / 2.0);

      int startx = (int) (cos(start) * dx) + ptCenter.x;
      int starty = (int) (cos(start) * dy) + ptCenter.x;

      int endx = (int) (cos(start + extends) * dx) + ptCenter.x;
      int endy = (int) (cos(start + extends) * dy) + ptCenter.x;

      return Arc(x1, y1, x2, y2, startx, starty, endx, endy);

   }

   bool graphics::Arc(LPCRECT lpRect, double start, double extends)
   {
      return Arc(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, start, extends);
   }

   bool graphics::Polyline(const POINT* lpPoints, int nCount)
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

   bool graphics::DrawIcon(int x, int y, ::visual::icon * picon)
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

   bool graphics::DrawIcon(int x, int y, ::visual::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
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

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int nTextLen, HBRUSH hBrush)
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

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int nTextLen, ::ca::brush* pBrush)
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

   bool graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
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

   bool graphics::Ellipse(int x1, int y1, int x2, int y2)
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


   bool graphics::DrawEllipse(int x1, int y1, int x2, int y2)
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

   bool graphics::FillEllipse(int x1, int y1, int x2, int y2)
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

   bool graphics::Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
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

   bool graphics::fill_polygon(const POINTD * lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::fill_polygon(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::Polygon(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyCounts);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::Polygon(point_array & pta)
   {
      return Polygon(pta.get_data(), (int) pta.get_count());
   }

   bool graphics::Rectangle(int x1, int y1, int x2, int y2)
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

   bool graphics::DrawRectangle(int x1, int y1, int x2, int y2)
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

   bool graphics::FillRectangle(int x1, int y1, int x2, int y2)
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

   bool graphics::RoundRect(int x1, int y1, int x2, int y2, int x3, int y3)
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

   bool graphics::PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception(get_app());
   }

   bool graphics::BitBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, DWORD dwRop)
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

   bool graphics::StretchBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
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

   COLORREF graphics::GetPixel(int x, int y) const
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

   COLORREF graphics::SetPixel(int x, int y, COLORREF crColor)
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

   bool graphics::FloodFill(int x, int y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   bool graphics::ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      UNREFERENCED_PARAMETER(nFillType);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(int x, int y, const char * lpszString, int nCount)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(int x, int y, const string & str)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   bool graphics::TextOut(double x, double y, const char * lpszString, int nCount)
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


   bool graphics::ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
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

   bool graphics::ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect, const string & str, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception(get_app());
   }

   size graphics::TabbedTextOut(int x, int y, const char * lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
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

   size graphics::TabbedTextOut(int x, int y, const string & str, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   size graphics::GetTabbedTextExtent(const string & str, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   size graphics::GetOutputTabbedTextExtent(const string & str, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
   }

   bool graphics::GrayString(::ca::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight)
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

   int graphics::GetTextFace(int nCount, LPTSTR lpszFacename) const
   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszFacename);
      throw interface_only_exception(get_app());
   }

   int graphics::GetTextFace(string & rString) const
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

   int graphics::GetTextCharacterExtra() const
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

   DWORD graphics::GetFontLanguageInfo() const
   {
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   DWORD graphics::GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   DWORD graphics::GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
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

   bool graphics::ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::ca::region * pRgnUpdate, LPRECT lpRectUpdate)
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
   int graphics::Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData)
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

#ifdef WINDOWS

   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      UNREFERENCED_PARAMETER(lpDevMode);
      throw interface_only_exception(get_app());
   }

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

   DWORD graphics::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData,  DWORD cbData) const
   {
      UNREFERENCED_PARAMETER(dwTable);
      UNREFERENCED_PARAMETER(dwOffset);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(cbData);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   int graphics::GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const
   {
      UNREFERENCED_PARAMETER(nPairs);
      UNREFERENCED_PARAMETER(lpkrnpair);
      throw interface_only_exception(get_app());
   }

   DWORD graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,  DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
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
   int graphics::StartDoc(LPDOCINFO lpDocInfo)
   {
      UNREFERENCED_PARAMETER(lpDocInfo);
      throw interface_only_exception(get_app());
   }

#endif

   int graphics::StartPage()
   {
      throw interface_only_exception(get_app());
   }

   int graphics::EndPage()
   {
      throw interface_only_exception(get_app());
   }

   int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
   {
      UNREFERENCED_PARAMETER(lpfn);
      throw interface_only_exception(get_app());
   }

   int graphics::AbortDoc()
   {
      throw interface_only_exception(get_app());
   }

   int graphics::EndDoc()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::MaskBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
      int xSrc, int ySrc, ::ca::bitmap& maskBitmap, int xMask, int yMask, DWORD dwRop)
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
   bool graphics::PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc,
      int nWidth, int nHeight, ::ca::bitmap& maskBitmap, int xMask, int yMask)
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

   bool graphics::SetPixelV(int x, int y, COLORREF crColor)
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

   bool graphics::AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
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

   int graphics::GetArcDirection() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

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

   bool graphics::PolyBezier(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   int graphics::DrawEscape(int nEscape, int nInputSize, const char * lpszInputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      throw interface_only_exception(get_app());
   }

   int graphics::Escape(int nEscape, int nInputSize, const char * lpszInputData, int nOutputSize, char * lpszOutputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      UNREFERENCED_PARAMETER(nOutputSize);
      UNREFERENCED_PARAMETER(lpszOutputData);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

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

   int graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const
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

   bool graphics::TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
      ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, UINT crTransparent)
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

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, DWORD dwMode)
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

   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpnFit);
      UNREFERENCED_PARAMETER(alpDx);
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
   }

   bool graphics::GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE lpSize) const
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

   void graphics::FillSolidRect(int x, int y, int cx, int cy, COLORREF clr)
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

   void graphics::Draw3dRect(int x, int y, int cx, int cy,  COLORREF clrTopLeft, COLORREF clrBottomRight)
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

   int graphics::StartDoc(const char * lpszDocName)
   {
      UNREFERENCED_PARAMETER(lpszDocName);
      throw interface_only_exception(get_app());
   }

   int graphics::SaveDC()
   {
      throw interface_only_exception(get_app());
   }

   bool graphics::RestoreDC(int nSavedDC)
   {
      UNREFERENCED_PARAMETER(nSavedDC);
      throw interface_only_exception(get_app());
   }

   ::ca::graphics_object* graphics::SelectStockObject(int nIndex)
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

   int graphics::SelectObject(::ca::region * pRgn)
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

   int graphics::SetBkMode(int nBkMode)
   {
      UNREFERENCED_PARAMETER(nBkMode);
      throw interface_only_exception(get_app());
   }

   int graphics::SetPolyFillMode(int nPolyFillMode)
   {
      UNREFERENCED_PARAMETER(nPolyFillMode);
      throw interface_only_exception(get_app());
   }

   int graphics::SetROP2(int nDrawMode)
   {
      UNREFERENCED_PARAMETER(nDrawMode);
      throw interface_only_exception(get_app());
   }

   int graphics::SetStretchBltMode(int nStretchMode)
   {
      UNREFERENCED_PARAMETER(nStretchMode);
      throw interface_only_exception(get_app());
   }

   COLORREF graphics::SetTextColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
   }

   int graphics::SetGraphicsMode(int iMode)
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

   bool graphics::ModifyWorldTransform(const XFORM* pXform, DWORD iMode)
   {
      UNREFERENCED_PARAMETER(pXform);
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception(get_app());
   }

#endif

   int graphics::SetMapMode(int nMapMode)
   {
      UNREFERENCED_PARAMETER(nMapMode);
      throw interface_only_exception(get_app());
   }

   point graphics::SetViewportOrg(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   point graphics::OffsetViewportOrg(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   size graphics::SetViewportExt(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   size graphics::ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception(get_app());
   }

   point graphics::SetWindowOrg(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   point graphics::OffsetWindowOrg(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
   }

   size graphics::SetWindowExt(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   size graphics::ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception(get_app());
   }

   int graphics::GetClipBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int graphics::GetClipBox(rect64 * lpRect) const
   {
      rect rect;
      int iClip = GetClipBox(rect);
      rect64 rect64(rect);
      *lpRect = rect64;
      return iClip;
   }

   int graphics::SelectClipRgn(::ca::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   int graphics::ExcludeClipRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int graphics::IntersectClipRect(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   int graphics::IntersectClipRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int graphics::OffsetClipRgn(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   int graphics::OffsetClipRgn(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
   }

   point graphics::MoveTo(int x, int y)
   {
      pointd pointd = MoveTo((double) x, (double) y);
      return point(pointd.x, pointd.y);
   }

   bool graphics::LineTo(int x, int y)
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

   int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   {
      UNREFERENCED_PARAMETER(nBreakExtra);
      UNREFERENCED_PARAMETER(nBreakCount);
      throw interface_only_exception(get_app());
   }

   int graphics::SetTextCharacterExtra(int nCharExtra)
   {
      UNREFERENCED_PARAMETER(nCharExtra);
      throw interface_only_exception(get_app());
   }

   DWORD graphics::SetMapperFlags(DWORD dwFlag)
   {
      UNREFERENCED_PARAMETER(dwFlag);
      throw interface_only_exception(get_app());
   }

   DWORD graphics::GetLayout() const
   {
      throw interface_only_exception(get_app());
   }

   DWORD graphics::SetLayout(DWORD dwSetLayout)
   {
      UNREFERENCED_PARAMETER(dwSetLayout);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
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

   int graphics::SetArcDirection(int nArcDirection)
   {
      UNREFERENCED_PARAMETER(nArcDirection);
      throw interface_only_exception(get_app());
   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::PolylineTo(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {
      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception(get_app());
   }

#endif

   bool graphics::PolyBezierTo(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
   }

   bool graphics::SelectClipPath(int nMode)
   {
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception(get_app());
   }

   int graphics::SelectClipRgn(::ca::region* pRgn, int nMode)
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

   size graphics::GetTextExtent(const char * lpszString, strsize nCount, int iIndex) const
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

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, int iIndex) const
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

   int graphics::draw_text(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception(get_app());
   }

   int graphics::draw_text(const string & str, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception(get_app());
   }

   int graphics::draw_text_ex(const char * lpszString, strsize nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
   }

   int graphics::draw_text_ex(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
   }

   bool graphics::from(point ptDst, size size, ::ca::graphics * pgraphicsSrc, point ptSrc, DWORD dwRop)
   {
      return BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, dwRop) != FALSE;
   }

   bool graphics::from(size size, ::ca::graphics * pgraphicsSrc, point ptSrc, DWORD dwRop)
   {
      return from(null_point(), size, pgraphicsSrc, ptSrc, dwRop);
   }

   bool graphics::from(size size, ::ca::graphics * pgraphicsSrc, DWORD dwRop)
   {
      return from(size, pgraphicsSrc, null_point(), dwRop);
   }

   bool graphics::alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dOpacity)
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
   bool graphics::alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
      ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, BLENDFUNCTION blend)
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



   point graphics::DrawLine(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      MoveTo(x1, y1);
      return LineTo(x2, y2);

   }

   point graphics::drawLine(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2);

   }

   point graphics::draw_line(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2);

   }

   bool graphics::DrawRect(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      Draw3dRect(x1, y1, x2, y2, m_crColor, m_crColor);

      return TRUE;

   }

   bool graphics::drawRect(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawRect(x1, y1, x2, y2);

   }

   bool graphics::draw_rect(int x1, int y1, int x2, int y2)
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

      m_penxyz.create_solid(dWidth, m_crColor);

   }



   client_graphics::client_graphics(::ca::window * pwindow)
   {
      m_pwindow = pwindow;
      create(pwindow->get_app());
      m_p->attach(pwindow->GetDC());
   }

   client_graphics::~client_graphics()
   {
      m_pwindow->ReleaseDC(m_p);
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
#ifdef WINDOWS
      m_p->attach(::BeginPaint((HWND) pwindow->get_safe_handle(), &m_ps));
#endif
   }

   paint_graphics::~paint_graphics()
   {
#ifdef WINDOWS
      ::EndPaint((HWND) m_pwindow->get_safe_handle(), &m_ps);
#endif
   }


   double graphics::get_dpix() const
   {
      return 96.0;
   }

} // namespace ca


dump_context& operator<<(dump_context & dumpcontext, SIZE size)
{
   return dumpcontext << "(" << size.cx << " x " << size.cy << ")";
}

dump_context& operator<<(dump_context & dumpcontext, POINT point)
{
   return dumpcontext << "(" << point.x << ", " << point.y << ")";
}

dump_context& operator<<(dump_context & dumpcontext, const RECT& rect)
{
   return dumpcontext << "(L " << rect.left << ", T " << rect.top << ", R " <<
      rect.right << ", B " << rect.bottom << ")";
}
