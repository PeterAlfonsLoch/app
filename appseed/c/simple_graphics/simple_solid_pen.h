#pragma once


class CLASS_DECL_c simple_solid_pen :
   public simple_pen
{
public:


   simple_solid_pen(simple_graphics & g, COLORREF cr, int iWidth = 1)
   {

      create_solid(g, cr, iWidth);

   }

};


