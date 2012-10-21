#pragma once


class CLASS_DECL_c simple_linear_gradient_brush :
   public simple_brush
{
public:

   
   inline simple_linear_gradient_brush(simple_graphics & g, int x1, int y1, int x2, int y2, COLORREF cr1, COLORREF cr2);
   inline simple_linear_gradient_brush(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);

};


inline simple_linear_gradient_brush::simple_linear_gradient_brush(simple_graphics & g, int x1, int y1, int x2, int y2, COLORREF cr1, COLORREF cr2)
{
   
   create_linear_gradient(g, point_coord(x1, y1), point_coord(x2, y2), cr1, cr2);
   
}


inline simple_linear_gradient_brush::simple_linear_gradient_brush(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2)
{
   
   create_linear_gradient(g, np1, np2, cr1, cr2);
   
}
