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
   
   m_etype = type_solid;
   m_dWidth = 0;
   m_cr = 0;
   
}

simple_pen::~simple_pen()
{
   
}

bool simple_pen::create_solid(simple_graphics & g, COLORREF cr, int iWidth)
{
   
   m_etype    = type_solid;
   
   m_dWidth    = iWidth;
   
   m_cr = cr;
   
   
   return TRUE;
   
}

bool simple_pen::from_stock(int iId)
{
   
   if(iId != NULL_PEN)
      return false;
   
   m_etype = type_null;
   
   return true;
   
   
}

bool simple_pen::destroy()
{
   
   m_etype = type_solid;
   m_dWidth = 0;
   m_cr = 0;
   
   
   return true;
   
}



simple_pen & simple_pen::operator = (const simple_pen & pen)
{
   
   m_etype    = pen.m_etype;
   
   m_dWidth    = pen.m_dWidth;
   
   m_cr  = pen.m_cr;
   
   return *this;
   
}


