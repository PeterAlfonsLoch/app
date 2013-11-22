#include "framework.h"


simple_pen::simple_pen()
{

   m_iStock = -1;
   m_etype = type_solid;
   m_iWidth = 0;
   m_cr = 0;

}

simple_pen::~simple_pen()
{

}

bool simple_pen::create_solid(::draw2d::graphics * pgraphics, COLORREF cr, int32_t iWidth)
{

   m_iStock = -1;

   m_etype    = type_solid;

   m_iWidth    = iWidth;

   m_cr = cr;


   return TRUE;

}

bool simple_pen::from_stock(int32_t iId)
{

   if(iId != NULL_PEN)
      return false;

   m_iStock = iId;

   return true;


}

bool simple_pen::destroy()
{

   m_iStock = -1;
   m_etype = type_solid;
   m_iWidth = 0;
   m_cr = 0;


   return true;

}



simple_pen & simple_pen::operator = (const simple_pen & pen)
{

   m_iStock = pen.m_iStock;

   m_etype    = pen.m_etype;

   m_iWidth    = pen.m_iWidth;

   m_cr  = pen.m_cr;

   return *this;

}


