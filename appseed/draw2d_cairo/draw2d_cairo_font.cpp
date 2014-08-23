#include "framework.h"


namespace draw2d_cairo
{


   font::font(sp(::aura::application) papp) :
   element(papp)
   {

      m_pfont = NULL;
      m_ft = NULL;
      m_pface = NULL;

   }


   font::~font()
   {

      destroy();

   }


   bool font::destroy()
   {
synch_lock ml(&cairo_mutex());
      if(m_pfont != NULL)
      {

         cairo_scaled_font_destroy(m_pfont);

         m_pfont = NULL;

      }

      if(m_pface != NULL)
      {

         cairo_font_face_destroy(m_pface);

         m_pface = NULL;

      }

      if(m_ft != NULL)
      {

         //FT_Done_Face (m_ft);

         m_ft = NULL;

      }

      return true;

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::font::dump(dumpcontext);

   }


   void * font::get_os_data() const
   {

      throw interface_only_exception(get_app());

      return NULL;

   }


} // namespace draw2d_cairo





