//
//  c_os_simple_brush.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once


class CLASS_DECL_BOOT simple_brush
{
public:
   
   enum e_type
   {
      type_null,
      type_solid,
      type_linear_gradient_point_color,
      
   };
   
   
   e_type                  m_etype;
   COLORREF                m_cr;
   POINT                   m_pt1;
   POINT                   m_pt2;
   COLORREF                m_cr1;
   COLORREF                m_cr2;
   CGGradientRef           m_gradient;
   CGColorRef              m_color;
   CGColorSpaceRef         m_colorspace;
   
   
   simple_brush();
   ~simple_brush();
   
   
   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(simple_graphics & g, COLORREF cr);
   bool create_linear_gradient(simple_graphics & g, POINT p1, POINT p2, COLORREF cr1, COLORREF cr2);
   bool destroy();
   
   
   // platform-specific
   bool from_stock(int iId);
   
   virtual void * get_os_data() const;
   
};
