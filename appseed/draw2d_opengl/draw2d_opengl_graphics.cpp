#include "framework.h"
#include <math.h>


#undef new


BOOL CALLBACK draw2d_opengl_EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,DWORD FontType,LPVOID p);


class draw2d_opengl_enum_fonts
{
public:


   stringa &      m_stra;


   draw2d_opengl_enum_fonts(stringa & stra):
      m_stra(stra)
   {

   }


};


namespace draw2d_opengl
{


   graphics::graphics(::aura::application * papp) :
      object(papp),
      ::draw2d::graphics(papp)
   {
      m_ptTranslate = null_point();
      m_bPrinting       = FALSE;
      m_pdibAlphaBlend  = NULL;
      //m_pgraphics       = NULL;
      m_hdc             = NULL;
      m_hdcGraphics     = NULL;
//      m_ppath           = NULL;
      //m_ppathPaint      = NULL;
      m_etextrendering  = ::draw2d::text_rendering_anti_alias_grid_fit;
      m_dFontFactor     = 1.0;
      //m_pm = new plusplus::Matrix();

   }


   void graphics::assert_valid() const
   {

      object::assert_valid();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      dumpcontext << "get_handle1() = " << get_handle1();
      dumpcontext << "\nm_hAttribDC = " << get_handle2();
      dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";
   }


   graphics::~graphics()
   {

      DeleteDC();

   }


   //::window_sp graphics::GetWindow() const
   //{
   //   //ASSERT(get_handle1() != NULL); return ::draw2d_opengl::user::interaction_impl::from_handle(::WindowFromDC(get_handle1()));
   //   return NULL;
   //}

   bool graphics::IsPrinting() const
   {
      return m_bPrinting;
   }

   bool graphics::CreateDC(const char * lpszDriverName,
                           const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }

   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      HDC hdc = Detach();

      if(hdc != NULL)
      {

         bool bDeleted = ::DeleteDC(hdc) != FALSE;

         if(!bDeleted)
         {

            TRACE("Failed to delete GDI device context");

         }

      }

      if(m_hdcGraphics != NULL)
      {

//         m_pgraphics->ReleaseHDC(m_hdcGraphics);

         m_hdcGraphics = NULL;

      }

      //if(m_pgraphics != NULL)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      TRACE("graphics::CreateCompatibleDC(::draw2d::graphics * ) : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = NULL;

      //}

      //if(pgraphics == NULL)
      //{

      //   hdc = ::CreateCompatibleDC(NULL);

      //}
      //else if(GL2D_GRAPHICS(pgraphics)->m_hdc != NULL)
      //{

      //   hdc = ::CreateCompatibleDC(GL2D_GRAPHICS(pgraphics)->m_hdc);

      //}
      //else if(GL2D_GRAPHICS(pgraphics)->m_hdcGraphics != NULL)
      //{

      //   hdc = ::CreateCompatibleDC(GL2D_GRAPHICS(pgraphics)->m_hdcGraphics);

      //}
      //else
      //{

      //   HDC hdcTemplate = ((plusplus::Graphics *) pgraphics->get_os_data())->GetHDC();

      //   hdc = ::CreateCompatibleDC(hdcTemplate);

      //   ((plusplus::Graphics *) pgraphics->get_os_data())->ReleaseHDC(hdc);

      //}

      //if(hdc == NULL)
      //   return false;

      //m_hdc = hdc;

      //m_pgraphics = new plusplus::Graphics(m_hdc);

      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      return true;

   }


   int32_t graphics::ExcludeUpdateRgn(::user::primitive * pwindow)
   {
      ASSERT(get_handle1() != NULL);
      ::exception::throw_not_implemented(get_app());
      //return ::ExcludeUpdateRgn(get_handle1(), WIN_WINDOW(pwindow)->get_handle());
      return 0;
   }

   int32_t graphics::GetDeviceCaps(int32_t nIndex) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetDeviceCaps(get_handle2(), nIndex);
   }

   point graphics::GetBrushOrg() const
   {
      ASSERT(get_handle1() != NULL);
      POINT point;
      VERIFY(::GetBrushOrgEx(get_handle1(), &point));
      return point;
   }

   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {
      ASSERT(get_handle1() != NULL);
      POINT point;
      VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
      return point;
   }

   point graphics::SetBrushOrg(POINT point)
   {
      ASSERT(get_handle1() != NULL);
      VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
      return point;
   }

   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      ASSERT(get_handle2() != NULL);
      return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);
   }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap * pBitmap)
   {


      if(pBitmap == NULL)
         return NULL;

      m_spbitmap = pBitmap;

      /*      if(get_handle1() == NULL)
               return NULL;
            if(pBitmap == NULL)
               return NULL;
            return dynamic_cast < ::draw2d::bitmap* > (SelectGdiObject(get_app(), get_handle1(), pBitmap->get_os_data()));*/
      //if(m_pgraphics != NULL)
      //{
      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      TRACE("graphics::SelectObject(::draw2d::bitmap *) : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = NULL;

      //}

      //m_pgraphics = new plusplus::Graphics((plusplus::Bitmap *) pBitmap->get_os_data());

      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      //set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //m_spbitmap = pBitmap;

      return m_spbitmap;
   }


   ::draw2d::object* graphics::SelectObject(::draw2d::object* pObject)
   {
      /*      ASSERT(get_handle1() != NULL);
         if(pObject == NULL)
            return NULL;
         return SelectGdiObject(get_app(), get_handle1(), pObject->get_os_data()); */
      return NULL;
   }

   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
   {

      UINT uiType = GetObjectType(hObject);

      if(uiType == OBJ_BITMAP)
      {

         HBITMAP hbitmap = (HBITMAP) hObject;

         if(m_spbitmap.is_null())
            m_spbitmap.alloc(allocer());

         if(m_spbitmap.is_null())
            return NULL;

         //(dynamic_cast < ::draw2d_opengl::bitmap * > (m_spbitmap.m_p))->m_pbitmap = new plusplus::Bitmap(hbitmap, NULL);

         //if(m_pgraphics != NULL)
         //{

         //   try
         //   {

         //      delete m_pgraphics;

         //   }
         //   catch(...)
         //   {

         //      TRACE("graphics::SelectObject(HGDIOBJ) OBJ_BITMAP : Failed to delete plusplus::Graphics");

         //   }

         //   m_pgraphics = NULL;

         //}

         //m_pgraphics = new plusplus::Graphics((plusplus::Bitmap *) m_spbitmap->get_os_data());

         //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

         //set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

         return hbitmap;

      }

      //*ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object
      //return (hObject != NULL) ? ::SelectObject(get_handle1(), hObject) : NULL; */
      return NULL;
   }

   COLORREF graphics::GetNearestColor(COLORREF crColor) const
   {
      return ::GetNearestColor(get_handle2(), crColor);
   }

   UINT graphics::RealizePalette()
   {
      return ::RealizePalette(get_handle1());
   }

   void graphics::UpdateColors()
   {
      ::UpdateColors(get_handle1());
   }

   int32_t graphics::GetPolyFillMode() const
   {
      return ::GetPolyFillMode(get_handle2());
   }

   int32_t graphics::GetROP2() const
   {
      return ::GetROP2(get_handle2());
   }

   int32_t graphics::GetStretchBltMode() const
   {
      return ::GetStretchBltMode(get_handle2());
   }

   int32_t graphics::GetMapMode() const
   {
      return ::GetMapMode(get_handle2());
   }

   int32_t graphics::GetGraphicsMode() const
   {
      return ::GetGraphicsMode(get_handle2());
   }

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {



      //m_pgraphics->GetTransform(((graphics *)this)->m_pm);

      //plusplus::REAL r[6];

      //m_pm->GetElements(r);

      //pXform->eM11 = r[0];
      //pXform->eM12 = r[1];
      //pXform->eM21 = r[2];
      //pXform->eM22 = r[3];

      //pXform->eDx = r[4];
      //pXform->eDy = r[5];


      return true;

   }

   size graphics::GetViewportExt() const
   {
      SIZE size;
      ::GetViewportExtEx(get_handle2(), &size);
      return size;
   }

   point graphics::GetWindowOrg() const
   {
      POINT point;
      ::GetWindowOrgEx(get_handle2(), &point);
      return point;
   }

   size graphics::GetWindowExt() const
   {
      SIZE size;
      ::GetWindowExtEx(get_handle2(), &size);
      return size;
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {

      return SetViewportOrg(point.x, point.y);

   }

   size graphics::SetViewportExt(SIZE size)
   {
      return SetViewportExt(size.cx, size.cy);
   }

   point graphics::SetWindowOrg(POINT point)
   {
      return SetWindowOrg(point.x, point.y);
   }

   size graphics::SetWindowExt(SIZE size)
   {
      return SetWindowExt(size.cx, size.cy);
   }

   void graphics::DPtoLP(LPPOINT lpPoints, count nCount) const
   {
      ::DPtoLP(get_handle2(), lpPoints, (int) nCount);
   }

   void graphics::DPtoLP(LPRECT lpRect) const
   {
      ::DPtoLP(get_handle2(), (LPPOINT)lpRect, 2);
   }

   void graphics::LPtoDP(LPPOINT lpPoints,count nCount) const
   {
      ::LPtoDP(get_handle2(), lpPoints, (int)  nCount);
   }

   void graphics::LPtoDP(LPRECT lpRect) const
   {
      ::LPtoDP(get_handle2(), (LPPOINT)lpRect, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != FALSE;

   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {

      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != FALSE;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      ASSERT(get_handle1() != NULL);

      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != FALSE;

   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

      ASSERT(get_handle1() != NULL);

      return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != FALSE;

   }

   bool graphics::PtVisible(int32_t x, int32_t y) const
   {

      ASSERT(get_handle1() != NULL);

      return ::PtVisible(get_handle1(), x, y) != FALSE;

   }

   bool graphics::PtVisible(POINT point) const
   {
      ASSERT(get_handle1() != NULL);   // call virtual
      return PtVisible(point.x, point.y);
   }

   bool graphics::RectVisible(const RECT &  lpRect) const
   {

      ASSERT(get_handle1() != NULL);

      return ::RectVisible(get_handle1(), &lpRect) != FALSE;

   }

   point graphics::GetCurrentPosition() const
   {
      ASSERT(get_handle2() != NULL);
      POINT point;
      VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
      return point;
   }

   bool graphics::Polyline(const POINT* lpPoints,count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      bool bOk1 = FALSE;

      //plusplus::Point * ppoints = new plusplus::Point[nCount];

      //try
      //{

      //   for(int32_t i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }

      //   bOk1 = m_pgraphics->DrawLines(gl2d_pen(),ppoints,(INT) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      return bOk1;
   }


   bool graphics::Arc(int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3,int32_t x4,int32_t y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / System.math().GetPi();
      double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / System.math().GetPi();
      double sweep      = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return Arc(x1,y1,x2-x1,y2-y1,start,sweep);

   }


   bool graphics::Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / System.math().GetPi();
      double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / System.math().GetPi();
      double sweep      = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return Arc(x1,y1, x2-x1, y2-y1, start, sweep);

   }


   bool graphics::Arc(int32_t x1,int32_t y1,int32_t w,int32_t h,double start, double extends)
   {

      //::plusplus::Rect rect(x1,y1,w,h);

      //return m_pgraphics->DrawArc(gl2d_pen(),rect,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::Arc(double x1,double y1,double w,double h,double start,double extends)
   {

      //::plusplus::RectF rectf((plusplus::REAL) x1,(plusplus::REAL) y1,(plusplus::REAL) w,(plusplus::REAL) h);

      //return m_pgraphics->DrawArc(gl2d_pen(),rectf,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

      return true;

   }


   void graphics::FillRect(const RECT & rectParam, ::draw2d::brush* pbrush)
   {

      //plusplus::Rect rect(rectParam.left,rectParam.top,width(rectParam),height(rectParam));

      //set_smooth_mode(::draw2d::smooth_mode_none);

      //m_pgraphics->FillRectangle((::plusplus::Brush *) pbrush->get_os_data(),rect);


   }


   void graphics::FrameRect(const RECT &  rectParam,::draw2d::brush* pBrush)
   {

      //ASSERT(get_handle1() != NULL);

      //::FrameRect(get_handle1(),&rectParam,(HBRUSH)pBrush->get_os_data());

   }


   bool graphics::DrawRect(const RECT & rectParam,::draw2d::pen * ppen)
   {

      //plusplus::Rect rect(rectParam.left,rectParam.top,width(rectParam), height(rectParam));

      //return m_pgraphics->DrawRectangle((::plusplus::Pen *) ppen->get_os_data(), rect) == ::plusplus::Ok;


      try
      {

         if (m_spbitmap.is_null())
            return false;

         ::size s = m_spbitmap.cast < bitmap>()->m_sizeOut;

         if (s.area() <= 0)
            return false;

         if (is_ptr_null(ppen, 1024))
            return false;

         m_spbitmap.cast < bitmap>()->flash();

         glColor4f(argb_get_r_value(ppen->m_cr) / 255.f, argb_get_g_value(ppen->m_cr) / 255.f, argb_get_b_value(ppen->m_cr) / 255.f, argb_get_a_value(ppen->m_cr) / 255.f);						// Set Top Point Of Triangle To Red
         glEnd();
         glLineWidth(ppen->m_dWidth);
         glBegin(GL_LINE_LOOP);
         glVertex2f(rectParam.left, rectParam.top);
         glVertex2f(rectParam.right, rectParam.top);
         glVertex2f(rectParam.right, rectParam.bottom);
         glVertex2f(rectParam.left, rectParam.bottom);
         //glVertex2f(rectParam.left, rectParam.top);
         glEnd();


         //if(m_pgraphics == NULL)
         //   return;

         //if(m_esmoothmode != ::draw2d::smooth_mode_none)
         //{

         //   set_smooth_mode(::draw2d::smooth_mode_none);

         //}
         //else
         //{
         //   //TRACE("optimized smoothing mode");
         //}

         //::draw2d::brush_sp brushCurrent;

         //if(m_spbrush.is_null() || m_spbrush->m_etype != ::draw2d::brush::type_solid || m_spbrush->m_cr != clr)
         //{

         //   brushCurrent = m_spbrush;

         //   ::draw2d::brush_sp brush(allocer(),clr);

         //   SelectObject(brush);

         //}
         //else
         //{

         //   //TRACE("optimized brush");

         //}

         //m_pgraphics->FillRectangle(gl2d_brush(), x, y, cx, cy);


      }
      catch (...)
      {
         return false;
      }


      return true;

   }


   void graphics::InvertRect(const RECT &  rectParam)
   {
      ASSERT(get_handle1() != NULL);
      ::InvertRect(get_handle1(),&rectParam);
   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon)
   {

      ASSERT(get_handle1() != NULL);

      if(picon == NULL)
         return false;

      return ::DrawIcon(get_handle1(), x, y, (HICON) picon->m_picon) != FALSE;

   }

   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {

      ASSERT(get_handle1() != NULL);

      if(picon == NULL)
         return false;

      return ::DrawIcon(get_handle1(), point.x, point.y, (HICON) picon->m_picon) != FALSE;

   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {

      //try
      //{

      //   if(picon == NULL)
      //      return FALSE;

      //   if(m_pgraphics == NULL)
      //      return FALSE;

      //   bool bOk = FALSE;

      //   BITMAPINFO info;
      //   COLORREF * pcolorref;

      //   ZeroMemory(&info, sizeof (BITMAPINFO));

      //   info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      //   info.bmiHeader.biWidth         = cx;
      //   info.bmiHeader.biHeight        = - cy;
      //   info.bmiHeader.biPlanes        = 1;
      //   info.bmiHeader.biBitCount      = 32;
      //   info.bmiHeader.biCompression   = BI_RGB;
      //   info.bmiHeader.biSizeImage     = cx * cy * 4;

      //   HBITMAP hbitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void **) &pcolorref, NULL, 0);

      //   HDC hdc = ::CreateCompatibleDC(NULL);

      //   HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

      //   ICONINFO ii;
      //   BITMAPINFO biC;
      //   BITMAPINFO biM;

      //   ZERO(biC);
      //   ZERO(biM);



      //   if(::GetIconInfo((HICON)picon->m_picon,&ii))
      //   {

      //      ::GetObject(ii.hbmColor,sizeof(biC),(LPVOID)&biC);

      //      ::GetObject(ii.hbmMask,sizeof(biM),(LPVOID)&biM);

      //   }



      //   if(!::DrawIconEx(hdc,0,0,(HICON)picon->m_picon,cx,cy,istepIfAniCur,NULL,DI_IMAGE | DI_MASK))
      //   {

      //      output_debug_string("nok");
      //   }
      //   else
      //   {

      //      bool bAllZeroAlpha = true;
      //      bool bTheresUint32 = false;

      //      int area = cx * cy;

      //      COLORREF * pc = pcolorref;
      //      BYTE * pA = &((BYTE *) pcolorref)[3];

      //      for(int i = 0; i < area; i++)
      //      {
      //         if(*pc != 0)
      //         {
      //            bTheresUint32 = true;
      //         }
      //         if(*pA != 0)
      //         {
      //            bAllZeroAlpha = false;
      //            break;
      //         }
      //         pc++;
      //         pA +=4;
      //      }

      //      if(bAllZeroAlpha && bTheresUint32)
      //      {

      //         pc = pcolorref;
      //         pA = &((BYTE *)pcolorref)[3];

      //         for(int i = 0; i < area; i++)
      //         {
      //            if(*pc != 0)
      //            {
      //               *pA = 255;
      //            }
      //            pc++;
      //            pA +=4;
      //         }
      //      }

      //      ::SelectObject(hdc, hbitmapOld);

      //      try
      //      {

      //         plusplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (BYTE *) pcolorref);

      //         bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, plusplus::UnitPixel) == plusplus::Ok;

      //      }
      //      catch(...)
      //      {
      //      }

      //   }

      //   ::DeleteDC(hdc);

      //   ::DeleteObject(hbitmap);

      //   return bOk;

      //}
      //catch(...)
      //{
      //   return FALSE;
      //}

      //return ::DrawIconEx(get_handle1(), x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

return true;

   }

   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {

      ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {

      ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)pBitmap->get_os_data(), 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {

      ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }


   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   {

      ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, HBRUSH hBrush)
   {

      ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), hBrush,  NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::draw2d::brush* pBrush)
   {

      ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   {  ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), hBrush,
                         lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;
   }
   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
   {  ASSERT(get_handle1() != NULL);
      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(),
                         lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;
   }
   bool graphics::DrawEdge(const RECT & rectParam,UINT nEdge,UINT nFlags)
   {
      ASSERT(get_handle1() != NULL);
      return ::DrawEdge(get_handle1(),(LPRECT)&rectParam,nEdge,nFlags) != FALSE;
   }
   bool graphics::DrawFrameControl(const RECT & rectParam,UINT nType,UINT nState)
   {
      ASSERT(get_handle1() != NULL);
      return ::DrawFrameControl(get_handle1(),(LPRECT) &rectParam,nType,nState) != FALSE;
   }

   bool graphics::Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3,
                        int32_t x4, int32_t y4)
   {
      ASSERT(get_handle1() != NULL);
      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
   }
   bool graphics::Chord(const RECT &  rectParam,POINT ptStart,POINT ptEnd)
   {
      ASSERT(get_handle1() != NULL);
      return ::Chord(get_handle1(),rectParam.left,rectParam.top,
                     rectParam.right,rectParam.bottom,ptStart.x,ptStart.y,
                     ptEnd.x, ptEnd.y) != FALSE;
   }
   void graphics::DrawFocusRect(const RECT &  rectParam)
   {
      ASSERT(get_handle1() != NULL);
      ::DrawFocusRect(get_handle1(),&rectParam);
   }


   bool graphics::DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(gl2d_pen(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

      return true;
   }


   bool graphics::DrawEllipse(const RECT &  rectParam)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(gl2d_pen(),rectParam.left,rectParam.top,rectParam.right - rectParam.left,rectParam.bottom - rectParam.top)) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->FillEllipse(gl2d_brush(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

      return true;

   }

   bool graphics::FillEllipse(const RECT &  rectParam)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

//      return (m_pgraphics->FillEllipse(gl2d_brush(), rectParam.left, rectParam.top, rectParam.right - rectParam.left, rectParam.bottom - rectParam.top)) == plusplus::Status::Ok;

      return true;

   }



   bool graphics::DrawEllipse(double x1,double y1,double x2,double y2)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(gl2d_pen(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::DrawEllipse(const RECTD & rectParam)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(gl2d_pen(),(plusplus::REAL)rectParam.left,(plusplus::REAL)rectParam.top,
      //                                 (plusplus::REAL)(rectParam.right - rectParam.left),
      //                                 (plusplus::REAL)(rectParam.bottom - rectParam.top))) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::FillEllipse(double x1,double y1,double x2,double y2)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->FillEllipse(gl2d_brush(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

      return true;

   }

   bool graphics::FillEllipse(const RECTD & rectParam)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->FillEllipse(gl2d_brush(),(plusplus::REAL)rectParam.left,(plusplus::REAL)rectParam.top,
      //                                 (plusplus::REAL)(rectParam.right - rectParam.left),
      //                                 (plusplus::REAL)(rectParam.bottom - rectParam.top))) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      ASSERT(get_handle1() != NULL);
      return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
   }
   bool graphics::Pie(const RECT &  rectParam,POINT ptStart,POINT ptEnd)
   {  ASSERT(get_handle1() != NULL);
      return ::Pie(get_handle1(), rectParam.left, rectParam.top,
                   rectParam.right, rectParam.bottom, ptStart.x, ptStart.y,
                   ptEnd.x, ptEnd.y) != FALSE;
   }

   bool graphics::fill_polygon(const POINTD * lpPoints,count nCount)
   {

   //   if(nCount <= 0)
   //      return TRUE;

   //   bool bOk1 = FALSE;

   //   plusplus::PointF * ppoints = new plusplus::PointF[nCount];

   //   try
   //   {

   //      for(int32_t i = 0; i < nCount; i++)
   //      {
   //         ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
   //         ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
   //      }

   //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //      set_smooth_mode(::draw2d::smooth_mode_high);


   //      bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (INT) nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

   //   }
   //   catch(...)
   //   {
   //   }

   //   try
   //   {
   //      delete ppoints;
   //   }
   //   catch(...)
   //   {
   //   }


   //   return bOk1;

      return true;
   }

   bool graphics::fill_polygon(const POINT* lpPoints,count nCount)
   {

   //   if(nCount <= 0)
   //      return TRUE;

   //   bool bOk1 = FALSE;

   //   plusplus::Point * ppoints = new plusplus::Point[nCount];

   //   try
   //   {

   //      for(int32_t i = 0; i < nCount; i++)
   //      {
   //         ppoints[i].X = lpPoints[i].x;
   //         ppoints[i].Y = lpPoints[i].y;
   //      }

   //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //      bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (INT)  nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

   //   }
   //   catch(...)
   //   {
   //   }

   //   try
   //   {
   //      delete ppoints;
   //   }
   //   catch(...)
   //   {
   //   }


   //   return bOk1;

      return true;
   }

   bool graphics::draw_polygon(const POINT* lpPoints,count nCount)
   {

      //if (nCount <= 0)
      //   return TRUE;

      //bool bOk1 = FALSE;

      //plusplus::Point * ppoints = new plusplus::Point[nCount];

      //try
      //{

      //   for (int32_t i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   set_smooth_mode(::draw2d::smooth_mode_high);

      //   bOk1 = m_pgraphics->DrawPolygon(gl2d_pen(), ppoints, (INT) nCount) == plusplus::Status::Ok;

      //}
      //catch (...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch (...)
      //{
      //}


      //return bOk1;
      return true;
   }

   bool graphics::draw_polygon(const POINTD* lpPoints,count nCount)
   {

      //if(nCount <= 0)
      //   return TRUE;

      //bool bOk1 = FALSE;

      //plusplus::PointF * ppoints = new plusplus::PointF[nCount];

      //try
      //{

      //   for(int32_t i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
      //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   bOk1 = m_pgraphics->DrawPolygon(gl2d_pen(),ppoints,(INT) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1;

      return true;
   }

   bool graphics::Polygon(const POINT* lpPoints,count nCount)
   {

      //if(nCount <= 0)
      //   return TRUE;

      //bool bOk1 = FALSE;

      //bool bOk2 = FALSE;

      //plusplus::Point * ppoints = new plusplus::Point[nCount];

      //try
      //{

      //   for(int32_t i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }


      //   set_smooth_mode(::draw2d::smooth_mode_high);

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //   bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (INT) nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   bOk2 = m_pgraphics->DrawPolygon(gl2d_pen(), ppoints, (INT) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1 && bOk2;

      return true;

   }


   bool graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts,count nCount)
   {

      ASSERT(get_handle1() != NULL);


      return ::PolyPolygon(get_handle1(), lpPoints, (const INT *) lpPolyCounts, (int) nCount) != FALSE;

   }


   bool graphics::Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      //plusplus::RectF rectf((plusplus::REAL) x1, (plusplus::REAL) y1, (plusplus::REAL) (x2 - x1), (plusplus::REAL) (y2 - y1));

      //bool bOk1 = m_pgraphics->FillRectangle(gl2d_brush(), rectf) == plusplus::Status::Ok;

      //bool bOk2 = m_pgraphics->DrawRectangle(gl2d_pen(), rectf) == plusplus::Status::Ok;

      //return bOk1 && bOk2;

      return true;

   }

   bool graphics::Polygon(const POINTD* lpPoints,count nCount)
   {

      //if(nCount <= 0)
      //   return TRUE;

      //bool bOk1 = FALSE;

      //bool bOk2 = FALSE;

      //plusplus::PointF * ppoints = new plusplus::PointF[nCount];

      //try
      //{

      //   for(int32_t i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
      //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   if(m_ealphamode == ::draw2d::alpha_mode_set)
      //   {

      //      set_smooth_mode(::draw2d::smooth_mode_none);

      //   }
      //   else
      //   {

      //      set_smooth_mode(::draw2d::smooth_mode_high);

      //   }


      //   bOk1 = m_pgraphics->FillPolygon(gl2d_brush(),ppoints,(INT) nCount,gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   bOk2 = m_pgraphics->DrawPolygon(gl2d_pen(),ppoints,(INT) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1 && bOk2;

      return true;

   }

   bool graphics::Rectangle(const RECT &  rectParam)
   {

      return Rectangle(rectParam.left, rectParam.top, rectParam.right, rectParam.bottom);

   }

   bool graphics::DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      //plusplus::RectF rectf((plusplus::REAL) x1, (plusplus::REAL) y1, (plusplus::REAL) (x2 - x1), (plusplus::REAL) (y2 - y1));

      //bool bOk = m_pgraphics->DrawRectangle(gl2d_pen(), rectf) == plusplus::Status::Ok;

      //return bOk;

      return true;

   }

   bool graphics::DrawRectangle(const RECT &  rectParam)
   {

      return DrawRectangle(rectParam.left, rectParam.top, rectParam.right, rectParam.bottom);

   }

   bool graphics::FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      //plusplus::RectF rectf((plusplus::REAL) x1, (plusplus::REAL) y1, (plusplus::REAL) (x2 - x1), (plusplus::REAL) (y2 - y1));

      //bool bOk = m_pgraphics->FillRectangle(gl2d_brush(), rectf) == plusplus::Status::Ok;

      //return bOk;

      return true;

   }

   bool graphics::FillRectangle(const RECT &  rectParam)
   {

      return FillRectangle(rectParam.left, rectParam.top, rectParam.right, rectParam.bottom);

   }

   bool graphics::RoundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
   {
      ASSERT(get_handle1() != NULL);
      return ::RoundRect(get_handle1(), x1, y1, x2, y2, x3, y3) != FALSE;
   }
   bool graphics::RoundRect(const RECT &  rectParam,POINT point)
   {  ASSERT(get_handle1() != NULL);
      return ::RoundRect(get_handle1(), rectParam.left, rectParam.top,
                         rectParam.right, rectParam.bottom, point.x, point.y) != FALSE;
   }
   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop)
   {
      ASSERT(get_handle1() != NULL);
      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != FALSE;
   }


   bool graphics::BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop)
   {
//      if (m_pgraphics == NULL)
//         return FALSE;
//
//      if (::draw2d::graphics::BitBlt(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop))
//         return true;
//
      try
      {

         if(pgraphicsSrc == NULL)
            return FALSE;

         if (pgraphicsSrc->get_current_bitmap() == NULL)
            return FALSE;

         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == NULL)
            return FALSE;

         pgraphicsSrc->get_current_bitmap().cast <bitmap>()->create_texture(0);

         glBegin(GL_QUADS);
         // Front Face
         glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
         glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
         glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
         glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);


//
//
//         return m_pgraphics->DrawImage(
//                   (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),
//                   x, y, xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y, nWidth, nHeight, plusplus::UnitPixel) == plusplus::Status::Ok;
//
      }
      catch(...)
      {
         return FALSE;
      }
//
//      //return ::BitBlt(get_handle1(), x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, dwRop);
//
//gdi_fallback:
//
//      HDC hdcDst = get_hdc();
//
//      if(hdcDst == NULL)
//         return false;
//
//      HDC hdcSrc = GL2D_GRAPHICS(pgraphicsSrc)->get_hdc();
//
//      if(hdcSrc == NULL)
//      {
//
//         release_hdc(hdcDst);
//
//         return false;
//
//      }
//
//      bool bOk = ::BitBlt(hdcDst, x, y, nWidth, nHeight, hdcSrc, x, y, dwRop) != FALSE;
//
//      GL2D_GRAPHICS(pgraphicsSrc)->release_hdc(hdcSrc);
//
//      release_hdc(hdcDst);
//
//      return bOk;

      return true;

   }


   bool graphics::StretchBlt(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop)
   {

      //if(pgraphicsSrc == NULL)
      //   return FALSE;

      //plusplus::RectF dstRect((plusplus::REAL) xDst, (plusplus::REAL) yDst, (plusplus::REAL) nDstWidth, (plusplus::REAL) nDstHeight);

      //plusplus::RectF srcRect((plusplus::REAL) xSrc, (plusplus::REAL) ySrc, (plusplus::REAL) nSrcWidth, (plusplus::REAL) nSrcHeight);

      //if(pgraphicsSrc == NULL || pgraphicsSrc->get_current_bitmap() == NULL)
      //   return false;

      //try
      //{
      //   return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),  dstRect, srcRect, plusplus::UnitPixel) == plusplus::Status::Ok;
      //}
      //catch(...)
      //{

      //}

      //return FALSE;

      ////return ::StretchBlt(get_handle1(), x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);

      return true;

   }


   COLORREF graphics::GetPixel(int32_t x, int32_t y) const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetPixel(get_handle1(), x, y);
   }
   COLORREF graphics::GetPixel(POINT point) const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetPixel(get_handle1(), point.x, point.y);
   }
   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {
      return 0;
   }
   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {

      FillSolidRect(point.x,point.y,1,1,crColor);

      return crColor;

   }
   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {
      ASSERT(get_handle1() != NULL);
      return ::FloodFill(get_handle1(), x, y, crColor) != FALSE;
   }
   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {
      ASSERT(get_handle1() != NULL);
      return ::ExtFloodFill(get_handle1(), x, y, crColor, nFillType) != FALSE;
   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::TextOut(int32_t x, int32_t y, const string & str)
   {

      return TextOut((double) x, (double) y, str, (int32_t) str.get_length());

   }


   bool graphics::TextOut(double x, double y, const string & str)
   {

      return TextOut(x, y, str, (int32_t) str.get_length());

   }


   bool graphics::ExtTextOut(int32_t x,int32_t y,UINT nOptions,const RECT &  rectParam,const char * lpszString,strsize nCount,LPINT lpDxWidths)
   {

      ASSERT(get_handle1() != NULL);

      return ::ExtTextOut(get_handle1(),x,y,nOptions,&rectParam,lpszString,(UINT) nCount,lpDxWidths) != FALSE;

   }


   bool graphics::ExtTextOut(int32_t x,int32_t y,UINT nOptions,const RECT &  rectParam, const string & str, LPINT lpDxWidths)
   {

      ASSERT(get_handle1() != NULL);

      return ::ExtTextOut(get_handle1(),x,y,nOptions,&rectParam, str, (UINT)str.get_length(), lpDxWidths) != FALSE;

   }


   size graphics::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      ASSERT(get_handle1() != NULL);

      return ::TabbedTextOut(get_handle1(), x, y, lpszString, (int) nCount, (int) nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   size graphics::TabbedTextOut(int32_t x, int32_t y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      ASSERT(get_handle1() != NULL);

      return ::TabbedTextOut(get_handle1(), x, y, str, (int32_t)str.get_length(), (int) nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) const
   {

      ASSERT(get_handle2() != NULL);

      return ::GetTabbedTextExtent(get_handle2(), lpszString, (int32_t) nCount, (int) nTabPositions, lpnTabStopPositions);

   }


   size graphics::GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) const
   {

      ASSERT(get_handle2() != NULL);

      return ::GetTabbedTextExtent(get_handle2(), str, (int32_t) str.get_length(), (int) nTabPositions, lpnTabStopPositions);

   }


   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) const
   {

      ASSERT(get_handle1() != NULL);

      return ::GetTabbedTextExtent(get_handle1(), lpszString, (int32_t) nCount, (int) nTabPositions, lpnTabStopPositions);

   }


   size graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) const
   {

      ASSERT(get_handle1() != NULL);

      return ::GetTabbedTextExtent(get_handle1(), str, (int32_t) str.get_length(), (int) nTabPositions, lpnTabStopPositions);

   }


   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount,int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
   {

      ASSERT(get_handle1() != NULL);

      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != FALSE;

   }


   UINT graphics::GetTextAlign() const
   {

      ASSERT(get_handle2() != NULL);

      return ::GetTextAlign(get_handle2());

   }


   int32_t graphics::GetTextFace(count nCount, LPTSTR lpszFacename) const
   {

      ASSERT(get_handle2() != NULL);

      return ::GetTextFace(get_handle2(), (int) nCount, lpszFacename);

   }


   int32_t graphics::GetTextFace(string & rString) const
   {

      ASSERT(get_handle2() != NULL);

      int32_t nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256));
      rString.ReleaseBuffer();

      return nResult;

   }

   bool graphics::get_text_metrics(::draw2d::text_metric * lpMetrics) const
   {

      set(m_spfont);

      sp(font) pfont = m_spfont;

      TEXTMETRIC tm;

      GetTextMetrics(pfont->m_hdcFont, &tm);

      lpMetrics->tmAscent = tm.tmAscent;
      lpMetrics->tmHeight = tm.tmHeight;
      lpMetrics->tmDescent = tm.tmDescent;
      lpMetrics->tmAveCharWidth = tm.tmAveCharWidth;

      //if (m_pgraphics == NULL)
      //   return false;

      //graphics * pgraphics = ((graphics *)this);

      //if(pgraphics->gl2d_font() == NULL)
      //   return false;

      //plusplus::Font * pfont = pgraphics->gl2d_font();

      //plusplus::FontFamily family;

      //pfont->GetFamily(&family);

      //INT iStyle = pfont->GetStyle();

      //double dHeight = family.GetEmHeight(iStyle);

      //double dSize = pfont->GetSize();

      //double dFontHeight = pfont->GetHeight((plusplus::REAL) pgraphics->get_dpiy());

      //lpMetrics->tmAscent              = (LONG) (dSize * family.GetCellAscent(iStyle) / dHeight);
      //lpMetrics->tmDescent             = (LONG) (dSize * family.GetCellDescent(iStyle) / dHeight);
      //lpMetrics->tmHeight              = (LONG)dFontHeight;

      //double dLineSpacing = MAX(dFontHeight, dSize * family.GetLineSpacing(iStyle) / dHeight);

      //lpMetrics->tmInternalLeading     = (LONG) (lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight);
      //lpMetrics->tmExternalLeading     = (LONG) (dLineSpacing - (lpMetrics->tmAscent + lpMetrics->tmDescent));

      //const plusplus::FontFamily * pfamilyMono = family.GenericMonospace();

      //::plusplus::Font font2(pfamilyMono, pfamilyMono->GetEmHeight(((graphics * )this)->gl2d_font()->GetStyle()));

      //wstring wstr(L"123AWZwmc123AWZwmcpQçg");
      //plusplus::RectF rect(0.f, 0.f, 1024.f * 1024.f, 1024.f * 1024.f);
      //plusplus::RectF rect2;
      //plusplus::PointF origin(0, 0);

      //m_pgraphics->MeasureString(wstr, (INT) wstr.get_length(), ((graphics * )this)->gl2d_font(), origin, &rect);


      ///*wstr = L"";
      //m_pgraphics->MeasureString(wstr.m_pwsz, -1, (plusplus::Font *) m_font->get_os_data(), origin, &rect2);*/

      //lpMetrics->tmAveCharWidth = (LONG) (rect.Width * get_current_font()->m_dFontWidth / (double) wstr.get_length());


      return TRUE;
   }


   bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics) const
   {

      ASSERT(get_handle1() != NULL);

      //return ::GetTextMetricsW(get_handle1(), lpMetrics) != FALSE;

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   int32_t graphics::GetTextCharacterExtra() const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetTextCharacterExtra(get_handle2());
   }
   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;
   }
   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;
   }
   uint32_t graphics::GetFontLanguageInfo() const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetFontLanguageInfo(get_handle1());
   }


   uint32_t graphics::GetCharacterPlacement(const char * lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {

      ASSERT(get_handle1() != NULL);

      return ::GetCharacterPlacement(get_handle1(), lpString, (int) nCount, (int) nMaxExtent, lpResults, dwFlags);

   }


   uint32_t graphics::GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) const
   {

      ASSERT(get_handle1() != NULL);

      return ::GetCharacterPlacement(get_handle1(), (const char *)str, (int32_t) str.get_length(), (int) nMaxExtent, lpResults, dwFlags);

   }


   size graphics::GetAspectRatioFilter() const
   {
      ASSERT(get_handle2() != NULL);
      SIZE size;
      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
      return size;
   }
   bool graphics::ScrollDC(int32_t dx, int32_t dy,
                           const RECT &  lpRectScroll,const RECT &  rectClip,
                           ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate)
   {
      ASSERT(get_handle1() != NULL);
      return ::ScrollDC(get_handle1(),dx,dy,&rectClip,
                        &rectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != FALSE;
   }

   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {
      ASSERT(get_handle1() != NULL);
      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);
   }

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const RECT &  rectBounds, UINT flags)
   {
      ASSERT(get_handle1() != NULL);
      return ::SetBoundsRect(get_handle1(), &rectBounds, flags);
   }
   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {
      ASSERT(get_handle2() != NULL);
      return ::GetBoundsRect(get_handle2(), lpRectBounds, flags);
   }
   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      ASSERT(get_handle2() != NULL);
      return ::ResetDC(get_handle2(), lpDevMode) != NULL;
   }
   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetOutlineTextMetricsW(get_handle2(), cbData, lpotm);
   }
   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != FALSE;
   }
   uint32_t graphics::GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData,
                                  uint32_t cbData) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);
   }
   int32_t graphics::GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);
   }
   uint32_t graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
                                      uint32_t cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   {  ASSERT(get_handle2() != NULL);
      return ::GetGlyphOutline(get_handle2(), nChar, nFormat,
                               lpgm, cbBuffer, lpBuffer, lpmat2);
   }

   // ::user::document handling functions
   int32_t graphics::StartDoc(LPDOCINFO lpDocInfo)
   {

      ASSERT(m_hdc != NULL);

      return ::StartDoc(m_hdc, lpDocInfo);

   }

   int32_t graphics::StartPage()
   {

      //ASSERT(m_hdc != NULL);

      //::StartPage(m_hdc);

      //m_pgraphics = new plusplus::Graphics(m_hdc);

      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      return 1;

   }


   int32_t graphics::EndPage()
   {

     /* ASSERT(m_hdc != NULL);

      delete m_pgraphics;

*/
      return ::EndPage(m_hdc);

   }


   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {

      ASSERT(m_hdc != NULL);

      return ::SetAbortProc(m_hdc, (ABORTPROC)lpfn);

   }


   int32_t graphics::AbortDoc()
   {

      ASSERT(m_hdc != NULL);

      return ::AbortDoc(m_hdc);

   }


   int32_t graphics::EndDoc()
   {

      ASSERT(m_hdc != NULL);

      return ::EndDoc(m_hdc);

   }

   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                          int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask, uint32_t dwRop)
   {  ASSERT(get_handle1() != NULL);
      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc),
                       xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != FALSE;
   }

   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
                         int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
   {

      /*try
      {

         if(pgraphicsSrc == NULL)
            return FALSE;

         if(pgraphicsSrc->get_current_bitmap() == NULL)
            return false;

         if(pgraphicsSrc->get_current_bitmap()->get_os_data() == NULL)
            return false;

         plusplus::Point p[3];

         p[0].X = lpPoint[0].x;
         p[0].Y = lpPoint[0].y;
         p[1].X = lpPoint[1].x;
         p[1].Y = lpPoint[1].y;
         p[2].X = lpPoint[2].x;
         p[2].Y = lpPoint[2].y;

         return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), p, 3) == plusplus::Status::Ok;

      }
      catch(...)
      {
         return FALSE;
      }
*/
      return true;

   }



   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {  ASSERT(get_handle1() != NULL);
      return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;
   }
   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {  ASSERT(get_handle1() != NULL);
      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;
   }

   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {  ASSERT(get_handle1() != NULL);
      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != FALSE;
   }


   bool graphics::ArcTo(const RECT &  rectParam,POINT ptStart,POINT ptEnd)
   {  ASSERT(get_handle1() != NULL);
      return ArcTo(rectParam.left, rectParam.top, rectParam.right,
                   rectParam.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
   }
   int32_t graphics::GetArcDirection() const
   {  ASSERT(get_handle2() != NULL);
      return ::GetArcDirection(get_handle2());
   }


   bool graphics::PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount)
   {

      ASSERT(get_handle1() != NULL);

      return ::PolyPolyline(get_handle1(), lpPoints, (LPDWORD) lpPolyPoints, (DWORD) nCount) != FALSE;

   }


   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {  ASSERT(get_handle2() != NULL);
      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
   }

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


   bool graphics::PolyBezier(const POINT* lpPoints, count nCount)
   {

      ASSERT(get_handle1() != NULL);

      return ::PolyBezier(get_handle1(), lpPoints, (DWORD) nCount) != FALSE;

   }


   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {

      ASSERT(get_handle1() != NULL);

      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);

   }

   int32_t graphics::Escape(__in int32_t nEscape, __in int32_t nInputSize, __in_bcount(nInputSize) const char * lpszInputData,  __in int32_t nOutputSize, __out_bcount(nOutputSize) char * lpszOutputData)
   {
      ASSERT(get_handle1() != NULL);
      return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
   }

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
                                   LPABCFLOAT lpABCF) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;
   }
   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const
   {
      ASSERT(get_handle2() != NULL);
      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;
   }

   bool graphics::AbortPath()
   {
      //if(m_ppath != NULL)
      //{
      //   delete m_ppath;
      //   m_ppath = NULL;
      //}
      return true;
   }

   bool graphics::BeginPath()
   {

 /*     if(m_ppath != NULL)
         delete m_ppath;

      m_ppath = new plusplus::GraphicsPath;
*/
//      return m_ppath != NULL;

      return true;

   }

   bool graphics::CloseFigure()
   {
      //ASSERT(m_ppath != NULL);
      //return m_ppath->CloseFigure() == plusplus::Status::Ok;
      return true;

   }

   bool graphics::EndPath()
   {

      //if(m_ppath == NULL)
      //   return FALSE;

      //m_ppathPaint   = m_ppath;
      //m_ppath        = NULL;

      return true;

   }

   bool graphics::FillPath()
   {

      //return m_pgraphics->FillPath(gl2d_brush(), m_ppath) == plusplus::Status::Ok;
      return true;

   }

   bool graphics::FlattenPath()
   {
//      return m_ppath->Flatten() == plusplus::Status::Ok;
      return true;
   }

   float graphics::GetMiterLimit() const
   {
      ASSERT(get_handle1() != NULL);
      float fMiterLimit;
      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      return fMiterLimit;
   }


   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, count nCount) const
   {

      ASSERT(get_handle1() != NULL);

      return ::GetPath(get_handle1(), lpPoints, lpTypes, (int) nCount);

   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {
      ASSERT(get_handle1() != NULL);
      return ::SetMiterLimit(get_handle1(), fMiterLimit, NULL) != FALSE;
   }

   bool graphics::StrokeAndFillPath()
   {

      //bool bOk1 = m_pgraphics->FillPath(gl2d_brush(), m_ppathPaint) == plusplus::Status::Ok;

      //bool bOk2 = m_pgraphics->DrawPath(gl2d_pen(), m_ppathPaint) == plusplus::Status::Ok;

      //return bOk1 && bOk2;

      return true;

   }

   bool graphics::StrokePath()
   {

//      return m_pgraphics->DrawPath(gl2d_pen(), m_ppathPaint) == plusplus::Status::Ok;

      return true;

   }

   bool graphics::WidenPath()
   {

      //return m_ppath->Widen(gl2d_pen()) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      //m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeAntiAlias);
      //m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //return m_pgraphics->DrawPath(gl2d_pen(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;
      return true;


   }

   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      //return m_pgraphics->DrawPath((::plusplus::Pen *) ppen->get_os_data(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      return true;

   }

   bool graphics::fill_path(::draw2d::path * ppath)
   {

      //return m_pgraphics->FillPath(gl2d_brush(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      return true;

   }

   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      //return m_pgraphics->FillPath((::plusplus::Brush *) pbrush->get_os_data(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      return true;

   }

   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {
      ASSERT(get_handle1() != NULL);
      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;
   }


   /*bool CALLBACK metaCallback(
      EmfPlusRecordType recordType,
      uint32_t flags,
      uint32_t dataSize,
      const uchar* pStr,
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
      // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
      graphics.EnumerateMetafile(
      pMeta,
      Rect(0, 0, 300, 50),
      metaCallback,
      pMeta);
      // Draw pMeta as an image.
      graphics.DrawImage(pMeta, Point(0, 150));
      delete pMeta;;
   }*/
   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const RECT &  rectBounds)
   {

      //plusplus::RectF rect((plusplus::REAL) rectBounds.left,(plusplus::REAL) rectBounds.top,(plusplus::REAL) width(rectBounds),(plusplus::REAL) height(rectBounds));

      //plusplus::Metafile* pMeta = new plusplus::Metafile(hEnhMF, false);

      ////m_pgraphcis->EnumerateMetafile(pMeta, rect, metaCallback, PMETAHEADER);

      //bool bOk = m_pgraphics->DrawImage(pMeta, rect) == plusplus::Status::Ok;

      //delete pMeta;

      //return bOk ? TRUE : FALSE;
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

      return true;

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

   bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dRate)
   {

//      if (m_pgraphics == NULL)
//         return false;
//
//      if(m_pdibAlphaBlend != NULL)
//      {
//
//
//         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
//
//
//         ::draw2d::dib * pdibWork = NULL;
//         ::draw2d::dib * pdibWork2 = NULL;
////         ::draw2d::dib * pdibWork3 = NULL;
//         ::draw2d::dib * pdibWork4 = NULL;
//
//
//         class point ptSrc(xSrc, ySrc);
//         class point ptDest(xDest, yDest);
//         class size size(nDestWidth, nDestHeight);
//
//
//
//         ::draw2d::dib_sp spdib;
//         if(pdibWork == NULL)
//         {
//            spdib.alloc(allocer());
//            pdibWork = spdib;
//         }
//         if(pdibWork == NULL)
//            return false;
//         if(!pdibWork->create(size))
//            return false;
//         if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
//            return false;
//
//
//
//
//         ::draw2d::dib_sp spdib2;
//         if(pdibWork2 == NULL)
//         {
//            spdib2.alloc(allocer());
//            pdibWork2 = spdib2;
//         }
//
//
//         ::draw2d::dib_sp spdib4;
//         if(pdibWork4 == NULL)
//         {
//            spdib4.alloc(allocer());
//            pdibWork4 = spdib4;
//         }
//         if(pdibWork4 == NULL)
//            return false;
//         if(!pdibWork4->create(size))
//            return false;
//
//
//         pdibWork4->Fill(255, 0, 0, 0);
//
//         pdibWork4->from(point(MAX(0, m_ptAlphaBlend.x - xDest), MAX(0, m_ptAlphaBlend.y - yDest)),
//                         m_pdibAlphaBlend->get_graphics(), point(MAX(0, xDest - m_ptAlphaBlend.x), MAX(0, yDest - m_ptAlphaBlend.y)), size);
//
//         pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);
//
//
//         keep < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
//
//
//         return BitBlt(ptDest.x, ptDest.y, size.cx, size.cy, pdibWork->get_graphics(), ptSrc.x, ptSrc.y, SRCCOPY);
//
//
//      }
//
//
//      float fA = (float) dRate;
//
//      plusplus::ColorMatrix matrix = {
//         1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//         0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//         0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//         0.0f, 0.0f, 0.0f, fA  , 0.0f,
//         0.0f, 0.0f, 0.0f, 0.0f, 1.0f
//      };
//
//      plusplus::ImageAttributes attributes;
//
//      attributes.SetColorMatrix(&matrix, plusplus::ColorMatrixFlagsDefault, plusplus::ColorAdjustTypeBitmap);
//
//      plusplus::RectF dstRect((plusplus::REAL) xDest, (plusplus::REAL) yDest, (plusplus::REAL) nDestWidth, (plusplus::REAL) nDestHeight);
//
//      if(pgraphicsSrc == NULL)
//         return false;
//
//      if(pgraphicsSrc->get_current_bitmap() == NULL)
//         return false;
//
//      plusplus::Bitmap * pbitmap = NULL;
//
//      try
//      {
//
//         pbitmap = (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();
//
//      }
//      catch(...)
//      {
//      }
//
//      if(pbitmap != NULL)
//      {
//
//         m_pgraphics->DrawImage(pbitmap,dstRect,(plusplus::REAL) xSrc,(plusplus::REAL) ySrc,(plusplus::REAL) nSrcWidth,(plusplus::REAL) nSrcHeight,plusplus::UnitPixel,&attributes);
//
//      }
//
      return true;

   }


   /*bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, BLENDFUNCTION blend)
   {

      ::exception::throw_not_implemented(get_app());
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
            spdib.alloc(allocer());
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
            spdib2.alloc(allocer());
            pdibWork2 = spdib2;
         }


         ::draw2d::dib_sp spdib4;
         if(pdibWork4 == NULL)
         {
            spdib4.alloc(allocer());
            pdibWork4 = spdib4;
         }
         if(pdibWork4 == NULL)
            return false;
         if(!pdibWork4->create(size))
            return false;


         pdibWork4->Fill(255, 0, 0, 0);

         pdibWork4->from(point(MAX(0, m_ptAlphaBlend.x - xDest), MAX(0, m_ptAlphaBlend.y - yDest)),
            m_pdibAlphaBlend->get_graphics(), point(MAX(0, xDest - m_ptAlphaBlend.x), MAX(0, yDest - m_ptAlphaBlend.y)), size);

         pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);


         keep < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);


         return System.visual().imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), ptSrc);


      }

      return ::AlphaBlend(get_handle1(), xDest, yDest,
         nDestWidth, nDestHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != FALSE;
   }*/


   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
   {

      ASSERT(get_handle1() != NULL);

      //return ::TransparentBlt(get_handle1(), xDest, yDest,  nDestWidth, nDestHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,  nSrcHeight, crTransparent) != FALSE;

      return true;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, uint32_t dwMode)
   {

      ASSERT(get_handle1() != NULL);

      //return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != FALSE;

      return true;

   }

   // This is core API library.
   //
   //
   //
   //
   //
   //
   //
   //

   // Always Inline. Functions only in Win98/Win2K or later

   inline COLORREF graphics::GetDCBrushColor() const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetDCBrushColor(get_handle1());
   }
   inline COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {
      ASSERT(get_handle1() != NULL);
      return ::SetDCBrushColor(get_handle1(), crColor);
   }

   inline COLORREF graphics::GetDCPenColor() const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetDCPenColor(get_handle1());
   }
   inline COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {
      ASSERT(get_handle1() != NULL);
      return ::SetDCPenColor(get_handle1(), crColor);
   }

   inline bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != FALSE;
   }
   inline bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
   {
      ASSERT(get_handle1() != NULL);
      return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != FALSE;
   }

   inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
   {
      ENSURE(lpSize != NULL);
      ASSERT(get_handle1() != NULL);
      return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize) != FALSE;
   }
   inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, LPSIZE lpSize) const
   {
      ENSURE(lpSize != NULL);
      ASSERT(get_handle1() != NULL);
      return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, lpSize) != FALSE;
   }







#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      int32_t nMapMode;
      if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained map mode, map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         DPtoLP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // map against logical inch for non-constrained mapping modes
         int32_t cxPerInch, cyPerInch;
         if (this != NULL)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != NULL);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);
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
   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      int32_t nMapMode;
      if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained map mode, map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         LPtoDP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // map against logical inch for non-constrained mapping modes
         int32_t cxPerInch, cyPerInch;
         if (this != NULL)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != NULL);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);
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

   ::draw2d::brush* graphics::GetHalftoneBrush(::aura::application * papp)
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

      //      return ::draw2d_opengl::brush::from_handle(papp, gen_HalftoneBrush);*/
      return NULL;
   }

   void graphics::DrawDragRect(const RECT &  lpRect, SIZE size, const RECT &  lpRectLast, SIZE sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      ::exception::throw_not_implemented(get_app());

      /*

            ASSERT(__is_valid_address(lpRect, sizeof(RECT), FALSE));
            ASSERT(lpRectLast == NULL ||
               __is_valid_address(lpRectLast, sizeof(RECT), FALSE));

            // first, determine the update region and select it
            ::draw2d::region rgnNew;
            ::draw2d::region rgnOutside, rgnInside;
            rgnOutside.create_rect(lpRect);
            rect rect = *lpRect;
            rect.inflate(-size.cx, -size.cy);
            rect.intersect(rect, lpRect);
            rgnInside.create_rect(rect);
            rgnNew.create_rect(0, 0, 0, 0);
            rgnNew.combine(&rgnOutside, &rgnInside, RGN_XOR);

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
               rgnLast.create_rect(0, 0, 0, 0);
               rgnOutside.SetRectRgn(lpRectLast);
               rect = *lpRectLast;
               rect.inflate(-sizeLast.cx, -sizeLast.cy);
               rect.intersect(rect, lpRectLast);
               rgnInside.SetRectRgn(rect);
               rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

               // only diff them if brushes are the same
               if (pBrush->get_os_data() == pBrushLast->get_os_data())
               {
                  rgnUpdate.create_rect(0, 0, 0, 0);
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

   /*void graphics::FillSolidRect(const RECT &  lpRect, COLORREF clr)
   {
      ::SetBkColor(get_handle1(), clr);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
   }*/

   void graphics::FillSolidRect(const RECT64 * lpRect, COLORREF clr)
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

   void graphics::Draw3dRect(const RECT &  rectParam,
                             COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      Draw3dRect(rectParam.left, rectParam.top, rectParam.right - rectParam.left,
                 rectParam.bottom - rectParam.top, clrTopLeft, clrBottomRight);
   }

   void graphics::Draw3dRect(int32_t x, int32_t y, int32_t cx, int32_t cy,
                             COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
      FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
      FillSolidRect(x + cx - 1, y, 1, cy, clrBottomRight);
      FillSolidRect(x, y + cy - 1, cx, 1, clrBottomRight);
   }





   //::draw2d::graphics * ::draw2d_opengl::graphics::from_handle(HDC hDC)
   //{
   //hdc_map* pMap = afxMapHDC(TRUE); //create map if not exist
   //ASSERT(pMap != NULL);
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pgraphics == NULL || (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1() == hDC);
   //  return pgraphics;
   // return NULL;
   //}

   bool graphics::Attach(HDC hdc)
   {

      //if(hdc == NULL)
      //   return FALSE;

      //if(m_hdc == hdc)
      //{

      //   if(m_pgraphics != NULL)
      //      return TRUE;

      //}

      //if(hdc != NULL)
      //{

      //   m_pgraphics = new ::plusplus::Graphics((HDC) hdc);

      //   m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      //   set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      //   m_hdc = (HDC) hdc;

      //}

      //return m_pgraphics != NULL;

      return true;

      /*ASSERT(get_handle1() == NULL);      // only attach once, detach on destroy
      ASSERT(get_handle2() == NULL);    // only attach to an is_empty DC

      if (hDC == NULL)
      {
         return FALSE;
      }
      // remember early to avoid leak
      set_handle1(hDC);
      hdc_map* pMap = afxMapHDC(TRUE); // create map if not exist
      ASSERT(pMap != NULL);
      pMap->set_permanent(get_handle1(), this);

      SetAttribDC(get_handle1());     // Default to same as output
      return TRUE;*/
   }

   HDC graphics::Detach()
   {

      //if(m_hdc == NULL)
      //   return NULL;

      //if(m_pgraphics == NULL)
      //   return NULL;

      //try
      //{

      //   delete m_pgraphics;

      //}
      //catch(...)
      //{

      //   TRACE("graphics::Detach : Failed to delete plusplus::Graphics");

      //}

      //m_pgraphics = NULL;

      //HDC hdc = m_hdc;
      //m_hdc = NULL;

      //return hdc;

      return NULL;

   }


   bool graphics::AttachPrinter(HDC hdc)
   {

      //if (hdc == NULL)
      //   return FALSE;

      //if (m_hdc == hdc)
      //{

      //   return TRUE;

      //}

      //if (hdc != NULL)
      //{

      //   m_hdc = (HDC)hdc;

      //}

      //return m_hdc != NULL;

      return true;

   }


   HDC graphics::DetachPrinter()
   {

      //if (m_hdc == NULL)
      //   return NULL;

      //HDC hdc = m_hdc;

      //m_hdc = NULL;

      //return hdc;

      return NULL;

   }


   bool graphics::DeleteDC()
   {

      //HDC hdc = Detach();

      //if(hdc != NULL)
      //{

      //   bool bDeleted = ::DeleteDC(hdc) != FALSE;

      //   if(!bDeleted)
      //   {

      //      TRACE("graphics::DeleteDC : Failed to delete GDI device context");

      //   }

      //}

      //if(m_pgraphics != NULL)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      TRACE("graphics::DeleteDC : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = NULL;

      //}

      //if(m_ppath != NULL)
      //{

      //   try
      //   {

      //      delete m_ppath;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppath = NULL;

      //}

      //if(m_ppathPaint != NULL)
      //{

      //   try
      //   {

      //      delete m_ppathPaint;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppathPaint = NULL;

      //}

      return true;

   }



   void graphics::SetAttribDC(HDC hDC)  // set the Attribute DC
   {
//      set_handle2(hDC);
   }

   void graphics::SetOutputDC(HDC hDC)  // set the Output DC
   {
#ifdef DEBUG
      /*      hdc_map* pMap = afxMapHDC();
            if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
            {
               TRACE(::aura::trace::category_AppMsg, 0, "Cannot set Output hDC on Attached graphics.\n");
               ASSERT(FALSE);
            }*/
#endif
      //    set_handle1(hDC);
   }

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
               TRACE(::aura::trace::category_AppMsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
               ASSERT(FALSE);
            }*/
#endif
      //set_handle1(NULL);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int32_t graphics::StartDoc(const char * lpszDocName)
   {
      DOCINFO di;
      memset(&di, 0, sizeof(DOCINFO));
      di.cbSize = sizeof(DOCINFO);
      di.lpszDocName = lpszDocName;
      return StartDoc(&di);
   }

   int32_t graphics::SaveDC()
   {
//      return m_pgraphics->Save();
      return 0;
   }

   bool graphics::RestoreDC(int32_t nSavedDC)
   {

      //return m_pgraphics->Restore(nSavedDC) != FALSE;
      return true;

   }

//   ::draw2d::object* graphics::SelectGdiObject(::aura::application * papp, HDC hDC, HGDIOBJ h)
   // {
//      return ::draw2d_opengl::object::from_handle(papp, ::SelectObject(hDC, h));
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
            return ::draw2d_opengl::object::from_handle(get_app(), hOldObj);*/

      return NULL;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* pPen)
   {
      /*HGDIOBJ hOldObj = NULL;
      if(pPen == NULL)
         return NULL;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), pPen->get_os_data());
      if(get_handle2() != NULL)
         hOldObj = ::SelectObject(get_handle2(), pPen->get_os_data());
      return dynamic_cast < pen * > (::draw2d_opengl::object::from_handle(get_app(), hOldObj));*/
      m_sppen = pPen;
      return m_sppen;
   }

   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pBrush)
   {
      /*      HGDIOBJ hOldObj = NULL;
            if(pBrush == NULL)
               return NULL;
            if(get_handle1() != NULL && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), pBrush->get_os_data());
            if(get_handle2() != NULL)
               hOldObj = ::SelectObject(get_handle2(), pBrush->get_os_data());
            return dynamic_cast < ::draw2d::brush * > (::draw2d_opengl::object::from_handle(get_app(), hOldObj));*/
      m_spbrush = pBrush;
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
            return dynamic_cast < ::draw2d::font * > (::draw2d_opengl::object::from_handle(get_app(), hOldObj));*/

      /*ASSERT(pFont != NULL);

      if(pFont == NULL)
         return NULL;

      m_fontxyz = *pFont;
      return &m_fontxyz;*/

      if(!select_font(pfont))
         return NULL;

      return m_spfont;

   }

   int32_t graphics::SelectObject(::draw2d::region* pRgn)
   {
      int32_t nRetVal = GDI_ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle1(), (HGDIOBJ) pRgn->get_os_data());
      if(get_handle2() != NULL)
         nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle2(), (HGDIOBJ) pRgn->get_os_data());
      return nRetVal;
   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return NULL;
//      return dynamic_cast < ::draw2d::palette * > (::draw2d_opengl::object::from_handle(get_app(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }

   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
      return nRetVal;
   }

   int32_t graphics::SetROP2(int32_t nDrawMode)
   {
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetROP2(get_handle1(), nDrawMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetROP2(get_handle2(), nDrawMode);
      return nRetVal;
   }

   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {

      //if(m_pgraphics == NULL)
      //{

      //   return -1;

      //}

      //if(nStretchMode == 0)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeNearestNeighbor);
      //}
      //else if(nStretchMode == HALFTONE)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);
      //}
      //else
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeLowQuality);
      //}
      //return 1;

      return true;

      /*int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
      return nRetVal;*/
   }


   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {
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
   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      //plusplus::REAL r[6];

      //r[0] = pXform->eDx;
      //r[1] = pXform->eDy;

      //r[2] = pXform->eM11;
      //r[3] = pXform->eM12;
      //r[4] = pXform->eM21;
      //r[5] = pXform->eM22;

      //plusplus::Matrix m;

      //m.SetElements(r[2],r[3],r[4],r[5],r[0],r[1]);

      //m_pgraphics->SetTransform(&m);

      return true;
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,uint32_t iMode)
   {
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
   }

   int32_t graphics::SetMapMode(int32_t nMapMode)
   {
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetMapMode(get_handle1(), nMapMode);
      if(get_handle2() != NULL)
         nRetVal = ::SetMapMode(get_handle2(), nMapMode);
      return nRetVal;
   }

   point graphics::GetViewportOrg() const
   {
      //POINT point;
      //::GetViewportOrgEx(get_handle2(), &point);

      //if (m_pgraphics == NULL)
      //{

      //   return null_point();

      //}

      //plusplus::Point origin(0, 0);

      //m_pgraphics->TransformPoints(
      //   plusplus::CoordinateSpacePage,
      //   plusplus::CoordinateSpaceWorld,
      //   &origin,
      //   1);

      //return point((int64_t) origin.X, (int64_t) origin.Y);

      return m_ptTranslate;

   }



   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {

      if (m_spbitmap.is_null())
         return null_point();

      ::size s = m_spbitmap.cast < bitmap>()->m_sizeOut;

      if (s.area() <= 0)
         return null_point();

      //if (m_pgraphics == NULL)
      //{

      //   return null_point();

      //}

      //m_pm->Reset();

      //m_pm->Translate((plusplus::REAL) x, (plusplus::REAL) y);

      //m_pgraphics->SetTransform(m_pm);

      //return point(x, y);
      glLoadIdentity();
      
      
      glScalef(2.0 / (float)s.cx, 2.0 / (float)s.cy, 0);
      
      glTranslatef(-s.cx/2.0+x, -s.cy/2.0+y, 0);

      
      m_ptTranslate.x = x;
      m_ptTranslate.y = y;


      return null_point();

   }


   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {

      point point = GetViewportOrg();

      if (nWidth == 0 && nHeight == 0)
      {

         return point;

      }

      point.offset(nWidth, nHeight);

      return SetViewportOrg(point.x, point.y);

   }

   size graphics::SetViewportExt(int32_t x, int32_t y)
   {
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetViewportExtEx(get_handle1(), x, y, &size);
      if(get_handle2() != NULL)
         ::SetViewportExtEx(get_handle2(), x, y, &size);
      return size;
   }

   size graphics::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::ScaleViewportExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
      if(get_handle2() != NULL)
         ::ScaleViewportExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
      return size;
   }

   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {
      point point(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetWindowOrgEx(get_handle1(), x, y, &point);
      if(get_handle2() != NULL)
         ::SetWindowOrgEx(get_handle2(), x, y, &point);
      return point;
   }

   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {
      point point(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
      if(get_handle2() != NULL)
         ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
      return point;
   }

   size graphics::SetWindowExt(int32_t x, int32_t y)
   {
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetWindowExtEx(get_handle1(), x, y, &size);
      if(get_handle2() != NULL)
         ::SetWindowExtEx(get_handle2(), x, y, &size);
      return size;
   }

   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      size size(0, 0);
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
      if(get_handle2() != NULL)
         ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
      return size;
   }

   int32_t graphics::GetClipBox(LPRECT lpRect) const
   {

      //plusplus::Rect r;

      //m_pgraphics->GetClipBounds(&r);

      //lpRect->left = r.X;
      //lpRect->top = r.Y;
      //lpRect->right = r.X + r.Width;
      //lpRect->bottom = r.Y + r.Height;

      return 1;

   }

   int32_t graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      //if(pregion == NULL)
      //{
      //   m_pgraphics->ResetClip();
      //}
      //else
      //{
      //   m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data());
      //}

      return 0;

      /*      int32_t nRetVal = ERROR;
            if(get_handle1() != NULL && get_handle1() != get_handle2())
               nRetVal = ::SelectClipRgn(get_handle1(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
            if(get_handle2() != NULL)
               nRetVal = ::SelectClipRgn(get_handle2(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
            return nRetVal;*/
   }

   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
      if(get_handle2() != NULL)
         nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
      return nRetVal;
   }

   int32_t graphics::ExcludeClipRect(const RECT &  rectParam)
   {
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::ExcludeClipRect(get_handle1(), rectParam.left, rectParam.top,
                                     rectParam.right, rectParam.bottom);
      if(get_handle2() != NULL)
         nRetVal = ::ExcludeClipRect(get_handle2(), rectParam.left, rectParam.top,
                                     rectParam.right, rectParam.bottom);
      return nRetVal;
   }

   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
      if(get_handle2() != NULL)
         nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
      return nRetVal;
   }

   int32_t graphics::IntersectClipRect(const RECT &  rectBounds)
   {
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::IntersectClipRect(get_handle1(),rectBounds.left,rectBounds.top,rectBounds.right,rectBounds.bottom);
      if(get_handle2() != NULL)
         nRetVal = ::IntersectClipRect(get_handle2(),rectBounds.left,rectBounds.top,rectBounds.right,rectBounds.bottom);
      return nRetVal;
   }

   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
      if(get_handle2() != NULL)
         nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
      return nRetVal;
   }

   int32_t graphics::OffsetClipRgn(SIZE size)
   {
      int32_t nRetVal = ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
      if(get_handle2() != NULL)
         nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
      return nRetVal;
   }


   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UINT nRetVal = GDI_ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         ::SetTextAlign(get_handle1(), nFlags);
      if(get_handle2() != NULL)
         nRetVal = ::SetTextAlign(get_handle2(), nFlags);
      return nRetVal;
   }

   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {
      int32_t nRetVal = 0;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
      if(get_handle2() != NULL)
         nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
      return nRetVal;
   }

   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {
      ASSERT(get_handle1() != NULL);
      int32_t nRetVal = 0x8000000;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
      if(get_handle2() != NULL)
         nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
      return nRetVal;
   }

   uint32_t graphics::SetMapperFlags(uint32_t dwFlag)
   {
      ASSERT(get_handle1() != NULL);
      uint32_t dwRetVal = GDI_ERROR;
      if(get_handle1() != NULL && get_handle1() != get_handle2())
         dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
      if(get_handle2() != NULL)
         dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
      return dwRetVal;
   }

   typedef uint32_t (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   typedef uint32_t (CALLBACK* __GDISETLAYOUTPROC)(HDC, uint32_t);

   uint32_t graphics::GetLayout() const
   {
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != NULL);
      /*      uint32_t dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != NULL)
               dwGetLayout = (*pfn)(get_handle1());
            else
            {
               dwGetLayout = GDI_ERROR;
               SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
            }*/
      //return dwGetLayout;
      return 0;
   }

   uint32_t graphics::SetLayout(uint32_t dwSetLayout)
   {
      /*HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != NULL);
      uint32_t dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != NULL)
         dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;*/

      return 0;

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
      ASSERT(get_handle1() != NULL);
      bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
   }

   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {
      ASSERT(get_handle1() != NULL);
      int32_t nResult = 0;
      if (get_handle1() != get_handle2())
         nResult = ::SetArcDirection(get_handle1(), nArcDirection);
      if (get_handle2() != NULL)
         nResult = ::SetArcDirection(get_handle2(), nArcDirection);
      return nResult;
   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, count nCount)
   {

      ASSERT(get_handle1() != NULL);

      bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, (int) nCount) != FALSE;

      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
   }

   bool graphics::PolylineTo(const POINT* lpPoints, count nCount)
   {
      ASSERT(get_handle1() != NULL);
      bool bResult = ::PolylineTo(get_handle1(), lpPoints, (DWORD) nCount) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
   }

   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {
      ASSERT(get_handle1() != NULL);
      bool bResult = FALSE;
      if (get_handle1() != get_handle2())
         bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != FALSE;
      if (get_handle2() != NULL)
         bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
      return bResult;
   }

   bool graphics::PolyBezierTo(const POINT* lpPoints, count nCount)
   {
      ASSERT(get_handle1() != NULL);
      bool bResult = ::PolyBezierTo(get_handle1(), lpPoints, (DWORD) nCount) != FALSE;
      if (get_handle1() != get_handle2())
      {
         point pt;
         VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
         VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
      }
      return bResult;
   }

   bool graphics::SelectClipPath(int32_t nMode)
   {
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
            TRACE(::aura::trace::category_AppMsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
            bResult = FALSE;
         }
         ::DeleteObject(hRgn);
      }
      return bResult;
   }


   int32_t graphics::SelectClipRgn(::draw2d::region* pregion,int32_t nMode)
   {

      //if(pregion == NULL)
      //{

      //   m_pgraphics->ResetClip();

      //}
      //else
      //{

      //   if(nMode == RGN_AND)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(), plusplus::CombineModeIntersect);

      //   }
      //   else if(nMode == RGN_OR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeUnion);

      //   }
      //   else if(nMode == RGN_XOR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeXor);

      //   }
      //   else if(nMode == RGN_COPY)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeReplace);

      //   }
      //   else if(nMode == RGN_DIFF)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeExclude);

      //   }

      //}

      return 0;

   }


   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback

   int32_t CALLBACK __enum_meta_file_procedure(HDC hDC,
         HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int32_t nHandles, LPARAM lParam)
   {
      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;
      ASSERT_VALID(pgraphics);

      switch (pMetaRec->rdFunction)
      {
      // these records have effects different for each graphics derived class
      case META_SETMAPMODE:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetMapMode((int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWEXT:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetWindowExt(
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWORG:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetWindowOrg(
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTEXT:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetViewportExt(
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTORG:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetViewportOrg(
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SCALEWINDOWEXT:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->ScaleWindowExt(
            (int32_t)(int16_t)pMetaRec->rdParm[3], (int32_t)(int16_t)pMetaRec->rdParm[2],
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SCALEVIEWPORTEXT:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->ScaleViewportExt(
            (int32_t)(int16_t)pMetaRec->rdParm[3], (int32_t)(int16_t)pMetaRec->rdParm[2],
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_OFFSETVIEWPORTORG:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->OffsetViewportOrg(
            (int32_t)(int16_t)pMetaRec->rdParm[1], (int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SAVEDC:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SaveDC();
         break;
      case META_RESTOREDC:
         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->RestoreDC((int32_t)(int16_t)pMetaRec->rdParm[0]);
         break;
      case META_SETBKCOLOR:
         {
            ::draw2d::brush_sp brush((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->allocer(), *(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
            (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(brush);
         }
         break;
      case META_SETTEXTCOLOR:
         {
            ::draw2d::brush_sp brush((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->allocer(), *(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
            (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(brush);
         }
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
               HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1(), hStockFont);
               HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1(), hObject);
               if (hObjOld == hStockFont)
               {
                  // got the stock object back, so must be selecting a font
                  throw not_implemented(get_thread_app());
//                  (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(::draw2d_opengl::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
                  break;  // don't play the default record
               }
               else
               {
                  // didn't get the stock object back, so restore everything
                  ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1(), hFontOld);
                  ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1(), hObjOld);
               }
               // and fall through to PlayMetaFileRecord...
            }
            else if (nObjType == OBJ_FONT)
            {
               // play back as graphics::SelectObject(::draw2d::font*)
//               (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(::draw2d_opengl::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
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
   }

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      if (::GetDeviceCaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
      {
         // playing metafile in metafile, just use core windows API
         return ::PlayMetaFile(get_handle1(), hMF) != FALSE;
      }

      // for special playback, lParam == pgraphics
      return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      size sizeWinExt = GetWindowExt();
      size sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
   }

   void graphics::DPtoLP(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      size sizeWinExt = GetWindowExt();
      size sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
   }


   int32_t graphics::draw_text(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat)
   {

      return draw_text(string(lpszString,nCount),lpRect,nFormat);

   }


   int32_t graphics::draw_text(const string & str,const RECT & rectParam,UINT nFormat)
   {

      ::rectd rect;

      ::copy(rect,&rectParam);

      return draw_text(str,rect,nFormat);

   }


   int32_t graphics::draw_text(const char * lpszString, strsize nCount, const RECTD & rectParam, UINT nFormat)
   {

      return draw_text(string(lpszString,nCount),rectParam,nFormat);

   }


   int32_t graphics::draw_text(const string & str, const RECTD & rectParam, UINT nFormat)
   {

      //try
      //{

      //   if(m_pgraphics == NULL)
      //      return FALSE;

      //   /*

      //   switch(m_etextrendering)
      //   {
      //   case ::draw2d::text_rendering_anti_alias:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);
      //      break;
      //   case ::draw2d::text_rendering_anti_alias_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAliasGridFit);
      //      break;
      //   case ::draw2d::text_rendering_single_bit_per_pixel:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintSingleBitPerPixel);
      //      break;
      //   case ::draw2d::text_rendering_clear_type_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintClearTypeGridFit);
      //      break;
      //   }

      //   */
      //   m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //   m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);


      //}
      //catch(...)
      //{
      //}



      //plusplus::StringFormat format(plusplus::StringFormat::GenericTypographic());


      //format.SetFormatFlags(format.GetFormatFlags()
      //                      | plusplus::StringFormatFlagsNoClip | plusplus::StringFormatFlagsMeasureTrailingSpaces
      //                      | plusplus::StringFormatFlagsLineLimit);

      //if(nFormat & DT_LEFT)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & DT_RIGHT)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & DT_CENTER)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}

      //if(nFormat & DT_BOTTOM)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & DT_TOP)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & DT_VCENTER)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}

      //plusplus::REAL stops[] = {16,32,48, 64,80,96,112,128};

      //format.SetTabStops(0,8,stops);

      ////m_dFontSize             = fontSrc.m_dFontSize;

      //plusplus::Matrix m;
      //m_pgraphics->GetTransform(&m);
      //plusplus::Matrix * pmNew = m.Clone();
      //try
      //{


      //   pmNew->Translate((plusplus::REAL) rectParam.left,(plusplus::REAL) rectParam.top);
      //   pmNew->Scale((plusplus::REAL) m_spfont->m_dFontWidth,(plusplus::REAL) 1.0,plusplus::MatrixOrderAppend);

      //   plusplus::RectF rectf(0,0,(plusplus::REAL) ((rectParam.right - rectParam.left) * m_spfont->m_dFontWidth),(plusplus::REAL) (rectParam.bottom - rectParam.top));

      //   m_pgraphics->SetTransform(pmNew);

      //   m_pgraphics->DrawString(::str::international::utf8_to_unicode(str),-1,gl2d_font(),rectf,&format,gl2d_brush());
      //}
      //catch(...)
      //{
      //}

      //m_pgraphics->SetTransform(&m);

      //delete pmNew;

      return 1;

   }


   int32_t graphics::draw_text_ex(LPTSTR lpszString,strsize nCount,const RECT & rectParam,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {

      if(get_handle1() == NULL)
         return -1;

      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = ::str::international::utf8_to_unicode(string(lpszString, nCount));
      return ::DrawTextExW(get_handle1(),const_cast<wchar_t *>((const wchar_t *)wstr),(int32_t)wcslen(wstr),(LPRECT) &rectParam,nFormat,lpDTParams);

   }


   int32_t graphics::draw_text_ex(const string & str,const RECT & rectParam,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      ASSERT(get_handle1() != NULL);
      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = ::str::international::utf8_to_unicode(str);
      return ::DrawTextExW(get_handle1(),const_cast<wchar_t *>((const wchar_t *)wstr),(int32_t)wcslen(wstr),(LPRECT) &rectParam,nFormat,lpDTParams);
   }


   int32_t graphics::draw_text_ex(LPTSTR lpszString,strsize nCount,const RECTD & rectParam,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {

      return ::draw2d::graphics::draw_text_ex(lpszString,nCount,rectParam,nFormat,lpDTParams);

   }


   int32_t graphics::draw_text_ex(const string & str,const RECTD & rectParam,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {

      return ::draw2d::graphics::draw_text_ex(str,rectParam,nFormat,lpDTParams);

   }


   size graphics::GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) const
   {

      if(lpszString == NULL || *lpszString == '\0')
         return size(0, 0);

      if(nCount < 0)
         nCount = strlen(lpszString);

      if(iIndex > nCount)
         return size(0, 0);

      if(iIndex < 0)
         return size(0, 0);


      wstring wstr = ::str::international::utf8_to_unicode(lpszString, nCount);

      strsize iRange = 0;
      strsize i = 0;
      strsize iLen;
      const char * psz = lpszString;
      while(i < iIndex)
      {
         iLen = ::str::get_utf8_char(psz).length();
         iRange++;
         i += iLen;
         psz = ::str::utf8_inc(psz);
         if(psz == NULL)
            break;
         if(*psz == '\0')
            break;
      }

      set(m_spfont);

      sp(font) pfont = m_spfont;

      SIZE s = { 0 };

      ::GetTextExtentPointW(pfont->m_hdcFont, wstr, wstr.get_length(), &s);

      return s;

   }


   size graphics::GetTextExtent(const char * lpszString, strsize nCount) const
   {

      class sized size;

      if (!GetTextExtent(size, lpszString, nCount, 0))
         return class size(0, 0);

      return ::size(size.cx, size.cy);

   }


   size graphics::GetTextExtent(const string & str) const
   {

      class sized size;

      if(!GetTextExtent(size, str, (int32_t) str.get_length(), (int32_t) str.get_length()))
         return class size(0, 0);

      return class size((long) size.cx, (long) size.cy);

   }

   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount) const
   {
      ASSERT(get_handle1() != NULL);
      SIZE size;
      string str(lpszString, nCount);
      wstring wstr = ::str::international::utf8_to_unicode(str);
      VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int32_t)wstr.get_length(), &size));
      return size;

   }


   size graphics::GetOutputTextExtent(const string & str) const
   {

      ASSERT(get_handle1() != NULL);

      SIZE size;

      wstring wstr = ::str::international::utf8_to_unicode(str);

      ::GetTextExtentPoint32W(get_handle1(), wstr, (int32_t)wstr.get_length(), &size);

      return size;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex) const
   {

      //ASSERT(get_handle1() != NULL);

      set(m_spfont);

      sp(font) pfont = m_spfont;

      SIZE s;

      wstring wstr = ::str::international::utf8_to_unicode(string(&lpszString[iIndex], nCount));

      if (!::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (int32_t)wstr.get_length(), &s))
         return false;

      size.cx = s.cx;

      size.cy = s.cy;

      return true;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount) const
   {

      //ASSERT(get_handle1() != NULL);

      set(m_spfont);

      sp(font) pfont = m_spfont;

      SIZE s;

      wstring wstr = ::str::international::utf8_to_unicode(lpszString, nCount);

      if (!::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (int32_t)wstr.get_length(), &s))
         return false;

      size.cx = s.cx;

      size.cy = s.cy;
   
      return true;

   }


   bool graphics::GetTextExtent(sized & size, const string & str) const
   {

      //ASSERT(get_handle1() != NULL);

      set(m_spfont);

      sp(font) pfont = m_spfont;

      SIZE s;

      wstring wstr = ::str::international::utf8_to_unicode(str);

      if (::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (int32_t)wstr.get_length(), &s))
         return false;

      size.cx = s.cx;

      size.cy = s.cy;

      return true;

   }

} // namespace draw2d_opengl






namespace draw2d_opengl
{

   void graphics::FillSolidRect(const RECT &  rectParam,COLORREF clr)
   {

      FillSolidRect(rectParam.left,rectParam.top,width(rectParam),height(rectParam),clr);

   }

   void graphics::FillSolidRect(int32_t l, int32_t t, int32_t cx, int32_t cy, COLORREF clr)
   {

      try
      {

         if (m_spbitmap.is_null())
            return;

         ::size s = m_spbitmap.cast < bitmap>()->m_sizeOut;

         if (s.area() <= 0)
            return;

         float r = l + cx;
         float b = t + cy;

         m_spbitmap.cast < bitmap>()->flash();

         glBegin(GL_QUADS);
         // Front Face
         glColor4f(argb_get_r_value(clr) / 255.f, argb_get_g_value(clr) / 255.f, argb_get_b_value(clr) / 255.f, argb_get_a_value(clr) / 255.f);						// Set Top Point Of Triangle To Red
         glVertex2f(l, t);
         glVertex2f(r, t);
         glVertex2f(r, b);
         glVertex2f(l, b);
         glEnd();


         //if(m_pgraphics == NULL)
         //   return;

         //if(m_esmoothmode != ::draw2d::smooth_mode_none)
         //{

         //   set_smooth_mode(::draw2d::smooth_mode_none);

         //}
         //else
         //{
         //   //TRACE("optimized smoothing mode");
         //}

         //::draw2d::brush_sp brushCurrent;

         //if(m_spbrush.is_null() || m_spbrush->m_etype != ::draw2d::brush::type_solid || m_spbrush->m_cr != clr)
         //{

         //   brushCurrent = m_spbrush;

         //   ::draw2d::brush_sp brush(allocer(),clr);

         //   SelectObject(brush);

         //}
         //else
         //{

         //   //TRACE("optimized brush");

         //}

         //m_pgraphics->FillRectangle(gl2d_brush(), x, y, cx, cy);


      }
      catch(...)
      {
         return;
      }

   }


   bool graphics::TextOut(int32_t x, int32_t y, const char * lpszString, strsize nCount)
   {

      return TextOut((double)x, (double)y, lpszString, nCount);

   }


   bool graphics::TextOut(double x, double y, const char * lpszString, strsize nCount)
   {

      if(m_spfont.is_null())
         return false;

      if (::draw2d::graphics::TextOut(x, y, lpszString, nCount))
         return true;

      set(m_spfont);

      sp(font) pfont = m_spfont;

      int length = 0;

      for (unsigned int loop = 0; loop < (strlen(lpszString)); loop++)	// Loop To Find Text Length
      {

         length += pfont->m_gmf[lpszString[loop]].gmfCellIncX;			// Increase Length By Each Characters Width

      }

      glTranslatef(x, y, 0.0f);					// Center Our Text On The Screen

      glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
      glListBase(pfont->m_baseFont);									// Sets The Base Character to 0
      glCallLists(strlen(lpszString), GL_UNSIGNED_BYTE, lpszString);	// Draws The Display List Text
      glPopAttrib();										// Pops The Display List Bits      }

      glTranslatef(-x, -y, 0.0f);					// Center Our Text On The Screen

      return true;

   }

   
   void graphics::set(::draw2d::pen * ppen)
   {

      glLineWidth(ppen->m_dWidth);
      glColor4f(
         argb_get_r_value(ppen->m_cr) / 255.f, 
         argb_get_g_value(ppen->m_cr) / 255.f, 
         argb_get_b_value(ppen->m_cr) / 255.f, 
         argb_get_a_value(ppen->m_cr) / 255.f);	

   }

   void graphics::set(::draw2d::brush * pbrush)
   {

      glColor4f(
         argb_get_r_value(pbrush->m_cr) / 255.f, 
         argb_get_g_value(pbrush->m_cr) / 255.f,
         argb_get_b_value(pbrush->m_cr) / 255.f,
         argb_get_a_value(pbrush->m_cr) / 255.f);

   }


   void graphics::set(const ::draw2d::font * pfont) const 
   {

      pfont->get_os_data();

   }


   bool graphics::LineTo(double x, double y)
   {

      set(m_sppen);

      glBegin(GL_LINE);
      glVertex2f(m_x, m_y);
      glVertex2f(x, y);
      glEnd();
      m_x = x;
      m_y = y;

      return TRUE;

   }

   bool graphics::LineTo(int x,int y)
   {

      set(m_sppen);

      glBegin(GL_LINE);
      glVertex2f(m_x, m_y);
      glVertex2f(x, y);
      glEnd();
      m_x = x;
      m_y = y;

      return TRUE;

   }

   bool graphics::DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen)
   {

      set(m_sppen);

      glBegin(GL_LINE);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
      glEnd();
      m_x = x2;
      m_y = y2;

      return TRUE;

   }


   bool graphics::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, ::draw2d::pen * ppen)
   {

      set(m_sppen);

      glBegin(GL_LINE);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);
      glEnd();
      m_x = x2;
      m_y = y2;

      return TRUE;

   }

   void graphics::set_smooth_mode(::draw2d::e_smooth_mode esmoothmode)
   {

      //if(m_esmoothmode == esmoothmode)
      //   return;

      //::draw2d::graphics::set_smooth_mode(esmoothmode);

      //try
      //{

      //   if(m_pgraphics == NULL)
      //      return;

      //   if(m_esmoothmode == ::draw2d::smooth_mode_none)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeNone);

      //   }
      //   else if(m_esmoothmode == ::draw2d::smooth_mode_antialias)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighSpeed);

      //   }
      //   else if(m_esmoothmode == ::draw2d::smooth_mode_high)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighQuality);

      //   }

      //}
      //catch(...)
      //{
         return;
      //}

   }


   void graphics::set_alpha_mode(::draw2d::e_alpha_mode ealphamode)
   {

      try
      {

         //if(m_pgraphics == NULL)
         //   return;

         ::draw2d::graphics::set_alpha_mode(ealphamode);
         if(m_ealphamode == ::draw2d::alpha_mode_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         }
         else if(m_ealphamode == ::draw2d::alpha_mode_set)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
         }

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

//      return (void *) m_pgraphics;

      return NULL;

   }

   void * graphics::get_os_data_ex(int i) const
   {

      if(i == 1)
      {
//         return m_pgraphics->GetHDC();
      }
      else
      {
         return ::draw2d::graphics::get_os_data_ex(i);
      }

      return NULL;
   }

   void graphics::release_os_data_ex(int i,void * p)
   {
      if(i == 1)
      {
//         m_pgraphics->ReleaseHDC((HDC)p);
      }
      else
      {
         ::draw2d::graphics::release_os_data_ex(i, p);
      }
   }



   HDC graphics::get_handle() const
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
   }


   bool graphics::attach(void * pdata)
   {

      //if(m_pgraphics != NULL)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      TRACE("graphics::attach : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = NULL;

      //}

      //m_pgraphics = (plusplus::Graphics *) pdata;

      return false;

   }


   void * graphics::detach()
   {

      //plusplus::Graphics * pgraphics = m_pgraphics;

      //m_pgraphics = NULL;

      //m_hdc = NULL;

      //return pgraphics;

      return NULL;

   }

   //plusplus::Font * graphics::gl2d_font()
   //{
   //   if(m_spfont.is_null())
   //   {
   //      m_spfont.alloc(allocer());
   //      if(m_spfont.is_set())
   //      {
   //         m_spfont->m_powner = this;
   //      }
   //   }
   //   if(m_spfont.is_null())
   //   {
   //      return NULL;
   //   }
   //   return (plusplus::Font *) m_spfont->get_os_data();
   //}

   //plusplus::Brush * graphics::gl2d_brush()
   //{
   //   if(m_spbrush.is_null())
   //   {
   //      m_spbrush.alloc(allocer());
   //      if(m_spbrush.is_set())
   //      {
   //         m_spbrush->m_powner = this;
   //      }
   //   }
   //   if(m_spbrush.is_null())
   //   {
   //      return NULL;
   //   }
   //   return (plusplus::Brush *) m_spbrush->get_os_data();
   //}

   //plusplus::Pen * graphics::gl2d_pen()
   //{

   //   synch_lock sl(m_pmutex);

   //   if(m_sppen.is_null())
   //   {
   //      m_sppen.alloc(allocer());
   //      if(m_sppen.is_set())
   //      {
   //         m_sppen->m_powner = this;
   //      }
   //   }
   //   if(m_sppen.is_null())
   //   {
   //      return NULL;
   //   }
   //   return (plusplus::Pen *) m_sppen->get_os_data();
   //}

   //plusplus::FillMode graphics::gl2d_get_fill_mode()
   //{
   //   return plusplus::FillModeWinding;
   //}

   bool graphics::blur(bool bExpand,double dRadius,const RECT & rectParam)
   {

   //   // Commented Out for Running in cosan machine running Windows 2008

   //   //if(m_spbitmap.is_null() || m_spbitmap->get_os_data() == NULL)
   //   //   return false;

   //   //plusplus::BlurParams myBlurParams;

   //   //myBlurParams.expandEdge    = bExpand ? 1 : 0;
   //   //myBlurParams.radius        = (float) dRadius;

   //   //plusplus::Blur myBlur;
   //   //myBlur.SetParameters(&myBlurParams);

   //   //

   //   //plusplus::Matrix m;
   //   //m_pgraphics->GetTransform(&m);

   //   //plusplus::PointF points[2];

   //   //points[0].X    = (plusplus::REAL) rectParam.left;
   //   //points[0].Y    = (plusplus::REAL) rectParam.top;
   //   //points[1].X    = (plusplus::REAL) rectParam.right;
   //   //points[1].Y    = (plusplus::REAL) rectParam.bottom;

   //   //m.TransformPoints(points, 2);

   //   ////plusplus::RectF rectf(points[0].X, points[0].Y, points[1].X - points[0].X, points[1].Y - points[0].Y);

   //   //RECT rect;

   //   //rect.left      = (LONG) points[0].X;
   //   //rect.top       = (LONG) points[0].Y;
   //   //rect.right     = (LONG) points[1].X;
   //   //rect.bottom    = (LONG) points[1].Y;

   //   //plusplus::Bitmap * pbitmap = ((plusplus::Bitmap *) m_spbitmap->get_os_data());

   //   //pbitmap->ApplyEffect(&myBlur, &rect);

   //   return true;

      return true;
   }


   double graphics::get_dpix() const
   {

      //if (m_pgraphics == NULL)
      //   return 96.0;

      //return m_pgraphics->GetDpiX();

      return 96.0;

   }


   double graphics::get_dpiy() const
   {

      //if (m_pgraphics == NULL)
      //   return 96.0;

      //return m_pgraphics->GetDpiY();

      return 96.0;

   }


   bool graphics::flush()
   {

      synch_lock sl(m_pmutex);

//      m_pgraphics->Flush();

      return true;

   }


   bool graphics::sync_flush()
   {

      synch_lock sl(m_pmutex);

      //m_pgraphics->Flush(plusplus::FlushIntentionSync);

      return true;

   }

   HDC graphics::get_hdc()
   {

      if(m_hdc != NULL)
         return m_hdc;

      ////if(m_pgraphics == NULL)
      //   return NULL;

      //return m_pgraphics->GetHDC();

      return NULL;

   }

   void graphics::release_hdc(HDC hdc)
   {

      if(m_hdc != NULL)
         return;

      //m_pgraphics->ReleaseHDC(hdc);

   }


   void graphics::enum_fonts(stringa & straPath, stringa & stra)
   {

      synch_lock sl(m_pmutex);

      draw2d_opengl_enum_fonts fonts(stra);

      HDC hdc = ::CreateCompatibleDC(NULL);

      ::EnumFontFamilies(hdc,(LPCTSTR)NULL,(FONTENUMPROC)draw2d_opengl_EnumFamCallBack,(LPARAM)&fonts);

      ::DeleteDC(hdc);

      straPath = stra;

   }


   bool graphics::prefer_mapped_dib_on_mix()
   {

      return true;

   }


} // namespace draw2d_opengl





BOOL CALLBACK draw2d_opengl_EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,DWORD FontType,LPVOID p)
{

   draw2d_opengl_enum_fonts * pfonts = (draw2d_opengl_enum_fonts *) p;

   if(FontType & RASTER_FONTTYPE)
   {

   }
   else if(FontType & TRUETYPE_FONTTYPE)
   {

      pfonts->m_stra.add_unique(lplf->lfFaceName);

   }
   else
   {

   }

   return TRUE;

}

