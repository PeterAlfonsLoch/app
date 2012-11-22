#pragma once


namespace ca
{


   class CLASS_DECL_ca graphics_path :
      virtual public graphics_object
   {
   public:


      graphics_path();


      virtual bool begin_figure(bool bFill, ::ca::e_fill_mode efillmode);
      virtual bool end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool add_arc(const RECT & rect, int iStart, int iAngle);

      virtual bool add_line(int x1, int y1, int x2, int y2);
      virtual bool add_line(point p1, point p2);

      virtual bool add_line(int x, int y);
      virtual bool add_line(point p);

      virtual bool add_move(int x, int y);
      virtual bool add_move(point p);

   };

   typedef smart_pointer < graphics_path > graphics_path_sp;

} // namespace ca
