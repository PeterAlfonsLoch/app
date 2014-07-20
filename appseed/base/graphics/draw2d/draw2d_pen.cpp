#include "framework.h"


namespace draw2d
{


   pen_sp::pen_sp(::draw2d::graphics * pgraphics, double dWidth, COLORREF crColor) :
      smart_pointer < pen > (pgraphics->allocer())
   {
      m_p->create_solid(dWidth, crColor);
   }


   pen::pen()
   {

      m_elinecapBeg           = line_cap_flat;
      m_elinecapEnd           = line_cap_flat;
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

   bool pen::create_solid(double dWidth, COLORREF crColor)
   {

      if (m_etype == type_solid
         && dWidth >= (m_dWidth - 0.1)
         && dWidth <= (m_dWidth + 0.1)
         && m_cr == crColor)
         return true;

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
      m_elinecapBeg     = penSrc.m_elinecapBeg;
      m_elinecapEnd     = penSrc.m_elinecapEnd;
      m_elinejoin       = penSrc.m_elinejoin;
      m_bUpdated        = false;

      return *this;

   }

   pen::e_line_cap pen::get_beg_cap()
   {

      return m_elinecapBeg;

   }

   bool pen::set_beg_cap(e_line_cap elinecapBeg)
   {

      m_elinecapBeg = elinecapBeg;

      return true;

   }


   pen::e_line_cap pen::get_end_cap()
   {

      return m_elinecapEnd;

   }

   bool pen::set_end_cap(e_line_cap elinecapEnd)
   {

      m_elinecapEnd = elinecapEnd;

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



