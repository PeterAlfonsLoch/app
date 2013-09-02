#include "framework.h"


namespace draw2d
{


   pen_sp::pen_sp(::draw2d::graphics * pgraphics, double dWidth, COLORREF crColor) :
      smart_pointer < pen > (pgraphics->allocer())
   {
      m_p->create_solid(pgraphics, dWidth, crColor);
   }


   pen::pen()
   {

      m_eendcap               = end_cap_flat;
      m_elinejoin             = line_join_miter;
      m_cr                    = ARGB(127, 0, 0, 0);
      m_etype                 = type_solid;
      m_dWidth                = 1.0;

   }

   pen::~pen()
   {
   }


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

   bool pen::create_solid(::draw2d::graphics * pdc, double dWidth, COLORREF crColor)
   {

      UNREFERENCED_PARAMETER(pdc);

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
      m_eendcap         = penSrc.m_eendcap;
      m_elinejoin       = penSrc.m_elinejoin;
      m_bUpdated        = false;

      return *this;

   }

   pen::e_end_cap pen::get_end_cap()
   {

      return m_eendcap;

   }

   bool pen::set_end_cap(e_end_cap eendcap)
   {

      m_eendcap = eendcap;

      return true;

   }


   pen::e_line_join pen::get_line_join()
   {

      return m_elinejoin;

   }

   bool pen::set_line_join(e_line_join elinejoin)
   {

      m_elinejoin = elinejoin;

      return true;

   }


} // namespace draw2d



