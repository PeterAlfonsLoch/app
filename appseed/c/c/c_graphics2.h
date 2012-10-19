#pragma once



class CLASS_DECL_c simple_solid_brush :
   public simple_brush
{
public:

   simple_solid_brush(COLORREF cr, simple_graphics & g)
   {
      create_solid(cr, g);
   }

};


class CLASS_DECL_c simple_linear_gradient_brush :
   public simple_brush
{
public:

   simple_linear_gradient_brush(int x1, int y1, int x2, int y2, COLORREF cr1, COLORREF cr2)
   {
      create_liner_gradient(point_coord(x1, y1), point_coord(x2, y2), cr1, cr2);
   }

   simple_linear_gradient_brush(POINT np1, POINT np2, COLORREF cr1, COLORREF cr2)
   {
      create_liner_gradient(np1, np2, cr1, cr2);
   }

};

class CLASS_DECL_c simple_solid_pen :
   public simple_pen
{
public:


   simple_solid_pen(simple_graphics & g, COLORREF cr, int iWidth = 1)
   {

      create_solid(g, cr, iWidth);

   }

};





