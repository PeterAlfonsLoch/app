#pragma once




class CLASS_DECL_c simple_graphics :
   public os_simple_graphics
{
public:

   
   simple_graphics();
   ~simple_graphics();


   
   using ::os_simple_graphics::draw_line;
   inline bool draw_line(int x1, int y1, int x2, int y2);
   inline bool draw_line(POINT p1, POINT p2, simple_pen & pen);
   inline bool draw_line(POINT p1, POINT p2);

   using ::os_simple_graphics::rectangle;
   inline bool rectangle(const RECT & rect);

   using ::os_simple_graphics::draw_rect;
   inline bool draw_rect(const RECT & rect);
   inline bool draw_rect(const RECT & rect, simple_pen & pen);

   using ::os_simple_graphics::fill_rect;
   inline bool fill_rect(const RECT & rect);
   inline bool fill_rect(const RECT & rect, simple_brush & brush);

   using ::os_simple_graphics::fill_solid_rect;
   inline void fill_solid_rect(const RECT & rect, COLORREF clr);

};




inline bool simple_graphics::draw_line(int x1, int y1, int x2, int y2)
{
   
   return draw_line(x1, y1, x2, y2, m_pen);

}

inline bool simple_graphics::draw_line(POINT p1, POINT p2, simple_pen & pen)
{

   return draw_line(p1.x, p1.y, p2.x, p2.y, pen);

}

inline bool simple_graphics::draw_line(POINT p1, POINT p2)
{
   
   return draw_line(p1, p2, m_pen);

}




inline bool simple_graphics::draw_rect(const RECT & rect)
{

   return draw_rect(&rect, m_pen);

}

inline bool simple_graphics::draw_rect(const RECT & rect, simple_pen & pen)
{

   return draw_rect(&rect, pen);

}

inline bool simple_graphics::fill_rect(const RECT & rect)
{

   return fill_rect(&rect, m_brush);

}

inline bool simple_graphics::fill_rect(const RECT & rect, simple_brush & brush)
{

   return fill_rect(&rect, brush);

}

inline bool simple_graphics::rectangle(const RECT & rect)
{

   return rectangle(&rect);

}





