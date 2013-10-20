#pragma once




class CLASS_DECL_BOOT simple_solid_brush :
   public simple_brush
{
public:

   
   inline simple_solid_brush(simple_graphics & g, COLORREF cr);

   
};



inline simple_solid_brush::simple_solid_brush(simple_graphics & g, COLORREF cr)
{
   
   create_solid(g, cr);
   
}





