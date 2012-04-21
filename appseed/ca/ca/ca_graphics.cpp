#include "StdAfx.h"
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
      return get_os_data() != NULL;
   }

   void * graphics::get_os_data() const
   {
      throw interface_only_exception();
      return NULL;
   }

#ifdef WINDOWS

   BOOL graphics::Attach(HDC hdc)
   {
      throw interface_only_exception();
   }

   HDC graphics::Detach()
   {
      throw interface_only_exception();
   }

#endif

   void graphics::attach(void * pdata)
   {
      throw interface_only_exception();
   }

   BOOL graphics::IsPrinting() const
   {
      throw interface_only_exception();
   }

   BOOL graphics::CreateDC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      throw interface_only_exception();
   }

   BOOL graphics::CreateIC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      throw interface_only_exception();
   }

   BOOL graphics::CreateCompatibleDC(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();
   }

   int graphics::ExcludeUpdateRgn(::ca::window* pWnd)
   {
      UNREFERENCED_PARAMETER(pWnd);
      throw interface_only_exception();
   }

   int graphics::GetDeviceCaps(int nIndex) const
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception();
   }

   point graphics::GetBrushOrg() const
   {
      throw interface_only_exception();
   }

   point graphics::SetBrushOrg(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   point graphics::SetBrushOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();
   }

   int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      UNREFERENCED_PARAMETER(nObjectType);
      UNREFERENCED_PARAMETER(lpfn);
      UNREFERENCED_PARAMETER(lpData);
      throw interface_only_exception();
   }

   ::ca::bitmap* graphics::SelectObject(::ca::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception();
   }

   ::ca::graphics_object* graphics::SelectObject(::ca::graphics_object* pObject)
   {
      UNREFERENCED_PARAMETER(pObject);
      throw interface_only_exception();
   }

   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
   {
      UNREFERENCED_PARAMETER(hObject);
      throw interface_only_exception();
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
      throw interface_only_exception();
   }

   UINT graphics::RealizePalette()
   {
      throw interface_only_exception();
   }

   void graphics::UpdateColors()
   {
      throw interface_only_exception();
   }

   COLORREF graphics::GetBkColor() const
   {
      throw interface_only_exception();
   }

   int graphics::GetBkMode() const
   {
      throw interface_only_exception();
   }

   int graphics::GetPolyFillMode() const
   {
      throw interface_only_exception();
   }

   int graphics::GetROP2() const
   {
      throw interface_only_exception();
   }

   int graphics::GetStretchBltMode() const
   {
      throw interface_only_exception();
   }

   COLORREF graphics::GetTextColor() const
   {
      throw interface_only_exception();
   }

   int graphics::GetMapMode() const
   {
      throw interface_only_exception();
   }

   int graphics::GetGraphicsMode() const
   {
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::GetWorldTransform(XFORM* pXform) const
   {
      UNREFERENCED_PARAMETER(pXform);
      throw interface_only_exception();
   }

#endif

   point graphics::GetViewportOrg() const
   {
      throw interface_only_exception();
   }

   size graphics::GetViewportExt() const
   {
      throw interface_only_exception();
   }

   point graphics::GetWindowOrg() const
   {
      throw interface_only_exception();
   }

   size graphics::GetWindowExt() const
   {
      throw interface_only_exception();
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();
   }

   size graphics::SetViewportExt(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception();
   }

   point graphics::SetWindowOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();
   }

   size graphics::SetWindowExt(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception();
   }

   void graphics::DPtoLP(LPPOINT lpPoints, int nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   void graphics::DPtoLP(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   void graphics::LPtoDP(LPPOINT lpPoints, int nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   void graphics::LPtoDP(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::FillRgn(::ca::region* pRgn, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

   BOOL graphics::FrameRgn(::ca::region* pRgn, ::ca::brush* pBrush, int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception();
   }

   BOOL graphics::InvertRgn(::ca::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception();
   }

   BOOL graphics::PaintRgn(::ca::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception();
   }

   BOOL graphics::PtVisible(int x, int y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   BOOL graphics::PtVisible(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();
   }

   BOOL graphics::RectVisible(LPCRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   point graphics::GetCurrentPosition() const
   {
      throw interface_only_exception();
   }

   point graphics::MoveTo(POINT point)
   {
      return MoveTo((double)point.x, (double)point.y);
   }

   BOOL graphics::LineTo(POINT point)
   {
      return LineTo(double(point.x), double(point.y));
   }

   BOOL graphics::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception();
   }

   BOOL graphics::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception();
   }


   BOOL graphics::Arc(int x1, int y1, int x2, int y2, double start, double extends)
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

   BOOL graphics::Arc(LPCRECT lpRect, double start, double extends)
   {
      return Arc(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, start, extends);
   }

   BOOL graphics::Polyline(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   void graphics::FillRect(LPCRECT lpRect, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

   void graphics::FrameRect(LPCRECT lpRect, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

   void graphics::InvertRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::DrawIcon(int x, int y, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(picon);
      throw interface_only_exception();
   }

   BOOL graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(picon);
      throw interface_only_exception();
   }

   BOOL graphics::DrawIcon(int x, int y, ::visual::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(picon);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(istepIfAniCur);
      UNREFERENCED_PARAMETER(hbrFlickerFreeDraw);
      UNREFERENCED_PARAMETER(diFlags);
      throw interface_only_exception();
   }

   BOOL graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception();
   }

   BOOL graphics::DrawState(point pt, size size, ::ca::bitmap* pBitmap, UINT nFlags, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(pBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception();
   }

   BOOL graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

#endif

   BOOL graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, BOOL bPrefixText, int nTextLen, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception();
   }

   BOOL graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, BOOL bPrefixText, int nTextLen, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception();
   }

   BOOL graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::ca::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

#endif

   BOOL graphics::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nEdge);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();
   }

   BOOL graphics::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nType);
      UNREFERENCED_PARAMETER(nState);
      throw interface_only_exception();
   }

   BOOL graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception();
   }

   BOOL graphics::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception();
   }

   void graphics::DrawFocusRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::Ellipse(int x1, int y1, int x2, int y2)
   {

      BOOL bFill = FillEllipse(x1, y1, x2, y2);

      BOOL bDraw = DrawEllipse(x1, y1, x2, y2);

      return bFill && bDraw;

   }

   BOOL graphics::Ellipse(LPCRECT lpRect)
   {

      BOOL bFill = FillEllipse(lpRect);

      BOOL bDraw = DrawEllipse(lpRect);

      return bFill && bDraw;

   }


   BOOL graphics::DrawEllipse(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   BOOL graphics::DrawEllipse(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::FillEllipse(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   BOOL graphics::FillEllipse(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception();
   }

   BOOL graphics::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception();
   }

   BOOL graphics::Polygon(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   BOOL graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyCounts);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   BOOL graphics::Polygon(point_array & pta)
   {
      return Polygon(pta.get_data(), (int) pta.get_count());
   }

   BOOL graphics::Rectangle(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   BOOL graphics::Rectangle(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::DrawRectangle(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   BOOL graphics::DrawRectangle(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::FillRectangle(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   BOOL graphics::FillRectangle(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   BOOL graphics::RoundRect(int x1, int y1, int x2, int y2, int x3, int y3)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      throw interface_only_exception();
   }

   BOOL graphics::RoundRect(LPCRECT lpRect, POINT point)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();
   }

   BOOL graphics::PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception();
   }

   BOOL graphics::BitBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, DWORD dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception();
   }

   BOOL graphics::StretchBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
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
      throw interface_only_exception();
   }

   COLORREF graphics::GetPixel(int x, int y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   COLORREF graphics::GetPixel(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();
   }

   COLORREF graphics::SetPixel(int x, int y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   BOOL graphics::FloodFill(int x, int y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   BOOL graphics::ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      UNREFERENCED_PARAMETER(nFillType);
      throw interface_only_exception();
   }

   BOOL graphics::TextOut(int x, int y, const char * lpszString, int nCount)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   BOOL graphics::TextOut(int x, int y, const string & str)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception();
   }

   BOOL graphics::ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception();
   }

   BOOL graphics::ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect, const string & str, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception();
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
      throw interface_only_exception();
   }

   size graphics::TabbedTextOut(int x, int y, const string & str, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);
      throw interface_only_exception();
   }

   size graphics::GetTabbedTextExtent(const char * lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception();
   }

   size graphics::GetTabbedTextExtent(const string & str, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception();
   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception();
   }

   size graphics::GetOutputTabbedTextExtent(const string & str, int nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception();
   }

   BOOL graphics::GrayString(::ca::brush* pBrush, BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int),
      LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(lpfnOutput);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception();
   }

   UINT graphics::GetTextAlign() const
   {
      throw interface_only_exception();
   }

   int graphics::GetTextFace(int nCount, LPTSTR lpszFacename) const
   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszFacename);
      throw interface_only_exception();
   }

   int graphics::GetTextFace(string & rString) const
   {
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::_AFX_FUNCNAME(GetTextMetrics)(LPTEXTMETRIC lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception();
   }

   BOOL graphics::GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception();
   }

#endif

   int graphics::GetTextCharacterExtra() const
   {
      throw interface_only_exception();
   }

   BOOL graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception();
   }

   BOOL graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception();
   }

   DWORD graphics::GetFontLanguageInfo() const
   {
      throw interface_only_exception();
   }

#ifdef WINDOWS

   DWORD graphics::GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();
   }

   DWORD graphics::GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();
   }

#endif

   size graphics::GetAspectRatioFilter() const
   {
      throw interface_only_exception();
   }

   BOOL graphics::ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::ca::region * pRgnUpdate, LPRECT lpRectUpdate)
   {
      UNREFERENCED_PARAMETER(dx);
      UNREFERENCED_PARAMETER(dy);
      UNREFERENCED_PARAMETER(lpRectScroll);
      UNREFERENCED_PARAMETER(lpRectClip);
      UNREFERENCED_PARAMETER(pRgnUpdate);
      UNREFERENCED_PARAMETER(lpRectUpdate);
      throw interface_only_exception();
   }

   // Printer Escape Functions
   int graphics::Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszInData);
      UNREFERENCED_PARAMETER(lpOutData);
      throw interface_only_exception();
   }

   // ::ca::graphics_sp 3.1 Specific functions
   UINT graphics::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception();
   }

   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      UNREFERENCED_PARAMETER(lpDevMode);
      throw interface_only_exception();
   }

   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
   {
      UNREFERENCED_PARAMETER(cbData);
      UNREFERENCED_PARAMETER(lpotm);
      throw interface_only_exception();
   }

   BOOL graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpabc);
      throw interface_only_exception();
   }

#endif

   DWORD graphics::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData,  DWORD cbData) const
   {
      UNREFERENCED_PARAMETER(dwTable);
      UNREFERENCED_PARAMETER(dwOffset);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(cbData);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   int graphics::GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const
   {
      UNREFERENCED_PARAMETER(nPairs);
      UNREFERENCED_PARAMETER(lpkrnpair);
      throw interface_only_exception();
   }

   DWORD graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,  DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   {
      UNREFERENCED_PARAMETER(nChar);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpgm);
      UNREFERENCED_PARAMETER(cbBuffer);
      UNREFERENCED_PARAMETER(lpBuffer);
      UNREFERENCED_PARAMETER(lpmat2);
      throw interface_only_exception();
   }

   // ::userbase::document handling functions
   int graphics::StartDoc(LPDOCINFO lpDocInfo)
   {
      UNREFERENCED_PARAMETER(lpDocInfo);
      throw interface_only_exception();
   }

#endif

   int graphics::StartPage()
   {
      throw interface_only_exception();
   }

   int graphics::EndPage()
   {
      throw interface_only_exception();
   }

   int graphics::SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, int))
   {
      UNREFERENCED_PARAMETER(lpfn);
      throw interface_only_exception();
   }

   int graphics::AbortDoc()
   {
      throw interface_only_exception();
   }

   int graphics::EndDoc()
   {
      throw interface_only_exception();
   }

   BOOL graphics::MaskBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
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

      throw interface_only_exception();
   }
   BOOL graphics::PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc,
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
      throw interface_only_exception();
   }

   BOOL graphics::SetPixelV(int x, int y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   BOOL graphics::SetPixelV(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   BOOL graphics::AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nRadius);
      UNREFERENCED_PARAMETER(fStartAngle);
      UNREFERENCED_PARAMETER(fSweepAngle);
      throw interface_only_exception();
   }

   BOOL graphics::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception();
   }

   int graphics::GetArcDirection() const
   {
      throw interface_only_exception();
   }

   BOOL graphics::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {
      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception();
   }

#endif

   ::ca::pen & graphics::GetCurrentPen() const
   {
      throw interface_only_exception();
   }

   ::ca::brush & graphics::GetCurrentBrush() const
   {
      throw interface_only_exception();
   }

   ::ca::palette & graphics::GetCurrentPalette() const
   {
      throw interface_only_exception();
   }

   ::ca::font & graphics::GetCurrentFont() const
   {
      throw interface_only_exception();
   }

   ::ca::bitmap & graphics::GetCurrentBitmap() const
   {
      throw interface_only_exception();
   }

   BOOL graphics::PolyBezier(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   int graphics::DrawEscape(int nEscape, int nInputSize, const char * lpszInputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      throw interface_only_exception();
   }

   int graphics::Escape(int nEscape, int nInputSize, const char * lpszInputData, int nOutputSize, char * lpszOutputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      UNREFERENCED_PARAMETER(nOutputSize);
      UNREFERENCED_PARAMETER(lpszOutputData);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpABCF);
      throw interface_only_exception();
   }

#endif

   BOOL graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float * lpFloatBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpFloatBuffer);
      throw interface_only_exception();
   }

   BOOL graphics::AbortPath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::BeginPath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::CloseFigure()
   {
      throw interface_only_exception();
   }

   BOOL graphics::EndPath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::FillPath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::FlattenPath()
   {
      throw interface_only_exception();
   }

   float graphics::GetMiterLimit() const
   {
      throw interface_only_exception();
   }

   int graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   BOOL graphics::SetMiterLimit(float fMiterLimit)
   {
      UNREFERENCED_PARAMETER(fMiterLimit);
      throw interface_only_exception();
   }

   BOOL graphics::StrokeAndFillPath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::StrokePath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::WidenPath()
   {
      throw interface_only_exception();
   }

   BOOL graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {
      UNREFERENCED_PARAMETER(nDataSize);
      UNREFERENCED_PARAMETER(pCommentData);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::PlayMetaFile(HENHMETAFILE hEnhMF, LPCRECT lpBounds)
   {
      UNREFERENCED_PARAMETER(hEnhMF);
      UNREFERENCED_PARAMETER(lpBounds);
      throw interface_only_exception();
   }

#endif

   BOOL graphics::TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
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
      throw interface_only_exception();
   }

   BOOL graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, DWORD dwMode)
   {
      UNREFERENCED_PARAMETER(pVertices);
      UNREFERENCED_PARAMETER(nVertices);
      UNREFERENCED_PARAMETER(pMesh);
      UNREFERENCED_PARAMETER(nMeshElements);
      UNREFERENCED_PARAMETER(dwMode);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   COLORREF graphics::GetDCBrushColor() const
   {
      throw interface_only_exception();
   }

   COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   COLORREF graphics::GetDCPenColor() const
   {
      throw interface_only_exception();
   }

   COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   BOOL graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpabc);
      throw interface_only_exception();
   }

   BOOL graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception();
   }

   BOOL graphics::GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpnFit);
      UNREFERENCED_PARAMETER(alpDx);
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   BOOL graphics::GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

#endif

   void graphics::DPtoHIMETRIC(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   void graphics::HIMETRICtoLP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   ::ca::brush* PASCAL graphics::GetHalftoneBrush()
   {
      throw interface_only_exception();
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
      throw interface_only_exception();
   }

   void graphics::FillSolidRect(LPCRECT lpRect, COLORREF clr)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(clr);
      throw interface_only_exception();
   }

   void graphics::FillSolidRect(const __rect64 * lpRect, COLORREF clr)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(clr);
      throw interface_only_exception();
   }

   void graphics::FillSolidRect(int x, int y, int cx, int cy, COLORREF clr)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(clr);
      throw interface_only_exception();
   }

   void graphics::Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(clrTopLeft);
      UNREFERENCED_PARAMETER(clrBottomRight);
      throw interface_only_exception();
   }

   void graphics::Draw3dRect(int x, int y, int cx, int cy,  COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(clrTopLeft);
      UNREFERENCED_PARAMETER(clrBottomRight);
      throw interface_only_exception();
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::ca::graphics_sp

   void graphics::assert_valid() const
   {
      throw interface_only_exception();
   }

   void graphics::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }




   BOOL graphics::DeleteDC()
   {
      throw interface_only_exception();
   }

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int graphics::StartDoc(const char * lpszDocName)
   {
      UNREFERENCED_PARAMETER(lpszDocName);
      throw interface_only_exception();
   }

   int graphics::SaveDC()
   {
      throw interface_only_exception();
   }

   BOOL graphics::RestoreDC(int nSavedDC)
   {
      UNREFERENCED_PARAMETER(nSavedDC);
      throw interface_only_exception();
   }

   ::ca::graphics_object* PASCAL graphics::SelectGdiObject(HDC hDC, HGDIOBJ h)
   {
      UNREFERENCED_PARAMETER(hDC);
      UNREFERENCED_PARAMETER(h);
      throw interface_only_exception();
   }

   ::ca::graphics_object* graphics::SelectStockObject(int nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception();
   }

   ::ca::pen* graphics::SelectObject(::ca::pen * pPen)
   {
      UNREFERENCED_PARAMETER(pPen);
      throw interface_only_exception();
   }

   ::ca::brush* graphics::SelectObject(::ca::brush * pBrush)
   {
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception();
   }

   ::ca::font* graphics::SelectObject(::ca::font * pFont)
   {
      UNREFERENCED_PARAMETER(pFont);
      throw interface_only_exception();
   }

   int graphics::SelectObject(::ca::region * pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception();
   }

   ::ca::palette* graphics::SelectPalette(::ca::palette * pPalette, BOOL bForceBackground)
   {
      UNREFERENCED_PARAMETER(pPalette);
      UNREFERENCED_PARAMETER(bForceBackground);
      throw interface_only_exception();
   }

   COLORREF graphics::SetBkColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   int graphics::SetBkMode(int nBkMode)
   {
      UNREFERENCED_PARAMETER(nBkMode);
      throw interface_only_exception();
   }

   int graphics::SetPolyFillMode(int nPolyFillMode)
   {
      UNREFERENCED_PARAMETER(nPolyFillMode);
      throw interface_only_exception();
   }

   int graphics::SetROP2(int nDrawMode)
   {
      UNREFERENCED_PARAMETER(nDrawMode);
      throw interface_only_exception();
   }

   int graphics::SetStretchBltMode(int nStretchMode)
   {
      UNREFERENCED_PARAMETER(nStretchMode);
      throw interface_only_exception();
   }

   COLORREF graphics::SetTextColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   int graphics::SetGraphicsMode(int iMode)
   {
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::SetWorldTransform(const XFORM* pXform)
   {
      UNREFERENCED_PARAMETER(pXform);
      throw interface_only_exception();
   }

   BOOL graphics::ModifyWorldTransform(const XFORM* pXform, DWORD iMode)
   {
      UNREFERENCED_PARAMETER(pXform);
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception();
   }

#endif

   int graphics::SetMapMode(int nMapMode)
   {
      UNREFERENCED_PARAMETER(nMapMode);
      throw interface_only_exception();
   }

   point graphics::SetViewportOrg(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   point graphics::OffsetViewportOrg(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception();
   }

   size graphics::SetViewportExt(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   size graphics::ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception();
   }

   point graphics::SetWindowOrg(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   point graphics::OffsetWindowOrg(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception();
   }

   size graphics::SetWindowExt(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   size graphics::ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception();
   }

   int graphics::GetClipBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
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
      throw interface_only_exception();
   }

   int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   int graphics::ExcludeClipRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   int graphics::IntersectClipRect(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();
   }

   int graphics::IntersectClipRect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();
   }

   int graphics::OffsetClipRgn(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   int graphics::OffsetClipRgn(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception();
   }

   point graphics::MoveTo(int x, int y)
   {
      return MoveTo((double)x, (double)y);
   }

   BOOL graphics::LineTo(int x, int y)
   {
      return LineTo((double) x, (double) y);
   }

   BOOL graphics::LineTo(double x, double y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();
   }

   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception();
   }

   int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   {
      UNREFERENCED_PARAMETER(nBreakExtra);
      UNREFERENCED_PARAMETER(nBreakCount);
      throw interface_only_exception();
   }

   int graphics::SetTextCharacterExtra(int nCharExtra)
   {
      UNREFERENCED_PARAMETER(nCharExtra);
      throw interface_only_exception();
   }

   DWORD graphics::SetMapperFlags(DWORD dwFlag)
   {
      UNREFERENCED_PARAMETER(dwFlag);
      throw interface_only_exception();
   }

   DWORD graphics::GetLayout() const
   {
      throw interface_only_exception();
   }

   DWORD graphics::SetLayout(DWORD dwSetLayout)
   {
      UNREFERENCED_PARAMETER(dwSetLayout);
      throw interface_only_exception();
   }

   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   BOOL graphics::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      throw interface_only_exception();
   }

   int graphics::SetArcDirection(int nArcDirection)
   {
      UNREFERENCED_PARAMETER(nArcDirection);
      throw interface_only_exception();
   }

   BOOL graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   BOOL graphics::PolylineTo(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {
      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception();
   }

#endif

   BOOL graphics::PolyBezierTo(const POINT* lpPoints, int nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   BOOL graphics::SelectClipPath(int nMode)
   {
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception();
   }

   int graphics::SelectClipRgn(::ca::region* pRgn, int nMode)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   BOOL graphics::PlayMetaFile(HMETAFILE hMF)
   {
      UNREFERENCED_PARAMETER(hMF);
      throw interface_only_exception();
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   void graphics::DPtoLP(LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception();
   }

   int graphics::_AFX_FUNCNAME(DrawText)(const char * lpszString, int nCount, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception();
   }

   int graphics::DrawText(const string & str, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   int graphics::DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception();
   }

   int graphics::DrawTextEx(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception();
   }

#endif

   size graphics::GetTextExtent(const char * lpszString, int nCount, int iIndex) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(iIndex);
      throw interface_only_exception();
   }

   size graphics::GetTextExtent(const char * lpszString, int nCount) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   size graphics::GetTextExtent(const string & str) const
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception();
   }

   size graphics::GetOutputTextExtent(const char * lpszString, int nCount) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception();
   }

   size graphics::GetOutputTextExtent(const string & str) const
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception();
   }

#ifdef WINDOWS

#pragma push_macro("GetTextMetrics")
#undef GetTextMetrics
   BOOL graphics::GetTextMetrics(LPTEXTMETRIC lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception();
   }
#pragma pop_macro("GetTextMetrics")
   #pragma push_macro("DrawText")
   #pragma push_macro("DrawTextEx")
   #undef DrawText
   #undef DrawTextEx

#endif

   int graphics::DrawText(const char * lpszString, int nCount, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   int graphics::DrawText(const string & str, LPRECT lpRect, UINT nFormat)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      throw interface_only_exception();
   }

   int graphics::DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception();
   }

   int graphics::DrawTextEx(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception();
   }

   #pragma pop_macro("DrawText")
   #pragma pop_macro("DrawTextEx")

#endif

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
      throw interface_only_exception();
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
      throw interface_only_exception();
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


   bool graphics::blur(bool bExpand, double dRadius, LPCRECT lpcrect)
   {
      throw interface_only_exception();
   }


   COLORREF graphics::SetColor(COLORREF crColor)
   {

      m_crColor = crColor;

      m_penxyz.m_crPenColor = crColor;
      m_penxyz.m_bUpdated = false;

      m_brushxyz.m_crColor = crColor;
      m_brushxyz.m_bUpdated = false;


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

   BOOL graphics::DrawRect(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      Draw3dRect(x1, y1, x2, y2, m_crColor, m_crColor);

      return TRUE;

   }

   BOOL graphics::drawRect(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawRect(x1, y1, x2, y2);

   }

   BOOL graphics::draw_rect(int x1, int y1, int x2, int y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawRect(x1, y1, x2, y2);

   }

   point graphics::MoveTo(double x, double y)
   {
      int px = (int) m_x;
      int py = (int) m_y;
      m_x = x;
      m_y = y;
      return point(px, py);
   }


   void graphics::set_solid_pen(double dWidth)
   {

      m_penxyz.CreatePen(PS_SOLID, dWidth, m_crColor);

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
      m_p->attach(::BeginPaint(pwindow->get_safe_handle(), &m_ps));
#endif
   }

   paint_graphics::~paint_graphics()
   {
#ifdef WINDOWS
      ::EndPaint(m_pwindow->get_safe_handle(), &m_ps);
#endif
   }


   double graphics::get_dpix() const
   {
      return 96.0;
   }

} // namespace ca




// resource failure
void AfxThrowResourceException()
{
   throw resource_exception();
}

// ::fontopus::user alert
void AfxThrowUserException()
{
   throw user_exception();
}


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
