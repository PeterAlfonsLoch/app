#include "framework.h"


simple_brush::simple_brush()
{

   m_iStock = NULL_BRUSH;

   m_etype = type_stock;

   m_cr = 0;

}


simple_brush::~simple_brush()
{


}

bool simple_brush::create_solid(simple_graphics & graphics, COLORREF cr)
{

   m_iStock = -1;

   m_etype = type_solid;

   m_cr = cr;

   return true;

}


bool simple_brush::from_stock(int32_t iId)
{

   if(iId != NULL_BRUSH)
      return false;

   m_etype = type_stock;

   m_iStock = iId;

   return true;

}



bool simple_brush::destroy()
{

   m_iStock = NULL_BRUSH;

   m_etype = type_stock;

   m_cr = 0;

}



bool simple_brush::create_linear_gradient(simple_graphics & graphics, POINT pt1, POINT pt2, COLORREF cr1, COLORREF cr2)
{

   m_iStock = -1;

   m_etype = type_linear_gradient;

   m_cr1 = cr1;

   m_cr2 = cr2;

   m_p1 = pt1;

   m_p2 = pt2;

   return true;

}
