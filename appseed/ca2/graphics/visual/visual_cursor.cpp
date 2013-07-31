#include "framework.h"

namespace visual
{

   cursor::cursor(sp(::ca2::application) papp) :
      ca2(papp),
      m_dib(allocer()),
      m_dibWork(allocer())
   {
   }

   bool cursor::load_from_file(const char * psz)
   {
      string str(psz);
      if(!::ca2::str::ends_eat_ci(str, ".png"))
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

   bool cursor::to(::draw2d::graphics * pgraphics, int32_t x, int32_t y)
   {
      if(&System.visual().imaging() == NULL)
         return false;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return System.visual().imaging().color_blend(
         pgraphics,
         point(x - m_ptHotspot.x, y - m_ptHotspot.y),
         m_dib->size(),
         m_dib->get_graphics(), 
         null_point(),
         m_dibWork,
         m_dibWork2); 
   }

   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {
      return to(pgraphics, pt.x, pt.y); 
   }

} // namespace visual