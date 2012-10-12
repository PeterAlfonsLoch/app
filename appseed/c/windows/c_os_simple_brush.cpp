#include "framework.h"


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

