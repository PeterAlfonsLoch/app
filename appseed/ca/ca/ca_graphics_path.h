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

      virtual bool add_arc(const RECT & rect, int32_t iStart, int32_t iAngle);

      virtual bool add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool add_line(point p1, point p2);

      virtual bool add_lines(const POINT * lppoint, int32_t nCount);

      virtual bool add_line(int32_t x, int32_t y);
      virtual bool add_line(point p);

      virtual bool add_move(int32_t x, int32_t y);
      virtual bool add_move(point p);

      virtual bool add_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool add_rect(LPCRECT lpcrect);

      virtual void * detach();

   };

   typedef smart_pointer < graphics_path > graphics_path_sp;

} // namespace ca
