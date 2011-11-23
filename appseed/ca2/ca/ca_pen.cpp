#include "StdAfx.h"


namespace ca
{

   void pen::construct(int nPenStyle, double nWidth, COLORREF crColor)
   {

      m_nPenStyle             = nPenStyle;
      m_dPenWidth             = nWidth;
      m_crPenColor            = crColor;
      m_bUpdated              = false;

   }

   void pen::construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const DWORD* lpStyle)
   {

      m_nPenStyle             = nPenStyle;
      m_dPenWidth             = nWidth;
      m_crPenColor            = 0;
      m_bUpdated              = false;

   }

#ifdef _DEBUG
   void pen::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }
#endif

   void AfxThrowResourceException()
   {
      throw resource_exception();
   }

   void AfxThrowUserException()
   {
      throw user_exception();
   }


   BOOL pen::CreatePen(int nPenStyle, double dWidth, COLORREF crColor)
   {

      m_nPenStyle             = nPenStyle;
      m_dPenWidth             = dWidth;
      m_crPenColor            = 0;
      m_bUpdated              = false;

      return TRUE;

   }

   BOOL pen::CreatePen(int nPenStyle, double dWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const DWORD* lpStyle)
   {

      m_nPenStyle             = nPenStyle;
      m_dPenWidth             = dWidth;
      m_crPenColor            = 0;
      m_bUpdated              = false;

      return TRUE;

   }


} // namespace ca

