#include "framework.h"


namespace ca
{

   graphics_path::graphics_path()
   {

      m_bUpdated     = false;
      m_bFill        = false;
      m_efillmode    = ::ca::fill_mode_winding;
      m_bHasPoint    = false;

   }

   graphics_path::~graphics_path()
   {

   }


   bool graphics_path::has_current_point()
   {

      return m_bHasPoint;

   }

   point graphics_path::last_point()
   {

      if(!m_bHasPoint)
         throw "there is no point";

      return m_pt;

   }



   bool graphics_path::add_arc(const RECT & rect, int32_t iStart, int32_t iAngle)
   {

      if(width(rect) <= 0 || height(rect) <= 0)
         return true;

      element e;

      e.m_etype               = element::type_arc;
      e.m_arc.m_xCenter       = ((double) rect.right + (double) rect.left) / 2.0;
      e.m_arc.m_yCenter       = ((double) rect.bottom + (double) rect.top) / 2.0;
      e.m_arc.m_dRadiusX      = (double) rect.right - e.m_arc.m_xCenter;
      e.m_arc.m_dRadiusY      = (double) rect.bottom - e.m_arc.m_yCenter;
      e.m_arc.m_dAngle1        = iStart * 3.1415 / 180.0;
      e.m_arc.m_dAngle2        = e.m_arc.m_dAngle1 + iAngle * 3.1415 / 180.0;

      m_elementa.add(e);

      m_bHasPoint = true;
      m_pt.x = (LONG) (e.m_arc.m_xCenter + e.m_arc.m_dRadiusX * cos(e.m_arc.m_dAngle2));
      m_pt.y = (LONG) (e.m_arc.m_yCenter + e.m_arc.m_dRadiusY * sin(e.m_arc.m_dAngle2));

      m_bUpdated = false;

      return true;

   }

   bool graphics_path::add_move(int32_t x, int32_t y)
   {

      element e;

      e.m_etype               = element::type_move;
      e.m_move.m_x            = x;
      e.m_move.m_y            = y;

      m_elementa.add(e);

      m_bHasPoint = true;
      m_pt.x = x;
      m_pt.y = y;

      m_bUpdated = false;


      return true;

   }

   bool graphics_path::add_line(int32_t x, int32_t y)
   {

      element e;

      e.m_etype               = element::type_line;
      e.m_line.m_x            = x;
      e.m_line.m_y            = y;

      m_elementa.add(e);

      m_bHasPoint = true;
      m_pt.x = x;
      m_pt.y = y;

      m_bUpdated = false;

      return true;

   }

   bool graphics_path::add_line(int32_t x, int32_t y, int32_t x2, int32_t y2)
   {

      bool bOk1 = add_line(x, y);
      
      bool bOk2 = add_line(x2, y2);

      return bOk1 && bOk2;

   }


   bool graphics_path::begin_figure(bool bFill, ::ca::e_fill_mode efillmode)
   {

      m_bFill = bFill;

      m_efillmode = efillmode;

      m_bHasPoint = false;

      m_bUpdated = false;

      return true;

   }

   bool graphics_path::end_figure(bool bClose)
   {


      element e;

      e.m_etype               = element::type_end;
      
      e.m_end.m_bClose        = bClose;

      m_elementa.add(e);

      m_bUpdated = false;

      return true;

   }







   bool graphics_path::add_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
      rect rect;

      rect.left      = x1;
      rect.top       = y1;
      rect.right     = x2;
      rect.bottom    = y2;

      return add_rect(rect);

   }

   bool graphics_path::add_rect(LPCRECT lpcrect)
   {

      return add_rect(lpcrect->left, lpcrect->top, lpcrect->right, lpcrect->bottom);

   }

   bool graphics_path::add_line(point p1, point p2)
   {

      return add_line(p1.x, p1.y, p2.x, p2.y);

   }

   bool graphics_path::add_line(point p)
   {

      return add_line(p.x, p.y);

   }

   bool graphics_path::add_lines(const POINT * lppoint, int32_t nCount)
   {

      bool bOk = true;

      for(int32_t i = 0; i < nCount; i++)
      {

         if(!add_line(lppoint[i]))
            bOk = false;
      }

      return bOk;

   }

   bool graphics_path::add_move(point p)
   {

      return add_move(p.x, p.y);

   }

   void * graphics_path::detach()
   {

      throw interface_only_exception(get_app());

   }

   
} // namespace ca






