#include "framework.h"


simple_brush::simple_brush()
{

   m_iStock = -1;

   m_iStyle = FillSolid;

   m_cr = 0;

}


simple_brush::~simple_brush()
{


}

bool simple_brush::create_solid(simple_graphics & graphics, COLORREF cr)
{

   m_iStock = -1;

   m_iStyle = FillSolid;

   m_cr = cr;

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

   m_iStyle = FillSolid;

   m_cr = 0;

}

