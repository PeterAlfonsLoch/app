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


   bool graphics_path::add_line(int x1, int y1, int x2, int y2)
   {

      bool bOk1 = add_line(x1, y1);

      bool bOk2 = add_line(x2, y2);

      return bOk1 && bOk2;

   }


   bool graphics_path::add_line(point p1, point p2)
   {

      bool bOk1 = add_line(p1);

      bool bOk2 = add_line(p2);

      return bOk1 && bOk2;

   }

   bool graphics_path::add_line(int x, int y)
   {

      throw interface_only_exception(get_app());

   }

   bool graphics_path::add_line(point p)
   {

      throw interface_only_exception(get_app());

   }

   bool graphics_path::add_move(int x, int y)
   {

      return add_move(point(x, y));

   }

   bool graphics_path::add_move(point p)
   {

      return add_move(p.x, p.y);

   }

} // namespace ca
