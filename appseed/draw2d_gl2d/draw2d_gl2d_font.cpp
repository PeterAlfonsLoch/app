#include "framework.h"

#undef new

namespace draw2d_gl2d
{


   font::font(::aura::application * papp) :
      ::object(papp)
   {

      //m_pfont     = NULL;
      m_bUpdated  = false;

   }

   font::font(const font & font):
      ::object(font.get_app())
   {

      //m_pfont     = NULL;
      m_bUpdated  = false;

      ::draw2d::font::operator = (font);

   }


   font::~font()
   { 

 /*     if(m_pfont != NULL)
      {
         delete m_pfont;
         m_pfont = NULL;
      }
   */
   }

   void font::construct(const ::draw2d::font & fontParam)
      {
         //class font & font = const_cast < ::draw2d_gl2d::font & > (dynamic_cast < const ::draw2d_gl2d::font & > (fontParam));
         //if(font.m_pfont == NULL)
         //{
         //   if(m_pfont != NULL)
         //   {
         //      delete m_pfont;
         //      m_pfont = NULL;
         //   }
         //}
         //else
         //{
         //   m_pfont = font.m_pfont->Clone();
         //}
      }


      void font::dump(dump_context & dumpcontext) const
      {
         ::draw2d::object::dump(dumpcontext);

      }




   //void * font::get_os_data() const
   //{
   //   
   //   if(m_pfont == NULL || !m_bUpdated)
   //   {
   //      if(m_pfont != NULL)
   //      {
   //         try
   //         {
   //            delete ((font *) this)->m_pfont;
   //         }
   //         catch(...)
   //         {
   //         }
   //         ((font *) this)->m_pfont = NULL;
   //      }


   //      int32_t iStyle = 0;

   //      if(m_iFontWeight >= 600)
   //      {
   //         iStyle |= (int32_t) plusplus::FontStyleBold;
   //      }

   //      if(m_bItalic)
   //      {
   //         iStyle |= (int32_t) plusplus::FontStyleItalic;
   //      }

   //      if(m_bUnderline)
   //      {
   //         iStyle |= (int32_t) plusplus::FontStyleUnderline;
   //      }

   //      if(m_bStrikeout)
   //      {
   //         iStyle |= (int32_t) plusplus::FontStyleStrikeout;
   //      }

   //      plusplus::Unit unit;

   //      switch(m_eunitFontSize)
   //      {
   //      case ::draw2d::unit_pixel:
   //         unit = plusplus::UnitPixel;
   //         break;
   //      case ::draw2d::unit_point:
   //         unit = plusplus::UnitPoint;
   //         break;
   //      default:
   //         unit = plusplus::UnitPoint;
   //         break;
   //      };
   //      
   //      //retry_single_lock slplusplus(&System.s_mutexplusplus, millis(1), millis(1));

   //      ((font *) this)->m_pfont = new plusplus::Font(
   //            ::str::international::utf8_to_unicode(m_strFontFamilyName),
   //            (plusplus::REAL) m_dFontSize,
   //            iStyle,
   //            unit);

   //   }


   //   if(m_pfont != NULL)
   //   {
   //      ((font *) this)->m_bUpdated = true;
   //   }

   //   return (void *) (plusplus::Font *) m_pfont;

   //}

} // namespace draw2d_gl2d