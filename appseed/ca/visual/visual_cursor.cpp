#include "framework.h"

namespace visual
{

   cursor::cursor(::ca::application * papp) :
      ca(papp),
      m_dib(papp),
      m_dibWork(papp)
   {
   }

   bool cursor::load_from_file(const char * psz)
   {
      string str(psz);
      if(!gen::str::ends_eat_ci(str, ".png"))
         return false;
      if(!m_dib.load_from_file(psz))
         return false;
      str += ".xml";
      string strNode = Application.file().as_string(str);
      ::xml::document doc(get_app());
      if(doc.load(strNode))
      {
         m_ptHotspot.x = doc.get_root()->attr("x");
         m_ptHotspot.y = doc.get_root()->attr("y");
      }
      return true;
   }

   bool cursor::load_from_matter(const char * pszMatter)
   {
      return load_from_file(Application.dir().matter(pszMatter));
   }

   bool cursor::to(::ca::graphics * pgraphics, int32_t x, int32_t y)
   {
      if(&Application.m_visual.imaging() == NULL)
         return false;

      pgraphics->set_alpha_mode(::ca::alpha_mode_blend);

      return Application.visual().imaging().color_blend(
         pgraphics,
         point(x - m_ptHotspot.x, y - m_ptHotspot.y),
         m_dib->size(),
         m_dib->get_graphics(), 
         null_point(),
         m_dibWork,
         m_dibWork2); 
   }

   bool cursor::to(::ca::graphics * pgraphics, point pt)
   {
      return to(pgraphics, pt.x, pt.y); 
   }

} // namespace visual