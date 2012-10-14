#include "framework.h"
#undef new
#include <gdiplus.h>


simple_brush::simple_brush()
{

   m_hbrush = NULL;

}

simple_brush::~simple_brush()
{
   
   if(m_hbrush != NULL)
   {

      destroy();

   }

}

bool simple_brush::create_solid(COLORREF cr)
{

   if(m_hbrush != NULL)
      destroy();

   m_bDelete = true;

   m_hbrush = ::CreateSolidBrush(cr);

   if(m_hbrush == NULL)
      return false;

   return true;

}


bool simple_brush::create_liner_gradient(POINT np1, POINT np2, COLORREF cr1, COLORREF cr2)
{

   if(m_pbrush != NULL)
   {

      destroy();

   }

   Gdiplus::Point p1;
   Gdiplus::Point p2;

   p1.X = np1.x;
   p1.Y = np1.y;
   
   p2.X = np2.x;
   p2.Y = np2.y;

   m_pbrush = new Gdiplus::LinearGradientBrush(p1, p2. Gdiplus::Color(crOut), GdiplusColor(cr2)));

   if(m_pbrush == NULL)
      return false;

}


bool simple_brush::from_stock(int iId)
{

   if(m_hbrush != NULL)
      destroy();

   m_bDelete = false;

   m_hbrush = (HBRUSH) ::GetStockObject(iId);

   if(m_hbrush == NULL)
      return false;

   if(::GetObjectType(m_hbrush) != OBJ_BRUSH)
   {
      
      m_hbrush = NULL;

      return false;

   }

   return true;

}



bool simple_brush::destroy()
{

   if(!m_bDelete)
      return false;
   
   if(m_hbrush == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hbrush) != FALSE;

   m_hbrush = NULL;

   if(!bOk)
      return false;

   return true;

}

