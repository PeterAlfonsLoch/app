#include "framework.h"


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

   void pen::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }

   BOOL pen::CreatePen(int nPenStyle, double dWidth, COLORREF crColor)
   {

      m_nPenStyle             = nPenStyle;
      m_dPenWidth             = dWidth;
      m_crPenColor            = crColor;
      m_bUpdated              = false;

      return TRUE;

   }

   BOOL pen::CreatePen(int nPenStyle, double dWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const DWORD* lpStyle)
   {

      m_nPenStyle             = nPenStyle;
      m_dPenWidth             = dWidth;
      m_crPenColor            = pLogBrush->lbColor;
      m_bUpdated              = false;

      return TRUE;

   }


   pen & pen::operator = (const pen & penSrc)
   {

      m_nPenStyle       = penSrc.m_nPenStyle;
      m_dPenWidth       = penSrc.m_dPenWidth;
      m_crPenColor      = penSrc.m_crPenColor;
      m_bUpdated        = false;

      return *this;

   }


} // namespace ca

