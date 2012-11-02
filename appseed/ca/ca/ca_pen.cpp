#include "framework.h"


namespace ca
{

   void pen::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception(get_app());
   }

   bool pen::create_null()
   {

      m_etype                 = type_null;
      m_dWidth                = 0.0;
      m_cr                    = ARGB(0, 0, 0, 0);
      m_bUpdated              = false;

      return true;

   }

   bool pen::create_solid(double dWidth, COLORREF crColor)
   {

      m_etype                 = type_solid;
      m_dWidth                = dWidth;
      m_cr                    = crColor;
      m_bUpdated              = false;

      return true;

   }


   pen & pen::operator = (const pen & penSrc)
   {

      m_etype           = penSrc.m_etype;
      m_dWidth          = penSrc.m_dWidth;
      m_cr              = penSrc.m_cr;
      m_bUpdated        = false;

      return *this;

   }


} // namespace ca

