#include "framework.h"


namespace ca
{


   graphics_path::graphics_path()
   {

   }


   bool graphics_path::begin_figure(bool bFill, ::ca::e_fill_mode efillmode)
   {

      throw interface_only_exception(get_app());

   }


   bool graphics_path::end_figure(bool bClose)
   {

      throw interface_only_exception(get_app());

   }

/*   point graphics_path::current_point()
   {

      throw interface_only_exception(get_app());

   }


   bool graphics_path::is_empty()
   {

      return !has_current_point();

   }

   bool graphics_path::has_current_point()
   {

      return !is_empty();

   }
   */

   bool graphics_path::add_arc(const RECT & rect, int iStart, int iAngle)
   {

      throw interface_only_exception(get_app());

   }

   bool graphics_path::add_rect(int x1, int y1, int x2, int y2)
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

   bool graphics_path::add_line(int x1, int y1, int x2, int y2)
   {

      return add_line(point(x1, y1), point(x2, y2));

   }


   bool graphics_path::add_line(point p1, point p2)
   {

      return add_line(p1.x, p1.y, p2.x, p2.y);

   }

   bool graphics_path::add_line(int x, int y)
   {

      return add_line(point(x, y));

   }

   bool graphics_path::add_line(point p)
   {

      return add_line(p.x, p.y);

   }

   bool graphics_path::add_lines(const POINT * lppoint, int nCount)
   {

      bool bOk = true;

      for(int i = 0; i < nCount; i++)
      {

         if(!add_line(lppoint[i]))
            bOk = false;
      }

      return bOk;

   }

   bool graphics_path::add_move(int x, int y)
   {

      return add_move(point(x, y));

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
