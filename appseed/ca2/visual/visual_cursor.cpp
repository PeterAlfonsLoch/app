#include "StdAfx.h"

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
      ::xml::node node(get_app());
      if(node.load(strNode))
      {
         m_ptHotspot.x = node.attr("x");
         m_ptHotspot.y = node.attr("y");
      }
      return true;
   }

   bool cursor::load_from_matter(const char * pszMatter)
   {
      return load_from_file(Application.dir().matter(pszMatter));
   }

   bool cursor::to(::ca::graphics * pgraphics, int x, int y)
   {
      if(&System.imaging() == NULL)
         return false;
      return System.imaging().color_blend(
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