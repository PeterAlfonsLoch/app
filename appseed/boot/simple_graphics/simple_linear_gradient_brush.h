#pragma once


class CLASS_DECL_ca simple_linear_gradient_brush :
   public simple_brush
{
public:

   
   inline simple_linear_gradient_brush(simple_graphics & g, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLORREF cr1, COLORREF cr2);
   inline simple_linear_gradient_brush(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);

};


inline simple_linear_gradient_brush::simple_linear_gradient_brush(simple_graphics & g, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLORREF cr1, COLORREF cr2)
{
   
   create_linear_gradient(g, point_coord(x1, y1), point_coord(x2, y2), cr1, cr2);
   
}


inline simple_linear_gradient_brush::simple_linear_gradient_brush(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2)
{
   
   create_linear_gradient(g, np1, np2, cr1, cr2);
   
}
