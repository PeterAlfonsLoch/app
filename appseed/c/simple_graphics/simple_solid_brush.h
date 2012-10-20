#pragma once




class CLASS_DECL_c simple_solid_brush :
   public simple_brush
{
public:

   simple_solid_brush(simple_graphics & g, COLORREF cr)
   {
      create_solid(g, cr);
   }

};
