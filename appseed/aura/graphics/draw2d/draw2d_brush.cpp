#include "framework.h"
#include "draw2d_fwd.h"
#include "draw2d_object.h"
#include "draw2d_brush.h"


namespace draw2d
{


   brush::brush()
   {

      m_cr        = ARGB(0, 0, 0, 0);

      m_etype     = type_solid;

      m_bUpdated  = false;


   }


   brush::~brush()
   {

   }


/*
   void brush::construct(COLORREF crColor)
   {

      m_crColor   = crColor;
      m_etype     = type_solid;
      m_bUpdated  = false;

   }

   void brush::construct(int32_t nIndex, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(crColor);
      ::exception::throw_interface_only(get_app());
   }
   void brush::construct(::draw2d::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      ::exception::throw_interface_only(get_app());
   }

*/


#ifdef WINDOWS
   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
   {
      UNREFERENCED_PARAMETER(hPackedDIB);
      UNREFERENCED_PARAMETER(nUsage);
      ::exception::throw_interface_only(get_app());
      return false;
   }
#endif

   void brush::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      ::exception::throw_interface_only(get_app());
   }

   bool brush::create_null()
   {

      m_cr        = ARGB(0, 0, 0, 0);

      m_etype     = type_null;

      m_bUpdated  = true;

      return true;

   }

   bool brush::create_solid(COLORREF crColor)
   {

      if(m_cr != crColor || m_etype != type_solid)
      {
       
         m_cr        = crColor;

         m_etype     = type_solid;

         m_bUpdated  = false;

      }

      return true;

   }

   bool brush::CreateHatchBrush(int32_t nIndex, COLORREF crColor)
   {

      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(crColor);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
   {
      UNREFERENCED_PARAMETER(lpLogBrush);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool brush::CreatePatternBrush(::draw2d::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      ::exception::throw_interface_only(get_app());
      return false;
   }
   bool brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
   {
      UNREFERENCED_PARAMETER(lpPackedDIB);
      UNREFERENCED_PARAMETER(nUsage);
      ::exception::throw_interface_only(get_app());
      return false;
   }
   bool brush::CreateSysColorBrush(int32_t nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      ::exception::throw_interface_only(get_app());
      return false;
   }
   int32_t brush::GetLogBrush(LOGBRUSH* pLogBrush)
   {
      UNREFERENCED_PARAMETER(pLogBrush);
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   bool brush::CreateLinearGradientBrush(point p1, point p2, COLORREF cr1, COLORREF cr2)
   {

      if (m_etype == type_linear_gradient_point_color
         && m_pt1 == p1
         && m_pt2 == p2
         && m_cr1 == cr1
         && m_cr2 == cr2)
         return true;

      m_etype           = type_linear_gradient_point_color;
      m_pt1             = p1;
      m_pt2             = p2;
      m_cr1             = cr1;
      m_cr2             = cr2;
      m_bUpdated        = false;

      return true;

   }

   bool brush::CreateRadialGradientBrush(point p,size s,COLORREF cr1,COLORREF cr2)
   {

      if(m_etype == type_radial_gradient_color
         && m_pt == p
         && m_size == s)
         return true;

      m_etype           = type_radial_gradient_color;
      m_pt              = p;
      m_size            = s;
      m_cr1             = cr1;
      m_cr2             = cr2;
      m_bUpdated        = false;

      return true;

   }

   brush & brush::operator = (const brush & brushSrc)
   {

      m_etype           = brushSrc.m_etype;
      m_cr              = brushSrc.m_cr;
      m_pt1             = brushSrc.m_pt1;
      m_pt2             = brushSrc.m_pt2;
      m_cr1             = brushSrc.m_cr1;
      m_cr2             = brushSrc.m_cr2;
      m_pt              = brushSrc.m_pt;
      m_size            = brushSrc.m_size;
      m_bUpdated        = false;

      return *this;

   }


} // namespace draw2d






