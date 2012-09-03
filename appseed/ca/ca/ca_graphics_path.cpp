#include "framework.h"


namespace ca
{


   graphics_path::graphics_path()
   {

   }


   bool graphics_path::start_figure()
   {

      throw interface_only_exception();

   }


   bool graphics_path::close_figure()
   {

      throw interface_only_exception();

   }



   point graphics_path::last_point()
   {

      throw interface_only_exception();

   }



   bool graphics_path::add_line(int x1, int y1, int x2, int y2)
   {

      throw interface_only_exception();

   }


   bool graphics_path::add_line(point p1, point p2)
   {

      throw interface_only_exception();

   }

   bool graphics_path::add_line(int x2, int y2)
   {

      point pt1 = last_point();
      
      return add_line(pt1.x, pt1.y, x2, y2);

   }

   bool graphics_path::add_line(point p2)
   {
      
      return add_line(last_point(), p2);

   }

} // namespace ca