//
//  c_os_simple_brush.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#include "framework.h"


simple_brush::simple_brush()
{
   
   m_iStock = -1;
   
   m_estyle = style_solid;
   
   m_cr = 0;
   
}


simple_brush::~simple_brush()
{
   
   
}

bool simple_brush::create_solid(simple_graphics & g, COLORREF cr)
{
   
   m_iStock = -1;
   
   m_estyle = style_solid;
   
   m_cr = cr;
   
   return true;
   
}

bool simple_brush::create_linear_gradient(simple_graphics & g, POINT p1, POINT p2, COLORREF cr1, COLORREF cr2)
{
   
   m_estyle = style_linear_gradient;
   
   m_p1 = p1;
   m_p2 = p2;
   m_cr1 = cr1;
   m_cr2 = cr2;
   
   return true;
   
}


bool simple_brush::from_stock(int iId)
{
   
   if(iId != NULL_BRUSH)
      return false;
   
   m_iStock = iId;
   
   return true;
   
}



bool simple_brush::destroy()
{
   
   m_iStock = -1;
   
   m_estyle = style_solid;
   
   m_cr = 0;
   
   return true;
   
}

