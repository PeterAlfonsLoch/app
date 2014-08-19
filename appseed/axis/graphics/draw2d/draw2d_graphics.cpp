#include "framework.h"
#include <math.h>


namespace draw2d
{

   void word_break(::draw2d::graphics * pdc, const string & strSource, const RECT & rect, string &str1, string & str2);

   strsize _EncodeV033(string & str);




   graphics::graphics()
   {
      m_puistrcontext         = NULL;
      m_pdrawcontext          = NULL;
      m_pdibAlphaBlend        = NULL;
      m_pjob                  = NULL;
      m_dFontFactor           = 1.0;
      m_pdib                  = NULL;
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

   void * graphics::get_os_data_ex(int i) const
   {
      if(i == 0)
      {
         return get_os_data();
      }
      else
      {
         return NULL;
      }
   }

   void graphics::release_os_data_ex(int i, void * p)
   {
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

   bool graphics::attach(void * pdata)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   void * graphics::detach()
   {

       throw interface_only_exception(get_app());

       return NULL;

   }


   bool graphics::IsPrinting() const
   {

       throw interface_only_exception(get_app());

       return false;

   }


   bool graphics::CreateDC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

       UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      throw interface_only_exception(get_app());

      return false;

   }


   bool graphics::CreateIC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

       UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      throw interface_only_exception(get_app());

      return false;

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

       UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception(get_app());

      return false;

   }


/*   int32_t graphics::ExcludeUpdateRgn(::window_sp pwindow)
   {
      UNREFERENCED_PARAMETER(pwindow);
      throw interface_only_exception(get_app());
   }
   */

   int32_t graphics::GetDeviceCaps(int32_t nIndex) const
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());

      return -1;

   }

   point graphics::GetBrushOrg() const
   {

      throw interface_only_exception(get_app());

      return null_point();

   }

   bool graphics::set_text_color(COLORREF clr)
   {

      ::draw2d::brush_sp brush(allocer(), clr);

      if(brush.is_null())
         return false;

      return SelectObject(brush) != FALSE;

   }

   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {

       UNREFERENCED_PARAMETER(x);
        UNREFERENCED_PARAMETER(y);
        throw interface_only_exception(get_app());

      return null_point();

   }

   point graphics::SetBrushOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());


      return null_point();

   }

   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      UNREFERENCED_PARAMETER(nObjectType);
      UNREFERENCED_PARAMETER(lpfn);
      UNREFERENCED_PARAMETER(lpData);
      throw interface_only_exception(get_app());

      return -1;

   }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception(get_app());

      return NULL;

   }


   bool graphics::SelectFont(::draw2d::font * pfont)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_spfont = pfont;

      return true;

   }

   bool graphics::selectFont(::draw2d::font * pfont)
   {
      return SelectFont(pfont);
   }

   bool graphics::select_font(::draw2d::font * pfont)
   {
      return selectFont(pfont);
   }

   bool graphics::SetFont(::draw2d::font * pfont)
   {
      return select_font(pfont);
   }

   bool graphics::setFont(::draw2d::font * pfont)
   {
      return SetFont(pfont);
   }

   bool graphics::set_font(::draw2d::font * pfont)
   {
      return setFont(pfont);
   }

   COLORREF graphics::GetNearestColor(COLORREF crColor) const
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());

      return 0;

   }

   UINT graphics::RealizePalette()
   {
      throw interface_only_exception(get_app());

      return -1;

   }

   void graphics::UpdateColors()
   {
      throw interface_only_exception(get_app());



   }


   int32_t graphics::GetPolyFillMode() const
   {

      throw interface_only_exception(get_app());

      return -1;

   }


   int32_t graphics::GetROP2() const
   {

      throw interface_only_exception(get_app());

      return -1;

   }


   int32_t graphics::GetStretchBltMode() const
   {

      throw interface_only_exception(get_app());

      return -1;

   }


   int32_t graphics::GetMapMode() const
   {

      throw interface_only_exception(get_app());

      return -1;

   }


   int32_t graphics::GetGraphicsMode() const
   {

      throw interface_only_exception(get_app());

      return -1;

   }


#ifdef WINDOWS

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {
      UNREFERENCED_PARAMETER(pXform);
      throw interface_only_exception(get_app());

      return false;

   }

#endif

   point graphics::GetViewportOrg() const
   {
      throw interface_only_exception(get_app());

      return null_point();

   }

   size graphics::GetViewportExt() const
   {
      throw interface_only_exception(get_app());

      return size(0, 0);

   }

   point graphics::GetWindowOrg() const
   {
      throw interface_only_exception(get_app());

      return null_point();
   }

   size graphics::GetWindowExt() const
   {
      throw interface_only_exception(get_app());

      return size(0, 0);

   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());

      return null_point();
   }

   size graphics::SetViewportExt(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
      return ::size(0, 0);
   }

   point graphics::SetWindowOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());


      return null_point();

   }

   size graphics::SetWindowExt(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());

      return ::size(0, 0);

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

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());

      return false;
   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
      return false;

   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::PtVisible(int32_t x, int32_t y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());

      return false;
   }

   bool graphics::PtVisible(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());

      return false;
   }

   bool graphics::RectVisible(const RECT &  lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());

      return false;
   }

   point graphics::GetCurrentPosition() const
   {
      throw interface_only_exception(get_app());

      return null_point();
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

      return false;

   }


   bool graphics::Arc(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {

      return Arc(lpRect.left,lpRect.top,width(lpRect),height(lpRect),ptStart.x,ptStart.y,ptEnd.x,ptEnd.y);

   }


   bool graphics::Arc(int32_t x1, int32_t y1, int32_t w, int32_t h, double start, double extends)
   {

      point ptCenter;

      ptCenter.x = x1 + w / 2;
      ptCenter.y = y1 + h / 2;

      double dx = w / 2.0;
      double dy = h / 2.0;

      double startx = (cos(start * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double starty = (sin(start * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      double endx = (cos((start + extends) * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double endy = (sin((start + extends) * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      return Arc(x1, y1, x1 + w, y1 + h, (int32_t) startx, (int32_t) starty, (int32_t) endx, (int32_t) endy);

   }

   bool graphics::Arc(const RECT &  lpRect, double start, double extends)
   {
      return Arc(lpRect.left, lpRect.top, lpRect.right, lpRect.bottom, start, extends);
   }



   bool graphics::Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
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

      return false;
   }


   bool graphics::Arc(const RECTD & lpRect,POINTD ptStart,POINTD ptEnd)
   {

      return Arc(lpRect.left,lpRect.top,width(lpRect), height(lpRect),ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

   }


   bool graphics::Arc(double x1,double y1,double w,double h,double start,double extends)
   {

      pointd ptCenter;

      ptCenter.x = x1 + w / 2.0;
      ptCenter.y = y1 + h / 2.0;

      double dx = w / 2.0;
      double dy = h / 2.0;

      double startx = (cos(start * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double starty = (sin(start * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      double endx = (cos((start + extends) * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double endy = (sin((start + extends) * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      return Arc(x1,y1,x1 + w,y1 + h,(double)startx,(double)starty,(double)endx,(double)endy);

   }


   bool graphics::Arc(const RECTD & lpRect,double start,double extends)
   {

      return Arc(lpRect.left,lpRect.top,lpRect.right,lpRect.bottom,start,extends);

   }


   bool graphics::Polyline(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());

      return false;
   }

   void graphics::FillRect(const RECT &  lpRect, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

   void graphics::FrameRect(const RECT &  lpRect, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
   }

   void graphics::InvertRect(const RECT &  lpRect)
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

      return false;
   }

   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(picon);
      throw interface_only_exception(get_app());


      return false;

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

      return false;

   }

   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      throw interface_only_exception(get_app());

      return false;

   }

   bool graphics::DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(pBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());

      return false;
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

      return false;

   }

   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());

      return false;

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

      return false;

   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());

      return false;


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

      return false;

   }

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());

      return false;
   }

#endif

   bool graphics::DrawEdge(const RECT & lpRect,UINT nEdge,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nEdge);
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::DrawFrameControl(const RECT & lpRect,UINT nType,UINT nState)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nType);
      UNREFERENCED_PARAMETER(nState);
      throw interface_only_exception(get_app());
      return false;
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
      return false;
   }

   bool graphics::Chord(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
      return false;
   }

   void graphics::DrawFocusRect(const RECT &  lpRect)
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

   bool graphics::Ellipse(const RECT &  lpRect)
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
      return false;
   }

   bool graphics::DrawEllipse(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      ::rect rect(x1, y1, x2, y2);

      return FillEllipse(rect);


   }

   bool graphics::FillEllipse(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
   }


   bool graphics::Ellipse(double x1,double y1,double x2,double y2)
   {

      bool bFill = FillEllipse(x1,y1,x2,y2);

      bool bDraw = DrawEllipse(x1,y1,x2,y2);

      return bFill && bDraw;

   }

   bool graphics::Ellipse(const RECTD & lpRect)
   {

      bool bFill = FillEllipse(lpRect);

      bool bDraw = DrawEllipse(lpRect);

      return bFill && bDraw;

   }


   bool graphics::DrawEllipse(double x1,double y1,double x2,double y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::DrawEllipse(const RECTD & lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::FillEllipse(double x1,double y1,double x2,double y2)
   {

      ::rectd rect(x1,y1,x2,y2);

      return FillEllipse(rect);


   }

   bool graphics::FillEllipse(const RECTD & lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
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
      return false;
   }

   bool graphics::Pie(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::fill_polygon(const POINTD * lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::draw_polygon(const POINTD * lpPoints,int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::fill_polygon(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::draw_polygon(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }


   bool graphics::Polygon(const POINT* lpPoints, int32_t nCount)
   {

      bool bOk1 = fill_polygon(lpPoints, nCount);

      bool bOk2 = draw_polygon(lpPoints, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::Polygon(const POINTD* lpPoints,int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyCounts);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::Polygon(point_array & pta)
   {
      return Polygon(pta.get_data(), (int32_t) pta.get_count());
   }


   bool graphics::Polygon(pointd_array & pta)
   {
      return Polygon(pta.get_data(),(int32_t)pta.get_count());
   }



   bool graphics::draw_polygon(point_array & pta)
   {
      return draw_polygon(pta.get_data(),(int32_t)pta.get_count());
   }


   bool graphics::draw_polygon(pointd_array & pta)
   {
      return draw_polygon(pta.get_data(),(int32_t)pta.get_count());
   }


   bool graphics::fill_polygon(point_array & pta)
   {
      return fill_polygon(pta.get_data(),(int32_t)pta.get_count());
   }


   bool graphics::fill_polygon(pointd_array & pta)
   {
      return fill_polygon(pta.get_data(),(int32_t)pta.get_count());
   }

   bool graphics::Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::Rectangle(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::DrawRectangle(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::FillRectangle(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return false;
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
      return false;
   }

   bool graphics::RoundRect(const RECT &  lpRect, POINT point)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(dwRop);
      throw interface_only_exception(get_app());
      return false;
   }


   bool graphics::BitBlt(POINT ptDst, SIZE size, ::draw2d::graphics * pgraphicsSrc, POINT ptSrc, uint32_t dwRop)
   {

      return BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, dwRop);

   }


   bool graphics::BitBlt(const RECT &  lpcrect,::draw2d::graphics * pgraphicsSrc,POINT ptSrc,uint32_t dwRop)
   {

      return BitBlt(lpcrect.left, lpcrect.top, width(lpcrect), height(lpcrect), pgraphicsSrc, ptSrc.x, ptSrc.y, dwRop);

   }


   bool graphics::BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop)
   {

      if (m_pdibAlphaBlend != NULL)
      {

         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());

         rect rectBlt(point((int64_t)x, (int64_t)y), size(nWidth, nHeight));

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            // The following commented out code does not work well when there is clipping
            // and some calculations are not precise
            //if (m_pdib != NULL && pgraphicsSrc->m_pdib != NULL)
            //{

            //   point ptOff = GetViewportOrg();

            //   x += ptOff.x;

            //   y += ptOff.y;

            //   return m_pdib->blend(point(x, y), pgraphicsSrc->m_pdib, point(xSrc, ySrc), m_pdibAlphaBlend, point(m_ptAlphaBlend.x - x, m_ptAlphaBlend.y - y), rectBlt.size());

            //}
            //else
            {

               ::draw2d::dib_sp dib1(allocer());

               dib1->create(rectBlt.size());

               dib1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               if (!dib1->from(null_point(), pgraphicsSrc, point(xSrc, ySrc), rectBlt.size()))
                  return false;

               dib1->blend(point(0, 0), m_pdibAlphaBlend, point((int)max(0, x - m_ptAlphaBlend.x), (int)max(0, y - m_ptAlphaBlend.y)), rectBlt.size());

               keep < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);

               return BitBlt(x, y, nWidth, nHeight, dib1->get_graphics(), 0, 0, dwRop);

            }

         }

      }

      return false;
   }


   bool graphics::StretchBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop)
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
      return false;
   }

   COLORREF graphics::GetPixel(int32_t x, int32_t y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
      return 0;
   }

   COLORREF graphics::GetPixel(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
      return 0;
   }

   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return 0;
   }

   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return 0;
   }

   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      UNREFERENCED_PARAMETER(nFillType);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::TextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount)
   {

      return TextOut((double)x, (double)y, lpszString, nCount);

   }

   bool graphics::TextOut(int32_t x, int32_t y, const string & str)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::TextOut(double x, double y, const char * lpszString, int32_t nCount)
   {
      if (m_pdibAlphaBlend != NULL)
      {

         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());

         rect rectText(point((int64_t)x, (int64_t)y), GetTextExtent(lpszString, nCount));

         if (rectIntersect.intersect(rectIntersect, rectText))
         {

            ::draw2d::dib_sp dib1(allocer());
            dib1->create(rectText.size());
            dib1->Fill(0, 0, 0, 0);
            dib1->get_graphics()->SelectObject(get_current_font());
            dib1->get_graphics()->SelectObject(get_current_brush());
            dib1->get_graphics()->TextOut(0, 0, lpszString, nCount);


            // The following commented out code does not work well when there is clipping
            // and some calculations are not precise
            //::rect rectClip;

            //GetClipBox(rectClip);

            //if (m_pdib != NULL && rectClip.is_null())
            //{

            //   point ptOff = GetViewportOrg();

            //   x += ptOff.x;

            //   y += ptOff.y;

            //   m_pdib->blend(point((int)x, (int)y), dib1, point(0, 0), m_pdibAlphaBlend, point((int)(m_ptAlphaBlend.x - x), (int) (m_ptAlphaBlend.y - y)), rectText.size());

            //}
            //else
            {

               dib1->blend(null_point(), m_pdibAlphaBlend, point((int)max(0, x - m_ptAlphaBlend.x), (int)max(0, y - m_ptAlphaBlend.y)), rectText.size());

               set_alpha_mode(::draw2d::alpha_mode_blend);

               keep < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);

               BitBlt((int)x, (int)y, rectText.width(), rectText.height(), dib1->get_graphics(), 0, 0, SRCCOPY);

            }

            /*
            ::draw2d::pen_sp p(allocer());

            p->create_solid(1.0, ARGB(255, 255, 0, 0));
            SelectObject(p);
            MoveTo(0., y);
            LineTo(500., y);
            p->create_solid(1.0, ARGB(255, 0, 255, 0));
            SelectObject(p);
            MoveTo(0, m_ptAlphaBlend.y);
            LineTo(500, m_ptAlphaBlend.y);
            p->create_solid(1.0, ARGB(255, 0, 255, 255));
            SelectObject(p);
            MoveTo(0, m_ptAlphaBlend.y + m_pdibAlphaBlend->m_size.cy);
            LineTo(500, m_ptAlphaBlend.y + m_pdibAlphaBlend->m_size.cy);
            */

            return true;
         }

      }

      return false;

   }

   bool graphics::TextOut(double x, double y, const string & str)
   {
      return TextOut(x, y, str, (int32_t) str.get_length());
   }


   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT &  lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT &  lpRect, const string & str, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpDxWidths);
      throw interface_only_exception(get_app());
      return false;
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
      return size(0, 0);
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
      return size(0, 0);
   }

   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
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
      return false;
   }

   UINT graphics::GetTextAlign() const
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::GetTextFace(int32_t nCount, LPTSTR lpszFacename) const
   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszFacename);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::GetTextFace(string & rString) const
   {
      UNREFERENCED_PARAMETER(rString);
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::get_text_metrics(text_metric * lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::get_output_text_metrics(text_metric * lpMetrics) const
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      throw interface_only_exception(get_app());
      return false;
   }

   int32_t graphics::GetTextCharacterExtra() const
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception(get_app());
      return false;
   }

   uint32_t graphics::GetFontLanguageInfo() const
   {
      throw interface_only_exception(get_app());
      return -1;
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
      return -1;
   }

   uint32_t graphics::GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
      return -1;
   }

#endif

   size graphics::GetAspectRatioFilter() const
   {
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   bool graphics::ScrollDC(int32_t dx, int32_t dy, const RECT &  lpRectScroll, const RECT &  lpRectClip, ::draw2d::region * pRgnUpdate, LPRECT lpRectUpdate)
   {
      UNREFERENCED_PARAMETER(dx);
      UNREFERENCED_PARAMETER(dy);
      UNREFERENCED_PARAMETER(lpRectScroll);
      UNREFERENCED_PARAMETER(lpRectClip);
      UNREFERENCED_PARAMETER(pRgnUpdate);
      UNREFERENCED_PARAMETER(lpRectUpdate);
      throw interface_only_exception(get_app());
      return false;
   }

   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszInData);
      UNREFERENCED_PARAMETER(lpOutData);
      throw interface_only_exception(get_app());
      return -1;
   }

   // ::draw2d::graphics_sp 3.1 Specific functions
   UINT graphics::SetBoundsRect(const RECT &  lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception(get_app());
      return -1;
   }

   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      throw interface_only_exception(get_app());
      return -1;
   }

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID) && !defined(SOLARIS)

   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      UNREFERENCED_PARAMETER(lpDevMode);
      throw interface_only_exception(get_app());
      return false;
   }

#endif


#ifdef WINDOWSEX

   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) const
   {
      UNREFERENCED_PARAMETER(cbData);
      UNREFERENCED_PARAMETER(lpotm);
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpabc);
      throw interface_only_exception(get_app());
      return false;
   }

#endif

   uint32_t graphics::GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData,  uint32_t cbData) const
   {
      UNREFERENCED_PARAMETER(dwTable);
      UNREFERENCED_PARAMETER(dwOffset);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(cbData);
      throw interface_only_exception(get_app());
      return -1;
   }

#ifdef WINDOWSEX

   int32_t graphics::GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const
   {
      UNREFERENCED_PARAMETER(nPairs);
      UNREFERENCED_PARAMETER(lpkrnpair);
      throw interface_only_exception(get_app());
      return -1;
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
      return -1;
   }

   // ::user::document handling functions
   int32_t graphics::StartDoc(LPDOCINFO lpDocInfo)
   {
      UNREFERENCED_PARAMETER(lpDocInfo);
      throw interface_only_exception(get_app());
      return -1;
   }

#endif

   int32_t graphics::StartPage()
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::EndPage()
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {
      UNREFERENCED_PARAMETER(lpfn);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::AbortDoc()
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::EndDoc()
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
      int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask, uint32_t dwRop)
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
      return false;
   }
   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
      int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
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
      return false;
   }

   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nRadius);
      UNREFERENCED_PARAMETER(fStartAngle);
      UNREFERENCED_PARAMETER(fSweepAngle);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::ArcTo(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      throw interface_only_exception(get_app());
      return false;
   }

   int32_t graphics::GetArcDirection() const
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::PolyPolyline(const POINT* lpPoints, const uint32_t* lpPolyPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

#ifdef WINDOWSEX

   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {
      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception(get_app());
      return false;
   }

#endif

   ::draw2d::pen_sp graphics::get_current_pen() const
   {
      throw interface_only_exception(get_app());
      return NULL;
   }

   ::draw2d::brush_sp graphics::get_current_brush() const
   {
      throw interface_only_exception(get_app());
      return NULL;
   }

   ::draw2d::palette_sp graphics::get_current_palette() const
   {
      throw interface_only_exception(get_app());
      return NULL;
   }

   ::draw2d::font_sp graphics::get_current_font() const
   {
      throw interface_only_exception(get_app());
      return NULL;
   }

   ::draw2d::bitmap_sp graphics::get_current_bitmap() const
   {
      throw interface_only_exception(get_app());
      return NULL;
   }

   bool graphics::PolyBezier(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData, int32_t nOutputSize, char * lpszOutputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      UNREFERENCED_PARAMETER(nOutputSize);
      UNREFERENCED_PARAMETER(lpszOutputData);
      throw interface_only_exception(get_app());
      return -1;
   }

#ifdef WINDOWSEX

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpABCF);
      throw interface_only_exception(get_app());
      return false;
   }

#endif

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float * lpFloatBuffer) const
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpFloatBuffer);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::AbortPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::BeginPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::CloseFigure()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::EndPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::FillPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::FlattenPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   float graphics::GetMiterLimit() const
   {
      throw interface_only_exception(get_app());
      return false;
   }

   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount) const
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {
      UNREFERENCED_PARAMETER(fMiterLimit);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::StrokeAndFillPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::StrokePath()
   {
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::WidenPath()
   {
      throw interface_only_exception(get_app());
      return false;
   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      throw interface_only_exception(get_app());
      return false;

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      throw interface_only_exception(get_app());
      return false;

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      throw interface_only_exception(get_app());
      return false;

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      throw interface_only_exception(get_app());
      return false;

   }


   bool graphics::path(::draw2d::path * ppath)
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
      return false;
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const RECT &  lpBounds)
   {
      UNREFERENCED_PARAMETER(hEnhMF);
      UNREFERENCED_PARAMETER(lpBounds);
      throw interface_only_exception(get_app());
      return false;
   }

#endif

   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
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
      return false;
   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, uint32_t dwMode)
   {
      UNREFERENCED_PARAMETER(pVertices);
      UNREFERENCED_PARAMETER(nVertices);
      UNREFERENCED_PARAMETER(pMesh);
      UNREFERENCED_PARAMETER(nMeshElements);
      UNREFERENCED_PARAMETER(dwMode);
      throw interface_only_exception(get_app());
      return false;
   }

#ifdef WINDOWS

   COLORREF graphics::GetDCBrushColor() const
   {
      throw interface_only_exception(get_app());
      return 0;
   }

   COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return 0;
   }

   COLORREF graphics::GetDCPenColor() const
   {
      throw interface_only_exception(get_app());
      return 0;
   }

   COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception(get_app());
      return 0;
   }

#ifndef METROWIN

   bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpabc);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpBuffer);
      throw interface_only_exception(get_app());
      return false;
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
      return false;
   }

   bool graphics::GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, LPSIZE lpSize) const
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(lpSize);
      throw interface_only_exception(get_app());
      return false;
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

   ::draw2d::brush * graphics::GetHalftoneBrush()
   {
      throw interface_only_exception(get_app());
      return NULL;
   }

   // top of windows implementation

   void graphics::DrawDragRect(const RECT &  lpRect, SIZE size, const RECT &  lpRectLast, SIZE sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpRectLast);
      UNREFERENCED_PARAMETER(sizeLast);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(pBrushLast);
      throw interface_only_exception(get_app());
   }

   void graphics::FillSolidRect(const RECT &  lpRect, COLORREF clr)
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

   void graphics::Draw3dRect(const RECT &  lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
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
   // ::draw2d::graphics_sp

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
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int32_t graphics::StartDoc(const char * lpszDocName)
   {
      UNREFERENCED_PARAMETER(lpszDocName);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::SaveDC()
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::RestoreDC(int32_t nSavedDC)
   {
      UNREFERENCED_PARAMETER(nSavedDC);
      throw interface_only_exception(get_app());
      return false;
   }

   ::draw2d::object* graphics::SelectStockObject(int32_t nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception(get_app());
      return NULL;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen * pPen)
   {
      UNREFERENCED_PARAMETER(pPen);
      throw interface_only_exception(get_app());
      return NULL;
   }

   ::draw2d::brush* graphics::SelectObject(::draw2d::brush * pBrush)
   {
      UNREFERENCED_PARAMETER(pBrush);
      throw interface_only_exception(get_app());
      return NULL;
   }


   ::draw2d::font* graphics::SelectObject(::draw2d::font * pFont)
   {

      set_font(pFont);

      return m_spfont;

   }


   int32_t graphics::SelectObject(::draw2d::region * pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
      return -1;
   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette * pPalette, bool bForceBackground)
   {
      UNREFERENCED_PARAMETER(pPalette);
      UNREFERENCED_PARAMETER(bForceBackground);
      throw interface_only_exception(get_app());
      return NULL;
   }


   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {
      UNREFERENCED_PARAMETER(nPolyFillMode);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::SetROP2(int32_t nDrawMode)
   {
      UNREFERENCED_PARAMETER(nDrawMode);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {
      UNREFERENCED_PARAMETER(nStretchMode);
      throw interface_only_exception(get_app());
      return -1;
   }


   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception(get_app());
      return -1;
   }

#ifdef WINDOWS

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {
      UNREFERENCED_PARAMETER(pXform);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform, uint32_t iMode)
   {
      UNREFERENCED_PARAMETER(pXform);
      UNREFERENCED_PARAMETER(iMode);
      throw interface_only_exception(get_app());
      return false;
   }

#endif

   int32_t graphics::SetMapMode(int32_t nMapMode)
   {
      UNREFERENCED_PARAMETER(nMapMode);
      throw interface_only_exception(get_app());
      return -1;
   }

   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
      return null_point();
   }

   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
      return null_point();
   }

   size graphics::SetViewportExt(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
      return null_point();
   }

   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw interface_only_exception(get_app());
      return null_point();
   }

   size graphics::SetWindowExt(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   int32_t graphics::GetClipBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::GetClipBox(rect64 * lpRect) const
   {
      rect rect;
      int32_t iClip = GetClipBox(rect);
      rect64 rect64(rect);
      *lpRect = rect64;
      return iClip;
   }

   int32_t graphics::SelectClipRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::ExcludeClipRect(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::IntersectClipRect(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::OffsetClipRgn(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
      return -1;
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

      return LineTo((int32_t) x, (int32_t) y);

   }

   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UNREFERENCED_PARAMETER(nFlags);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {
      UNREFERENCED_PARAMETER(nBreakExtra);
      UNREFERENCED_PARAMETER(nBreakCount);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {
      UNREFERENCED_PARAMETER(nCharExtra);
      throw interface_only_exception(get_app());
      return -1;
   }

   uint32_t graphics::SetMapperFlags(uint32_t dwFlag)
   {
      UNREFERENCED_PARAMETER(dwFlag);
      throw interface_only_exception(get_app());
      return -1;
   }

   uint32_t graphics::GetLayout() const
   {
      throw interface_only_exception(get_app());
      return -1;
   }

   uint32_t graphics::SetLayout(uint32_t dwSetLayout)
   {
      UNREFERENCED_PARAMETER(dwSetLayout);
      throw interface_only_exception(get_app());
      return -1;
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
      return false;
   }

   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {
      UNREFERENCED_PARAMETER(nArcDirection);
      throw interface_only_exception(get_app());
      return -1;
   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::PolylineTo(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }


#ifdef WINDOWSEX


   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {

      UNREFERENCED_PARAMETER(lpColorAdjust);
      throw interface_only_exception(get_app());
      return false;

   }


#endif


   bool graphics::PolyBezierTo(const POINT* lpPoints, int32_t nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return false;
   }

   bool graphics::SelectClipPath(int32_t nMode)
   {
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception(get_app());
      return false;
   }

   int32_t graphics::SelectClipRgn(::draw2d::region* pRgn, int32_t nMode)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception(get_app());
      return -1;
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      UNREFERENCED_PARAMETER(hMF);
      throw interface_only_exception(get_app());
      return false;
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

      return GetTextExtent(lpszString, iIndex);

   }

   size graphics::GetTextExtent(const char * lpszString, strsize nCount) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::GetTextExtent(const string & str) const
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex) const
   {

      ::size sz = GetTextExtent(string(lpszString), iIndex);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount) const
   {

      ::size sz = GetTextExtent(string(lpszString), nCount);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   bool graphics::GetTextExtent(sized & size, const string & str) const
   {

      ::size sz = GetTextExtent(str);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount) const
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }

   size graphics::GetOutputTextExtent(const string & str) const
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
      return size(0, 0);
   }


   int32_t graphics::draw_text(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat)
   {

      return draw_text(string(lpszString, nCount), lpRect, nFormat);

   }


   int32_t graphics::draw_text(const string & str,const RECT & lpRect,UINT nFormat)
   {

      synch_lock ml(&user_mutex());

      size sz = GetTextExtent(str);

      double dx;

      double dy;

      if(nFormat & DT_RIGHT)
      {
         dx = lpRect.right - lpRect.left - sz.cx;
      }
      else if(nFormat & DT_CENTER)
      {
         dx = ((lpRect.right - lpRect.left) - (sz.cx)) / 2.0;
      }
      else
      {
         dx = 0.;
      }

      if(nFormat & DT_BOTTOM)
      {
         dy = lpRect.bottom - lpRect.top - sz.cy;
      }
      else if(nFormat & DT_VCENTER)
      {
         dy = ((lpRect.bottom - lpRect.top) - (sz.cy)) / 2.0;
      }
      else
      {
         dy = 0.;
      }

      TextOut(lpRect.left + dx, lpRect.top + dy, str);

      return 1;

   }


   int32_t graphics::draw_text(const char * lpszString,strsize nCount,const RECTD & lpRect,UINT nFormat)
   {

      return draw_text(string(lpszString,nCount),lpRect,nFormat);

   }


   int32_t graphics::draw_text(const string & str,const RECTD & lpRect,UINT nFormat)
   {

      synch_lock ml(&user_mutex());

      size sz = GetTextExtent(str);

      double dx;

      double dy;

      if(nFormat & DT_RIGHT)
      {
         dx = lpRect.right - lpRect.left - sz.cx;
      }
      else if(nFormat & DT_CENTER)
      {
         dx = ((lpRect.right - lpRect.left) - (sz.cx)) / 2.0;
      }
      else
      {
         dx = 0.;
      }

      if(nFormat & DT_BOTTOM)
      {
         dy = lpRect.bottom - lpRect.top - sz.cy;
      }
      else if(nFormat & DT_VCENTER)
      {
         dy = ((lpRect.bottom - lpRect.top) - (sz.cy)) / 2.0;
      }
      else
      {
         dy = 0.;
      }

      TextOut(lpRect.left + dx,lpRect.top + dy,str);

      return 1;

   }

#ifndef METROWIN

   int32_t graphics::draw_text_ex(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::draw_text_ex(const string & str,const RECT & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
      return -1;
   }
   int32_t graphics::draw_text_ex(const char * lpszString,strsize nCount,const RECTD & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
      return -1;
   }

   int32_t graphics::draw_text_ex(const string & str,const RECTD & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      throw interface_only_exception(get_app());
      return -1;
   }

#endif


   bool graphics::from(point ptDst, size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop)
   {
      return BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, dwRop) != FALSE;
   }

   bool graphics::from(size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, uint32_t dwRop)
   {
      return from(null_point(), size, pgraphicsSrc, ptSrc, dwRop);
   }

   bool graphics::from(size size, ::draw2d::graphics * pgraphicsSrc, uint32_t dwRop)
   {
      return from(size, pgraphicsSrc, null_point(), dwRop);
   }

   bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dOpacity)
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
      return false;
   }

   bool graphics::alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, double dOpacity)
   {
      return alpha_blend(ptDst.x, ptDst.y, szDst.cx, szDst.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, szSrc.cx, szSrc.cy, dOpacity);
   }

   bool graphics::alpha_blend(point ptDst, size size,::draw2d::graphics * pgraphicsSrc, point ptSrc, double dOpacity)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, ptSrc, size, dOpacity);
   }

   bool graphics::alpha_blend(point ptDst, size size,::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, null_point(), dOpacity);
   }

   bool graphics::alpha_blend(size size,::draw2d::graphics * pgraphicsSrc, point ptSrc, double dOpacity)
   {
      return alpha_blend(null_point(), size, pgraphicsSrc, ptSrc, dOpacity);
   }

   bool graphics::alpha_blend(size size,::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {
      return alpha_blend(size, pgraphicsSrc, null_point(), dOpacity);
   }


/*
   bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, BLENDFUNCTION blend)
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

/*   bool graphics::alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(ptDst.x, ptDst.y, szDst.cx, szDst.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, szSrc.cx, szSrc.cy, blend);
   }

   bool graphics::alpha_blend(point ptDst, size size,::draw2d::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, ptSrc, size, blend);
   }

   bool graphics::alpha_blend(point ptDst, size size,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(ptDst, size, pgraphicsSrc, null_point(),blend);
   }

   bool graphics::alpha_blend(size size,::draw2d::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(null_point(), size, pgraphicsSrc, ptSrc, blend);
   }

   bool graphics::alpha_blend(size size,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend)
   {
      return alpha_blend(size, pgraphicsSrc, null_point(), blend);
   }*/

   void graphics::set_alpha_mode(e_alpha_mode ealphamode)
   {
      m_ealphamode = ealphamode;
   }

   void graphics::set_text_rendering(e_text_rendering etextrendering)
   {
//      throw not_implemented(get_app());
   }

   bool graphics::blur(bool bExpand, double dRadius, const RECT & rect)
   {
      throw interface_only_exception(get_app());
      return false;
   }



   bool graphics::DrawLine(float x1, float y1, float x2, float y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      MoveTo(x1, y1);
      return LineTo(x2, y2);

   }

   bool graphics::drawLine(float x1, float y1, float x2, float y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2);

   }

   bool graphics::draw_line(float x1, float y1, float x2, float y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2);

   }


   bool graphics::DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return draw_line(x1, y1, x2, y2, ppen);

   }

   bool graphics::drawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2, ppen);

   }

   bool graphics::draw_line(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2, ppen);

   }



   bool graphics::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      MoveTo(x1, y1);
      return LineTo(x2, y2);

   }

   bool graphics::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2);

   }

   bool graphics::draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2);

   }


   bool graphics::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return draw_line(x1, y1, x2, y2, ppen);

   }

   bool graphics::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return DrawLine(x1, y1, x2, y2, ppen);

   }

   bool graphics::draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      return drawLine(x1, y1, x2, y2, ppen);

   }

   bool graphics::DrawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods
      DrawRect(rect(x1,y1,x2,y2),m_sppen);

      return true;

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



   bool graphics::DrawRect(const RECT & rect, ::draw2d::pen * ppen)
   {

      return draw_rect(rect, ppen);

   }

   bool graphics::drawRect(const RECT & rect, ::draw2d::pen * ppen)
   {

      return DrawRect(rect, ppen);

   }

   bool graphics::draw_rect(const RECT & rect, ::draw2d::pen * ppen)
   {

      return drawRect(rect, ppen);

   }



   pointd graphics::MoveTo(double x, double y)
   {
      double px = m_x;
      double py = m_y;
      m_x = x;
      m_y = y;
      return pointd(px, py);
   }


   void graphics::set_solid_pen(double dWidth, COLORREF cr)
   {

      if(m_sppen.is_null())
      {

         m_sppen.alloc(allocer());

      }

      m_sppen->create_solid(dWidth, cr);

   }

   memory_graphics::memory_graphics(allocatorsp allocer) :
      ::draw2d::graphics_sp(allocer)
   {
      ::draw2d::graphics_sp::m_p->CreateCompatibleDC(NULL);
   }

   memory_graphics::~memory_graphics()
   {

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
   bool graphics::draw_round_rect(const RECT & rect, ::draw2d::pen * ppen, int32_t radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->add_round_rect(rect, 2 * radius);

      path->end_figure(true);

      draw_path(path, ppen);

      return true;

   }


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
   bool graphics::draw_round_rect(const RECT & rect, COLORREF cr, int32_t radius, int32_t width)
   {

      RECT r = rect;

      int32_t dia = 2 * radius;

      ::draw2d::pen_sp pen(this, 1.0, cr);

      draw_round_rect(r, pen, radius);


      for (int32_t i = 1; i<width; i++)
      {
         dia++;

         // left stroke
         deflate_rect(r, 1, 0);

         draw_round_rect(r, pen, dia / 2);

         // up stroke
         deflate_rect(r, 0, 1);

         draw_round_rect(r, pen, dia / 2);

      }

      return true;

   }


   bool graphics::draw_round_top_left(const RECT & rect, ::draw2d::pen  * ppen, int32_t radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(false, ::draw2d::fill_mode_winding);

      path->add_round_top_left(rect, 2 * radius);

      path->end_figure(false);

      draw_path(path, ppen);

      return true;

   }


   bool graphics::draw_round_top_left(const RECT & rect, COLORREF cr, int32_t radius, int32_t width)
   {

      RECT r = rect;

      int32_t dia = 2 * radius;

      ::draw2d::pen_sp pen(this, 1.0, cr);

      draw_round_top_left(r, pen, radius);


      for (int32_t i = 1; i<width; i++)
      {
         dia++;

         // left stroke
         deflate_rect(r, 1, 0);

         draw_round_top_left(r, pen, dia / 2);

         // up stroke
         deflate_rect(r, 0, 1);

         draw_round_top_left(r, pen, dia / 2);

      }

      return true;

   }


   bool graphics::draw_round_bottom_right(const RECT & rect, ::draw2d::pen  * ppen, int32_t radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(false, ::draw2d::fill_mode_winding);

      path->add_round_bottom_right(rect, 2 * radius);

      path->end_figure(false);

      draw_path(path, ppen);

      return true;

   }


   bool graphics::draw_round_bottom_right(const RECT & rect, COLORREF cr, int32_t radius, int32_t width)
   {

      RECT r = rect;

      int32_t dia = 2 * radius;

      ::draw2d::pen_sp pen(this, 1.0, cr);

      draw_round_bottom_right(r, pen, radius);

      for (int32_t i = 1; i<width; i++)
      {

         dia++;

         // left stroke
         deflate_rect(r, 1, 0);

         draw_round_bottom_right(r, pen, dia / 2);

         // up stroke
         deflate_rect(r, 0, 1);

         draw_round_bottom_right(r, pen, dia / 2);

      }

      return true;

   }

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
   bool graphics::fill_round_rect(const RECT & r, COLORREF cr, int32_t radius)
   {

      ::draw2d::brush_sp br(allocer(), cr);

      return fill_round_rect(r, br, radius);

   }

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
   bool graphics::fill_round_rect(const RECT & rect, ::draw2d::brush * pbr, int32_t radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->add_round_rect(rect, 2 * radius);

      path->end_figure(true);

      fill_path(path, pbr);

      return true;

   }

   bool graphics::round_rect(const RECT & r, int32_t radius)
   {

      bool bOk1 = fill_round_rect(r, m_spbrush, radius);

      bool bOk2 = draw_round_rect(r, m_sppen, radius);

      return bOk1 && bOk2;

   }

   int32_t graphics::_DrawText(const string & str, const RECT & rect, UINT uiFormat, ::draw2d::font * pfontUnderline)
   {
      return _DrawText(str, str.get_length(), rect, uiFormat, pfontUnderline);
   }

   int32_t graphics::_DrawText(const char * lpcsz, strsize iCount, const RECT & rectParam, UINT uiFormat, ::draw2d::font * pfontUnderline)
   {

      text_metric tm2;

      get_text_metrics(&tm2);

      int iLineSpacing = tm2.tmHeight;

      ::draw2d::graphics * pdc = this;

      string strParam(lpcsz, iCount);

      wstring wstr = ::str::international::utf8_to_unicode(strParam);

      string str(lpcsz);

      string str2;

      rect rectClip(rectParam);

      if (rectClip.area() <= 0)
         return 0;

      size sz;

      sz.cx = 0;

      sz.cy = 0;

      strsize iUnderline = _EncodeV033(str);

      strsize iLen = str.get_length();

      if ((uiFormat & DT_END_ELLIPSIS) != 0)
      {
         sz = pdc->GetTextExtent(str, (int32_t)iLen);
         if (sz.cx > rectClip.width())
         {
            iLen += 3;
            char * lpsz = str.GetBuffer(iLen + 1);
            strsize i = sz.cx == 0 ? iLen : (iLen * rectClip.width()) / sz.cx;
            if (i > iLen)
               i = iLen;
            if (i < 4)
               i = 4;

            while (true)
            {
               lpsz[i - 4] = '.';
               lpsz[i - 3] = '.';
               lpsz[i - 2] = '.';
               lpsz[i - 1] = '\0';
               sz = pdc->GetTextExtent(lpsz, (int32_t)i);
               if (sz.cx < rectClip.width())
               {
                  if (i >= iLen)
                     break;
                  i++;
               }
               else
               {
                  break;
               }
               strncpy(lpsz, str, i);
            }
            while (true)
            {
               if (i <= 4)
                  break;
               lpsz[i - 4] = L'.';
               lpsz[i - 3] = L'.';
               lpsz[i - 2] = L'.';
               lpsz[i - 1] = L'\0';
               sz = pdc->GetTextExtent(lpsz, (int32_t)i);
               if (sz.cx > rectClip.width())
               {
                  i--;
               }
               else
               {
                  break;
               }
            }
            str.ReleaseBuffer();
            iLen = str.get_length();
         }
      }
      else if ((uiFormat & DT_WORDBREAK) != 0)
      {
         sz = pdc->GetTextExtent(str, (int32_t)iLen);
         if (sz.cx > rectClip.width())
         {
            word_break(pdc, lpcsz, rectClip, str, str2);
         }
      }
      else
      {
         sz = pdc->GetTextExtent(str, (int32_t)iLen);
         /*::GetTextExtentPoint32U(
         (HDC) pdc->get_os_data(),
         str,
         iLen,
         &sz);*/
         //         uint32_t dw = ::GetLastError();
         if (sz.cx > rectClip.width())
         {
            strsize i = iLen;
            if (i < 0)
               i = 0;
            char * lpsz = str.GetBuffer(max(0, i) + 1);
            while (i > 0)
            {
               sz = pdc->GetTextExtent(str, (int32_t)i);
               if (sz.cx > rectClip.width())
               {
                  i--;
                  if (i <= 0)
                     break;
               }
               else
               {
                  break;
               }
            }
            lpsz[i] = L'\0';
            str.ReleaseBuffer();
         }
      }

      if (str.is_empty())
         return 0;


      ::draw2d::font_sp fontUnderline;
      //      ::draw2d::font * pfont;


      if (iUnderline >= 0)
      {
         if (pfontUnderline == NULL)
         {
            fontUnderline.alloc(allocer());
            pfontUnderline = fontUnderline;
            fontUnderline ->operator=(*pdc->get_current_font());
            fontUnderline->set_bold();
         }
      }

      rect rect;
      rect.left = 0;
      rect.top = 0;
      rect.right = sz.cx;
      rect.bottom = iLineSpacing;

      int32_t align = 0;
      if (uiFormat & DT_BOTTOM)
      {
         align |= ::AlignBottom;
      }
      else if (uiFormat & DT_VCENTER)
      {
         align |= ::AlignVerticalCenter;
      }
      else
      {
         align |= ::AlignTop;
      }
      if (uiFormat & DT_RIGHT)
      {
         align |= ::AlignRight;
      }
      else if (uiFormat & DT_CENTER)
      {
         align |= ::AlignHorizontalCenter;
      }
      else
      {
         align |= ::AlignLeft;
      }

      rect.Align(align, rectParam);

      if (iUnderline >= 0 && iUnderline < str.get_length())
      {

         ::draw2d::font * pfontOld;

         pdc->TextOut(rect.left, rect.top, str, (int32_t)min(iUnderline, str.get_length()));
         /*::TextOutU(
         (HDC)pdc->get_os_data(),
         rect.left,
         rect.top,
         str,
         min(iUnderline, str.get_length()));*/
         if (iUnderline <= str.get_length())
         {
            ::draw2d::font fPrevious = *pdc->get_current_font();
            pfontOld = pdc->SelectObject(pfontUnderline);
            /*::GetTextExtentPoint32U(
            (HDC)pdc->get_os_data(),
            str,
            iUnderline,
            &sz);*/
            sz = pdc->GetTextExtent(str, (int32_t)iUnderline);
            char wch = str[iUnderline];
            /*::TextOutU(
            (HDC)pdc->get_os_data(),
            rect.left + sz.cx,
            rect.top,
            &wch,
            1);*/
            pdc->TextOut(rect.left + sz.cx, rect.top, &wch, 1);
            pdc->SelectObject(&fPrevious);
            if (iUnderline + 1 <= str.get_length())
            {
               sz = pdc->GetTextExtent(str, (int32_t)(iUnderline + 1));
               /*::GetTextExtentPoint32U(
               (HDC)pdc->get_os_data(),
               str,
               iUnderline + 1,
               &sz);*/
               strsize iCount = str.get_length() - iUnderline - 1;
               pdc->TextOut(rect.left + sz.cx, rect.top, str.Right(iCount), (int32_t)iCount);
               /*::TextOutU(
               (HDC)pdc->get_os_data(),
               rect.left + sz.cx,
               rect.top,
               str.Right(iCount),
               iCount);*/
            }
            pdc->SelectObject(pfontOld);
         }
      }
      else
      {
         pdc->TextOut(rect.left, rect.top, str);
      }

      if (str2.get_length() > 0)
      {

         rectClip.top += iLineSpacing;

         _DrawText(str2, str2.get_length(), rectClip, uiFormat);

      }

      return 1;

   }



   void word_break(::draw2d::graphics * pdc, const string & strSource, const RECT & rectParam, string &str1, string & str2)
   {

      string str;

      rect rectClip(rectParam);

      const char * lpszSource = strSource;

      strsize len = strSource.get_length();

      const char * lpszEnd = lpszSource + len;

//      index iFind = str.find(L' ');

      const char * lpszStart = ::str::utf8_inc(lpszSource);

      size sz;

      const char * lpszSpaceStart = NULL;
      const char * lpszSpaceEnd = NULL;

      const char * lpsz = lpszStart;

      const char * lpszPrevious = lpszSource;

      string strChar;

      while(lpsz <= lpszEnd)
      {

         sz = pdc->GetTextExtent(lpszSource, lpsz - lpszSource);

         if(::str::ch::is_space_char(lpszPrevious))
         {
            lpszSpaceStart       = lpszPrevious;
            do
            {
               lpszSpaceEnd      = lpsz;
               if(!::str::ch::is_space_char(lpsz))
               {
                  break;
               }
               lpszPrevious      = lpsz;
               lpsz              = ::str::utf8_inc(lpsz);
            } while(lpsz != NULL);
         }

         if (sz.cx > rectClip.width())
         {

            if(lpsz == lpszStart)
            {
               lpszEnd = lpszStart;
               break;
            }

            if(lpszSpaceStart != NULL)
            {
               // "legit" word break, i.meaning., found mid space in text and split there, instead of slicing a full word in a single-character (above) or the maximum-unclipped (below).
               lpsz = lpszSpaceStart;
               lpszEnd = lpszSpaceEnd;
               break;
            }

            lpsz = ::str::utf8_dec(lpszSource, lpsz);
            lpszEnd = lpsz;

            break;

         }

         lpszPrevious = lpsz;
         lpsz = ::str::utf8_inc(lpsz);

      }

      str1 = string(lpszSource, lpsz - lpszSource);

      str2 = string(lpszEnd);

   }


   strsize _EncodeV033(string & str)
   {
      strsize iStart = 0;
      strsize iIndex;
      strsize iLen = str.get_length();
      while (true)
      {
         iIndex = str.find(L'&', iStart);
         if (iIndex < 0)
            break;
         if (iIndex + 1 >= iLen)
            break;
         if (str[iIndex + 1] == L'&')
         {
            iIndex++;
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
         }
         else
         {
            // Found !
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
            return iIndex;
         }

         if (iIndex >= str.get_length())
            break;
      }
      // Not Found
      return -1;
   }


#ifdef WINDOWSEX


   bool graphics::Attach(HDC hdc)
   {

      throw not_implemented(get_app());

      return false;

   }


   HDC graphics::Detach()
   {

      throw not_implemented(get_app());

      return NULL;

   }


   bool graphics::AttachPrinter(HDC hdc)
   {

      throw not_implemented(get_app());

      return false;

   }


   HDC graphics::DetachPrinter()
   {

      throw not_implemented(get_app());

      return NULL;

   }

#endif
   
   bool graphics::draw_stock_icon(const RECT & rectParam, e_stock_icon eicon)
   {
      
      ::draw2d::pen_sp pen(allocer());
      ::draw2d::brush_sp brush(allocer());
      
      *pen = *m_sppen;
      *brush = *m_spbrush;
      
      ::rect rect(rectParam);
      
      if(eicon == stock_icon_close)
      {

         rect.deflate(rect.width() / 7,rect.height() / 7);
         
         m_sppen->m_dWidth *= 2.0;
         m_sppen->m_bUpdated = false;
         MoveTo(rect.top_left());
         LineTo(rect.bottom_right());
         MoveTo(rect.bottom_left());
         LineTo(rect.top_right());
         
      }
      else if(eicon == stock_icon_zoom)
      {
         
         rect.deflate(0, rect.height() / 7);

         draw_rect(rect.left,rect.top, rect.right, rect.bottom);
         
         m_sppen->m_elinecapBeg = ::draw2d::pen::line_cap_flat;
         m_sppen->m_elinecapEnd = ::draw2d::pen::line_cap_flat;
         MoveTo(rect.top_left() + size(0,(int64_t) (pen->m_dWidth/2.0)));
         LineTo(rect.top_right() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         MoveTo(rect.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         LineTo(rect.top_right() + size(0,(int64_t)(pen->m_dWidth)));
         MoveTo(rect.top_left() + size(0,(int64_t)(pen->m_dWidth *3.0 / 2.0)));
         LineTo(rect.top_right() + size(0,(int64_t)(pen->m_dWidth *3.0 / 2.0)));
         MoveTo(rect.top_left() + size(0,(int64_t)(pen->m_dWidth*2.0)));
         LineTo(rect.top_right() + size(0,(int64_t)(pen->m_dWidth*2.0)));

      }
      else if(eicon == stock_icon_restore)
      {
         
         rect.deflate(0, rect.height() / 7);
 
         ::rect rect1(rect);

         rect1.deflate(0, 0, rect.width() / 3, rect.height() / 3);
         
         ::rect rect2(rect1);
         
         rect2.Align(AlignBottom | AlignRight, rect);

         draw_rect(rect2.left,rect2.top,rect2.right,rect2.bottom);

         m_sppen->m_elinecapBeg = ::draw2d::pen::line_cap_flat;
         m_sppen->m_elinecapEnd = ::draw2d::pen::line_cap_flat;
         MoveTo(rect2.top_left() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         LineTo(rect2.top_right() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         MoveTo(rect2.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         LineTo(rect2.top_right() + size(0,(int64_t)(pen->m_dWidth)));


         MoveTo(rect1.top_left());
         LineTo(rect1.top_right());
         MoveTo(rect1.top_left() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         LineTo(rect1.top_right() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         MoveTo(rect1.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         LineTo(rect1.top_right() + size(0,(int64_t)(pen->m_dWidth)));



         m_sppen->m_elinecapBeg = ::draw2d::pen::line_cap_square;
         m_sppen->m_elinecapEnd = ::draw2d::pen::line_cap_square;
         m_sppen->m_bUpdated = false;
         MoveTo(rect1.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         LineTo(rect1.bottom_left());
         LineTo(rect2.left, rect1.bottom);

         MoveTo(rect1.top_right() + size(0,(int64_t)(pen->m_dWidth)));
         LineTo(rect1.right,(int)(rect2.top - (int64_t)(pen->m_dWidth)));
         
      }
      else if(eicon == stock_icon_iconify)
      {
         
         rect.deflate(0, rect.height() / 7);
         
         
         MoveTo(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth*2.0)));
         LineTo(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth*2.0)));
         MoveTo(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth*3.0 / 2.0)));
         LineTo(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth*3.0 / 2.0)));
         MoveTo(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth)));
         LineTo(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth)));
         MoveTo(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth / 2.0)));
         LineTo(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth / 2.0)));
         MoveTo(rect.bottom_left());
         LineTo(rect.bottom_right());
         
      }
      else if(eicon == stock_icon_dock)
      {
         
         rect.deflate(rect.height() / 8, rect.height() / 8);
         
         DrawEllipse(rect);

         ::rect rect1(rect);
         
         rect1.deflate((int32_t)(m_sppen->m_dWidth / 2.0),(int32_t)(m_sppen->m_dWidth / 2.0));

         DrawEllipse(rect1);

         ::rect rect2(rect);

         rect2.deflate((int32_t)(m_sppen->m_dWidth),(int32_t)(m_sppen->m_dWidth));

         DrawEllipse(rect2);

      }
      else
      {
         
         throw not_implemented(get_app());
         
      }
      
      *m_sppen = *pen;
      *m_spbrush = *brush;
      
      return true;
      
   }
   


} // namespace draw2d


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


