#pragma once


class CLASS_DECL_c simple_solid_pen :
   public simple_pen
{
public:


   inline simple_solid_pen(simple_graphics & g, COLORREF cr, int32_t iWidth = 1);
   

};



inline simple_solid_pen::simple_solid_pen(simple_graphics & g, COLORREF cr, int32_t iWidth)
{
   
   create_solid(g, cr, iWidth);
   
}