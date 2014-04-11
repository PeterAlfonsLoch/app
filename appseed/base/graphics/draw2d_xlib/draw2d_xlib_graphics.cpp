#include "framework.h"
#include <X11/Xft/Xft.h>
#include <math.h>

HDC CreateCompatibleDC(HDC hdc);

array < XChar2b > utf8toXChar2b(const char *input, int inlen);

namespace draw2d_xlib
{


   graphics::graphics(sp(base_application) papp) :
      element(papp),
      m_ui(papp)
   {

      m_bPrinting       = FALSE;
      m_pdibAlphaBlend  = NULL;
      m_pdc             = NULL;
/*      m_hdc             = NULL;
      m_ppath           = NULL;
      m_ppathPaint      = NULL;
      */
      m_etextrendering  = ::draw2d::text_rendering_anti_alias_grid_fit;

      m_spfont.create(allocer());
      m_spfont->m_strFontFamilyName = "Helvetica";
      m_spfont->m_dFontSize = 12.0;


      m_nStretchBltMode = HALFTONE;

   }

   graphics::graphics() :
      m_ui(NULL)
   {

      m_bPrinting       = FALSE;
      m_pdc             = NULL;
/*      m_pgraphics       = NULL;
      m_hdc             = NULL;
      m_ppath           = NULL;
      m_ppathPaint      = NULL;*/
      m_etextrendering  = ::draw2d::text_rendering_anti_alias_grid_fit;


      m_nStretchBltMode = HALFTONE;

   }


   void graphics::assert_valid() const
   {
      object::assert_valid();
   }

   void graphics::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

//      dumpcontext << "get_handle1() = " << get_handle1();
  //    dumpcontext << "\nm_hAttribDC = " << get_handle2();
    //  dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";
   }


   graphics::~graphics()
   {

      synch_lock ml(&user_mutex());

/*      HDC hdc = Detach();

      if(hdc != NULL)
      {
         bool bDeleted = ::DeleteDC(hdc) != FALSE;
         if(!bDeleted)
         {
            TRACE("Failed to delete GDI device context");
         }
      }*/

      if(m_pdc != NULL)
      {
//	if(m_pdc ==  xlib_keep::g_xlib)
	//{
     //    printf("123");

	//}
     //    xlib_destroy(m_pdc);
         m_pdc = NULL;
      }

/*      if(m_ppath != NULL)
      {
         delete m_ppath;
         m_ppath = NULL;
      }

      if(m_ppathPaint != NULL)
      {
         delete m_ppathPaint;
         m_ppathPaint = NULL;
      }*/

   }


/*   sp(::user::window) graphics::GetWindow() const
   {
      ASSERT(get_handle1() != NULL); return ::win::window::from_handle(::WindowFromDC(get_handle1()));
   }
*/

   bool graphics::IsPrinting() const
   {
      return m_bPrinting;
   }

   bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      throw not_supported_exception(get_app());
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }

   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      throw not_supported_exception(get_app());
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
   }

   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      synch_lock ml(&user_mutex());

      if(m_pdc != NULL)
      {
//	if(m_pdc ==  xlib_keep::g_xlib)
	//{
     ///    printf("123");

	//}

         DeleteDC();

         m_pdc = NULL;

      }

      if(pgraphics == NULL)
      {

//         xlib_surface_t * psurface = xlib_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);

//         if(psurface == NULL)
  //          return false;

    //     m_pdc = xlib_create(psurface);

//if(psurface == xlib_keep::g_xlibsurface)
//{
  // printf("123");
//}         xlib_surface_destroy(psurface);


         m_spbitmap.create(allocer());

         m_spbitmap->CreateCompatibleBitmap(this, 256, 256);

         SelectObject(m_spbitmap);

         return m_pdc != NULL;

      }
      else
      {

         m_pdc = ::CreateCompatibleDC((HDC) pgraphics->get_os_data());

  /*       xlib_surface_t * psurface = xlib_get_target((xlib_t *) pgraphics->get_os_data());

         if(xlib_surface_status(psurface) != CAIRO_STATUS_SUCCESS)
            return false;

         xlib_surface_t * psurfaceNew = xlib_surface_create_similar(psurface, xlib_surface_get_content(psurface), 1, 1);

         if(psurfaceNew == NULL)
            return false;
if(psurfaceNew == xlib_keep::g_xlibsurface)
{
   printf("123");
}
         m_pdc = xlib_create(psurfaceNew);

         xlib_surface_destroy(psurfaceNew);*/

         return m_pdc != NULL;

      }
/*
      HDC hdc = NULL;

      if(pgraphics == NULL)
      {
         hdc = ::CreateCompatibleDC(NULL);
      }
      else
      {
         hdc = ::CreateCompatibleDC((HDC)(dynamic_cast<::win::graphics * >(pgraphics))->get_handle1());
      }

      if(!Attach(hdc))
      {
         ::DeleteDC(hdc);
         return FALSE;
      }
      */

      return true;

   }


   int32_t graphics::ExcludeUpdateRgn(::window * pWnd)
   {

//       ASSERT(get_handle1() != NULL);
//       return ::ExcludeUpdateRgn(get_handle1(), WIN_WINDOW(pWnd)->get_handle());
         throw not_implemented(get_app());
         return 0;

   }


   int32_t graphics::GetDevicecaps(int32_t nIndex) const
   {
/*      ASSERT(get_handle2() != NULL);
      return ::GetDevicecaps(get_handle2(), nIndex);*/
         throw not_implemented(get_app());
         return 0;
   }

   point graphics::GetBrushOrg() const
   {
/*      ASSERT(get_handle1() != NULL);
      POINT point;
      VERIFY(::GetBrushOrgEx(get_handle1(), &point));
      return point;*/
         throw not_implemented(get_app());
         return point(0, 0);

   }

   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {
/*      ASSERT(get_handle1() != NULL);
      POINT point;
      VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
      return point;*/
         throw not_implemented(get_app());
         return point(0, 0);

   }

   point graphics::SetBrushOrg(POINT point)
   {
/*      ASSERT(get_handle1() != NULL);
      VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
      return point;*/
         throw not_implemented(get_app());
         return ::point(0, 0);

   }

   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
/*      ASSERT(get_handle2() != NULL);
      return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);*/
         throw not_implemented(get_app());
         return 0;

   }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap * pbitmapParam)
   {

      if(pbitmapParam == NULL)
         return NULL;

      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (pbitmapParam);

      if(pbitmap == NULL)
         return NULL;

/*      if(get_handle1() == NULL)
         return NULL;
      if(pbitmap == NULL)
         return NULL;
      return dynamic_cast < ::draw2d::bitmap* > (SelectGdiObject(get_app(), get_handle1(), pbitmap->get_os_data()));*/
      if(m_pdc != NULL)
      {

         DeleteDC();

      }

      //m_pdc = xlib_create((xlib_surface_t *) pbitmap->get_os_data());

      m_pdc                = new device_context();

      m_pdc->m_pdisplay    = pbitmap->m_ui.m_window->display();

      m_pdc->m_pixmap      = pbitmap->m_pixmap;

      m_pdc->m_drawable    = m_pdc->m_pixmap;

      ::XGCValues values;

      values.background    = 1;

      values.fill_rule     = WindingRule;

      m_pdc->m_gc          = ::XCreateGC(m_pdc->m_pdisplay, m_pdc->m_drawable, GCBackground | GCFillRule, &values);

      set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      m_spbitmap = pbitmap;

      return m_spbitmap;
   }


   ::draw2d_xlib::object* graphics::SelectObject(draw2d_xlib::object* pObject)
   {
   /*      ASSERT(get_handle1() != NULL);
      if(pObject == NULL)
         return NULL;
      return SelectGdiObject(get_app(), get_handle1(), pObject->get_os_data()); */
      return NULL;
   }

/*   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
   {

      UINT uiType = GetObjectType(hObject);

      if(uiType == OBJ_BITMAP)
      {

         HBITMAP hbitmap = (HBITMAP) hObject;

         if(m_spbitmap.is_null())
            m_spbitmap.create(get_app());

         if(m_spbitmap.is_null())
            return NULL;

         (dynamic_cast < ::win::bitmap * > (m_spbitmap.m_p))->m_pbitmap = new Gdiplus::Bitmap(hbitmap, NULL);

         if(m_pgraphics != NULL)
         {
            delete m_pgraphics;
         }

         m_pgraphics = new Gdiplus::Graphics((Gdiplus::Bitmap *) m_spbitmap->get_os_data());

         set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

         return hbitmap;

      }

      //*ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object
      //return (hObject != NULL) ? ::SelectObject(get_handle1(), hObject) : NULL; */
  /*    return NULL;
   }*/

   COLORREF graphics::GetNearestColor(COLORREF crColor) const
   {
      //throw not_implemented(get_app());
      return crColor;
//      return ::GetNearestColor(get_handle2(), crColor);
   }

   UINT graphics::RealizePalette()
   {
//      return ::RealizePalette(get_handle1());
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(get_handle1());

   }

   int32_t graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(get_handle2());
//      return xlib_get_fill_rule(m_pdc) == CAIRO_FILL_RULE_WINDING ? ::draw2d::fill_mode_winding : ::draw2d::fill_mode_alternate;
      return ::draw2d::fill_mode_winding;
   }

   int32_t graphics::GetROP2() const
   {
      //return ::GetROP2(get_handle2());
      return 0;
   }

   int32_t graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(get_handle2());
      return 0;
   }

   int32_t graphics::GetMapMode() const
   {
      //return ::GetMapMode(get_handle2());
      return 0;
   }

   int32_t graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(get_handle2());
      return 0;
   }

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {

      //return ::GetWorldTransform(get_handle2(),pXform) != FALSE;
      return 0;

   }

   size graphics::GetViewportExt() const
   {
      /*SIZE size;
      ::GetViewportExtEx(get_handle2(), &size);
      return size;*/

      return ::size(0, 0);
   }

   point graphics::GetWindowOrg() const
   {
      /*POINT point;
      ::GetWindowOrgEx(get_handle2(), &point);
      return point;*/
      return ::point(0, 0);
   }

   size graphics::GetWindowExt() const
   {
      /*SIZE size;
      ::GetWindowExtEx(get_handle2(), &size);
      return size;*/
      return ::size(0, 0);
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {

      m_pdc->m_pt = point;

      return m_pdc->m_pt;

   }


   size graphics::SetViewportExt(SIZE size)
   {
      //return SetViewportExt(size.cx, size.cy);
      return ::size(0, 0);
   }

   point graphics::SetWindowOrg(POINT point)
   {
      //return SetWindowOrg(point.x, point.y);
      return ::point(0, 0);
   }

   size graphics::SetWindowExt(SIZE size)
   {
      //return SetWindowExt(size.cx, size.cy);
      return ::size(0, 0);
   }

   void graphics::DPtoLP(LPPOINT lpPoints, int32_t nCount) const
   {
      //::DPtoLP(get_handle2(), lpPoints, nCount);
   }

   void graphics::DPtoLP(LPRECT lpRect) const
   {
      //::DPtoLP(get_handle2(), (LPPOINT)lpRect, 2);
   }

   void graphics::LPtoDP(LPPOINT lpPoints, int32_t nCount) const
   {
      //::LPtoDP(get_handle2(), lpPoints, nCount);
   }

   void graphics::LPtoDP(LPRECT lpRect) const
   {
      //::LPtoDP(get_handle2(), (LPPOINT)lpRect, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      throw not_implemented(get_app());
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != FALSE;
      return false;

   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {

//      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != FALSE;
      throw not_implemented(get_app());
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

  //    ASSERT(get_handle1() != NULL);

//      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != FALSE;
      throw not_implemented(get_app());
      return false;


   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

//      ASSERT(get_handle1() != NULL);

  //    return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != FALSE;
      throw not_implemented(get_app());
      return false;

   }

   bool graphics::PtVisible(int32_t x, int32_t y) const
   {

  //    ASSERT(get_handle1() != NULL);

//      return ::PtVisible(get_handle1(), x, y) != FALSE;
      throw not_implemented(get_app());
      return false;

   }

   bool graphics::PtVisible(POINT point) const
   {

//      ASSERT(get_handle1() != NULL);

//      return PtVisible(point.x, point.y);

      throw not_implemented(get_app());
      return false;

   }

   bool graphics::RectVisible(LPCRECT lpRect) const
   {

//      ASSERT(get_handle1() != NULL);

//      return ::RectVisible(get_handle1(), lpRect) != FALSE;

      throw not_implemented(get_app());
      return false;

   }

   point graphics::GetCurrentPosition() const
   {
//      ASSERT(get_handle2() != NULL);
//      POINT point;
//      VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
//      return point;
      throw not_implemented(get_app());
      return ::point(0, 0);

   }

   bool graphics::Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;
      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      double start      = atan2(y3 - centery, x3 - centerx);
      double end        = atan2(y4 - centery, x4 - centerx);


/*      xlib_keep keep(m_pdc);

      xlib_translate(m_pdc, centerx, centery);

      xlib_scale(m_pdc, radiusx, radiusy);

      xlib_arc(m_pdc, 0.0, 0.0, 1.0, start, end);*/

      return true;

   }

   bool graphics::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {

      return Arc(
                 lpRect->left,
                 lpRect->top,
                 lpRect->right,
                 lpRect->bottom,
                 ptStart.x,
                 ptStart.y,
                 ptEnd.x,
                 ptEnd.y);

   }

   bool graphics::Polyline(const POINT* lpPoints, int32_t nCount)
   {

      /*ASSERT(get_handle1() != NULL);

      return ::Polyline(get_handle1(), lpPoints, nCount) != FALSE;*/

      throw not_implemented(get_app());
      return false;

   }

   void graphics::FillRect(LPCRECT lpRect, ::draw2d::brush* pBrush)
   {

      set(pBrush);

      XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
         lpRect->left + m_pdc->m_ptOffset.x, lpRect->top + m_pdc->m_ptOffset.y,
         width(lpRect), height(lpRect));
//      throw not_implemented(get_app());
  //    return;

//      ASSERT(get_handle1() != NULL); ::FillRect(get_handle1(), lpRect, (HBRUSH)pBrush->get_os_data());

   }
   void graphics::FrameRect(LPCRECT lpRect, ::draw2d::brush* pBrush)
   {

      throw not_implemented(get_app());
      return;

//       ASSERT(get_handle1() != NULL); ::FrameRect(get_handle1(), lpRect, (HBRUSH)pBrush->get_os_data());

   }


   bool graphics::DrawRect(LPCRECT lpRect, ::draw2d::pen * ppen)
   {

      return DrawRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ppen);

   }


   bool graphics::DrawRect(int x1, int y1, int x2, int y2, ::draw2d::pen * ppen)
   {

      set(ppen);

      XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
         x1 + m_pdc->m_ptOffset.x, y1 + m_pdc->m_ptOffset.y,
         x2 - x1 - 1, y2 - y1 -1);

      return true;

   }


   void graphics::InvertRect(LPCRECT lpRect)
   {

      throw not_implemented(get_app());
      return;

//      ASSERT(get_handle1() != NULL); ::InvertRect(get_handle1(), lpRect);

   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon)
   {

      throw not_implemented(get_app());
      return false;


  //    ASSERT(get_handle1() != NULL);

    //  if(picon == NULL)
      //   return false;

//      return ::DrawIcon(get_handle1(), x, y, (HICON) picon->m_picon) != FALSE;

   }

   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {

      throw not_implemented(get_app());
      return false;
/*      ASSERT(get_handle1() != NULL);

      if(picon == NULL)
         return false;

      return ::DrawIcon(get_handle1(), point.x, point.y, (HICON) picon->m_picon) != FALSE;*/

   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {


   #ifdef WINDOWS

      try
      {

         if(picon == NULL)
            return FALSE;

         if(m_pdc == NULL)
            return FALSE;

         if(cx <= 0 || cx <= 0)
            return false;


         bool bOk = FALSE;

         BITMAPINFO info;
         COLORREF * pcolorref;

         ZeroMemory(&info, sizeof (BITMAPINFO));

         info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
         info.bmiHeader.biWidth         = cx;
         info.bmiHeader.biHeight        = - cy;
         info.bmiHeader.biPlanes        = 1;
         info.bmiHeader.biBitCount      = 32;
         info.bmiHeader.biCompression   = BI_RGB;
         info.bmiHeader.biSizeImage     = cx * cy * 4;

         HBITMAP hbitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void **) &pcolorref, NULL, 0);

         HDC hdc = ::CreateCompatibleDC(NULL);

         HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, NULL, DI_IMAGE | DI_MASK))
         {

            ::SelectObject(hdc, hbitmapOld);

            try
            {

               //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (BYTE *) pcolorref);

               ::draw2d::bitmap_sp b(allocer());

               b->CreateBitmap(this, cx, cy, 1, 32, pcolorref, cx * sizeof(COLORREF));

               xlib_surface_t * psurface = (xlib_surface_t *) b->get_os_data();

               if(psurface == NULL)
                  return false;

               xlib_pattern_t * ppattern = xlib_pattern_create_for_surface(psurface);

               if(ppattern == NULL)
                  return false;

               xlib_matrix_t matrix;

               xlib_matrix_t matrixOld;

               xlib_keep keep(m_pdc);

               xlib_translate(m_pdc, x, y);

               xlib_pattern_get_matrix(ppattern, &matrixOld);

               xlib_matrix_init_translate(&matrix, 0, 0);

               xlib_pattern_set_matrix(ppattern, &matrix);

               xlib_rectangle(m_pdc, 0, 0, cx, cy);

               xlib_clip(m_pdc);

               xlib_set_source(m_pdc, ppattern);

               xlib_paint(m_pdc);

               xlib_pattern_set_matrix(ppattern, &matrixOld);

               xlib_pattern_destroy(ppattern);
            }
            catch(...)
            {
            }

         }

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);

         return bOk;

      }
      catch(...)
      {
      }

      #endif

      return false;
   }

   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)pBitmap->get_os_data(), 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

/*   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }


   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }*/

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, HBRUSH hBrush)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), hBrush,  NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::draw2d::brush* pBrush)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

/*

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

   }

*/

   bool graphics::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::DrawEdge(get_handle1(), lpRect, nEdge, nFlags) != FALSE;

   }

   bool graphics::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
   {

      throw not_implemented(get_app());
      return false;
//      ASSERT(get_handle1() != NULL);
//      return ::DrawFrameControl(get_handle1(), lpRect, nType, nState) != FALSE;

   }

   bool graphics::Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
   }

   bool graphics::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {

      throw not_implemented(get_app());
      return false;

      //ASSERT(get_handle1() != NULL);
      //return ::Chord(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;

   }

   void graphics::DrawFocusRect(LPCRECT lpRect)
   {

      throw not_implemented(get_app());

      //ASSERT(get_handle1() != NULL); ::DrawFocusRect(get_handle1(), lpRect);

   }

   bool graphics::DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      ::XDrawArc(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1, 0, 360 * 64);

/*      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;
      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      xlib_translate(m_pdc, centerx, centery);

      xlib_scale(m_pdc, radiusx, radiusy);

      xlib_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.pulse();

      set(m_sppen);

      xlib_stroke(m_pdc);*/

      return true;

   }

   bool graphics::DrawEllipse(LPCRECT lprect)
   {

      return DrawEllipse(lprect->left, lprect->top, lprect->right, lprect->bottom);

      /*return ::Ellipse(get_handle1(), lpRect->left, lpRect->top,
   lpRect->right, lpRect->bottom); */


   }

   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      ::XFillArc(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1, 0, 360 * 64);

      /*double centerx    = (x2 + x1) / 2.0;

      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;

      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;


      xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      xlib_translate(m_pdc, centerx, centery);

      xlib_scale(m_pdc, radiusx, radiusy);

      xlib_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.restore();

      fill();*/


      return true;

   }


   bool graphics::FillEllipse(LPCRECT lpRect)
   {

      /*return ::Ellipse(get_handle1(), lpRect->left, lpRect->top,
   lpRect->right, lpRect->bottom); */

      return FillEllipse(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);

   }

   bool graphics::Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      throw not_implemented(get_app());
      return false;

/*      ASSERT(get_handle1() != NULL);
      return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;*/

   }

   bool graphics::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {

      throw not_implemented(get_app());
      return false;


/*      ASSERT(get_handle1() != NULL);
      return ::Pie(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;*/

   }

   bool graphics::fill_polygon(const POINTD * pa, int32_t iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(int32_t i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_ptOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_ptOffset.y;

      }

      //set(m_sppen);

      set(m_spbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      delete xpa;

      return true;

   }

   bool graphics::fill_polygon(const POINT* pa, int32_t iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(int32_t i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_ptOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_ptOffset.y;

      }

      //set(m_sppen);

      set(m_spbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::draw_polygon(const POINTD * pa, int32_t iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(int32_t i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_ptOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_ptOffset.y;

      }

      set(m_sppen);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::draw_polygon(const POINT* pa, int32_t iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(int32_t i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_ptOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_ptOffset.y;

      }

      set(m_sppen);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::Polygon(const POINT* pa, int32_t iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(int32_t i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_ptOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_ptOffset.y;

      }

      set(m_sppen);

      set(m_spbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int32_t nCount)
   {

      throw not_implemented(get_app());
      return false;
   //   ASSERT(get_handle1() != NULL); return ::PolyPolygon(get_handle1(), lpPoints, lpPolyCounts, nCount) != FALSE;

   }

   bool graphics::Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

/*      Gdiplus::RectF rectf((Gdiplus::REAL) x1, (Gdiplus::REAL) y1, (Gdiplus::REAL) (x2 - x1), (Gdiplus::REAL) (y2 - y1));

      bool bOk1 = m_pgraphics->FillRectangle(gdiplus_brush(), rectf) == Gdiplus::Status::Ok;

      bool bOk2 = m_pgraphics->DrawRectangle(gdiplus_pen(), rectf) == Gdiplus::Status::Ok;

      return bOk1 && bOk2;*/

      set(m_spbrush);

      ::XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1 + m_pdc->m_ptOffset.x, y1 + m_pdc->m_ptOffset.y, x2 - x1, y2 - y1);

      set(m_sppen);

      ::XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1 + m_pdc->m_ptOffset.x, y1 + m_pdc->m_ptOffset.y, x2 - x1 - 1, y2 - y1 - 1);

      return true;




   }

   bool graphics::Rectangle(LPCRECT lpRect)
   {

      return Rectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);

   }

   bool graphics::DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      set(m_sppen);

      set(m_spbrush);

      ::XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1);

      return true;

   }

   bool graphics::DrawRectangle(LPCRECT lpRect)
   {

      return DrawRectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);

   }

   bool graphics::FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      set(m_sppen);

      set(m_spbrush);

      ::XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1);

      return true;

   }

   bool graphics::FillRectangle(LPCRECT lpRect)
   {

      return FillRectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);

   }

   bool graphics::RoundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::RoundRect(get_handle1(), x1, y1, x2, y2, x3, y3) != FALSE;

   }

   bool graphics::RoundRect(LPCRECT lpRect, POINT point)
   {

      //ASSERT(get_handle1() != NULL);
      //return ::RoundRect(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, point.x, point.y) != FALSE;
      throw not_implemented(get_app());
      return false;


   }

   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop)
   {

//      ASSERT(get_handle1() != NULL);
//      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != FALSE;

      throw not_implemented(get_app());
      return false;


   }


   bool graphics::BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop)
   {

      synch_lock ml(&user_mutex());

      if(m_pdibAlphaBlend != NULL)
      {
         throw not_implemented(get_app());

         /*rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());


         ::draw2d::dib * pdibWork = NULL;
         ::draw2d::dib * pdibWork2 = NULL;
//         ::draw2d::dib * pdibWork3 = NULL;
         ::draw2d::dib * pdibWork4 = NULL;


         class point ptSrc(xSrc, ySrc);
         class point ptDest(x, y);
         class size size(nWidth, nHeight);



         ::draw2d::dib_sp spdib;
         if(pdibWork == NULL)
         {
            spdib.create(get_app());
            pdibWork = spdib;
         }
         if(pdibWork == NULL)
            return false;
         if(!pdibWork->create(size))
            return false;

         pdibWork->Fill(0, 0, 0, 0);

         pdibWork->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
            return false;




         ::draw2d::dib_sp spdib2;
         if(pdibWork2 == NULL)
         {
            spdib2.create(get_app());
            pdibWork2 = spdib2;
         }


         ::draw2d::dib_sp spdib4;
         if(pdibWork4 == NULL)
         {
            spdib4.create(get_app());
            pdibWork4 = spdib4;
         }
         if(pdibWork4 == NULL)
            return false;
         if(!pdibWork4->create(size))
            return false;


         pdibWork4->Fill(255, 0, 0, 0);

         pdibWork4->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         pdibWork4->from(point(max(0, m_ptAlphaBlend.x - x), max(0, m_ptAlphaBlend.y - y)),
            m_pdibAlphaBlend->get_graphics(), point(max(0, x - m_ptAlphaBlend.x), max(0, y - m_ptAlphaBlend.y)),
                               class size(max(0, m_pdibAlphaBlend->width() - max(0, x - m_ptAlphaBlend.x)), max(0, m_pdibAlphaBlend->height() - max(0, y - m_ptAlphaBlend.y))));

         pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);

         /*pdibWork->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         pdibWork->from(point(max(0, m_ptAlphaBlend.x - x), max(0, m_ptAlphaBlend.y - y)),
            m_pdibAlphaBlend->get_graphics(), point(max(0, x - m_ptAlphaBlend.x), max(0, y - m_ptAlphaBlend.y)),
                               class size(max(0, size.cx - max(0, x - m_ptAlphaBlend.x)), max(0, size.cy - max(0, y - m_ptAlphaBlend.y))));*/

         //keeper < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);

         /*Gdiplus::CompositingMode mode = m_pgraphics->GetCompositingMode();

         //m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         bool bOk = m_pgraphics->DrawImage(
            (Gdiplus::Bitmap *) pdibWork->get_graphics()->get_current_bitmap()->get_os_data(),
            x, y , 0, 0, nWidth, nHeight, Gdiplus::UnitPixel) == Gdiplus::Status::Ok;


         m_pgraphics->SetCompositingMode(mode);

         return bOk;

         //return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), null_point());
*/

      }


      try
      {

         if(pgraphicsSrc == NULL)
            return false;

         if(nWidth <= 0 || nHeight <= 0)
            return false;

         ::draw2d_xlib::graphics * psrc = dynamic_cast < ::draw2d_xlib::graphics * > (pgraphicsSrc);

         if(psrc == NULL)
            return false;

         if(psrc->m_spbitmap.is_null())
            return false;

         XCopyArea(m_pdc->m_pdisplay, psrc->m_pdc->m_drawable, m_pdc->m_drawable, m_pdc->m_gc,
            xSrc + m_pdc->m_ptOffset.x,
            ySrc + m_pdc->m_ptOffset.y,
            nWidth,
            nHeight,
            x + m_pdc->m_ptOffset.x,
            y + m_pdc->m_ptOffset.y);

         return true;

      }
      catch(...)
      {

         return false;

      }

      //return ::BitBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, dwRop);

   }


   bool graphics::StretchBlt(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop)
   {

      return false;

/*      synch_lock ml(&user_mutex());

      if(pgraphicsSrc == NULL)
         return false;

      if(nSrcWidth <= 0 || nSrcHeight <= 0 || nDstWidth <= 0 || nDstHeight <= 0)
         return false;

         if(pgraphicsSrc == NULL)
            return false;

         xlib_surface_t * psurface = xlib_get_target((xlib_t *) pgraphicsSrc->get_os_data());

         if(psurface == NULL)
            return false;

         xlib_pattern_t * ppattern = xlib_pattern_create_for_surface(psurface);

         if(ppattern == NULL)
            return false;

         xlib_matrix_t matrix;

         xlib_matrix_t matrixOld;

         xlib_pattern_get_matrix(ppattern, &matrixOld);

         xlib_keep keep(m_pdc);

         xlib_translate(m_pdc, xDst, yDst);

         xlib_matrix_init_translate(&matrix, -xSrc, -ySrc);

         xlib_matrix_scale(&matrix, (double) nSrcWidth / (double) nDstWidth, (double) nSrcHeight / (double) nDstHeight);

         xlib_pattern_set_matrix(ppattern, &matrix);

         xlib_rectangle(m_pdc, 0, 0, nDstWidth, nDstHeight);

         xlib_clip(m_pdc);

         xlib_set_source(m_pdc, ppattern);

         if(m_nStretchBltMode == 0)
         {
            xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_NEAREST);
         }
         else if(m_nStretchBltMode == HALFTONE)
         {
            xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_GOOD);
         }
         else
         {
            xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_FAST);
         }

         xlib_paint(m_pdc);

         xlib_pattern_set_matrix(ppattern, &matrixOld);

         xlib_pattern_destroy(ppattern);


      return true;*/

      //return ::StretchBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);

   }


   COLORREF graphics::GetPixel(int32_t x, int32_t y) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GetPixel(get_handle1(), x, y);

   }

   COLORREF graphics::GetPixel(POINT point) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GetPixel(get_handle1(), point.x, point.y);

   }

   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::SetPixel(get_handle1(), x, y, crColor);

   }

   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::SetPixel(get_handle1(), point.x, point.y, crColor);

   }

   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::FloodFill(get_handle1(), x, y, crColor) != FALSE;

   }

   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::ExtFloodFill(get_handle1(), x, y, crColor, nFillType) != FALSE;

   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::TextOut(int32_t x, int32_t y, const string & str)
   {

      if(m_pdibAlphaBlend != NULL)
      {
         throw not_implemented(get_app());
         //if(GetBkMode() == TRANSPARENT)
/*         {
         //   return TRUE;
            rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
            rect rectText(point(x, y), GetTextExtent(str));
            if(rectIntersect.intersect(rectIntersect, rectText))
            {
               /*::draw2d::dib_sp dib0(get_app());
               dib0->create(rectText.size());
               dib0->Fill(0, 0, 0, 0);
               dib0->get_graphics()->SetTextColor(ARGB(255, 255, 255, 255));
               dib0->get_graphics()->SelectObject(&get_current_font());
               dib0->get_graphics()->SetBkMode(TRANSPARENT);
               dib0->get_graphics()->TextOut(0, 0, str);
               dib0->ToAlpha(0);*/
  /*             ::draw2d::dib_sp dib1(get_app());
               dib1->create(rectText.size());
               dib1->Fill(0, 0, 0, 0);
//               dib1->get_graphics()->set_color(m_crColor);
               dib1->get_graphics()->SelectObject(&get_current_font());
               dib1->get_graphics()->SetBkMode(TRANSPARENT);
               dib1->get_graphics()->TextOut(0, 0, str);
               //dib1->channel_from(visual::rgba::channel_alpha, dib0);
               ::draw2d::dib_sp dib2(get_app());
               dib2->create(rectText.size());
               dib2->Fill(255, 0, 0, 0);
               dib2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               dib2->from(point(max(0, m_ptAlphaBlend.x - x), max(0, m_ptAlphaBlend.y - y)),
                  m_pdibAlphaBlend->get_graphics(), point(max(0, x - m_ptAlphaBlend.x), max(0, y - m_ptAlphaBlend.y)),
                  size(max(0, m_pdibAlphaBlend->width()-max(0, x - m_ptAlphaBlend.x)),
                        max(0, m_pdibAlphaBlend->height()-max(0, y - m_ptAlphaBlend.y))));
               dib1->channel_multiply(visual::rgba::channel_alpha, dib2);
               /*::draw2d::dib_sp dib3(get_app());
               dib1->mult_alpha(dib3);*/

    /*           keeper < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);

               return System.imaging().true_blend(this, point(x, y), rectText.size(), dib1->get_graphics(), null_point());

               /*BLENDFUNCTION bf;
               bf.BlendOp     = AC_SRC_OVER;
               bf.BlendFlags  = 0;
               bf.SourceConstantAlpha = 0xFF;
               bf.AlphaFormat = AC_SRC_ALPHA;
               return ::AlphaBlend(get_handle1(), x, y,
                  rectText.width(), rectText.height(), WIN_HDC(dib1->get_graphics()), 0, 0, rectText.width(),
                  rectText.height(), bf) != FALSE; */
      //      }
        // }
      }

      //ASSERT(get_handle1() != NULL);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      return TextOut(x, y, str, (int32_t) str.get_length());

   } // call virtual

   bool graphics::TextOut(double x, double y, const string & str)
   {
      if(m_pdibAlphaBlend != NULL)
      {
//         if(GetBkMode() == TRANSPARENT)
         {
         //   return TRUE;
            rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
            rect rectText(point((int64_t) x, (int64_t) y), GetTextExtent(str));
            if(rectIntersect.intersect(rectIntersect, rectText))
            {
               ::draw2d::dib_sp dib0(allocer());
               dib0->create(rectText.size());
               ::draw2d::brush_sp brush(allocer(),ARGB(255, 255, 255, 255));
               dib0->get_graphics()->SelectObject(get_current_font());
               dib0->get_graphics()->SelectObject(brush);
               dib0->get_graphics()->TextOut(0, 0, str);
               dib0->ToAlpha(0);
               ::draw2d::dib_sp dib1(allocer());
               dib1->create(rectText.size());
               brush->create_solid(m_spbrush->m_cr);
               dib1->get_graphics()->SelectObject(get_current_font());
               dib1->get_graphics()->TextOut(0, 0, str);
               dib1->channel_from(visual::rgba::channel_alpha, dib0);
               ::draw2d::dib_sp dib2(allocer());
               dib2->create(rectText.size());
               dib2->Fill(255, 0, 0, 0);
               dib2->from(point((int64_t) max(0, m_ptAlphaBlend.x - x), (int64_t) max(0, m_ptAlphaBlend.y - y)),
               m_pdibAlphaBlend->get_graphics(), point((int64_t) max(0, x - m_ptAlphaBlend.x), (int64_t) max(0, y - m_ptAlphaBlend.y)), rectText.size());
               dib1->channel_multiply(visual::rgba::channel_alpha, dib2.m_p);
               /*::draw2d::dib_sp dib3(get_app());
               dib1->mult_alpha(dib3);*/

               keeper < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);

               return BitBlt((int32_t) x, (int32_t) y, rectText.width(), rectText.height(), dib1->get_graphics(), 0, 0, SRCCOPY);

               /*BLENDFUNCTION bf;
               bf.BlendOp     = AC_SRC_OVER;
               bf.BlendFlags  = 0;
               bf.SourceConstantAlpha = 0xFF;
               bf.AlphaFormat = AC_SRC_ALPHA;
               return ::AlphaBlend(get_handle1(), x, y,
                  rectText.width(), rectText.height(), WIN_HDC(dib1->get_graphics()), 0, 0, rectText.width(),
                  rectText.height(), bf) != FALSE; */
            }
         }
      }

      //ASSERT(get_handle1() != NULL);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      return TextOut(x, y, str, (int32_t) str.get_length());

   } // call virtual

   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::ExtTextOut(get_handle1(), x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths) != FALSE;

   }

   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect, const string & str, LPINT lpDxWidths)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::ExtTextOut(get_handle1(), x, y, nOptions, lpRect, str, (UINT)str.get_length(), lpDxWidths) != FALSE;

   }

   size graphics::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

//      ASSERT(get_handle1() != NULL);
//      return ::TabbedTextOut(get_handle1(), x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);

   }

   size graphics::TabbedTextOut(int32_t x, int32_t y, const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

//      ASSERT(get_handle1() != NULL);
//      return ::TabbedTextOut(get_handle1(), x, y, str, (int32_t)str.get_length(), nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

//      ASSERT(get_handle2() != NULL);
//      return ::GetTabbedTextExtent(get_handle2(), lpszString, (int32_t) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

//      ASSERT(get_handle2() != NULL);
//      return ::GetTabbedTextExtent(get_handle2(), str, (int32_t) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

//      ASSERT(get_handle1() != NULL);
//      return ::GetTabbedTextExtent(get_handle1(), lpszString, (int32_t) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

//      ASSERT(get_handle1() != NULL);
//      return ::GetTabbedTextExtent(get_handle1(), str, (int32_t) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount,int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != FALSE;

   }

   UINT graphics::GetTextAlign() const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetTextAlign(get_handle2());

   }

   int32_t graphics::GetTextFace(int32_t nCount, LPTSTR lpszFacename) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetTextFace(get_handle2(), nCount, lpszFacename);

   }

   int32_t graphics::GetTextFace(string & rString) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      int32_t nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256)); rString.ReleaseBuffer();
//      return nResult;

   }

   bool graphics::get_text_metrics(::draw2d::text_metric * lpMetrics) const
   {
      //ASSERT(get_handle2() != NULL); return ::GetTextMetrics(get_handle2(), lpMetrics);

      /*
      str = L"123AWZwmc";
      Gdiplus::RectF rect;
      Gdiplus::RectF rect2;
      Gdiplus::PointF origin(0, 0);
      m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect);

      wstr = L"123AWZwmcpQçg";
      m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect2);*/

      string str1;
      str1 = L"WM123AWZwmciItf";
      string str2;
      str2 = L"WWÜ123AWZwmcpQçgÁiItf";

      size sz1 = GetTextExtent(str1);
      size sz2 = GetTextExtent(str2);

      lpMetrics->tmAveCharWidth = sz2.cx / (double) str2.get_length();
      lpMetrics->tmAscent = sz1.cy;
      lpMetrics->tmDescent = sz2.cy - sz1.cy;


      //retry_single_lock slGdiplus(&System.s_mutexGdiplus, millis(1), millis(1));

      /*((::draw2d_xlib::graphics *) this)->set(m_spfont);

      // Get the font from GC.
      ::XFontStruct *font = ::XQueryFont(m_pdc->m_pdisplay, ::XGContextFromGC(m_pdc->m_gc));

      // Compute and return the line height.
      if(NULL == font)
      {

         return false;
      }

      lpMetrics->tmAscent              = (LONG) font->max_bounds.ascent;
      lpMetrics->tmDescent             = (LONG) font->max_bounds.descent;
      lpMetrics->tmHeight              = (LONG) font->ascent + font->descent;*/

      lpMetrics->tmInternalLeading     = (LONG) lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight;
      lpMetrics->tmExternalLeading     = (LONG) (lpMetrics->tmHeight * 0.25);

//      lpMetrics->tmAveCharWidth        = (LONG) (font->max_bounds.width + font->min_bounds.width) / 2; // fast calculation

      //::XFreeFontInfo(NULL, font, 0);

      return true;

   }


   bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GetTextMetrics(get_handle1(), lpMetrics) != FALSE;

   }


   int32_t graphics::GetTextCharacterExtra() const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetTextCharacterExtra(get_handle2());

   }

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle2() != NULL);
//      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;

   }

   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;

   }

   uint32_t graphics::GetFontLanguageInfo() const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::GetFontLanguageInfo(get_handle1());

   }

/*

   uint32_t graphics::GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);

   }

   uint32_t graphics::GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::GetCharacterPlacement(get_handle1(), (const char *)str, (int32_t) str.get_length(), nMaxExtent, lpResults, dwFlags);

   }

*/

   size graphics::GetAspectRatioFilter() const
   {

      throw not_implemented(get_app());
      return size(0, 0);

//      ASSERT(get_handle2() != NULL);
//      SIZE size;
//      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
//      return size;

   }


   bool graphics::ScrollDC(int32_t dx, int32_t dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::ScrollDC(get_handle1(), dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != FALSE;

   }

   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);

   }

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::SetBoundsRect(get_handle1(), lpRectBounds, flags);

   }

   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetBoundsRect(get_handle2(), lpRectBounds, flags);

   }

/*

   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {

      throw not_implemented(get_app());
      return false;

//    ASSERT(get_handle2() != NULL);
//    return ::ResetDC(get_handle2(), lpDevMode) != NULL;

   }

   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetOutlineTextMetrics(get_handle2(), cbData, lpotm);

   }

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle2() != NULL);
//      return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != FALSE;

   }

*/

   uint32_t graphics::GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData, uint32_t cbData) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);

   }

/*

   int32_t graphics::GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);

   }

   uint32_t graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, uint32_t cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetGlyphOutline(get_handle2(), nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);

   }

*/

/*

   // ::user::object handling functions
   int32_t graphics::StartDoc(LPDOCINFO lpDocInfo)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::StartDoc(get_handle1(), lpDocInfo);

   }

*/

   int32_t graphics::StartPage()
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::StartPage(get_handle1());

   }

   int32_t graphics::EndPage()
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::EndPage(get_handle1());

   }

   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   }

   int32_t graphics::AbortDoc()
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::AbortDoc(get_handle1());

   }

   int32_t graphics::EndDoc()
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::EndDoc(get_handle1());

   }

   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask, uint32_t dwRop)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != FALSE;

   }

   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != FALSE;

   }

   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;

   }

   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;

   }

   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != FALSE;

   }

   bool graphics::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ArcTo(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

   }

   int32_t graphics::GetArcDirection() const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle2() != NULL);
//      return ::GetArcDirection(get_handle2());

   }

   bool graphics::PolyPolyline(const POINT* lpPoints, const uint32_t* lpPolyPoints, int32_t nCount)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::PolyPolyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != FALSE;

   }

/*

   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle2() != NULL);
//      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;

   }

*/

   ::draw2d::pen_sp graphics::get_current_pen() const
   {

      return m_sppen;

   }

   ::draw2d::brush_sp graphics::get_current_brush() const
   {

      return m_spbrush;

   }

   ::draw2d::palette_sp graphics::get_current_palette() const
   {

      return (::draw2d::palette *)NULL;

   }

   ::draw2d::font_sp graphics::get_current_font() const
   {

      return m_spfont;

   }


   ::draw2d::bitmap_sp graphics::get_current_bitmap() const
   {

      return m_spbitmap;

   }

   bool graphics::PolyBezier(const POINT* lpPoints, int32_t nCount)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::PolyBezier(get_handle1(), lpPoints, nCount) != FALSE;

   }

   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);

   }

   int32_t graphics::Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData,  int32_t nOutputSize, char * lpszOutputData)
   {

      throw not_implemented(get_app());
      return 0;

//       ASSERT(get_handle1() != NULL);
//       return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);

   }

/*

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle2() != NULL);
//      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;

   }

*/

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle2() != NULL);
//      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;

   }

   bool graphics::AbortPath()
   {

      throw not_implemented(get_app());
      return false;

/*
      if(m_ppath != NULL)
      {
         delete m_ppath;
         m_ppath = NULL;
      }
      return true;
*/

   }

   bool graphics::BeginPath()
   {

      throw not_implemented(get_app());
      return false;

/*
      if(m_ppath != NULL)
         delete m_ppath;

      m_ppath = new Gdiplus::GraphicsPath;

      return m_ppath != NULL;
*/

   }

   bool graphics::CloseFigure()
   {

      throw not_implemented(get_app());
      return false;

/*
      ASSERT(m_ppath != NULL);
      return m_ppath->CloseFigure() == Gdiplus::Status::Ok;
*/
   }

   bool graphics::EndPath()
   {

      throw not_implemented(get_app());
      return false;

/*
      if(m_ppath == NULL)
         return FALSE;

      m_ppathPaint   = m_ppath;
      m_ppath        = NULL;

      return true;
*/
   }

   bool graphics::FillPath()
   {

      throw not_implemented(get_app());
      return false;

//      return m_pgraphics->FillPath(gdiplus_brush(), m_ppath) == Gdiplus::Status::Ok;

   }

   bool graphics::FlattenPath()
   {

      throw not_implemented(get_app());
      return false;

//      return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }

   float graphics::GetMiterLimit() const
   {

      throw not_implemented(get_app());
      return 0.f;

//      ASSERT(get_handle1() != NULL);
//      float fMiterLimit;
//      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
//      return fMiterLimit;

   }

   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount) const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::GetPath(get_handle1(), lpPoints, lpTypes, nCount);

   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::SetMiterLimit(get_handle1(), fMiterLimit, NULL) != FALSE;

   }

   bool graphics::StrokeAndFillPath()
   {

      throw not_implemented(get_app());
      return false;

//      bool bOk1 = m_pgraphics->FillPath(gdiplus_brush(), m_ppathPaint) == Gdiplus::Status::Ok;

//      bool bOk2 = m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

//      return bOk1 && bOk2;

   }

   bool graphics::StrokePath()
   {

      throw not_implemented(get_app());
      return false;

//      return m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

   }

   bool graphics::WidenPath()
   {

      throw not_implemented(get_app());
      return false;

//      return m_ppath->Widen(gdiplus_pen()) == Gdiplus::Status::Ok;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      return draw();

   }

   bool graphics::fill_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      return fill();

   }


   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;

   }


/*bool CALLBACK metacallback(
   EmfPlusRecordType recordType,
   uint32_t flags,
   uint32_t dataSize,
   const unsigned char* pStr,
   void* callbackData)
{
   // Play only EmfPlusRecordTypeFillEllipse records.
   if (recordType == EmfPlusRecordTypeFillEllipse)
   {
   // Explicitly cast callbackData as a metafile pointer, and use it to call
   // the PlayRecord method.
   static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
   }
   return TRUE;
}

VOID Example_EnumerateMetafile9(HDC hdc)
{
   Graphics graphics(hdc);
   // Create a Metafile object from an existing disk metafile.
   Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
   {
      // Fill a rectangle and an ellipse in pMeta.
      Graphics metaGraphics(pMeta);
      metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
  metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
   }
   // Enumerate pMeta to the destination rectangle, passing pMeta as the CALLBACK data.
   graphics.EnumerateMetafile(
   pMeta,
   Rect(0, 0, 300, 50),
   metacallback,
   pMeta);
   // Draw pMeta as an image.
   graphics.DrawImage(pMeta, Point(0, 150));
   delete pMeta;;
}*/

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, LPCRECT lpBounds)
   {

      throw not_implemented(get_app());
      return false;


/*      Gdiplus::RectF rect((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

      Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);

      //m_pgraphcis->EnumerateMetafile(pMeta, rect, metacallback, PMETAHEADER);

      bool bOk = m_pgraphics->DrawImage(pMeta, rect) == Gdiplus::Status::Ok;

      delete pMeta;

      return bOk ? TRUE : FALSE;*/
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

   }

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

// Thank you
// Jiju George T
// Web Developer
// India India
// Member

   bool graphics::alpha_blend(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dRate)
   {

   return this->BitBlt(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, SRCCOPY);

      synch_lock ml(&user_mutex());

      if(m_pdibAlphaBlend != NULL)
      {

         throw not_implemented(get_app());

/*
         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());


         ::draw2d::dib * pdibWork = NULL;
         ::draw2d::dib * pdibWork2 = NULL;
//         ::draw2d::dib * pdibWork3 = NULL;
         ::draw2d::dib * pdibWork4 = NULL;


         class point ptSrc(xSrc, ySrc);
         class point ptDest(xDest, yDest);
         class size size(nDestWidth, nDestHeight);



         ::draw2d::dib_sp spdib;
         if(pdibWork == NULL)
         {
            spdib.create(get_app());
            pdibWork = spdib;
         }
         if(pdibWork == NULL)
            return false;
         if(!pdibWork->create(size))
            return false;
         if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
            return false;




         ::draw2d::dib_sp spdib2;
         if(pdibWork2 == NULL)
         {
            spdib2.create(get_app());
            pdibWork2 = spdib2;
         }


         ::draw2d::dib_sp spdib4;
         if(pdibWork4 == NULL)
         {
            spdib4.create(get_app());
            pdibWork4 = spdib4;
         }
         if(pdibWork4 == NULL)
            return false;
         if(!pdibWork4->create(size))
            return false;


         pdibWork4->Fill(255, 0, 0, 0);

         pdibWork4->from(point(max(0, m_ptAlphaBlend.x - xDest), max(0, m_ptAlphaBlend.y - yDest)),
            m_pdibAlphaBlend->get_graphics(), point(max(0, xDest - m_ptAlphaBlend.x), max(0, yDest - m_ptAlphaBlend.y)), size);

         pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);


         keeper < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);


         return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), ptSrc);

*/
      }

      /*if(pgraphicsSrc == NULL)
         return false;


      if(nSrcWidth == 0 || nSrcHeight == 0 || nDstWidth == 0 || nDstHeight == 0)
         return false;

      xlib_pattern_t * ppattern = xlib_get_source((xlib_t *) pgraphicsSrc->get_os_data());

      if(ppattern == NULL)
         return false;

      if(xlib_pattern_status(ppattern) != CAIRO_STATUS_SUCCESS)
         return false;

      if(m_pdc == NULL)
         return false;

      xlib_keep keep(m_pdc);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_translate(m_pdc, xDst, yDst);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_scale(m_pdc, (double) nDstWidth / (double) nSrcWidth, (double) nDstHeight / (double) nSrcHeight);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_set_source(m_pdc, ppattern);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_paint_with_alpha(m_pdc, dRate);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_pattern_destroy(ppattern);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;*/

      return true;

   }


   /*bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, BLENDFUNCTION blend)
   {

      throw not_implemented(get_app());
      //if(get_handle1() == NULL)
        // return false;


      if(m_pdibAlphaBlend != NULL)
      {


         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());


         ::draw2d::dib * pdibWork = NULL;
         ::draw2d::dib * pdibWork2 = NULL;
//         ::draw2d::dib * pdibWork3 = NULL;
         ::draw2d::dib * pdibWork4 = NULL;


         class point ptSrc(xSrc, ySrc);
         class point ptDest(xDest, yDest);
         class size size(nDestWidth, nDestHeight);



         ::draw2d::dib_sp spdib;
         if(pdibWork == NULL)
         {
            spdib.create(get_app());
            pdibWork = spdib;
         }
         if(pdibWork == NULL)
            return false;
         if(!pdibWork->create(size))
            return false;
         if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
            return false;




         ::draw2d::dib_sp spdib2;
         if(pdibWork2 == NULL)
         {
            spdib2.create(get_app());
            pdibWork2 = spdib2;
         }


         ::draw2d::dib_sp spdib4;
         if(pdibWork4 == NULL)
         {
            spdib4.create(get_app());
            pdibWork4 = spdib4;
         }
         if(pdibWork4 == NULL)
            return false;
         if(!pdibWork4->create(size))
            return false;


         pdibWork4->Fill(255, 0, 0, 0);

         pdibWork4->from(point(max(0, m_ptAlphaBlend.x - xDest), max(0, m_ptAlphaBlend.y - yDest)),
            m_pdibAlphaBlend->get_graphics(), point(max(0, xDest - m_ptAlphaBlend.x), max(0, yDest - m_ptAlphaBlend.y)), size);

         pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);


         keeper < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);


         return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), ptSrc);


      }

      return ::AlphaBlend(get_handle1(), xDest, yDest,
         nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != FALSE;
   }*/


   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != FALSE;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, uint32_t dwMode)
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != FALSE;

   }

      #if (_WIN32_WINNT >= 0x0500)

   // Always Inline. Functions only in Win98/Win2K or later


   COLORREF graphics::GetDCBrushColor() const
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::GetDCBrushColor(get_handle1());

   }

   COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::SetDCBrushColor(get_handle1(), crColor);

   }

   COLORREF graphics::GetDCPenColor() const
   {

      throw not_implemented(get_app());
      return 0;

//       ASSERT(get_handle1() != NULL);
//       return ::GetDCPenColor(get_handle1());
   }

   COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {

      throw not_implemented(get_app());
      return 0;

//      ASSERT(get_handle1() != NULL);
//      return ::SetDCPenColor(get_handle1(), crColor);

   }

#endif

   #if (_WIN32_WINNT >= 0x0500)

   bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != FALSE;

   }

   bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
   {

      throw not_implemented(get_app());
      return false;

//      ASSERT(get_handle1() != NULL);
//      return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != FALSE;

   }

   #endif

   #if (_WIN32_WINNT >= 0x0500)

   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
   {

      throw not_implemented(get_app());
      return false;

//      ENSURE(lpSize != NULL);
//      ASSERT(get_handle1() != NULL);
//      return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize) != FALSE;

   }


   bool graphics::GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, LPSIZE lpSize) const
   {

      throw not_implemented(get_app());
      return false;

//      ENSURE(lpSize != NULL);
//      ASSERT(get_handle1() != NULL);
//      return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, lpSize) != FALSE;

   }


#endif


   /////////////////////////////////////////////////////////////////////////////
   // More coordinate transforms (in separate file to avoid transitive refs)

#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE lpSize) const
   {

      throw not_implemented(get_app());

/*
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      int32_t nMapMode;
      if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
      {
         // when using a constrained ::collection::map mode, ::collection::map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         DPtoLP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // ::collection::map against logical inch for non-constrained mapping modes
         int32_t cxPerInch, cyPerInch;
         if (this != NULL)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != NULL);  // no HDC attached or created?
            cxPerInch = GetDevicecaps(LOGPIXELSX);
            cyPerInch = GetDevicecaps(LOGPIXELSY);
         }
         else
         {
//            cxPerInch = afxData.cxPixelsPerInch;
  //          cyPerInch = afxData.cyPixelsPerInch;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         lpSize->cx = MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
         lpSize->cy = MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
      }

*/

   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize) const
   {

      throw not_implemented(get_app());

/*      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      int32_t nMapMode;
      if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
         nMapMode != MM_TEXT)
      {
         // when using a constrained ::collection::map mode, ::collection::map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         LPtoDP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // ::collection::map against logical inch for non-constrained mapping modes
         int32_t cxPerInch, cyPerInch;
         if (this != NULL)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != NULL);  // no HDC attached or created?
            cxPerInch = GetDevicecaps(LOGPIXELSX);
            cyPerInch = GetDevicecaps(LOGPIXELSY);
         }
         else
         {
//            cxPerInch = afxData.cxPixelsPerInch;
  //          cyPerInch = afxData.cyPixelsPerInch;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         lpSize->cx = MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
         lpSize->cy = MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
      }

*/

   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      LPtoDP(lpSize);
      DPtoHIMETRIC(lpSize);
   }

   void graphics::HIMETRICtoLP(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      HIMETRICtoDP(lpSize);
      DPtoLP(lpSize);
   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* PASCAL graphics::GetHalftoneBrush(sp(base_application) papp)
   {
/*      ::core::LockGlobals(CRIT_HALFTONEBRUSH);
      if (gen_HalftoneBrush == NULL)
      {
         WORD grayPattern[8];
         for (int32_t i = 0; i < 8; i++)
            grayPattern[i] = (WORD)(0x5555 << (i & 1));
         HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
         if (grayBitmap != NULL)
         {
            gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
            ::DeleteObject(grayBitmap);
         }
      }
      if (!gen_WingdixTerm)
         gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
      ::core::UnlockGlobals(CRIT_HALFTONEBRUSH);

//      return ::win::brush::from_handle(papp, gen_HalftoneBrush);*/
      return NULL;
   }

   void graphics::DrawDragRect(LPCRECT lpRect, SIZE size, LPCRECT lpRectLast, SIZE sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      throw not_implemented(get_app());

/*
      ASSERT(__is_valid_address(lpRect, sizeof(RECT), FALSE));
      ASSERT(lpRectLast == NULL ||
         __is_valid_address(lpRectLast, sizeof(RECT), FALSE));

      // first, determine the update region and select it
      ::draw2d::region rgnNew;
      ::draw2d::region rgnOutside, rgnInside;
      rgnOutside.CreateRectRgnIndirect(lpRect);
      rect rect = *lpRect;
      rect.inflate(-size.cx, -size.cy);
      rect.intersect(rect, lpRect);
      rgnInside.CreateRectRgnIndirect(rect);
      rgnNew.CreateRectRgn(0, 0, 0, 0);
      rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

      ::draw2d::brush* pBrushOld = NULL;
      if (pBrush == NULL)
      {
         pBrush = graphics::GetHalftoneBrush(get_app());
      }

      ENSURE(pBrush);

      if (pBrushLast == NULL)
      {
         pBrushLast = pBrush;
      }

      ::draw2d::region rgnLast, rgnUpdate;
      if (lpRectLast != NULL)
      {
         // find difference between new region and old region
         rgnLast.CreateRectRgn(0, 0, 0, 0);
         rgnOutside.SetRectRgn(lpRectLast);
         rect = *lpRectLast;
         rect.inflate(-sizeLast.cx, -sizeLast.cy);
         rect.intersect(rect, lpRectLast);
         rgnInside.SetRectRgn(rect);
         rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

         // only diff them if brushes are the same
         if (pBrush->get_os_data() == pBrushLast->get_os_data())
         {
            rgnUpdate.CreateRectRgn(0, 0, 0, 0);
            rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
         }
      }
      if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != NULL)
      {
         // brushes are different -- erase old region first
         SelectClipRgn(&rgnLast);
         GetClipBox(&rect);
         pBrushOld = SelectObject(pBrushLast);
         PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
         SelectObject(pBrushOld);
         pBrushOld = NULL;
      }

      // draw into the update/new region
      SelectClipRgn(rgnUpdate.get_os_data() != NULL ? &rgnUpdate : &rgnNew);
      GetClipBox(&rect);
      pBrushOld = SelectObject(pBrush);
      PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);

      // cleanup DC
      if (pBrushOld != NULL)
         SelectObject(pBrushOld);
      SelectClipRgn(NULL);

*/

   }

   /*void graphics::FillSolidRect(LPCRECT lpRect, COLORREF clr)
   {
      ::SetBkColor(get_handle1(), clr);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
   }*/

   void graphics::FillSolidRect(const __rect64 * lpRect, COLORREF clr)
   {
      rect rect32;
      ::copy(rect32, lpRect);
      FillSolidRect(rect32, clr);
   }


   /*

   void graphics::FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr)
   {
      ::SetBkColor(get_handle1(), clr);
      rect rect(x, y, x + cx, y + cy);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
   }

   */

   void graphics::Draw3dRect(LPCRECT lpRect,
      COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
         lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
   }

   void graphics::Draw3dRect(int32_t x, int32_t y, int32_t cx, int32_t cy,
      COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
      FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
      FillSolidRect(x + cx - 1, y, 1, cy, clrBottomRight);
      FillSolidRect(x, y + cy - 1, cx, 1, clrBottomRight);
   }





   //::draw2d::graphics * PASCAL ::win::graphics::from_handle(HDC hDC)
   //{
      //hdc_map* pMap = afxMapHDC(TRUE); //create ::collection::map if not exist
      //ASSERT(pMap != NULL);
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
  //    ASSERT(pgraphics == NULL || (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() == hDC);
    //  return pgraphics;
     // return NULL;
   //}

/*

   bool graphics::Attach(HDC hdc)
   {

      if(hdc == NULL)
         return false;

      if(m_hdc == hdc)
      {

         if(m_pgraphics != NULL)
            return true;

      }

      if(hdc != NULL)
      {

         m_pgraphics = new ::Gdiplus::Graphics(hdc);

         set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

         m_hdc = hdc;

      }

      return m_pgraphics != NULL;

      /*ASSERT(get_handle1() == NULL);      // only attach once, detach on destroy
      ASSERT(get_handle2() == NULL);    // only attach to an is_empty DC

      if (hDC == NULL)
      {
         return FALSE;
      }
      // remember early to avoid leak
      set_handle1(hDC);
      hdc_map* pMap = afxMapHDC(TRUE); // create ::collection::map if not exist
      ASSERT(pMap != NULL);
      pMap->set_permanent(get_handle1(), this);

      SetAttribDC(get_handle1());     // Default to same as output
      return TRUE;*/
//   }

  /* HDC graphics::Detach()
   {

      if(m_hdc == NULL)
         return NULL;

      if(m_pgraphics == NULL)
         return NULL;

      delete m_pgraphics;
      m_pgraphics = NULL;

      HDC hdc = m_hdc;
      m_hdc = NULL;

      return hdc;

   }
*/

   bool graphics::DeleteDC()
   {

      synch_lock ml(&user_mutex());

      m_spbitmap.release();

      if(m_pdc == NULL)
         return true;

      XFreeGC(m_pdc->m_pdisplay, m_pdc->m_gc);

      delete m_pdc;

      m_pdc = NULL;

      return true;

   }


/*

   void graphics::SetAttribDC(HDC hDC)  // Set the Attribute DC
   {
//      set_handle2(hDC);
   }

   void graphics::SetOutputDC(HDC hDC)  // Set the Output DC
   {
#ifdef DEBUG
/*      hdc_map* pMap = afxMapHDC();
      if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
      {
         TRACE(::core::trace::category_AppMsg, 0, "cannot Set Output hDC on Attached graphics.\n");
         ASSERT(FALSE);
      }*/
//#endif
  //    set_handle1(hDC);
   //}
/*
   void graphics::ReleaseAttribDC()     // Release the Attribute DC
   {
//      set_handle2(NULL);
   }

   void graphics::ReleaseOutputDC()     // Release the Output DC
   {
#ifdef DEBUG
/*      hdc_map* pMap = afxMapHDC();
      if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
      {
         TRACE(::core::trace::category_AppMsg, 0, "cannot Release Output hDC on Attached graphics.\n");
         ASSERT(FALSE);
      }*/
//#endif
      //set_handle1(NULL);
   //

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int32_t graphics::StartDoc(const char * lpszDocName)
   {

      throw not_implemented(get_app());
      return 0;

/*
      DOCINFO di;
      memset(&di, 0, sizeof(DOCINFO));
      di.cbSize = sizeof(DOCINFO);
      di.lpszDocName = lpszDocName;
      return StartDoc(&di);
*/

   }

   int32_t graphics::SaveDC()
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = 0;
      if(get_handle2() != NULL)
         nRetVal = ::SaveDC(get_handle2());
      if(get_handle1() != NULL && get_handle1() != get_handle2() && ::SaveDC(get_handle1()) != 0)
         nRetVal = -1;   // -1 is the only valid restore value for complex DCs
      return nRetVal;
*/

   }

   bool graphics::RestoreDC(int32_t nSavedDC)
   {

      throw not_implemented(get_app());
      return false;

/*
      bool bRetVal = TRUE;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != FALSE;
      if(get_handle2() != NULL)
         bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC) != FALSE);
      return bRetVal;
*/

   }

//   object* PASCAL graphics::SelectGdiObject(sp(base_application) papp, HDC hDC, HGDIOBJ h)
  // {
//      return ::win::object::from_handle(papp, ::SelectObject(hDC, h));
   //}

   ::draw2d::object* graphics::SelectStockObject(int32_t nIndex)
   {
/*      HGDIOBJ hObject = ::GetStockObject(nIndex);
      HGDIOBJ hOldObj = NULL;
      ASSERT(hObject != NULL);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), hObject);
      if(get_handle2() != NULL)
         hOldObj = ::SelectObject(get_handle2(), hObject);
      return ::win::object::from_handle(get_app(), hOldObj);*/

      return NULL;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* ppen)
   {
      /*HGDIOBJ hOldObj = NULL;
      if(pPen == NULL)
         return NULL;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), pPen->get_os_data());
      if(get_handle2() != NULL)
         hOldObj = ::SelectObject(get_handle2(), pPen->get_os_data());
      return dynamic_cast < pen * > (::win::object::from_handle(get_app(), hOldObj));*/
      m_sppen = ppen;
      return m_sppen;
   }

   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pbrush)
   {
/*      HGDIOBJ hOldObj = NULL;
      if(pBrush == NULL)
         return NULL;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), pBrush->get_os_data());
      if(get_handle2() != NULL)
         hOldObj = ::SelectObject(get_handle2(), pBrush->get_os_data());
      return dynamic_cast < ::draw2d::brush * > (::win::object::from_handle(get_app(), hOldObj));*/
      m_spbrush = pbrush;
      return m_spbrush;

   }

   ::draw2d::font* graphics::SelectObject(::draw2d::font* pfont)
   {
/*      HGDIOBJ hOldObj = NULL;
      if(pFont == NULL)
         return NULL;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), pFont->get_os_data());
      if(get_handle2() != NULL)
         hOldObj = ::SelectObject(get_handle2(), pFont->get_os_data());
      return dynamic_cast < ::draw2d::font * > (::win::object::from_handle(get_app(), hOldObj));*/

      /*ASSERT(pFont != NULL);

      if(pFont == NULL)
         return NULL;

      m_fontxyz = *pFont;
      return m_spfont;*/

      if(!select_font(pfont))
         return NULL;

      return m_spfont;

   }

   int32_t graphics::SelectObject(::draw2d::region* pRgn)
   {

      throw not_implemented(get_app());
      return false;

/*
      int32_t nRetVal = GDI_ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle1(), (HGDIOBJ) pRgn->get_os_data());
      if(get_handle2() != NULL)
         nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle2(), (HGDIOBJ) pRgn->get_os_data());
      return nRetVal;
*/

   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return NULL;
//      return dynamic_cast < ::draw2d::palette * > (::win::object::from_handle(get_app(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }


   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
      return nRetVal;
*/

   }

   int32_t graphics::SetROP2(int32_t nDrawMode)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetROP2(get_handle1(), nDrawMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetROP2(get_handle2(), nDrawMode);
      return nRetVal;
*/

   }

   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {

      //throw not_implemented(get_app());
//      return 0;

m_nStretchBltMode = nStretchMode;
return 1;

      /*int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
      return nRetVal;*/
   }


   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
      {
         nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
      }
      if(get_handle2() != NULL)
      {
         nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
      }
      return nRetVal;
*/

   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      throw not_implemented(get_app());
      return false;

/*
      bool nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
      {
         nRetVal = ::SetWorldTransform(get_handle1(), pXform) != FALSE;
      }
      if(get_handle2() != NULL)
      {
         nRetVal = ::SetWorldTransform(get_handle2(), pXform) != FALSE;
      }
      return nRetVal;
*/

   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,uint32_t iMode)
   {

      throw not_implemented(get_app());
      return false;


/*
      bool nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
      {
         nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != FALSE;
      }
      if(get_handle2() != NULL)
      {
         nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != FALSE;
      }
      return nRetVal;
*/

   }

   int32_t graphics::SetMapMode(int32_t nMapMode)
   {

      //throw not_implemented(get_app());
      return 0;


/*
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetMapMode(get_handle1(), nMapMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetMapMode(get_handle2(), nMapMode);
      return nRetVal;
*/

   }


   point graphics::GetViewportOrg() const
   {

      return m_pdc->m_ptOffset;

   }


   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {

      m_pdc->m_ptOffset.x = x;

      m_pdc->m_ptOffset.y = y;

      return m_pdc->m_ptOffset;

   }


   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {

      m_pdc->m_ptOffset.x += nWidth;

      m_pdc->m_ptOffset.y += nHeight;

      return m_pdc->m_ptOffset;

   }

   size graphics::SetViewportExt(int32_t x, int32_t y)
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

/*
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetViewportExtEx(get_handle1(), x, y, &size);
      if(get_handle2() != NULL)
         ::SetViewportExtEx(get_handle2(), x, y, &size);
      return size;
*/
   }

   size graphics::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

/*
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::ScaleViewportExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
      if(get_handle2() != NULL)
         ::ScaleViewportExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
      return size;
*/

   }

   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {

      throw not_implemented(get_app());
      return ::point(0, 0);

/*
      point point(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetWindowOrgEx(get_handle1(), x, y, &point);
      if(get_handle2() != NULL)
         ::SetWindowOrgEx(get_handle2(), x, y, &point);
      return point;
*/
   }

   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {

      throw not_implemented(get_app());
      return ::point(0, 0);

/*
      point point(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
      if(get_handle2() != NULL)
         ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
      return point;
*/

   }

   size graphics::SetWindowExt(int32_t x, int32_t y)
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

/*
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetWindowExtEx(get_handle1(), x, y, &size);
      if(get_handle2() != NULL)
         ::SetWindowExtEx(get_handle2(), x, y, &size);
      return size;
*/

   }

   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

/*
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
      if(get_handle2() != NULL)
         ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
      return size;
*/

   }

   int32_t graphics::GetClipBox(LPRECT lpRect) const
   {

      //throw not_implemented(get_app());
      return 0;

/*      return ::GetClipBox(get_handle1(), lpRect);*/
   }

   int32_t graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      /*synch_lock ml(&user_mutex());
      if(pregion == NULL)
      {

         xlib_reset_clip(m_pdc);

      }
      else
      {

         if(m_spregion.is_null())
            m_spregion.create(allocer());

         *m_spregion.m_p = *pregion;

         //xlib_clip(m_pdc);

      }*/

      return 0;

/*
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SelectClipRgn(get_handle1(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
      if(get_handle2() != NULL)
         nRetVal = ::SelectClipRgn(get_handle2(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
      return nRetVal;
*/

   }

   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
      if(get_handle2() != NULL)
         nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
      return nRetVal;
*/

   }

   int32_t graphics::ExcludeClipRect(LPCRECT lpRect)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::ExcludeClipRect(get_handle1(), lpRect->left, lpRect->top,
         lpRect->right, lpRect->bottom);
      if(get_handle2() != NULL)
         nRetVal = ::ExcludeClipRect(get_handle2(), lpRect->left, lpRect->top,
         lpRect->right, lpRect->bottom);
      return nRetVal;
*/

   }

   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
      if(get_handle2() != NULL)
         nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
      return nRetVal;
*/

   }

   int32_t graphics::IntersectClipRect(LPCRECT lpRect)
   {

      throw not_implemented(get_app());
      return 0;

/*      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::IntersectClipRect(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
      if(get_handle2() != NULL)
         nRetVal = ::IntersectClipRect(get_handle2(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
      return nRetVal;
*/

   }

   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
      if(get_handle2() != NULL)
         nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
      return nRetVal;
*/

   }

   int32_t graphics::OffsetClipRgn(SIZE size)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
      if(get_handle2() != NULL)
         nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
      return nRetVal;
*/
   }


   point graphics::MoveTo(int32_t x, int32_t y)
   {

      m_pdc->m_pt.x = x;

      m_pdc->m_pt.y = y;

      return m_pdc->m_pt;

   }


   pointd graphics::MoveTo(double x, double y)
   {

      m_pdc->m_pt.x = x;

      m_pdc->m_pt.y = y;

      return pointd(x, y);

   }

   UINT graphics::SetTextAlign(UINT nFlags)
   {

      throw not_implemented(get_app());
      return 0;

/*
      UINT nRetVal = GDI_ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetTextAlign(get_handle1(), nFlags);
      if(get_handle2() != NULL)
         nRetVal = ::SetTextAlign(get_handle2(), nFlags);
      return nRetVal;
*/

   }

   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {

      throw not_implemented(get_app());
      return 0;

/*
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
      if(get_handle2() != NULL)
         nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
      return nRetVal;
*/

   }

   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {

      throw not_implemented(get_app());
      return 0;

/*
      ASSERT(get_handle1() != NULL);
      int32_t nRetVal = 0x8000000;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
      if(get_handle2() != NULL)
         nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
      return nRetVal;
*/

   }

   uint32_t graphics::SetMapperFlags(uint32_t dwFlag)
   {

      throw not_implemented(get_app());
      return 0;

/*
      ASSERT(get_handle1() != NULL);
      uint32_t dwRetVal = GDI_ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
      if(get_handle2() != NULL)
         dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
      return dwRetVal;
*/

   }

//   typedef uint32_t (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
//   typedef uint32_t (CALLBACK* __GDISETLAYOUTPROC)(HDC, uint32_t);

   uint32_t graphics::GetLayout() const
   {

      throw not_implemented(get_app());
      return 0;

/*
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != NULL);
      uint32_t dwGetLayout = LAYOUT_LTR;
      __GDIGETLAYOUTPROC pfn;
      pfn = (__GDIGETLAYOUTPROC) GetProcaddress(hInst, "GetLayout");
      // if they API is available, just call it. If it is not
      // available, indicate an error.
      if (pfn != NULL)
         dwGetLayout = (*pfn)(get_handle1());
      else
      {
         dwGetLayout = GDI_ERROR;
         SetLastError(ERROR_caLL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;
*/

   }

   uint32_t graphics::SetLayout(uint32_t dwSetLayout)
   {

      throw not_implemented(get_app());
      return 0;

/*
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != NULL);
      uint32_t dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcaddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != NULL)
         dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         SetLastError(ERROR_caLL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;
*/

   }
   /*
   void window::ScreenToClient(LPRECT lpRect)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::ScreenToClient(get_handle1(), (LPPOINT)lpRect);
   ::ScreenToClient(get_handle1(), ((LPPOINT)lpRect)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rect::swap_left_right(lpRect);
   }

   void window::ClientToScreen(LPRECT lpRect)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::ClientToScreen(get_handle1(), (LPPOINT)lpRect);
   ::ClientToScreen(get_handle1(), ((LPPOINT)lpRect)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rect::swap_left_right(lpRect);
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      throw not_implemented(get_app());
      return false;

/*
      ASSERT(get_handle1() != NULL);
      bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
*/

   }

   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {


      throw not_implemented(get_app());
      return 0;

/*
      ASSERT(get_handle1() != NULL);
      int32_t nResult = 0;
      if (get_handle1() != get_handle2())
         nResult = ::SetArcDirection(get_handle1(), nArcDirection);
      if (get_handle2() != NULL)
         nResult = ::SetArcDirection(get_handle2(), nArcDirection);
      return nResult;
*/

   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount)
   {

      throw not_implemented(get_app());
      return false;

/*
      ASSERT(get_handle1() != NULL);
      bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, nCount) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
*/

   }

   bool graphics::PolylineTo(const POINT* lpPoints, int32_t nCount)
   {

      throw not_implemented(get_app());
      return false;

/*
      ASSERT(get_handle1() != NULL);
      bool bResult = ::PolylineTo(get_handle1(), lpPoints, nCount) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
*/

   }

/*
   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {

      throw not_implemented(get_app());
      return false;

/*
      ASSERT(get_handle1() != NULL);
      bool bResult = FALSE;
      if (get_handle1() != get_handle2())
         bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != FALSE;
      if (get_handle2() != NULL)
         bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
      return bResult;
*/

//   }

   bool graphics::PolyBezierTo(const POINT* lpPoints, int32_t nCount)
   {

      throw not_implemented(get_app());
      return 0;

/*
      ASSERT(get_handle1() != NULL);
      bool bResult = ::PolyBezierTo(get_handle1(), lpPoints, nCount) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
*/

   }

   bool graphics::SelectClipPath(int32_t nMode)
   {

      throw not_implemented(get_app());
      return 0;

/*
      ASSERT(get_handle1() != NULL);

      // output DC always holds the current path
      if (!::SelectClipPath(get_handle1(), nMode))
         return FALSE;

      // transfer clipping region into the attribute DC
      bool bResult = TRUE;
      if (get_handle1() != get_handle2())
      {
         HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
         if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
         {
            TRACE(::core::trace::category_AppMsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
            bResult = FALSE;
         }
         ::DeleteObject(hRgn);
      }
      return bResult;
*/

   }

   int32_t graphics::SelectClipRgn(::draw2d::region* pRgn, int32_t nMode)
   {

      throw not_implemented(get_app());
      return 0;

/*      ASSERT(get_handle1() != NULL);
      int32_t nRetVal = ERROR;
      if (get_handle1() != get_handle2())
         nRetVal = ::ExtSelectClipRgn(get_handle1(), (HRGN)pRgn->get_os_data(), nMode);
      if (get_handle2() != NULL)
         nRetVal = ::ExtSelectClipRgn(get_handle2(), (HRGN)pRgn->get_os_data(), nMode);
      return nRetVal;
*/

   }

   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback
/*
   int32_t CALLBACK __enum_meta_file_procedure(HDC hDC,
      HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int32_t nHandles, LPARAM lParam)
   {
      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;
      ASSERT_VALID(pgraphics);

      switch (pMetaRec->rdFunction)
      {
         // these records have effects different for each graphics derived class
      case META_SETMAPMODE:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetMapMode((int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWEXT:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowExt(
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWORG:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowOrg(
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTEXT:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetViewportExt(
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTORG:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetViewportOrg(
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_ScaLEWINDOWEXT:
         (dynamic_cast<::win::graphics * >(pgraphics))->ScaleWindowExt(
            (int32_t)(short)pMetaRec->rdParm[3], (int32_t)(short)pMetaRec->rdParm[2],
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_ScaLEVIEWPORTEXT:
         (dynamic_cast<::win::graphics * >(pgraphics))->ScaleViewportExt(
            (int32_t)(short)pMetaRec->rdParm[3], (int32_t)(short)pMetaRec->rdParm[2],
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_OFFSETVIEWPORTORG:
         (dynamic_cast<::win::graphics * >(pgraphics))->OffsetViewportOrg(
            (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_SAVEDC:
         (dynamic_cast<::win::graphics * >(pgraphics))->SaveDC();
         break;
      case META_RESTOREDC:
         (dynamic_cast<::win::graphics * >(pgraphics))->RestoreDC((int32_t)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETBKCOLOR:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetBkColor(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
         break;
      case META_SETTEXTCOLOR:
         (dynamic_cast<::win::graphics * >(pgraphics))->SetTextColor(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
         break;

         // need to watch out for SelectObject(HFONT), for custom font mapping
      case META_SELECTOBJECT:
         {
            HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
            UINT nObjType = GetObjectType(hObject);
            if (nObjType == 0)
            {
               // object type is unknown, determine if it is a font
               HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
               HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hStockFont);
               HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObject);
               if (hObjOld == hStockFont)
               {
                  // got the stock object back, so must be selecting a font
                  throw not_implemented(get_thread_app());
//                  (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
                  break;  // don't play the default record
               }
               else
               {
                  // didn't get the stock object back, so restore everything
                  ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hFontOld);
                  ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObjOld);
               }
               // and fall through to PlayMetaFileRecord...
            }
            else if (nObjType == OBJ_FONT)
            {
               // play back as graphics::SelectObject(::draw2d::font*)
//               (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
               throw not_implemented(get_thread_app());
               break;  // don't play the default record
            }
         }
         // fall through...

      default:
         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
         break;
      }

      return 1;
   }*/

/*

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {

      throw not_implemented(get_app());
      return false;

/*
      if (::GetDevicecaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
      {
         // playing metafile in metafile, just use core windows API
         return ::PlayMetaFile(get_handle1(), hMF) != FALSE;
      }

      // for special playback, lParam == pgraphics
      return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != FALSE;
*/

//   }

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize) const
   {

      throw not_implemented(get_app());
      return;

/*
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      size sizeWinExt = GetWindowExt();
      size sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
*/

   }

   void graphics::DPtoLP(LPSIZE lpSize) const
   {

      throw not_implemented(get_app());
      return;

/*
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      size sizeWinExt = GetWindowExt();
      size sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
*/

   }



   int32_t graphics::draw_text(const char * lpszString, int32_t nCount, LPRECT lpRect, UINT nFormat)
   {
      /*if(get_handle1() == NULL)
         return -1;
      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = ::str::international::utf8_to_unicode(string(lpszString, nCount));
      return ::DrawTextW(get_handle1(), wstr, (int32_t) wcslen(wstr), lpRect, nFormat); */

      return draw_text(string(lpszString, nCount), lpRect, nFormat);

   }


   int32_t graphics::draw_text(const string & str, LPRECT lpRect, UINT nFormat)
   {

      synch_lock ml(&user_mutex());

      if(m_spfont.is_null())
         return 0;

      set(m_spfont);

/*      XGCValues v;

      XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

      if(v.font == -1)
         return 0;*/

      int h = compute_line_height();

      size sz = GetTextExtent(str);

      xlib_keep keep(this);

      double dx;

      double dy;

      if(nFormat & DT_RIGHT)
      {
         dx = lpRect->right - lpRect->left - sz.cx;
      }
      else if(nFormat & DT_CENTER)
      {
         dx = ((lpRect->right - lpRect->left) - (sz.cx)) / 2.0;
      }
      else
      {
         dx = 0.;
      }

      if(nFormat & DT_BOTTOM)
      {
         dy = lpRect->bottom - lpRect->top - sz.cy;
      }
      else if(nFormat & DT_VCENTER)
      {
         dy = ((lpRect->bottom - lpRect->top) - (sz.cy)) / 2.0;
      }
      else
      {
         dy = 0.;
      }

/*      array < XChar2b > xa = utf8toXChar2b(str, str.get_length());

      ::XDrawString16(
         m_pdc->m_pdisplay,
         m_pdc->m_drawable,
         m_pdc->m_gc,
         lpRect->left + dx + m_pdc->m_ptOffset.x,
         lpRect->top + h + dy + m_pdc->m_ptOffset.y,
         xa.get_data(),
         xa.get_count());*/

      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_spbitmap.m_p);

      if(pbitmap == NULL)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_spfont.m_p);

      if(pfont == NULL)
         return false;

      XftDraw * pdraw = XftDrawCreateAlpha (m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_iDepth);

      XRenderColor c;

      c.red = argb_get_r_value(m_spbrush->m_cr) * 255;
      c.green = argb_get_g_value(m_spbrush->m_cr) * 255;
      c.blue = argb_get_b_value(m_spbrush->m_cr) * 255;
      c.alpha = argb_get_a_value(m_spbrush->m_cr) * 255;

      XftColor ftc;
      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

      XftDrawStringUtf8(pdraw, &ftc, pfont->m_pft,
      lpRect->left + dx + m_pdc->m_ptOffset.x,
      lpRect->top + h + dy + m_pdc->m_ptOffset.y, (const FcChar8 *) (const char *) str, str.get_length());

      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);

      return true;

   }

   int32_t graphics::draw_text_ex(LPTSTR lpszString, int32_t nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {

      throw not_implemented(get_app());
      return 0 ;

/*
      if(get_handle1() == NULL)
         return -1;
      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = ::str::international::utf8_to_unicode(string(lpszString, nCount));
      return ::DrawTextExW(get_handle1(), const_cast<wchar_t *>((const wchar_t *)wstr), (int32_t)wcslen(wstr), lpRect, nFormat, lpDTParams);
*/
   }

   int32_t graphics::draw_text_ex(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {

      throw not_implemented(get_app());
      return 0;

/*
      ASSERT(get_handle1() != NULL);
      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = ::str::international::utf8_to_unicode(str);
      return ::DrawTextExW(get_handle1(), const_cast<wchar_t *>((const wchar_t *)wstr), (int32_t)wcslen(wstr), lpRect, nFormat, lpDTParams);
*/

   }

/**
 * Computes the text rectangle.
 * \return CUInt2dRectangle.
 */
   size graphics::GetTextExtent(const char * lpszString, strsize nCount, int32_t iIndex) const
   {

      synch_lock ml(&user_mutex());

      //int direction = 0, fontAscent = 0, fontDescent = 0;

      if(m_spfont.is_null())
         return size(0, 0);

      ((graphics *) this)->set(m_spfont);

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_spfont.m_p);

      if(pfont == NULL)
         return size(0, 0);

      XGlyphInfo extents;

      ZERO(extents);

//      wstring wstr(lpszString, nCount);

      XftTextExtentsUtf8 (m_pdc->m_pdisplay, pfont->m_pft, (const FcChar8 *) (const char *) lpszString, nCount, &extents);

      //XGCValues v;

      //XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

      //if(v.font == -1)
        // return size(0, 0);

      //array < XChar2b > x = utf8toXChar2b(&lpszString[iIndex], nCount - iIndex);

      //::XCharStruct charStruct;

      //::XQueryTextExtents16(m_pdc->m_pdisplay, ::XGContextFromGC(m_pdc->m_gc), x.get_data(), x.get_count(), &direction, &fontAscent, &fontDescent, &charStruct);

      //return ::size(charStruct.rbearing - charStruct.lbearing, fontAscent + fontDescent);

      return size(extents.width, extents.height);

   }


   size graphics::GetTextExtent(const char * lpszString, strsize nCount) const
   {

      return GetTextExtent(lpszString, nCount, 0);

   }


   size graphics::GetTextExtent(const string & str) const
   {

      return GetTextExtent(str, str.get_length());

   }


   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount) const
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

/*
      ASSERT(get_handle1() != NULL);
      SIZE size;
      string str(lpszString, nCount);
      wstring wstr = ::str::international::utf8_to_unicode(str);
      VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int32_t)wstr.get_length(), &size));
      return size;
*/

   }

   size graphics::GetOutputTextExtent(const string & str) const
   {

      throw not_implemented(get_app());
      return ::size(0, 0);

/*
      ASSERT(get_handle1() != NULL);
      SIZE size;
      wstring wstr = ::str::international::utf8_to_unicode(str);
      VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int32_t)wstr.get_length(), &size));
      return size;
*/
   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex) const
   {

      synch_lock ml(&user_mutex());

      class ::size  sz = GetTextExtent(lpszString, nCount, iIndex);

      size.cx = sz.cx;

      size.cy = sz.cy;

      return true;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount) const
   {

      return GetTextExtent(size, lpszString, nCount, 0);

   }


   bool graphics::GetTextExtent(sized & size, const string & str) const
   {

      return GetTextExtent(size, str, str.get_length(), 0);

   }



/*

   /////////////////////////////////////////////////////////////////////////////
   // Helper DCs


   void CClientDC::assert_valid() const
   {
      graphics::assert_valid();
      ASSERT(m_hWnd == NULL || ::IsWindow(m_hWnd));
   }

   void CClientDC::dump(dump_context & dumpcontext) const
   {
      graphics::dump(dumpcontext);

      dumpcontext << "get_handle1() = " << m_hWnd;
      dumpcontext << "\n";
   }


   CClientDC::CClientDC(window * pWnd)
   {
      ASSERT(pWnd == NULL || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

      if (!Attach(::GetDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
         throw resource_exception();
   }

   CClientDC::~CClientDC()
   {
      ASSERT(get_handle1() != NULL);
      ::ReleaseDC(m_hWnd, Detach());
   }


   void CWindowDC::assert_valid() const
   {
      graphics::assert_valid();
      ASSERT(m_hWnd == NULL || ::IsWindow(m_hWnd));
   }

   void CWindowDC::dump(dump_context & dumpcontext) const
   {
      graphics::dump(dumpcontext);

      dumpcontext << "get_handle1() = " << m_hWnd;
      dumpcontext << "\n";
   }


   CWindowDC::CWindowDC(window * pWnd)
   {
      ASSERT(pWnd == NULL || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

      if (!Attach(::GetWindowDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
         throw resource_exception();
   }

   CWindowDC::~CWindowDC()
   {
      ASSERT(get_handle1() != NULL);
      ::ReleaseDC(m_hWnd, Detach());
   }


   void CPaintDC::assert_valid() const
   {
      graphics::assert_valid();
      ASSERT(::IsWindow(m_hWnd));
   }

   void CPaintDC::dump(dump_context & dumpcontext) const
   {
      graphics::dump(dumpcontext);

      dumpcontext << "get_handle1() = " << m_hWnd;
      dumpcontext << "\nm_ps.hdc = " << m_ps.hdc;
      dumpcontext << "\nm_ps.fErase = " << m_ps.fErase;
      dumpcontext << "\nm_ps.rcPaint = " << (rect)m_ps.rcPaint;

      dumpcontext << "\n";
   }


   CPaintDC::CPaintDC(window * pWnd)
   {
      ASSERT_VALID(pWnd);
      ASSERT(::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

      if (!Attach(::BeginPaint(m_hWnd = WIN_WINDOW(pWnd)->get_handle1(), &m_ps)))
         throw resource_exception();
   }

   CPaintDC::~CPaintDC()
   {
      ASSERT(get_handle1() != NULL);
      ASSERT(::IsWindow(m_hWnd));

      ::EndPaint(m_hWnd, &m_ps);
      Detach();
   }

*/







   // IMPLEMENT_DYNAMIC(resource_exception, ::exception::base)
   //resource_exception _simpleResourceException(FALSE, __IDS_RESOURCE_EXCEPTION);

   // IMPLEMENT_DYNAMIC(user_exception, ::exception::base)
   //user_exception _simpleUserException(FALSE, __IDS_USER_EXCEPTION);

   // IMPLEMENT_DYNCREATE(graphics, object)
   // IMPLEMENT_DYNAMIC(CClientDC, graphics)
   // IMPLEMENT_DYNAMIC(CWindowDC, graphics)
   // IMPLEMENT_DYNAMIC(CPaintDC, graphics)
   // IMPLEMENT_DYNCREATE(object, object)

   // IMPLEMENT_DYNAMIC(pen, object)
   // IMPLEMENT_DYNAMIC(::draw2d::brush, object)
   // IMPLEMENT_DYNAMIC(::draw2d::font, object)
   // IMPLEMENT_DYNAMIC(::draw2d::bitmap, object)
   // IMPLEMENT_DYNAMIC(::draw2d::palette, object)
   // IMPLEMENT_DYNAMIC(::draw2d::region, object)


   void graphics::FillSolidRect(LPCRECT lpRect, COLORREF clr)
   {

      FillSolidRect(lpRect->left, lpRect->top, width(lpRect), height(lpRect), clr);

   }


   void graphics::FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr)
   {

      if(cx <= 0 || cy <= 0)
         return;

      synch_lock ml(&user_mutex());

      set_os_color(clr);

      XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x, y, cx, cy);

   }


   bool graphics::TextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount)
   {

      synch_lock ml(&user_mutex());

      if(m_spfont.is_null())
         return false;

      set(m_spfont);

/*      XGCValues v;

      XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

      if(v.font == -1)
         return false;*/

      int h = compute_line_height();

      /*set(m_spbrush);

      array < XChar2b > xa = utf8toXChar2b(lpszString, nCount);

      ::XDrawString16(
         m_pdc->m_pdisplay,
         m_pdc->m_drawable,
         m_pdc->m_gc,
         x + m_pdc->m_ptOffset.x,
         h + y + m_pdc->m_ptOffset.y,
         xa.get_data(),
         xa.get_count());*/


      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_spbitmap.m_p);

      if(pbitmap == NULL)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_spfont.m_p);

      if(pfont == NULL)
         return false;

      XftDraw * pdraw = XftDrawCreateAlpha (m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_iDepth);

      XRenderColor c;

      c.red = argb_get_r_value(m_spbrush->m_cr) * 255;
      c.green = argb_get_g_value(m_spbrush->m_cr) * 255;
      c.blue = argb_get_b_value(m_spbrush->m_cr) * 255;
      c.alpha = 0xffff;

      XftColor ftc;
      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

//      wstring wstr(lpszString, nCount);

      XftDrawStringUtf8(pdraw, &ftc, pfont->m_pft,
      x + m_pdc->m_ptOffset.x,
      y + h + m_pdc->m_ptOffset.y, (const FcChar8 *) (const char *) lpszString, nCount);

      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);


      return true;

   }


   bool graphics::TextOut(double x, double y, const char * lpszString, int32_t nCount)
   {

      return TextOut(int32_t(x), int32_t(y), lpszString, nCount);

   }



   bool graphics::LineTo(double x, double y)
   {

      synch_lock ml(&user_mutex());

      set(m_sppen);

      XDrawLine(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
         m_pdc->m_pt.x + m_pdc->m_ptOffset.x,
         m_pdc->m_pt.y + m_pdc->m_ptOffset.y,
         x + m_pdc->m_ptOffset.x,
         y + m_pdc->m_ptOffset.y);

      m_pdc->m_pt.x = x;

      m_pdc->m_pt.y = y;

      return true;

   }


   void graphics::set_alpha_mode(::draw2d::e_alpha_mode ealphamode)
   {

      synch_lock ml(&user_mutex());

      try
      {

         if(m_pdc == NULL)
            return;

/*
         ::draw2d::graphics::set_alpha_mode(ealphamode);
         if(m_ealphamode == ::draw2d::alpha_mode_blend)
         {
            xlib_set_operator(m_pdc, CAIRO_OPERATOR_OVER);
         }
         else if(m_ealphamode == ::draw2d::alpha_mode_set)
         {
            xlib_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
         }
*/
      }
      catch(...)
      {
         return;
      }

   }


   void graphics::set_text_rendering(::draw2d::e_text_rendering etextrendering)
   {
      m_etextrendering = etextrendering;

   }


   void * graphics::get_os_data() const
   {

      return (void *) m_pdc;

   }


/*   HDC graphics::get_handle() const
   {
      return m_hdc;
   }

   HDC graphics::get_handle1() const
   {
      return get_handle();
   }

   HDC graphics::get_handle2() const
   {
      return get_handle();
   }*/

   bool graphics::attach(void * pdata)
   {

      if(m_pdc != NULL)
      {
/*	if(m_pdc ==  xlib_keep::g_xlib)
	{
         printf("123");

	}

         xlib_destroy(m_pdc);*/

      }

      m_pdc = (device_context *) pdata;

      return true;

   }

/*
   Gdiplus::Font * graphics::gdiplus_font()
   {
      if(m_spfont.is_null())
      {
         m_spfont.create(get_app());
         m_spfont->operator=(m_fontxyz);
      }
      else if(!m_spfont->m_bUpdated)
      {
         m_spfont->m_bUpdated = true;
         m_spfont->operator=(m_fontxyz);
      }
      return (Gdiplus::Font *) m_spfont->get_os_data();
   }

   Gdiplus::Brush * graphics::gdiplus_brush()
   {
      if(m_spbrush.is_null())
      {
         m_spbrush.create(get_app());
         m_spbrush->operator=(m_brushxyz);
      }
      else if(!m_spbrush->m_bUpdated)
      {
         m_spbrush->m_bUpdated = true;
         m_spbrush->operator=(m_brushxyz);
      }
      return (Gdiplus::Brush *) m_spbrush->get_os_data();
   }

   Gdiplus::Pen * graphics::gdiplus_pen()
   {
      if(m_sppen.is_null())
      {
         m_sppen.create(get_app());
         m_sppen->operator=(m_penxyz);
      }
      else if(!m_sppen->m_bUpdated)
      {
         m_sppen->m_bUpdated = true;
         m_sppen->operator=(m_penxyz);
      }
      return (Gdiplus::Pen *) m_sppen->get_os_data();
   }*/


//   ::core::e_fill_mode graphics::gdiplus_get_fill_mode()
  // {
//      return ::draw2d::fill_mode_winding;
  // }

/*void xlib_image_surface_blur( xlib_surface_t* surface, double radius )
{
    // Steve Hanov, 2009
    // Released into the public domain.

    // get width, height
    int32_t width = xlib_image_surface_get_width( surface );
    int32_t height = xlib_image_surface_get_height( surface );
    unsigned char* dst = (unsigned char*)malloc(width*height*4);
    unsigned* precalc =
        (unsigned*)malloc(width*height*sizeof(unsigned));
    unsigned char* src = xlib_image_surface_get_data( surface );
    double mul=1.f/((radius*2)*(radius*2));
    int32_t channel;

    // The number of times to perform the averaging. According to wikipedia,
    // three iterations is good enough to pass for a gaussian.
    const int32_t MAX_ITERATIONS = 3;
    int32_t iteration;

    memcpy( dst, src, width*height*4 );

    for ( iteration = 0; iteration < MAX_ITERATIONS; iteration++ ) {
        for( channel = 0; channel < 4; channel++ ) {
            int32_t x,y;

            // precomputation step.
            unsigned char* pix = src;
            unsigned* pre = precalc;

            pix += channel;
            for (y=0;y<height;y++) {
                for (x=0;x<width;x++) {
                    int32_t tot=pix[0];
                    if (x>0) tot+=pre[-1];
                    if (y>0) tot+=pre[-width];
                    if (x>0 && y>0) tot-=pre[-width-1];
                    *pre++=tot;
                    pix += 4;
                }
            }

            // blur step.
            pix = dst + (int32_t)radius * width * 4 + (int32_t)radius * 4 + channel;
            for (y=(int32_t) radius;y<height-radius;y++) {
                for (x=(int32_t) radius;x<width-radius;x++) {
                    int32_t l = (int32_t) (x < radius ? 0 : x - radius);
                    int32_t t = (int32_t) (y < radius ? 0 : y - radius);
                    int32_t r = (int32_t) (x + radius >= width ? width - 1 : x + radius);
                    int32_t b = (int32_t) (y + radius >= height ? height - 1 : y + radius);
                    int32_t tot = precalc[r+b*width] + precalc[l+t*width] -
                        precalc[l+b*width] - precalc[r+t*width];
                    *pix=(unsigned char)(tot*mul);
                    pix += 4;
                }
                pix += (int32_t)radius * 2 * 4;
            }
        }
        memcpy( src, dst, width*height*4 );
    }

    free( dst );
    free( precalc );
}*/


   bool graphics::blur(bool bExpand, double dRadius, LPCRECT lpcrect)
   {

/*      xlib_pattern_t * ppattern = xlib_get_source(m_pdc);

      if(ppattern == NULL)
         return false;

      xlib_surface_t * psurfaceSrc = NULL;

      xlib_pattern_get_surface(ppattern, &psurfaceSrc);*/

      /*

      xlib_surface_t * psurface = xlib_surface_create_for_rectangle(psurfaceSrc, lpcrect->left, lpcrect->top, width(lpcrect), height(lpcrect));

      xlib_image_surface_blur(psurface, dRadius);

      */

      return true;

   }


   double graphics::get_dpix() const
   {

//      return m_pgraphics->GetDpiX();
      return 72.0;

   }


   bool graphics::set(const ::draw2d::brush * pbrushParam)
   {

      if(pbrushParam == NULL)
         return false;

      ::draw2d_xlib::brush * pbrush = dynamic_cast < ::draw2d_xlib::brush * > ((::draw2d::brush *) pbrushParam);

      if(pbrush == NULL)
         return false;

      if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
      {

         //xlib_pattern_t * ppattern = xlib_pattern_create_linear(pbrush->m_pt1.x, pbrush->m_pt1.y, pbrush->m_pt2.x, pbrush->m_pt2.y);

         //xlib_pattern_add_color_stop_rgba(ppattern, 0., argb_get_r_value(pbrush->m_cr1) / 255.0, argb_get_g_value(pbrush->m_cr1) / 255.0, argb_get_b_value(pbrush->m_cr1) / 255.0, argb_get_a_value(pbrush->m_cr1) / 255.0);

         //xlib_pattern_add_color_stop_rgba(ppattern, 1., argb_get_r_value(pbrush->m_cr2) / 255.0, argb_get_g_value(pbrush->m_cr2) / 255.0, argb_get_b_value(pbrush->m_cr2) / 255.0, argb_get_a_value(pbrush->m_cr2) / 255.0);

         //xlib_set_source(m_pdc, ppattern);

         //xlib_pattern_destroy(ppattern);

         //pbrush->get_os_data();

         pbrush->m_color.create(
            m_pdc->m_pdisplay,
            m_pdc->m_iScreen,
            (argb_get_r_value(pbrush->m_cr1) + argb_get_r_value(pbrush->m_cr2)) / 2,
            (argb_get_g_value(pbrush->m_cr1) + argb_get_g_value(pbrush->m_cr2)) / 2,
            (argb_get_b_value(pbrush->m_cr1) + argb_get_b_value(pbrush->m_cr2)) / 2,
            (argb_get_a_value(pbrush->m_cr1) + argb_get_a_value(pbrush->m_cr2)) / 2);

         XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, pbrush->m_color.m_color.pixel);

      }
      else
      {

         //pbrush->get_os_data();

         pbrush->m_color.create(
            m_pdc->m_pdisplay,
            m_pdc->m_iScreen,
            argb_get_r_value(pbrush->m_cr),
            argb_get_g_value(pbrush->m_cr),
            argb_get_b_value(pbrush->m_cr),
            argb_get_a_value(pbrush->m_cr));

         XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, pbrush->m_color.m_color.pixel);

      }

      return true;

   }


   bool graphics::set(const ::draw2d::pen * ppenParam)
   {

      if(ppenParam == NULL)
         return false;

      ::draw2d_xlib::pen * ppen = dynamic_cast < ::draw2d_xlib::pen * > ((::draw2d::pen *) ppenParam);

      if(ppen == NULL)
         return false;

      ppen->m_color.create(
         m_pdc->m_pdisplay,
         m_pdc->m_iScreen,
         argb_get_r_value(ppen->m_cr),
         argb_get_g_value(ppen->m_cr),
         argb_get_b_value(ppen->m_cr),
         argb_get_a_value(ppen->m_cr));

      XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, ppen->m_color.m_color.pixel);

      XSetLineAttributes(m_pdc->m_pdisplay, m_pdc->m_gc, ppen->m_dWidth, LineSolid, CapNotLast, JoinMiter);

      return true;

   }


   bool graphics::set(const ::draw2d::font * pfontParam)
   {

      if(pfontParam == NULL)
         return false;

      string strFont;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) pfontParam);

      if(pfont == NULL)
         return false;

      int iPoint = pfont->m_dFontSize;

      /*if(pfont->m_pfont != NULL)
      {

         XFreeFont(pfont->m_pdisplay, pfont->m_pfont);

         pfont->m_pfont = NULL;

      }*/

      if(pfont->m_pft != NULL)
      {

         XftFontClose(pfont->m_pdisplay, pfont->m_pft);

         pfont->m_pft = NULL;

      }


      //strFont.Format("-*-helvetica-*-r-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);

      char ** szMissing;
      int i;
      char * szmf;

      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                    XFT_FAMILY, XftTypeString, "helvetica",
                    pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                    NULL);

      //pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft != NULL)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

//      strFont.Format("-*-sans-*-r-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);
      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                    XFT_FAMILY, XftTypeString, "sans",
                    pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                    NULL);

//      pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft != NULL)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

  //    strFont.Format("-*-fixed-*-r-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);

      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                    XFT_FAMILY, XftTypeString, "sans",
                    pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                    NULL);
//      pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);


      if (pfont->m_pft != NULL)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

//      strFont = "fixed";
      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                    XFT_FAMILY, XftTypeString, "charter",
                    pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                    NULL);

  //    pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft == NULL)
         return false;

ok:

      pfont->m_pdisplay = m_pdc->m_pdisplay;

      //XSetFont (m_pdc->m_pdisplay, m_pdc->m_gc, pfont->m_pfont->fid);

      return true;

   }


   bool graphics::fill_and_draw()
   {

      /*bool bPen = m_sppen->m_etype != ::draw2d::pen::type_null;

      xlib_keep keep(this);

      if(m_spbrush->m_etype != ::draw2d::brush::type_null)
      {

         set(m_spbrush);

         set_alpha_mode(m_ealphamode);

         if(bPen)
         {

            xlib_fill_preserve(m_pdc);

         }
         else
         {

            xlib_fill(m_pdc);

         }

      }

      keep.pulse();

      if(bPen)
      {

         set(m_sppen);

         set_alpha_mode(m_ealphamode);

         xlib_stroke(m_pdc);


      }*/

      return false;

   }


   bool graphics::fill(::draw2d::brush * pbrush)
   {

      /*if(pbrush == NULL || pbrush->m_etype == ::draw2d::brush::type_null)
         return true;

      xlib_keep keep(m_pdc);

      set(pbrush);

      xlib_fill(m_pdc);*/

      return false;

   }


   bool graphics::draw(::draw2d::pen * ppen)
   {

      /*if(ppen == NULL || ppen->m_etype == ::draw2d::pen::type_null)
         return true;

      xlib_keep keep(m_pdc);

      set(ppen);

      xlib_stroke(m_pdc);*/

      return false;

   }


   bool graphics::set(const ::draw2d::path * ppathParam)
   {

      /*xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      ::draw2d_xlib::path * ppath = dynamic_cast < ::draw2d_xlib::path * > ((::draw2d::path *) ppathParam);

      for(int32_t i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         set(ppath->m_elementa[i]);

      }

      if(ppath->m_efillmode == ::draw2d::fill_mode_alternate)
      {

         xlib_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);

      }
      else
      {

         xlib_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);

      }*/

      return false;

   }


   bool graphics::set(const ::draw2d_xlib::path::element & e)
   {

/*      switch(e.m_etype)
      {
      case ::draw2d::path::element::type_arc:
         set(e.m_arc);
         break;
      case ::draw2d::path::element::type_line:
         set(e.m_line);
         break;
      case ::draw2d::path::element::type_move:
         set(e.m_move);
         break;
      case ::draw2d::path::element::type_end:
         {

            if(e.m_end.m_bClose)
            {
            xlib_close_path(m_pdc);
            }
         }
         break;
      default:
         throw "unexpected simple os graphics element type";
      }*/

      return false;

   }

   bool graphics::set(const ::draw2d_xlib::path::arc & a)
   {

/*      xlib_keep keep(m_pdc);

      xlib_translate(m_pdc, a.m_xCenter, a.m_yCenter);

      xlib_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);

      xlib_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);*/

      return true;

   }

   bool graphics::set(const ::draw2d_xlib::path::line & l)
   {

      /*if(!xlib_has_current_point(m_pdc))
      {

         xlib_move_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }
      else
      {

         xlib_line_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }*/

      return true;

   }


   bool graphics::set(const ::draw2d_xlib::path::move & p)
   {

      //xlib_move_to(m_pdc, p.m_x + 0.5, p.m_y + 0.5);

      return true;

   }



   bool graphics::fill()
   {

      return fill(m_spbrush);


   }

   bool graphics::draw()
   {

      return draw(m_sppen);

   }

    void * graphics::detach()
    {

       device_context * p = m_pdc;

       m_pdc = NULL;

       return p;
    }

    bool graphics::set_os_color(COLORREF cr)
    {

       //xlib_set_source_rgba(m_pdc, argb_get_r_value(cr) / 255.0, argb_get_g_value(cr) / 255.0, argb_get_b_value(cr) / 255.0, argb_get_a_value(cr) / 255.0);

      return true;

    }




/**
 * Computes text line height.
 * \return Text line height.
 */
   unsigned int graphics::compute_line_height()
   {

   size sz = GetTextExtent(L"Ac");
      return sz.cy;
/*
      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_spbitmap.m_p);

      if(pbitmap == NULL)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_spfont.m_p);

      if(pfont == NULL)
         return false;

      XftDraw * pdraw = XftDrawCreate (m_pdc->m_pdisplay, m_pdc->m_drawable, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap);

      XRenderColor c;

      c.red = argb_get_r_value(m_spbrush->m_cr);
      c.green = argb_get_g_value(m_spbrush->m_cr);
      c.blue = argb_get_b_value(m_spbrush->m_cr);
      c.alpha = argb_get_a_value(m_spbrush->m_cr);

      XftColor ftc;
      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

      XftDrawString8(pdraw, &ftc, pfont->m_pft,
      lpRect->left + dx + m_pdc->m_ptOffset.x,
      lpRect->top + h + dy + m_pdc->m_ptOffset.y, (FcChar8 *) (const char *) str, str.get_length());

      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->visual(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);*/

/*      if(m_spfont.is_null())
         return 0;

      set(m_spfont);

      XGCValues v;

      XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

      if(v.font == -1)
         return 0;

      ::draw2d_xlib::font * pfont = m_spfont.cast < ::draw2d_xlib::font >();

      if(pfont == NULL)
         return 0;

      return pfont->m_pfont->max_bounds.ascent + pfont->m_pfont->max_bounds.descent;*/


   }

} // namespace draw2d_xlib








array < XChar2b > utf8toXChar2b(const char *input, int inlen)
{

   array < XChar2b > output_r;

	int j, k;

	for(j = 0, k = 0; j < inlen; j++)
	{

		unsigned char c = input[j];

		if (c < 128)
		{
			output_r.element_at_grow(k).byte1 = 0;
			output_r.element_at_grow(k).byte2 = c;
			k++;
		}
		else if (c < 0xC0)
		{
			/* we're inside a character we don't know  */
			continue;
		}
		else switch(c & 0xF0)
		{
		case 0xC0:
		case 0xD0: /* two bytes 5+6 = 11 bits */
			if (inlen < j + 1)
			{
            return output_r;
         }
			output_r.element_at_grow(k).byte1 = (c & 0x1C) >> 2;
			j++;
			output_r.element_at_grow(k).byte2 = ((c & 0x3) << 6) + (input[j] & 0x3F);
			k++;
			break;
		case 0xE0: /* three bytes 4+6+6 = 16 bits */
			if (inlen < j + 2)
			{
            return output_r;
         }
			j++;
			output_r.element_at_grow(k).byte1 = ((c & 0xF) << 4) + ((input[j] & 0x3C) >> 2);
			c = input[j];
			j++;
			output_r.element_at_grow(k).byte2 = ((c & 0x3) << 6) + (input[j] & 0x3F);
			k++;
			break;
		case 0xFF:
			/* the character uses more than 16 bits */
			continue;
		}

	}

	return output_r;

}

