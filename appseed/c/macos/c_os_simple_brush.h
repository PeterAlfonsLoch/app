//
//  c_os_simple_brush.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once


class CLASS_DECL_c simple_brush
{
public:
   
   enum e_style
   {
      style_stock,
     style_solid,
      
   };
   
   
   int                  m_estyle;
   COLORREF             m_cr;
   int                  m_iStock;
   
   
   simple_brush();
   ~simple_brush();
   
   
   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(COLORREF cr);
   bool destroy();
   
   
   // platform-specific
   bool from_stock(int iId);
   
   
};
