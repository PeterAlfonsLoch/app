#include "framework.h"

namespace ca
{


   brush::brush()
   {

      m_crColor   = 0;
      m_etype     = type_solid;
      m_bUpdated  = false;


   }

   void brush::construct(COLORREF crColor)
   {

      m_crColor   = crColor;
      m_etype     = type_solid;
      m_bUpdated  = false;

   }

   void brush::construct(int nIndex, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   void brush::construct(::ca::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception();
   }

#ifdef WINDOWS
   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
   {
      UNREFERENCED_PARAMETER(hPackedDIB);
      UNREFERENCED_PARAMETER(nUsage);
      throw interface_only_exception();
   }
#endif

   void brush::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }

   bool brush::CreateStockObject(int nIndex)
   {

      if(nIndex == NULL_BRUSH)
      {
         m_crColor   = ARGB(0, 0, 0, 0);
         m_etype     = type_solid;
         m_bUpdated  = false;
      }
      else
      {
         m_crColor   = ARGB(0, 0, 0, 0);
         m_etype     = type_solid;
         m_bUpdated  = false;
      }

      return TRUE;

   }

   bool brush::CreateSolidBrush(COLORREF crColor)
   {

      m_crColor   = crColor;
      m_etype     = type_solid;
      m_bUpdated  = false;

      return TRUE;

   }
   bool brush::CreateHatchBrush(int nIndex, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }
   bool brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
   {
      UNREFERENCED_PARAMETER(lpLogBrush);
      throw interface_only_exception();
   }
   bool brush::CreatePatternBrush(::ca::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception();
   }
   bool brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
   {
      UNREFERENCED_PARAMETER(lpPackedDIB);
      UNREFERENCED_PARAMETER(nUsage);
      throw interface_only_exception();
   }
   bool brush::CreateSysColorBrush(int nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception();
   }
   int brush::GetLogBrush(LOGBRUSH* pLogBrush)
   {
      UNREFERENCED_PARAMETER(pLogBrush);
      throw interface_only_exception();
   }

   bool brush::CreateLinearGradientBrush(point p1, point p2, COLORREF cr1, COLORREF cr2)
   {

      m_etype           = type_linear_gradient_point_color;
      m_pt1             = p1;
      m_pt2             = p2;
      m_cr1             = cr1;
      m_cr2             = cr2;
      m_bUpdated        = false;

      return true;

   }


   brush & brush::operator = (const brush & brushSrc)
   {

      m_etype           = brushSrc.m_etype;
      m_crColor         = brushSrc.m_crColor;
      m_pt1             = brushSrc.m_pt1;
      m_pt2             = brushSrc.m_pt2;
      m_cr1             = brushSrc.m_cr1;
      m_cr2             = brushSrc.m_cr2;
      m_bUpdated        = false;

      return *this;

   }

} // namespace ca
