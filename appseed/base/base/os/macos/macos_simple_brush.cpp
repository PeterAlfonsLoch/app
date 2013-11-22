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
   
   m_etype = type_solid;
   
   m_cr = 0;
   
}


simple_brush::~simple_brush()
{
   
   
}

bool simple_brush::create_solid(simple_graphics & g, COLORREF cr)
{
   
   m_etype = type_solid;
   
   m_cr = cr;
   
   return true;
   
}

bool simple_brush::create_linear_gradient(simple_graphics & g, POINT p1, POINT p2, COLORREF cr1, COLORREF cr2)
{
   
   m_etype = type_linear_gradient_point_color;
   
   m_pt1 = p1;
   m_pt2 = p2;
   m_cr1 = cr1;
   m_cr2 = cr2;
   
   return true;
   
}


bool simple_brush::from_stock(int iId)
{
   
   if(iId != NULL_BRUSH)
      return false;
   
   m_etype = type_null;
   
   return true;
   
}



bool simple_brush::destroy()
{
   
   m_etype = type_solid;
   
   m_cr = 0;
   
   return true;
   
}



void * simple_brush::get_os_data() const
{
   
   if(m_etype == type_null)
   {
      return NULL;
   }
   else if(m_etype == type_linear_gradient_point_color)
   {
      return m_gradient;
   }
   else if(m_etype == type_solid)
   {
      return m_color;
   }
   else
   {
      return NULL;
   }
   
   
}