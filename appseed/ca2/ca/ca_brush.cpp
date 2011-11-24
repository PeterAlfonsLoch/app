#include "StdAfx.h"

namespace ca
{

   void brush::construct(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
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

   BOOL brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
   {
      UNREFERENCED_PARAMETER(hPackedDIB);
      UNREFERENCED_PARAMETER(nUsage);
      throw interface_only_exception();
   }

#ifdef _DEBUG
   void brush::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }
#endif

   BOOL brush::CreateSolidBrush(COLORREF crColor)
   {
      
      m_crColor = crColor;
      m_bUpdated = false;
      
      return TRUE;

   }
   BOOL brush::CreateHatchBrush(int nIndex, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }
   BOOL brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
   {
      UNREFERENCED_PARAMETER(lpLogBrush);
      throw interface_only_exception();
   }
   BOOL brush::CreatePatternBrush(::ca::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      throw interface_only_exception();
   }
   BOOL brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
   {
      UNREFERENCED_PARAMETER(lpPackedDIB);
      UNREFERENCED_PARAMETER(nUsage);
      throw interface_only_exception();
   }
   BOOL brush::CreateSysColorBrush(int nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      throw interface_only_exception();
   }
   int brush::GetLogBrush(LOGBRUSH* pLogBrush)
   {
      UNREFERENCED_PARAMETER(pLogBrush);
      throw interface_only_exception();
   }


   brush & brush::operator = (const brush & brushSrc)
   {

      m_crColor         = brushSrc.m_crColor;
      m_bUpdated        = false;

      return *this;

   }

} // namespace ca