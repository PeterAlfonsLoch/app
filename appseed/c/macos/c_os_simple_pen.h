//
//  c_os_simple_pen.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//

#pragma once


class CLASS_DECL_c simple_pen
{
public:
   
   
   enum e_style
   {
      style_stock,
      style_solid,
   };
   
   
   int                  m_iStock;
   e_style              m_estyle;
   int                  m_iWidth;
   COLORREF             m_cr;
   
   
   simple_pen();
   ~simple_pen();
   
   bool create_solid(simple_graphics & g, COLORREF cr, int iWidth);
   bool from_stock(int iId);
   
   bool destroy();
   
   simple_pen & operator = (const simple_pen & pen);
   
};


