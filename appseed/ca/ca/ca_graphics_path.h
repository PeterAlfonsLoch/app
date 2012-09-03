#pragma once


namespace ca
{


   class CLASS_DECL_ca graphics_path : 
      virtual public graphics_object
   {
   public:


      graphics_path();


      virtual bool start_figure();
      virtual bool close_figure();


      virtual point last_point();

      virtual bool add_line(int x1, int y1, int x2, int y2);
      virtual bool add_line(point p1, point p2);

      virtual bool add_line(int x2, int y2);
      virtual bool add_line(point p2);

   };

   typedef smart_pointer < graphics_path > graphics_path_sp;

} // namespace ca