//
//  c_os_simple_pen.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#include "framework.h"


simple_pen::simple_pen()
{
   
   m_iStock = -1;
   m_estyle = style_solid;
   m_iWidth = 0;
   m_cr = 0;
   m_psolidbrush = NULL;
   
}

simple_pen::~simple_pen()
{
   
}

bool simple_pen::create_solid(simple_graphics & g, int iWidth, COLORREF cr)
{
   
   m_iStock = -1;
   
   m_estyle    = style_solid;
   
   m_iWidth    = iWidth;
   
   m_cr = cr;

   D2D1_COLOR_F c;

   c.a = GetAValue(cr) / 255.0f;
   c.r = GetRValue(cr) / 255.0f;
   c.g = GetGValue(cr) / 255.0f;
   c.b = GetBValue(cr) / 255.0f;

   g.m_pdc->CreateSolidColorBrush(c, &m_psolidbrush);
   
   return TRUE;
   
}

bool simple_pen::from_stock(int iId)
{
   
   if(iId != NULL_PEN)
      return false;
   
   m_iStock = iId;
   
   return true;
   
   
}

bool simple_pen::destroy()
{
   
   m_iStock = -1;
   m_estyle = style_solid;
   m_iWidth = 0;
   m_cr = 0;
   
   
   return true;
   
}



simple_pen & simple_pen::operator = (const simple_pen & pen)
{
   
   m_iStock    = pen.m_iStock;
   
   m_estyle    = pen.m_estyle;
   
   m_iWidth    = pen.m_iWidth;
   
   m_cr  = pen.m_cr;
   
   return *this;
   
}



ID2D1Brush * simple_pen::get_os_brush()
{
   return m_psolidbrush;
}