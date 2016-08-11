#include "framework.h"


namespace estamira
{


   tileset::tileset(::aura::application * papp) :
      ::object(papp),
      m_il(papp)
   {


   }


   tileset::~tileset()
   {

   }

   bool tileset::load_tilemap(string strMatter)
   {

      ::visual::dib_sp dib(allocer());

      if (!dib.load_from_matter(strMatter + ".png", false))
      {

         return false;

      }

      string str = Application.file().as_string("matter://" + strMatter + ".tilemap");

      str.trim();

      if (str.is_empty())
      {
         return false;
      }

      stringa stra;

      stra.add_lines(str);

      if (stra.get_size() <= 0)
      {

         return false;

      }

      bool bOk = false;

      if (stra[0] == "imagelist")
      {
         
         bOk = load_imagelist(dib, stra);

      }

#if _ESTAMIRA_DEBUG

      if (bOk)
      {

         ::visual::dib_sp dib(allocer());

         *dib= *m_il.m_spdib;

         dib.save_to_file(::dir::system() / "estamira\\imagelisttest\\"+strMatter+".png");

      }

#endif


      return bOk;

   }

   bool tileset::load_imagelist(::draw2d::dib * pdib, const stringa & stra)
   {
      
      if (stra.get_size() <= 2)
      {

         return false;

      }

      {

         size s;
         s.cx = atoi(stra[1]);
         s.cy = atoi(stra[2]);

         if (s.area() <= 0)
         {

            return false;

         }

         if (!m_il.create(s.cx, s.cy, 0, 16, 16))
         {

            return false;

         }

      }

      int iRowCount = pdib->m_size.cx / m_il.m_size.cx;
      int iColCount = pdib->m_size.cy / m_il.m_size.cy;

      if (iRowCount <= 0)
         return false;

      if (iColCount <= 0)
         return false;

      int iMaxImageTileCount = iRowCount * iColCount;

      index iLine = 3;

      int iIcon;

      for (; iLine < stra.get_size(); iLine++)
      {

         index iIndex = iLine - 3;

         string strLine = stra[iLine];

         if (iIndex >= iMaxImageTileCount)
            break;

         index i = iIndex % iRowCount;
         index j = iIndex / iRowCount;

         int x = i * m_il.m_size.cx;
         int y = j * m_il.m_size.cy;

         iIcon = m_il.add_dib(pdib, x, y);

         m_map.set_at(strLine, iIcon);

      }

      for (; iLine < stra.get_size(); iLine++)
      {

         index iIndex = iLine - 3;

         string strLine = stra[iLine];

         strLine.trim();

         if (strLine.is_empty())
            continue;

         stringa straSplit;

         straSplit.explode(":", strLine);

         if (straSplit.get_size() <= 1 || straSplit.get_size() >= 4)
         {
            continue;
         }

         if (straSplit.get_size() == 2)
         {
            m_map.set_at(straSplit[0], m_map[straSplit[1]]);
         }
         else // size == 3
         {
            ::draw2d::dib_sp  dib(allocer());
            if (!dib->create(m_il.m_size))
               continue;

            draw(dib->get_graphics(), straSplit[2], 0, 0);

            if (!dib->op("horz-swap"))
               continue;

            iIcon = m_il.add_dib(dib, 0, 0);
            m_map.set_at(straSplit[0], iIcon);
         }

      }
      
      return true;

   }

   bool tileset::draw(::draw2d::graphics * pgraphics, const char * psz, int x, int y)
   {

      int i = -1;

      if (!m_map.Lookup(psz, i))
         return false;

      if (!m_il.draw(pgraphics, i, point(x, y), 0))
      {

         return false;

      }

      return true;

   }

}